#include <algorithm>

#include "src/ir/dfa/closure.h"
#include "src/ir/nfa/nfa.h"

namespace re2c
{

static void closure_one(closure_t &clos, Tagpool &tagpool, clos_t &c0, nfa_state_t *n, tagver_t *tags, closure_t *shadow);
bool is_better(const clos_t &c1, const clos_t &c2, Tagpool &tagpool);
static bool compare_by_rule(const clos_t &c1, const clos_t &c2);
static void prune_final_items(closure_t &clos, std::valarray<Rule> &rules);
static void update_versions(closure_t &clos, Tagpool &tagpool, tagver_t &maxver, tagver_t *newvers);

void closure(closure_t &clos1, closure_t &clos2, Tagpool &tagpool,
	std::valarray<Rule> &rules, tagver_t &maxver, tagver_t *newvers,
	bool lookahead, closure_t *shadow)
{
	// build tagged epsilon-closure of the given set of NFA states
	clos2.clear();
	if (shadow) shadow->clear();
	tagver_t *tags = tagpool.buffer1;
	std::fill(tags, tags + tagpool.ntags, TAGVER_ZERO);
	for (clositer_t c = clos1.begin(); c != clos1.end(); ++c) {
		closure_one(clos2, tagpool, *c, c->state, tags, shadow);
	}

	// The only difference between TDFA and LATDFA is here:
	// TDFA backups tags after current transition, while LATDFA delays this
	// till the next transition. This allows LATDFA to use lookahead symbol
	// and backup tags only in case of matching lookahead, while TDFA cannot
	// exploit lookahead and has to backup tags anyway.
	if (!lookahead) {
		for (clositer_t c = clos2.begin(); c != clos2.end(); ++c) {
			c->ttran = c->tlook;
			c->tlook = ZERO_TAGS;
		}
	}

	// see note [at most one final item per closure]
	prune_final_items(clos2, rules);

	// sort closure, group items by rule
	std::sort(clos2.begin(), clos2.end(), compare_by_rule);

	// merge tags from different rules, find nondeterministic tags
	update_versions(clos2, tagpool, maxver, newvers);
}

/* note [epsilon-closures in tagged NFA]
 *
 * DFA state is a set of NFA states.
 * However, DFA state includes not all NFA states that are in
 * epsilon-closure (NFA states that have only epsilon-transitions
 * and are not final states are omitted).
 * The included states are called 'kernel' states.
 *
 * For tagged NFA we have to trace all epsilon-paths to each
 * kernel state, accumulate tags along the way and compare
 * resulting tag sets: if they differ, then NFA is tagwise
 * ambiguous. All tags are merged together; ambiguity is reported.
 */
void closure_one(closure_t &clos, Tagpool &tagpool, clos_t &c0,
	nfa_state_t *n, tagver_t *tags, closure_t *shadow)
{
	// trace the first iteration of each loop:
	// epsilon-loops may add ney tags and reveal conflicts
	if (n->loop > 1) {
		return;
	}

	++n->loop;
	switch (n->type) {
		case nfa_state_t::NIL:
			closure_one(clos, tagpool, c0, n->nil.out, tags, shadow);
			break;
		case nfa_state_t::ALT:
			closure_one(clos, tagpool, c0, n->alt.out1, tags, shadow);
			closure_one(clos, tagpool, c0, n->alt.out2, tags, shadow);
			break;
		case nfa_state_t::TAG: {
			const size_t t = n->tag.info;
			const tagver_t old = tags[t];
			tags[t] = n->tag.bottom ? TAGVER_BOTTOM : TAGVER_CURSOR;
			closure_one(clos, tagpool, c0, n->tag.out, tags, shadow);
			tags[t] = old;
			break;
		}
		case nfa_state_t::RAN:
		case nfa_state_t::FIN: {
			c0.state = n;
			c0.tlook = tagpool.insert(tags);
			clositer_t
				c = clos.begin(),
				e = clos.end();
			for (; c != e && c->state != n; ++c);
			if (c == e) {
				clos.push_back(c0);
			} else {
				if (shadow) shadow->push_back(*c);
				if (is_better(*c, c0, tagpool)) *c = c0;
			}
			break;
		}
	}
	--n->loop;
}

/*
 * Compare conflicting configurations and choose one of them,
 * don't merge: merging only makes sense for tags from different
 * rules, and it is impossible to reach the same NFA state from
 * different rules (hence no need to mess with masks here).
 */
bool is_better(const clos_t &c1, const clos_t &c2, Tagpool &tagpool)
{
	if (c1.tlook == c2.tlook
		&& c1.ttran == c2.ttran
		&& c1.tvers == c2.tvers) return false;

	const tagver_t
		*l1 = tagpool[c1.tlook], *l2 = tagpool[c2.tlook],
		*t1 = tagpool[c1.ttran], *t2 = tagpool[c2.ttran],
		*v1 = tagpool[c1.tvers], *v2 = tagpool[c2.tvers];
	tagver_t x, y;

	// compare configurations tag by tag
	// (tags with greater numbers have lower priority)
	for (size_t t = tagpool.ntags; t --> 0;) {

		// lookahead tags gathered by epsilon-closure
		x = l1[t]; y = l2[t];
		if (x > y) return false;
		if (x < y) return true;

		// tags set on transition that is being constructed
		x = t1[t]; y = t2[t];
		if (x > y) return false;
		if (x < y) return true;

		// tag versions before the constructed transition
		x = v1[t]; y = v2[t];
		if (x > y) return false;
		if (x < y) return true;
	}

	return false;
}

// The first comparison criterion is rule.
// The second criterion is destination NFA state:
// by construction all closure items have different state,
// thus comaprison on state yields strict total ordering.
bool compare_by_rule(const clos_t &c1, const clos_t &c2)
{
	const nfa_state_t
		*s1 = c1.state,
		*s2 = c2.state;
	const size_t
		r1 = s1->rule,
		r2 = s2->rule;

	if (r1 < r2) return true;
	if (r1 > r2) return false;
	if (s1 < s2) return true;
	if (s1 > s2) return false;

	// each closure item has unique state
	assert(c1.origin == c2.origin
		&& c1.tvers == c2.tvers
		&& c1.ttran == c2.ttran
		&& c1.tlook == c2.tlook);
	return false;
}

/* note [at most one final item per closure]
 *
 * By construction NFA has exactly one final state per rule.
 * Thus closure has at most one final item per rule (in other
 * words, all final items in closure belong to different rules).
 * The rule with the highest priority shadowes all other rules.
 * Final items that correspond to shadowed rules are useless
 * and should be removed as early as possible.
 *
 * If we let such items remain in closure, they may prevent the
 * new DFA state from being merged with other states. But this
 * won't affect the resulting program: meaningless finalizing tags
 * will be removed by dead code elimination and after that DFA
 * minimization will merge equivalent final states.
 *
 * But it is much easier and cleaner to remove useless items
 * immediately (and thas't what we do).
 */
void prune_final_items(closure_t &clos, std::valarray<Rule> &rules)
{
	clositer_t
		b = clos.begin(),
		e = clos.end(),
		f = std::partition(b, e, clos_t::not_fin);
	if (f != e) {
		std::partial_sort(f, f, e, compare_by_rule);
		// mark all rules except the first one as shadowed
		const uint32_t line = rules[f->state->rule].code->fline;
		for (cclositer_t c = f + 1; c != e; ++c) {
			rules[c->state->rule].shadow.insert(line);
		}
		// remove shadowed final items from closure
		clos.resize(static_cast<size_t>(f - b) + 1);
	}
}

void update_versions(closure_t &clos, Tagpool &tagpool,
	tagver_t &maxver, tagver_t *newvers)
{
	const size_t ntag = tagpool.ntags;
	tagver_t *cur = tagpool.buffer1,
		*bot = tagpool.buffer2,
		*ver = tagpool.buffer3;
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
			if (tagpool[c->ttran][t] == TAGVER_CURSOR) {
				if (newcur == TAGVER_ZERO) {
					newcur = ++maxver;
				}
				cur[t] = newcur;
				break;
			}
		}

		for (c = b; c != e; ++c) {
			if (tagpool[c->ttran][t] == TAGVER_BOTTOM) {
				if (newbot == TAGVER_ZERO) {
					newbot = -(++maxver);
				}
				bot[t] = newbot;
				break;
			}
		}
	}

	// apply transition tags to tag versions
	for (c = b; c != e; ++c) {
		if (c->ttran == ZERO_TAGS) continue;

		const tagver_t
			*tran = tagpool[c->ttran],
			*ver0 = tagpool[c->tvers];

		for (size_t t = 0; t < ntag; ++t) {
			switch(tran[t]) {
				case TAGVER_ZERO:   ver[t] = ver0[t]; break;
				case TAGVER_CURSOR: ver[t] = cur[t]; break;
				case TAGVER_BOTTOM: ver[t] = bot[t]; break;
			}
		}

		c->tvers = tagpool.insert(ver);
	}
}

} // namespace re2c
