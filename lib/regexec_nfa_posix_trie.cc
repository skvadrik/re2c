#include "lib/lex.h"
#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/options/opt.h"
#include "src/debug/debug.h"
#include "src/dfa/closure_posix.h"
#include "src/dfa/determinization.h"
#include "src/dfa/posix_precedence.h"
#include "src/nfa/nfa.h"


namespace re2c {
namespace libre2c {

static void make_step(pzsimctx_t &, uint32_t);
static void make_final_step(pzsimctx_t &);

int regexec_nfa_posix_trie(const regex_t *preg, const char *string
    , size_t nmatch, regmatch_t pmatch[], int)
{
    pzsimctx_t &ctx = *static_cast<pzsimctx_t*>(preg->simctx);
    init(ctx, string);

    nfa_state_t *s0 = ctx.nfa.root;
    const conf_t c0(s0, s0->coreid, HROOT);
    ctx.reach.push_back(c0);
    closure_posix_gtop(ctx);
    for (;;) {
        const uint32_t sym = static_cast<uint8_t>(*ctx.cursor++);
        if (ctx.state.empty() || sym == 0) break;
        make_step(ctx, sym);
        closure_posix_gtop(ctx);
    }
    make_final_step(ctx);

    return finalize(ctx, string, nmatch, pmatch);
}

void make_step(pzsimctx_t &ctx, uint32_t sym)
{
    const confset_t &state = ctx.state;
    confset_t &reach = ctx.reach;
    cconfiter_t b = state.begin(), e = state.end(), i;

    reach.clear();
    for (i = b; i != e; ++i) {
        nfa_state_t *s = i->state;

        s->clos = NOCLOS;
        DASSERT(s->active == 0);

        if (s->type == nfa_state_t::RAN) {
            for (const Range *r = s->ran.ran; r; r = r->next()) {
                if (r->lower() <= sym && sym < r->upper()) {
                    const conf_t c(s->ran.out, s->coreid, i->thist);
                    reach.push_back(c);
                    break;
                }
            }
        }
        else if (s->type == nfa_state_t::FIN) {
            ctx.marker = ctx.cursor;
            ctx.hidx = i->thist;
            ctx.rule = 0;
        }
    }

    ++ctx.step;
}

void make_final_step(pzsimctx_t &ctx)
{
    for (confiter_t i = ctx.state.begin(), e = ctx.state.end(); i != e; ++i) {
        nfa_state_t *s = i->state;

        s->clos = NOCLOS;
        DASSERT(s->active == 0);

        if (s->type == nfa_state_t::FIN) {
            ctx.marker = ctx.cursor;
            ctx.hidx = i->thist;
            ctx.rule = 0;
        }
    }
}

} // namespace libre2c
} // namespace re2c

