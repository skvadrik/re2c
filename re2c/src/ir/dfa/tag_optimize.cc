#include <string.h>

#include "src/ir/dfa/dfa.h"
#include "src/ir/dfa/tag_optimize.h"

namespace re2c
{

static size_t count_variable_tags(const std::valarray<Tag> &tags);

tagver_t optimize_tags(dfa_t &dfa)
{
	if (count_variable_tags(dfa.tags) == 0) return 0;

	const size_t
		narc = dfa.states.size() * dfa.nchars,
		nver = dfa.tags.size() + 1;
	bool *live = new bool[narc * nver];
	bool *interf = new bool[nver * nver];
	tagver_t *ver2new = new tagver_t[nver];

	tag_liveness(dfa, live);
	tag_dce(dfa, live);
	tag_interference(dfa, live, interf);
	const tagver_t maxver = tag_allocation(dfa, interf, ver2new);
	tag_renaming(dfa, ver2new, maxver);

	delete[] live;
	delete[] interf;
	delete[] ver2new;
	return maxver;
}

size_t count_variable_tags(const std::valarray<Tag> &tags)
{
	size_t nvar = 0, ntag = tags.size();
	for (size_t t = 0; t < ntag; ++t) {
		if (tags[t].type == Tag::VAR) {
			++nvar;
		}
	}
	return nvar;
}

void unpack(size_t nver, bool *vers, size_t ntag, const tagver_t *tags)
{
	memset(vers, 0, nver * sizeof(bool));
	for (size_t t = 0; t < ntag; ++t) {
		const tagver_t v = tags[t];
		if (v != TAGVER_ZERO) {
			vers[v] = true;
		}
	}
}

} // namespace re2c

