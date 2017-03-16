#include <string.h>

#include "src/dfa/closure.h"
#include "src/nfa/nfa.h"
#include "src/util/local_increment.h"

namespace re2c
{

static void closure_one(closure_t &clos, Tagpool &tagpool, tagtree_t &tagtree,
	clos_t &c0, nfa_state_t *n, const std::vector<Tag> &tags, closure_t *shadow, std::valarray<Rule> &rules);
static bool better(const clos_t &c1, const clos_t &c2, Tagpool &tagpool, tagtree_t &tagtree, const std::vector<Tag> &tags);
static void lower_lookahead_to_transition(closure_t &clos, Tagpool &tagpool, tagtree_t &tagtree);
static void update_versions(closure_t &clos, Tagpool &tagpool, tagtree_t &tagtree, tagver_t &maxver, tagver_t *newvers);
static void orders(closure_t &clos, Tagpool &tagpool, tagtree_t &tagtree, const std::vector<Tag> &tags);
static void find_nondet(const closure_t &clos, size_t *nondet, const Tagpool &tagpool, const std::valarray<Rule> &rules);
static bool cmpby_rule_state(const clos_t &x, const clos_t &y);

void closure(closure_t &clos1, closure_t &clos2, Tagpool &tagpool, tagtree_t &tagtree,
	std::valarray<Rule> &rules, tagver_t &maxver, tagver_t *newvers,
	size_t *nondet, bool lookahead, closure_t *shadow, const std::vector<Tag> &tags)
{
	// build tagged epsilon-closure of the given set of NFA states
	clos2.clear();
	if (shadow) shadow->clear();
	tagtree.init();
	for (clositer_t c = clos1.begin(); c != clos1.end(); ++c) {
		closure_one(clos2, tagpool, tagtree, *c, c->state, tags, shadow, rules);
	}

	orders(clos2, tagpool, tagtree, tags);

	std::sort(clos2.begin(), clos2.end(), cmpby_rule_state);

	// see note [the difference between TDFA(0) and TDFA(1)]
	if (!lookahead) {
		lower_lookahead_to_transition(clos2, tagpool, tagtree);
		if (shadow) lower_lookahead_to_transition(*shadow, tagpool, tagtree);
	}

	find_nondet(clos2, nondet, tagpool, rules);

	// merge tags from different rules, find nondeterministic tags
	update_versions(clos2, tagpool, tagtree, maxver, newvers);
	if (shadow) update_versions(*shadow, tagpool, tagtree, maxver, newvers);
}

bool cmpby_rule_state(const clos_t &x, const clos_t &y)
{
	const nfa_state_t *sx = x.state, *sy = y.state;
	const size_t rx = sx->rule, ry = sy->rule;
	if (rx < ry) return true;
	if (rx > ry) return false;
	if (sx < sy) return true;
	if (sx > sy) return false;
	assert(false);
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
 * and can be parsed in different ways. Disambiguation strategy depends
 * on the type of the first (most prioritized) ambiguous tag: for simple
 * tags we always choose the leftmost epsilon-path through the NFA, for
 * POSIX captures the rules are more complex (opening and closing tags
 * are maximized unless one of them is bottom, in which case we fallback
 * to leftmost strategy; orbit tags are compared by order and by tagged
 * epsilon-paths so that earlier iterations are maximized).
 */
void closure_one(closure_t &clos, Tagpool &tagpool, tagtree_t &tagtree, clos_t &c0,
	nfa_state_t *n, const std::vector<Tag> &tags, closure_t *shadow,
	std::valarray<Rule> &rules)
{
	if (n->loop) return;
	local_increment_t<uint8_t> _(n->loop);

	clositer_t c = clos.begin(), e = clos.end();
	switch (n->type) {
		case nfa_state_t::NIL:
			closure_one(clos, tagpool, tagtree, c0, n->nil.out, tags, shadow, rules);
			return;
		case nfa_state_t::ALT:
			closure_one(clos, tagpool, tagtree, c0, n->alt.out1, tags, shadow, rules);
			closure_one(clos, tagpool, tagtree, c0, n->alt.out2, tags, shadow, rules);
			return;
		case nfa_state_t::TAG:
			tagtree.push(n->tag.info, n->tag.bottom ? TAGVER_BOTTOM : TAGVER_CURSOR);
			closure_one(clos, tagpool, tagtree, c0, n->tag.out, tags, shadow, rules);
			tagtree.pop(n->tag.info);
			return;
		case nfa_state_t::RAN:
			for (; c != e && c->state != n; ++c);
			break;
		case nfa_state_t::FIN:
			// see note [at most one final item per closure]
			for (; c != e && c->state->type != nfa_state_t::FIN; ++c);
			if (c != e && c->state != n) {
				rules[n->rule].shadow.insert(rules[c->state->rule].code->fline);
				return;
			}
			break;
	}

	clos_t c2 = {c0.origin, n, c0.tvers,
		tagpool.insert(tagtree.leaves()), c0.order, c0.index++};
	if (c == e) {
		clos.push_back(c2);
	} else {
		clos_t &c1 = *c;
		if (better(c1, c2, tagpool, tagtree, tags)) std::swap(c1, c2);
		if (shadow) shadow->push_back(c2);
	}
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

bool better(const clos_t &c1, const clos_t &c2,
	Tagpool &tagpool, tagtree_t &tagtree, const std::vector<Tag> &tags)
{
	if (c1.ttran == c2.ttran
		&& c1.tvers == c2.tvers
		&& c1.order == c2.order
		&& c1.index == c2.index) return false;

	const tagver_t
		*l1 = tagpool[c1.ttran], *l2 = tagpool[c2.ttran],
		*v1 = tagpool[c1.tvers], *v2 = tagpool[c2.tvers],
		*o1 = tagpool[c1.order], *o2 = tagpool[c2.order];
	tagver_t x, y;

	for (size_t t = 0; t < tagpool.ntags; ++t) {
		const Tag &tag = tags[t];

		// orbit capture tag: compare by order and tagged epsilon-paths
		if (orbit(tag)) {
			x = o1[t]; y = o2[t];
			if (x < y) return false;
			if (x > y) return true;

			const int cmp = tagtree.compare_paths(l1[t], l2[t]);
			if (cmp < 0) return false;
			if (cmp > 0) return true;

			assert(v1[t] == v2[t]);

		// open/close capture tag: maximize (on lookahead and versions);
		// if either one is bottom, fallback to leftmost disambiguation
		} else if (capture(tag)) {
			x = tagtree.elem(l1[t]);
			y = tagtree.elem(l2[t]);
			if (x < 0 || y < 0) goto leftmost;
			if (x > y) return false;
			if (x < y) return true;

			x = v1[t]; y = v2[t];
			if (x < 0 || y < 0) goto leftmost;
			if (x > y) return false;
			if (x < y) return true;

		// simple tag: always prefer leftmost
		} else {
		leftmost:
			x = o1[t]; y = o2[t];
			if (x < y) return false;
			if (x > y) return true;

			size_t i = c1.index, j = c2.index;
			if (i < j) return false;
			if (i > j) return true;
			assert(false); // all indexes are different
		}
	}

	return false;
}

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
void lower_lookahead_to_transition(closure_t &clos, Tagpool &tagpool, tagtree_t &tagtree)
{
	const size_t ntag = tagpool.ntags;
	tagver_t *vers = tagpool.buffer1;

	for (clositer_t c = clos.begin(); c != clos.end(); ++c) {
		if (c->ttran == ZERO_TAGS) continue;

		const tagver_t
			*look = tagpool[c->ttran],
			*oldv = tagpool[c->tvers];
		for (size_t t = 0; t < ntag; ++t) {
			const tagver_t l = tagtree.elem(look[t]);
			vers[t] = l == TAGVER_ZERO ? oldv[t] : l;
		}
		c->tvers = tagpool.insert(vers);
		c->ttran = ZERO_TAGS;
	}
}

void update_versions(closure_t &clos, Tagpool &tagpool, tagtree_t &tagtree,
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
			const tagver_t o = oldv[i], l = tagtree.elem(look[i]);
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

/* note [POSIX disambiguation]
 *
 * POSIX disambiguation rules demand that earlier subexpressions match
 * the longest possible prefix of the input string (without violating the
 * whole match). To accommodate these rules, we resolve conflicts on orbit
 * tags by lexicographic comparison of tag offsets on the way to conflicting
 * NFA states.
 *
 * By lexicographic comparison we mean that if one history is a proper prefix
 * of another history, it is lexicographically less; otherwise for the first
 * pair of different offsets, if one offset is greater than the other, then
 * the corresponding history is lexicographically less.
 *
 * For the given input string, it is possible to define lexicographical order
 * on tag histories corresponding to all matching paths through NFA, because
 * the length of histories is bounded by the length of input (epsilon-cycles
 * are forbidden) and the set of all possible offsets is finite (also bounded
 * by input length).
 *
 * Moreover, for a given prefix of the input string, lexicographic order on
 * histories of the whole string is an extension of order on prefix histories:
 * once comparison of two prefix histories X and Y establishes that X < Y,
 * all further comarisons of X's descendants to Y's descendants will yield
 * the same result. This is obvious unless X is a proper prefix of Y;
 * otherwise, this is true because any offset appended to X will be greater
 * than any offset in Y (it corresponds to further position in the input
 * string) and therefore all descendants of X will be less than Y.
 *
 * Therefore, at any point of ambiguity we can choose lexicographically least
 * history and claim that it corresponds to lexicographically least history
 * for the whole input.
 *
 * For the same reason, keeping the whole history of offsets is not necessary:
 * it is sufficient to remember only the relative order of any pair of
 * histories and use it as the first component in lexicographic comparison.
 *
 * This part of the algorithm was invented by Christopher Kuklewicz.
 */

typedef std::pair<tagver_t, tagver_t> key1_t;
struct cmp_t
{
	tagtree_t &tree;
	bool operator()(const key1_t &x, const key1_t &y)
	{
		if (x.first < y.first) return true;
		if (x.first > y.first) return false;
		return tree.compare_paths(x.second, y.second) < 0;
	}
};

void orders(closure_t &clos, Tagpool &tagpool,
	tagtree_t &tagtree, const std::vector<Tag> &tags)
{
	clositer_t b = clos.begin(), e = clos.end(), c;
	const size_t
		ntag = tagpool.ntags,
		nclos = clos.size();

	const cmp_t cmp = {tagtree};
	std::set<key1_t, cmp_t> keys1(cmp);

	typedef std::pair<tagver_t, size_t> key2_t;
	std::set<key2_t> keys2;

	size_t &maxclos = tagpool.maxclos;
	tagver_t *&orders = tagpool.orders, *o;
	if (maxclos < nclos) {
		maxclos = nclos * 2; // in advance
		delete[] orders;
		orders = new tagver_t[ntag * maxclos];
	}

	for (size_t t = 0; t < ntag; ++t) {
		o = orders;

		// see note [POSIX disambiguation]
		if (orbit(tags[t])) {
			keys1.clear();
			for (c = b; c != e; ++c) {
				keys1.insert(key1_t(tagpool[c->order][t], tagpool[c->ttran][t]));
			}
			for (c = b; c != e; ++c, o += ntag) {
				const ptrdiff_t d = std::distance(keys1.begin(),
					keys1.find(key1_t(tagpool[c->order][t], tagpool[c->ttran][t])));
				o[t] = static_cast<tagver_t>(d);
			}

		// for simple tags and non-orbit capture tags item's order
		// equals position of this item in leftmost NFA traversal
		// (it's the same for all tags)
		} else {
			for (c = b; c != e; ++c) {
				keys2.insert(key2_t(tagpool[c->order][t], c->index));
			}
			for (c = b; c != e; ++c, o += ntag) {
				const ptrdiff_t d = std::distance(keys2.begin(),
					keys2.find(key2_t(tagpool[c->order][t], c->index)));
				o[t] = static_cast<tagver_t>(d);
			}
		}
	}

	o = orders;
	for (c = b; c != e; ++c, o += ntag) {
		c->order = tagpool.insert(o);
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

	size_t r0 = 0;
	for (c = b; c != e;) {
		const size_t r = c->state->rule;
		const Rule &rule = rules[r];

		// closure items must be grouped by rule
		assert(r >= r0); r0 = r;

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
