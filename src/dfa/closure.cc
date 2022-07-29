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
template<typename ctx_t> void prune(ctx_t& ctx);
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
    prune(ctx);
    std::sort(ctx.state.begin(), ctx.state.end(), cmpby_rule_state);
    compute_prectable(ctx);
}

template<> void closure<ldetctx_t>(ldetctx_t& ctx) {
    closure_leftmost(ctx);
    prune(ctx);
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
void prune(ctx_t& ctx) {
    // Filter out configurations which states have transitions on symbols. If we have any
    // configurations with final state, pick the one with the lowest rule. See note [at most one
    // final item per closure].

    closure_t& closure = ctx.state, &buffer = ctx.reach;
    const clos_t* f = nullptr;
    buffer.clear();

    for (const clos_t& c : closure) {
        TnfaState* s = c.state;

        closure_cleanup<ctx_t>(s);

        if (s->kind == TnfaState::Kind::RAN) {
            buffer.push_back(c);
        } else if (s->kind == TnfaState::Kind::FIN
                && (f == nullptr || s->rule < f->state->rule)) {
            f = &c;
        }
    }

    if (f != nullptr) {
        buffer.push_back(*f);

        // mark dropped rules as shadowed
        if (ctx.msg.warn.is_set(Warn::UNREACHABLE_RULES)) {
            std::vector<Rule>& rules = ctx.rules;
            const uint32_t l = rules[f->state->rule].semact->loc.line;
            for (const clos_t& c : closure) {
                if (&c != f && c.state->kind == TnfaState::Kind::FIN) {
                    rules[c.state->rule].shadow.insert(l);
                }
            }
        }
    }

    closure.swap(buffer);
}

template<typename ctx_t>
void generate_versions(ctx_t& ctx) {
    Tdfa& dfa = ctx.dfa;
    const std::vector<Tag>& tags = ctx.tags;
    const size_t ntag = tags.size();
    tagver_t& maxver = dfa.maxtagver;
    tagver_table_t& tvtbl = ctx.tagvertbl;
    tagver_t* vers = tvtbl.buffer;
    closure_t& clos = ctx.state;
    typename ctx_t::history_t& thist = ctx.history;
    typename ctx_t::newvers_t& newvers = ctx.newvers;

    typename ctx_t::newvers_t newacts(
        newver_cmp_t<typename ctx_t::history_t>(thist, ctx.hc_caches));
    tcmd_t* cmd = nullptr;

    // For each tag, if there is at least one tagged transition, allocate a new version: negative
    // in the case of transition with a negative tag, and positive otherwise. The absolute version
    // value should be unique among all versions of all tags.
    for (clos_t& c : clos) {
        const hidx_t l = c.thist, h = c.ttran;
        if (h == HROOT) continue;

        const tagver_t* vs = tvtbl[c.tvers];
        for (size_t t = 0; t < ntag; ++t) {
            const Tag& tag = tags[t];

            const tagver_t h0 = last(thist, h, t);
            if (h0 == TAGVER_ZERO) continue;

            const tagver_t v = history(tag) ? vs[t] : TAGVER_ZERO;
            newver_t x = {t, v, h};
            const tagver_t n = maxver + 1;
            const tagver_t m = newvers.insert(std::make_pair(x, n)).first->second;
            if (n == m) ++maxver;

            if (!fixed(tag) && (history(tag) || last(thist, l, t) == TAGVER_ZERO)) {
                newacts.insert(std::make_pair(x, m));
            }
        }
    }

    // actions
    for (const auto& i : newacts) {
        const tagver_t m = i.second, v = i.first.base;
        const hidx_t h = i.first.history;
        const size_t t = i.first.tag;
        if (history(tags[t])) {
            cmd = dfa.tcpool.make_add(cmd, abs(m), abs(v), thist, h, t);
        } else {
            cmd = dfa.tcpool.make_set(cmd, abs(m), last(thist, h, t));
        }
    }

    // mark tags with history
    for (const auto& j : newvers) {
        if (history(tags[j.first.tag])) {
            dfa.mtagvers.insert(abs(j.second));
        }
    }

    // update tag versions in closure
    for (clos_t& c : clos) {
        const hidx_t h = c.ttran;
        if (h == HROOT) continue;

        const tagver_t* vs = tvtbl[c.tvers];
        for (size_t t = 0; t < ntag; ++t) {
            const tagver_t v0 = vs[t];
            const tagver_t h0 = last(thist, h, t);
            const tagver_t v = history(tags[t]) ? v0 : TAGVER_ZERO;
            if (h0 == TAGVER_ZERO) {
                vers[t] = v0;
            } else {
                newver_t x = {t, v, h};
                vers[t] = newvers[x];
            }
        }
        c.tvers = tvtbl.insert(vers);
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
