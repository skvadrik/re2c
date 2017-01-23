#include "src/ir/dfa/cfg/cfg.h"

namespace re2c
{

tagver_t cfg_t::compact(const cfg_t &cfg, tagver_t *ver2new)
{
	const size_t
		nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1,
		ntag = cfg.dfa.vartags.size();
	const tagver_t *fins = cfg.dfa.finvers;
	bool *used = new bool[nver];

	std::fill(used, used + nver, false);
	for (size_t t = 0; t < ntag; ++t) {
		used[fins[t]] = true;
	}
	for (size_t i = 0; i < cfg.nbbfall; ++i) {
		const cfg_bb_t &b = cfg.bblocks[i];

		for (const tagsave_t *p = b.cmd->save; p; p = p->next) {
			used[p->ver] = true;
		}

		for (const tagcopy_t *p = b.cmd->copy; p; p = p->next) {
			used[p->lhs] = used[p->rhs] = true;
		}
	}

	tagver_t maxver = 0;
	for (size_t v = 0; v < nver; ++v) {
		if (used[v]) {
			ver2new[v] = ++maxver;
		}
	}

	delete[] used;
	return maxver;
}

} // namespace re2c

