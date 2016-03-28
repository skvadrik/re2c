#include "src/ir/dfa/dfa.h"

namespace re2c
{

/* note [fallback states]
 *
 * Find accepting states that may be shadowed by other accepting
 * states: when the short rule matches, lexer must try to match
 * longer rules; if this attempt is unsuccessful it must fallback
 * to the short match.
 */
void fallback_states(const dfa_t &dfa, std::vector<size_t> &fallback)
{
	const size_t count = dfa.states.size();
	for (size_t i = 0; i < count; ++i) {
		dfa_state_t *s = dfa.states[i];
		if (s->rule != Rule::NONE) {
			for (size_t c = 0; c < dfa.nchars; ++c) {
				const size_t j = s->arcs[c];
				if (j != dfa_t::NIL
					&& dfa.states[j]->rule == Rule::NONE) {
					fallback.push_back(i);
				}
			}
		}
	}
}

} // namespace re2c

