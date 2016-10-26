#include <string.h>

#include "src/ir/dfa/tag_optimize.h"

namespace re2c
{

static void forwprop(const dfa_t &dfa, bool *been, size_t state, bool *live, const bool *need);

void tag_liveness(const dfa_t &dfa, bool *live)
{
	const size_t
		nstate = dfa.states.size(),
		nsym = dfa.nchars,
		narc = nstate * nsym,
		ntag = dfa.tags.size(),
		nver = static_cast<size_t>(dfa.maxtagver) + 1;
	bool *buf1 = new bool[nver];
	bool *buf2 = new bool[nver];
	bool *been = new bool[nstate];

	/* note [control flow equations for tag liveness]
	 *
	 * Tag liveness in basic block x is given by control-flow equations:
	 *
	 *     need-out(x) = use(x) + need-in(y), for all y successors of x
	 *     need-in(x) = need-out(x) - define(x)
	 *
	 * Equations are solved by iteration until fix point.
	 * Basic blocks are arcs. Successors of arc s1 -> s2 are:
	 *     - all outgoing arcs from state s2
	 *     - if state s2 is final, corresponding rule action
	 */
	memset(live, 0, narc * nver * sizeof(bool));
	for (bool loop = true; loop;) {
		loop = false;

		for (size_t a = 0; a < narc; ++a) {
			const size_t i = dfa.states[a / nsym]->arcs[a % nsym];
			if (i == dfa_t::NIL) continue;
			const dfa_state_t *s = dfa.states[i];

			memset(buf1, 0, nver * sizeof(bool));

			if (s->rule != Rule::NONE) {
				const tagver_t
					*use = dfa.tagpool[dfa.rules[s->rule].tags],
					*def = dfa.tagpool[s->rule_tags.set];
				for (size_t t = 0; t < ntag; ++t) {
					const tagver_t u = use[t], d = def[t];
					if (u != TAGVER_ZERO && d == TAGVER_ZERO) {
						buf1[u] = true;
					}
				}
			}

			for (size_t c = 0; c < nsym; ++c) {
				const bool *use = &live[(i * nsym + c) * nver];
				unpack(nver, buf2, ntag, dfa.tagpool[s->tags[c].set]);
				for (size_t v = 0; v < nver; ++v) {
					buf1[v] |= use[v] && !buf2[v];
				}
				// copy tags are only used for fallback tags,
			}

			bool *liv = &live[a * nver];
			if (memcmp(liv, buf1, nver * sizeof(bool)) != 0) {
				memcpy(liv, buf1, nver * sizeof(bool));
				loop = true;
			}
		}
	}

	/* note [fallback tag liveness]
	 *
	 * Liveness of fallback tag is propagated forward from fallback
	 * state (see note [fallback states]) and until there remain
	 * any fallthrough paths from current state.
	 *
	 * Fallback version of tag is either backup copy of tag's final
	 * version, or (if there's no backup) the final version itself.
	 * Absence of backup means that final version is not overwritten,
	 * but still we should prevent it from merging with other tags
	 * (otherwise it may become overwritten).
	 */
	for (size_t i = 0; i < nstate; ++i) {
		const dfa_state_t *s = dfa.states[i];
		if (!s->fallback) continue;

		const tagver_t
			*use = dfa.tagpool[dfa.rules[s->rule].tags],
			*def = dfa.tagpool[s->rule_tags.set];

		memset(buf1, 0, nver * sizeof(bool));
		for (size_t t = 0; t < ntag; ++t) {
			const tagver_t u = use[t], d = def[t];
			if (u != TAGVER_ZERO && d == TAGVER_ZERO) {
				buf1[u] = true;
			}
		}
		for (const tagcopy_t *p = s->rule_tags.copy; p; p = p->next) {
			// in rule tags copies are swapped:
			// LHS is the origin, RHS is backup
			buf1[p->lhs] = false;
			buf1[p->rhs] = true;
		}

		memset(been, 0, nstate * sizeof(bool));
		forwprop(dfa, been, i, live, buf1);
	}

	delete[] buf1;
	delete[] buf2;
	delete[] been;
}

void forwprop(const dfa_t &dfa, bool *been, size_t state, bool *live,
	const bool *need)
{
	if (been[state]) return;
	been[state] = true;

	const size_t
		nsym = dfa.nchars,
		nver = static_cast<size_t>(dfa.maxtagver) + 1;
	const dfa_state_t *s = dfa.states[state];

	for (size_t c = 0; c < nsym; ++c) {
		const size_t dest = s->arcs[c];
		if (dest != dfa_t::NIL && dfa.states[dest]->fallthru) {
			bool *l = &live[(state * nsym + c) * nver];
			for (size_t v = 0; v < nver; ++v) {
				l[v] |= need[v];
			}
			forwprop(dfa, been, dest, live, need);
		}
	}
}

} // namespace re2c

