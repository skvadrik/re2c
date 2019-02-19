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

struct cmp_gor1_t
{
    simctx_t &ctx;
    inline cmp_gor1_t(simctx_t &c) : ctx(c) {}

    bool operator()(const conf_t &x, const conf_t &y) const;
};

enum sssp_alg_t {GOR1, GTOP};

template<sssp_alg_t ALG> static int do_regexec(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int);
template<sssp_alg_t ALG> static void closure_posix(simctx_t &ctx);
static void make_one_step(simctx_t &, uint32_t);
static void make_final_step(simctx_t &);
static void update_offsets(simctx_t &ctx, const conf_t &c);
static void update_prectbl(simctx_t &);
static int32_t precedence(simctx_t &ctx, const conf_t &x, const conf_t &y, int32_t &prec1, int32_t &prec2);

// we *do* want these to be inlined
static inline bool scan(simctx_t &ctx, nfa_state_t *q, bool all);
static inline bool relax_gor1(simctx_t &, const conf_t &);
static inline void relax_gtop(simctx_t &, const conf_t &);

int regexec_nfa_posix(const regex_t *preg, const char *string
    , size_t nmatch, regmatch_t pmatch[], int eflags)
{
    return preg->flags & REG_GTOP
        ? do_regexec<GTOP>(preg, string, nmatch, pmatch, eflags)
        : do_regexec<GOR1>(preg, string, nmatch, pmatch, eflags);
}

