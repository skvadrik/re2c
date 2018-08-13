#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"


namespace re2c
{

static nfa_state_t *explore(determ_context_t &, nfa_state_t *);
static nfa_state_t *relax(determ_context_t &, clos_t);
static int32_t pack(int32_t, int32_t);


void closure_posix(determ_context_t &ctx)
{
    const closure_t &init = ctx.dc_reached;
    closure_t &done = ctx.dc_closure;
    std::stack<nfa_state_t*>
        &topsort = ctx.dc_stack_topsort,
        &linear = ctx.dc_stack_linear;
    nfa_state_t *q, *p;

    done.clear();

    // enqueue all initial states (there might be duplicates)
    for (cclositer_t c = init.begin(); c != init.end(); ++c) {
        q = relax(ctx, *c);
        if (q) {
            topsort.push(q);
            q->status = GOR_TOPSORT;
        }
    }

    // Gordberg-Radzik 'shortest path' algorithm.
    // Papers: 1993, "A heuristic improvement of the Bellman-Ford
    // algorithm" by Goldberg, Radzik and 1996, Shortest paths algorithms:
    // Theory and experimental evaluation" by Cherkassky, Goldberg, Radzik.
    // Complexity for digraph G=(V,E) is O(|V|*|E|).
    for (; !topsort.empty(); ) {

        // 1st pass: scan admissible subgraph reachable from B-stack
        // and topologically sort it (this can be done by a single
        // depth-first postorder traversal)
        for (; !topsort.empty(); ) {
            q = topsort.top();
            topsort.pop();

            if (q->status != GOR_LINEAR) {
                q->status = GOR_TOPSORT;

                // find next admissible transition
                while ((p = explore(ctx, q))
                    && p->status != GOR_NOPASS) {
                    p->active = 1;
                }

                // follow the admissible transition
                if (p) {
                    topsort.push(q);
                    topsort.push(p);
                    p->arcidx = 0;
                }
                // done with this state: all deps visited
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
                // scan admissible transitions
                q->arcidx = 0;
                while ((p = explore(ctx, q))) {
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

    // clean up (do this before removing any states from closure)
    for (clositer_t i = done.begin(); i != done.end(); ++i) {
        q = i->state;
        q->clos = NOCLOS;
        q->arcidx = 0;
        assert(q->status == GOR_NOPASS && q->active == 0);
    }
}


nfa_state_t *explore(determ_context_t &ctx, nfa_state_t *q)
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


int32_t pack(int32_t longest, int32_t leftmost)
{
    // leftmost: higher 2 bits, longest: lower 30 bits
    return longest | (leftmost << 30);
}

} // namespace re2c
