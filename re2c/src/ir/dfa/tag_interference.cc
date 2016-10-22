#include <string.h>

#include "src/ir/dfa/tag_optimize.h"

namespace re2c
{

static void interfere(bool *interf, size_t nver, const bool *live, const bool *tags);

void tag_interference(const dfa_t &dfa, const bool *live, bool *interf)
{
	const size_t
		nstate = dfa.states.size(),
		ntag = dfa.tags.size(),
		nver = ntag + 1,
		nsym = dfa.nchars;
	bool *buf1 = new bool[nver];
	bool *buf2 = new bool[nver];

	memset(interf, 0, nver * nver * sizeof(bool));
	for (size_t i = 0; i < nstate; ++i) {
		const dfa_state_t *s = dfa.states[i];

		if (s->rule != Rule::NONE) {
			unpack(nver, buf1, ntag, dfa.tagpool[dfa.rules[s->rule].tags]);
			unpack(nver, buf2, ntag, dfa.tagpool[s->rule_tags.set]);
			interfere(interf, nver, buf1, buf2);
		}

		for (size_t c = 0; c < nsym; ++c) {
			const size_t x = s->tags[c].set;
			if (x != ZERO_TAGS) {
				const bool *liv = &live[(i * nsym + c) * nver];
				unpack(nver, buf1, ntag, dfa.tagpool[x]);
				interfere(interf, nver, liv, buf1);
			}
		}
	}

	delete[] buf1;
	delete[] buf2;
}

// tags that are updated here are pairwise incompatible
// with all tags that are alive, but not updated here
void interfere(bool *interf, size_t nver, const bool *live, const bool *tags)
{
	for (size_t i = 0; i < nver; ++i) {
		if (live[i] && !tags[i]) {
			for (size_t j = 0; j < nver; ++j) {
				if (tags[j]) {
					interf[i * nver + j] = interf[j * nver + i] = true;
				}
			}
		}
	}
}

} // namespace re2c

