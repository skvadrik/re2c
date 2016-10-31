#include <string.h>

#include "src/ir/dfa/tag_optimize.h"

namespace re2c
{

void tag_liveness(const cfg_t &cfg, bool *live)
{
	const Tagpool &tagpool = cfg.dfa.tagpool;
	const size_t
		nbb = cfg.nbblock,
		nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1,
		ntag = tagpool.ntags;
	bool *buf1 = new bool[nver];
	bool *buf2 = new bool[nver];

	/* note [control flow equations for tag liveness]
	 *
	 * Tag liveness in basic block x is given by control-flow equations:
	 *
	 *     need-out(x) = use(x) + need-in(y), for all y successors of x
	 *     need-in(x) = need-out(x) - define(x)
	 *
	 * Equations are solved by iteration until fix point.
	 */
	memset(live, 0, nbb * nver * sizeof(bool));
	for (bool loop = true; loop;) {
		loop = false;

		for (cfg_ix_t i = 0; i < nbb; ++i) {
			const cfg_bb_t *b = cfg.bblocks + i;

			memset(buf1, 0, nver * sizeof(bool));
			if (b->use != TAGVER_ZERO) {
				// final bblock, no successors
				const tagver_t *use = tagpool[b->use];
				for (size_t t = 0; t < ntag; ++t) {
					const tagver_t u = use[t];
					if (u != TAGVER_ZERO) {
						buf1[u] = true;
					}
				}
			} else {
				// transition bblock, no final rule tags
				for (cfg_ix_t *j = b->succb; j < b->succe; ++j) {
					const bool *liv = &live[*j * nver];
					memcpy(buf2, liv, nver * sizeof(bool));

					for (const tagsave_t *p = cfg.bblocks[*j].cmd->save; p; p = p->next) {
						buf2[p->ver] = false;
					}

					// copy tags are only used for fallback tags,
					// their liveness is handled in a special way

					for (size_t v = 0; v < nver; ++v) {
						buf1[v] |= buf2[v];
					}
				}
			}

			bool *liv = &live[i * nver];
			if (memcmp(liv, buf1, nver * sizeof(bool)) != 0) {
				memcpy(liv, buf1, nver * sizeof(bool));
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

		if (b->use == TAGVER_ZERO) continue;

		const tagver_t *use = tagpool[b->use];
		memset(buf1, 0, nver * sizeof(bool));
		for (size_t t = 0; t < ntag; ++t) {
			const tagver_t u = use[t];
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

