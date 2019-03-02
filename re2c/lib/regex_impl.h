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

struct conf_t
{
    nfa_state_t *state;
    uint32_t origin;
    int32_t thist;

    inline conf_t(): state(NULL), origin(0), thist(HROOT) {}
    inline conf_t(nfa_state_t *s, uint32_t o, int32_t h)
        : state(s), origin(o), thist(h) {}
    inline conf_t(const conf_t &c, nfa_state_t *s)
        : state(s), origin(c.origin), thist(c.thist) {}
    inline conf_t(const conf_t &c, nfa_state_t *s, int32_t h)
        : state(s), origin(c.origin), thist(h) {}
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
    typedef libre2c::conf_t conf_t;
    typedef std::vector<conf_t> confset_t;
    typedef confset_t::iterator confiter_t;
    typedef confset_t::const_iterator cconfiter_t;
    typedef confset_t::reverse_iterator rconfiter_t;
    typedef confset_t::const_reverse_iterator rcconfiter_t;

    const nfa_t &nfa;
    const size_t nsub;
    const int flags;

    tag_history_t history;
    int32_t hidx;

    uint32_t step;

    size_t rule;

    const char *cursor;
    const char *marker;

    regoff_t *offsets1;
    regoff_t *offsets2;
    regoff_t *offsets3;
    bool *done;

    int32_t *newprectbl;
    int32_t *oldprectbl;
    size_t oldprecdim;
    std::vector<histleaf_t> histlevel;
    std::vector<uint32_t> sortcores;
    std::vector<uint32_t> fincount;
    std::vector<int32_t> worklist;
    cache_t cache;

    confset_t reach;
    confset_t state;
    std::vector<nfa_state_t*> gor1_topsort;
    std::vector<nfa_state_t*> gor1_linear;
    std::vector<nfa_state_t*> gtop_heap_storage;
    cmp_gtop_t gtop_cmp;
    gtop_heap_t gtop_heap;
    closure_stats_t dc_clstats;

    simctx_t(const nfa_t &nfa, size_t re_nsub, int flags);
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
