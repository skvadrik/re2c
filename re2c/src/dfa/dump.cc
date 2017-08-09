#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <valarray>
#include <vector>

#include "src/conf/opt.h"
#include "src/dfa/dfa.h"
#include "src/dfa/dump.h"
#include "src/dfa/tagpool.h"
#include "src/dfa/tagtree.h"
#include "src/dfa/tcmd.h"
#include "src/nfa/nfa.h"
#include "src/re/rule.h"
#include "src/re/tag.h"

namespace re2c
{

static void dump_tcmd_or_tcid(tcmd_t *const *tcmd, const tcid_t *tcid, size_t sym, const tcpool_t &tcpool);
static const char *tagname(const Tag &t);
static void dump_tags(const Tagpool &tagpool, hidx_t ttran, size_t tvers);

dump_dfa_t::dump_dfa_t(const dfa_t &d, const Tagpool &pool, const nfa_t &n)
	: debug(pool.opts->dump_dfa_raw)
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

uint32_t dump_dfa_t::index(const nfa_state_t *s) const
{
	return static_cast<uint32_t>(s - base);
}

static void dump_history(const dfa_t &dfa, const tagtree_t &h, hidx_t i)
{
	if (i == HROOT) {
		fprintf(stderr, " /");
		return;
	}

	dump_history(dfa, h, h.pred(i));

	const Tag &t = dfa.tags[h.tag(i)];
	const tagver_t v = h.elem(i);
	if (capture(t)) {
		fprintf(stderr, "%u", (uint32_t)t.ncap);
	} else if (!trailing(t)) {
		fprintf(stderr, "%s", t.name->c_str());
	}
	fprintf(stderr, v == TAGVER_BOTTOM ? "&darr;" : "&uarr;");
	fprintf(stderr, " ");
}

void dump_dfa_t::closure_tags(cclositer_t c)
{
	if (!debug) return;
	if (c->tvers == ZERO_TAGS) return;

	const hidx_t l = c->tlook;
	const tagver_t *vers = tagpool[c->tvers];
//	const tagver_t *ords = tagpool[c->order];
	const size_t ntag = tagpool.ntags;

	for (size_t t = 0; t < ntag; ++t) {
		fprintf(stderr, " %s%d", tagname(dfa.tags[t]), abs(vers[t]));
//		if (tagpool.opts->posix_captures) {
//			fprintf(stderr, "[%d]", ords[t]);
//		}
	}

	if (l != HROOT) {
		dump_history(dfa, tagpool.history, l);
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

	for (s = s1; s != s2; ++s) {
		fprintf(stderr, "<TR><TD ALIGN=\"left\" PORT=\"_%u_%d\"%s%s><FONT%s>%u",
			index(s->state), (int)(s - s1), color, style, color, index(s->state));
		closure_tags(s);
		fprintf(stderr, "</FONT></TD></TR>");
	}
	if (!shadow->empty()) {
		fprintf(stderr, "<TR><TD BORDER=\"0\"></TD></TR>");
	}
	for (c = c1; c != c2; ++c) {
		fprintf(stderr, "<TR><TD ALIGN=\"left\" PORT=\"%u\"%s>%u",
			index(c->state), style, index(c->state));
		closure_tags(c);
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
		fprintf(stderr, "  void -> 0:_%u_%d:w [style=dotted color=lightgray fontcolor=lightgray label=\"",
			index(c->state), (int)(c - shadow->begin()));
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
		fprintf(stderr, "  %u:%u:e -> %s%u:_%u_%d:w [color=lightgray fontcolor=lightgray label=\"%u",
			x, index(c->origin), prefix, z, index(c->state), (int)(c - b), a);
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

void dump_tags(const Tagpool &tagpool, hidx_t ttran, size_t tvers)
{
	if (ttran == HROOT) return;

	const tagver_t *vers = tagpool[tvers];
	const tagtree_t &h = tagpool.history;

	fprintf(stderr, "/");
	for (size_t i = 0; i < tagpool.ntags; ++i) {
		if (h.last(ttran, i) == TAGVER_ZERO) continue;

		fprintf(stderr, "%d", abs(vers[i]));
		for (hidx_t t = ttran; t != HROOT; t = h.pred(t)) {
			if (h.tag(t) != i) continue;
			if (h.elem(t) < TAGVER_ZERO) {
				fprintf(stderr, "&darr;");
			} else if (t > TAGVER_ZERO) {
				fprintf(stderr, "&uarr;");
			}
		}
		fprintf(stderr, " ");
	}
}

} // namespace re2c
