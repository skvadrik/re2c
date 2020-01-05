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
static void dump_history1(const history_t &history, std::set<int32_t> &used,
    hidx_t idx)
{
    if (idx == HROOT) return;
    used.insert(idx).second;
    dump_history1(history, used, history.node(idx).pred);
    fprintf(stderr, "->h%d", idx);
}

template<typename history_t>
static void dump_history2(const history_t &history, std::set<int32_t> &used,
    hidx_t idx, size_t target, hidx_t base)
{
    if (idx == HROOT) return;
    used.insert(idx).second;
    dump_history2(history, used, history.node(idx).pred, target, base);
    fprintf(stderr, "->hx%lu_%d", target, idx + base);
}

static inline uint32_t hash4(uint32_t h, uint32_t k)
{
    return h ^ ((h << 5) + (h >> 2) + k);
}

static inline uint32_t hash_path(const std::vector<uint32_t> &path)
{
    uint32_t h = 0;
    for (size_t i = 0; i < path.size(); ++i) {
        h = hash4(h, path[i]);
    }
    return h;
}

template<typename ctx_t>
dump_dfa_tree_t<ctx_t>::dump_dfa_tree_t(const ctx_t &ctx)
    : ctx(ctx)
    , origmap()
    , uniqidx(0)
    , used_nodes()
{
    if (!ctx.dc_opts->dump_dfa_tree) return;

    fprintf(stderr,
        "digraph tag_tree {\n"
        " rankdir=LR\n"
        " graph[style=rounded]\n"
        " node[shape=rectangle style=rounded fontname=Courier]\n"
        " node[height=0.2 width=0.2 margin=0.025]\n"
        " edge[arrowhead=vee arrowsize=0.5 fontname=Courier label=\"\"]\n"
        " fontname=Courier\n"
        " ranksep=0.25\n\n"
        " subgraph cluster_all {\n"
        "  style=invis\n\n");
}

template<typename ctx_t>
void dump_dfa_tree_t<ctx_t>::path_tree(const std::vector<uint32_t> &path,
    const std::vector<uint32_t> &syms, bool loop)
{
    const nfa_t &nfa = ctx.nfa;
    const typename ctx_t::history_t &history = ctx.history;
    const kernels_t &kernels = ctx.dc_kernels;
    std::set<const nfa_state_t *> active, active2;
    std::set<int32_t> used;
    const uint32_t pathlen = static_cast<uint32_t>(path.size());
    const size_t histsize = history.nodes.size();

    // real state index
    uint32_t target = path.back();

    // fake unique state index
    const uint32_t targetx = hash_path(syms);

    fprintf(stderr,
        " subgraph cluster_path_%u {\n"
        "  style=invis\n"
        "  void%u[label=\"S%u\" style=\"rounded,filled\" bgcolor=lightgray]\n",
        targetx, targetx, target);

    // active subses includes TNFA states that are backwards reachable from
    // the last DFA state on the path (it is used to prune deadend branches)
    const kernel_t *kernel = kernels[target];
    for (uint32_t i = 0; i < kernel->size; ++i) {
        active.insert(kernel->state[i]);
    }

    // unwind path tree from leaves to root
    for (uint32_t k = pathlen; k --> 0; ) {
        target = path[k];
        kernel = kernels[target];

        // fake unique history indices
        const hidx_t hidxbase = loop && k == pathlen - 1
            ? static_cast<hidx_t>(histsize) : 0;

        // pretty nodes for TNFA states
        for (std::set<const nfa_state_t*>::const_iterator i = active.begin();
                i != active.end(); ++i) {
            fprintf(stderr,
                "  nx%u_%u_%u"
                " [label=\"s%u\" style=\"rounded,filled\" bgcolor=lightgray]\n",
                targetx, k, index(nfa, *i), index(nfa, *i));
        }

        used.clear();

        for (uint32_t i = 0; i < kernel->size; ++i) {
            const nfa_state_t *x = kernel->state[i];
            if (active.find(x) == active.end()) continue;

            if (k == 0) {
                fprintf(stderr, "  void%u", targetx);
            }
            else {
                const uint32_t origin = path[k - 1], symbol = syms[k - 1];
                const origmap_t::key_type key = std::make_pair(origin, symbol);
                const nfa_state_t *y = origmap[key].at(i);
                active2.insert(y);
                fprintf(stderr, "  nx%u_%u_%u", targetx, k - 1, index(nfa, y));
            }
            dump_history2(history, used, kernel->thist[i], targetx, hidxbase);
            fprintf(stderr, "->nx%u_%u_%u\n", targetx, k, index(nfa, x));
        }

        active.swap(active2);
        active2.clear();

        // pretty nodes for tag history indices
        for (uint32_t i = 0; i < histsize; ++i) {
            const hidx_t idx = static_cast<hidx_t>(i);
            if (used.find(idx) != used.end()) {
                fprintf(stderr, "  hx%u_%d[label=\"%u\"]\n",
                    targetx, idx + hidxbase, history.nodes[i].info.idx);
            }
        }
    }

    fprintf(stderr, " }\n");
}

