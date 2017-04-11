#include <stdio.h>

#include "src/dfa/dump.h"

namespace re2c
{

static void dump_tcmd_or_tcid(tcmd_t *const *tcmd, const tcid_t *tcid, size_t sym, const tcpool_t &tcpool);
static void dump_tcmd(const tcmd_t *p);
static const char *tagname(const Tag &t);
static void dump_tags(const Tagpool &tagpool, size_t ttran, size_t tvers);

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

void dump_dfa_t::closure_tags(cclositer_t c,
	const tagver_t *lookahead, bool shadowed)
{
	if (!debug) return;
	if (c->tvers == ZERO_TAGS) return;

	const tagver_t
		*look = tagpool[c->tlook],
		*vers = tagpool[c->tvers],
		*ord =  tagpool[c->order];
	const size_t ntag = tagpool.ntags;
	for (size_t t = 0; t < ntag; ++t) {
		const Tag &tag = dfa.tags[t];

		fprintf(stderr, " %s", tagname(tag));
		fprintf(stderr, "%d", abs(vers[t]));
		if (lookahead[t]) {
			const tagver_t l = tagpool.history.elem(look[t]);
			if (l == TAGVER_BOTTOM) {
				fprintf(stderr, " &darr;");
			} else if (l == TAGVER_CURSOR) {
				fprintf(stderr, " &uarr;");
			} else {
				fprintf(stderr, "  ");
			}
		}
		if (!shadowed && capture(tag)) {
			fprintf(stderr, "[%d]", ord[t]);
		}
	}
}

void dump_dfa_t::closure(const closure_t &clos, uint32_t state, bool isnew)
{
	if (!debug) return;

	cclositer_t c1 = clos.begin(), c2 = clos.end(), c,
		s1 = shadow->begin(), s2 = shadow->end(), s;
	const char
		*style = isnew ? "" : " STYLE=\"dotted\"",
		*color = " COLOR=\"lightgray\"";

	fprintf(stderr, "  %s%u [label=<<TABLE"
		" BORDER=\"0\""
		" CELLBORDER=\"1\""
		">", isnew ? "" : "i", state);

	tagver_t *look = tagpool.buffer;
	for (size_t t = 0; t < tagpool.ntags; ++t) {
		for (c = c1; c != c2 && tagpool.history.elem(tagpool[c->tlook][t]) == TAGVER_ZERO; ++c);
		for (s = s1; s != s2 && tagpool.history.elem(tagpool[s->tlook][t]) == TAGVER_ZERO; ++s);
		look[t] = c != c2 || s != s2;
	}

	for (s = s1; s != s2; ++s) {
		fprintf(stderr, "<TR><TD ALIGN=\"left\" PORT=\"_%u_%ld\"%s%s><FONT%s>%u",
			index(s->state), s - s1, color, style, color, index(s->state));
		closure_tags(s, look, true);
		fprintf(stderr, "</FONT></TD></TR>");
	}
	if (!shadow->empty()) {
		fprintf(stderr, "<TR><TD BORDER=\"0\"></TD></TR>");
	}
	for (c = c1; c != c2; ++c) {
		fprintf(stderr, "<TR><TD ALIGN=\"left\" PORT=\"%u\"%s>%u",
			index(c->state), style, index(c->state));
		closure_tags(c, look, true);
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
		dump_tags(tagpool, c->ttran, c->tvers);
		fprintf(stderr, "\"]\n");
	}
	for (cclositer_t c = clos.begin(); c != clos.end(); ++c) {
		fprintf(stderr, "  void -> 0:%u:w [style=dotted label=\"", index(c->state));
		dump_tags(tagpool, c->ttran, c->tvers);
		fprintf(stderr, "\"]\n");
	}
}

void dump_dfa_t::state(const closure_t &clos, size_t state, size_t symbol, bool isnew)
{
	if (!debug) return;

	const dfa_state_t *s = dfa.states[state];
	const size_t state2 = s->arcs[symbol];

	if (state2 == dfa_t::NIL) return;

	const tcmd_t *cmd = s->tcmd[symbol];
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
		dump_tcmd(cmd);
		fprintf(stderr, "\"]\n");
	}
	for (cclositer_t b = shadow->begin(), c = b; c != shadow->end(); ++c) {
		fprintf(stderr, "  %u:%u:e -> %s%u:_%u_%ld:w [color=lightgray fontcolor=lightgray label=\"%u",
			x, index(c->origin), prefix, z, index(c->state), c - b, a);
		dump_tags(tagpool, c->ttran, c->tvers);
		fprintf(stderr, "\"]\n");
	}
	for (cclositer_t c = clos.begin(); c != clos.end(); ++c) {
		fprintf(stderr, "  %u:%u:e -> %s%u:%u:w [label=\"%u",
			x, index(c->origin), prefix, z, index(c->state), a);
		dump_tags(tagpool, c->ttran, c->tvers);
		fprintf(stderr, "\"]\n");
	}
}

