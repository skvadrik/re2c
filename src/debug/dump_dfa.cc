#ifdef RE2C_DEBUG

#include <stdio.h>
#include <algorithm>
#include <string>
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
#include "src/util/check.h"

namespace re2c {

template<typename ctx_t>
static void dump_history(const std::vector<Tag>&, const typename ctx_t::history_t&, hidx_t);
template<typename ctx_t>
static void dump_tags(const tagver_table_t&, const typename ctx_t::history_t&, hidx_t, uint32_t);
static void dump_tcmd_or_tcid(tcmd_t* const*, const tcid_t*, size_t, const tcpool_t&);
static const char* tagname(const Tag&);

// explicit instantiation for context types
template void dump_dfa_t::state<pdetctx_t>(const pdetctx_t& ctx, bool isnew);
template void dump_dfa_t::state<ldetctx_t>(const ldetctx_t& ctx, bool isnew);
template void dump_clstats<pdetctx_t>(const pdetctx_t&);
template void dump_clstats<ldetctx_t>(const ldetctx_t&);
template void reset_clstats<pdetctx_t>(pdetctx_t&);
template void reset_clstats<ldetctx_t>(ldetctx_t&);

dump_dfa_t::dump_dfa_t(const opt_t* opts): debug(opts->dump_dfa_raw), uniqidx(0) {
    if (!debug) return;

    fprintf(stderr,
            "digraph DFA {\n"
            "  rankdir=LR\n"
            "  node[shape=plaintext fontname=Courier]\n"
            "  edge[arrowhead=vee fontname=Courier]\n\n");
}

dump_dfa_t::~dump_dfa_t() {
    if (!debug) return;

    fprintf(stderr, "}\n");
}

template<typename ctx_t>
void dump_dfa_t::state(const ctx_t& ctx, bool isnew) {
    if (!debug) return;

    const uint32_t origin = ctx.origin;
    const uint32_t target = ctx.target;
    const uint32_t symbol = ctx.symbol;
    const Tdfa& dfa = ctx.dfa;
    const tagver_table_t& tvtbl = ctx.tagvertbl;
    const typename ctx_t::history_t& thist = ctx.history;
    uint32_t i;

    if (target == Tdfa::NIL) return;

    const uint32_t state = isnew ? target : ++uniqidx;
    const char* prefix = isnew ? "" : "i";
    const char* style = isnew ? "" : " STYLE=\"dotted\"";

    // closure
    fprintf(stderr, "  %s%u [label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\">", prefix, state);
    i = 0;
    for (const clos_t& c : ctx.state) {
        fprintf(stderr, "<TR><TD ALIGN=\"left\" PORT=\"%u\"%s>%u", i, style, c.state->topord);

        if (c.tvers != ZERO_TAGS) {
            const tagver_t* vers = tvtbl[c.tvers];
            const size_t ntag = ctx.tags.size();

            for (size_t t = 0; t < ntag; ++t) {
                fprintf(stderr, " %s%d", tagname(ctx.tags[t]), abs(vers[t]));
            }

            if (c.thist != HROOT) {
                dump_history<ctx_t>(ctx.tags, thist, c.thist);
            }
        }

        fprintf(stderr, "</TD></TR>");
        ++i;
    }
    fprintf(stderr, "</TABLE>>]\n");

    // transitions (initial state)
    if (origin == Tdfa::NIL) {
        fprintf(stderr, "  void [shape=point]\n");

        uint32_t j = 0;
        for (const clos_t& c : ctx.state) {
            fprintf(stderr, "  void -> 0:%u:w [style=dotted label=\"", j);
            dump_tags<ctx_t>(tvtbl, thist, c.ttran, c.tvers);
            fprintf(stderr, "\"]\n");
            ++j;
        }
    }

    // transitions (other states)
    else {
        if (!isnew) {
            const TdfaState* o = dfa.states[origin];
            fprintf(stderr,
                    "  i%u [style=dotted]\n"
                    "  i%u:s -> %zu:s [style=dotted label=\"",
                    state, state, o->arcs[symbol]);
            dump_tcmd(o->tcmd[symbol]);
            fprintf(stderr, "\"]\n");
        }

        uint32_t j = 0;
        for (const clos_t& c : ctx.state) {
            fprintf(stderr,
                    "  %u:%u:e -> %s%u:%u:w [label=\"%u",
                    origin, c.origin, prefix, state, j, symbol);
            dump_tags<ctx_t>(tvtbl, thist, c.ttran, c.tvers);
            fprintf(stderr, "\"]\n");
            ++j;
        }
    }

    // if final state, dump finalizer
    const TdfaState* t = dfa.states[target];
    if (t->rule != Rule::NONE) {
        const Rule& r = ctx.rules[t->rule];
        const tcmd_t* cmd = t->tcmd[dfa.nchars];

        // see note [at most one final item per closure]
        cclositer_t b = ctx.state.begin(), e = ctx.state.end(), c = std::find_if(b, e, clos_t::fin);
        DCHECK(c != e);

        fprintf(stderr, "  r%u [shape=none label=\"(", state);
        for (size_t j = r.ltag; j < r.htag; ++j) {
            if (j > r.ltag) fprintf(stderr, " ");
            fprintf(stderr, "%s%d", tagname(ctx.tags[j]), abs(dfa.finvers[j]));
        }
        fprintf(stderr, ")\"]\n");

        fprintf(stderr, "  %u:%td:e -> r%u [style=dotted label=\"", state, c - b, state);
        dump_tcmd(cmd);
        fprintf(stderr, "\"]\n");
    }
}

template<typename ctx_t>
void dump_history(const std::vector<Tag>& tags, const typename ctx_t::history_t& h, hidx_t i) {
    if (i == HROOT) {
        fprintf(stderr, " /");
        return;
    }

    const typename ctx_t::history_t::node_t& n = h.node(i);
    dump_history<ctx_t>(tags, h, n.pred);
    dump_tag(tags[n.info.idx], n.info.neg);
    fprintf(stderr, " ");
}

void dump_dfa(const Tdfa& dfa) {
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
            "  n -> n0 [style=dotted label=\"\"]\n");

