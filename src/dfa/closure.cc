#include "src/util/c99_stdint.h"
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <set>
#include <utility>
#include <valarray>
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

/* note [epsilon-closures in tagged NFA]
 *
 * The closure includes all NFA states that are reachable by epsilon-paths
 * from the given set of states and either are final or have non-epsilon
 * transitions. Note that by construction NFA states cannot have both
 * epsilon and non-epsilon transitions.
 *
 * Each closure state might be reachable by multiple epsilon-paths with
 * different tags: this means that the regular expression is ambiguous
 * and can be parsed in different ways. Which parse to choose depends on the
 * disambiguation policy. RE2C supports two policies: leftmost greedy and
 * POSIX.
 *
 * We use Goldber-Radzik algorithm to find the "shortest path".
 * Both disambiguation policies forbid epsilon-cycles with negative weight.
 */

/* note [at most one final item per closure]
 *
 * By construction NFA has exactly one final state per rule. Thus closure
 * has at most one final item per rule (in other words, all final items
 * in closure belong to different rules). The rule with the highest priority
 * shadowes all other rules. Final items that correspond to shadowed rules
 * are useless and should be removed as early as possible.
 *
 * If we let such items remain in closure, they may prevent the new DFA
 * state from being merged with other states. This won't affect the final
 * program: meaningless finalizing tags will be removed by dead code
 * elimination and subsequent minimization will merge equivalent final
 * states. However, it's better not to add useless final items at all.
 *
 * Note that the first final item reached by the epsilon-closure it the one
 * with the highest priority (see note [closure items are sorted by rule]).
 */

/* note [the difference between TDFA(0) and TDFA(1)]
 *
 * TDFA(0) performs epsilon-closure after transition on symbol,
 * while TDFA(1) performs it before the transition and uses the lookahead
 * symbol to filter the closure.
 *
 * TDFA(0) is one step ahead of TDFA(1): it consumes a symol, then builds
 * epsilon-closure, eagerly applies all tags reachable by it and goes to
 * the next state.
 *
 * TDFA(1) is more lazy: it builds epsilon-closure, then filters it with
 * respect to the current symbol (uses only those states which have outgoing
 * transitions on this symbol), then applies corresponding tags (probably
 * not all tags applied by TDFA(0)) and then consumes the symbol and goes
 * to the next state.
 *
 * Thus in general TDFA(1) raises less conflicts than TDFA(0).
 */

template<typename ctx_t> static inline void closure(ctx_t &ctx);
template<typename ctx_t> static void generate_versions(ctx_t &);
template<typename ctx_t> static void generate_stadfa_actions(ctx_t &);
template<typename ctx_t> void prune(ctx_t &ctx);
static void lower_lookahead_to_transition(closure_t &);
static bool cmpby_rule_state(const clos_t &, const clos_t &);

// explicit specialization for context types
template void tagged_epsilon_closure<pdetctx_t>(pdetctx_t &ctx);
template void tagged_epsilon_closure<ldetctx_t>(ldetctx_t &ctx);

template<typename ctx_t>
void tagged_epsilon_closure(ctx_t &ctx)
{
    // build tagged epsilon-closure of the given set of NFA states
    closure(ctx);

    // see note [the difference between TDFA(0) and TDFA(1)]
    if (!ctx.dc_opts->lookahead) {
        lower_lookahead_to_transition(ctx.state);
    }

    if (!ctx.dc_opts->stadfa) {
        generate_versions(ctx);
    }
    else {
        generate_stadfa_actions(ctx);
    }
}

template<>
inline void closure<pdetctx_t>(pdetctx_t &ctx)
{
    closure_posix(ctx);
    prune(ctx);
    std::sort(ctx.state.begin(), ctx.state.end(), cmpby_rule_state);
    compute_prectable(ctx);
}

template<>
inline void closure<ldetctx_t>(ldetctx_t &ctx)
{
    closure_leftmost(ctx);
    prune(ctx);
}

bool cmpby_rule_state(const clos_t &x, const clos_t &y)
{
    const nfa_state_t *sx = x.state, *sy = y.state;
    const size_t rx = sx->rule, ry = sy->rule;
    if (rx < ry) return true;
    if (rx > ry) return false;
    if (sx < sy) return true;
    if (sx > sy) return false;
    // all items in closute have different states
    return false;
}

