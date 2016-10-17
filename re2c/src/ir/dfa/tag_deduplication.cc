#include <limits>

#include "src/ir/dfa/dfa.h"

namespace re2c
{

static void forwprop(const dfa_t &dfa, bool *been, size_t state,
	size_t *live, size_t need)
{
	if (been[state]) return;
	been[state] = true;

	const dfa_state_t *s = dfa.states[state];
	size_t *l = &live[state * dfa.nchars];
	for (size_t c = 0; c < dfa.nchars; ++c) {
		const size_t dest = s->arcs[c];
		if (dest != dfa_t::NIL && dfa.states[dest]->fallthru) {
			l[c] = dfa.tagpool.orl(l[c], need);
			forwprop(dfa, been, dest, live, need);
		}
	}
}

static void calc_live(const dfa_t &dfa, size_t *live)
{
	const size_t
		nstate = dfa.states.size(),
		nsym = dfa.nchars,
		narc = nstate * nsym;

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
	std::fill(live, live + narc, ZERO_TAGS);
	for (bool loop = true; loop;) {
		loop = false;

		for (size_t a = 0; a < narc; ++a) {
			const size_t i = dfa.states[a / nsym]->arcs[a % nsym];
			if (i == dfa_t::NIL) continue;
			const dfa_state_t *s = dfa.states[i];

			size_t l = s->rule == Rule::NONE
				? ZERO_TAGS
				: dfa.tagpool.andlinv(dfa.rules[s->rule].tags, s->rule_tags.set);

			const size_t *live_i = &live[i * nsym];
			for (size_t c = 0; c < nsym; ++c) {
				l = dfa.tagpool.orl(l,
					dfa.tagpool.andlinv(live_i[c], s->tags[c].set));
			}

			size_t *pl = &live[a];
			if (*pl != l) {
				*pl = l;
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
	bool *been = new bool[nstate];
	for (size_t i = 0; i < nstate; ++i) {
		dfa_state_t *s = dfa.states[i];
		if (s->fallback) {
			const size_t need = dfa.tagpool.andlinv(
				dfa.rules[s->rule].tags, s->rule_tags.set);
			std::fill(been, been + nstate, false);
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
		const size_t *l = &live[i * dfa.nchars];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			const size_t j = s->arcs[c];
			if (j != dfa_t::NIL) {
				s->tags[c].set = dfa.tagpool.andl(s->tags[c].set, l[c]);
			}
		}
		if (s->rule != Rule::NONE) {
			s->rule_tags.set = dfa.tagpool.andl(s->rule_tags.set,
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
		const size_t *l = &livetags[i * dfa.nchars];
		for (size_t c = 0; c < dfa.nchars; ++c) {
			const size_t j = s->arcs[c];
			if (j != dfa_t::NIL) {
				incompatible(incompattbl, dfa.tagpool, l[c], s->tags[c].set);
			}
		}
		if (s->rule != Rule::NONE) {
			incompatible(incompattbl, dfa.tagpool,
				dfa.rules[s->rule].tags, s->rule_tags.set);
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
			s->tags[c].set = dfa.tagpool.subst(s->tags[c].set, represent);
			s->tags[c].copy = dfa.tagpool.subst(s->tags[c].copy, represent);
		}
		s->rule_tags.set = dfa.tagpool.subst(s->rule_tags.set, represent);
		s->rule_tags.copy = dfa.tagpool.subst(s->rule_tags.copy, represent);
	}
	dfa.copy_tags = dfa.tagpool.subst(dfa.copy_tags, represent);

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

	const size_t
		nstates = dfa.states.size(),
		nedges = nstates * dfa.nchars;
	size_t *live = new size_t[nedges]();
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

