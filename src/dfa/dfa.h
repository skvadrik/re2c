#ifndef _RE2C_DFA_DFA_
#define _RE2C_DFA_DFA_

#include "src/util/c99_stdint.h"
#include <valarray>
#include <vector>
#include <set>
#include <string.h>

#include "src/msg/msg.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/forbid_copy.h"


namespace re2c {

struct nfa_t;
struct opt_t;

struct dfa_state_t
{
    size_t *arcs;
    tcmd_t **tcmd;
    tcid_t *tcid;
    tcmd_t *stacmd;
    tcid_t stacid;
    size_t rule;
    bool fallthru;
    bool fallback;

    explicit dfa_state_t(size_t nchars)
        : arcs(new size_t[nchars])
        , tcmd(NULL)
        , tcid(NULL)
        , stacmd(NULL)
        , stacid(TCID0)
        , rule(Rule::NONE)
        , fallthru(false)
        , fallback(false)
    {
        size_t sz = nchars + 2; // +2 for final and fallback epsilon-transitions
        tcmd = new tcmd_t*[sz];
        memset(tcmd, 0, sizeof (tcmd_t*) * sz);
    }
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

    dfa_t(const nfa_t &nfa, const opt_t *opts, const std::string &cond
        , Msg &msg);
    ~dfa_t();

    FORBID_COPY(dfa_t);
};

enum dfa_minimization_t
{
    DFA_MINIMIZATION_TABLE,
    DFA_MINIMIZATION_MOORE
};

enum posix_closure_t
{
    POSIX_CLOSURE_GOR1,
    POSIX_CLOSURE_GTOP
};

enum posix_prectable_alg_t
{
    POSIX_PRECTABLE_NAIVE,
    POSIX_PRECTABLE_COMPLEX
};

void minimization(dfa_t &dfa, dfa_minimization_t type);
void fillpoints(const dfa_t &dfa, std::vector<size_t> &fill);
void cutoff_dead_rules(dfa_t &dfa, const opt_t *opts, size_t defrule, const std::string &cond, Msg &msg);
void insert_fallback_tags(const opt_t *opts, dfa_t &dfa);
void compact_and_optimize_tags(const opt_t *opts, dfa_t &dfa);
void freeze_tags(dfa_t &dfa);

} // namespace re2c

#endif // _RE2C_DFA_DFA_
