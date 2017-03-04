#include <stdio.h>

#include "src/dfa/cfg/cfg.h"

namespace re2c
{

void cfg_t::dump(const cfg_t &cfg, const bool *live)
{
	const tagver_t nver = cfg.dfa.maxtagver + 1;
	const size_t ntag = cfg.dfa.tags.size();

	fprintf(stderr, "digraph CFG {\n"
		"  rankdir=LR\n"
		"  node[shape=Mrecord fontname=Terminus height=0.2 width=0.2]\n"
		"  edge[arrowhead=vee fontname=Terminus]\n\n");

	for (cfg_ix_t i = 0; i < cfg.nbbfall; ++i, live += nver) {
		const cfg_bb_t *b = cfg.bblocks + i;

		fprintf(stderr, "  n%u [label=\"%u\\n", i, i);
		for (const tagsave_t *p = b->cmd->save; p; p = p->next) {
			fprintf(stderr, "%i ", p->ver);
		}
		for (const tagcopy_t *p = b->cmd->copy; p; p = p->next) {
			fprintf(stderr, "%i~%i ", p->lhs, p->rhs);
		}
		fprintf(stderr, "/");
		if (b->use) {
			for (size_t t = 0; t < ntag; ++t) {
				const tagver_t v = b->use[t];
				if (v != TAGVER_ZERO) {
					fprintf(stderr, "%i ", v);
				}
			}
		}

if (i < cfg.nbbfin) {
		fprintf(stderr, "\\nneed:");
		for (tagver_t v = 0; v < nver; ++v) {
			if (live[v]) {
				fprintf(stderr, " %i", v);
			}
		}
}

		fprintf(stderr, "\"]\n");

		const char *style = b->use ? "dotted" : "solid";
		for (cfg_ix_t *j = b->succb; j < b->succe; ++j) {
			fprintf(stderr, "  n%u -> n%u [style=%s]\n", i, *j, style);
		}
	}

	fprintf(stderr, "}\n");
}

} // namespace re2c

