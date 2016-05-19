#include "src/ir/dfa/dfa.h"

namespace re2c
{

/* note [fallback states]
 *
 * Check if the given state is accepting, but may be shadowed
 * by other accepting states: when the short rule matches,
 * lexer must try to match longer rules; if this attempt is
 * unsuccessful it must fallback to the short match.
 */
bool fallback_state(const dfa_t &dfa, size_t i)
{
	dfa_state_t *s = dfa.states[i];

	if (s->rule == Rule::NONE) {
		return false;
	}

	for (size_t c = 0; c < dfa.nchars; ++c) {
		const size_t j = s->arcs[c];
		if (j != dfa_t::NIL
			&& dfa.states[j]->rule == Rule::NONE) {
			return true;
		}
	}

	return false;
}

} // namespace re2c

