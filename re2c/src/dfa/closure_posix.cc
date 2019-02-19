#include <queue>

#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"


namespace re2c
{

/*
 * States of in-degree less than 2 are not joint points;
 * the fact that we are re-scanning this state means that we found
 * a better path to some previous state. Due to the right distributivity
 * of path comparison over path concatenation (X < Y => XZ < YZ) we
 * can just propagate the new path up to the next join point.
 */

struct cmp_gor1_t
{
    determ_context_t &ctx;

    cmp_gor1_t(determ_context_t &);
    bool operator()(const clos_t &, const clos_t &) const;
};

static void closure_posix_gor1(determ_context_t &);
static void closure_posix_gtop(determ_context_t &);

// we *do* want these to be inlined
static inline bool scan(determ_context_t &ctx, nfa_state_t *q, bool all);
static inline bool relax_gor1(determ_context_t &, const clos_t &);
static inline void relax_gtop(determ_context_t &, const clos_t &);


void closure_posix(determ_context_t &ctx)
{
    DRESET_CLSTATS(ctx);

    switch (ctx.dc_opts->posix_closure) {
        case POSIX_CLOSURE_GOR1: closure_posix_gor1(ctx); break;
        case POSIX_CLOSURE_GTOP: closure_posix_gtop(ctx); break;
        default: DASSERT(false); break;
    }

    DDUMP_CLSTATS(ctx);

    // cleanup
    closure_t &cl = ctx.dc_closure;
    for (clositer_t i = cl.begin(); i != cl.end(); ++i) {
        nfa_state_t *q = i->state;
        q->clos = NOCLOS;
        q->arcidx = 0;
        DASSERT(q->status == GOR_NOPASS && q->active == 0);
    }
}

/*
 * note [GOR1 SSSP algorithm]
 * Cherkassky-Goldberg-Radzik Single Source Shortest Path algorithm.
 *
 * Papers:
 * - "A heuristic improvement of the Bellman-Ford algorithm"
 *   by Goldberg, Radzik (1993)
 * - "Shortest paths algorithms: Theory and experimental evaluation"
 *   by Cherkassky, Goldberg, Radzik (1996)
 *
 * Complexity for digraph G = (V, E) is O(|V| * |E|), and O(|V| + |E|)
 * in case of acyclic graph.
 */
void closure_posix_gor1(determ_context_t &ctx)
{
    closure_t &state = ctx.dc_closure, &reach = ctx.dc_reached;
    std::vector<nfa_state_t*>
        &topsort = ctx.dc_gor1_topsort,
        &linear = ctx.dc_gor1_linear;

    // init: push configurations ordered by POSIX precedence (highest on top)
    state.clear();
    std::sort(reach.begin(), reach.end(), cmp_gor1_t(ctx));
    for (rcclositer_t c = reach.rbegin(); c != reach.rend(); ++c) {
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
                DINCCOUNT_CLSCANS(ctx);
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
                DINCCOUNT_CLSCANS(ctx);
                scan(ctx, q, true);
            }
            q->status = GOR_NOPASS;
        }
    }
}

inline cmp_gor1_t::cmp_gor1_t(determ_context_t &ctx) : ctx(ctx) {}

inline bool cmp_gor1_t::operator()(const clos_t &x, const clos_t &y) const
{
    const uint32_t xo = x.origin, yo = y.origin;
    if (xo == yo) return false;

    // if longest components differ, leftmost already incorporates that
    const kernel_t *k = ctx.dc_kernels[ctx.dc_origin];
    return unpack_leftmost(k->prectbl[xo * k->size + yo]) < 0;
}

