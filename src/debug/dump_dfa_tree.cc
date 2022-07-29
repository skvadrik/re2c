#ifdef RE2C_DEBUG

#include <stdint.h>
#include <stdio.h>

#include "src/debug/debug.h"
#include "src/dfa/dfa.h"
#include "src/dfa/determinization.h"
#include "src/dfa/tag_history.h"
#include "src/options/opt.h"

namespace re2c {

// explicit instantiation for context types
template dump_dfa_tree_t<pdetctx_t>::dump_dfa_tree_t(const pdetctx_t& ctx);
template dump_dfa_tree_t<ldetctx_t>::dump_dfa_tree_t(const ldetctx_t& ctx);
template dump_dfa_tree_t<pdetctx_t>::~dump_dfa_tree_t();
template dump_dfa_tree_t<ldetctx_t>::~dump_dfa_tree_t();
template void dump_dfa_tree_t<pdetctx_t>::state(bool isnew);
template void dump_dfa_tree_t<ldetctx_t>::state(bool isnew);

template<typename history_t>
static void dump_history1(const history_t& history, std::set<int32_t>& used, hidx_t idx) {
    if (idx == HROOT) return;
    used.insert(idx);
    dump_history1(history, used, history.node(idx).pred);
    fprintf(stderr, "->h%d", idx);
}

template<typename history_t>
static void dump_history2(const history_t& history,
                          std::set<int32_t>& used,
                          hidx_t idx,
                          size_t target,
                          hidx_t base) {
    if (idx == HROOT) return;
    used.insert(idx);
    dump_history2(history, used, history.node(idx).pred, target, base);
    fprintf(stderr, "->hx%zu_%d", target, idx + base);
}

static inline uint32_t hash4(uint32_t h, uint32_t k) {
    return h ^ ((h << 5) + (h >> 2) + k);
}

static inline uint32_t hash_path(const std::vector<uint32_t>& path) {
    uint32_t h = 0;
    for (uint32_t i : path) {
        h = hash4(h, i);
    }
    return h;
}

template<typename ctx_t>
dump_dfa_tree_t<ctx_t>::dump_dfa_tree_t(const ctx_t& ctx)
    : ctx(ctx),
      origmap(),
      uniqidx(0),
      used_nodes() {
    if (!ctx.opts->dump_dfa_tree) return;

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
void dump_dfa_tree_t<ctx_t>::path_tree(const std::vector<uint32_t>& path,
                                       const std::vector<uint32_t>& syms,
                                       bool loop) {
    const typename ctx_t::history_t& history = ctx.history;
    const kernels_t& kernels = ctx.kernels;
    std::set<const TnfaState*> active, active2;
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

    // Active subses includes TNFA states that are backwards reachable from the last DFA state on
    // the path (it is used to prune deadend branches).
    const kernel_t* kernel = kernels[target];
    for (uint32_t i = 0; i < kernel->size; ++i) {
        active.insert(kernel->state[i]);
    }

    // unwind path tree from leaves to root
    for (uint32_t k = pathlen; k --> 0; ) {
        target = path[k];
        kernel = kernels[target];

        // fake unique history indices
        const hidx_t hidxbase = loop && k == pathlen - 1 ? static_cast<hidx_t>(histsize) : 0;

        // pretty nodes for TNFA states
        for (const TnfaState* s : active) {
            fprintf(stderr,
                    "  nx%u_%u_%u"
                    " [label=\"s%u\" style=\"rounded,filled\" bgcolor=lightgray]\n",
                    targetx, k, s->topord, s->topord);
        }

        used.clear();

        for (uint32_t i = 0; i < kernel->size; ++i) {
            const TnfaState* x = kernel->state[i];
            if (active.find(x) == active.end()) continue;

            if (k == 0) {
                fprintf(stderr, "  void%u", targetx);
            } else {
                const uint32_t origin = path[k - 1], symbol = syms[k - 1];
                const origmap_t::key_type key = std::make_pair(origin, symbol);
                const TnfaState* y = origmap[key].at(i);
                active2.insert(y);
                fprintf(stderr, "  nx%u_%u_%u", targetx, k - 1, y->topord);
            }
            dump_history2(history, used, kernel->thist[i], targetx, hidxbase);
            fprintf(stderr, "->nx%u_%u_%u\n", targetx, k, x->topord);
        }

        active.swap(active2);
        active2.clear();

        // pretty nodes for tag history indices
        for (uint32_t i = 0; i < histsize; ++i) {
            const hidx_t idx = static_cast<hidx_t>(i);
            if (used.find(idx) != used.end()) {
                const tag_info_t info = history.nodes[i].info;
                fprintf(stderr,
                        "  hx%u_%d[label=\"%s%u\"]\n",
                        targetx, idx + hidxbase, info.neg ? "-" : "", info.idx);
            }
        }
    }

    fprintf(stderr, " }\n");
}

template<typename ctx_t>
dump_dfa_tree_t<ctx_t>::~dump_dfa_tree_t() {
    if (!ctx.opts->dump_dfa_tree) return;

    fprintf(stderr, " }\n");

    for (uint32_t i = 0; i < ctx.history.nodes.size(); ++i) {
        if (used_nodes.find(static_cast<int32_t>(i)) != used_nodes.end()) {
            const tag_info_t info = ctx.history.nodes[i].info;
            fprintf(stderr, " h%d[label=\"%s%u\"]\n", i, info.neg ? "-" : "", info.idx);
        }
    }

    const size_t nkern = ctx.kernels.size();
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
        for (; c < nsym && ctx.dfa.states[i]->arcs[c] == Tdfa::NIL; ++c);

        if (c < nsym || loop) {
            syms.push_back(c);
            path_tree(path, syms, loop);
            syms.pop_back();
        }

        if (loop) {
            path.pop_back();
            syms.pop_back();
            been[i]--;
        } else if (c == nsym) {
            sym[i] = c;
            path.pop_back();
            syms.pop_back();
            been[i]--;
        } else {
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
void dump_dfa_tree_t<ctx_t>::state(bool isnew) {
    if (!ctx.opts->dump_dfa_tree) return;

    const uint32_t origin = ctx.origin;
    const uint32_t target = ctx.target;
    const uint32_t targetx = isnew ? target : ++uniqidx;

    if (target == Tdfa::NIL) return;

    // initial "void" node
    if (origin == Tdfa::NIL) {
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
    for (const clos_t& c : ctx.state) {
        fprintf(stderr,
                "    n%u_%u [label=\"s%u\" style=\"rounded,filled\" bgcolor=lightgray]\n",
                targetx, c.state->topord, c.state->topord);
    }
    fprintf(stderr, "   }\n");
    fprintf(stderr, "   style=\"rounded%s\"\n", isnew ? "" : ",dotted");

    // transitions constituiting the tag history tree
    for (const clos_t& c : ctx.state) {
        if (origin == Tdfa::NIL) {
            fprintf(stderr, "   void");
        } else {
            fprintf(stderr, "   n%u_%u", origin, ctx.kernels[origin]->state[c.origin]->topord);
        }
        dump_history1(ctx.history, used_nodes, c.thist);
        fprintf(stderr, "->n%u_%u%s\n", targetx, c.state->topord, isnew ? "" : " [style=dotted]");
    }

    // end cluster for the current tag history tree
    fprintf(stderr, "  }\n");

    // save TNFA origins for this TDFA state
    origins_t& origins = origmap[std::make_pair(origin, ctx.symbol)];
    for (const clos_t& c : ctx.state) {
        origins.push_back(origin == Tdfa::NIL ? nullptr : ctx.kernels[origin]->state[c.origin]);
    }
}

} // namespace re2c

#endif // RE2C_DEBUG
