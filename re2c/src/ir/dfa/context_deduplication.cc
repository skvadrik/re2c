#include <limits>
#include <set>
#include <vector>

#include "src/ir/dfa/dfa.h"

namespace re2c
{

static void calc_live(
	const dfa_t &dfa,
	const std::set<size_t> &fallback,
	std::vector<bool> &visited,
	std::vector<std::set<size_t> > &live,
	size_t i)
{
	if (!visited[i]) {
		visited[i] = true;

		dfa_state_t *s = dfa.states[i];

		bool fallthru = false;
		for (size_t c = 0; c < dfa.nchars; ++c) {
			const size_t j = s->arcs[c];
			if (j != dfa_t::NIL) {
				calc_live(dfa, fallback, visited, live, j);
				live[i].insert(live[j].begin(), live[j].end());
			} else {
				fallthru = true;
			}
		}

		if (s->rule != NULL) {
			live[i].insert(s->rule->ctxvar.begin(), s->rule->ctxvar.end());
			const Trail &ctx = s->rule->trail;
			if (ctx.type == Trail::VAR) {
				live[i].insert(ctx.pld.var);
			}
		} else if (fallthru) {
			// transition to default state: all fallback rules
			// are potentialy reachable, their contexts are alive
			live[i].insert(fallback.begin(), fallback.end());
		}
	}
}

bool deduplicate_contexts(
	const dfa_t &dfa,
	const std::vector<size_t> &fallback)
{
	const size_t nctxs = dfa.contexts.size();
	if (nctxs < 2) {
		return false;
	}

	std::set<size_t> fbctxs;
	for (size_t i = 0; i < fallback.size(); ++i) {
		const RuleInfo *rule = dfa.states[fallback[i]]->rule;
		fbctxs.insert(rule->ctxvar.begin(), rule->ctxvar.end());
		if (rule->trail.type == Trail::VAR) {
			fbctxs.insert(rule->trail.pld.var);
		}
	}

	const size_t nstates = dfa.states.size();

	std::vector<bool> visited(nstates);
	std::vector<std::set<size_t> > live(nstates);
	calc_live(dfa, fbctxs, visited, live, 0);

	std::vector<size_t> buffer(nctxs);
	std::vector<bool> xxx(nctxs * nctxs);
	for (size_t i = 0; i < nstates; ++i) {
		const std::set<size_t>
			&ctxs = dfa.states[i]->ctxs,
			&liv = live[i];
		std::vector<size_t>::iterator
			diff = buffer.begin(),
			diff_end = std::set_difference(liv.begin(), liv.end(),
				ctxs.begin(), ctxs.end(), diff);
		for (; diff != diff_end; ++diff) {
			for (std::set<size_t>::const_iterator j = ctxs.begin(); j != ctxs.end(); ++j) {
				xxx[*diff * nctxs + *j] = xxx[*j * nctxs + *diff] = true;
			}
		}
	}

	// We have a binary relation on the set of all contexts
	// and must construct set decomposition into subsets such that
	// all contexts in the same subset are equivalent.
	//
	// This problem is isomorphic to partitioning graph into cliques
	// (aka finding the 'clique cover' of a graph).
	//
	// Finding minimal clique cover in arbitrary graph is NP-complete.
	// We build just some cover (not necessarily minimal).
	// The algorithm takes quadratic (in the number of contexts) time.

	static const size_t END = std::numeric_limits<size_t>::max();
	std::vector<size_t>
		part(nctxs, 0),   // partition: mapping of context to its representative
		head(nctxs, END), // list of representatives
		next(nctxs, END); // list of contexts mapped to the same representative
	// skip the 1st context, it maps to itself
	for (size_t c = 1; c < nctxs; ++c) {
		size_t h;
		for (h = 0; h != END; h = head[h]) {
			size_t n;
			for (n = h; n != END; n = next[n]) {
				if (xxx[c * nctxs + n]) {
					break;
				}
			}
			if (n == END) {
				part[c] = h;
				next[c] = next[h];
				next[h] = c;
				break;
			}
		}
		if (h == END) {
			part[c] = c;
			head[c] = head[0];
			head[0] = c;
		}
	}
	const bool multiple_contexts = head[0] != END;

/*
	std::vector<size_t> c2c;
	std::vector<std::vector<size_t> > part;
	for (size_t i = 0; i < nctxs; ++i) {
		size_t j;
		for (j = 0; j < partn.size(); ++j) {
			std::vector<size_t> &p = part[j];
			size_t k;
			for (k = 0; k < p.size(); ++k) {
				if (xxx[i * nctxs + p[k]]) {
					break;
				}
			}
			if (k == p.size()) {
				break;
			}
		}
		if (j == part.size()) {
			part.push_back(std::vector<size_t>());
		}
		part[j].push_back(i);
		c2c[i] = part[j][0];
	}
*/
	for (size_t i = 0; i < nstates; ++i) {
		dfa_state_t *s = dfa.states[i];
		std::set<size_t> ctxs;
		for (std::set<size_t>::const_iterator j = s->ctxs.begin(); j != s->ctxs.end(); ++j) {
			ctxs.insert(part[*j]);
		}
		s->ctxs.swap(ctxs);
	}
	for (size_t i = 0; i < nctxs; ++i) {
		dfa.contexts[i].fullname = dfa.contexts[part[i]].fullname;
	}

	return multiple_contexts;
}




} // namespace re2c

