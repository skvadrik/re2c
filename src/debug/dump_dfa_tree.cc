#ifdef RE2C_DEBUG

#include "src/util/c99_stdint.h"
#include <stdio.h>

#include "src/debug/debug.h"
#include "src/dfa/determinization.h"
#include "src/dfa/tag_history.h"


namespace re2c {

// explicit specialization for context types
template dump_dfa_tree_t<pdetctx_t>::dump_dfa_tree_t(const pdetctx_t &ctx);
template dump_dfa_tree_t<ldetctx_t>::dump_dfa_tree_t(const ldetctx_t &ctx);
template dump_dfa_tree_t<pdetctx_t>::~dump_dfa_tree_t();
template dump_dfa_tree_t<ldetctx_t>::~dump_dfa_tree_t();
template void dump_dfa_tree_t<pdetctx_t>::state(bool isnew);
template void dump_dfa_tree_t<ldetctx_t>::state(bool isnew);

template<typename history_t>
static void dump_history(const history_t &history, std::set<int32_t> &used,
    hidx_t idx)
{
    if (idx == HROOT || !used.insert(idx).second) return;
    dump_history(history, used, history.node(idx).pred);
    fprintf(stderr, "->h%d", idx);
}

template<typename ctx_t>
dump_dfa_tree_t<ctx_t>::dump_dfa_tree_t(const ctx_t &ctx)
    : ctx(ctx)
    , uniqidx(0)
    , used_nodes()
{
    if (!ctx.dc_opts->dump_dfa_tree) return;

    fprintf(stderr,
        "digraph tag_tree {\n"
        "  rankdir=LR\n"
        "  graph[style=rounded]\n"
        "  node[shape=rectangle style=rounded fontname=Courier]\n"
        "  node[height=0.2 width=0.2 margin=0.025]\n"
        "  edge[arrowhead=vee arrowsize=0.5 fontname=Courier label=\"\"]\n"
        "  fontname=Courier\n"
        "  ranksep=0.25\n"
        "  compound=true\n\n");
}

template<typename ctx_t>
dump_dfa_tree_t<ctx_t>::~dump_dfa_tree_t()
{
    if (!ctx.dc_opts->dump_dfa_tree) return;

    for (uint32_t i = 0; i < ctx.history.nodes.size(); ++i) {
        if (used_nodes.find(static_cast<int32_t>(i)) != used_nodes.end()) {
            fprintf(stderr, " h%d[label=\"%u\"]\n", i, ctx.history.nodes[i].info.idx);
        }
    }

    fprintf(stderr, "}\n");
}

template<typename ctx_t>
void dump_dfa_tree_t<ctx_t>::state(bool isnew)
{
    if (!ctx.dc_opts->dump_dfa_tree) return;

    const nfa_t &nfa = ctx.nfa;
    cclositer_t b = ctx.state.begin(), e = ctx.state.end(), c;
    const uint32_t origin = ctx.dc_origin;
    const uint32_t target = ctx.dc_target;
    const uint32_t targetx = isnew ? target : ++uniqidx;

    if (target == dfa_t::NIL) return;

    // initial "void" node
    if (origin == dfa_t::NIL) {
        fprintf(stderr,
            " subgraph cluster_void {\n"
            "  style=invis\n"
            "  void[label=\" \" style=\"rounded,filled\"  bgcolor=lightgray]\n"
            " }\n");
    }

    // start cluster for the current tag history tree
    fprintf(stderr,
        " subgraph cluster%u {\n"
        "  label=\"%sS%u\"\n", targetx, isnew ? "" : "mapped to ", target);

    // align TNFA states vertically by assigning them equal rank
    fprintf(stderr,
        "  subgraph {\n"
        "   rank=same\n");
    for (c = b; c != e; ++c) {
        fprintf(stderr,
            "   n%u_%u [label=\"s%u\" style=\"rounded,filled\" bgcolor=lightgray]\n",
            targetx, index(nfa, c->state), index(nfa, c->state));
    }
    fprintf(stderr, "  }\n");

    // mapped states are marked as dotted
    if (!isnew) {
        fprintf(stderr, "  style=\"rounded,dotted\"\n");
    }

    // transitions constituiting the tag history tree
    for (c = b; c != e; ++c) {
        if (origin == dfa_t::NIL) {
            fprintf(stderr, "  void");
        }
        else {
            fprintf(stderr, "  n%u_%u",
                origin, index(nfa, ctx.dc_kernels[origin]->state[c->origin]));
        }
        dump_history(ctx.history, used_nodes, c->thist);
        fprintf(stderr, "->n%u_%u%s\n",
            targetx, index(nfa, c->state), isnew ? "" : " [style=dotted]");
    }

    // end cluster for the current tag history tree
    fprintf(stderr, " }\n");
}

} // namespace re2c

#endif // RE2C_DEBUG
