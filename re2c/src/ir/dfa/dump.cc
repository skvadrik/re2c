#include <stdio.h>

#include "src/ir/dfa/dump.h"

namespace re2c
{

static void dump_tcmd(const dfa_t &dfa, const dfa_state_t *state, size_t sym)
{
	const tagsave_t *s;
	const tagcopy_t *c;

	if (state->tcmd) {
		const tcmd_t &cmd = state->tcmd[sym];
		s = cmd.save;
		c = cmd.copy;
	} else {
		const tccmd_t &cmd = dfa.tcpool[state->tcid[sym]];
		s = cmd.save;
		c = cmd.copy;
	}

	if (!s && !c) return;

	fprintf(stderr, "/");
	for (; c; c = c->next) {
		fprintf(stderr, "%d=%d ", c->lhs, c->rhs);
	}
	for (; s; s = s->next) {
		fprintf(stderr, "%d%s ", s->ver, s->bottom ? "?" : "");
	}
}

void dump_dfa(const dfa_t &dfa)
{
	const size_t
		nstate = dfa.states.size(),
		nsym = dfa.nchars;

	fprintf(stderr,
		"digraph DFA {\n"
		"  rankdir=LR\n"
		"  node[shape=Mrecord fontname=fixed]\n"
		"  edge[arrowhead=vee fontname=fixed]\n\n");

	for (uint32_t i = 0; i < nstate; ++i) {
		const dfa_state_t *s = dfa.states[i];

		// state
		fprintf(stderr, "  n%u [height=0.2 width=0.2 label=\"%u\"]\n", i, i);

		// finalizer
		if (s->rule != Rule::NONE) {
			const Rule &r = dfa.rules[s->rule];

			fprintf(stderr,
				"subgraph { rank=same"
				" n%u [style=filled fillcolor=lightgray]"
				" dr%u [shape=none label=\"",
				i, i);
			dump_tcmd(dfa, s, nsym);

			fprintf(stderr, "(");
			for (size_t t = r.lvar; t < r.hvar; ++t) {
				if (t > r.lvar) fprintf(stderr, " ");
				fprintf(stderr, "%d", dfa.finvers[t]);
			}
			fprintf(stderr, ")");

			fprintf(stderr, "\"]"
				" n%u:s -> dr%u:n [style=dotted minlen=0]}\n",
				i, i);
		}

		// transitions
		for (uint32_t c = 0; c < nsym; ++c) {
			const size_t j = s->arcs[c];
			if (j != dfa_t::NIL) {
				fprintf(stderr, "  n%u -> n%u [label=\"%u",
					i, static_cast<uint32_t>(j), c);
				dump_tcmd(dfa, s, c);
				fprintf(stderr, "\"]\n");
			}
		}
	}

	fprintf(stderr, "}\n");
}

} // namespace re2c
