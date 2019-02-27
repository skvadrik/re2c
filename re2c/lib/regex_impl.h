#ifndef _RE2C_LIB_REGEX_IMPL_
#define _RE2C_LIB_REGEX_IMPL_

#include "regex.h"
#include <stddef.h>
#include <map>
#include <vector>
#include <queue>

#include "src/dfa/determinization.h"
#include "src/nfa/nfa.h"


namespace re2c {
namespace libre2c {

typedef std::vector<tag_info_t> tag_path_t;

const tag_info_t NOINFO = {0x3fffFFFF, 0};

static const uint32_t NONFIN = ~0u;
static const uint32_t USED = NONFIN - 1;

struct history_t
{
    struct arc_t {
        int32_t node;
        int32_t prev;
        int32_t next;

        inline arc_t(int32_t node, int32_t prev, int32_t next)
            : node(node), prev(prev), next(next) {}
    };

    struct node_t {
        tag_info_t info;
        int32_t pred;
        union {
            int32_t last;
            uint32_t step;
        };
        union {
            int32_t next;
            uint32_t orig;
        };
        uint32_t finidx;

        inline node_t(tag_info_t info, int32_t pred)
            : info(info), pred(pred), last(-1), next(-1), finidx(NONFIN) {}
        inline node_t(tag_info_t info, int32_t pred, uint32_t step, uint32_t orig)
            : info(info), pred(pred), step(step), orig(orig), finidx(NONFIN) {}
    };

    static const int32_t ROOT;

    std::vector<node_t> nodes;
    std::vector<arc_t> arcs;

    explicit history_t(size_t nstates);
    inline void init();
    inline node_t &node(int32_t i) { return nodes[static_cast<uint32_t>(i)]; }
    inline const node_t &node(int32_t i) const { return nodes[static_cast<uint32_t>(i)]; }
    inline arc_t &arc(int32_t i) { return arcs[static_cast<uint32_t>(i)]; }
    inline const arc_t &arc(int32_t i) const { return arcs[static_cast<uint32_t>(i)]; }
    inline int32_t push(int32_t i, uint32_t step, tag_info_t info, uint32_t orig);
    inline int32_t push(tag_info_t info, int32_t idx);
    FORBID_COPY(history_t);
};

struct conf_t
{
    nfa_state_t *state;
    uint32_t origin;
    int32_t thist;

    inline conf_t(): state(NULL), origin(0), thist(history_t::ROOT) {}
    inline conf_t(nfa_state_t *s, uint32_t o, int32_t h)
        : state(s), origin(o), thist(h) {}
};

struct histleaf_t
{
    uint32_t coreid;
    uint32_t origin;
    int32_t hidx;
    int32_t height;
};

struct ran_or_fin_t
{
    inline bool operator()(const conf_t &c);
};

struct cache_entry_t
{
    int32_t prec1;
    int32_t prec2;
    int32_t prec;
};

typedef std::map<uint64_t, cache_entry_t> cache_t;

typedef std::vector<conf_t> confset_t;
typedef confset_t::iterator confiter_t;
typedef confset_t::const_iterator cconfiter_t;
typedef confset_t::const_reverse_iterator rcconfiter_t;

struct simctx_t
{
    const nfa_t *nfa;
    const size_t nsub;
    const int flags;

    confset_t reach;
    confset_t state;

    history_t hist;
    int32_t hidx;

    uint32_t step;

    size_t rule;

    const char *cursor;
    const char *marker;

    regoff_t *offsets1;
    regoff_t *offsets2;
    regoff_t *offsets3;

    bool *done;

    int32_t *prectbl1;
    int32_t *prectbl2;
    cache_t cache;
    std::vector<histleaf_t> histlevel;
    std::vector<const conf_t*> sortcores;
    std::vector<uint32_t> fincount;
    std::vector<int32_t> worklist;

    std::vector<nfa_state_t*> gor1_topsort;
    std::vector<nfa_state_t*> gor1_linear;
    std::vector<nfa_state_t*> gtop_heap_storage;
    cmp_gtop_t gtop_cmp;
    gtop_heap_t gtop_heap;

    simctx_t(const nfa_t *nfa, size_t re_nsub, int flags);
    ~simctx_t();
    FORBID_COPY(simctx_t);
};

void init(simctx_t &ctx, const char *string);
int finalize(const simctx_t &ctx, const char *string, size_t nmatch, regmatch_t pmatch[]);
int regexec_dfa(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
int regexec_nfa_posix(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
int regexec_nfa_posix_trie(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
int regexec_nfa_leftmost(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
int regexec_nfa_leftmost_trie(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);

void history_t::init()
{
    nodes.clear();
    arcs.clear();
    nodes.push_back(node_t(NOINFO, -1));
}

int32_t history_t::push(tag_info_t info, int32_t idx)
{
    const int32_t i = static_cast<int32_t>(nodes.size());
    if (idx != -1) {
        node_t &n = node(idx);
        const int32_t a = static_cast<int32_t>(arcs.size());
        arcs.push_back(arc_t(i, n.last, -1));
        if (n.next == -1) {
            n.next = a;
        }
        else {
            arc(n.last).next = a;
        }
        n.last = a;
    }
    nodes.push_back(node_t(info, idx));
    return i;
}

int32_t history_t::push(int32_t idx, uint32_t step, tag_info_t info, uint32_t orig)
{
    const int32_t i = static_cast<int32_t>(nodes.size());
    nodes.push_back(node_t(info, idx, step, orig));
    return i;
}

bool ran_or_fin_t::operator()(const conf_t &c)
{
    switch (c.state->type) {
        case nfa_state_t::RAN:
        case nfa_state_t::FIN: return true;
        default: return false;
    }
}

} // namespace libre2c
} // namespace re2c

#endif // _RE2C_LIB_REGEX_IMPL_
