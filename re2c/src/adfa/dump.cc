#include <stdio.h>

#include "src/adfa/dump.h"

namespace re2c
{

static void dump_adfa_tcmd(const tccmd_t &cmd)
{
	const tagsave_t *s = cmd.save;
	const tagcopy_t *c = cmd.copy;
	if (!s && !c) return;

	fprintf(stderr, "/");
	for (; c; c = c->next) {
		fprintf(stderr, "%d=%d ", c->lhs, c->rhs);
	}
	for (; s; s = s->next) {
		fprintf(stderr, "%d%s ", s->ver, s->bottom ? "?" : "");
	}
}

static void dump_adfa_range(uint32_t lower, uint32_t upper)
{
	fprintf(stderr, "%u", lower);
	if (--upper > lower) {
		fprintf(stderr, "-%u", upper);
	}
}

void dump_adfa(const DFA &dfa)
{
	fprintf(stderr,
		"digraph DFA {\n"
		"  rankdir=LR\n"
		"  node[shape=Mrecord fontname=fixed]\n"
		"  edge[arrowhead=vee fontname=fixed]\n\n");

	fprintf(stderr,
		"  n [shape=point]"
		"  n -> n%p [style=dotted label=\"", (void*)dfa.head);
	dump_adfa_tcmd(dfa.tcpool[dfa.tags0]);
	fprintf(stderr, "\"]\n");

	for (const State *s = dfa.head; s; s = s->next) {
		const char *attr;
		Action::type_t action = s->action.type;

		switch (action) {
			case Action::ACCEPT: attr = "style=filled fillcolor=gray"; break;
			case Action::RULE:   attr = "style=filled fillcolor=lightgray"; break;
			default:             attr = ""; break;
		}
		fprintf(stderr, "  n%p [height=0.2 width=0.2 label=\"", (void*)s);
		if (s->fill && action != Action::MOVE) {
			fprintf(stderr, "F(%u) ", (uint32_t)s->fill);
		}
		if (action == Action::RULE) {
			const Rule &r = dfa.rules[s->action.info.rule];
			for (size_t t = r.ltag; t < r.htag; ++t) {
				if (t > r.ltag) fprintf(stderr, " ");
				const std::string *name = dfa.tags[t].name;
				fprintf(stderr, "%s(%d)",
					name ? name->c_str() : "/", dfa.finvers[t]);
			}
		}
		dump_adfa_tcmd(dfa.tcpool[s->go.tags]);
		fprintf(stderr, "\" %s]\n", attr);

		if (action == Action::ACCEPT) {
			const accept_t &accept = *s->action.info.accepts;
			for (uint32_t i = 0; i < accept.size(); ++i) {
				fprintf(stderr, "  n%p -> n%p [label=\"",
					(void*)s, (void*)accept[i].first);
				dump_adfa_tcmd(dfa.tcpool[accept[i].second]);
				fprintf(stderr, "\" style=dotted]\n");
			}
		}

		const Span *x = s->go.span, *e = x + s->go.nSpans;
		for (uint32_t lb = 0; x < e; lb = x->ub, ++x) {
			if (!x->to) continue;

			bool eat = true;
			switch (x->to->action.type) {
				case Action::MOVE:
				case Action::RULE:
					attr = "style=dotted";
					eat = false;
					break;
				default:
					attr = "";
					break;
			}
			fprintf(stderr, "  n%p -> n%p [label=\"", (void*)s, (void*)x->to);
			if (eat) dump_adfa_range(lb, x->ub);
			dump_adfa_tcmd(dfa.tcpool[x->tags]);
			fprintf(stderr, "\" %s]\n", attr);
		}
	}

	fprintf(stderr, "}\n");
}

} // namespace re2c
