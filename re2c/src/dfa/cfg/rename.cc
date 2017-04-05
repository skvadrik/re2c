#include "src/dfa/cfg/cfg.h"

namespace re2c
{

void cfg_t::renaming(cfg_t &cfg, const tagver_t *ver2new, tagver_t maxver)
{
	tagver_t &oldmax = cfg.dfa.maxtagver;
	if (oldmax == maxver) return;
	oldmax = maxver;

	cfg_bb_t *b = cfg.bblocks, *be = b + cfg.nbbfall;
	for (; b < be; ++b) {
		for (tcmd_t *p, **pp = &b->cmd; (p = *pp);) {
			tagver_t &l = p->lhs, &r = p->rhs, &h = p->pred;

			l = ver2new[l];
			if (tcmd_t::iscopy(r)) {
				r = ver2new[r];
			}
			if (h != TAGVER_ZERO) {
				h = ver2new[h];
			}
			if (l == r) {
				*pp = p->next;
			} else {
				pp = &p->next;
			}
		}
	}

	// final tag versions
	tagver_t *fins = cfg.dfa.finvers;
	const std::vector<Tag> &tags = cfg.dfa.tags;
	for (size_t t = 0; t < tags.size(); ++t) {
		if (!fixed(tags[t])) {
			fins[t] = ver2new[fins[t]];
		}
	}
}

} // namespace re2c

