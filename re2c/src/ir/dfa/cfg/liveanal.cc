#include <string.h>

#include "src/ir/dfa/cfg/cfg.h"

namespace re2c
{

void tag_liveness(const cfg_t &cfg, bool *live)
{
	const size_t
		nbb = cfg.nbblock,
		nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1,
		ntag = cfg.dfa.tags.size();
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

	memset(live, 0, nbb * nver * sizeof(bool));
	for (cfg_ix_t i = 0; i < nbb; ++i) {
		const tagver_t *use = cfg.bblocks[i].use;
		if (!use) continue;

		bool *l = &live[i * nver];
		for (size_t t = 0; t < ntag; ++t) {
			const tagver_t u = use[t];
			if (u != TAGVER_ZERO) {
				l[u] = true;
			}
		}
	}

	for (bool loop = true; loop;) {
		loop = false;

		for (cfg_ix_t i = 0; i < nbb; ++i) {
			const cfg_bb_t *b = cfg.bblocks + i;
			if (b->use) continue;

			bool *old = &live[i * nver];
			memcpy(buf1, old, nver * sizeof(bool));
			for (cfg_ix_t *j = b->succb; j < b->succe; ++j) {
				const bool *l = &live[*j * nver];
				memcpy(buf2, l, nver * sizeof(bool));

				const tagsave_t *p = cfg.bblocks[*j].cmd->save;
				for (; p; p = p->next) {
					buf2[p->ver] = false;
				}

				// copy tags are only used for fallback tags,
				// their liveness is handled in a special way

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
	for (cfg_ix_t i = 0; i < nbb; ++i) {
		const cfg_bb_t *b = cfg.bblocks + i;
		if (!b->use) continue;

		memset(buf1, 0, nver * sizeof(bool));
		for (size_t t = 0; t < ntag; ++t) {
			const tagver_t u = b->use[t];
			if (u != TAGVER_ZERO) {
				buf1[u] = true;
			}
		}
		for (const tagsave_t *p = b->cmd->save; p; p = p->next) {
			buf1[p->ver] = false;
		}

		// in rule tags copies are swapped: LHS is the origin, RHS is backup
		for (const tagcopy_t *p = b->cmd->copy; p; p = p->next) {
			buf1[p->lhs] = false;
			buf1[p->rhs] = true;
		}

		// final bblock has no successors, instead it has the list
		// of all bblocks reachable by non-accepting DFA paths
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

