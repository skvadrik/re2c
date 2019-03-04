#include "lib/lex.h"
#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/options/opt.h"
#include "src/debug/debug.h"
#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"


namespace re2c {
namespace libre2c {

static void reach_on_symbol(lzctx_t &, uint32_t);
static void closure_leftmost(lzctx_t &);

int regexec_nfa_leftmost_trie(const regex_t *preg, const char *string
    , size_t nmatch, regmatch_t pmatch[], int)
{
    lzctx_t &ctx = *static_cast<lzctx_t*>(preg->simctx);
    init(ctx, string);

    nfa_state_t *s0 = ctx.nfa.root;
    const conf_t c0(s0, s0->coreid, HROOT);
    ctx.reach.push_back(c0);
    closure_leftmost(ctx);

    for (;;) {
        const uint32_t sym = static_cast<uint8_t>(*ctx.cursor++);
        if (ctx.state.empty() || sym == 0) break;
        reach_on_symbol(ctx, sym);
        ++ctx.step;
        closure_leftmost(ctx);
    }

    const confset_t &state = ctx.state;
    cconfiter_t b = state.begin(), e = state.end(), i;
    for (i = b; i != e; ++i) {
        i->state->clos = NOCLOS;
    }

    return finalize(ctx, string, nmatch, pmatch);
}

void reach_on_symbol(lzctx_t &ctx, uint32_t sym)
{
    const confset_t &state = ctx.state;
    confset_t &reach = ctx.reach;

    // in reverse, so that future closure DFS has states in stack order
    rcconfiter_t b = state.rbegin(), e = state.rend(), i;
    DASSERT(reach.empty());

    for (i = b; i != e; ++i) {
        nfa_state_t *s = i->state;

        // cleanup from previous closure
        s->clos = NOCLOS;

        if (s->type == nfa_state_t::RAN) {
            for (const Range *r = s->ran.ran; r; r = r->next()) {
                if (r->lower() <= sym && sym < r->upper()) {
                    const conf_t c(s->ran.out, 0, i->thist);
                    reach.push_back(c);
                    break;
                }
            }
        }
    }
}

void closure_leftmost(lzctx_t &ctx)
{
    confset_t &state = ctx.state, &wl = ctx.reach;
    state.clear();
    for (; !wl.empty(); ) {

        const conf_t &x = wl.back();
        nfa_state_t *n = x.state;
        const uint32_t o = x.origin;
        const int32_t h = x.thist;
        wl.pop_back();

        if (n->clos != NOCLOS) continue;

        n->clos = 0;
        state.push_back(x);

        switch (n->type) {
            case nfa_state_t::NIL:
                wl.push_back(conf_t(n->nil.out, o, h));
                break;
            case nfa_state_t::ALT:
                wl.push_back(conf_t(n->alt.out2, o, h));
                wl.push_back(conf_t(n->alt.out1, o, h));
                break;
            case nfa_state_t::TAG:
                wl.push_back(conf_t(n->tag.out, o
                    , ctx.history.push(h, ctx.step, n->tag.info, o)));
                break;
            case nfa_state_t::RAN:
                break;
            case nfa_state_t::FIN:
                ctx.marker = ctx.cursor + 1;
                ctx.hidx = x.thist;
                ctx.rule = 0;
                break;
        }
    }
}

} // namespace libre2
} // namespace re2c

