#include <algorithm>

#include "src/ir/dfa/closure.h"
#include "src/ir/nfa/nfa.h"

namespace re2c
{

static void closure_one(closure_t &clos, Tagpool &tagpool, nfa_state_t *n, bool *tags, bool *badtags);
static void check_tags(const Tagpool &tagpool, size_t oldidx, size_t newidx, bool *badtags);
static bool compare_by_rule(const clos_t &c1, const clos_t &c2);
static void prune_final_items(closure_t &clos, std::valarray<Rule> &rules);

void closure(const closure_t &clos1, closure_t &clos2,
	Tagpool &tagpool, std::valarray<Rule> &rules,
	bool *tags, bool *badtags)
{
	clos2.clear();
	for (cclositer_t c = clos1.begin(); c != clos1.end(); ++c) {
		closure_one(clos2, tagpool, c->state, tags, badtags);
	}

	prune_final_items(clos2, rules);

	// sort closure: we need this to compare closures by hash
	std::sort(clos2.begin(), clos2.end(), compare_by_rule);
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
void closure_one(closure_t &clos, Tagpool &tagpool,
	nfa_state_t *n, bool *tags, bool *badtags)
{
	// trace the first iteration of each loop:
	// epsilon-loops may add ney tags and reveal conflicts
	if (n->loop > 1) {
		return;
	}

	++n->loop;
	switch (n->type) {
		case nfa_state_t::ALT:
			closure_one(clos, tagpool, n->alt.out1, tags, badtags);
			closure_one(clos, tagpool, n->alt.out2, tags, badtags);
			break;
		case nfa_state_t::TAG: {
			const size_t t = n->tag.info;
			const bool old = tags[t];
			tags[t] = true;
			closure_one(clos, tagpool, n->tag.out, tags, badtags);
			tags[t] = old;
			break;
		}
		case nfa_state_t::RAN:
		case nfa_state_t::FIN: {
			const size_t tagidx = tagpool.insert(tags);
			clositer_t
				c = clos.begin(),
				e = clos.end();
			for (; c != e && c->state != n; ++c);
			if (c == e) {
				clos.push_back(clos_t(n, tagidx));
			} else {
				check_tags(tagpool, c->tagidx, tagidx, badtags);
			}
			break;
		}
	}
	--n->loop;
}

/*
 * Check configurations for possible conflicts.
 * In case of conflict choose random configuration (e.g. the first one)
 * and don't merge: merging only makes sense for tags from different
 * rules, and it is impossible to reach the same NFA state from different
 * rules (hence no need to mess with masks here).
 */
void check_tags(const Tagpool &tagpool, size_t oldidx, size_t newidx, bool *badtags)
{
	const bool
		*oldtags = tagpool[oldidx],
		*newtags = tagpool[newidx];
	for (size_t i = 0; i < tagpool.ntags; ++i) {
		badtags[i] |= oldtags[i] ^ newtags[i];
	}
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
	assert(c1.tagidx == c2.tagidx);
	return false;
}

/* node [at most one final item per closure]
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
		f = std::partition(b, e, clos_t::not_final);
	if (f != e) {
		std::partial_sort(f, f, e, compare_by_rule);
		// mark all rules except the first one as shadowed
		const uint32_t line = rules[f->state->rule].info->loc.line;
		for (cclositer_t c = f + 1; c != e; ++c) {
			rules[c->state->rule].shadow.insert(line);
		}
		// remove shadowed final items from closure
		clos.resize(static_cast<size_t>(f - b) + 1);
	}
}

} // namespace re2c
