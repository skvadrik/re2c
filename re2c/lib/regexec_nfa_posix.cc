#include <queue>

#include "lib/lex.h"
#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/options/opt.h"
#include "src/options/warn.h"
#include "src/debug/debug.h"
#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"


namespace re2c {

static void reach_on_symbol(simctx_t &, uint32_t);
static void closure_posix(simctx_t &);
static void relax(simctx_t &, const conf_t &, worklist_t &);
static int32_t precedence(simctx_t &, const conf_t &, const conf_t &, int32_t &, int32_t &);

int regexec_nfa_posix(const regex_t *preg, const char *string, size_t nmatch,
    regmatch_t pmatch[], int)
{
    simctx_t ctx(preg, string);
    const nfa_t *nfa = ctx.nfa;

    const conf_t c0 = {nfa->root, index(nfa, nfa->root), HROOT};
    ctx.reach.push_back(c0);
    closure_posix(ctx);

    for (;;) {
        const uint32_t sym = static_cast<uint8_t>(*ctx.cursor++);
        if (ctx.state.empty() || sym == 0) break;
        reach_on_symbol(ctx, sym);
        ++ctx.step;
        closure_posix(ctx);
    }

    return finalize(ctx, string, nmatch, pmatch);
}

void reach_on_symbol(simctx_t &ctx, uint32_t sym)
{
    const nfa_t *nfa = ctx.nfa;
    const confset_t &state = ctx.state;
    confset_t &reach = ctx.reach;
    cconfiter_t b = state.begin(), e = state.end(), i;

    reach.clear();
    for (i = b; i != e; ++i) {
        nfa_state_t *s = i->state;
        if (s->type == nfa_state_t::RAN) {
            for (const Range *r = s->ran.ran; r; r = r->next()) {
                if (r->lower() <= sym && sym < r->upper()) {
                    conf_t c = {s->ran.out, index(nfa, s), i->thist};
                    reach.push_back(c);
                }
            }
        }
    }
}

void closure_posix(simctx_t &ctx)
{
    const nfa_t *nfa = ctx.nfa;
    const confset_t &reach = ctx.reach;
    confset_t &state = ctx.state;

    worklist_t wl;
    state.clear();

    for (cconfiter_t c = reach.begin(); c != reach.end(); ++c) {
        relax(ctx, *c, wl);
    }

    for (; !wl.empty(); ) {
        nfa_state_t *q = wl.top();
        wl.pop();
        q->active = 0;
        conf_t x = state[q->clos];

        switch (q->type) {
            case nfa_state_t::NIL:
                x.state = q->nil.out;
                relax(ctx, x, wl);
                break;
            case nfa_state_t::ALT:
                x.state = q->alt.out1;
                relax(ctx, x, wl);
                x.state = q->alt.out2;
                relax(ctx, x, wl);
                break;
            case nfa_state_t::TAG:
                x.state = q->tag.out;
                x.thist = ctx.hist.push(x.thist, ctx.step, q->tag.info);
                relax(ctx, x, wl);
                break;
            case nfa_state_t::FIN:
                ctx.marker = ctx.cursor + 1;
                ctx.hidx = x.thist;
                ctx.rule = 0;
                break;
            case nfa_state_t::RAN:
                break;
        }
    }

    confiter_t b = state.begin(), e = state.end(), i, j;

    for (i = b; i != e; ++i) {
        i->state->clos = NOCLOS;
        DASSERT(i->state->active == 0);
    }

    // drop "inner" states (non-final without outgoing non-epsilon transitions)
    e = std::partition(b, e, ran_or_fin_t());
    size_t n = static_cast<size_t>(e - b);
    state.resize(n);

    int32_t *prec = ctx.prec_next;
    const size_t nstates = nfa->size;
    for (i = b; i != e; ++i) {
        uint32_t ix = index(nfa, i->state);
        for (j = i + 1; j != e; ++j) {
            uint32_t jx = index(nfa, j->state);
            int32_t rho1, rho2, l;
            l = precedence(ctx, *i, *j, rho1, rho2);
            prec[ix * nstates + jx] = pack(rho1, l);
            prec[jx * nstates + ix] = pack(rho2, -l);
        }
        prec[ix * nstates + ix] = 0;
    }
    std::swap(ctx.prec, ctx.prec_next);
}

void relax(simctx_t &ctx, const conf_t &c, worklist_t &wl)
{
    confset_t &state = ctx.state;
    nfa_state_t *q = c.state;
    const uint32_t idx = q->clos;
    int32_t h1, h2;

    // first time we see this state
    if (idx == NOCLOS) {
        q->clos = static_cast<uint32_t>(state.size());
        state.push_back(c);
    }

    // States of in-degree less than 2 are not joint points;
    // the fact that we are re-scanning this state means that we found
    // a better path to some previous state. Due to the right distributivity
    // of path comparison over path concatenation (X < Y => XZ < YZ) we
    // can just propagate the new path up to the next join point.
    else if (q->indeg < 2) {
        state[idx] = c;
    }

    // join point; compare the new path and the old path
    else if (precedence(ctx, c, state[idx], h1, h2) < 0) {
        state[idx] = c;
    }

    // the previous path was better, discard the new one
    else {
        q = NULL;
    }

    if (q != NULL && !q->active) {
        q->active = 1;
        wl.push(q);
    }
}

int32_t precedence(simctx_t &ctx, const conf_t &x, const conf_t &y
    , int32_t &rhox, int32_t &rhoy)
{
    const size_t nstates = ctx.nfa->size;
    const std::vector<Tag> &tags = ctx.nfa->tags;
    const uint32_t xl = x.thist, yl = y.thist;
    const uint32_t xo = x.origin, yo = y.origin;

    if (xl == yl && xo == yo) {
        rhox = rhoy = MAX_RHO;
        return 0;
    }

    history_t &hist = ctx.hist;
    tag_path_t &p1 = hist.path1, &p2 = hist.path2;
    hist.reconstruct(p1, xl, ctx.step);
    hist.reconstruct(p2, yl, ctx.step);
    tag_path_t::const_reverse_iterator
        i1 = p1.rbegin(), e1 = p1.rend(), j1 = i1, g1,
        i2 = p2.rbegin(), e2 = p2.rend(), j2 = i2, g2;

    const bool fork_frame = xo == yo;

    // longest precedence
    if (fork_frame) {
        // find fork
        for (; j1 != e1 && j2 != e2 && *j1 == *j2; ++j1, ++j2);
        rhox = rhoy = j1 > i1
            ? tags[(j1 - 1)->idx].height : MAX_RHO;
    }
    else {
        // get precedence table and size of the origin state
        rhox = unpack_longest(ctx.prec[xo * nstates + yo]);
        rhoy = unpack_longest(ctx.prec[yo * nstates + xo]);
    }
    for (g1 = j1; g1 != e1; ++g1) {
        rhox = std::min(rhox, tags[g1->idx].height);
    }
    for (g2 = j2; g2 != e2; ++g2) {
        rhoy = std::min(rhoy, tags[g2->idx].height);
    }
    if (rhox > rhoy) return -1;
    if (rhox < rhoy) return 1;

    // leftmost precedence
    if (fork_frame) {
        // equal => not less
        if (j1 == e1 && j2 == e2) return 0;

        // shorter => less
        if (j1 == e1) return -1;
        if (j2 == e2) return 1;

        const uint32_t idx1 = j1->idx, idx2 = j2->idx;
        const bool neg1 = j1->neg, neg2 = j2->neg;

        // can't be both closing
        DASSERT(!(idx1 % 2 == 1 && idx2 % 2 == 1));

        // closing vs opening: closing wins
        if (idx1 % 2 == 1) return -1;
        if (idx2 % 2 == 1) return 1;

        // can't be both negative
        DASSERT(!(neg1 && neg2));

        // positive vs negative: positive wins
        if (neg1) return 1;
        if (neg2) return -1;

        // positive vs positive: smaller wins
        // (this case is only possible because multiple
        // top-level RE don't have proper negative tags)
        if (idx1 < idx2) return -1;
        if (idx1 > idx2) return 1;
    }
    else {
        return unpack_leftmost(ctx.prec[xo * nstates + yo]);
    }

    // unreachable
    DASSERT(false);
    return 0;
}

} // namespace re2c

