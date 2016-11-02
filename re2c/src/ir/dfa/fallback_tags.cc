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
	for (size_t c = 0; c < dfa.nchars; ++c) {
		for (const tagsave_t *p = s->tcmd[c].save; p; p = p->next) {
			owrt[p->ver] = true;
		}
		for (const tagcopy_t *p = s->tcmd[c].copy; p; p = p->next) {
			owrt[p->lhs] = true;
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
	tagver_t maxver = dfa.maxtagver;
	tcpool_t &pool = dfa.tcpool;
	const size_t
		nstates = dfa.states.size(),
		nsym = dfa.nchars,
		ntags = dfa.tags.size(),
		nver = static_cast<size_t>(maxver) + 1;
	bool *been = new bool[nstates];
	bool *owrt = new bool[nver];

	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];

		if (!s->fallback) continue;

		std::fill(been, been + nstates, false);
		std::fill(owrt, owrt + nver, false);
		find_overwritten_tags(dfa, i, been, owrt);

		const tagver_t *fin = dfa.rules[s->rule].tags;
		for (const tagsave_t *p = s->tcmd[nsym].save; p; p = p->next) {
			owrt[p->ver] = false;
		}

		for (size_t t = 0; t < ntags; ++t) {
			const tagver_t
				f = fin[t],
				b = static_cast<tagver_t>(nver + t);

			if (f == TAGVER_ZERO || !owrt[f]) continue;

			// patch commands (backups must go first)
			tagcopy_t **p = &s->tcmd[nsym].copy;
			*p = pool.make_copy(*p, f, b);
			for (size_t c = 0; c < nsym; ++c) {
				size_t j = s->arcs[c];
				if (j != dfa_t::NIL && dfa.states[j]->fallthru) {
					p = &s->tcmd[c].copy;
					*p = pool.make_copy(*p, b, f);
				}
			}
			maxver = std::max(maxver, b);
		}
	}

	delete[] been;
	delete[] owrt;

	dfa.maxtagver = maxver;
}

} // namespace re2c
