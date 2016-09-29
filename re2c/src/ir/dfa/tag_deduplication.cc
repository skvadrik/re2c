#include <limits>

#include "src/ir/dfa/dfa.h"

namespace re2c
{

struct revarc_t
{
	size_t dest;
	size_t tags;
	revarc_t *next;
};

static void backprop(revarc_t **rdfa,
	Tagpool &tagpool,
	size_t *live,
	size_t tags,
	size_t state)
{
	const size_t l = live[state];
	live[state] = tagpool.orl(l, tags);
	if (l == live[state]) return;

	for (const revarc_t *a = rdfa[state]; a; a = a->next) {
		backprop(rdfa, tagpool, live,
			tagpool.andlinv(tags, a->tags), a->dest);
	}
}

static void forwprop(const dfa_t &dfa, bool *been, size_t state,
	size_t *live, size_t need)
{
	if (been[state]) return;
	been[state] = true;

	live[state] = dfa.tagpool.orl(live[state], need);

	const dfa_state_t *s = dfa.states[state];
	for (size_t c = 0; c < dfa.nchars; ++c) {
		const size_t dest = s->arcs[c];
		if (dest != dfa_t::NIL && dfa.states[dest]->fallthru) {
			forwprop(dfa, been, dest, live, need);
		}
	}
}

/* note [liveness analyses on tags]
 *
 * Liveness of a rule tag is propagated backwards from final
 * state and until we meet transition that updates this tag.
 *
 * Liveness of fallback tag is propagated forward from fallback
 * state (see note [fallback states]) and until there remain
 * any fallthrough paths from current state.
 */
static void calc_live(const dfa_t &dfa, size_t *live)
{
	const size_t nstates = dfa.states.size();

	// backward-propagate rule tags
	revarc_t **rdfa = new revarc_t*[nstates]();
	revarc_t *rarcs = new revarc_t[nstates * dfa.nchars];
	revarc_t *a = rarcs;
	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			const size_t j = s->arcs[c];
			if (j != dfa_t::NIL) {
				a->dest = i;
				a->tags = s->tags[c];
				a->next = rdfa[j];
				rdfa[j] = a++;
			}
		}
	}
	for (size_t i = 0; i < nstates; ++i) {
		const dfa_state_t *s = dfa.states[i];
		if (s->rule != Rule::NONE) {
			const size_t need = dfa.tagpool.andlinv(
				dfa.rules[s->rule].tags, s->rule_tags);
			backprop(rdfa, dfa.tagpool, live, need, i);
		}
	}
	delete[] rdfa;
	delete[] rarcs;

	// forward-propagate fallback tags
	bool *been = new bool[nstates];
	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		if (s->fallback) {
			const size_t need = dfa.tagpool.andlinv(
				dfa.rules[s->rule].tags, s->rule_tags);
			std::fill(been, been + nstates, false);
			forwprop(dfa, been, i, live, need);
		}
	}
	delete[] been;
}

static void mask_dead(dfa_t &dfa, const size_t *live)
{
	const size_t nstates = dfa.states.size();
	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			const size_t j = s->arcs[c];
			if (j != dfa_t::NIL) {
				s->tags[c] = dfa.tagpool.andl(s->tags[c],
					live[j]);
			}
		}
		if (s->rule != Rule::NONE) {
			s->rule_tags = dfa.tagpool.andl(s->rule_tags,
				dfa.rules[s->rule].tags);
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
	const size_t *livetags, bool *incompattbl)
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
		if (s->rule != Rule::NONE) {
			incompatible(incompattbl, dfa.tagpool,
				dfa.rules[s->rule].tags, s->rule_tags);
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
	size_t ntags, size_t *represent)
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

static void patch_tags(dfa_t &dfa, const size_t *represent)
{
	const size_t nstates = dfa.states.size();
	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			s->tags[c] = dfa.tagpool.subst(s->tags[c], represent);
		}
		s->rule_tags = dfa.tagpool.subst(s->rule_tags, represent);
	}

	const size_t ntags = dfa.tags.size();
	for (size_t i = 0; i < ntags; ++i) {
		Tag &t = dfa.tags[i];
		if (t.type == Tag::VAR) {
			t.var.orig = represent[i];
		}
	}
}

size_t deduplicate_tags(dfa_t &dfa)
{
	const size_t ntags = dfa.tags.size();
	if (ntags == 0) {
		return 0;
	}

	const size_t nstates = dfa.states.size();
	size_t *live = new size_t[nstates]();
	calc_live(dfa, live);

	mask_dead(dfa, live);

	bool *incompattbl = new bool[ntags * ntags]();
	incompatibility_table(dfa, live, incompattbl);

	size_t *represent = new size_t[ntags]();
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
	delete[] represent;

	return nreps;
}

} // namespace re2c

