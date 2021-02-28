#include <stddef.h>
#include <valarray>
#include <vector>

#include "lib/regcomp_dfa_regless.h"
#include "lib/regex.h"
#include "lib/regex_impl.h"
#include "src/debug/debug.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"


namespace re2c {
namespace libre2c {

template<typename history_t>
inline void unwind_tag_history(const determ_context_t<history_t> &ctx, hidx_t hidx,
    regoff_t *result, regoff_t offset)
{
    for (int32_t i = hidx; i != HROOT; ) {
        const typename history_t::node_t &n = ctx.history.node(i);
        const size_t t = n.info.idx;
        i = n.pred;

        // If already updated, skip.
        if (result[t] != NORESULT) continue;

        if (!n.info.neg) {
            // Update positive tag.
            result[t] = offset;
        } else {
            // Update negative tag together with its sibling and nested tags.
            const Tag &tag = ctx.dfa.tags[t];
            for (size_t l = tag.lnest; l < tag.hnest; ++l) {
                result[l] = -1;
            }
        }
    }
}

template<typename ctx_t>
int regexec_dfa_regless(const regex_t *preg, const char *string, size_t nmatch,
    regmatch_t pmatch[], int /* eflags */)
{
    const rldfa_t *rldfa = preg->rldfa;
    const std::vector<rldfa_state_t*> &states = rldfa->states;
    std::vector<const rldfa_backlink_t* const*> &log = rldfa->log;

    const char *strptr = string, *finstrptr = strptr;
    rldfa_backlink_t finlink = {NOCONF, HROOT};

    // Match RLDFA on the input string, logging backlink arrays on the way.
    log.clear();
    for (size_t stidx = 0;;) {
        const int32_t chr = *strptr++;
        const size_t cls = preg->char2class[chr];

        const rldfa_state_t *state = states[stidx];
        const rldfa_arc_t &arc = state->arcs[cls];
        stidx = arc.state;

        log.push_back(&arc.backlinks);

        if (state->finlink.conf != NOCONF) {
            finlink = state->finlink;
            finstrptr = strptr;
        }

        if (stidx == dfa_t::NIL || chr == 0) break;
    }

    // No final state has been encountered on the way; return no-match.
    if (finlink.conf == NOCONF) return REG_NOMATCH;

    ctx_t &ctx = *static_cast<ctx_t*>(rldfa->ctx);
    const std::vector<Tag> &tags = ctx.dfa.tags;
    const size_t ntags = tags.size();

    // It is necessary to initialize tag offsets to prevent overwriting the
    // latest tag value when unwinding tag history.
    regoff_t *result = rldfa->result;
    std::fill(result, result + ntags, NORESULT);

    const regoff_t finoffset = finstrptr - string - 1;

    // Unwind tag history back from the final RLDFA state to the initial state.
    rldfa_backlink_t link = finlink;
    for (regoff_t offset = finoffset;;) {
        unwind_tag_history(ctx, link.hidx, result, offset);

        if (offset == 0) break;
        --offset;

        link = (*log[static_cast<size_t>(offset)])[link.conf];
    }

    // Copy tag offsets to submatch results in the pmatch[] array.
    regmatch_t *match = pmatch, *lastmatch = pmatch + nmatch;
    match->rm_so = 0;
    match->rm_eo = finoffset;
    ++match;

    for (size_t t = 0; t < ntags && match < lastmatch; t += 2) {
        const Tag &tag = tags[t];
        if (fictive(tag)) continue;

        const regoff_t so = result[t], eo = result[t + 1];

        // Submatch groups corresponding to this tag pair: there may be more
        // than one capturing parenthesis per tag in regexp like (...(e)...).
        for (size_t s = tag.lsub; s <= tag.hsub && match < lastmatch; s += 2, ++match) {
            DASSERT(match - 1 == &pmatch[s / 2]);
            match->rm_so = so;
            match->rm_eo = eo;
        }
    }

    return 0;
}

// explicit instantiation for disambiguation policy (leftmost greedy / POSIX)
template int regexec_dfa_regless<ldetctx_t>(const regex_t*, const char*, size_t,
    regmatch_t[], int);
template int regexec_dfa_regless<pdetctx_t>(const regex_t*, const char*, size_t,
    regmatch_t[], int);

} // namespace libre2c
} // namespace re2c