void dump_dfa_t::final(size_t state, const nfa_state_t *port)
{
	if (!debug) return;

	const dfa_state_t *s = dfa.states[state];
	const Rule &r = dfa.rules[s->rule];
	const tcmd_t *cmd = s->tcmd[dfa.nchars];
	const uint32_t x = static_cast<uint32_t>(state);

	fprintf(stderr, "  r%u [shape=none label=\"(", x);
	for (size_t t = r.ltag; t < r.htag; ++t) {
		if (t > r.ltag) fprintf(stderr, " ");
		fprintf(stderr, "%s%d", tagname(dfa.tags[t]), abs(dfa.finvers[t]));
	}
	fprintf(stderr, ")\"]\n");

	fprintf(stderr, "  %u:%u:e -> r%u [style=dotted label=\"", x, index(port), x);
	dump_tcmd(cmd);
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
	dump_tcmd_or_tcid(dfa.tcmd0 ? &dfa.tcmd0 : NULL, &dfa.tcid0, 0, dfa.tcpool);
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

void dump_tcmd_or_tcid(tcmd_t *const *tcmd, const tcid_t *tcid,
	size_t sym, const tcpool_t &tcpool)
{
	const tcmd_t *cmd = tcmd ? tcmd[sym] : tcpool[tcid[sym]];
	dump_tcmd(cmd);
}

void dump_tcmd(const tcmd_t *p)
{
	if (!p) return;

	fprintf(stderr, "/");
	for (; p; p = p->next) {
		const tagver_t l = p->lhs, r = p->rhs, *h = p->history;
		if (tcmd_t::iscopy(p)) {
			fprintf(stderr, "%d=%d ", l, r);
		} else {
			fprintf(stderr, "%d", l);
			if (r != TAGVER_ZERO) {
				fprintf(stderr, "=%d", r);
			}
			for (; *h != TAGVER_ZERO; ++h) {
				fprintf(stderr, "%s", *h == TAGVER_BOTTOM ? "&darr;" : "&uarr;");
			}
			fprintf(stderr, " ");
		}
	}
}

const char *tagname(const Tag &t)
{
	return t.name ? t.name->c_str() : "";
}

void dump_tags(const Tagpool &tagpool, size_t ttran, size_t tvers)
{
	if (ttran == ZERO_TAGS) return;

	fprintf(stderr, "/");
	const tagver_t
		*tran = tagpool[ttran],
		*vers = tagpool[tvers];
	for (size_t i = 0; i < tagpool.ntags; ++i) {
		tagver_t v = vers[i], t = tran[i];
		if (tagpool.history.elem(t) == TAGVER_ZERO) continue;
		fprintf(stderr, "%d", abs(v));
		for (; t != -1; t = tagpool.history.pred(t)) {
			if (tagpool.history.elem(t) < TAGVER_ZERO) {
				fprintf(stderr, "&darr;");
			} else if (t > TAGVER_ZERO) {
				fprintf(stderr, "&uarr;");
			}
		}
		fprintf(stderr, " ");
	}
}

} // namespace re2c
