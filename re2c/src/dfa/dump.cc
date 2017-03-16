#include <stdio.h>

#include "src/dfa/dump.h"

namespace re2c
{

static void dump_tcmd_or_tcid(const tcmd_t *tcmd, const tcid_t *tcid, size_t sym, const tcpool_t &tcpool);
static void dump_tcmd(const tagsave_t *s, const tagcopy_t *c);
static const char *tagname(const Tag &t);
static void dump_tags(const Tagpool &tagpool, size_t ttran);

dump_dfa_t::dump_dfa_t(const dfa_t &d, const Tagpool &pool, const nfa_t &n, bool dbg)
	: debug(dbg)
	, dfa(d)
	, tagpool(pool)
	, uniqidx(0)
	, base(n.states)
	, shadow(NULL)
{
	if (!debug) return;

	shadow = new closure_t;
	fprintf(stderr, "digraph DFA {\n"
		"  rankdir=LR\n"
		"  node[shape=plaintext fontname=fixed]\n"
		"  edge[arrowhead=vee fontname=fixed]\n\n");
}

dump_dfa_t::~dump_dfa_t()
{
	if (!debug) return;

	delete shadow;
	fprintf(stderr, "}\n");
}

uint32_t dump_dfa_t::index(const nfa_state_t *s)
{
	return static_cast<uint32_t>(s - base);
}

void dump_dfa_t::closure_tags(cclositer_t c, bool shadowed)
{
	if (!debug) return;
	if (c->tvers == ZERO_TAGS) return;

	const tagver_t *vers = tagpool[c->tvers];
	const size_t ntag = tagpool.ntags;
	for (size_t t = 0; t < ntag; ++t) {
		const Tag &tag = dfa.tags[t];

		fprintf(stderr, " %s", tagname(tag));

		const tagver_t v = vers[t];
		if (v == TAGVER_BOTTOM) {
			fprintf(stderr, "&darr;");
		} else if (v == TAGVER_CURSOR) {
			fprintf(stderr, "&uarr;");
		} else {
			fprintf(stderr, "%d", abs(v));
		}

		if (!shadowed && capture(tag)) {
			fprintf(stderr, "[%d]", tagpool[c->order][t]);
		}
	}
}

void dump_dfa_t::closure(const closure_t &clos, uint32_t state, bool isnew)
{
	if (!debug) return;

	const char
		*style = isnew ? "" : " STYLE=\"dotted\"",
		*color = " COLOR=\"lightgray\"";

	fprintf(stderr, "  %s%u [label=<<TABLE"
		" BORDER=\"0\""
		" CELLBORDER=\"1\""
		">", isnew ? "" : "i", state);

	for (cclositer_t b = shadow->begin(), c = b; c != shadow->end(); ++c) {
		fprintf(stderr, "<TR><TD ALIGN=\"left\" PORT=\"_%u_%ld\"%s%s><FONT%s>%u",
			index(c->state), c - b, color, style, color, index(c->state));
		closure_tags(c, true);
		fprintf(stderr, "</FONT></TD></TR>");
	}
	if (!shadow->empty()) {
		fprintf(stderr, "<TR><TD BORDER=\"0\"></TD></TR>");
	}
	for (cclositer_t c = clos.begin(); c != clos.end(); ++c) {
		fprintf(stderr, "<TR><TD ALIGN=\"left\" PORT=\"%u\"%s>%u",
			index(c->state), style, index(c->state));
		closure_tags(c, true);
		fprintf(stderr, "</TD></TR>");
	}
	fprintf(stderr, "</TABLE>>]\n");
}

void dump_dfa_t::state0(const closure_t &clos)
{
	if (!debug) return;

	closure(clos, 0, true);
	fprintf(stderr, "  void [shape=point]\n");
	for (cclositer_t c = shadow->begin(); c != shadow->end(); ++c) {
		fprintf(stderr, "  void -> 0:_%u_%ld:w [style=dotted color=lightgray fontcolor=lightgray label=\"", index(c->state), c - shadow->begin());
		dump_tags(tagpool, c->ttran);
		fprintf(stderr, "\"]\n");
	}
	for (cclositer_t c = clos.begin(); c != clos.end(); ++c) {
		fprintf(stderr, "  void -> 0:%u:w [style=dotted label=\"", index(c->state));
		dump_tags(tagpool, c->ttran);
		fprintf(stderr, "\"]\n");
	}
}

void dump_dfa_t::state(const closure_t &clos, size_t state, size_t symbol, bool isnew)
{
	if (!debug) return;

	const dfa_state_t *s = dfa.states[state];
	const size_t state2 = s->arcs[symbol];

	if (state2 == dfa_t::NIL) return;

	const tcmd_t &cmd = s->tcmd[symbol];
	const uint32_t
		a = static_cast<uint32_t>(symbol),
		x = static_cast<uint32_t>(state),
		y = static_cast<uint32_t>(state2),
		z = isnew ? y : ++uniqidx;
	const char *prefix = isnew ? "" : "i";

	closure(clos, z, isnew);
	if (!isnew) {
		fprintf(stderr, "  i%u [style=dotted]\n"
			"  i%u:s -> %u:s [style=dotted label=\"", z, z, y);
		dump_tcmd(cmd.save, cmd.copy);
		fprintf(stderr, "\"]\n");
	}
	for (cclositer_t b = shadow->begin(), c = b; c != shadow->end(); ++c) {
		fprintf(stderr, "  %u:%u:e -> %s%u:_%u_%ld:w [color=lightgray fontcolor=lightgray label=\"%u",
			x, index(c->origin), prefix, z, index(c->state), c - b, a);
		dump_tags(tagpool, c->ttran);
		fprintf(stderr, "\"]\n");
	}
	for (cclositer_t c = clos.begin(); c != clos.end(); ++c) {
		fprintf(stderr, "  %u:%u:e -> %s%u:%u:w [label=\"%u",
			x, index(c->origin), prefix, z, index(c->state), a);
		dump_tags(tagpool, c->ttran);
		fprintf(stderr, "\"]\n");
	}
}

void dump_dfa_t::final(size_t state, const nfa_state_t *port)
{
	if (!debug) return;

	const dfa_state_t *s = dfa.states[state];
	const Rule &r = dfa.rules[s->rule];
	const tcmd_t &cmd = s->tcmd[dfa.nchars];
	const uint32_t x = static_cast<uint32_t>(state);

	fprintf(stderr, "  r%u [shape=none label=\"(", x);
	for (size_t t = r.ltag; t < r.htag; ++t) {
		if (t > r.ltag) fprintf(stderr, " ");
		fprintf(stderr, "%s%d", tagname(dfa.tags[t]), abs(dfa.finvers[t]));
	}
	fprintf(stderr, ")\"]\n");

	fprintf(stderr, "  %u:%u:e -> r%u [style=dotted label=\"", x, index(port), x);
	dump_tcmd(cmd.save, cmd.copy);
	fprintf(stderr, "\"]\n");
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

	// initializer
	fprintf(stderr,
		"  n [shape=point]"
		"  n -> n0 [style=dotted label=\"");
	dump_tcmd_or_tcid(dfa.tcmd0, dfa.tcid0, 0, dfa.tcpool);
	fprintf(stderr, "\"]\n");

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
			dump_tcmd_or_tcid(s->tcmd, s->tcid, nsym, dfa.tcpool);

			fprintf(stderr, "(");
			for (size_t t = r.ltag; t < r.htag; ++t) {
				if (t > r.ltag) fprintf(stderr, " ");
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
				dump_tcmd_or_tcid(s->tcmd, s->tcid, c, dfa.tcpool);
				fprintf(stderr, "\"]\n");
			}
		}
	}

	fprintf(stderr, "}\n");
}