template<typename ctx_t>
void prune(ctx_t &ctx)
{
    // Filter out configurations which states have transitions on symbols.
    // If we have any configurations with final state, pick the one with
    // the lowest rule. See note [at most one final item per closure].

    closure_t &closure = ctx.state, &buffer = ctx.reach;
    clositer_t b = closure.begin(), e = closure.end(), i, f = e;
    buffer.clear();

    for (i = b; i != e; ++i) {
        nfa_state_t *s = i->state;

        closure_cleanup<ctx_t>(s);

        if (s->type == nfa_state_t::RAN) {
            buffer.push_back(*i);
        }
        else if (s->type == nfa_state_t::FIN
            && (f == e || s->rule < f->state->rule)) {
            f = i;
        }
    }

    if (f != e) {
        buffer.push_back(*f);

        // mark dropped rules as shadowed
        if (ctx.dc_msg.warn.is_set(Warn::UNREACHABLE_RULES)) {
            std::valarray<Rule> &rules = ctx.nfa.rules;
            const uint32_t l = rules[f->state->rule].code->loc.line;
            for (i = b; i != e; ++i) {
                if (i != f && i->state->type == nfa_state_t::FIN) {
                    rules[i->state->rule].shadow.insert(l);
                }
            }
        }
    }

    closure.swap(buffer);
}

void lower_lookahead_to_transition(closure_t &closure)
{
    for (clositer_t c = closure.begin(); c != closure.end(); ++c) {
        c->ttran = c->thist;
        c->thist = HROOT;
    }
}

template<typename ctx_t>
void generate_versions(ctx_t &ctx)
{
    dfa_t &dfa = ctx.dfa;
    const std::vector<Tag> &tags = dfa.tags;
    const size_t ntag = tags.size();
    tagver_t &maxver = dfa.maxtagver;
    tagver_table_t &tvtbl = ctx.dc_tagvertbl;
    tagver_t *vers = tvtbl.buffer;
    closure_t &clos = ctx.state;
    typename ctx_t::history_t &thist = ctx.history;
    typename ctx_t::newvers_t &newvers = ctx.dc_newvers;

    clositer_t b = clos.begin(), e = clos.end(), c;
    typename ctx_t::newvers_t newacts(newver_cmp_t<typename ctx_t::history_t>(thist, ctx.dc_hc_caches));
    tcmd_t *cmd = NULL;

    // for each tag, if there is at least one tagged transition,
    // allocate new version (negative for bottom and positive for
    // normal transition, however absolute value should be unique
    // among all versions of all tags)
    for (c = b; c != e; ++c) {
        const hidx_t l = c->thist, h = c->ttran;
        if (h == HROOT) continue;

        const tagver_t *vs = tvtbl[c->tvers];
        for (size_t t = 0; t < ntag; ++t) {
            const Tag &tag = tags[t];

            const tagver_t h0 = last(thist, h, t);
            if (h0 == TAGVER_ZERO) continue;

            const tagver_t v = history(tag) ? vs[t] : TAGVER_ZERO;
            newver_t x = {t, v, h};
            const tagver_t
                n = (maxver + 1) * (h0 == TAGVER_BOTTOM ? -1 : 1),
                m = newvers.insert(std::make_pair(x, n)).first->second;
            if (n == m) ++maxver;

            if (!fixed(tag) && (history(tag) || last(thist, l, t) == TAGVER_ZERO)) {
                newacts.insert(std::make_pair(x, m));
            }
        }
    }

    // actions
    for (typename ctx_t::newvers_t::iterator i = newacts.begin(); i != newacts.end(); ++i) {
        const tagver_t m = i->second, v = i->first.base;
        const hidx_t h = i->first.history;
        const size_t t = i->first.tag;
        if (history(tags[t])) {
            cmd = dfa.tcpool.make_add(cmd, abs(m), abs(v), thist, h, t);
        } else {
            cmd = dfa.tcpool.make_set(cmd, abs(m), last(thist, h, t));
        }
    }

    // mark tags with history
    for (typename ctx_t::newvers_t::iterator j = newvers.begin(); j != newvers.end(); ++j) {
        if (history(tags[j->first.tag])) {
            dfa.mtagvers.insert(abs(j->second));
        }
    }

    // update tag versions in closure
    for (c = b; c != e; ++c) {
        const hidx_t h = c->ttran;
        if (h == HROOT) continue;

        const tagver_t *vs = tvtbl[c->tvers];
        for (size_t t = 0; t < ntag; ++t) {
            const tagver_t
                v0 = vs[t],
                h0 = last(thist, h, t),
                v = history(tags[t]) ? v0 : TAGVER_ZERO;
            if (h0 == TAGVER_ZERO) {
                vers[t] = v0;
            } else {
                newver_t x = {t, v, h};
                vers[t] = newvers[x];
            }
        }
        c->tvers = tvtbl.insert(vers);
    }

    ctx.dc_actions = cmd;
}

