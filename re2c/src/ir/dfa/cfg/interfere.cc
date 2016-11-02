#include <string.h>

#include "src/ir/dfa/cfg/cfg.h"

namespace re2c
{

static void interfere(const tcmd_t &cmd, bool *interf, bool *live, bool *buf, size_t nver);

void cfg_t::interference(const cfg_t &cfg, const bool *live, bool *interf)
{
	const size_t nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1;
	bool *buf1 = new bool[nver];
	bool *buf2 = new bool[nver];
	const cfg_bb_t *b = cfg.bblocks, *e = b + cfg.nbblock;

	memset(interf, 0, nver * nver * sizeof(bool));
	for (; b < e; ++b, live += nver) {
		memcpy(buf1, live, nver * sizeof(bool));
		interfere(*b->cmd, interf, buf1, buf2, nver);
	}

	delete[] buf1;
	delete[] buf2;
}

void interfere(const tcmd_t &cmd, bool *interf, bool *live, bool *buf,
	size_t nver)
{
	// Each tag updated by save command interferes with all tags
	// that are alive after this command, except those udated by
	// other save commands (all saved tags have the same value:
	// current input position). So the interfering set is exactly
	// the set of tags alive before the first save command.

	for (const tagsave_t *p = cmd.save; p; p = p->next) {
		live[p->ver] = false;
	}

	for (const tagsave_t *p = cmd.save; p; p = p->next) {
		const size_t x = static_cast<size_t>(p->ver);
		for (size_t y = 0; y < nver; ++y) {
			if (!live[y]) continue;
			interf[x * nver + y] = interf[y * nver + x] = true;
		}
	}

	// Each tag X updated by copy command X = Y interferes with
	// all tags alive after this command except tags equal to Y.
	// We don't track which tags are equal to Y at this point,
	// but at least we can exclude Y itself and all tags assigned
	// to Y by copy commands.
	for (const tagcopy_t *p = cmd.copy; p; p = p->next) {
		const tagver_t r = p->rhs;

		// alive after this command: tags used by subsequent copy
		// commands plus all tags alive before the first save command
		memcpy(buf, live, nver * sizeof(bool));
		for (const tagcopy_t *q = p->next; q; q = q->next) {
			if (q->rhs != r) {
				buf[q->rhs] = true;
			}
		}

		// exclude: tags equal to RHS of this command
		buf[r] = false;
		for (const tagcopy_t *q = cmd.copy; q; q = q->next) {
			if (q->rhs == r) {
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

