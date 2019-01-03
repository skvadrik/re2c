#include <queue>

#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"


namespace re2c
{

struct cmp_gor1_t
{
    determ_context_t &ctx;

    cmp_gor1_t(determ_context_t &);
    bool operator()(const clos_t &, const clos_t &) const;
};

struct cmp_gtop_t
{
    bool operator() (const nfa_state_t *, const nfa_state_t *) const;
};

static void closure_posix_gor1(determ_context_t &);
static void closure_posix_gtop(determ_context_t &);
static nfa_state_t *next_admissible_arc(determ_context_t &, nfa_state_t *);
static nfa_state_t *relax(determ_context_t &, clos_t);
static void cleanup(closure_t &);


void closure_posix(determ_context_t &ctx)
{
    DRESET_CLSTATS(ctx);

    switch (ctx.dc_opts->posix_closure) {
        case POSIX_CLOSURE_GOR1: closure_posix_gor1(ctx); break;
        case POSIX_CLOSURE_GTOP: closure_posix_gtop(ctx); break;
        default: DASSERT(false); break;
    }

    DDUMP_CLSTATS(ctx);
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
    closure_t &init = ctx.dc_reached;
    closure_t &done = ctx.dc_closure;
    std::stack<nfa_state_t*>
        &topsort = ctx.dc_stack_topsort,
        &linear = ctx.dc_stack_linear;
    nfa_state_t *q, *p;

    done.clear();

    // initialization: topsort stack must contain configurations
    // ordered by POSIX precedence (with highest precedence on top)
    std::sort(init.begin(), init.end(), cmp_gor1_t(ctx));
    for (rcclositer_t c = init.rbegin(); c != init.rend(); ++c) {
        q = c->state;
        if (q->clos == NOCLOS) {
            q->clos = static_cast<uint32_t>(done.size());
            done.push_back(*c);
        }
        else {
            // duplicate state, but higher precedence => overwrite
            done[q->clos] = *c;
        }
        topsort.push(q);
    }

    for (; !topsort.empty(); ) {

        // 1st pass: scan admissible subgraph reachable from B-stack
        // and topologically sort it (this can be done by a single
        // depth-first postorder traversal)
        for (; !topsort.empty(); ) {
            q = topsort.top();
            topsort.pop();

            if (q->status != GOR_LINEAR) {
                DINCCOUNT_CLSCANS(ctx);

                q->status = GOR_TOPSORT;
                while ((p = next_admissible_arc(ctx, q))
                    && p->status != GOR_NOPASS) {
                    p->active = 1;
                }

                if (p) {
                    topsort.push(q);
                    topsort.push(p);
                    p->arcidx = 0;
                }
                else {
                    q->status = GOR_LINEAR;
                    linear.push(q);
                }
            }
        }

        // 2nd pass: scan topologically ordered states from A-stack
        // and push head states of relaxed transitions to B-stack
        for (; !linear.empty(); ) {
            q = linear.top();
            linear.pop();

            if (q->active) {
                DINCCOUNT_CLSCANS(ctx);

                q->arcidx = 0;
                while ((p = next_admissible_arc(ctx, q))) {
                    if (p->status == GOR_NOPASS) {
                        topsort.push(p);
                        p->arcidx = 0;
                    }
                    else if (p->status == GOR_LINEAR) {
                        p->active = 1;
                    }
                }
            }

            q->status = GOR_NOPASS;
            q->active = 0;
        }
    }

    cleanup(done);
}

inline cmp_gor1_t::cmp_gor1_t(determ_context_t &c) : ctx(c) {}

inline bool cmp_gor1_t::operator()(const clos_t &x, const clos_t &y) const
{
    const kernel_t *k = ctx.dc_kernels[ctx.dc_origin];
    const uint32_t xo = x.origin, yo = y.origin;

    DASSERT(xo != yo && x.tlook == HROOT && y.tlook == HROOT);

    // if longest components differ, leftmost already incorporates that
    return unpack_leftmost(k->prectbl[xo * k->size + yo]) < 0;
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
    const closure_t &init = ctx.dc_reached;
    closure_t &done = ctx.dc_closure;

    std::priority_queue<nfa_state_t*, std::vector<nfa_state_t*>
        , cmp_gtop_t> todo;

    done.clear();

    for (cclositer_t c = init.begin(); c != init.end(); ++c) {
        nfa_state_t *q = relax(ctx, *c);
        if (q && q->active == 0) {
            todo.push(q);
            q->active = 1;
        }
    }

    for (; !todo.empty(); ) {
        DINCCOUNT_CLSCANS(ctx);

        nfa_state_t *q = todo.top();
        todo.pop();
        q->active = 0;
        q->arcidx = 0;

        while (true) {
            nfa_state_t *p = next_admissible_arc(ctx, q);
            if (!p) break;
            if (!p->active) {
                todo.push(p);
                p->active = 1;
            }
        }
    }

    cleanup(done);
}

inline bool cmp_gtop_t::operator() (const nfa_state_t *x, const nfa_state_t *y) const
{
    return x->topord < y->topord;
}

nfa_state_t *next_admissible_arc(determ_context_t &ctx, nfa_state_t *q)
{
    // find the next admissible transition, adjust the index
    // of the next transition and return the to-state
    nfa_state_t *p = NULL;
    clos_t x = ctx.dc_closure[q->clos];
    switch (q->type) {
        case nfa_state_t::NIL:
            if (q->arcidx == 0) {
                x.state = q->nil.out;
                p = relax(ctx, x);
                ++q->arcidx;
            }
            break;
        case nfa_state_t::ALT:
            if (q->arcidx == 0) {
                x.state = q->alt.out1;
                p = relax(ctx, x);
                ++q->arcidx;
            }
            if (q->arcidx == 1 && !p) {
                x.state = q->alt.out2;
                p = relax(ctx, x);
                ++q->arcidx;
            }
            break;
        case nfa_state_t::TAG:
            if (q->arcidx == 0) {
                x.state = q->tag.out;
                x.tlook = ctx.dc_taghistory.push(x.tlook, q->tag.info);
                p = relax(ctx, x);
                ++q->arcidx;
            }
            break;
        case nfa_state_t::RAN:
        case nfa_state_t::FIN:
            break;
    }
    return p;
}

nfa_state_t *relax(determ_context_t &ctx, clos_t x)
{
    closure_t &done = ctx.dc_closure;
    nfa_state_t *q = x.state;
    const uint32_t idx = q->clos;
    int32_t h1, h2;

    // first time we see this state
    if (idx == NOCLOS) {
        q->clos = static_cast<uint32_t>(done.size());
        done.push_back(x);
    }

    // States of in-degree less than 2 are not joint points;
    // the fact that we are re-scanning this state means that we found
    // a better path to some previous state. Due to the right distributivity
    // of path comparison over path concatenation (X < Y => XZ < YZ) we
    // can just propagate the new path up to the next join point.
    else if (q->indeg < 2) {
        done[idx] = x;
    }

    // join point; compare the new path and the old path
    else if (precedence(ctx, x, done[idx], h1, h2) < 0) {
        done[idx] = x;
    }

    // the previous path was better, discard the new one
    else {
        q = NULL;
    }

    return q;
}

void cleanup(closure_t &closure)
{
    for (clositer_t i = closure.begin(); i != closure.end(); ++i) {
        nfa_state_t *q = i->state;
        q->clos = NOCLOS;
        q->arcidx = 0;
        DASSERT(q->status == GOR_NOPASS && q->active == 0);
    }
}

void orders(determ_context_t &ctx)
{
    closure_t &closure = ctx.dc_closure;
    const size_t nclos = closure.size();

    prectable_t *prectbl = ctx.dc_allocator.alloct<prectable_t>(nclos * nclos);

    for (size_t i = 0; i < nclos; ++i) {
        for (size_t j = i + 1; j < nclos; ++j) {
            int32_t rho1, rho2, l;
            l = precedence (ctx, closure[i], closure[j], rho1, rho2);
            prectbl[i * nclos + j] = pack(rho1, l);
            prectbl[j * nclos + i] = pack(rho2, -l);
        }
        prectbl[i * nclos + i] = 0;
    }

    ctx.dc_prectbl = prectbl;
}

} // namespace re2c
