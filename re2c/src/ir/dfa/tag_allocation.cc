#include <limits>

#include "src/ir/dfa/tag_optimize.h"

namespace re2c
{

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
tagver_t tag_allocation(const dfa_t &dfa, const bool *interf,
	tagver_t *ver2new)
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

} // namespace re2c