template<typename history_t>
bool newver_cmp_t<history_t>::operator()(const newver_t &x, const newver_t &y) const
{
    if (x.tag < y.tag) return true;
    if (x.tag > y.tag) return false;

    if (x.base < y.base) return true;
    if (x.base > y.base) return false;

    hidx_t xh = x.history, yh = y.history;
    if (xh == yh) return false;

    hc_cache_t &cache = caches[x.tag];
    int32_t cmp;

    bool invert = xh > yh;
    if (invert) std::swap(xh, yh);

    uint64_t k = static_cast<uint32_t>(xh);
    k = (k << 32) | static_cast<uint32_t>(yh);

    hc_cache_t::const_iterator i = cache.find(k);
    if (i != cache.end()) {
        cmp = i->second;
    }
    else {
        cmp = compare_reversed(history, xh, yh, x.tag);
        cache.insert(std::make_pair(k, cmp));
    }

    if (invert) cmp = -cmp;
    return cmp < 0;
}

template<typename ctx_t>
void generate_stadfa_actions(ctx_t &ctx)
{
    const size_t ntag = ctx.dfa.tags.size();
    allocator_t &alc = ctx.dc_allocator;
    clositer_t b = ctx.state.begin(), e = ctx.state.end(), c;

    stacmd_t *cmd = NULL;

    // store and transfer actions
    if (ctx.dc_origin == dfa_t::NIL) {
        for (c = b; c != e; ++c) {
            const int32_t i = static_cast<int32_t>(c->state - ctx.nfa.states);
            for (size_t t = 0; t < ntag; ++t) {
                if (!fixed(ctx.dfa.tags[t])) {
                    cmd = make_stacmd(alc, stacmd_t::TRANSFER, cmd, t, i, -1,
                        HROOT);
                }
            }
        }
    }
    else {
        const kernel_t *kernel = ctx.dc_kernels[ctx.dc_origin];

        for (c = b; c != e; ++c) {
            const int32_t i = static_cast<int32_t>(c->state - ctx.nfa.states);
            const int32_t j = static_cast<int32_t>(kernel->state[c->origin]
                - ctx.nfa.states);

            // delayed store actions for transition tags
            for (size_t t = 0; t < ntag; ++t) {
                if (!fixed(ctx.dfa.tags[t])
                        && last(ctx.history, c->ttran, t) != TAGVER_ZERO) {
                    cmd = make_stacmd(alc, stacmd_t::STORE, cmd, t, i, j,
                        c->ttran);
                }
            }

            // transfer actions for store/transfer actions in the origin state
            for (const stacmd_t *p = kernel->stacmd; p; p = p->next) {
                if (p->lhs != j || p->kind == stacmd_t::ACCEPT) continue;
                const size_t t = p->tag;

                // if there already exists action for the same tag and index,
                // it must be a store, and it takes precedence over transfer
                const stacmd_t *q = cmd;
                for (; q && !(q->tag == t && q->lhs == i); q = q->next);
                if (q) {
                    DASSERT(q->kind == stacmd_t::STORE);
                    continue;
                }

                cmd = make_stacmd(alc, stacmd_t::TRANSFER, cmd, t, i, j, HROOT);
            }
        }
    }

    // accept actions (if there is a final TNFA substate, it must be unique)
    for (c = b; c != e && c->state->type != nfa_state_t::FIN; ++c);
    if (c != e) {
        const int32_t i = static_cast<int32_t>(c->state - ctx.nfa.states);

        // save the head of store/transfer list before adding accept actions
        const stacmd_t *const st_cmd = cmd;

        // accept actions for lookahead tags
        for (size_t t = 0; t < ntag; ++t) {
            if (!fixed(ctx.dfa.tags[t])
                    && last(ctx.history, c->thist, t) != TAGVER_ZERO) {
                // there must be a store/transfer action for the final sub-state
                cmd = make_stacmd(alc, stacmd_t::ACCEPT, cmd, t, -1, i,
                    c->thist);
            }
        }

        // accept actions for store/transfer actions in the current state
        for (const stacmd_t *p = st_cmd; p; p = p->next) {
            if (p->lhs != i) continue;
            const size_t t = p->tag;

            // if there already exists accept action for the same tag and index,
            // it must come from lookahead tags, and therefore takes precedence
            const stacmd_t *q = cmd;
            for (; q != st_cmd && q->tag != t; q = q->next);
            if (q != st_cmd) {
                DASSERT(q->hist != HROOT);
                continue;
            }

            cmd = make_stacmd(alc, stacmd_t::ACCEPT, cmd, t, -1, i, HROOT);
        }
    }

    // staDFA actions must be sorted before searching for identical state
    sort_stacmd(cmd);

    ctx.stadfa_actions = cmd;
}

} // namespace re2c
