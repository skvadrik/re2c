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
struct Tdfa;
struct tcmd_t;
class Msg;

using prectable_t = int32_t;

struct clos_t {
    TnfaState* state;
    uint32_t origin;
    uint32_t tvers; // vector of tag versions (including lookahead tags)
    hidx_t ttran; // history of transition tags
    hidx_t thist; // history of lookahead tags

    inline clos_t(): state(nullptr), origin(0), tvers(0), ttran(0), thist(HROOT) {}
    inline clos_t(TnfaState* s, uint32_t o, uint32_t v, hidx_t t, hidx_t h)
        : state(s), origin(o), tvers(v), ttran(t), thist(h) {}
    inline clos_t(const clos_t& c, TnfaState* s)
        : state(s), origin(c.origin), tvers(c.tvers), ttran(c.ttran), thist(c.thist) {}
    inline clos_t(const clos_t& c, TnfaState* s, hidx_t h)
        : state(s), origin(c.origin), tvers(c.tvers), ttran(c.ttran), thist(h) {}
    static inline bool fin(const clos_t& c) { return c.state->kind == TnfaState::Kind::FIN; }
    static inline bool ran(const clos_t& c) { return c.state->kind == TnfaState::Kind::RAN; }
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

// TDFA state under construction ("kernel").
struct kernel_t {
    size_t size;                // kernel size (the number of TNFA states in it)
    TnfaState** state;          // TNFA states
    hidx_t* thist;              // lookahead tag histories for each TNFA state
    const prectable_t* prectbl; // POSIX precedence table, if applicable
    uint32_t* tvers;            // tag versions for each TNFA state

    FORBID_COPY(kernel_t);
};

// Temporary buffers used for manipulations on the kernels.
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

struct histleaf_t {
    uint32_t coreid;
    uint32_t origin;
    int32_t hidx;
    int32_t height;
};

using kernels_t = lookup_t<const kernel_t*>;

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

    const opt_t* opts;       // options
    Msg& msg;                // error messages and warnings
    const std::string& cond; // the name of current condition (with -c)

    // determinization input: TNFA
    TnfaState* nfa_root;

    // common data shared by all representations 
    IrAllocator ir_alc;
    std::vector<uint32_t> charset;
    std::vector<Rule> rules;
    std::vector<Tag> tags;

    // determinization output: TDFA
    Tdfa& dfa;

    // temporary structures used by determinization
    uint32_t origin;                // from-state of the current transition
    uint32_t target;                // to-state of the current transition
    uint32_t symbol;                // alphabet symbol of the current transition
    tcmd_t* actions;                // tag actions of the current transition
    tagver_table_t tagvertbl;
    history_t history;              // prefix trie of tag histories
    kernels_t kernels;              // TDFA states under construction
    size_t kernels_total;           // sum total of all kernel sizes
    kernel_buffers_t buffers;
    hc_caches_t hc_caches;          // per-tag cache of history comparisons
    newvers_t newvers;              // map of triples (tag, version, history) to new version
    tag_path_t path1;               // buffer 1 for tag history
    tag_path_t path2;               // buffer 2 for tag history
    tag_path_t path3;               // buffer 3 for tag history
    std::vector<uint32_t> tagcount; // buffer for counting sort on tag history

    // tagged epsilon-closure
    confset_t reach;
    confset_t state;
    std::vector<TnfaState*> gor1_topsort; // stack used in GOR1 (POSIX closure)
    std::vector<TnfaState*> gor1_linear;  // stack used in GOR1 (POSIX closure)

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
    dump_dfa_t dump;
    closure_stats_t clstats;

    determ_context_t(Tnfa&& nfa, Tdfa& dfa, const opt_t* opts, Msg& msg, const std::string& cond);
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
TnfaState* transition(TnfaState*, uint32_t);

} // namespace re2c

#endif // _RE2C_DFA_DETERMINIZATION_
