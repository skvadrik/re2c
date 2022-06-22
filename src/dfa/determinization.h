#ifndef _RE2C_DFA_DETERMINIZATION_
#define _RE2C_DFA_DETERMINIZATION_

#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <queue>

#include "src/nfa/nfa.h"
#include "src/debug/debug.h"
#include "src/dfa/tagver_table.h"
#include "src/dfa/tag_history.h"
#include "src/regexp/tag.h"
#include "src/util/allocator.h"
#include "src/util/containers.h"
#include "src/util/forbid_copy.h"

namespace re2c {

struct opt_t;
struct dfa_t;
struct tcmd_t;
class Msg;

using allocator_t = slab_allocator_t<1024 * 1024, sizeof(void*)>;
using prectable_t = int32_t;

struct clos_t {
    nfa_state_t* state;
    uint32_t origin;
    uint32_t tvers; // vector of tag versions (including lookahead tags)
    hidx_t ttran; // history of transition tags
    hidx_t thist; // history of lookahead tags

    inline clos_t(): state(nullptr), origin(0), tvers(0), ttran(0), thist(HROOT) {}
    inline clos_t(nfa_state_t* s, uint32_t o, uint32_t v, hidx_t t, hidx_t h)
        : state(s), origin(o), tvers(v), ttran(t), thist(h) {}
    inline clos_t(const clos_t& c, nfa_state_t* s)
        : state(s), origin(c.origin), tvers(c.tvers), ttran(c.ttran), thist(c.thist) {}
    inline clos_t(const clos_t& c, nfa_state_t* s, hidx_t h)
        : state(s), origin(c.origin), tvers(c.tvers), ttran(c.ttran), thist(h) {}
    static inline bool fin(const clos_t& c) { return c.state->kind == nfa_state_t::Kind::FIN; }
    static inline bool ran(const clos_t& c) { return c.state->kind == nfa_state_t::Kind::RAN; }
};

using closure_t = std::vector<clos_t>;
using clositer_t = closure_t::iterator;
using cclositer_t = closure_t::const_iterator;
using rclositer_t = closure_t::reverse_iterator;
using rcclositer_t = closure_t::const_reverse_iterator;

struct newver_t {
    size_t tag;
    tagver_t base;
    hidx_t history;
};

using hc_cache_t = std::map<uint64_t, int32_t>; // 'hc' for history comparison
using hc_caches_t = std::vector<hc_cache_t>;

template<typename history_t>
struct newver_cmp_t {
    history_t& history;
    hc_caches_t& caches;

    newver_cmp_t(history_t& h, hc_caches_t& c): history(h), caches(c) {}
    bool operator()(const newver_t&, const newver_t&) const;
};

struct kernel_t {
    size_t size;                // the number of items in the kernel
    nfa_state_t** state;        // TNFA state for each item
    hidx_t* thist;              // lookahead tag history for each item
    const prectable_t* prectbl; // POSIX precedence table, if applicable
    uint32_t* tvers;            // TDFA: tag versions for each item

    FORBID_COPY(kernel_t);
};

struct kernel_buffers_t {
    size_t maxsize;
    kernel_t* kernel;
    tagver_t cap; // capacity (greater or equal to max)
    tagver_t max; // maximal tag version
    char* memory;
    tagver_t* x2y;
    tagver_t* y2x;
    size_t* x2t;
    uint32_t* indegree;
    tcmd_t* backup_actions;

    kernel_buffers_t();
};

struct cmp_gtop_t {
    inline bool operator() (const nfa_state_t* x, const nfa_state_t* y) const;
};

struct histleaf_t {
    uint32_t coreid;
    uint32_t origin;
    int32_t hidx;
    int32_t height;
};

using kernels_t = lookup_t<const kernel_t*>;
using gtop_heap_t = std::priority_queue<nfa_state_t*, std::vector<nfa_state_t*>, cmp_gtop_t>;

template<typename history_type_t>
struct determ_context_t {
    using conf_t = clos_t;
    using confset_t = std::vector<conf_t>;
    using confiter_t = confset_t::iterator;
    using cconfiter_t = confset_t::const_iterator;
    using rconfiter_t = confset_t::reverse_iterator;
    using rcconfiter_t = confset_t::const_reverse_iterator;
    using history_t = history_type_t;
    using newvers_t = std::map<newver_t, tagver_t, newver_cmp_t<history_t>>;

