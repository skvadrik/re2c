#ifndef _RE2C_DFA_DFA_
#define _RE2C_DFA_DFA_

#include "src/util/c99_stdint.h"
#include <valarray>
#include <vector>
#include <set>

#include "src/conf/warn.h"
#include "src/dfa/tcmd.h"
#include "src/re/rule.h"
#include "src/re/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

struct nfa_t;
struct opt_t;

struct dfa_state_t
{
    size_t *arcs;
    tcmd_t **tcmd;
    tcid_t *tcid;
    size_t rule;
    bool fallthru;
    bool fallback;

    explicit dfa_state_t(size_t nchars)
        : arcs(new size_t[nchars])
        , tcmd(new tcmd_t*[nchars + 2]()) // +2 for final and fallback epsilon-transitions
        , tcid(NULL)
        , rule(Rule::NONE)
        , fallthru(false)
        , fallback(false)
    {}
    ~dfa_state_t()
    {
        delete[] arcs;
        delete[] tcmd;
        delete[] tcid;
    }
    FORBID_COPY(dfa_state_t);
};

struct dfa_t
{
    static const uint32_t NIL;

    std::vector<dfa_state_t*> states;
    const size_t nchars;
    std::vector<uint32_t> &charset;
    std::valarray<Rule> &rules;
    std::vector<Tag> &tags;
    std::set<tagver_t> &mtagvers;
    tagver_t *finvers;
    tcpool_t &tcpool;
    tagver_t maxtagver;
    tcmd_t *tcmd0;
    tcid_t tcid0;

    dfa_t(const nfa_t &nfa, const opt_t *opts,
        const std::string &cond, Warn &warn);
    ~dfa_t();

    FORBID_COPY(dfa_t);
};

enum dfa_minimization_t
{
    DFA_MINIMIZATION_TABLE,
    DFA_MINIMIZATION_MOORE
};

void minimization(dfa_t &dfa, dfa_minimization_t type);
void fillpoints(const dfa_t &dfa, std::vector<size_t> &fill);
void cutoff_dead_rules(dfa_t &dfa, size_t defrule, const std::string &cond, Warn &warn);
void insert_fallback_tags(dfa_t &dfa);
void compact_and_optimize_tags(dfa_t &dfa, bool optimize);
void freeze_tags(dfa_t &dfa);

} // namespace re2c

#endif // _RE2C_DFA_DFA_
