#include <string.h>

#include "src/dfa/cfg/cfg.h"

namespace re2c
{

typedef std::vector<tagver_t> vals_t;
static void interfere(const tcmd_t *cmd, const bool *live, bool *interf, bool *buf, vals_t *vals, size_t nver);

void cfg_t::interference(const cfg_t &cfg, const bool *live, bool *interf)
{
	const size_t nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1;
	bool *buf = new bool[nver];
	vals_t *vals = new vals_t[nver]();
	const cfg_bb_t *b = cfg.bblocks, *e = b + cfg.nbbfin;

	memset(interf, 0, nver * nver * sizeof(bool));
	for (; b < e; ++b, live += nver) {
		interfere(b->cmd, live, interf, buf, vals, nver);
	}

	delete[] buf;
	delete[] vals;
}

void interfere(const tcmd_t *cmd, const bool *live, bool *interf,
	bool *buf, vals_t *vals, size_t nver)
{
	// initialize value of RHS for all commands in this basic block
	for (const tcmd_t *p = cmd; p; p = p->next) {
		const tagver_t r = p->rhs;
		if (r != TAGVER_ZERO) {
			vals[r].clear();
			vals[r].push_back(r);
		}
	}

	// find interference list for LHS of each command
	for (const tcmd_t *p = cmd; p; p = p->next) {
		const tagver_t l = p->lhs, r = p->rhs, *h = p->history;
		vals_t &vl = vals[l], &vr = vals[r];

		// alive after this command
		memcpy(buf, live, nver * sizeof(bool));
		cfg_t::live_through_bblock(p->next, buf);

		// if copy command, exclude RHS
		if (tcmd_t::iscopy(p)) buf[r] = false;

		// update value of current command's LHS
		if (tcmd_t::iscopy(p)) {
			vl = vr;
		} else if (tcmd_t::isset(p)) {
			vl.clear();
			vl.push_back(*h);
		} else {
			if (l != r) vl = vr;
			for (; *++h != TAGVER_ZERO;); // history is reversed
			for (; h-- != p->history;) {
				vl.push_back(*h);
			}
		}
		// Exclude from interference list all LHS from preceding commands
		// which value is equal to current LHS value. Subsequent commands
		// are ignored: if subsequent command that sets LHS to the same value
		// precedes any use of it, liveness propagation through basic block
		// would mark this LHS as dead and not interfering anyway; otherwise
		// (if use precedes setting to the same value), then it indeed
		// interferes with current LHS.
		for (const tcmd_t *q = cmd; q != p; q = q->next) {
			if (vals[q->lhs] == vl) {
				buf[q->lhs] = false;
			}
		}

		const size_t u = static_cast<size_t>(l);
		for (size_t v = 0; v < nver; ++v) {
			if (!buf[v]) continue;
			interf[u * nver + v] = interf[v * nver + u] = true;
		}
	}
}

} // namespace re2c
