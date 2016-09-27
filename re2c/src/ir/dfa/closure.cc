#include <string.h>

#include "src/ir/dfa/closure.h"
#include "src/ir/nfa/nfa.h"

namespace re2c
{

static void closure_one(closure_t &clos, nfa_state_t *n, bool *tags, bool *badtags, size_t ntags);
static void merge_tags(bool *oldtags, const bool *newtags, bool *badtags, size_t ntags);

void closure(const closure_t &clos1, closure_t &clos2, bool *tags, bool *badtags, size_t ntags)
{
	clos2.clear();
	for (cclositer_t c = clos1.begin(); c != clos1.end(); ++c) {
		closure_one(clos2, c->state, tags, badtags, ntags);
	}
}

void merge_tags(bool *oldtags, const bool *newtags,
	bool *badtags, size_t ntags)
{
	for (size_t i = 0; i < ntags; ++i) {
		badtags[i] |= oldtags[i] ^ newtags[i];
		oldtags[i] |= newtags[i];
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
void closure_one(closure_t &clos, nfa_state_t *n, bool *tags, bool *badtags, size_t ntags)
{
	// trace the first iteration of each loop:
	// epsilon-loops may add ney tags and reveal conflicts
	if (n->loop > 1) {
		return;
	}

	++n->loop;
	switch (n->type) {
		case nfa_state_t::ALT:
			closure_one(clos, n->alt.out1, tags, badtags, ntags);
			closure_one(clos, n->alt.out2, tags, badtags, ntags);
			break;
		case nfa_state_t::TAG: {
			const size_t t = n->tag.info;
			const bool old = tags[t];
			tags[t] = true;
			closure_one(clos, n->tag.out, tags, badtags, ntags);
			tags[t] = old;
			break;
		}
		case nfa_state_t::RAN:
		case nfa_state_t::FIN: {
			clositer_t
				c = clos.begin(),
				e = clos.end();
			for (; c != e && c->state != n; ++c);
			if (c == e) {
				bool *tagptr = new bool[ntags];
				memcpy(tagptr, tags, ntags * sizeof(bool));
				clos.push_back(clos_t(n, tagptr));
			} else {
				// it is impossible to reach the same NFA state from
				// different rules, so no need to mess with masks here
				merge_tags(c->tagptr, tags, badtags, ntags);
			}
			break;
		}
	}
	--n->loop;
}

} // namespace re2c
