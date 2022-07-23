#ifndef _RE2C_DFA_CLOSURE_POSIX_
#define _RE2C_DFA_CLOSURE_POSIX_

#include <queue>

#include "src/debug/debug.h"
#include "src/dfa/determinization.h"
#include "src/dfa/posix_precedence.h"
#include "src/nfa/nfa.h"
#include "src/util/check.h"

namespace re2c {

// States of in-degree less than 2 are not joint points; the fact that we are re-scanning this state
// means that we found a better path to some previous state. Due to the right distributivity of path
// comparison over path concatenation (X < Y => XZ < YZ) we can just propagate the new path up to
// the next join point.

template<typename ctx_t> void closure_cleanup(TnfaState* q);
template<typename ctx_t> static void closure_posix_gor1(ctx_t&);
template<typename ctx_t> static void closure_posix_gtop(ctx_t&);

// we *do* want these to be inlined
template<typename ctx_t> static inline void init_gor1(ctx_t& ctx);
template<typename ctx_t> static inline bool scan(ctx_t& ctx, TnfaState* q, bool all);
template<typename ctx_t> static inline bool relax_gor1(ctx_t&, const typename ctx_t::conf_t&);
template<typename ctx_t> static inline void relax_gtop(ctx_t&, const typename ctx_t::conf_t&);

inline void closure_posix(pdetctx_t& ctx) {
    DRESET_CLSTATS(ctx);

    ctx.history.detach();

    switch (ctx.dc_opts->posix_closure) {
    case PosixClosure::GOR1:
        closure_posix_gor1(ctx);
        break;
    case PosixClosure::GTOP:
        closure_posix_gtop(ctx);
        break;
    }

    DDUMP_CLSTATS(ctx);
}

template<typename ctx_t>
struct cmp_gor1_t {
    ctx_t& ctx;

    cmp_gor1_t(ctx_t& ctx) : ctx(ctx) {}

