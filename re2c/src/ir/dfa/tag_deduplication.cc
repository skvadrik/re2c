#include <limits>
#include <string.h>

#include "src/ir/dfa/dfa.h"

namespace re2c
{

static void unpack(size_t nver, bool *vers, size_t ntag, const tagver_t *tags)
{
	memset(vers, 0, nver * sizeof(bool));
	for (size_t t = 0; t < ntag; ++t) {
		const tagver_t v = tags[t];
		if (v != TAGVER_ZERO) {
			vers[v] = true;
		}
	}
}

static void forwprop(const dfa_t &dfa, bool *been, size_t state,
	bool *live, const bool *need)
{
	if (been[state]) return;
	been[state] = true;

	const size_t
		nsym = dfa.nchars,
		nver = dfa.tags.size() + 1;
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

static void liveness_analysis(const dfa_t &dfa, bool *live)
{
	const size_t
		nstate = dfa.states.size(),
		nsym = dfa.nchars,
		narc = nstate * nsym,
		ntag = dfa.tags.size(),
		nver = ntag + 1;
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
	 */
	for (size_t i = 0; i < nstate; ++i) {
		const dfa_state_t *s = dfa.states[i];
		if (s->fallback) {
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
			memset(been, 0, nstate * sizeof(bool));
			forwprop(dfa, been, i, live, buf1);
		}
	}

	delete[] buf1;
	delete[] buf2;
	delete[] been;
}

static void dead_code_elimination(dfa_t &dfa, const bool *live)
{
	const size_t
		nsym = dfa.nchars,
		narc = dfa.states.size() * nsym,
		ntag = dfa.tags.size(),
		nver = ntag + 1;

	for (size_t a = 0; a < narc; ++a) {
		const size_t
			c = a % nsym,
			i = a / nsym;
		const dfa_state_t *s = dfa.states[i];
		// rule tags can't be dead by construction

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

// tags that are updated here are pairwise incompatible
// with all tags that are alive, but not updated here
static void interfere(bool *interf, size_t nver,
	const bool *live, const bool *tags)
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

static void interference_table(const dfa_t &dfa,
	const bool *live, bool *interf)
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
static tagver_t version_allocation(const dfa_t &dfa,
	const bool *interf, tagver_t *ver2new)
{
	const size_t
		END = std::numeric_limits<size_t>::max(),
		nver = dfa.tags.size() + 1;
	size_t *head = new size_t[nver]; // list of class representatives
	size_t *next = new size_t[nver]; // list of class members
	size_t h0 = END, h, n;

	std::fill(head, head + nver, END);
	std::fill(next, next + nver, END);
	for (size_t v = 0; v < nver; ++v) {
		const bool *interfv = &interf[v * nver];

		// try all existing classes
		for (h = h0; h != END; h = head[h]) {

			// check interference with class members
			for (n = h; n != END; n = next[n]) {
				if (interfv[n]) break;
			}

			// no interference; add to class
			if (n == END) {
				next[v] = next[h];
				next[h] = v;
				break;
			}
		}

		// make new equivalence class
		if (h == END) {
			head[v] = h0;
			h0 = v;
		}
	}

	tagver_t maxver = 0;
	for (h = h0; h != END; h = head[h]) {
		++maxver;
		for (n = h; n != END; n = next[n]) {
			ver2new[n] = maxver;
		}
	}

	delete[] head;
	delete[] next;

	return maxver;
}

static void rename(Tagpool &tagpool, size_t &tags,
	const tagver_t *ver2new, bool unify)
{
	if (tags == ZERO_TAGS) return;

	const tagver_t *oldver = tagpool[tags];
	tagver_t *newver = tagpool.buffer1;
	const size_t ntag = tagpool.ntags;

	for (size_t t = 0; t < ntag; ++t) {
		const tagver_t v = oldver[t];
		newver[t] = v != TAGVER_ZERO
			? ver2new[v]
			: v;
	}

	// for transition tags, we don't care how versions map to
	// tags: identical sets of versions should compare equal
	// this doesn't apply to final tag versions in rules
	if (unify) {
		tagver_t *e = newver + ntag;
		std::sort(newver, e);
		std::fill(std::unique(newver, e), e, TAGVER_ZERO);
	}

	tags = tagpool.insert(newver);
}

static void version_renaming(dfa_t &dfa,
	const tagver_t *ver2new, tagver_t maxver)
{
	const tagver_t oldmax = static_cast<tagver_t>(dfa.tags.size());
	if (maxver >= oldmax) {
		assert(maxver == oldmax);
		return;
	}

	Tagpool &tagpool = dfa.tagpool;
	const size_t
		nstates = dfa.states.size(),
		nrule = dfa.rules.size();

	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			rename(tagpool, s->tags[c].set, ver2new, true);
			rename(tagpool, s->tags[c].copy, ver2new, true);
		}
		rename(tagpool, s->rule_tags.set, ver2new, true);
		rename(tagpool, s->rule_tags.copy, ver2new, true);
	}
	rename(dfa.tagpool, dfa.copy_tags, ver2new, true);
	for (size_t i = 0; i < nrule; ++i) {
		rename(tagpool, dfa.rules[i].tags, ver2new, false);
	}
}

static size_t count_vartags(const std::valarray<Tag> &tags)
{
	size_t nvar = 0, ntag = tags.size();
	for (size_t t = 0; t < ntag; ++t) {
		if (tags[t].type == Tag::VAR) {
			++nvar;
		}
	}
	return nvar;
}

tagver_t deduplicate_tags(dfa_t &dfa)
{
	if (count_vartags(dfa.tags) == 0) return 0;

	const size_t
		narc = dfa.states.size() * dfa.nchars,
		nver = dfa.tags.size() + 1;
	bool *live = new bool[narc * nver];
	bool *interf = new bool[nver * nver];
	tagver_t *rename = new tagver_t[nver];

	liveness_analysis(dfa, live);
	dead_code_elimination(dfa, live);
	interference_table(dfa, live, interf);
	const tagver_t maxver = version_allocation(dfa, interf, rename);
	version_renaming(dfa, rename, maxver);

	delete[] live;
	delete[] interf;
	delete[] rename;

	return maxver;
}

} // namespace re2c

