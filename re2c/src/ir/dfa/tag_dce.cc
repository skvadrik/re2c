#include "src/ir/dfa/tag_optimize.h"

namespace re2c
{

/* Dead code elimination */
void tag_dce(dfa_t &dfa, const bool *live)
{
	const size_t
		nsym = dfa.nchars,
		narc = dfa.states.size() * nsym,
		nver = static_cast<size_t>(dfa.maxtagver) + 1;

	for (size_t a = 0; a < narc; ++a) {
		tagcmd_t &cmd = dfa.states[a / nsym]->tags[a % nsym];
		const bool *liv = &live[a * nver];

		for (tagsave_t *s, **ps = &cmd.save; (s = *ps);) {
			if (!liv[s->ver]) {
				*ps = s->next;
			} else {
				ps = &s->next;
			}
		}

		// rule tags and copy tags can't be dead by construction
		// (copy tags are only used for fallback tags)
	}
}

} // namespace re2c

