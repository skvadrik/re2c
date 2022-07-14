#include <stddef.h>
#include <algorithm>
#include <utility>
#include <vector>

#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/dfa/closure_leftmost.h"
#include "src/dfa/tag_history.h"
#include "src/nfa/nfa.h"
#include "src/regexp/rule.h"
#include "src/util/check.h"
#include "src/util/range.h"

namespace re2c {
namespace libre2c {

static void reach_on_symbol(lsimctx_t&, uint32_t);

int regexec_nfa_leftmost(
        const regex_t* preg, const char* string, size_t nmatch, regmatch_t pmatch[], int) {
    lsimctx_t& ctx = *static_cast<lsimctx_t*>(preg->simctx);
    init(ctx, string);

    // root state can be non-core, so we pass zero as origin to avoid checks
    const conf_t c0(ctx.nfa.root, 0, HROOT);
    ctx.reach.push_back(c0);

    for (;;) {
        closure_leftmost_dfs(ctx);
        const uint32_t sym = static_cast<uint8_t>(*ctx.cursor++);
        if (ctx.state.empty() || sym == 0) break;
        reach_on_symbol(ctx, sym);
    }

    for (cconfiter_t i = ctx.state.begin(), e = ctx.state.end(); i != e; ++i) {
        TnfaState* s = i->state;
        s->clos = NOCLOS;
        if (s->kind == TnfaState::Kind::FIN) {
            update_offsets(ctx, *i, NONCORE);
        }
    }

    if (ctx.rule == Rule::NONE) {
        return REG_NOMATCH;
    }

    const getoff_nfa_t fn = { ctx.offsets3 };
    tags_to_submatch(ctx.nfa.tags, nmatch, pmatch, ctx.marker - string - 1, fn);

    return 0;
}

void reach_on_symbol(lsimctx_t& ctx, uint32_t sym) {
    const confset_t& state = ctx.state;
    confset_t& reach = ctx.reach;
    DCHECK(reach.empty());

    // in reverse, so that future closure DFS has states in stack order
    uint32_t j = 0;
    for (rcconfiter_t i = state.rbegin(), e = state.rend(); i != e; ++i) {
        TnfaState* s = i->state;
        s->clos = NOCLOS;

        if (s->kind == TnfaState::Kind::RAN) {
            for (const Range* r = s->ran; r; r = r->next()) {
                if (r->lower() <= sym && sym < r->upper()) {
                    conf_t c(s->out1, j, HROOT);
                    reach.push_back(c);
                    update_offsets(ctx, *i, j);
                    ++j;
                    break;
                }
            }
        } else if (s->kind == TnfaState::Kind::FIN) {
            update_offsets(ctx, *i, NONCORE);
        }
    }

    std::swap(ctx.offsets1, ctx.offsets2);
    ctx.history.init();
    ++ctx.step;
}

} // namespace libre2
} // namespace re2c
