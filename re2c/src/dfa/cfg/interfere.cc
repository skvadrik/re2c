#include <string.h>

#include "src/dfa/cfg/cfg.h"

namespace re2c
{

static void interfere(const tcmd_t *cmd, const bool *live, bool *interf, bool *buf, size_t nver);

void cfg_t::interference(const cfg_t &cfg, const bool *live, bool *interf)
{
	const size_t nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1;
	bool *buf = new bool[nver];
	const cfg_bb_t *b = cfg.bblocks, *e = b + cfg.nbbfin;

	memset(interf, 0, nver * nver * sizeof(bool));
	for (; b < e; ++b, live += nver) {
		interfere(b->cmd, live, interf, buf, nver);
	}

	delete[] buf;
}

void interfere(const tcmd_t *cmd, const bool *live, bool *interf,
	bool *buf, size_t nver)
{
	// LHS of each command iterferes with all tags that are alive after
	// this command except its RHS and tags that are are assigned to
	// the same RHS by other commands in this block.
	for (const tcmd_t *p = cmd; p; p = p->next) {
		const tagver_t r = p->rhs, *h = p->history;

		// alive after this command
		memcpy(buf, live, nver * sizeof(bool));
		cfg_t::live_through_bblock(p->next, buf);

		// exclude RHS
		if (tcmd_t::iscopy(p)) buf[r] = false;

		// exclude tags assigned to the same RHS
		for (const tcmd_t *q = cmd; q; q = q->next) {
			if (q->rhs == r && tcmd_t::equal_history(h, q->history)) {
				buf[q->lhs] = false;
			}
		}

		const size_t l = static_cast<size_t>(p->lhs);
		for (size_t v = 0; v < nver; ++v) {
			if (!buf[v]) continue;
			interf[l * nver + v] = interf[v * nver + l] = true;
		}
	}
}

} // namespace re2c
