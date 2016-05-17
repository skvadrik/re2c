#include <limits>

#include "src/ir/dfa/dfa.h"

namespace re2c
{

static size_t mask_dead_tags(Tagpool &tagpool,
	size_t oldidx, const bool *live)
{
	const bool *oldtags = tagpool[oldidx];
	bool *newtags = new bool[tagpool.ntags];
	for (size_t i = 0; i < tagpool.ntags; ++i) {
		newtags[i] = oldtags[i] & live[i];
	}
	const size_t newidx = tagpool.insert(newtags);
	delete[] newtags;
	return newidx;
}

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
 * Tag T is alive in state S if either:
 *
 *    - There is a transition from S to default state that does not set T,
 *      S is final and T belongs to tag set associated with rule in S.
 *
 *    - There is a transition from S to default state that does not set T
 *      and T belongs to any tag set associated with fallback rules.
 *
 *    - There is a transition from S to some state S' (maybe equal to S)
 *      that does not set T and T is alive in S'.
 */
static void calc_live(const dfa_t &dfa, const bool *fallback, bool *live)
{
	const size_t nstates = dfa.states.size();
	const size_t ntags = dfa.tags.size();

	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		if (dangling_arcs(s->arcs, dfa.nchars)) {
			if (s->rule != Rule::NONE) {
				// final state, only rule tags are alive
				add_tags_with_mask(&live[i * ntags],
					dfa.rules[s->rule].tags,
					dfa.tagpool[s->rule_tags],
					ntags);
			} else {
				// transition to default state and dispatch on
				// 'yyaccept': all fallback rules are potentially
				// reachable, their tags are alive
				// no mask: no rule implies no rule tags
				add_tags(&live[i * ntags], fallback, ntags);
			}
		}
	}

	for (bool loop = true; loop;) {
		loop = false;
		for (size_t i = 0; i < nstates; ++i) {
			dfa_state_t *s = dfa.states[i];
			for (size_t c = 0; c < dfa.nchars; ++c) {
				const size_t j = s->arcs[c];
				if (j != dfa_t::NIL) {
					loop |= addcmp_tags_with_mask(&live[i * ntags],
						&live[j * ntags],
						dfa.tagpool[s->tags[c]],
						ntags);
				}
			}
		}
	}
}

static void mask_dead(dfa_t &dfa,
	const bool *livetags)
{
	const size_t nstates = dfa.states.size();
	const size_t ntags = dfa.tags.size();
	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			const size_t j = s->arcs[c];
			if (j != dfa_t::NIL) {
				s->tags[c] = mask_dead_tags(dfa.tagpool,
					s->tags[c], &livetags[j * ntags]);
			}
		}
		if (s->rule != Rule::NONE) {
			s->rule_tags = mask_dead_tags(dfa.tagpool,
				s->rule_tags, dfa.rules[s->rule].tags);
		}
	}
}

// tags that are updated here are pairwise incompatible
// with all tags that are alive, but not updated here
static void incompatible(bool *tbl,
	const bool *live,
	const bool *tags,
	size_t ntags)
{
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
	const bool *livetags,
	const bool *deftags,
	bool *incompattbl)
{
	const size_t nstates = dfa.states.size();
	const size_t ntags = dfa.tags.size();
	for (size_t i = 0; i < nstates; ++i) {
		const dfa_state_t *s = dfa.states[i];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			const size_t j = s->arcs[c];
			if (j != dfa_t::NIL) {
				incompatible(incompattbl,
					&livetags[j * ntags],
					dfa.tagpool[s->tags[c]],
					ntags);
			}
		}
		if (dangling_arcs(s->arcs, dfa.nchars)) {
			if (s->rule != Rule::NONE) {
				incompatible(incompattbl,
					dfa.rules[s->rule].tags,
					dfa.tagpool[s->rule_tags],
					ntags);
			} else {
				incompatible(incompattbl,
					deftags,
					dfa.tagpool[s->rule_tags],
					ntags);
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
 * static void equivalence_classes(const std::vector<bool> &incompattbl,
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

static size_t patch_tagset(Tagpool &tagpool, size_t oldidx,
	const std::vector<size_t> &represent)
{
	const bool *oldtags = tagpool[oldidx];
	bool *newtags = new bool[tagpool.ntags]();
	for (size_t i = 0; i < tagpool.ntags; ++i) {
		if (oldtags[i]) {
			newtags[represent[i]] = true;
		}
	}
	const size_t newidx = tagpool.insert(newtags);
	delete[] newtags;
	return newidx;
}

static void patch_tags(dfa_t &dfa, const std::vector<size_t> &represent)
{
	const size_t nstates = dfa.states.size();
	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			s->tags[c] = patch_tagset(dfa.tagpool, s->tags[c], represent);
		}
		s->rule_tags = patch_tagset(dfa.tagpool, s->rule_tags, represent);
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

	bool *fbtags = new bool[ntags]();
	for (size_t i = 0; i < fallback.size(); ++i) {
		const size_t r = dfa.states[fallback[i]]->rule;
		add_tags(fbtags, dfa.rules[r].tags, ntags);
	}

	const size_t nstates = dfa.states.size();
	bool *live = new bool[nstates * ntags]();
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

	delete[] fbtags;
	delete[] live;
	delete[] incompattbl;

	return nreps;
}

} // namespace re2c