void dump_tcmd_or_tcid(const tcmd_t *tcmd, const tcid_t *tcid,
	size_t sym, const tcpool_t &tcpool)
{
	if (tcmd) {
		const tcmd_t &cmd = tcmd[sym];
		dump_tcmd(cmd.save, cmd.copy);
	} else {
		const tccmd_t &cmd = tcpool[tcid[sym]];
		dump_tcmd(cmd.save, cmd.copy);
	}
}

void dump_tcmd(const tagsave_t *s, const tagcopy_t *c)
{
	if (!s && !c) return;

	fprintf(stderr, "/");
	for (; c; c = c->next) {
		fprintf(stderr, "%d=%d ", c->lhs, c->rhs);
	}
	for (; s; s = s->next) {
		fprintf(stderr, "%d%s ", s->ver, s->bottom ? "&darr;" : "&uarr;");
	}
}

const char *tagname(const Tag &t)
{
	return t.name ? t.name->c_str() : "";
}

void dump_tags(const Tagpool &tagpool, size_t ttran)
{
	if (ttran == ZERO_TAGS) return;

	fprintf(stderr, "/");
	const tagver_t *tran = tagpool[ttran];
	for (size_t t = 0; t < tagpool.ntags; ++t) {
		const tagver_t v = tran[t];
		if (v < TAGVER_ZERO) {
			fprintf(stderr, "%d&darr; ", -v);
		} else if (v > TAGVER_ZERO) {
			fprintf(stderr, "%d&uarr; ", v);
		}
	}
}

} // namespace re2c
