#include <stdint.h>
#include <algorithm>
#include <map>
#include <set>
#include <utility>
#include <vector>

#include "src/dfa/determinization.h"
#include "src/dfa/dfa.h"
#include "src/dfa/closure_leftmost.h"
#include "src/dfa/closure_posix.h"
#include "src/dfa/posix_precedence.h"
#include "src/dfa/tag_history.h"
#include "src/dfa/tagver_table.h"
#include "src/dfa/tcmd.h"
#include "src/msg/location.h"
#include "src/msg/warn.h"
#include "src/nfa/nfa.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"

namespace re2c {

// note [epsilon-closures in tagged NFA]
//
// The closure includes all TNFA states that are reachable by epsilon-paths from the given set of
// states and are final or have outgoing transitions on symbols. Note that by construction TNFA
// states cannot have both epsilon transitions and transitions on symbols.
//
// Each closure state might be reachable by multiple epsilon-paths with different tags: this means
// that the regular expression is ambiguous and can be parsed in different ways. Which way to choose
// depends on the disambiguation policy. RE2C supports two policies: leftmost greedy and POSIX.
//
// We use Goldber-Radzik algorithm to find the shortest path in the epsilon-closure. Both
// disambiguation policies forbid epsilon-cycles with negative weight.

// note [at most one final item per closure]
//
// By construction TNFA has exactly one final state per rule. Thus closure has at most one final
// item per rule (in other words, all final items in closure belong to different rules). The rule
// with the highest priority shadowes all other rules. Final items that correspond to shadowed rules
// are useless and should be removed as early as possible.
//
// If we let such items remain in closure, they may prevent the new TDFA state from being merged
// with other states. This won't affect the final program: meaningless finalizing tags will be
// removed by dead code elimination and subsequent minimization will merge equivalent final states.
// However, it's better not to add useless final items at all.
//
// Note that the first final item reached by the epsilon-closure it the one with the highest
// priority (see note [closure items are sorted by rule]).

template<typename ctx_t> static void generate_versions(ctx_t&);
template<typename ctx_t> void prune_and_copy_to_kbufs(ctx_t& ctx);
static bool cmpby_rule_state(const clos_t&, const clos_t&);

// explicit instantiation for context types
template void tagged_epsilon_closure<pdetctx_t>(pdetctx_t& ctx);
template void tagged_epsilon_closure<ldetctx_t>(ldetctx_t& ctx);

// Build tagged epsilon-closure of the given set of NFA states.
template<typename ctx_t>
void tagged_epsilon_closure(ctx_t& ctx) {
    closure(ctx);
    generate_versions(ctx);
}

template<> void closure<pdetctx_t>(pdetctx_t& ctx) {
    closure_posix(ctx);
    std::sort(ctx.state.begin(), ctx.state.end(), cmpby_rule_state);
    prune_and_copy_to_kbufs(ctx);
    compute_prectable(ctx);
}

template<> void closure<ldetctx_t>(ldetctx_t& ctx) {
    closure_leftmost(ctx);
    prune_and_copy_to_kbufs(ctx);
}

bool cmpby_rule_state(const clos_t& x, const clos_t& y) {
    const TnfaState* sx = x.state, *sy = y.state;
    const size_t rx = sx->rule, ry = sy->rule;
    if (rx < ry) return true;
    if (rx > ry) return false;
    if (sx < sy) return true;
    if (sx > sy) return false;
    // all items in closute have different states
    return false;
}

template<typename ctx_t>
void reserve_kbufs(ctx_t& ctx) {
    kernel_buffers_t& k = ctx.kbufs;
    size_t n = ctx.state.size();
    if (k.maxsize < n) {
        n *= 2; // in advance
        IrAllocator& alc = ctx.ir_alc;
        k.maxsize = n;
        k.state = alc.alloct<TnfaState*>(n);
        k.origin = alc.alloct<uint32_t>(n);
        k.thist = alc.alloct<hidx_t>(n);
        k.tvers = alc.alloct<uint32_t>(n);
    }
}

// Filter out configurations with states that have transitions on symbols.
// If there are any configurations with final state, pick the one with the lowest rule.
// See note [at most one final item per closure].
template<typename ctx_t>
void prune_and_copy_to_kbufs(ctx_t& ctx) {

    closure_t& closure = ctx.state;
    const clos_t* f = nullptr;

    reserve_kbufs(ctx);
    kernel_buffers_t& k = ctx.kbufs;
    size_t i = 0;

    for (const clos_t& c : closure) {
        TnfaState* s = c.state;

        closure_cleanup<ctx_t>(s);

        if (s->kind == TnfaState::Kind::RAN) {
            k.state[i] = s;
            k.origin[i] = c.origin;
            k.thist[i] = c.thist;
            ++i;
        } else if (s->kind == TnfaState::Kind::FIN && f == nullptr) {
            k.state[i] = s;
            k.origin[i] = c.origin;
            k.thist[i] = c.thist;
            ++i;

            f = &c;

        }
    }
    k.size = i;

    // mark dropped rules as shadowed
    if (f != nullptr && ctx.msg.warn.is_set(Warn::UNREACHABLE_RULES)) {
        std::vector<Rule>& rules = ctx.rules;
        const uint32_t l = rules[f->state->rule].semact->loc.line;
        for (const clos_t& c : closure) {
            if (&c != f && c.state->kind == TnfaState::Kind::FIN) {
                rules[c.state->rule].shadow.insert(l);
            }
        }
    }
}

template<typename ctx_t>
void generate_versions(ctx_t& ctx) {
    Tdfa& dfa = ctx.dfa;
    const std::vector<Tag>& tags = ctx.tags;
    const size_t ntag = tags.size();
    tagver_t& maxver = dfa.maxtagver;
    tagver_table_t& tagvertbl = ctx.tagvertbl;
    typename ctx_t::history_t& thistory = ctx.history;
    typename ctx_t::newvers_t& newvers = ctx.newvers;
    kernel_buffers_t& kbufs = ctx.kbufs;

    if (ctx.origin == Tdfa::NIL) {
        ctx.actions = nullptr;
        std::fill(kbufs.tvers, kbufs.tvers + kbufs.size, ctx.init_tags);
        return;
    }

    // Origin kernel (TDFA state) from which the current closure has been reached.
    const kernel_t* kernel = ctx.kernels[ctx.origin];

    typename ctx_t::newvers_t newacts(
        newver_cmp_t<typename ctx_t::history_t>(thistory, ctx.hc_caches));
    tcmd_t* cmd = nullptr;

    // For each tag, if there is at least one tagged transition, allocate a new version: negative
    // in the case of transition with a negative tag, and positive otherwise. The absolute version
    // value should be unique among all versions of all tags.
    for (size_t k = 0; k < kbufs.size; ++k) {
        uint32_t orig = kbufs.origin[k];
        hidx_t orig_thist = kernel->thist[orig];

        if (orig_thist == HROOT) continue;

        hidx_t look_thist = kbufs.thist[k];
        const tagver_t* old_vers = tagvertbl[kernel->tvers[orig]];

        for (size_t t = 0; t < ntag; ++t) {
            if (last(thistory, orig_thist, t) == TAGVER_ZERO) continue;

            const Tag& tag = tags[t];
            tagver_t old_ver = history(tag) ? old_vers[t] : TAGVER_ZERO;
            newver_t key{t, old_ver, orig_thist};
            tagver_t next_free_ver = maxver + 1;
            tagver_t ver = newvers.insert(std::make_pair(key, next_free_ver)).first->second;
            if (ver == next_free_ver) ++maxver;

            if (!fixed(tag) && (history(tag) || last(thistory, look_thist, t) == TAGVER_ZERO)) {
                newacts.insert(std::make_pair(key, ver));
            }
        }
    }

    // actions
    for (const auto& i : newacts) {
        tagver_t ver = i.second;
        tagver_t old_ver = i.first.base;
        hidx_t thist = i.first.history;
        size_t t = i.first.tag;
        if (history(tags[t])) {
            cmd = dfa.tcpool.make_add(cmd, abs(ver), abs(old_ver), thistory, thist, t);
        } else {
            cmd = dfa.tcpool.make_set(cmd, abs(ver), last(thistory, thist, t));
        }
    }

    // mark tags with history
    for (const auto& j : newvers) {
        if (history(tags[j.first.tag])) {
            dfa.mtagvers.insert(abs(j.second));
        }
    }

    // update tag versions in closure
    for (size_t k = 0; k < kbufs.size; ++k) {
        uint32_t orig = kbufs.origin[k];
        uint32_t orig_tvers = kernel->tvers[orig];
        hidx_t orig_thist = kernel->thist[orig];

        if (orig_thist == HROOT) {
            // empty history for all tags => use origin versions
            kbufs.tvers[k] = orig_tvers;
        } else {
            const tagver_t* old_vers = tagvertbl[orig_tvers];
            tagver_t* vers = tagvertbl.buffer;
            for (size_t t = 0; t < ntag; ++t) {
                if (last(thistory, orig_thist, t) == TAGVER_ZERO) {
                    // empty history for tag `t` => use origin version
                    vers[t] = old_vers[t];
                } else {
                    // use new version for tag `t`
                    tagver_t old_ver = history(tags[t]) ? old_vers[t] : TAGVER_ZERO;
                    vers[t] = newvers[{t, old_ver, orig_thist}];
                }
            }
            kbufs.tvers[k] = tagvertbl.insert(vers);
        }
    }

    ctx.actions = cmd;
}

template<typename history_t>
bool newver_cmp_t<history_t>::operator()(const newver_t& x, const newver_t& y) const {
    if (x.tag < y.tag) return true;
    if (x.tag > y.tag) return false;

    if (x.base < y.base) return true;
    if (x.base > y.base) return false;

    hidx_t xh = x.history, yh = y.history;
    if (xh == yh) return false;

    hc_cache_t& cache = caches[x.tag];
    int32_t cmp;

    bool invert = xh > yh;
    if (invert) std::swap(xh, yh);

    uint64_t k = static_cast<uint32_t>(xh);
    k = (k << 32) | static_cast<uint32_t>(yh);

    hc_cache_t::const_iterator i = cache.find(k);
    if (i != cache.end()) {
        cmp = i->second;
    } else {
        cmp = compare_reversed(history, xh, yh, x.tag);
        cache.insert(std::make_pair(k, cmp));
    }

    if (invert) cmp = -cmp;
    return cmp < 0;
}

} // namespace re2c