template<typename ctx_t>
dump_dfa_tree_t<ctx_t>::~dump_dfa_tree_t()
{
    if (!ctx.dc_opts->dump_dfa_tree) return;

    fprintf(stderr, " }\n");

    for (uint32_t i = 0; i < ctx.history.nodes.size(); ++i) {
        if (used_nodes.find(static_cast<int32_t>(i)) != used_nodes.end()) {
            fprintf(stderr, " h%d[label=\"%u\"]\n",
                i, ctx.history.nodes[i].info.idx);
        }
    }

    const size_t nkern = ctx.dc_kernels.size();
    const size_t nsym = ctx.dfa.nchars;
    std::vector<uint32_t> path; // states
    std::vector<uint32_t> syms; // symbols
    std::vector<uint32_t> sym(nkern);
    std::vector<uint8_t> been(nkern);

    path.push_back(0);
    been[0]++;

    for (; !path.empty(); ) {
        const size_t i = path.back();
        const bool loop = been[i] > 1;

        uint32_t c = sym[i];
        for (; c < nsym && ctx.dfa.states[i]->arcs[c] == dfa_t::NIL; ++c);

        if (c < nsym || loop) {
            syms.push_back(c);
            path_tree(path, syms, loop);
            syms.pop_back();
        }

        if (loop) {
            path.pop_back();
            syms.pop_back();
            been[i]--;
        }
        else if (c == nsym) {
            sym[i] = c;
            path.pop_back();
            syms.pop_back();
            been[i]--;
        }
        else {
            const size_t j = ctx.dfa.states[i]->arcs[c];
            path.push_back(static_cast<uint32_t>(j));
            syms.push_back(c);
            sym[i] = c + 1;
            been[j]++;
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
            "  subgraph cluster_void {\n"
            "   void[label=\" \" style=\"rounded,filled\"  bgcolor=lightgray]\n"
            "  }\n");
    }

    // start cluster for the current tag history tree
    fprintf(stderr,
        "  subgraph cluster%u {\n"
        "   label=\"%sS%u\"\n", targetx, isnew ? "" : "mapped to ", target);

    // align TNFA states vertically by assigning them equal rank
    fprintf(stderr,
        "   subgraph {\n"
        "    rank=same\n");
    for (c = b; c != e; ++c) {
        fprintf(stderr,
            "    n%u_%u [label=\"s%u\" style=\"rounded,filled\" bgcolor=lightgray]\n",
            targetx, index(nfa, c->state), index(nfa, c->state));
    }
    fprintf(stderr, "   }\n");
    fprintf(stderr, "   style=\"rounded%s\"\n", isnew ? "" : ",dotted");

    // transitions constituiting the tag history tree
    for (c = b; c != e; ++c) {
        if (origin == dfa_t::NIL) {
            fprintf(stderr, "   void");
        }
        else {
            fprintf(stderr, "   n%u_%u",
                origin, index(nfa, ctx.dc_kernels[origin]->state[c->origin]));
        }
        dump_history1(ctx.history, used_nodes, c->thist);
        fprintf(stderr, "->n%u_%u%s\n",
            targetx, index(nfa, c->state), isnew ? "" : " [style=dotted]");
    }

    // end cluster for the current tag history tree
    fprintf(stderr, "  }\n");

    // save TNFA origins for this TDFA state
    origins_t &origins = origmap[std::make_pair(origin, ctx.dc_symbol)];
    for (c = b; c != e; ++c) {
        const nfa_state_t *o = origin == dfa_t::NIL ? NULL
            : ctx.dc_kernels[origin]->state[c->origin];
        origins.push_back(o);
    }
}

} // namespace re2c

#endif // RE2C_DEBUG
