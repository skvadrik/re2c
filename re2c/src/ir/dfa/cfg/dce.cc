#include "src/ir/dfa/cfg/cfg.h"

namespace re2c
{

void cfg_t::dead_code_elimination(cfg_t &cfg, const bool *live)
{
	const tagver_t nver = cfg.dfa.maxtagver + 1;
	// final and fallback tags can't be dead by construction
	cfg_bb_t *b = cfg.bblocks, *e = b + cfg.nbbarc;

	for (; b < e; ++b, live += nver) {
		for (tagsave_t *s, **ps = &b->cmd->save; (s = *ps);) {
			if (!live[s->ver]) {
				*ps = s->next;
			} else {
				ps = &s->next;
			}
		}
		for (tagcopy_t *c, **pc = &b->cmd->copy; (c = *pc);) {
			if (!live[c->lhs]) {
				*pc = c->next;
			} else {
				pc = &c->next;
			}
		}
	}
}

} // namespace re2c

