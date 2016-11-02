#include "src/ir/dfa/cfg/cfg.h"

namespace re2c
{

void cfg_t::renaming(cfg_t &cfg, const tagver_t *ver2new, tagver_t maxver)
{
	tagver_t &oldmax = cfg.dfa.maxtagver;
	if (oldmax == maxver) return;
	oldmax = maxver;

	cfg_bb_t *b = cfg.bblocks, *e = b + cfg.nbblock;
	for (; b < e; ++b) {

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

	// final tag versions in rules
	std::valarray<Rule> &rules = cfg.dfa.rules;
	for (size_t r = 0, t = 0; r < rules.size(); ++r) {
		Rule &rule = rules[r];
		for (; t < rule.htag; ++t) {
			tagver_t &v = rule.tags[t];
			if (v != TAGVER_ZERO) {
				v = ver2new[v];
			}
		}
	}
}

} // namespace re2c

