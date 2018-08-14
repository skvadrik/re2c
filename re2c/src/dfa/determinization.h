#ifndef _RE2C_DFA_DETERMINIZATION_
#define _RE2C_DFA_DETERMINIZATION_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <map>
#include <stack>
#include <string>
#include <vector>

#include "src/nfa/nfa.h"
#include "src/dfa/dump.h"
#include "src/dfa/tagver_table.h"
#include "src/dfa/tag_history.h"
#include "src/util/forbid_copy.h"
#include "src/util/lookup.h"
#include "src/util/slab_allocator.h"


namespace re2c
{

// fwd
struct opt_t;
struct Warn;
struct dfa_t;
struct tcmd_t;


typedef slab_allocator_t<4 * 1024, 1024 * 1024, sizeof(void*)> allocator_t;


struct clos_t
{
    nfa_state_t *state;
    uint32_t origin;
    uint32_t tvers; // vector of tag versions (including lookahead tags)
    hidx_t ttran; // history of transition tags
    hidx_t tlook; // history of lookahead tags

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


struct newver_cmp_t
{
    tag_history_t &history;

    explicit newver_cmp_t(tag_history_t &h) : history(h) {}
    bool operator()(const newver_t &, const newver_t &) const;
};


typedef std::map<newver_t, tagver_t, newver_cmp_t> newvers_t;


struct kernel_t
{
    size_t size;
    const prectable_t *prectbl;
    nfa_state_t **state;
    uint32_t *tvers; // tag versions
    hidx_t *tlook; // lookahead tags

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


typedef lookup_t<const kernel_t*> kernels_t;


struct determ_context_t
{
    // determinization input
    const opt_t             *dc_opts;       // options
    Warn                    &dc_warn;       // warnings
    const std::string       &dc_condname;   // the name of current condition (with -c)
    const nfa_t             &dc_nfa;        // TNFA

    // determinization output
    dfa_t                   &dc_dfa;        // resulting TDFA

    // temporary structures used by determinization
    allocator_t              dc_allocator;
    uint32_t                 dc_origin;     // from-state of the current transition
    uint32_t                 dc_target;     // to-state of the current transition
    uint32_t                 dc_symbol;     // alphabet symbol of the current transition
    tcmd_t                  *dc_actions;    // tag actions of the current transition
    closure_t                dc_reached;
    closure_t                dc_closure;
    prectable_t             *dc_prectbl;    // precedence table for Okui POSIX disambiguation
    tagver_table_t           dc_tagvertbl;
    tag_history_t            dc_taghistory; // prefix trie of tag histories
    kernels_t                dc_kernels;    // TDFA states under construction
    kernel_buffers_t         dc_buffers;
    newvers_t                dc_newvers;
    std::stack<nfa_state_t*> dc_stack_topsort;
    std::stack<nfa_state_t*> dc_stack_linear;
    std::stack<clos_t>       dc_stack_dfs;
    dump_dfa_t               dc_dump;

    determ_context_t(const opt_t *, Warn &, const std::string &, const nfa_t &, dfa_t &);
    FORBID_COPY(determ_context_t);
};


void tagged_epsilon_closure(determ_context_t &ctx);
void closure_posix(determ_context_t &);
void closure_leftmost(determ_context_t &);
void orders(determ_context_t &);
void find_state(determ_context_t &ctx);
int32_t precedence(determ_context_t &, const clos_t &, const clos_t &, int32_t &, int32_t &);

} // namespace re2c

#endif // _RE2C_DFA_DETERMINIZATION_
