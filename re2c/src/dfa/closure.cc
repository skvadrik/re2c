#include <string.h>

#include "src/dfa/closure.h"
#include "src/nfa/nfa.h"
#include "src/util/local_increment.h"

namespace re2c
{

static void raw_closure(const closure_t &clos1, closure_t &clos, closure_t *shadow,
	Tagpool &tagpool, const std::vector<Tag> &tags, std::valarray<Rule> &rules);
static bool better(const clos_t &c1, const clos_t &c2, Tagpool &tagpool, const std::vector<Tag> &tags);
static void lower_lookahead_to_transition(closure_t &clos);
static tcmd_t *generate_versions(closure_t &clos, const std::vector<Tag> &tags,
	Tagpool &tagpool, tcpool_t &tcpool, tagver_t &maxver, newvers_t &newvers);
static void orders(closure_t &clos, Tagpool &tagpool, const std::vector<Tag> &tags);
static bool cmpby_rule_state(const clos_t &x, const clos_t &y);

tcmd_t *closure(closure_t &clos1, closure_t &clos2, Tagpool &tagpool,
	tcpool_t &tcpool, std::valarray<Rule> &rules, tagver_t &maxver,
	newvers_t &newvers, bool lookahead, closure_t *shadow,
	const std::vector<Tag> &tags)
{
	// build tagged epsilon-closure of the given set of NFA states
	raw_closure(clos1, clos2, shadow, tagpool, tags, rules);

	orders(clos2, tagpool, tags);

	std::sort(clos2.begin(), clos2.end(), cmpby_rule_state);

	// see note [the difference between TDFA(0) and TDFA(1)]
	if (!lookahead) {
		lower_lookahead_to_transition(clos2);
		if (shadow) lower_lookahead_to_transition(*shadow);
	}

	// merge tags from different rules, find nondeterministic tags
	tcmd_t *cmd = generate_versions(clos2, tags, tagpool, tcpool, maxver, newvers);
	if (shadow) generate_versions(*shadow, tags, tagpool, tcpool, maxver, newvers);

	return cmd;
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

static void indegree(nfa_state_t *s)
{
	++s->indeg;
	++s->indeg_backup;
	if (s->indeg > 1) return;
	switch (s->type) {
		case nfa_state_t::NIL:
			indegree(s->nil.out);
			break;
		case nfa_state_t::ALT:
			indegree(s->alt.out1);
			indegree(s->alt.out2);
			break;
		case nfa_state_t::TAG:
			indegree(s->tag.out);
			break;
		default:
			break;
	}
}

/*
 * If there is an epsilon-loop through initial closure states X and Y,
 * then in-degree of both X and Y in queue is non-zero; whichever of them
 * is popped out of queue first (say, X) may lead to an epsilon-loop through
 * Y back to X, reducing Y's in-degree before epsilon-path starting in Y is
 * inspected. In such unfortunate cases we have to reinstate Y's original
 * in-degree and repeat all the work.
 *
 * Paths with epsilon-loops will be terminated: by the time they are added
 * to queue, the resulting closure must already contain a non-looping path
 * for the same state, so the looping path must be compared to the old one.
 * This comparison will favour non-looping path with both POSIX and leftmost
 * policies. With leftmost non-looping history will dominate, since it is a
 * prefix of looping history. With POSIX either histories are equal for all
 * tags and there's no point in adding identical path to queue, or histories
 * of some orbit tag are not equal and shorter orbit history dominates.
 */
static void enqueue(closure_t &todo, closure_t &done, closure_t *shadow,
	clos_t x, Tagpool &tagpool, const std::vector<Tag> &tags)
{
	nfa_state_t *n = x.state;
	clositer_t e, c;

	if (n->indeg == 0) n->indeg = n->indeg_backup;
	--n->indeg;

	c = done.begin(); e = done.end();
	for(; c != e && c->state != n; ++c);
	if (c == e) {
		done.push_back(x);
	} else if (better(*c, x, tagpool, tags)) {
		if (shadow) shadow->push_back(*c);
		*c = x;
	} else {
		if (shadow) shadow->push_back(x);
		return;
	}

	c = todo.begin(); e = todo.end();
	for(; c != e && c->state != n; ++c);
	if (c == e) {
		todo.push_back(x);
	} else if (better(*c, x, tagpool, tags)) {
		std::swap(*c, x);
	}
}

void raw_closure(const closure_t &clos1, closure_t &done, closure_t *shadow,
	Tagpool &tagpool, const std::vector<Tag> &tags, std::valarray<Rule> &rules)
{
	closure_t todo;
	tagtree_t &history = tagpool.history;

	// initialize in-degree of NFA states in this epsilon-closure
	// (outer NFA transitions do not contribute to in-degree)
	for (cclositer_t c = clos1.begin(); c != clos1.end(); ++c) {
		indegree(c->state);
	}

	// enqueue all initial states
	done.clear();
	if (shadow) shadow->clear();
	for (cclositer_t c = clos1.begin(); c != clos1.end(); ++c) {
		enqueue(todo, done, shadow, *c, tagpool, tags);
	}

	while (!todo.empty()) {

		// find state with the least in-degree and remove it from queue
		clositer_t c = todo.begin(), e = todo.end(), c0 = c;
		for (; c != e; ++c) {
			if (c0->state->indeg == 0) break;
			if (c0->state->indeg > c->state->indeg) c0 = c;
		}
		clos_t x = *c0;
		*c0 = todo.back(); todo.pop_back(); // "quick" removal

		// enqueue child NFA states
		nfa_state_t *n = x.state;
		switch (n->type) {
			default: break;
			case nfa_state_t::NIL:
				x.state = n->nil.out;
				enqueue(todo, done, shadow, x, tagpool, tags);
				break;
			case nfa_state_t::ALT:
				x.state = n->alt.out1;
				x.index = history.push(x.index, Tag::RIGHTMOST, 1);
				enqueue(todo, done, shadow, x, tagpool, tags);
				x.state = n->alt.out2;
				x.index = history.push(x.index, Tag::RIGHTMOST, 0);
				enqueue(todo, done, shadow, x, tagpool, tags);
				break;
			case nfa_state_t::TAG:
				x.state = n->tag.out;
				x.tlook = history.push(x.tlook, n->tag.info,
					n->tag.bottom ? TAGVER_BOTTOM : TAGVER_CURSOR);
				enqueue(todo, done, shadow, x, tagpool, tags);
				break;
		}
	}

	// reset in-degree to zero (before removing any states from closure)
	for (clositer_t c = done.begin(); c != done.end(); ++c) {
		c->state->indeg = c->state->indeg_backup = 0;
	}

	// drop "inner" states (non-final without outgoing non-epsilon transitions)
	clositer_t b = done.begin(), e = done.end(), f;
	f = std::partition(b, e, clos_t::ran);
	e = std::partition(f, e, clos_t::fin);
	done.resize(static_cast<size_t>(e - b));

	// drop all final states except one; mark dropped rules as shadowed
	// see note [at most one final item per closure]
	if (e != f) {
		std::sort(f, e, cmpby_rule_state);
		const uint32_t l = rules[f->state->rule].code->fline;
		for (clositer_t c = f; ++c < e;) {
			rules[c->state->rule].shadow.insert(l);
		}
		done.resize(static_cast<size_t>(f - b) + 1);
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
	Tagpool &tagpool, const std::vector<Tag> &tags)
{
	if (c1.ttran == c2.ttran
		&& c1.tvers == c2.tvers
		&& c1.tlook == c2.tlook
		&& c1.order == c2.order
		&& c1.index == c2.index) return false;

	const hidx_t
		l1 = c1.tlook, l2 = c2.tlook,
		t1 = c1.ttran, t2 = c2.ttran;
	const tagver_t
		*v1 = tagpool[c1.tvers], *v2 = tagpool[c2.tvers],
		*o1 = tagpool[c1.order], *o2 = tagpool[c2.order];
	tagver_t x, y;
	tagtree_t &tagtree = tagpool.history;

	for (size_t t = 0; t < tagpool.ntags; ++t) {
		const Tag &tag = tags[t];

		// orbit capture tag: compare by order and tagged epsilon-paths
		if (orbit(tag)) {
			x = o1[t]; y = o2[t];
			if (x < y) return false;
			if (x > y) return true;

			const int cmp = tagtree.compare_last(l1, l2, t);
			if (cmp < 0) return false;
			if (cmp > 0) return true;

			assert(v1[t] == v2[t]);

		// open/close capture tag: maximize (on lookahead and versions);
		// if either one is bottom, fallback to leftmost disambiguation
		// we don't use orders for minimize/maximize, because they are
		// already used for leftmost
		} else if (capture(tag)) {
			x = tagtree.last(l1, t);
			y = tagtree.last(l2, t);
			if (x < 0 || y < 0) goto leftmost;
			if (x > y) return false;
			if (x < y) return true;

			x = tagtree.last(t1, t);
			y = tagtree.last(t2, t);
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

			const int cmp = tagtree.compare_full(c1.index, c2.index, Tag::RIGHTMOST);
			if (cmp < 0) return false;
			if (cmp > 0) return true;

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

void lower_lookahead_to_transition(closure_t &clos)
{
	for (clositer_t c = clos.begin(); c != clos.end(); ++c) {
		c->ttran = c->tlook;
		c->tlook = HROOT;
	}
}

tcmd_t *generate_versions(closure_t &clos, const std::vector<Tag> &tags,
	Tagpool &tagpool, tcpool_t &tcpool, tagver_t &maxver, newvers_t &newvers)
{
	tcmd_t *cmd = NULL;
	const size_t ntag = tagpool.ntags;
	tagver_t *vers = tagpool.buffer;
	tagtree_t &tagtree = tagpool.history;
	clositer_t b = clos.begin(), e = clos.end(), c;
	newver_cmp_t cmp = {tagtree};
	newvers_t newacts(cmp);

	// for each tag, if there is at least one tagged transition,
	// allocate new version (negative for bottom and positive for
	// normal transition, however absolute value should be unique
	// among all versions of all tags)
	for (c = b; c != e; ++c) {
		const hidx_t l = c->tlook, h = c->ttran;
		if (h == HROOT) continue;

		const tagver_t *vs = tagpool[c->tvers];
		for (size_t t = 0; t < ntag; ++t) {
			const Tag &tag = tags[t];
			const tagver_t
				h0 = tagtree.last(h, t),
				l0 = tagtree.last(l, t);

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
			cmd = tcpool.make_add(cmd, abs(m), abs(v), tagtree, h, t);
		} else {
			cmd = tcpool.make_set(cmd, abs(m), tagtree.last(h, t));
		}
	}

	// update tag versions in closure
	for (c = b; c != e; ++c) {
		const hidx_t h = c->ttran;
		if (h == HROOT) continue;

		const tagver_t *vs = tagpool[c->tvers];
		for (size_t t = 0; t < ntag; ++t) {
			const tagver_t
				v0 = vs[t],
				h0 = tagtree.last(h, t),
				v = history(tags[t]) ? v : TAGVER_ZERO;
			if (h0 == TAGVER_ZERO) {
				vers[t] = v0;
			} else {
				newver_t x = {t, v, h};
				vers[t] = newvers[x];
			}
		}
		c->tvers = tagpool.insert(vers);
	}

	return cmd;
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

typedef std::pair<tagver_t, hidx_t> key_t;
struct cmp_orbit_t
{
	tagtree_t &tree;
	size_t tag;
	bool operator()(const key_t &x, const key_t &y)
	{
		if (x.first < y.first) return true;
		if (x.first > y.first) return false;
		return tree.compare_last(x.second, y.second, tag) < 0;
	}
};
struct cmp_leftmost_t
{
	tagtree_t &tree;
	bool operator()(const key_t &x, const key_t &y)
	{
		if (x.first < y.first) return true;
		if (x.first > y.first) return false;
		return tree.compare_full(x.second, y.second, Tag::RIGHTMOST) < 0;
	}
};

void orders(closure_t &clos, Tagpool &tagpool, const std::vector<Tag> &tags)
{
	tagtree_t &tagtree = tagpool.history;
	clositer_t b = clos.begin(), e = clos.end(), c;
	const size_t
		ntag = tagpool.ntags,
		nclos = clos.size();

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
			const cmp_orbit_t cmp = {tagtree, t};
			std::set<key_t, cmp_orbit_t> keys(cmp);
			for (c = b; c != e; ++c) {
				keys.insert(key_t(tagpool[c->order][t], c->tlook));
			}
			for (c = b; c != e; ++c, o += ntag) {
				const ptrdiff_t d = std::distance(keys.begin(),
					keys.find(key_t(tagpool[c->order][t], c->tlook)));
				o[t] = static_cast<tagver_t>(d);
			}

		// for simple tags and non-orbit capture tags item's order
		// equals position of this item in leftmost NFA traversal
		// (it's the same for all tags)
		} else {
			const cmp_leftmost_t cmp = {tagtree};
			std::set<key_t, cmp_leftmost_t> keys(cmp);
			for (c = b; c != e; ++c) {
				keys.insert(key_t(tagpool[c->order][t], c->index));
			}
			for (c = b; c != e; ++c, o += ntag) {
				const ptrdiff_t d = std::distance(keys.begin(),
					keys.find(key_t(tagpool[c->order][t], c->index)));
				o[t] = static_cast<tagver_t>(d);
			}
		}
	}

	o = orders;
	for (c = b; c != e; ++c, o += ntag) {
		c->order = tagpool.insert(o);
	}
}

} // namespace re2c
