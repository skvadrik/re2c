#ifndef _RE2C_LIB_REGEX_IMPL_
#define _RE2C_LIB_REGEX_IMPL_

#include "regex.h"
#include <stddef.h>
#include <vector>
#include <queue>

#include "src/nfa/nfa.h"


namespace re2c {

typedef std::vector<tag_info_t> tag_path_t;

struct history_t
{
    struct node_t {
        uint32_t pred;
        uint32_t step;
        tag_info_t info;
    };

    std::vector<node_t> nodes;
    tag_path_t path1;
    tag_path_t path2;

    history_t(size_t nstates, size_t ntags);
    inline uint32_t push(uint32_t i, uint32_t step, tag_info_t info);
    inline void reconstruct(tag_path_t &, uint32_t, uint32_t);
    FORBID_COPY(history_t);
};

struct conf_t
{
    nfa_state_t *state;
    uint32_t origin;
    uint32_t thist;
};

struct ran_or_fin_t
{
    inline bool operator()(const conf_t &c);
};

struct cmp_gtop_t
{
    inline bool operator() (const nfa_state_t *x, const nfa_state_t *y) const;
};

typedef std::vector<conf_t> confset_t;
typedef confset_t::iterator confiter_t;
typedef confset_t::const_iterator cconfiter_t;
typedef confset_t::const_reverse_iterator rcconfiter_t;
typedef std::priority_queue<nfa_state_t*, std::vector<nfa_state_t*>
    , cmp_gtop_t> worklist_t;

struct simctx_t
{
    const nfa_t *nfa;
    confset_t reach;
    confset_t state;
    int32_t *prec;
    int32_t *prec_next;
    history_t hist;
    uint32_t hidx;
    uint32_t step;
    size_t rule;
    const char *cursor;
    const char *marker;

    simctx_t(const regex_t *preg, const char *string);
    FORBID_COPY(simctx_t);
};

int regexec_dfa(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
int regexec_nfa_posix(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
int regexec_nfa_leftmost(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
int finalize(const simctx_t &ctx, const char *string, size_t nmatch, regmatch_t pmatch[]);
inline uint32_t index(const nfa_t *, const nfa_state_t *);

uint32_t history_t::push(uint32_t idx, uint32_t step, tag_info_t info)
{
    const node_t x = {idx, step, info};
    nodes.push_back(x);
    return static_cast<uint32_t>(nodes.size() - 1);
}

void history_t::reconstruct(tag_path_t &path, uint32_t idx, uint32_t step)
{
    path.clear();
    for (; idx != HROOT; ) {
        const node_t &n = nodes[idx];
        if (n.step != step) break;
        path.push_back(n.info);
        idx = n.pred;
    }
}

uint32_t index(const nfa_t *nfa, const nfa_state_t *state)
{
    return static_cast<uint32_t>(state - nfa->states);
}

bool ran_or_fin_t::operator()(const conf_t &c)
{
    switch (c.state->type) {
        case nfa_state_t::RAN:
        case nfa_state_t::FIN: return true;
        default: return false;
    }
}

bool cmp_gtop_t::operator() (const nfa_state_t *x, const nfa_state_t *y) const
{
    return x->topord < y->topord;
}

} // namespace re2c

#endif // _RE2C_LIB_REGEX_IMPL_
