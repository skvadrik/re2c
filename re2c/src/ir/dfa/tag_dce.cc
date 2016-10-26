#include "src/ir/dfa/tag_optimize.h"

namespace re2c
{

/* Dead code elimination */
void tag_dce(dfa_t &dfa, const bool *live)
{
	const size_t
		nsym = dfa.nchars,
		narc = dfa.states.size() * nsym,
		ntag = dfa.tags.size(),
		nver = static_cast<size_t>(dfa.maxtagver) + 1;

	for (size_t a = 0; a < narc; ++a) {
		const size_t
			c = a % nsym,
			i = a / nsym;
		const dfa_state_t *s = dfa.states[i];
		// rule tags and copy tags can't be dead by construction
		// (copy tags are only used for fallback tags)

		size_t *p = &s->tags[c].set;
		if (*p != ZERO_TAGS) {
			const bool *liv = &live[a * nver];
			const tagver_t *set = dfa.tagpool[*p];
			tagver_t *set_liv = dfa.tagpool.buffer1;
			for (size_t t = 0; t < ntag; ++t) {
				const tagver_t v = set[t];
				set_liv[t] = v != TAGVER_ZERO && liv[v]
					? v : TAGVER_ZERO;
			}
			*p = dfa.tagpool.insert(set_liv);
		}
	}
}

} // namespace re2c

