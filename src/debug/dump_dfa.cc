#ifdef RE2C_DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <valarray>
#include <vector>

#include "src/options/opt.h"
#include "src/debug/debug.h"
#include "src/dfa/dfa.h"
#include "src/dfa/determinization.h"
#include "src/dfa/tag_history.h"
#include "src/dfa/tagver_table.h"
#include "src/dfa/tcmd.h"
#include "src/nfa/nfa.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"


namespace re2c {

template<typename ctx_t> static void dump_history(const dfa_t &, const typename ctx_t::history_t &, hidx_t);
template<typename ctx_t> static void dump_tags(const tagver_table_t &, const typename ctx_t::history_t &, hidx_t, uint32_t);
static void dump_tcmd_or_tcid(tcmd_t *const *, const tcid_t *, size_t, const tcpool_t &);
static const char *tagname(const Tag &);
template <typename ctx_t> static void dump_stacmd(const ctx_t &, const stacmd_t *);

// explicit specialization for context types
template void dump_dfa_t::state<pdetctx_t>(const pdetctx_t &ctx, bool isnew);
template void dump_dfa_t::state<ldetctx_t>(const ldetctx_t &ctx, bool isnew);
template void dump_clstats<pdetctx_t>(const pdetctx_t &);
template void dump_clstats<ldetctx_t>(const ldetctx_t &);
template void reset_clstats<pdetctx_t>(pdetctx_t &);
template void reset_clstats<ldetctx_t>(ldetctx_t &);

dump_dfa_t::dump_dfa_t(const opt_t *opts)
    : debug(opts->dump_dfa_raw)
    , uniqidx(0)
{
    if (!debug) return;

    fprintf(stderr, "digraph DFA {\n"
        "  rankdir=LR\n"
        "  node[shape=plaintext fontname=Courier]\n"
        "  edge[arrowhead=vee fontname=Courier]\n\n");
}

dump_dfa_t::~dump_dfa_t()
{
    if (!debug) return;

    fprintf(stderr, "}\n");
}

template<typename ctx_t>
void dump_dfa_t::state(const ctx_t &ctx, bool isnew)
{
    if (!debug) return;

    const closure_t &closure = ctx.state;
    cclositer_t b = closure.begin(), e = closure.end(), c;
    const uint32_t origin = ctx.dc_origin;
    const uint32_t target = ctx.dc_target;
    const uint32_t symbol = ctx.dc_symbol;
    const dfa_t &dfa = ctx.dfa;
    const tagver_table_t &tvtbl = ctx.dc_tagvertbl;
    const typename ctx_t::history_t &thist = ctx.history;
    uint32_t i;

    if (target == dfa_t::NIL) return;

    const uint32_t state = isnew ? target : ++uniqidx;
    const char *prefix = isnew ? "" : "i";
    const char *style = isnew ? "" : " STYLE=\"dotted\"";

    // closure
    fprintf(stderr, "  %s%u [label=<<TABLE"
        " BORDER=\"0\""
        " CELLBORDER=\"1\""
        ">", prefix, state);
    i = 0;
    for (c = b; c != e; ++c, ++i) {
        fprintf(stderr, "<TR><TD ALIGN=\"left\" PORT=\"%u\"%s>%u",
            i, style, static_cast<uint32_t>(c->state - ctx.nfa.states));

        if (c->tvers != ZERO_TAGS) {
            const tagver_t *vers = tvtbl[c->tvers];
            const size_t ntag = dfa.tags.size();

            for (size_t t = 0; t < ntag; ++t) {
                fprintf(stderr, " %s%d", tagname(dfa.tags[t]), abs(vers[t]));
            }

            if (c->thist != HROOT) {
                dump_history<ctx_t>(dfa, thist, c->thist);
            }
        }

        fprintf(stderr, "</TD></TR>");
    }
    if (ctx.dc_opts->stadfa) {
        fprintf(stderr, "<TR><TD>");
        dump_stacmd(ctx, ctx.stadfa_actions);
        fprintf(stderr, "</TD></TR>");
    }
    fprintf(stderr, "</TABLE>>]\n");

    // transitions (initial state)
    if (origin == dfa_t::NIL) {
        fprintf(stderr, "  void [shape=point]\n");

        uint32_t j = 0;
        for (c = b; c != e; ++c, ++j) {
            fprintf(stderr, "  void -> 0:%u:w [style=dotted label=\"", j);
            dump_tags<ctx_t>(tvtbl, thist, c->ttran, c->tvers);
            fprintf(stderr, "\"]\n");
        }
    }

    // transitions (other states)
    else {
        if (!isnew) {
            const dfa_state_t *o = dfa.states[origin];
            fprintf(stderr,
                "  i%u [style=dotted]\n"
                "  i%u:s -> %u:s [style=dotted label=\"",
                state, state, static_cast<uint32_t>(o->arcs[symbol]));
            dump_tcmd(o->tcmd[symbol]);
            fprintf(stderr, "\"]\n");
        }

        uint32_t j = 0;
        for (c = b; c != e; ++c, ++j) {
            fprintf(stderr,
                "  %u:%u:e -> %s%u:%u:w [label=\"%u",
                origin, c->origin, prefix, state, j, symbol);
            dump_tags<ctx_t>(tvtbl, thist, c->ttran, c->tvers);
            fprintf(stderr, "\"]\n");
        }
    }

    // if final state, dump finalizer
    const dfa_state_t *t = dfa.states[target];
    if (t->rule != Rule::NONE) {
        const Rule &r = dfa.rules[t->rule];
        const tcmd_t *cmd = t->tcmd[dfa.nchars];

        // see note [at most one final item per closure]
        c = std::find_if(b, e, clos_t::fin);
        DASSERT(c != e);

        fprintf(stderr, "  r%u [shape=none label=\"(", state);
        for (size_t j = r.ltag; j < r.htag; ++j) {
            if (j > r.ltag) fprintf(stderr, " ");
            fprintf(stderr, "%s%d", tagname(dfa.tags[j]), abs(dfa.finvers[j]));
        }
        fprintf(stderr, ")\"]\n");

        fprintf(stderr, "  %u:%u:e -> r%u [style=dotted label=\"",
            state, static_cast<uint32_t>(c - b), state);
        dump_tcmd(cmd);
        fprintf(stderr, "\"]\n");
    }
}

template<typename ctx_t>
void dump_history(const dfa_t &dfa
    , const typename ctx_t::history_t &h, hidx_t i)
{
    if (i == HROOT) {
        fprintf(stderr, " /");
        return;
    }

    const typename ctx_t::history_t::node_t &n = h.node(i);
    dump_history<ctx_t>(dfa, h, n.pred);
    dump_tag(dfa.tags[n.info.idx], n.info.neg);
    fprintf(stderr, " ");
}

void dump_dfa(const dfa_t &dfa)
{
    const size_t
        nstate = dfa.states.size(),
        nsym = dfa.nchars;

    fprintf(stderr,
        "digraph DFA {\n"
        "  rankdir=LR\n"
        "  node[fontname=Courier]\n"
        "  edge[arrowhead=vee fontname=Courier]\n\n");

    // initializer
    fprintf(stderr,
        "  n [shape=point]"
        "  n -> n0 [style=dotted label=\"");
    dump_tcmd_or_tcid(dfa.tcmd0 ? &dfa.tcmd0 : NULL, &dfa.tcid0, 0, dfa.tcpool);
    fprintf(stderr, "\"]\n");

    for (uint32_t i = 0; i < nstate; ++i) {
        const dfa_state_t *s = dfa.states[i];

        // state
        fprintf(stderr, "  n%u [height=0.2 width=0.2 label=\"%u", i, i);
        dump_tcmd_or_tcid(s->stacmd ? &s->stacmd : NULL, &s->stacid, 0, dfa.tcpool);
        fprintf(stderr, "\"]\n");

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

template <typename ctx_t>
void dump_stacmd(const ctx_t &ctx, const stacmd_t *p)
{
    for (; p; p = p->next) {
        const tagver_t v = last(ctx.history, p->hist, p->tag);
        const uint32_t t = static_cast<uint32_t>(p->tag);

        switch (p->kind) {
        case stacmd_t::STORE:
            fprintf(stderr, "S(%u,%d,%d,%s)", t, p->lhs, p->rhs,
                v == TAGVER_BOTTOM ? "&darr;" : "&uarr;");
            break;
        case stacmd_t::TRANSFER:
            fprintf(stderr, "T(%u,%d,%d)", t, p->lhs, p->rhs);
            break;
        case stacmd_t::ACCEPT:
            if (v == TAGVER_CURSOR) {
                fprintf(stderr, "A(%u,%d,&uarr;)", t, p->rhs);
            }
            else if (v == TAGVER_BOTTOM) {
                fprintf(stderr, "A(%u,%d,&darr;)", t, p->rhs);
            }
            else {
                fprintf(stderr, "A(%u,%d)", t, p->rhs);
            }
            break;
        }
        if (p->next) fprintf(stderr, "<BR/>");
    }
}

const char *tagname(const Tag &t)
{
    return t.name ? t.name->c_str() : "";
}

template<typename ctx_t>
void dump_tags(const tagver_table_t &tagvertbl
    , const typename ctx_t::history_t &taghistory
    , hidx_t ttran, uint32_t tvers)
{
    if (ttran == HROOT) return;

    fprintf(stderr, "/");
    const tagver_t *vers = tagvertbl[tvers];
    for (size_t t = 0; t < tagvertbl.ntags; ++t) {

        if (last(taghistory, ttran, t) == TAGVER_ZERO) {
            continue;
        }

        fprintf(stderr, "%d", abs(vers[t]));
        for (hidx_t i = ttran; i != HROOT; ) {
            const typename ctx_t::history_t::node_t &n = taghistory.node(i);
            if (n.info.idx == t) {
                fprintf(stderr, n.info.neg ? "&darr;" : "&uarr;");
            }
            i = n.pred;
        }
        fprintf(stderr, " ");
    }
}

template<typename ctx_t>
void reset_clstats(ctx_t &ctx)
{
    closure_stats_t &cs = ctx.dc_clstats;
    cs.nscans = 0;
    cs.nprec = 0;
    cs.length = 0;
}

template<typename ctx_t>
void dump_clstats(const ctx_t &ctx)
{
    const closure_stats_t &cs = ctx.dc_clstats;
    if (ctx.dc_opts->dump_closure_stats) {
        fprintf(stderr, "scans: %-10u prec: %-10u length: %-10lu\n"
            , cs.nscans, cs.nprec, (unsigned long)cs.length);
    }
}

} // namespace re2c

#endif // RE2C_DEBUG
