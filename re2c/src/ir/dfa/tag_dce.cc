#include "src/ir/dfa/tag_optimize.h"

namespace re2c
{

void tag_dce(cfg_t &cfg, const bool *live)
{
	const tagver_t nver = cfg.dfa.maxtagver + 1;
	cfg_bb_t *b = cfg.bblocks, *e = b + cfg.nbblock;

	for (; b < e; ++b, live += nver) {
		for (tagsave_t *s, **ps = &b->cmd->save; (s = *ps);) {
			if (!live[s->ver]) {
				*ps = s->next;
			} else {
				ps = &s->next;
			}
		}
		// rule tags and copy tags can't be dead by construction
		// (copy tags are only used for fallback tags)
	}
}

} // namespace re2c

