#include <algorithm>

#include "src/ir/dfa/closure.h"
#include "src/ir/nfa/nfa.h"

namespace re2c
{

static void closure_one(closure_t &clos, Tagpool &tagpool, clos_t &c0, nfa_state_t *n, tagver_t *tags, closure_t *shadow, std::valarray<Rule> &rules);
static void assert_items_are_grouped_by_rule(const closure_t &clos);
static void lower_lookahead_to_transition(closure_t &clos, Tagpool &tagpool);
static void update_versions(closure_t &clos, Tagpool &tagpool, tagver_t &maxver, tagver_t *newvers);
static void find_nondet(const closure_t &clos, size_t *nondet, const Tagpool &tagpool, const std::valarray<Rule> &rules);

void closure(closure_t &clos1, closure_t &clos2, Tagpool &tagpool,
	std::valarray<Rule> &rules, tagver_t &maxver, tagver_t *newvers,
	size_t *nondet, bool lookahead, closure_t *shadow)
{
	// build tagged epsilon-closure of the given set of NFA states
	clos2.clear();
	if (shadow) shadow->clear();
	tagver_t *tags = tagpool.buffer1;
	std::fill(tags, tags + tagpool.ntags, TAGVER_ZERO);
	for (clositer_t c = clos1.begin(); c != clos1.end(); ++c) {
		closure_one(clos2, tagpool, *c, c->state, tags, shadow, rules);
	}

	assert_items_are_grouped_by_rule(clos2);

	// see note [the difference between TDFA(0) and TDFA(1)]
	if (!lookahead) {
		lower_lookahead_to_transition(clos2, tagpool);
		if (shadow) lower_lookahead_to_transition(*shadow, tagpool);
	}

	find_nondet(clos2, nondet, tagpool, rules);

	// merge tags from different rules, find nondeterministic tags
	update_versions(clos2, tagpool, maxver, newvers);
	if (shadow) update_versions(*shadow, tagpool, maxver, newvers);
}

/* note [closure items are sorted by rule]
 *
 * By NFA construction NFA rules with higher priority correspond to the left
 * alternative of the branching NFA states.
 *
 * The initial epsilon-closure explores each rule in turn: all states of the
 * high-priority rule are explored before any states of the low-priority rule.
 * Thus in the initial closure items are sorted by rule.
 *
 * Subsequent closures preserve this invariant: they explore states in the
 * exact same order as they are listed in the parent closure, so if states
 * were sorted by rule, they remain so in the new closure.
 */
void assert_items_are_grouped_by_rule(const closure_t &clos)
{
	size_t r1 = 0, r2;
	for (cclositer_t c = clos.begin(); c != clos.end(); ++c) {
		r2 = c->state->rule;
		assert(r2 >= r1);
		r1 = r2;
	}
}

/* note [epsilon-closures in tagged NFA]
 *
 * The closure includes all NFA states that are reachable by epsilon-paths
 * from the given set of states and either are final or have non-epsilon
 * transitions. Note that by construction NFA states cannot have both
 * epsilon and non-epsilon transitions.
 *
 * Each closure state might be reachable by multiple epsilon-paths with
 * different tags: this means that the regular expression is ambiguous
 * and can be parsed in different ways. We resolve ambiguity by always
 * choosing the leftmost epsilon-path through the NFA.
 *
 * Compilation of regular expression into NFA takes into account semantics
 * of individual subexpressions: e.g., greedy iteration is compiled so that
 * the leftmost path re-iterates rather than leaves the subexpression..
 */
void closure_one(closure_t &clos, Tagpool &tagpool, clos_t &c0,
	nfa_state_t *n, tagver_t *tags, closure_t *shadow,
	std::valarray<Rule> &rules)
{
	if (n->loop) return;

	n->loop = true;
	switch (n->type) {
		case nfa_state_t::NIL:
			closure_one(clos, tagpool, c0, n->nil.out, tags, shadow, rules);
			break;
		case nfa_state_t::ALT:
			closure_one(clos, tagpool, c0, n->alt.out1, tags, shadow, rules);
			closure_one(clos, tagpool, c0, n->alt.out2, tags, shadow, rules);
			break;
		case nfa_state_t::TAG: {
			const size_t t = n->tag.info;
			const tagver_t old = tags[t];
			tags[t] = n->tag.bottom ? TAGVER_BOTTOM : TAGVER_CURSOR;
			closure_one(clos, tagpool, c0, n->tag.out, tags, shadow, rules);
			tags[t] = old;
			break;
		}
		case nfa_state_t::RAN: {
			c0.state = n;
			c0.ttran = tagpool.insert(tags);
			clositer_t
				c = clos.begin(),
				e = clos.end();
			for (; c != e && c->state != n; ++c);
			if (c == e) {
				clos.push_back(c0);
			} else if (shadow) {
				shadow->push_back(c0);
			}
			break;
		}
		case nfa_state_t::FIN: {
			// see note [at most one final item per closure]
			c0.state = n;
			c0.ttran = tagpool.insert(tags);
			clositer_t
				c = clos.begin(),
				e = clos.end();
			for (; c != e && c->state->type != nfa_state_t::FIN; ++c);
			if (c == e) {
				clos.push_back(c0);
			} else {
				if (c->state != n) {
					rules[n->rule].shadow.insert(rules[c->state->rule].code->fline);
				}
				if (shadow) {
					shadow->push_back(c0);
				}
			}
			break;
		}
	}
	n->loop = false;
}

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

// Make TDFA(0) look like TDFA(1), which expects that after epsilon-closure
// lookahead tags occupy the place of future transition tags, while
// transition tags are scattered across tag versions inherited from the
// previous kernel. TDFA(0)'s representation is simpler and more logical,
// and 'lowering' is just a waste for TDFA(0). However, supporting two
// different handlers for TDFA(0) and TDFA(1) is unmaintainable, and since
// TDFA(1) is default, it has the fast path.
void lower_lookahead_to_transition(closure_t &clos, Tagpool &tagpool)
{
	const size_t ntag = tagpool.ntags;
	tagver_t *vers = tagpool.buffer1;

	for (clositer_t c = clos.begin(); c != clos.end(); ++c) {
		if (c->ttran == ZERO_TAGS) continue;

		const tagver_t
			*look = tagpool[c->ttran],
			*oldv = tagpool[c->tvers];
		for (size_t t = 0; t < ntag; ++t) {
			const tagver_t l = look[t];
			vers[t] = l == TAGVER_ZERO ? oldv[t] : l;
		}
		c->tvers = tagpool.insert(vers);
		c->ttran = ZERO_TAGS;
	}
}

void update_versions(closure_t &clos, Tagpool &tagpool,
	tagver_t &maxver, tagver_t *newvers)
{
	const size_t ntag = tagpool.ntags;
	tagver_t *cur = tagpool.buffer1,
		*bot = tagpool.buffer2,
		*vers = tagpool.buffer3,
		*tran = tagpool.buffer4;
	clositer_t b = clos.begin(), e = clos.end(), c;

	// for each tag, if there is at least one tagged transition,
	// allocate new version (negative for bottom and positive for
	// normal transition, however absolute value should be unique
	// among all versions of all tags)
	for (size_t t = 0; t < ntag; ++t) {
		tagver_t &newcur = newvers[t],
			&newbot = newvers[ntag + t];
		cur[t] = bot[t] = TAGVER_ZERO;

		for (c = b; c != e; ++c) {
			if (tagpool[c->tvers][t] == TAGVER_CURSOR) {
				if (newcur == TAGVER_ZERO) {
					newcur = ++maxver;
				}
				cur[t] = newcur;
				break;
			}
		}

		for (c = b; c != e; ++c) {
			if (tagpool[c->tvers][t] == TAGVER_BOTTOM) {
				if (newbot == TAGVER_ZERO) {
					newbot = -(++maxver);
				}
				bot[t] = newbot;
				break;
			}
		}
	}

	// set transition tags and update versions
	for (c = b; c != e; ++c) {
		const tagver_t
			*look = tagpool[c->ttran],
			*oldv = tagpool[c->tvers];

		for (size_t i = 0; i < ntag; ++i) {
			const tagver_t o = oldv[i], l = look[i];
			tagver_t &v = vers[i], &t = tran[i];

			if (l != TAGVER_ZERO) {
				v = l;
				t = TAGVER_ZERO;
			} else if (o == TAGVER_CURSOR) {
				v = t = cur[i];
			} else if (o == TAGVER_BOTTOM) {
				v = t = bot[i];
			} else {
				v = o;
				t = TAGVER_ZERO;
			}
		}

		c->tvers = tagpool.insert(vers);
		c->ttran = tagpool.insert(tran);
	}
}

/*
 * For each tag, find the number of parallel versions of this tag
 * used in this closure (degree of non-determinism).
 */
void find_nondet(const closure_t &clos, size_t *nondet,
	const Tagpool &tagpool, const std::valarray<Rule> &rules)
{
	std::set<tagver_t> uniq;
	cclositer_t b = clos.begin(), e = clos.end(), c, x0, x;

	// see note [closure items are sorted by rule]
	for (c = b; c != e;) {
		const size_t r = c->state->rule;
		const Rule &rule = rules[r];

		for (x0 = c; ++c != e && c->state->rule == r;);

		for (size_t t = rule.ltag; t < rule.htag; ++t) {
			uniq.clear();
			for (x = x0; x != c; ++x) {
				uniq.insert(tagpool[x->tvers][t]);
			}
			nondet[t] = std::max(nondet[t], uniq.size());
		}
	}
}

} // namespace re2c
