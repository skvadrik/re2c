#include <string.h>

#include "src/ir/dfa/cfg/cfg.h"

namespace re2c
{

void cfg_t::liveness_analysis(const cfg_t &cfg, bool *live)
{
	const size_t nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1;
	const tagver_t *fins = cfg.dfa.finvers;
	bool *buf1 = new bool[nver];
	bool *buf2 = new bool[nver];

	/* note [control flow equations for tag liveness]
	 *
	 * Liveness in bblock B is given by control flow equations:
	 *     live-out(B) = union of live-in(C), for all successors C
	 *     live-in(B)  = live-out(B) except defined(B)
	 * Equations are solved by iteration until fix point.
	 *
	 * Live set can only grow on each iteration, it never shrinks.
	 * Initially all final tag versions used in rules are alive;
	 * we pre-calculate them and then only update table by adding
	 * new versions.
	 */

	memset(live, 0, cfg.nbbfin * nver * sizeof(bool));
	for (cfg_ix_t i = cfg.nbbarc; i < cfg.nbbfin; ++i) {
		const cfg_bb_t *b = cfg.bblocks + i;
		const Rule *r = b->rule;
		bool *l = &live[i * nver];

		// all final bblocks have USE tags, but no successors
		assert(r && b->succb == b->succe);

		for (size_t t = r->lvar; t < r->hvar; ++t) {
			l[fins[t]] = true;
		}
	}

	for (bool loop = true; loop;) {
		loop = false;

		for (cfg_ix_t i = 0; i < cfg.nbbarc; ++i) {
			const cfg_bb_t *b = cfg.bblocks + i;
			bool *old = &live[i * nver];

			// transition bblocks have no USE tags
			assert(!b->rule);

			memcpy(buf1, old, nver * sizeof(bool));
			for (cfg_ix_t *j = b->succb; j < b->succe; ++j) {
				const bool *l = &live[*j * nver];
				const tcmd_t *cmd = cfg.bblocks[*j].cmd;
				memcpy(buf2, l, nver * sizeof(bool));

				for (const tagsave_t *p = cmd->save; p; p = p->next) {
					buf2[p->ver] = false;
				}
				for (const tagcopy_t *p = cmd->copy; p; p = p->next) {
					if (l[p->lhs]) {
						buf2[p->lhs] = false;
					}
				}
				for (const tagcopy_t *p = cmd->copy; p; p = p->next) {
					if (l[p->lhs]) {
						buf2[p->rhs] = true;
					}
				}

				for (size_t v = 0; v < nver; ++v) {
					buf1[v] |= buf2[v];
				}
			}

			if (memcmp(old, buf1, nver * sizeof(bool)) != 0) {
				memcpy(old, buf1, nver * sizeof(bool));
				loop = true;
			}
		}
	}

	/* note [fallback tag liveness]
	 *
	 * Liveness of fallback tag is propagated forward from fallback
	 * state (see note [fallback states]) and until there remain
	 * any fallthrough paths from current state.
	 *
	 * Fallback version of tag is either backup copy of tag's final
	 * version, or (if there's no backup) the final version itself.
	 * Absence of backup means that final version is not overwritten,
	 * but still we should prevent it from merging with other tags
	 * (otherwise it may become overwritten).
	 */
	for (cfg_ix_t i = cfg.nbbfin; i < cfg.nbbfall; ++i) {
		const cfg_bb_t *b = cfg.bblocks + i;
		const Rule *r = b->rule;

		// all fallback bblocks have USE tags
		assert(r);

		memset(buf1, 0, nver * sizeof(bool));
		for (size_t t = r->lvar; t < r->hvar; ++t) {
			buf1[fins[t]] = true;
		}
		for (const tagsave_t *p = b->cmd->save; p; p = p->next) {
			buf1[p->ver] = false;
		}
		for (const tagcopy_t *p = b->cmd->copy; p; p = p->next) {
			buf1[p->lhs] = false;
			buf1[p->rhs] = true;
		}
		for (cfg_ix_t *j = b->succb; j < b->succe; ++j) {
			bool *liv = &live[*j * nver];
			for (size_t v = 0; v < nver; ++v) {
				liv[v] |= buf1[v];
			}
		}
	}

	delete[] buf1;
	delete[] buf2;
}

} // namespace re2c

