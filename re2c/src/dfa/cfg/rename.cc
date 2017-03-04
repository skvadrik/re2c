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

		// tag versions in save commands
		for (tagsave_t *p = b->cmd->save; p; p = p->next) {
			p->ver = ver2new[p->ver];
		}

		// tag versions in copy commands
		for (tagcopy_t *c, **pc = &b->cmd->copy; (c = *pc);) {
			c->lhs = ver2new[c->lhs];
			c->rhs = ver2new[c->rhs];
			if (c->lhs == c->rhs) {
				*pc = c->next;
			} else {
				pc = &c->next;
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

