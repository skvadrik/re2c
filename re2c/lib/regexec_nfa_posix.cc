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
static void update_prectbl_naive(simctx_t &ctx);
static int32_t precedence(simctx_t &ctx, const conf_t &x, const conf_t &y, int32_t &prec1, int32_t &prec2);

// we *do* want these to be inlined
static inline bool scan(simctx_t &ctx, nfa_state_t *q, bool all);
static inline bool relax_gor1(simctx_t &, const conf_t &);
static inline void relax_gtop(simctx_t &, const conf_t &);
static inline int32_t leftprec(simctx_t &, tag_info_t info1, tag_info_t info2, bool last1, bool last2);

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
    const conf_t c0(ctx.nfa->root, 0, HROOT);
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
                    const conf_t c(s->ran.out, s->coreid, HROOT);
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

    if (!(ctx.flags & REG_SLOWPREC)) {
        update_prectbl(ctx);
    }
    else {
        update_prectbl_naive(ctx);
    }

    ctx.hist.init();
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
                    , ctx.hist.push1(h, q->tag.info)));
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

    if (q->status == GOR_TOPSORT) {
        return false;
    }

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
                    , ctx.hist.push1(h, q->tag.info)));
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
    tag_history_t &hist = ctx.hist;

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
            const tag_history_t::node_t &n = hist.node(i1);
            info1 = n.info;
            prec1 = std::min(prec1, tags[info1.idx].height);
            i1 = n.pred;
        }
        else {
            const tag_history_t::node_t &n = hist.node(i2);
            info2 = n.info;
            prec2 = std::min(prec2, tags[info2.idx].height);
            i2 = n.pred;
        }
    }
    if (i1 != HROOT) {
        DASSERT(fork_frame);
        const int32_t h = tags[hist.node(i1).info.idx].height;
        prec1 = std::min(prec1, h);
        prec2 = std::min(prec2, h);
    }

    // longest precedence
    if (prec1 > prec2) return -1;
    if (prec1 < prec2) return  1;

    // leftmost precedence
    return fork_frame
        ? leftprec(ctx, info1, info2, i1 == idx1, i2 == idx2)
        : unpack_leftmost(ctx.prectbl1[orig1 * ctx.nfa->ncores + orig2]);
}

int32_t leftprec(simctx_t &, tag_info_t info1, tag_info_t info2, bool last1, bool last2)
{
    // equal => not less
    if (last1 && last2) return 0;

    // shorter => less
    if (last1) return -1;
    if (last2) return  1;

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
    return 0;
}

void update_offsets(simctx_t &ctx, const conf_t &c)
{
    const size_t nsub = ctx.nsub;
    regoff_t *o;
    const std::vector<Tag> &tags = ctx.nfa->tags;
    nfa_state_t *s = c.state;
    bool *done = ctx.done;

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

    for (int32_t i = c.thist; i != HROOT; ) {
        const tag_history_t::node_t &n = ctx.hist.node(i);
        const Tag &tag = tags[n.info.idx];
        const size_t t = tag.ncap;
        regoff_t *off = o + t;
        if (!fictive(tag) && !done[t]) {
            done[t] = true;
            *off = n.info.neg ? -1 : static_cast<regoff_t>(ctx.step);
        }
        i = n.pred;
    }
}

