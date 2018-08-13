#include <assert.h>
#include "src/util/c99_stdint.h"
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <set>
#include <stack>
#include <utility>
#include <valarray>

#include "src/conf/opt.h"
#include "src/dfa/determinization.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/nfa/nfa.h"
#include "src/re/rule.h"


namespace re2c
{

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


static void prune(closure_t &, std::valarray<Rule> &);
static void lower_lookahead_to_transition(closure_t &);
static void generate_versions(determ_context_t &);
static bool cmpby_rule_state(const clos_t &, const clos_t &);


void tagged_epsilon_closure(determ_context_t &ctx)
{
    closure_t &closure = ctx.dc_closure;

    // build tagged epsilon-closure of the given set of NFA states
    if (ctx.dc_opts->posix_captures) {
        closure_posix(ctx);
        prune(closure, ctx.dc_nfa.rules);
        std::sort(closure.begin(), closure.end(), cmpby_rule_state);
        orders(ctx);
    } else {
        closure_leftmost(ctx);
        prune(closure, ctx.dc_nfa.rules);
    }

    // see note [the difference between TDFA(0) and TDFA(1)]
    if (!ctx.dc_opts->lookahead) {
        lower_lookahead_to_transition(closure);
    }

    // merge tags from different rules, find nondeterministic tags
    generate_versions(ctx);
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


void prune(closure_t &closure, std::valarray<Rule> &rules)
{
    clositer_t b = closure.begin(), e = closure.end(), i, j;

    // drop "inner" states (non-final without outgoing non-epsilon transitions)
    j = std::stable_partition(b, e, clos_t::ran);
    e = std::stable_partition(j, e, clos_t::fin);
    size_t n = static_cast<size_t>(e - b);

    // drop all final states except one; mark dropped rules as shadowed
    // see note [at most one final item per closure]
    if (j != e) {
        std::sort(j, e, cmpby_rule_state);
        const uint32_t l = rules[j->state->rule].code->fline;
        for (i = j; ++i < e;) {
            rules[i->state->rule].shadow.insert(l);
        }
        n = static_cast<size_t>(j - b) + 1;
    }

    closure.resize(n);
}


void lower_lookahead_to_transition(closure_t &closure)
{
    for (clositer_t c = closure.begin(); c != closure.end(); ++c) {
        c->ttran = c->tlook;
        c->tlook = HROOT;
    }
}


void generate_versions(determ_context_t &ctx)
{
    dfa_t &dfa = ctx.dc_dfa;
    const std::vector<Tag> &tags = dfa.tags;
    const size_t ntag = tags.size();
    tagver_t &maxver = dfa.maxtagver;
    tagver_table_t &tvtbl = ctx.dc_tagvertbl;
    tagver_t *vers = tvtbl.buffer;
    closure_t &clos = ctx.dc_closure;
    tag_history_t &thist = ctx.dc_taghistory;
    newvers_t &newvers = ctx.dc_newvers;

    clositer_t b = clos.begin(), e = clos.end(), c;
    newver_cmp_t cmp(thist);
    newvers_t newacts(cmp);
    tcmd_t *cmd = NULL;

    // for each tag, if there is at least one tagged transition,
    // allocate new version (negative for bottom and positive for
    // normal transition, however absolute value should be unique
    // among all versions of all tags)
    for (c = b; c != e; ++c) {
        const hidx_t l = c->tlook, h = c->ttran;
        if (h == HROOT) continue;

        const tagver_t *vs = tvtbl[c->tvers];
        for (size_t t = 0; t < ntag; ++t) {
            const Tag &tag = tags[t];
            const tagver_t
                h0 = thist.last(h, t),
                l0 = thist.last(l, t);

            if (h0 == TAGVER_ZERO) continue;

            const tagver_t v = history(tag) ? vs[t] : TAGVER_ZERO;
            newver_t x = {t, v, h};
            const tagver_t
                n = (maxver + 1) * (h0 == TAGVER_BOTTOM ? -1 : 1),
                m = newvers.insert(std::make_pair(x, n)).first->second;
            if (n == m) ++maxver;

            if (!fixed(tag) && (l0 == TAGVER_ZERO || history(tag))) {
                newacts.insert(std::make_pair(x, m));
            }
        }
    }

    // actions
    for (newvers_t::iterator i = newacts.begin(); i != newacts.end(); ++i) {
        const tagver_t m = i->second, v = i->first.base;
        const hidx_t h = i->first.history;
        const size_t t = i->first.tag;
        if (history(tags[t])) {
            cmd = dfa.tcpool.make_add(cmd, abs(m), abs(v), thist, h, t);
        } else {
            cmd = dfa.tcpool.make_set(cmd, abs(m), thist.last(h, t));
        }
    }

    // mark tags with history
    for (newvers_t::iterator j = newvers.begin(); j != newvers.end(); ++j) {
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
                h0 = thist.last(h, t),
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

} // namespace re2c