    for (uint32_t i = 0; i < nstate; ++i) {
        const TdfaState* s = dfa.states[i];

        // state
        fprintf(stderr, "  n%u [height=0.2 width=0.2 label=\"%u", i, i);
        fprintf(stderr, "\"]\n");

        // finalizer
        if (s->rule != Rule::NONE) {
            const Rule& r = dfa.rules[s->rule];

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

            fprintf(stderr, "\"] n%u:s -> dr%u:n [style=dotted minlen=0]}\n", i, i);
        }

        // transitions
        for (uint32_t c = 0; c < nsym; ++c) {
            const size_t j = s->arcs[c];
            if (j != Tdfa::NIL) {
                fprintf(stderr, "  n%u -> n%zu [label=\"%u", i, j, c);
                dump_tcmd_or_tcid(s->tcmd, s->tcid, c, dfa.tcpool);
                fprintf(stderr, "\"]\n");
            }
        }
    }

    fprintf(stderr, "}\n");
}

void dump_tcmd_or_tcid(
        tcmd_t* const* tcmd, const tcid_t* tcid, size_t sym, const tcpool_t& tcpool) {
    const tcmd_t* cmd = tcmd ? tcmd[sym] : tcpool[tcid[sym]];
    dump_tcmd(cmd);
}

void dump_tcmd(const tcmd_t* p) {
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

const char* tagname(const Tag& t) {
    return t.name ? t.name : "";
}

template<typename ctx_t>
void dump_tags(const tagver_table_t& tagvertbl,
               const typename ctx_t::history_t& taghistory,
               hidx_t ttran,
               uint32_t tvers) {
    if (ttran == HROOT) return;

    fprintf(stderr, "/");
    const tagver_t* vers = tagvertbl[tvers];
    for (size_t t = 0; t < tagvertbl.ntags; ++t) {

        if (last(taghistory, ttran, t) == TAGVER_ZERO) {
            continue;
        }

        fprintf(stderr, "%d", abs(vers[t]));
        for (hidx_t i = ttran; i != HROOT; ) {
            const typename ctx_t::history_t::node_t& n = taghistory.node(i);
            if (n.info.idx == t) {
                fprintf(stderr, n.info.neg ? "&darr;" : "&uarr;");
            }
            i = n.pred;
        }
        fprintf(stderr, " ");
    }
}

template<typename ctx_t>
void reset_clstats(ctx_t& ctx) {
    closure_stats_t& cs = ctx.clstats;
    cs.nscans = 0;
    cs.nprec = 0;
    cs.length = 0;
}

template<typename ctx_t>
void dump_clstats(const ctx_t& ctx) {
    const closure_stats_t& cs = ctx.clstats;
    if (ctx.opts->dump_closure_stats) {
        fprintf(stderr,
                "scans: %-10u prec: %-10u length: %-10zu\n",
                cs.nscans, cs.nprec, cs.length);
    }
}

} // namespace re2c

#endif // RE2C_DEBUG
