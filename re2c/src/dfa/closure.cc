#include <string.h>

#include "src/dfa/closure.h"
#include "src/dfa/tagpool.h"
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
	newvers_t &newvers, closure_t *shadow, const std::vector<Tag> &tags)
{
	// build tagged epsilon-closure of the given set of NFA states
	raw_closure(clos1, clos2, shadow, tagpool, tags, rules);

	orders(clos2, tagpool, tags);

	std::sort(clos2.begin(), clos2.end(), cmpby_rule_state);

	// see note [the difference between TDFA(0) and TDFA(1)]
	if (!tagpool.opts->lookahead) {
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

// leftmost greedy disambiguation: order equals item's position
// in leftmost NFA traversal (it's the same for all tags)
static int32_t cmp_leftmost(const clos_t &x, const clos_t &y, Tagpool &tagpool)
{
	const tagver_t
		ox = tagpool[x.order][0],
		oy = tagpool[y.order][0];
	if (ox < oy) return -1;
	if (ox > oy) return 1;
	return tagpool.history.compare_plain(x.index, y.index, Tag::RIGHTMOST);
}

// Skip non-orbit start tags: their position is fixed on some higher-priority
// tag (except the very first tag, but in RE2C match is always anchored).
// We cannot skip orbit start tag because the corresponding orbit end tag is
// hoisted out of loop (by construction) and is, in fact, non-orbit.
static bool redundant(size_t t, const std::vector<Tag> &tags) {
	return (t % 2 == 0) != orbit(tags[t]);
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
 * and can be parsed in different ways. Which parse to choose depends on the
 * disambiguation policy. RE2C supports two policies: leftmost greedy and
 * POSIX.
 *
 * We use Goldber-Radzik algorithm to find the "shortest path".
 * Both disambiguation policies forbid epsilon-cycles with negative weight.
 */

static void enqueue(clos_t x, std::stack<nfa_state_t*> &bstack, closure_t &done,
	closure_t *shadow, Tagpool &tagpool, const std::vector<Tag> &tags)
{
	nfa_state_t *n = x.state;
	uint32_t &i = n->clos;

	if (i == NOCLOS) {
		i = static_cast<uint32_t>(done.size());
		done.push_back(x);
	} else if (better(done[i], x, tagpool, tags)) {
		if (shadow) shadow->push_back(done[i]);
		done[i] = x;
	} else {
		if (shadow) shadow->push_back(x);
		return;
	}

	if (n->status != GOR_TOPSORT) {
		bstack.push(n);
		n->status = GOR_NEWPASS;
	}
}

static void scan(nfa_state_t *n, std::stack<nfa_state_t*> &bstack, closure_t &done,
	closure_t *shadow, Tagpool &tagpool, const std::vector<Tag> &tags)
{
	tagtree_t &history = tagpool.history;
	clos_t x = done[n->clos];
	switch (n->type) {
		default: break;
		case nfa_state_t::NIL:
			x.state = n->nil.out;
			enqueue(x, bstack, done, shadow, tagpool, tags);
			break;
		case nfa_state_t::ALT: {
			hidx_t idx = x.index;
			x.state = n->alt.out2;
			x.index = history.push(idx, Tag::RIGHTMOST, 0);
			enqueue(x, bstack, done, shadow, tagpool, tags);
			x.state = n->alt.out1;
			x.index = history.push(idx, Tag::RIGHTMOST, 1);
			enqueue(x, bstack, done, shadow, tagpool, tags);
			break;
		}
		case nfa_state_t::TAG:
			x.state = n->tag.out;
			x.tlook = history.push(x.tlook, n->tag.info,
				n->tag.bottom ? TAGVER_BOTTOM : TAGVER_CURSOR);
			enqueue(x, bstack, done, shadow, tagpool, tags);
			break;
	}
}

void raw_closure(const closure_t &init, closure_t &done, closure_t *shadow,
	Tagpool &tagpool, const std::vector<Tag> &tags, std::valarray<Rule> &rules)
{
	std::stack<nfa_state_t*>
		&astack = tagpool.astack,
		&bstack = tagpool.bstack;

	// enqueue all initial states
	done.clear();
	if (shadow) shadow->clear();
	for (cclositer_t c = init.begin(); c != init.end(); ++c) {
		enqueue(*c, bstack, done, shadow, tagpool, tags);
	}

	// Gordberg-Radzik 'shortest path' algorithm.
	// Papers: 1993, "A heuristic improvement of the Bellman-Ford
	// algorithm" by Goldberg, Radzik and 1996, Shortest paths algorithms:
	// Theory andexperimental evaluation" by Cherkassky, Goldberg, Radzik.
	// Complexity for digraph G=(V,E) is O(|V|*|E|).
	for (; !bstack.empty(); ) {

		// 1st step: find admissible subgraph reachable from B-stack
		// and topologically sort it (this can be done by a single
		// depth-first search that scans each state and pushes traversed
		// states to A-stack in postorder)
		for (; !bstack.empty(); ) {
			nfa_state_t *n = bstack.top();
			if (n->status == GOR_NEWPASS) {
				n->status = GOR_TOPSORT;
				scan(n, bstack, done, shadow, tagpool, tags);
			} else if (n->status == GOR_TOPSORT) {
				bstack.pop();
				astack.push(n);
			} else { // GOR_OFFSTACK
				bstack.pop();
			}
		}

		// 2nd step: scan topologically ordered states from A-stack
		// and push head states of relaxed transitions to B-stack
		for (; !astack.empty(); ) {
			nfa_state_t *n = astack.top();
			astack.pop();
			scan(n, bstack, done, shadow, tagpool, tags);
			n->status = GOR_OFFSTACK;
		}
	}

	clositer_t b = done.begin(), e = done.end(), i, j;

	// reset associated closure items and check status
	// (do this before removing any states from closure)
	for (i = b; i != e; ++i) {
		i->state->clos = NOCLOS;
		assert(i->state->status == GOR_OFFSTACK);
	}

	// drop "inner" states (non-final without outgoing non-epsilon transitions)
	j = std::partition(b, e, clos_t::ran);
	e = std::partition(j, e, clos_t::fin);
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

	done.resize(n);
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
	if (tagpool.ntags == 0
		|| (c1.order == c2.order
		&& c1.tlook == c2.tlook
		&& c1.index == c2.index)) return false;

	if (!tagpool.opts->posix_captures) {
		const int32_t cmp = cmp_leftmost(c1, c2, tagpool);
		if (cmp < 0) return false;
		if (cmp > 0) return true;
		return false;
	} else {
		tagtree_t &h = tagpool.history;
		for (size_t t = 0; t < tagpool.ntags; ++t) {
			if (redundant(t, tags)) continue;
			const hidx_t i1 = c1.tlook, i2 = c2.tlook;
			const tagver_t
				o1 = tagpool[c1.order][t],
				o2 = tagpool[c2.order][t];
			const int32_t cmp = h.compare_histories(i1, i2, o1, o2, t, orbit(tags[t]));
			if (cmp < 0) return false;
			if (cmp > 0) return true;
		}
		return false;
	}
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
				v = history(tags[t]) ? v0 : TAGVER_ZERO;
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

/* note [POSIX orbit tags]
 *
 * POSIX disambiguation rules demand that earlier subexpressions match
 * the longest possible prefix of the input string (without violating the
 * whole match). To accommodate these rules, we resolve conflicts on orbit
 * tags by comparison of tag subhistories on conflicting NFA paths.
 *
 * If one subhistory is a proper prefix of another subhistory, it is less;
 * otherwise for the first pair of different offsets, if one offset is greater
 * than the other, then the corresponding subhistory is less.
 *
 * It is possible to pre-compare two NFA paths corresponding to the same
 * input string prefix and ending in the same NFA state; if paths are not
 * equal, the result of this comparison will hold for any common suffix.
 *
 * It is also possible to pre-compare NFA paths that correspond to the same
 * input prefix, but end in different NFA states. Such comparison is incorrect
 * unless subhistories start at the same offset; but if it is incorrect, we
 * will never use its result (tags with higher priority will also disagree).
 *
 * Therefore instead of keeping the whole history of offsets we calculate
 * the relative order of any pair of subhistories on each step.
 *
 * This part of the algorithm was invented by Christopher Kuklewicz.
 */

struct cmp_posix_t
{
	Tagpool &tagpool;
	size_t tag;
	bool orbit;
	bool operator()(cclositer_t x, cclositer_t y)
	{
		const hidx_t i1 = x->tlook, i2 = y->tlook;
		const tagver_t
			o1 = tagpool[x->order][tag],
			o2 = tagpool[y->order][tag];
		// comparison result is inverted, because orders are used as offsets
		return tagpool.history.compare_last_subhistories(i1, i2, o1, o2, tag, orbit) > 0;
	}
};

struct cmp_leftmost_t
{
	Tagpool &tagpool;
	bool operator()(cclositer_t x, cclositer_t y)
		{ return cmp_leftmost(*x, *y, tagpool) < 0; }
};

template<typename cmp_t>
static void assign_orders(cclositer_t *xs, cclositer_t *xe, tagver_t *os, cmp_t &cmp)
{
	std::sort(xs, xe, cmp);
	tagver_t o = 0;
	for (cclositer_t *x = xs; x < xe; ++o) {
		*os++ = o;
		for (; ++x < xe && !cmp(x[-1], x[0]);) *os++ = o;
	}
}

void orders(closure_t &clos, Tagpool &tagpool, const std::vector<Tag> &tags)
{
	clositer_t b = clos.begin(), e = clos.end(), c;
	const size_t
		ntag = tagpool.ntags,
		nclos = clos.size();
	size_t &maxclos = tagpool.maxclos;
	tagver_t *&os = tagpool.orders, *o, *os0;
	cclositer_t *&ps = tagpool.closes, *pe;

	if (ntag == 0) return;

	// reallocate buffers if necessary
	if (maxclos < nclos) {
		maxclos = nclos * 2; // in advance
		delete[] os;
		delete[] ps;
		os = new tagver_t[(ntag + 1) * maxclos];
		ps = new cclositer_t[maxclos];
	}

	os0 = os + ntag * maxclos;
	pe = ps;
	for (c = b; c != e; ++c) *pe++ = c;

	memset(os, 0, ntag * nclos * sizeof(tagver_t));
	if (!tagpool.opts->posix_captures) {
		cmp_leftmost_t cmp = {tagpool};
		assign_orders(ps, pe, os0, cmp);
		o = os;
		for (c = b; c != e; ++c, o += ntag) {
			o[0] = os0[std::find(ps, pe, c) - ps];
		}
	} else {
		for (size_t t = 0; t < ntag; ++t) {
			if (redundant(t, tags)) continue;
			cmp_posix_t cmp = {tagpool, t, orbit(tags[t])};
			assign_orders(ps, pe, os0, cmp);
			o = os;
			for (c = b; c != e; ++c, o += ntag) {
				o[t] = os0[std::find(ps, pe, c) - ps];
			}
		}
	}

	o = os;
	for (c = b; c != e; ++c, o += ntag) {
		c->order = tagpool.insert(o);
	}
}

} // namespace re2c