bool scan(determ_context_t &ctx, nfa_state_t *q, bool all)
{
    bool any = false;
    clos_t x = ctx.dc_closure[q->clos];
    switch (q->type) {
        case nfa_state_t::NIL:
            if (q->arcidx == 0) {
                x.state = q->nil.out;
                any |= relax_gor1(ctx, x);
                ++q->arcidx;
            }
            break;
        case nfa_state_t::ALT:
            if (q->arcidx == 0) {
                x.state = q->alt.out1;
                any |= relax_gor1(ctx, x);
                ++q->arcidx;
            }
            if (q->arcidx == 1 && (!any || all)) {
                x.state = q->alt.out2;
                any |= relax_gor1(ctx, x);
                ++q->arcidx;
            }
            break;
        case nfa_state_t::TAG:
            if (q->arcidx == 0) {
                x.state = q->tag.out;
                x.tlook = ctx.dc_taghistory.push(x.tlook, q->tag.info);
                any |= relax_gor1(ctx, x);
                ++q->arcidx;
            }
            break;
        default:
            break;
    }
    return any;
}

bool relax_gor1(determ_context_t &ctx, const clos_t &x)
{
    closure_t &state = ctx.dc_closure;
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
        ctx.dc_gor1_topsort.push_back(q);
        q->arcidx = 0;
        return true;
    }
    else {
        q->active = 1;
        return false;
    }
}

/*
 * note [GTOP SSSP algorithm]
 * Global Topsort Single Source Shortest Path algorithm.
 *
 * It is well known that SSSP can be solved in linear time on DAGs (directed
 * acyclic graphs) by exploring graph nodes in topological order. In our case
 * TNFA is not a DAG (it may have cycles), but it is possible to compute fake
 * topologcal order by ignoring back edges.
 *
 * The algorithm works by having a priority queue of nodes, where priorities
 * are indices of nodes in fake topological ordering. At each step, the node
 * with the minimal priority is popped from queue and explored. All nodes
 * reachable from it on admissible arcs are enqueued, unless they are already
 * on queue.
 *
 * The resulting algorithm is of course not optimal: it can get stuck on
 * graphs with loops, because it will give priority to some of the loop nodes
 * compared to others for no good reason.
 *
 * However the algorithm is simple and optimal for DAGs, therefore we keep it.
 */

void closure_posix_gtop(determ_context_t &ctx)
{
    const closure_t &reach = ctx.dc_reached;
    closure_t &state = ctx.dc_closure;
    gtop_heap_t &heap = ctx.dc_gtop_heap;

    state.clear();
    for (cclositer_t c = reach.begin(); c != reach.end(); ++c) {
        relax_gtop(ctx, *c);
    }

    for (; !heap.empty(); ) {
        nfa_state_t *q = heap.top();
        heap.pop();
        q->active = 0;
        DINCCOUNT_CLSCANS(ctx);

        clos_t x = ctx.dc_closure[q->clos];
        switch (q->type) {
            case nfa_state_t::NIL:
                x.state = q->nil.out;
                relax_gtop(ctx, x);
                break;
            case nfa_state_t::ALT:
                x.state = q->alt.out1;
                relax_gtop(ctx, x);
                x.state = q->alt.out2;
                relax_gtop(ctx, x);
                break;
            case nfa_state_t::TAG:
                x.state = q->tag.out;
                x.tlook = ctx.dc_taghistory.push(x.tlook, q->tag.info);
                relax_gtop(ctx, x);
                break;
            default:
                break;
        }
    }
}

void relax_gtop(determ_context_t &ctx, const clos_t &c)
{
    closure_t &state = ctx.dc_closure;
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
        ctx.dc_gtop_heap.push(q);
    }
}

void orders(determ_context_t &ctx)
{
    closure_t &closure = ctx.dc_closure;
    const size_t nclos = closure.size();

    prectable_t *prectbl = ctx.dc_allocator.alloct<prectable_t>(nclos * nclos);
    static const int32_t P0 = pack(MAX_RHO, 0);

    for (size_t i = 0; i < nclos; ++i) {
        for (size_t j = i + 1; j < nclos; ++j) {
            int32_t rho1, rho2, l;
            l = precedence (ctx, closure[i], closure[j], rho1, rho2);
            prectbl[i * nclos + j] = pack(rho1, l);
            prectbl[j * nclos + i] = pack(rho2, -l);
        }
        prectbl[i * nclos + i] = P0;
    }

    ctx.dc_prectbl = prectbl;
}

} // namespace re2c
