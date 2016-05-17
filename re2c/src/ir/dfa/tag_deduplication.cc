#include <limits>

#include "src/ir/dfa/dfa.h"

namespace re2c
{

static bool dangling_arcs(const size_t *arcs, size_t narcs)
{
	for (size_t i = 0; i < narcs; ++i) {
		if (arcs[i] == dfa_t::NIL) {
			return true;
		}
	}
	return false;
}

/* note [liveness analyses on tags]
 *
 * Tag T is alive in state S if there is a transition
 * from S to some state S' that does not update T
 * and either:
 *
 *    - S' is the default state
 *      and S is final
 *      and T belongs to S's final tag set
 *
 *    - S' is the default state
 *      and S is not final
 *      and T belongs to fallback tag set
 *
 *    - S' is not the default state
 *      and T is alive in S'
 */
static void calc_live(const dfa_t &dfa, size_t fallback, size_t *live)
{
	const size_t nstates = dfa.states.size();

	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		if (dangling_arcs(s->arcs, dfa.nchars)) {
			if (s->rule != Rule::NONE) {
				// final state, only rule tags are alive
				dfa.tagpool.orl_with_mask(&live[i],
					dfa.rules[s->rule].tags, s->rule_tags);
			} else {
				// transition to default state and dispatch on
				// 'yyaccept': all fallback rules are potentially
				// reachable, their tags are alive
				// no mask: no rule implies no rule tags
				dfa.tagpool.orl(&live[i], fallback);
			}
		}
	}

	for (bool loop = true; loop;) {
		loop = false;
		for (size_t i = 0; i < nstates; ++i) {
			const size_t l = live[i];
			dfa_state_t *s = dfa.states[i];
			for (size_t c = 0; c < dfa.nchars; ++c) {
				const size_t j = s->arcs[c];
				if (j != dfa_t::NIL) {
					dfa.tagpool.orl_with_mask(&live[i], live[j], s->tags[c]);
				}
			}
			loop |= live[i] != l;
		}
	}
}

static void mask_dead(dfa_t &dfa, const size_t *live)
{
	const size_t nstates = dfa.states.size();
	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			const size_t j = s->arcs[c];
			if (j != dfa_t::NIL) {
				dfa.tagpool.andl(&s->tags[c], live[j]);
			}
		}
		if (s->rule != Rule::NONE) {
			dfa.tagpool.andl(&s->rule_tags, dfa.rules[s->rule].tags);
		}
	}
}

// tags that are updated here are pairwise incompatible
// with all tags that are alive, but not updated here
static void incompatible(bool *tbl,
	Tagpool &tagpool, size_t l, size_t t)
{
	const size_t ntags = tagpool.ntags;
	const bool *live = tagpool[l];
	const bool *tags = tagpool[t];
	for (size_t i = 0; i < ntags; ++i) {
		if (live[i] && !tags[i]) {
			for (size_t j = 0; j < ntags; ++j) {
				if (tags[j]) {
					tbl[i * ntags + j] = tbl[j * ntags + i] = true;
				}
			}
		}
	}
}

static void incompatibility_table(const dfa_t &dfa,
	const size_t *livetags, size_t deftags,
	bool *incompattbl)
{
	const size_t nstates = dfa.states.size();
	const size_t ntags = dfa.tags.size();
	for (size_t i = 0; i < nstates; ++i) {
		const dfa_state_t *s = dfa.states[i];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			const size_t j = s->arcs[c];
			if (j != dfa_t::NIL) {
				incompatible(incompattbl, dfa.tagpool,
					livetags[j], s->tags[c]);
			}
		}
		if (dangling_arcs(s->arcs, dfa.nchars)) {
			if (s->rule != Rule::NONE) {
				incompatible(incompattbl, dfa.tagpool,
					dfa.rules[s->rule].tags, s->rule_tags);
			} else {
				incompatible(incompattbl, dfa.tagpool,
					deftags, s->rule_tags);
			}
		}
	}

	// fixed tags should not participate in deduplication, so
	// each fixed tag is incompatible with all other tags
	for (size_t i = 0; i < ntags; ++i) {
		if (dfa.tags[i].type == Tag::FIX) {
			for (size_t j = 0; j < ntags; ++j) {
				incompattbl[i * ntags + j]
					= incompattbl[j * ntags + i]
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
static void equivalence_classes(const bool *incompattbl,
	size_t ntags, std::vector<size_t> &represent)
{
	static const size_t END = std::numeric_limits<size_t>::max();
	std::vector<size_t>
		head(ntags, END), // list of representatives
		next(ntags, END); // list of tags mapped to the same representative

	// skip the 1st tag, it maps to itself
	for (size_t c = 1; c < ntags; ++c) {
		size_t h;
		for (h = 0; h != END; h = head[h]) {
			size_t n;
			for (n = h; n != END; n = next[n]) {
				if (incompattbl[c * ntags + n]) {
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
}

static void patch_tags(dfa_t &dfa, const std::vector<size_t> &represent)
{
	const size_t nstates = dfa.states.size();
	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			dfa.tagpool.subst(&s->tags[c], represent);
		}
		dfa.tagpool.subst(&s->rule_tags, represent);
	}

	const size_t ntags = dfa.tags.size();
	for (size_t i = 0; i < ntags; ++i) {
		Tag &t = dfa.tags[i];
		if (t.type == Tag::VAR) {
			t.var.orig = represent[i];
		}
	}
}

size_t deduplicate_tags(dfa_t &dfa,
	const std::vector<size_t> &fallback)
{
	const size_t ntags = dfa.tags.size();
	if (ntags == 0) {
		return 0;
	}

	size_t fbtags = 0;
	for (size_t i = 0; i < fallback.size(); ++i) {
		const size_t r = dfa.states[fallback[i]]->rule;
		dfa.tagpool.orl(&fbtags, dfa.rules[r].tags);
	}

	const size_t nstates = dfa.states.size();
	size_t *live = new size_t[nstates]();
	calc_live(dfa, fbtags, live);

	mask_dead(dfa, live);

	bool *incompattbl = new bool[ntags * ntags]();
	incompatibility_table(dfa, live, fbtags, incompattbl);

	std::vector<size_t> represent(ntags, 0);
	equivalence_classes(incompattbl, ntags, represent);

	size_t nreps = 0;
	for (size_t i = 0; i < ntags; ++i) {
		if (dfa.tags[i].type == Tag::VAR && represent[i] == i) {
			++nreps;
		}
	}

	if (nreps < ntags) {
		patch_tags(dfa, represent);
	}

	delete[] live;
	delete[] incompattbl;

	return nreps;
}

} // namespace re2c