    bool operator()(const typename ctx_t::conf_t& x, const typename ctx_t::conf_t& y) const {
        // if longest components differ, leftmost already incorporates that
        const uint32_t xo = x.origin, yo = y.origin;
        return xo != yo && unpack_leftmost(ctx.oldprectbl[xo * ctx.oldprecdim + yo]) < 0;
    }
};

// note [GOR1 SSSP algorithm]
//
// Cherkassky-Goldberg-Radzik Single Source Shortest Path algorithm.
// Complexity for digraph G = (V, E) is O(|V| * |E|), and O(|V| + |E|) in case of acyclic graph.
//
// Papers:
//     - "A heuristic improvement of the Bellman-Ford algorithm" by Goldberg, Radzik (1993)
//     - "Shortest paths algorithms: Theory and experimental evaluation" by Cherkassky, Goldberg,
//       Radzik (1996)

template<typename ctx_t>
void closure_posix_gor1(ctx_t& ctx) {
    std::vector<TnfaState*>& topsort = ctx.gor1_topsort;
    std::vector<TnfaState*>& linear = ctx.gor1_linear;

    init_gor1(ctx);

    for (; !topsort.empty(); ) {
        // 1st pass: depth-first postorder traversal of admissible subgraph
        for (; !topsort.empty(); ) {
            TnfaState* q = topsort.back();
            if (q->status == GorPass::LINEAR) {
                topsort.pop_back();
            } else {
                q->status = GorPass::TOPSORT;
                DINCCOUNT_CLSCANS(ctx);
                if (!scan(ctx, q, false)) {
                    q->status = GorPass::LINEAR;
                    topsort.pop_back();
                    linear.push_back(q);
                }
            }
        }

        // 2nd pass: linear scan of topologically ordered states
        for (; !linear.empty(); ) {
            TnfaState* q = linear.back();
            linear.pop_back();
            if (q->active) {
                q->active = 0;
                q->arcidx = 0;
                DINCCOUNT_CLSCANS(ctx);
                scan(ctx, q, true);
            }
            q->status = GorPass::NOPASS;
        }
    }
}

template<typename ctx_t>
void init_gor1(ctx_t& ctx) {
    typename ctx_t::confset_t& state = ctx.state;
    typename ctx_t::confset_t& reach = ctx.reach;
    std::vector<TnfaState*>& topsort = ctx.gor1_topsort;

    // init: push configurations ordered by POSIX precedence (highest on top)
    state.clear();
    std::sort(reach.begin(), reach.end(), cmp_gor1_t<ctx_t>(ctx));
    typename ctx_t::rcconfiter_t c = reach.rbegin(), e = reach.rend();
    for (; c != e; ++c) {
        TnfaState* q = c->state;
        if (q->clos == NOCLOS) {
            q->clos = static_cast<uint32_t>(state.size());
            state.push_back(*c);
        } else {
            state[q->clos] = *c;
        }
        topsort.push_back(q);
    }
}

template<typename ctx_t>
bool scan(ctx_t& ctx, TnfaState* q, bool all) {
    bool any = false;

    using conf_t = typename ctx_t::conf_t;
    const conf_t x = ctx.state[q->clos];

    switch (q->kind) {
    case TnfaState::Kind::ALT:
        if (q->arcidx == 0) {
            any |= relax_gor1(ctx, conf_t(x, q->out1));
            ++q->arcidx;
        }
        if (q->arcidx == 1 && (!any || all)) {
            any |= relax_gor1(ctx, conf_t(x, q->out2));
            ++q->arcidx;
        }
        break;
    case TnfaState::Kind::TAG:
        if (q->arcidx == 0) {
            any |= relax_gor1(ctx, conf_t(x, q->out1, ctx.history.link(ctx, x)));
            ++q->arcidx;
        }
        break;
    case TnfaState::Kind::RAN:
    case TnfaState::Kind::FIN:
        break;
    }

    return any;
}

template<typename ctx_t>
bool relax_gor1(ctx_t& ctx, const typename ctx_t::conf_t& x) {
    typename ctx_t::confset_t& state = ctx.state;
    TnfaState* q = x.state;
    const uint32_t idx = q->clos;
    int32_t p1, p2;

    if (q->status == GorPass::TOPSORT) {
        return false;
    }

    if (idx == NOCLOS) {
        q->clos = static_cast<uint32_t>(state.size());
        state.push_back(x);
    } else if (q->indeg < 2 || ctx_t::history_t::precedence(ctx, x, state[idx], p1, p2) < 0) {
        state[idx] = x;
    } else {
        return false;
    }

    if (q->status == GorPass::NOPASS) {
        ctx.gor1_topsort.push_back(q);
        q->arcidx = 0;
        return true;
    } else {
        q->active = 1;
        return false;
    }
}

// note [GTOP SSSP algorithm]
//
// Global Topsort Single Source Shortest Path algorithm.
//
// It is well known that SSSP can be solved in linear time on DAGs (directed acyclic graphs) by
// exploring graph nodes in topological order. In our case TNFA is not a DAG (it may have cycles),
// but it is possible to compute fake topologcal order by ignoring back edges.
//
// The algorithm works by having a priority queue of nodes, where priorities are indices of nodes in
// fake topological ordering. At each step, the node with the minimal priority is popped from queue
// and explored. All nodes reachable from it on admissible arcs are enqueued, unless they are
// already in the queue.
//
// The resulting algorithm is of course not optimal: it can get stuck on graphs with loops, because
// it will give priority to some of the loop nodes compared to others for no good reason. However
// the algorithm is simple and optimal for DAGs, therefore we keep it.

template<typename ctx_t>
void closure_posix_gtop(ctx_t& ctx) {
    const typename ctx_t::confset_t& reach = ctx.reach;
    typename ctx_t::confset_t& state = ctx.state;
    gtop_heap_t& heap = ctx.gtop_heap;

    state.clear();
    for (const typename ctx_t::conf_t& conf : reach) {
        relax_gtop(ctx, conf);
    }

    for (; !heap.empty(); ) {
        TnfaState* q = heap.top();
        heap.pop();
        q->active = 0;
        DINCCOUNT_CLSCANS(ctx);

        using conf_t = typename ctx_t::conf_t;
        const conf_t x = ctx.state[q->clos];

        switch (q->kind) {
        case TnfaState::Kind::ALT:
            relax_gtop(ctx, conf_t(x, q->out1));
            relax_gtop(ctx, conf_t(x, q->out2));
            break;
        case TnfaState::Kind::TAG:
            relax_gtop(ctx, conf_t(x, q->out1, ctx.history.link(ctx, x)));
            break;
        case TnfaState::Kind::RAN:
        case TnfaState::Kind::FIN:
            break;
        }
    }
}

template<typename ctx_t>
void relax_gtop(ctx_t& ctx, const typename ctx_t::conf_t& c) {
    typename ctx_t::confset_t& state = ctx.state;
    TnfaState* q = c.state;
    const uint32_t idx = q->clos;
    int32_t p1, p2;

    if (idx == NOCLOS) {
        q->clos = static_cast<uint32_t>(state.size());
        state.push_back(c);
    } else if (q->indeg < 2 || ctx_t::history_t::precedence(ctx, c, state[idx], p1, p2) < 0) {
        state[idx] = c;
    } else {
        return;
    }

    if (!q->active) {
        q->active = 1;
        ctx.gtop_heap.push(q);
    }
}

template<>
inline void closure_cleanup<pdetctx_t>(TnfaState* q) {
    q->clos = NOCLOS;
    q->arcidx = 0;
    DCHECK(q->status == GorPass::NOPASS && q->active == 0);
}

} // namespace re2c

#endif // _RE2C_DFA_CLOSURE_POSIX_

