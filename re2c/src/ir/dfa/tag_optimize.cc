#include <string.h>

#include "src/ir/dfa/dfa.h"
#include "src/ir/dfa/tag_optimize.h"

namespace re2c
{

void optimize_tags(dfa_t &dfa)
{
	if (dfa.maxtagver == 0) return;

	const size_t
		narc = dfa.states.size() * dfa.nchars,
		nver = static_cast<size_t>(dfa.maxtagver) + 1;
	bool *live = new bool[narc * nver];
	bool *interf = new bool[nver * nver];
	tagver_t *ver2new = new tagver_t[nver];

	tag_liveness(dfa, live);
	tag_dce(dfa, live);
	tag_interference(dfa, live, interf);
	const tagver_t maxver = tag_allocation(dfa, interf, ver2new);
	tag_renaming(dfa, ver2new, maxver);
	tag_indexing(dfa);

	delete[] live;
	delete[] interf;
	delete[] ver2new;
}

} // namespace re2c

