#include <string.h>

#include "src/dfa/cfg/cfg.h"

namespace re2c
{

static void interfere(const tcmd_t &cmd, const bool *live, bool *interf, bool *buf1, bool *buf2, size_t nver);

void cfg_t::interference(const cfg_t &cfg, const bool *live, bool *interf)
{
	const size_t nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1;
	bool *buf1 = new bool[nver];
	bool *buf2 = new bool[nver];
	const cfg_bb_t *b = cfg.bblocks, *e = b + cfg.nbbfin;

	memset(interf, 0, nver * nver * sizeof(bool));
	for (; b < e; ++b, live += nver) {
		interfere(*b->cmd, live, interf, buf1, buf2, nver);
	}

	delete[] buf1;
	delete[] buf2;
}

void interfere(const tcmd_t &cmd, const bool *live, bool *interf,
	bool *buf1, bool *buf2, size_t nver)
{
	// Each tag updated by 'save' command interferes with all tags that
	// are alive after this command, except tags set to the same value
	// by other 'save' commands (all tags are set either to bottom, or
	// to current input position).
	memcpy(buf1, live, nver * sizeof(bool));
	memcpy(buf2, live, nver * sizeof(bool));
	for (const tagsave_t *p = cmd.save; p; p = p->next) {
		if (p->bottom) {
			buf1[p->ver] = false;
		} else {
			buf2[p->ver] = false;
		}
	}
	for (const tagsave_t *p = cmd.save; p; p = p->next) {
		const size_t x = static_cast<size_t>(p->ver);
		for (size_t y = 0; y < nver; ++y) {
			const bool
				i1 =  p->bottom && buf1[y],
				i2 = !p->bottom && buf2[y];
			if (i1 || i2) {
				interf[x * nver + y] = interf[y * nver + x] = true;
			}
		}
	}

	// Each tag X updated by 'copy' command X = Y interferes with all
	// tags alive after this command except tags equal to Y. We don't
	// track which tags are equal to Y at this point, but at least we
	// can exclude Y itself and all tags assigned to Y by other 'copy'
	// commands. The set of tags alive after 'copy' commands:
	for (const tagsave_t *p = cmd.save; p; p = p->next) {
		buf1[p->ver] = false;
	}
	for (const tagcopy_t *p = cmd.copy; p; p = p->next) {
		const tagver_t r = p->rhs;

		// alive after this command: tags used by subsequent 'copy'
		// commands plus all tags alive before the first save command
		memcpy(buf2, buf1, nver * sizeof(bool));
		for (const tagcopy_t *q = p->next; q; q = q->next) {
			if (q->rhs != r) {
				buf2[q->rhs] = true;
			}
		}

		// exclude: tags equal to RHS of this command
		buf2[r] = false;
		for (const tagcopy_t *q = cmd.copy; q; q = q->next) {
			if (q->rhs == r) {
				buf2[q->lhs] = false;
			}
		}

		const size_t l = static_cast<size_t>(p->lhs);
		for (size_t v = 0; v < nver; ++v) {
			if (!buf2[v]) continue;
			interf[l * nver + v] = interf[v * nver + l] = true;
		}
	}
}

} // namespace re2c

