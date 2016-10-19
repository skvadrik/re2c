#include "src/ir/dfa/dfa.h"

namespace re2c
{

static void find_overwritten_tags(const dfa_t &dfa, size_t state, bool *been, bool *owrt);

/* note [fallback tags]
 *
 * We need to backup tags in fallback states: these tags may be
 * updated on some non-accepting path from fallback state, and if
 * the attempt to match longer rule fails, there's no way to restore
 * the overwritten tags.
 *
 * Two different things may cause overwrites:
 *   - self-overlapping rules
 *   - overlapping rules which tags have been merged by deduplication
 *
 * We can prevent deduplication from merging such tags by propagating
 * their liveness on all non-accepting paths from fallback state.
 *
 * Handling self-overlapping rules is not so easy: damage is done by
 * DFA construction, which knows nothing about fallbacks. We have to
 * manually create one backup tag for each potentially overwritten
 * tag and add backup/restore instructions: transitions from fallback
 * state must backup tag, transitions from 'yyaccept' state must
 * restore it.
 *
 * We take special care not to create redundant backups (trace all
 * non-accepting paths from the given fallback state to find which
 * tags are potentially overwritten). In theory, deduplication
 * could remove redundant backups, but in practice such tags cause
 * artifical interference and confuse coloring heuristic.
 */

void find_overwritten_tags(const dfa_t &dfa, size_t state,
	bool *been, bool *owrt)
{
	if (been[state]) return;
	been[state] = true;

	const dfa_state_t *s = dfa.states[state];
	const size_t ntags = dfa.tags.size();

	for (size_t c = 0; c < dfa.nchars; ++c) {
		const bool *tags = dfa.tagpool[s->tags[c].set];
		for (size_t t = 0; t < ntags; ++t) {
			owrt[t] |= tags[t];
		}

		size_t dest = s->arcs[c];
		if (dest != dfa_t::NIL && dfa.states[dest]->fallthru) {
			find_overwritten_tags(dfa, dest, been, owrt);
		}
	}
}

// WARNING: this function assumes that falthrough and fallback
// attributes of DFA states have already been calculated, see
// note [fallback states]
void insert_fallback_tags(dfa_t &dfa)
{
	const size_t
		nstates = dfa.states.size(),
		ntags = dfa.tags.size();
	bool *been = new bool[nstates];
	bool *total = dfa.tagpool.buffer2;
	std::fill(total, total + ntags, false);

	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];

		if (!s->fallback) continue;

		bool *owrt = dfa.tagpool.buffer1;
		std::fill(owrt, owrt + ntags, false);
		std::fill(been, been + nstates, false);
		find_overwritten_tags(dfa, i, been, owrt);

		const bool
			*fin = dfa.tagpool[dfa.rules[s->rule].tags],
			*upd = dfa.tagpool[s->rule_tags.set];
		for (size_t t = 0; t < ntags; ++t) {
			owrt[t] &= fin[t] && !upd[t];
			total[t] |= owrt[t];
		}
		const size_t copy = dfa.tagpool.insert(owrt);

		if (copy != ZERO_TAGS) {
			for (size_t c = 0; c < dfa.nchars; ++c) {
				size_t j = s->arcs[c];
				if (j != dfa_t::NIL && dfa.states[j]->fallthru) {
					s->tags[c].copy = copy;
				}
			}
			s->rule_tags.copy = copy;
		}
	}

	dfa.copy_tags = dfa.tagpool.insert(total);

	delete[] been;
}

} // namespace re2c
