#include "src/ir/dfa/cfg/cfg.h"

namespace re2c
{

template<typename cmd_t> void normalize(cmd_t *cmd);

/* note [tag normalization]
 *
 * After optimizations different commands may become equal
 * up to reordering and removing duplicates. Such commands
 * should be recognized as equal by further optimizations
 * like minimization, hoisting, tunnelling, etc.
 * For that reason all commands are normalized.
 */

void tag_normalization(cfg_t &cfg)
{
	cfg_bb_t *b = cfg.bblocks, *e = b + cfg.nbblock;
	for (; b < e; ++b) {
		normalize(b->cmd->save);
		normalize(b->cmd->copy);
	}
}

template<typename cmd_t>
void normalize(cmd_t *cmd)
{
	// sort lexicographically
	for (cmd_t *p = cmd; p; p = p->next) {
		for (cmd_t *q = p->next; q; q = q->next) {
			if (cmd_t::less(*q, *p)) {
				cmd_t::swap(*p, *q);
			}
		}
	}

	// delete duplicates
	for (cmd_t *p = cmd; p; p = p->next) {
		cmd_t *q = p->next;
		if (q && cmd_t::equal(*p, *q)) {
			p->next = q->next;
		}
	}
}

} // namespace re2c

