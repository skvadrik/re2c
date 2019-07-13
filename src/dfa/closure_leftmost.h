#ifndef _RE2C_DFA_CLOSURE_LEFTMOST_
#define _RE2C_DFA_CLOSURE_LEFTMOST_

#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"


namespace re2c {

template<typename ctx_t> void closure_cleanup(nfa_state_t *q);
template<typename ctx_t> static void closure_leftmost_dfs(ctx_t &ctx);

inline void closure_leftmost(ldetctx_t &ctx)
{
    closure_leftmost_dfs(ctx);
}

template<typename ctx_t>
void closure_leftmost_dfs(ctx_t &ctx)
{
    typename ctx_t::confset_t &state = ctx.state, &stack = ctx.reach;
    state.clear();

    // DFS; linear complexity
    for (; !stack.empty(); ) {
        typedef typename ctx_t::conf_t conf_t;
        const conf_t x = stack.back();
        stack.pop_back();
        nfa_state_t *n = x.state;

        if (n->clos != NOCLOS) continue;

        n->clos = static_cast<uint32_t>(state.size());
        state.push_back(x);

        switch (n->type) {
            case nfa_state_t::NIL:
                stack.push_back(conf_t(x, n->nil.out));
                break;
            case nfa_state_t::ALT:
                stack.push_back(conf_t(x, n->alt.out2));
                stack.push_back(conf_t(x, n->alt.out1));
                break;
            case nfa_state_t::TAG:
                stack.push_back(conf_t(x, n->tag.out, ctx.history.link(ctx, x)));
                break;
            case nfa_state_t::RAN:
            case nfa_state_t::FIN:
                break;
        }
    }
}

template<>
inline void closure_cleanup<ldetctx_t>(nfa_state_t *q)
{
    q->clos = NOCLOS;
}

} // namespace re2c

#endif // _RE2C_DFA_CLOSURE_LEFTMOST_