    // determinization input
    const opt_t* dc_opts;           // options
    Msg& dc_msg;                    // error messages and warnings
    const std::string& dc_condname; // the name of current condition (with -c)
    const nfa_t& nfa;               // TNFA

    // determinization output
    dfa_t& dfa; // the resulting TDFA

    // temporary structures used by determinization
    allocator_t dc_allocator;
    uint32_t dc_origin;                // from-state of the current transition
    uint32_t dc_target;                // to-state of the current transition
    uint32_t dc_symbol;                // alphabet symbol of the current transition
    tcmd_t* dc_actions;                // tag actions of the current transition
    tagver_table_t dc_tagvertbl;
    history_t history;                 // prefix trie of tag histories
    kernels_t dc_kernels;              // TDFA states under construction
    size_t kernels_total;              // sum total of all kernel sizes
    kernel_buffers_t dc_buffers;
    hc_caches_t dc_hc_caches;          // per-tag cache of history comparisons
    newvers_t dc_newvers;              // map of triples (tag, version, history) to new version
    tag_path_t dc_path1;               // buffer 1 for tag history
    tag_path_t dc_path2;               // buffer 2 for tag history
    tag_path_t dc_path3;               // buffer 3 for tag history
    std::vector<uint32_t> dc_tagcount; // buffer for counting sort on tag history

    // tagged epsilon-closure
    confset_t reach;
    confset_t state;
    std::vector<nfa_state_t*> gor1_topsort; // stack used in GOR1 (POSIX closure)
    std::vector<nfa_state_t*> gor1_linear;  // stack used in GOR1 (POSIX closure)
    std::vector<nfa_state_t*> gtop_buffer;  // buffer used for heap in GTOP (POSIX closure)
    cmp_gtop_t gtop_cmp;                    // heap comparator used in GTOP (POSIX closure)
    gtop_heap_t gtop_heap;                  // heap used in GTOP (POSIX closure)

    // precedence table and auxilary data for POSIX disambiguation
    int32_t* newprectbl;
    const int32_t* oldprectbl;
    size_t oldprecdim;
    histleaf_t* histlevel;
    std::vector<uint32_t> sortcores;
    std::vector<uint32_t> fincount;
    std::vector<int32_t> worklist;

    // debug
    dump_dfa_tree_t<determ_context_t> dump_dfa_tree;
    dump_dfa_t dc_dump;
    closure_stats_t dc_clstats;

    determ_context_t(const opt_t*, Msg&, const std::string&, const nfa_t&, dfa_t&);
    ~determ_context_t();
    FORBID_COPY(determ_context_t);
};

using pdetctx_t = determ_context_t<phistory_t>;
using ldetctx_t = determ_context_t<lhistory_t>;

template<typename ctx_t> void tagged_epsilon_closure(ctx_t& ctx);
template<typename ctx_t> void closure(ctx_t& ctx);
template<typename ctx_t> void find_state(ctx_t& ctx);
template<typename ctx_t, bool b> bool do_find_state(ctx_t& ctx);
template<typename ctx_t> void reach_on_symbol(ctx_t& ctx, uint32_t sym);
template<typename ctx_t> uint32_t init_tag_versions(ctx_t& ctx);
nfa_state_t* transition(nfa_state_t*, uint32_t);

inline bool cmp_gtop_t::operator() (const nfa_state_t* x, const nfa_state_t* y) const {
    return x->topord < y->topord;
}

} // namespace re2c

#endif // _RE2C_DFA_DETERMINIZATION_
