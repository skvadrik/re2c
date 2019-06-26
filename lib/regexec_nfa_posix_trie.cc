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

// specialization that doesn't sort initial closure like Okui-Suzuki
// (there is no cheap way to sort it in the lazy-disambiguation algorithm)
template<> void init_gor1<libre2c::pzsimctx_t>(libre2c::pzsimctx_t &ctx);

namespace libre2c {

static inline void closure_posix(pzsimctx_t &ctx);
static void make_step(pzsimctx_t &, uint32_t);
static void make_final_step(pzsimctx_t &);

int regexec_nfa_posix_trie(const regex_t *preg, const char *string
    , size_t nmatch, regmatch_t pmatch[], int)
{
    pzsimctx_t &ctx = *static_cast<pzsimctx_t*>(preg->simctx);
    init(ctx, string);

    const conf_t c0(ctx.nfa.root, 0, HROOT);
    ctx.reach.push_back(c0);
    for (;;) {
        closure_posix(ctx);
        const uint32_t sym = static_cast<uint8_t>(*ctx.cursor++);
        if (ctx.state.empty() || sym == 0) break;
        make_step(ctx, sym);
    }
    make_final_step(ctx);

    return finalize(ctx, string, nmatch, pmatch);
    ctx.history.cache.clear();
}

void closure_posix(pzsimctx_t &ctx)
{
    if (ctx.flags & REG_GTOP) {
        closure_posix_gtop(ctx);
    }
    else {
        closure_posix_gor1(ctx);
    }
}

void make_step(pzsimctx_t &ctx, uint32_t sym)
{
    const confset_t &state = ctx.state;
    confset_t &reach = ctx.reach;
    cconfiter_t b = state.begin(), e = state.end(), i;

    reach.clear();
    uint32_t j = 0;
    for (i = b; i != e; ++i) {
        nfa_state_t *s = i->state;

        s->clos = NOCLOS;
        s->arcidx = 0;
        DASSERT(s->status == GOR_NOPASS && s->active == 0);

        if (s->type == nfa_state_t::RAN) {
            for (const Range *r = s->ran.ran; r; r = r->next()) {
                if (r->lower() <= sym && sym < r->upper()) {
                    const conf_t c(s->ran.out, j++, i->thist);
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
        s->arcidx = 0;
        DASSERT(s->status == GOR_NOPASS && s->active == 0);

        if (s->type == nfa_state_t::FIN) {
            ctx.marker = ctx.cursor;
            ctx.hidx = i->thist;
            ctx.rule = 0;
        }
    }
}

} // namespace libre2c

template<> void init_gor1<libre2c::pzsimctx_t>(libre2c::pzsimctx_t &ctx)
{
    ctx.state.clear();
    libre2c::pzsimctx_t::cconfiter_t c = ctx.reach.begin(), e = ctx.reach.end();
    for (; c != e; ++c) {
        relax_gor1(ctx, *c);
    }
}

} // namespace re2c

