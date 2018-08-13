#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"


namespace re2c
{

void closure_leftmost(determ_context_t &ctx)
{
    const closure_t &init = ctx.dc_reached;
    closure_t &done = ctx.dc_closure;
    std::stack<clos_t> &todo = ctx.dc_stack_dfs;

    // enqueue all initial states
    done.clear();
    for (rcclositer_t c = init.rbegin(); c != init.rend(); ++c) {
        todo.push(*c);
    }

    // DFS; linear complexity
    for (; !todo.empty(); ) {
        clos_t x = todo.top();
        todo.pop();
        nfa_state_t *n = x.state;

        if (n->clos == NOCLOS) {
            n->clos = static_cast<uint32_t>(done.size());
            done.push_back(x);

            switch (n->type) {
                case nfa_state_t::NIL:
                    x.state = n->nil.out;
                    todo.push(x);
                    break;
                case nfa_state_t::ALT:
                    x.state = n->alt.out2;
                    todo.push(x);
                    x.state = n->alt.out1;
                    todo.push(x);
                    break;
                case nfa_state_t::TAG:
                    x.state = n->tag.out;
                    x.tlook = ctx.dc_taghistory.push(x.tlook, n->tag.info);
                    todo.push(x);
                    break;
                case nfa_state_t::RAN:
                case nfa_state_t::FIN:
                    break;
            }
        }
    }

    // reset associated closure items
    // (do this before removing any states from closure)
    for (clositer_t i = done.begin(); i != done.end(); ++i) {
        i->state->clos = NOCLOS;
    }
}

} // namespace re2c
