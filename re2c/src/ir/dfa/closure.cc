#include <string.h>

#include "src/ir/dfa/closure.h"
#include "src/ir/nfa/nfa.h"

namespace re2c
{

static void closure_one(closure_t &clos, Tagpool &tagpool, nfa_state_t *n, bool *tags, bool *badtags);
static void check_tags(const Tagpool &tagpool, size_t oldidx, size_t newidx, bool *badtags);

void closure(const closure_t &clos1, closure_t &clos2,
	Tagpool &tagpool, bool *tags, bool *badtags)
{
	clos2.clear();
	for (cclositer_t c = clos1.begin(); c != clos1.end(); ++c) {
		closure_one(clos2, tagpool, c->state, tags, badtags);
	}
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

} // namespace re2c