template<sssp_alg_t ALG>
int do_regexec(const regex_t *preg, const char *string
    , size_t nmatch, regmatch_t pmatch[], int)
{
    simctx_t &ctx = *preg->simctx;
    init(ctx, string);

    // root state can be non-core, so we pass zero as origin to avoid checks
    const conf_t c0(ctx.nfa->root, 0, history_t::ROOT);
    ctx.reach.push_back(c0);
    closure_posix<ALG>(ctx);
    for (;;) {
        const uint32_t sym = static_cast<uint8_t>(*ctx.cursor++);
        if (ctx.state.empty() || sym == 0) break;
        make_one_step(ctx, sym);
        closure_posix<ALG>(ctx);
    }
    make_final_step(ctx);

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

void make_one_step(simctx_t &ctx, uint32_t sym)
{
    confset_t &state = ctx.state, &reach = ctx.reach;
    size_t j = 0;
    reach.clear();

    for (cconfiter_t i = state.begin(), e = state.end(); i != e; ++i) {
        nfa_state_t *s = i->state;

        s->clos = NOCLOS;
        s->arcidx = 0;
        DASSERT(s->status == GOR_NOPASS && s->active == 0);

        if (s->type == nfa_state_t::RAN) {
            for (const Range *r = s->ran.ran; r; r = r->next()) {
                if (r->lower() <= sym && sym < r->upper()) {
                    const conf_t c(s->ran.out, s->coreid, history_t::ROOT);
                    reach.push_back(c);
                    state[j++] = *i;
                    update_offsets(ctx, *i);
                    break;
                }
            }
        }
        else if (s->type == nfa_state_t::FIN) {
            update_offsets(ctx, *i);
        }
    }

    state.resize(j);
    std::swap(ctx.offsets1, ctx.offsets2);

    update_prectbl(ctx);

    ctx.hist.nodes.clear();

    ++ctx.step;
}

void make_final_step(simctx_t &ctx)
{
    for (cconfiter_t i = ctx.state.begin(), e = ctx.state.end(); i != e; ++i) {
        nfa_state_t *s = i->state;

        s->clos = NOCLOS;
        s->arcidx = 0;
        DASSERT(s->status == GOR_NOPASS && s->active == 0);

        if (s->type == nfa_state_t::FIN) {
            update_offsets(ctx, *i);
        }
    }
}

template<>
void closure_posix<GOR1>(simctx_t &ctx)
{
    confset_t &state = ctx.state, &reach = ctx.reach;
    std::vector<nfa_state_t*>
        &topsort = ctx.gor1_topsort,
        &linear = ctx.gor1_linear;

    // init: push configurations ordered by POSIX precedence (highest on top)
    state.clear();
    std::sort(reach.begin(), reach.end(), cmp_gor1_t(ctx));
    for (rcconfiter_t c = reach.rbegin(); c != reach.rend(); ++c) {
        nfa_state_t *q = c->state;
        if (q->clos == NOCLOS) {
            q->clos = static_cast<uint32_t>(state.size());
            state.push_back(*c);
        }
        else {
            state[q->clos] = *c;
        }
        topsort.push_back(q);
    }

    for (; !topsort.empty(); ) {

        // 1st pass: depth-first postorder traversal of admissible subgraph
        for (; !topsort.empty(); ) {
            nfa_state_t *q = topsort.back();
            if (q->status == GOR_LINEAR) {
                topsort.pop_back();
            }
            else {
                q->status = GOR_TOPSORT;
                if (!scan(ctx, q, false)) {
                    q->status = GOR_LINEAR;
                    topsort.pop_back();
                    linear.push_back(q);
                }
            }
        }

        // 2nd pass: linear scan of topologically ordered states
        for (; !linear.empty(); ) {
            nfa_state_t *q = linear.back();
            linear.pop_back();
            if (q->active) {
                q->active = 0;
                q->arcidx = 0;
                scan(ctx, q, true);
            }
            q->status = GOR_NOPASS;
        }
    }
}

inline bool cmp_gor1_t::operator()(const conf_t &x, const conf_t &y) const
{
    const uint32_t xo = x.origin, yo = y.origin;
    return xo != yo
        && unpack_leftmost(ctx.prectbl1[xo * ctx.nfa->ncores + yo]) < 0;
}

bool scan(simctx_t &ctx, nfa_state_t *q, bool all)
{
    bool any = false;

    const conf_t &x = ctx.state[q->clos];
    const uint32_t o = x.origin;
    const int32_t h = x.thist;

    switch (q->type) {
        case nfa_state_t::NIL:
            if (q->arcidx == 0) {
                any |= relax_gor1(ctx, conf_t(q->nil.out, o, h));
                ++q->arcidx;
            }
            break;
        case nfa_state_t::ALT:
            if (q->arcidx == 0) {
                any |= relax_gor1(ctx, conf_t(q->alt.out1, o, h));
                ++q->arcidx;
            }
            if (q->arcidx == 1 && (!any || all)) {
                any |= relax_gor1(ctx, conf_t(q->alt.out2, o, h));
                ++q->arcidx;
            }
            break;
        case nfa_state_t::TAG:
            if (q->arcidx == 0) {
                any |= relax_gor1(ctx, conf_t(q->tag.out, o
                    , ctx.hist.push(h, ctx.step, q->tag.info, o)));
                ++q->arcidx;
            }
            break;
        default:
            break;
    }

    return any;
}

bool relax_gor1(simctx_t &ctx, const conf_t &x)
{
    confset_t &state = ctx.state;
    nfa_state_t *q = x.state;
    const uint32_t idx = q->clos;
    int32_t p1, p2;

    if (idx == NOCLOS) {
        q->clos = static_cast<uint32_t>(state.size());
        state.push_back(x);
    }
    else if (q->indeg < 2
        || precedence(ctx, x, state[idx], p1, p2) < 0) {
        state[idx] = x;
    }
    else {
        return false;
    }

    if (q->status == GOR_NOPASS) {
        ctx.gor1_topsort.push_back(q);
        q->arcidx = 0;
        return true;
    }
    else {
        q->active = 1;
        return false;
    }
}

template<>
void closure_posix<GTOP>(simctx_t &ctx)
{
    const confset_t &reach = ctx.reach;
    confset_t &state = ctx.state;
    gtop_heap_t &heap = ctx.gtop_heap;

    state.clear();
    for (cconfiter_t c = reach.begin(); c != reach.end(); ++c) {
        relax_gtop(ctx, *c);
    }

    for (; !heap.empty(); ) {
        nfa_state_t *q = heap.top();
        heap.pop();
        q->active = 0;

        const conf_t &x = state[q->clos];
        const uint32_t o = x.origin;
        const int32_t h = x.thist;

        switch (q->type) {
            case nfa_state_t::NIL:
                relax_gtop(ctx, conf_t(q->nil.out, o, h));
                break;
            case nfa_state_t::ALT:
                relax_gtop(ctx, conf_t(q->alt.out1, o, h));
                relax_gtop(ctx, conf_t(q->alt.out2, o, h));
                break;
            case nfa_state_t::TAG:
                relax_gtop(ctx, conf_t(q->tag.out, o
                    , ctx.hist.push(h, ctx.step, q->tag.info, o)));
                break;
            default:
                break;
        }
    }
}

void relax_gtop(simctx_t &ctx, const conf_t &c)
{
    confset_t &state = ctx.state;
    nfa_state_t *q = c.state;
    const uint32_t idx = q->clos;
    int32_t p1, p2;

    if (idx == NOCLOS) {
        q->clos = static_cast<uint32_t>(state.size());
        state.push_back(c);
    }
    else if (q->indeg < 2
        || precedence(ctx, c, state[idx], p1, p2) < 0) {
        state[idx] = c;
    }
    else {
        return;
    }

    if (!q->active) {
        q->active = 1;
        ctx.gtop_heap.push(q);
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

void update_prectbl(simctx_t &ctx)
{
    cconfiter_t b = ctx.state.begin(), e = ctx.state.end(), c, d;
    const size_t ncores = ctx.nfa->ncores;
    int32_t *ptbl = ctx.prectbl2;
    const int32_t p0 = pack(MAX_RHO, 0);

    for (c = b; c != e; ++c) {
        nfa_state_t *s = c->state;
        DASSERT (s->type == nfa_state_t::RAN);
        ptbl[s->coreid * ncores + s->coreid] = p0;

        for (d = c + 1; d != e; ++d) {
            nfa_state_t *q = d->state;
            int32_t prec1, prec2;
            int32_t prec = precedence(ctx, *c, *d, prec1, prec2);
            ptbl[s->coreid * ncores + q->coreid] = pack(prec1, prec);
            ptbl[q->coreid * ncores + s->coreid] = pack(prec2, -prec);
        }
    }
    std::swap(ctx.prectbl1, ctx.prectbl2);
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
    }
    else {
        return unpack_leftmost(ctx.prectbl1[orig1 * ctx.nfa->ncores + orig2]);
    }

    DASSERT(false); // unreachable
    return 0;
}

} // namespace libre2c
} // namespace re2c

