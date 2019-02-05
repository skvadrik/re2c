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

namespace {

typedef std::vector<tag_info_t> tag_path_t;

struct history_t
{
    struct node_t {
        uint32_t pred;
        uint32_t step;
        tag_info_t info;
    };

    std::vector<node_t> nodes;
    tag_path_t path1;
    tag_path_t path2;

    inline history_t(size_t nstates, size_t ntags);
    inline uint32_t push(uint32_t i, uint32_t step, tag_info_t info);
    inline void reconstruct(tag_path_t &, uint32_t, uint32_t);
    FORBID_COPY(history_t);
};

struct conf_t
{
    nfa_state_t *state;
    uint32_t origin;
    uint32_t thist;
};

struct ran_or_fin_t
{
    inline bool operator()(const conf_t &c);
};

struct cmp_gtop_t
{
    inline bool operator() (const nfa_state_t *x, const nfa_state_t *y) const;
};

typedef std::vector<conf_t> confset_t;
typedef confset_t::iterator confiter_t;
typedef confset_t::const_iterator cconfiter_t;
typedef confset_t::const_reverse_iterator rcconfiter_t;
typedef std::priority_queue<nfa_state_t*, std::vector<nfa_state_t*>
    , cmp_gtop_t> worklist_t;

struct simctx_t
{
    const nfa_t *nfa;
    confset_t reach;
    confset_t state;
    int32_t *prec;
    int32_t *prec_next;
    history_t hist;
    uint32_t hidx;
    uint32_t step;
    size_t rule;
    const char *cursor;
    const char *marker;

    inline simctx_t(const regex_t *preg, const char *string);
    FORBID_COPY(simctx_t);
};

} // anonymous namespace

static void reach_on_symbol(simctx_t &, uint32_t);
static void closure_posix(simctx_t &);
static void relax(simctx_t &, const conf_t &, worklist_t &);
static int32_t precedence(simctx_t &, const conf_t &, const conf_t &, int32_t &, int32_t &);
static inline uint32_t index(const nfa_t *, const nfa_state_t *);

int regexec_nfa_posix(const regex_t *preg, const char *string, size_t nmatch,
    regmatch_t pmatch[], int)
{
    simctx_t ctx(preg, string);
    const nfa_t *nfa = ctx.nfa;
    int result = REG_NOMATCH;

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

    ctx.cursor = ctx.marker;

    if (ctx.rule != Rule::NONE) {
        result = 0;

        regmatch_t *m = pmatch;
        m->rm_so = 0;
        m->rm_eo = ctx.cursor - string - 1;

        size_t todo = nmatch * 2, ntags = nfa->tags.size();
        bool *done = new bool[ntags];
        memset(done, 0, ntags * sizeof(bool));

        for (size_t i = ctx.hidx; todo > 0 && i != HROOT; ) {
            const history_t::node_t &n = ctx.hist.nodes[i];
            const size_t t = n.info.idx;
            if (!done[t]) {
                done[t] = true;
                const Tag &tag = nfa->tags[t];
                if (!fictive(tag) && tag.ncap < nmatch * 2) {
                    --todo;
                    const regoff_t off = n.info.neg ? -1 : static_cast<regoff_t>(n.step);
                    m = &pmatch[tag.ncap / 2 + 1];
                    if (tag.ncap % 2 == 0) {
                        m->rm_so = off;
                    }
                    else {
                        m->rm_eo = off;
                    }
                }
            }
            i = n.pred;
        }

        delete[] done;
    }

    return result;
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

simctx_t::simctx_t(const regex_t *preg, const char *string)
    : nfa(preg->nfa)
    , reach()
    , state()
    , prec(preg->prec_buf1)
    , prec_next(preg->prec_buf2)
    , hist(nfa->size, nfa->tags.size())
    , hidx(HROOT)
    , step(0)
    , rule(Rule::NONE)
    , cursor(string)
    , marker(string)
{
    state.reserve(nfa->size);
    reach.reserve(nfa->size);
}

history_t::history_t(size_t nstates, size_t ntags)
    : nodes()
    , path1()
    , path2()
{
    nodes.reserve(ntags * nstates);
    path1.reserve(ntags);
    path2.reserve(ntags);
}

uint32_t history_t::push(uint32_t idx, uint32_t step, tag_info_t info)
{
    const node_t x = {idx, step, info};
    nodes.push_back(x);
    return static_cast<uint32_t>(nodes.size() - 1);
}

void history_t::reconstruct(tag_path_t &path, uint32_t idx, uint32_t step)
{
    path.clear();
    for (; idx != HROOT; ) {
        const node_t &n = nodes[idx];
        if (n.step != step) break;
        path.push_back(n.info);
        idx = n.pred;
    }
}

uint32_t index(const nfa_t *nfa, const nfa_state_t *state)
{
    return static_cast<uint32_t>(state - nfa->states);
}

bool ran_or_fin_t::operator()(const conf_t &c)
{
    switch (c.state->type) {
        case nfa_state_t::RAN:
        case nfa_state_t::FIN: return true;
        default: return false;
    }
}

bool cmp_gtop_t::operator() (const nfa_state_t *x, const nfa_state_t *y) const
{
    return x->topord < y->topord;
}

} // namespace re2c

