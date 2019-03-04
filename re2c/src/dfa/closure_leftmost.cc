#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"


namespace re2c
{

void closure_leftmost(ldetctx_t &ctx)
{
    closure_t &done = ctx.state, &todo = ctx.reach;
    done.clear();

    // DFS; linear complexity
    for (; !todo.empty(); ) {
        const clos_t &x = todo.back();
        nfa_state_t *n = x.state;
        todo.pop_back();

        if (n->clos != NOCLOS) continue;

        n->clos = static_cast<uint32_t>(done.size());
        done.push_back(x);

        switch (n->type) {
            case nfa_state_t::NIL:
                todo.push_back(clos_t(x, n->nil.out));
                break;
            case nfa_state_t::ALT:
                todo.push_back(clos_t(x, n->alt.out2));
                todo.push_back(clos_t(x, n->alt.out1));
                break;
            case nfa_state_t::TAG:
                todo.push_back(clos_t(x, n->tag.out, ctx.history.link(ctx, x)));
                break;
            default:
                break;
        }
    }

    // reset associated closure items
    // (do this before removing any states from closure)
    for (clositer_t i = done.begin(); i != done.end(); ++i) {
        i->state->clos = NOCLOS;
    }
}

} // namespace re2c
