#include <string.h>

#include "src/dfa/cfg/cfg.h"

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

static void normalize(tcmd_t *s, tcmd_t *e);

void cfg_t::normalization(cfg_t &cfg)
{
	const size_t nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1;
	uint32_t *indeg = new uint32_t[nver];
	memset(indeg, 0, nver * sizeof(uint32_t));

	cfg_bb_t *b = cfg.bblocks, *e = b + cfg.nbbfall;
	for (; b < e; ++b) {

		for (tcmd_t *x = b->cmd, *y; x;) {
			for (y = x; x && !tcmd_t::iscopy(x->rhs); x = x->next);
			normalize(y, x);
			for (y = x; x && tcmd_t::iscopy(x->rhs); x = x->next);
			normalize(y, x);
		}

		tcmd_t::topsort(&b->cmd, indeg);
	}

	delete[] indeg;
}

void normalize(tcmd_t *s, tcmd_t *e)
{
	// sort lexicographically
	for (tcmd_t *p = s; p != e; p = p->next) {
		for (tcmd_t *q = p->next; q != e; q = q->next) {
			if (tcmd_t::less(*q, *p)) {
				tcmd_t::swap(*p, *q);
			}
		}
	}

	// delete duplicates
	for (tcmd_t *p = s; p != e;) {
		tcmd_t *q = p->next;
		if (q != e && tcmd_t::equal(*p, *q)) {
			p->next = q->next;
		} else {
			p = q;
		}
	}
}

} // namespace re2c

