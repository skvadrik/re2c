#include <stdio.h>

#include "src/conf/opt.h"
#include "src/ir/dfa/dump.h"
#include "src/globals.h"

namespace re2c
{

static void dump_tcmd_or_tcid(const dfa_state_t *state, size_t sym, const tcpool_t &tcpool);
static void dump_tcmd(const tagsave_t *s, const tagcopy_t *c);
static const char *tagname(const VarTag &t);
static void dump_tags(const Tagpool &tagpool, size_t ttran, size_t tvers);

dump_dfa_t::dump_dfa_t(const dfa_t &d, const Tagpool &pool, const nfa_t &n)
	: debug(opts->dump_dfa_raw)
	, dfa(d)
	, tagpool(pool)
	, uniqidx(0)
	, base(n.states)
	, done()
{
	if (!debug) return;

	fprintf(stderr, "digraph DFA {\n"
		"  rankdir=LR\n"
		"  node[shape=Mrecord fontname=fixed]\n"
		"  edge[arrowhead=vee fontname=fixed]\n\n");
}

dump_dfa_t::~dump_dfa_t()
{
	if (!debug) return;

	fprintf(stderr, "}\n");
}

uint32_t dump_dfa_t::index(const nfa_state_t *s)
{
	return static_cast<uint32_t>(s - base);
}

void dump_dfa_t::closure(const closure_t &clos, uint32_t state, bool isnew)
{
	if (!debug) return;

	fprintf(stderr, "  %s%u [label=\"", isnew ? "" : "i", state);

	const size_t ntag = tagpool.ntags;
	cclositer_t b = clos.begin(), e = clos.end(), c;
	for (c = b; c != e; ++c) {

		if (c != b) fprintf(stderr, "|");
		fprintf(stderr, "<%u> %u", index(c->state), index(c->state));

		if (c->tvers != ZERO_TAGS) {
			fprintf(stderr, "/");
			const tagver_t *vers = tagpool[c->tvers];
			for (size_t t = 0; t < ntag; ++t) {
				if (t > 0) fprintf(stderr, " ");
				fprintf(stderr, "%s%d", tagname(dfa.vartags[t]), abs(vers[t]));
			}
		}

		if (c->tlook != ZERO_TAGS) {
			fprintf(stderr, "/");
			const tagver_t *look = tagpool[c->tlook];
			for (size_t t = 0; t < ntag; ++t) {
				const char *name = tagname(dfa.vartags[t]);
				switch (look[t]) {
					case TAGVER_ZERO: break;
					case TAGVER_CURSOR: fprintf(stderr, "%s ", name); break;
					case TAGVER_BOTTOM: fprintf(stderr, "%s? ", name); break;
				}
			}
		}
	}

	fprintf(stderr, "\"]\n");
}

void dump_dfa_t::state0(const closure_t &clos)
{
	if (!debug) return;

	done.insert(0);

	closure(clos, 0, true);

	fprintf(stderr, "  void [shape=point]\n");
	for (cclositer_t c = clos.begin(); c != clos.end(); ++c) {
		fprintf(stderr, "  void -> 0:%u:w [style=dotted label=\"", index(c->state));
		dump_tags(tagpool, c->ttran, c->tvers);
		fprintf(stderr, "\"]\n");
	}
}

void dump_dfa_t::state(const closure_t &clos, size_t state, size_t symbol)
{
	if (!debug) return;

	const dfa_state_t *s = dfa.states[state];
	const size_t state2 = s->arcs[symbol];

	if (state2 == dfa_t::NIL) return;

	const bool isnew = done.insert(state2).second;
	const tagcopy_t *copy = s->tcmd[symbol].copy;
	const uint32_t
		a = static_cast<uint32_t>(symbol),
		x = static_cast<uint32_t>(state),
		y = static_cast<uint32_t>(state2),
		z = isnew ? y : ++uniqidx;
	const char *prefix = isnew ? "" : "i";

	closure(clos, z, isnew);

	if (!isnew) {
		fprintf(stderr, "  i%u [style=dotted]\n"
			"  i%u -> %u [style=dotted label=\"", z, z, y);
		for (const tagcopy_t *p = copy; p; p = p->next) {
			fprintf(stderr, "%d=%d ", p->lhs, p->rhs);
		}
		fprintf(stderr, "\"]\n");
	}

	for (cclositer_t c = clos.begin(); c != clos.end(); ++c) {
		fprintf(stderr, "  %u:%u -> %s%u:%u [label=\"%u",
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
	const tcmd_t &cmd = s->tcmd[dfa.nchars];
	const uint32_t x = static_cast<uint32_t>(state);

	fprintf(stderr, "  r%u [shape=none label=\"(", x);
	for (size_t t = r.lvar; t < r.hvar; ++t) {
		if (t > r.lvar) fprintf(stderr, " ");
		fprintf(stderr, "%s%d", tagname(dfa.vartags[t]), abs(dfa.finvers[t]));
	}
	fprintf(stderr, ")\"]\n");

	fprintf(stderr, "  %u:%u -> r%u [style=dotted label=\"", x, index(port), x);
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
			dump_tcmd_or_tcid(s, nsym, dfa.tcpool);

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
				dump_tcmd_or_tcid(s, c, dfa.tcpool);
				fprintf(stderr, "\"]\n");
			}
		}
	}

	fprintf(stderr, "}\n");
}

void dump_tcmd_or_tcid(const dfa_state_t *state, size_t sym, const tcpool_t &tcpool)
{
	if (state->tcmd) {
		const tcmd_t &cmd = state->tcmd[sym];
		dump_tcmd(cmd.save, cmd.copy);
	} else {
		const tccmd_t &cmd = tcpool[state->tcid[sym]];
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
		fprintf(stderr, "%d%s ", s->ver, s->bottom ? "?" : "");
	}
}

const char *tagname(const VarTag &t)
{
	return t.name ? t.name->c_str() : "";
}

void dump_tags(const Tagpool &tagpool, size_t ttran, size_t tvers)
{
	if (ttran == ZERO_TAGS) return;

	const tagver_t
		*ts = tagpool[ttran],
		*vs = tagpool[tvers];

	fprintf(stderr, "/");
	for (size_t t = 0; t < tagpool.ntags; ++t) {
		const tagver_t v = abs(vs[t]);
		switch (ts[t]) {
			case TAGVER_ZERO: break;
			case TAGVER_CURSOR: fprintf(stderr, "%d ", v); break;
			case TAGVER_BOTTOM: fprintf(stderr, "%d? ", v); break;
		}
	}
}

} // namespace re2c