void update_prectbl(simctx_t &ctx)
{
    const confset_t &state = ctx.state;
    const std::vector<Tag> &tags = ctx.nfa->tags;
    std::vector<const conf_t*> &sortcores = ctx.sortcores;
    std::vector<uint32_t> &fcount = ctx.fincount;
    std::vector<int32_t> stack = ctx.worklist;
    std::vector<histleaf_t> &level = ctx.histlevel;
    std::vector<histleaf_t>::reverse_iterator li, lj, lk, le;
    tag_history_t &hist = ctx.hist;
    const size_t ncores = ctx.nfa->ncores;
    int32_t *oldtbl = ctx.prectbl1, *newtbl = ctx.prectbl2;

    // Group core configurations by their history tree index, so that later
    // while traversing the tree we will know at once which configurations
    // (if any) are bound to the given tree node. We use counting sort, which
    // requires additional memory, but is fast and conveniently creates an
    // array of boundaries in the sorted configuration array.
    uint32_t maxfin = 0;
    for (cconfiter_t c = state.begin(), e = state.end(); c != e; ++c) {
        uint32_t &x = hist.node1(c->thist).finidx;
        if (x >= USED) {
            x = maxfin++;
            fcount[x] = 0;

            // mark all nodes down to root as used (unless marked already)
            for (int32_t i = hist.node(c->thist).pred; i >= HROOT; ) {
                uint32_t &y = hist.node1(i).finidx;
                if (y <= USED) break;
                y = USED;
                i = hist.node(i).pred;
            }
        }
        ++fcount[x];
    }
    fcount[maxfin] = 0;
    for (size_t i = 1; i <= maxfin; ++i) {
        fcount[i] += fcount[i - 1];
    }
    sortcores.resize(state.size());
    for (rcconfiter_t c = state.rbegin(), e = state.rend(); c != e; ++c) {
        sortcores[--fcount[hist.node1(c->thist).finidx]] = &*c;
    }

    // Depth-first traversal of the history tree. During traversal we grow
    // an array of items (one item per core configuration). Items are added
    // in tree nodes that have core configurations associated with them.
    // Each item represents one history. Items have immutable part (core ID,
    // origin) and mutable part (current minimal height, current tree index)
    // that changes as we return down the tree.
    level.clear();
    stack.push_back(0);
    while (!stack.empty()) {
        const int32_t n = stack.back();
        tag_history_t::node1_t &node = hist.node1(n);
        const uint32_t fidx = node.finidx;

        if (fidx == NONFIN) {
            // aborted branch of search tree, don't waste time
            stack.pop_back();
            continue;
        }

        if (node.next != -1) {
            // start or continue visiting subtrees rooted at this node
            const tag_history_t::arc_t &arc = hist.arc(node.next);
            stack.push_back(arc.node);
            node.next = arc.next;
            continue;
        }

        // all subtrees visited, it's time to process this node
        const int32_t h = n == 0 ? MAX_RHO : tags[hist.node(n).info.idx].height;
        li = level.rbegin();
        le = level.rend();

        if (fidx < USED) {
            // this node has leaf configurations, add them to level
            for (uint32_t k = fcount[fidx], e = fcount[fidx + 1]; k < e; ++k) {
                const conf_t *c = sortcores[k];
                const histleaf_t l = {c->state->coreid, c->origin, HROOT, h};
                level.push_back(l);
            }

            // compute precedence for newly added configurations
            const int32_t p0 = pack(h, 0);
            for (lj = level.rbegin(); lj != li; ++lj) {
                for (lk = lj; lk != li; ++lk) {
                    const uint32_t cj = lj->coreid, ck = lk->coreid;
                    const uint32_t oj = lj->origin, ok = lk->origin;
                    const bool fork = n != 0 || oj == ok;
                    if (fork) {
                        newtbl[cj * ncores + ck] = p0;
                        newtbl[ck * ncores + cj] = p0;
                    }
                    else {
                        newtbl[cj * ncores + ck] = oldtbl[oj * ncores + ok];
                        newtbl[ck * ncores + cj] = oldtbl[ok * ncores + oj];
                    }
                }
            }
        }

        // Each subtree appended a sequence of items to level. We can find
        // sequence boundaries by looking at tree index of each item: it is
        // equal to tree index of the corresponding subtree (except for the
        // leaf items added at this node; but we know where they start).

        // We must compute precedence for each pair of items from different
        // sequences (including leaf items added at this node), but not within
        // sequence boundaries: those histories fork higher up the subtree;
        // their precedence has already been computed and must not be touched.

        for (int32_t a = node.last; a != -1; ) {
            const tag_history_t::arc_t &arc = hist.arc(a);
            a = arc.prev;

            // for all the items of this subtree
            for (lk = li; li != le && li->hidx == arc.node; ++li) {

                // update height of each item coming from subtree
                li->height = std::min(li->height, h);

                // for all the level items to the right of this subtree
                for (lj = level.rbegin(); lj != lk; ++lj) {

                    const uint32_t ci = li->coreid, cj = lj->coreid;
                    const uint32_t oi = li->origin, oj = lj->origin;
                    const bool fork = n != 0 || oi == oj;
                    int32_t p1 = li->height, p2 = lj->height, p;

                    if (!fork) {
                        p1 = std::min(p1, unpack_longest(oldtbl[oi * ncores + oj]));
                        p2 = std::min(p2, unpack_longest(oldtbl[oj * ncores + oi]));
                    }

                    if (p1 > p2) {
                        p = -1;
                    }
                    else if (p1 < p2) {
                        p = 1;
                    }
                    else if (fork) {
                        const tag_info_t t1 = hist.node(li->hidx).info;
                        const tag_info_t t2 = hist.node(lj->hidx).info;
                        p = leftprec(ctx, t1, t2, t1 == NOINFO, t2 == NOINFO);
                    }
                    else {
                        p = unpack_leftmost(oldtbl[oi * ncores + oj]);
                    }

                    newtbl[ci * ncores + cj] = pack(p1, p);
                    newtbl[cj * ncores + ci] = pack(p2, -p);
                }
            }
        }

        // finally, downgrade tree index of all subtree items, making their
        // origins indistinguishable from each other for the previous level
        for (lj = level.rbegin(); lj != li; ++lj) {
            lj->hidx = n;
        }

        stack.pop_back();
    }

    std::swap(ctx.prectbl1, ctx.prectbl2);
}

// Old naive algorithm that has cubic complexity in the size of TNFA.
// Example that exhibits cubic behaviour is ((a?){1,N})*. In this example
// closure has O(N) states, and the compared histories have O(N) length.
void update_prectbl_naive(simctx_t &ctx)
{
    const confset_t &state = ctx.state;
    const size_t ncores = ctx.nfa->ncores;
    int32_t *newtbl = ctx.prectbl2;

    const int32_t p0 = pack(MAX_RHO, 0);

    for (cconfiter_t c = state.begin(), e = state.end(); c != e; ++c) {
        nfa_state_t *s = c->state;
        DASSERT (s->type == nfa_state_t::RAN);
        newtbl[s->coreid * ncores + s->coreid] = p0;

        for (cconfiter_t d = c + 1; d != e; ++d) {
            nfa_state_t *q = d->state;
            int32_t prec1, prec2;
            int32_t prec = precedence(ctx, *c, *d, prec1, prec2);
            newtbl[s->coreid * ncores + q->coreid] = pack(prec1, prec);
            newtbl[q->coreid * ncores + s->coreid] = pack(prec2, -prec);
        }
    }

    std::swap(ctx.prectbl1, ctx.prectbl2);
}

} // namespace libre2c
} // namespace re2c

