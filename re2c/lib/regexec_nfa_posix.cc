#include <queue>
#include <stdio.h>

#include "lib/lex.h"
#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/options/opt.h"
#include "src/debug/debug.h"
#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"


namespace re2c {
namespace libre2c {

static void reach_on_symbol(simctx_t &, uint32_t);
static void closure_posix(simctx_t &);
static void update_offsets(simctx_t &ctx, const conf_t &c);
static void update_offsets_and_prectbl(simctx_t &);
static int32_t precedence(simctx_t &ctx, const conf_t &x, const conf_t &y, int32_t &prec1, int32_t &prec2);

// we *do* want this to be inlined
static inline void relax(simctx_t &, const conf_t &, worklist_t &);

int regexec_nfa_posix(const regex_t *preg, const char *string
    , size_t nmatch, regmatch_t pmatch[], int)
{
    simctx_t ctx(preg, string);
    const nfa_t *nfa = ctx.nfa;

    const conf_t c0 = {nfa->root, 0, history_t::ROOT};
    ctx.reach.push_back(c0);
    closure_posix(ctx);

    for (;;) {
        const uint32_t sym = static_cast<uint8_t>(*ctx.cursor++);
        if (ctx.state.empty() || sym == 0) break;
        reach_on_symbol(ctx, sym);
        update_offsets_and_prectbl(ctx);
        ++ctx.step;
        closure_posix(ctx);
    }

    for (cconfiter_t i = ctx.state.begin(), e = ctx.state.end(); i != e; ++i) {
        nfa_state_t *s = i->state;

        s->clos = NOCLOS;
        DASSERT(s->active == 0);

        if (s->type == nfa_state_t::FIN) {
            update_offsets(ctx, *i);
        }
    }

    if (ctx.rule == Rule::NONE) {
        return REG_NOMATCH;
    }

    regmatch_t *m = pmatch;
    m->rm_so = 0;
    m->rm_eo = ctx.marker - string - 1;
    const size_t n = std::min(ctx.nsub, 2 * nmatch);
    for (size_t t = 0; t < n; ++t) {
        const regoff_t off = ctx.offsets3[t];
        if (t % 2 == 0) {
            ++m;
            m->rm_so = off;
        }
        else {
            m->rm_eo = off;
        }
    }

    return 0;
}

void reach_on_symbol(simctx_t &ctx, uint32_t sym)
{
    confset_t &state = ctx.state, &reach = ctx.reach;

    reach.clear();
    size_t j = 0;
    for (cconfiter_t i = state.begin(), e = state.end(); i != e; ++i) {
        nfa_state_t *s = i->state;

        s->clos = NOCLOS;
        DASSERT(s->active == 0);

        if (s->type == nfa_state_t::RAN) {
            for (const Range *r = s->ran.ran; r; r = r->next()) {
                if (r->lower() <= sym && sym < r->upper()) {
                    conf_t c = {s->ran.out, s->coreid, history_t::ROOT};
                    reach.push_back(c);
                    state[j++] = *i;
                    break;
                }
            }
        }
        else if (s->type == nfa_state_t::FIN) {
            state[j++] = *i;
        }
    }
    state.resize(j);
}

void closure_posix(simctx_t &ctx)
{
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
                x.thist = ctx.hist.push(x.thist, ctx.step, q->tag.info, x.origin);
                relax(ctx, x, wl);
                break;
            default:
                break;
        }
    }
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

void update_offsets(simctx_t &ctx, const conf_t &c)
{
    const size_t nsub = ctx.nsub;
    bool *done = ctx.done;
    regoff_t *o;
    const std::vector<Tag> &tags = ctx.nfa->tags;
    nfa_state_t *s = c.state;

    if (s->type == nfa_state_t::FIN) {
        ctx.marker = ctx.cursor;
        ctx.rule = 0;
        o = ctx.offsets3;
    }
    else {
        o = ctx.offsets1 + s->coreid * nsub;
    }

    memcpy(o, ctx.offsets2 + c.origin * nsub, nsub * sizeof(regoff_t));
    memset(done, 0, nsub * sizeof(bool));

    for (int32_t i = c.thist; i != history_t::ROOT; ) {
        const history_t::node_t &n = ctx.hist.at(i);
        const Tag &tag = tags[n.info.idx];
        const size_t t = tag.ncap;
        if (!fictive(tag) && !done[t]) {
            done[t] = true;
            o[t] = n.info.neg ? -1 : static_cast<regoff_t>(ctx.step);
        }
        i = n.pred;
    }
}

void update_offsets_and_prectbl(simctx_t &ctx)
{
    cconfiter_t b = ctx.state.begin(), e = ctx.state.end(), c, d;
    const size_t ncores = ctx.nfa->ncores;
    int32_t *ptbl = ctx.prectbl2;
    const int32_t p0 = pack(MAX_RHO, 0);

    for (c = b; c != e; ++c) {
        update_offsets(ctx, *c);
    }
    std::swap(ctx.offsets1, ctx.offsets2);

    // precedence matrix
    for (c = b; c != e; ++c) {
        nfa_state_t *s = c->state;
        if (s->type != nfa_state_t::RAN) continue;

        ptbl[s->coreid * ncores + s->coreid] = p0;

        for (d = c + 1; d != e; ++d) {
            nfa_state_t *q = d->state;
            if (q->type != nfa_state_t::RAN) continue;

            int32_t prec1, prec2;
            int32_t prec = precedence(ctx, *c, *d, prec1, prec2);
            ptbl[s->coreid * ncores + q->coreid] = pack(prec1, prec);
            ptbl[q->coreid * ncores + s->coreid] = pack(prec2, -prec);
        }
    }
    std::swap(ctx.prectbl1, ctx.prectbl2);

    ctx.hist.nodes.clear();
}

int32_t precedence(simctx_t &ctx, const conf_t &x, const conf_t &y
    , int32_t &prec1, int32_t &prec2)
{
    const int32_t idx1 = x.thist, idx2 = y.thist;
    const uint32_t orig1 = x.origin, orig2 = y.origin;

    if (idx1 == idx2 && orig1 == orig2) {
        prec1 = prec2 = MAX_RHO;
        return 0;
    }

    const std::vector<Tag> &tags = ctx.nfa->tags;
    history_t &hist = ctx.hist;

    const bool fork_frame = orig1 == orig2;
    if (fork_frame) {
        prec1 = prec2 = MAX_RHO;
    }
    else {
        prec1 = unpack_longest(ctx.prectbl1[orig1 * ctx.nfa->ncores + orig2]);
        prec2 = unpack_longest(ctx.prectbl1[orig2 * ctx.nfa->ncores + orig1]);
    }

    tag_info_t info1, info2;
    int32_t i1 = idx1, i2 = idx2;
    for (; i1 != i2; ) {
        if (i1 > i2) {
            const history_t::node_t &n = hist.at(i1);
            info1 = n.info;
            prec1 = std::min(prec1, tags[info1.idx].height);
            i1 = n.pred;
        }
        else {
            const history_t::node_t &n = hist.at(i2);
            info2 = n.info;
            prec2 = std::min(prec2, tags[info2.idx].height);
            i2 = n.pred;
        }
    }
    if (i1 != history_t::ROOT) {
        DASSERT(fork_frame);
        const int32_t h = tags[hist.at(i1).info.idx].height;
        prec1 = std::min(prec1, h);
        prec2 = std::min(prec2, h);
    }

    // longest precedence
    if (prec1 > prec2) return -1;
    if (prec1 < prec2) return  1;

    // leftmost precedence
    if (fork_frame) {
        // equal => not less
        if (i1 == idx1 && i2 == idx2) return 0;

        // shorter => less
        if (i1 == idx1) return -1;
        if (i2 == idx2) return  1;

        const uint32_t tag1 = info1.idx, tag2 = info2.idx;
        const bool neg1 = info1.neg, neg2 = info2.neg;

        // can't be both closing
        DASSERT(!(tag1 % 2 == 1 && tag2 % 2 == 1));

        // closing vs opening: closing wins
        if (tag1 % 2 == 1) return -1;
        if (tag2 % 2 == 1) return  1;

        // can't be both negative
        DASSERT(!(neg1 && neg2));

        // positive vs negative: positive wins
        if (neg1) return  1;
        if (neg2) return -1;

        DASSERT(false);
    }
    else {
        return unpack_leftmost(ctx.prectbl1[orig1 * ctx.nfa->ncores + orig2]);
    }
}

} // namespace libre2c
} // namespace re2c

