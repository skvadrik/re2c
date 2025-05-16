#ifndef _RE2C_DFA_CLOSURE_LEFTMOST_
#define _RE2C_DFA_CLOSURE_LEFTMOST_

#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"

namespace re2c {

template<typename ctx_t> void closure_cleanup(TnfaState* q);
template<typename ctx_t> static void closure_leftmost_dfs(ctx_t& ctx);

inline void closure_leftmost(ldetctx_t& ctx) {
    closure_leftmost_dfs(ctx);
}

template<typename ctx_t>
void closure_leftmost_dfs(ctx_t& ctx) {
    typename ctx_t::confset_t& state = ctx.state, &stack = ctx.reach;
    state.clear();

    // DFS; linear complexity
    for (; !stack.empty(); ) {
        using conf_t = typename ctx_t::conf_t;
        conf_t& x = stack.back();
        TnfaState* n = x.state;

        if (n->clos != NOCLOS) {
            stack.pop_back();
            continue;
        }

        n->clos = static_cast<uint32_t>(state.size());
        state.push_back(x);

        switch (n->kind) {
        case TnfaState::Kind::ALT:
            x.state = n->out2; // use inplace stack slot for the right alternative
            stack.push_back(conf_t(n->out1, x.origin, x.thist));
            break;
        case TnfaState::Kind::TAG:
            x.thist = ctx.history.link(ctx, x);
            x.state = n->out1;
            break;
        case TnfaState::Kind::RAN:
        case TnfaState::Kind::FIN:
            stack.pop_back();
            break;
        }
    }
}

template<>
inline void closure_cleanup<ldetctx_t>(TnfaState* q) {
    q->clos = NOCLOS;
}

} // namespace re2c

#endif // _RE2C_DFA_CLOSURE_LEFTMOST_
