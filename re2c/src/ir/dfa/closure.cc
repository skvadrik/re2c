#include <string.h>

#include "src/ir/dfa/closure.h"
#include "src/ir/nfa/nfa.h"

namespace re2c
{

static void merge_tags(bool *oldtags, const bool *newtags, bool *badtags, size_t ntags);

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
void closure(kitem_t *const kernel, kitem_t *&kend,
	nfa_state_t *n, bool *tags, bool *badtags, size_t ntags)
{
	// trace the first iteration of each loop:
	// epsilon-loops may add ney tags and reveal conflicts
	if (n->loop > 1) {
		return;
	}

	++n->loop;
	switch (n->type) {
		case nfa_state_t::ALT:
			closure(kernel, kend, n->alt.out1, tags, badtags, ntags);
			closure(kernel, kend, n->alt.out2, tags, badtags, ntags);
			break;
		case nfa_state_t::TAG: {
			const size_t t = n->tag.info;
			const bool old = tags[t];
			tags[t] = true;
			closure(kernel, kend, n->tag.out, tags, badtags, ntags);
			tags[t] = old;
			break;
		}
		case nfa_state_t::RAN:
		case nfa_state_t::FIN: {
			kitem_t *k = kernel;
			while (k != kend && k->state != n) ++k;
			if (k == kend) {
				kend->state = n;
				kend->tagptr = new bool[ntags];
				memcpy(kend->tagptr, tags, ntags * sizeof(bool));
				++kend;
			} else {
				// it is impossible to reach the same NFA state from
				// different rules, so no need to mess with masks here
				merge_tags(k->tagptr, tags, badtags, ntags);
			}
			break;
		}
	}
	--n->loop;
}

} // namespace re2c
