#include <limits>
#include <string.h>

#include "src/ir/dfa/dfa.h"

namespace re2c
{

static void forwprop(const dfa_t &dfa, bool *been, size_t state,
	bool *live, const bool *need)
{
	if (been[state]) return;
	been[state] = true;

	const size_t
		nsym = dfa.nchars,
		ntag = dfa.tags.size();
	const dfa_state_t *s = dfa.states[state];

	for (size_t c = 0; c < nsym; ++c) {
		const size_t dest = s->arcs[c];
		if (dest != dfa_t::NIL && dfa.states[dest]->fallthru) {
			bool *l = &live[(state * nsym + c) * ntag];
			for (size_t t = 0; t < ntag; ++t) {
				l[t] |= need[t];
			}
			forwprop(dfa, been, dest, live, need);
		}
	}
}

static void liveness(const dfa_t &dfa, bool *live)
{
	const size_t
		nstate = dfa.states.size(),
		nsym = dfa.nchars,
		narc = nstate * nsym,
		ntag = dfa.tags.size();
	bool *l0 = dfa.tagpool.buffer1;

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
	memset(live, 0, narc * ntag * sizeof(bool));
	for (bool loop = true; loop;) {
		loop = false;

		for (size_t a = 0; a < narc; ++a) {
			const size_t i = dfa.states[a / nsym]->arcs[a % nsym];
			if (i == dfa_t::NIL) continue;
			const dfa_state_t *s = dfa.states[i];

			bool *l = &live[a * ntag];
			memcpy(l0, l, ntag * sizeof(bool));
			memset(l, 0, ntag * sizeof(bool));

			if (s->rule != Rule::NONE) {
				const bool
					*use = dfa.tagpool[dfa.rules[s->rule].tags],
					*def = dfa.tagpool[s->rule_tags.set];
				for (size_t t = 0; t < ntag; ++t) {
					l[t] |= use[t] && !def[t];
				}
			}

			for (size_t c = 0; c < nsym; ++c) {
				const bool
					*use = &live[(i * nsym + c) * ntag],
					*def = dfa.tagpool[s->tags[c].set];
				for (size_t t = 0; t < ntag; ++t) {
					l[t] |= use[t] && !def[t];
				}
			}

			loop |= memcmp(l, l0, ntag * sizeof(bool)) != 0;
		}
	}

	/* note [fallback tag liveness]
	 *
	 * Liveness of fallback tag is propagated forward from fallback
	 * state (see note [fallback states]) and until there remain
	 * any fallthrough paths from current state.
	 */
	bool *been = new bool[nstate];
	for (size_t i = 0; i < nstate; ++i) {
		const dfa_state_t *s = dfa.states[i];
		if (s->fallback) {
			const bool
				*use = dfa.tagpool[dfa.rules[s->rule].tags],
				*def = dfa.tagpool[s->rule_tags.set];
			for (size_t t = 0; t < ntag; ++t) {
				l0[t] = use[t] && !def[t];
			}
			std::fill(been, been + nstate, false);
			forwprop(dfa, been, i, live, l0);
		}
	}
	delete[] been;
}

static void mask_dead(dfa_t &dfa, const bool *live)
{
	const size_t
		nsym = dfa.nchars,
		narc = dfa.states.size() * nsym,
		ntag = dfa.tags.size();

	for (size_t a = 0; a < narc; ++a) {
		const size_t
			c = a % nsym,
			i = a / nsym;
		const dfa_state_t *s = dfa.states[i];
		// rule tags can't be dead by construction

		size_t *p = &s->tags[c].set;
		if (*p != ZERO_TAGS) {
			const bool
				*liv = &live[a * ntag],
				*set = dfa.tagpool[*p];
			bool *set_liv = dfa.tagpool.buffer1;
			for (size_t t = 0; t < ntag; ++t) {
				set_liv[t] = set[t] && liv[t];
			}
			*p = dfa.tagpool.insert(set_liv);
		}
	}
}

// tags that are updated here are pairwise incompatible
// with all tags that are alive, but not updated here
static void interfere(bool *intrf, size_t ntag,
	const bool *live, const bool *tags)
{
	for (size_t i = 0; i < ntag; ++i) {
		if (live[i] && !tags[i]) {
			for (size_t j = 0; j < ntag; ++j) {
				if (tags[j]) {
					intrf[i * ntag + j] = intrf[j * ntag + i] = true;
				}
			}
		}
	}
}

static void interference(const dfa_t &dfa,
	const bool *live, bool *intrf)
{
	const size_t
		nstate = dfa.states.size(),
		ntag = dfa.tags.size(),
		nsym = dfa.nchars;

	memset(intrf, 0, ntag * ntag * sizeof(bool));
	for (size_t i = 0; i < nstate; ++i) {
		const dfa_state_t *s = dfa.states[i];

		if (s->rule != Rule::NONE) {
			const bool
				*liv = dfa.tagpool[dfa.rules[s->rule].tags],
				*set = dfa.tagpool[s->rule_tags.set];
			interfere(intrf, ntag, liv, set);
		}

		for (size_t c = 0; c < nsym; ++c) {
			const size_t x = s->tags[c].set;
			if (x != ZERO_TAGS) {
				const bool
					*liv = &live[(i * nsym + c) * ntag],
					*set = dfa.tagpool[x];
				interfere(intrf, ntag, liv, set);
			}
		}
	}

	// fixed tags should not participate in deduplication, so
	// each fixed tag is incompatible with all other tags
	for (size_t i = 0; i < ntag; ++i) {
		if (dfa.tags[i].type == Tag::FIX) {
			for (size_t j = 0; j < ntag; ++j) {
				intrf[i * ntag + j]
					= intrf[j * ntag + i]
					= j != i;
			}
		}
	}
}

/* We have a binary relation on the set of all tags
 * and must construct set decomposition into subsets such that
 * all tags in the same subset are equivalent.
 *
 * This problem is isomorphic to partitioning graph into cliques
 * (aka finding the 'clique cover' of a graph).
 *
 * Finding minimal clique cover in arbitrary graph is NP-complete.
 * We build just some cover (not necessarily minimal).
 * The algorithm takes quadratic (in the number of tags) time.
 */
static size_t equivalence_classes(const dfa_t &dfa,
	const bool *intrf, size_t *represent)
{
	static const size_t END = std::numeric_limits<size_t>::max();
	const size_t ntags = dfa.tags.size();
	std::vector<size_t>
		head(ntags, END), // list of representatives
		next(ntags, END); // list of tags mapped to the same representative

	// skip the 1st tag, it maps to itself
	memset(represent, 0, ntags * sizeof(size_t));
	for (size_t c = 1; c < ntags; ++c) {
		size_t h;
		for (h = 0; h != END; h = head[h]) {
			size_t n;
			for (n = h; n != END; n = next[n]) {
				if (intrf[c * ntags + n]) {
					break;
				}
			}
			if (n == END) {
				represent[c] = h;
				next[c] = next[h];
				next[h] = c;
				break;
			}
		}
		if (h == END) {
			represent[c] = c;
			head[c] = head[0];
			head[0] = c;
		}
	}

	size_t nreps = 0;
	for (size_t i = 0; i < ntags; ++i) {
		if (dfa.tags[i].type == Tag::VAR && represent[i] == i) {
			++nreps;
		}
	}
	return nreps;
}

static void subst(Tagpool &tagpool, size_t *ptags, const size_t *represent)
{
	const size_t ntag = tagpool.ntags;
	const bool *tags = tagpool[*ptags];
	bool *subs = tagpool.buffer1;
	memset(subs, 0, ntag * sizeof(bool));
	for (size_t t = 0; t < ntag; ++t) {
		if (tags[t]) {
			subs[represent[t]] = true;
		}
	}
	*ptags = tagpool.insert(subs);
}

static void substitute(dfa_t &dfa, const size_t *represent)
{
	const size_t
		nstates = dfa.states.size(),
		ntags = dfa.tags.size();

	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			subst(dfa.tagpool, &s->tags[c].set, represent);
			subst(dfa.tagpool, &s->tags[c].copy, represent);
		}
		subst(dfa.tagpool, &s->rule_tags.set, represent);
		subst(dfa.tagpool, &s->rule_tags.copy, represent);
	}
	subst(dfa.tagpool, &dfa.copy_tags, represent);

	for (size_t i = 0; i < ntags; ++i) {
		Tag &t = dfa.tags[i];
		if (t.type == Tag::VAR) {
			t.var.orig = represent[i];
		}
	}
}

size_t deduplicate_tags(dfa_t &dfa)
{
	const size_t ntag = dfa.tags.size();
	if (ntag == 0) return 0;

	bool *live = new bool[dfa.states.size() * dfa.nchars * ntag];
	bool *interfere = new bool[ntag * ntag];
	size_t *represent = new size_t[ntag];

	liveness(dfa, live);
	mask_dead(dfa, live);
	interference(dfa, live, interfere);
	const size_t nrep = equivalence_classes(dfa, interfere, represent);
	if (nrep < ntag) {
		substitute(dfa, represent);
	}

	delete[] live;
	delete[] interfere;
	delete[] represent;

	return nrep;
}

} // namespace re2c

