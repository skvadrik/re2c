#ifndef _RE2C_DFA_DETERMINIZATION_
#define _RE2C_DFA_DETERMINIZATION_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <queue>

#include "src/nfa/nfa.h"
#include "src/debug/debug.h"
#include "src/dfa/tagver_table.h"
#include "src/dfa/tag_history.h"
#include "src/util/forbid_copy.h"
#include "src/util/lookup.h"
#include "src/util/slab_allocator.h"


namespace re2c {

// fwd
struct opt_t;
struct Msg;
struct dfa_t;
struct tcmd_t;

typedef slab_allocator_t<1024 * 1024, sizeof(void*)> allocator_t;
typedef int32_t prectable_t;

struct clos_t
{
    nfa_state_t *state;
    uint32_t origin;
    uint32_t tvers; // vector of tag versions (including lookahead tags)
    hidx_t ttran; // history of transition tags
    hidx_t thist; // history of lookahead tags

    inline clos_t()
        : state(NULL), origin(0), tvers(0), ttran(0), thist(HROOT) {}
    inline clos_t(nfa_state_t *s, uint32_t o, uint32_t v, hidx_t t, hidx_t h)
        : state(s), origin(o), tvers(v), ttran(t), thist(h) {}
    inline clos_t(const clos_t &c, nfa_state_t *s)
        : state(s), origin(c.origin), tvers(c.tvers), ttran(c.ttran), thist(c.thist) {}
    inline clos_t(const clos_t &c, nfa_state_t *s, hidx_t h)
        : state(s), origin(c.origin), tvers(c.tvers), ttran(c.ttran), thist(h) {}
    static inline bool fin(const clos_t &c) { return c.state->type == nfa_state_t::FIN; }
    static inline bool ran(const clos_t &c) { return c.state->type == nfa_state_t::RAN; }
};

typedef std::vector<clos_t> closure_t;
typedef closure_t::iterator clositer_t;
typedef closure_t::const_iterator cclositer_t;
typedef closure_t::reverse_iterator rclositer_t;
typedef closure_t::const_reverse_iterator rcclositer_t;

struct newver_t
{
    size_t tag;
    tagver_t base;
    hidx_t history;
};

typedef std::map<uint64_t, int32_t> hc_cache_t; // 'hc' for history comparison
typedef std::vector<hc_cache_t> hc_caches_t;

template<typename history_t>
struct newver_cmp_t
{
    history_t &history;
    hc_caches_t &caches;

    newver_cmp_t(history_t &h, hc_caches_t &c): history(h), caches(c) {}
    bool operator()(const newver_t &, const newver_t &) const;
};

struct kernel_t
{
    size_t size;
    const prectable_t *prectbl;
    nfa_state_t **state;
    uint32_t *tvers; // tag versions
    hidx_t *thist; // lookahead tags

    FORBID_COPY(kernel_t);
};

struct kernel_buffers_t
{
    size_t maxsize;
    kernel_t *kernel;
    tagver_t cap; // capacity (greater or equal to max)
    tagver_t max; // maximal tag version
    char *memory;
    tagver_t *x2y;
    tagver_t *y2x;
    size_t *x2t;
    uint32_t *indegree;
    tcmd_t *backup_actions;

    explicit kernel_buffers_t(allocator_t &alc);
};

struct cmp_gtop_t
{
    inline bool operator() (const nfa_state_t *x, const nfa_state_t *y) const;
};

struct histleaf_t
{
    uint32_t coreid;
    uint32_t origin;
    int32_t hidx;
    int32_t height;
};

typedef lookup_t<const kernel_t*> kernels_t;
typedef std::priority_queue<nfa_state_t*, std::vector<nfa_state_t*>
    , cmp_gtop_t> gtop_heap_t;

template<sema_t SEMA>
struct determ_context_t
{
    typedef clos_t conf_t;
    typedef std::vector<conf_t> confset_t;
    typedef confset_t::iterator confiter_t;
    typedef confset_t::const_iterator cconfiter_t;
    typedef confset_t::reverse_iterator rconfiter_t;
    typedef confset_t::const_reverse_iterator rcconfiter_t;
    typedef typename history_type_t<SEMA, STRICT>::type history_t;
    typedef std::map<newver_t, tagver_t, newver_cmp_t<history_t> > newvers_t;

    // determinization input
    const opt_t               *dc_opts;        // options
    Msg                       &dc_msg;         // error messages and warnings
    const std::string         &dc_condname;    // the name of current condition (with -c)
    const nfa_t               &nfa;            // TNFA

    // determinization output
    dfa_t                     &dfa;            // resulting TDFA

    // temporary structures used by determinization
    allocator_t               dc_allocator;
    uint32_t                  dc_origin;       // from-state of the current transition
    uint32_t                  dc_target;       // to-state of the current transition
    uint32_t                  dc_symbol;       // alphabet symbol of the current transition
    tcmd_t                   *dc_actions;      // tag actions of the current transition
    tagver_table_t            dc_tagvertbl;
    history_t                 history;         // prefix trie of tag histories
    kernels_t                 dc_kernels;      // TDFA states under construction
    kernel_buffers_t          dc_buffers;
    hc_caches_t               dc_hc_caches;    // per-tag cache of history comparisons
    newvers_t                 dc_newvers;      // map of triples (tag, version, history) to new version
    tag_path_t                dc_path1;        // buffer 1 for tag history
    tag_path_t                dc_path2;        // buffer 2 for tag history
    tag_path_t                dc_path3;        // buffer 3 for tag history
    std::vector<uint32_t>     dc_tagcount;     // buffer for counting sort on tag history

    // tagged epsilon-closure
    confset_t reach;
    confset_t state;
    std::vector<nfa_state_t*> gor1_topsort; // stack used in GOR1 (POSIX closure)
    std::vector<nfa_state_t*> gor1_linear;  // stack used in GOR1 (POSIX closure)
    std::vector<nfa_state_t*> gtop_buffer;  // buffer used for heap in GTOP (POSIX closure)
    cmp_gtop_t gtop_cmp;                    // heap comparator used in GTOP (POSIX closure)
    gtop_heap_t gtop_heap;                  // heap used in GTOP (POSIX closure)

    // precedence table and auxilary data for POSIX disambiguation
    int32_t *newprectbl;
    const int32_t *oldprectbl;
    size_t oldprecdim;
    std::vector<histleaf_t> histlevel;
    std::vector<uint32_t> sortcores;
    std::vector<uint32_t> fincount;
    std::vector<int32_t> worklist;

    // debug
    dump_dfa_t dc_dump;
    closure_stats_t dc_clstats;

    determ_context_t(const opt_t *, Msg &, const std::string &, const nfa_t &, dfa_t &);
    ~determ_context_t();
    FORBID_COPY(determ_context_t);
};

typedef determ_context_t<POSIX> pdetctx_t;
typedef determ_context_t<LEFTMOST> ldetctx_t;

template<typename ctx_t> void tagged_epsilon_closure(ctx_t &ctx);
template<typename ctx_t> void find_state(ctx_t &ctx);

inline bool cmp_gtop_t::operator() (const nfa_state_t *x, const nfa_state_t *y) const
{
    return x->topord < y->topord;
}

} // namespace re2c

#endif // _RE2C_DFA_DETERMINIZATION_
