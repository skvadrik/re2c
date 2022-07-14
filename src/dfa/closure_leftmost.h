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
        const conf_t x = stack.back();
        stack.pop_back();
        TnfaState* n = x.state;

        if (n->clos != NOCLOS) continue;

        n->clos = static_cast<uint32_t>(state.size());
        state.push_back(x);

        switch (n->kind) {
        case TnfaState::Kind::ALT:
            stack.push_back(conf_t(x, n->out2));
            stack.push_back(conf_t(x, n->out1));
            break;
        case TnfaState::Kind::TAG:
            stack.push_back(conf_t(x, n->out1, ctx.history.link(ctx, x)));
            break;
        case TnfaState::Kind::RAN:
        case TnfaState::Kind::FIN:
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
