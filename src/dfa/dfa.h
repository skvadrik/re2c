#ifndef _RE2C_DFA_DFA_
#define _RE2C_DFA_DFA_

#include <stdint.h>
#include <vector>
#include <set>
#include <string.h>

#include "src/constants.h"
#include "src/msg/msg.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/allocator.h"
#include "src/util/attribute.h"
#include "src/util/forbid_copy.h"

namespace re2c {

struct Tnfa;
struct opt_t;

struct TdfaState {
    size_t* arcs;
    tcmd_t** tcmd;
    tcid_t* tcid;
    size_t rule;
    bool fallthru;
    bool fallback;

    explicit TdfaState(size_t nchars)
        : arcs(new size_t[nchars]),
          tcmd(nullptr),
          tcid(nullptr),
          rule(Rule::NONE),
          fallthru(false),
          fallback(false) {
        size_t sz = nchars + 2; // +2 for final and fallback epsilon-transitions
        tcmd = new tcmd_t* [sz];
        memset(tcmd, 0, sizeof (tcmd_t*) * sz);
    }

    ~TdfaState() {
        delete[] arcs;
        delete[] tcmd;
        delete[] tcid;
    }

    FORBID_COPY(TdfaState);
};

struct Tdfa {
    static constexpr uint32_t NIL = ~0u;

    DfaAllocator& dfa_alc;

    IrAllocator ir_alc;
    std::vector<uint32_t> charset;
    std::vector<Rule> rules;
    std::vector<Tag> tags;

    std::vector<TdfaState*> states;
    const size_t nchars;
    std::set<tagver_t> mtagvers;
    tagver_t* finvers;
    tcpool_t tcpool;
    tagver_t maxtagver;
    size_t def_rule;
    size_t eof_rule;

    Tdfa(DfaAllocator& dfa_alc, size_t charset_bounds, size_t def_rule, size_t eof_rule);
    ~Tdfa();

    FORBID_COPY(Tdfa);
};

Ret determinization(
        Tnfa&& nfa, Tdfa& dfa, const opt_t* opts, Msg& msg, const std::string& cond) NODISCARD;
void minimization(Tdfa& dfa, Minimization type);
void fillpoints(const Tdfa& dfa, std::vector<size_t>& fill);
void cutoff_dead_rules(Tdfa& dfa, const opt_t* opts, const std::string& cond, Msg& msg);
void insert_fallback_tags(Tdfa& dfa);
void compact_and_optimize_tags(const opt_t* opts, Tdfa& dfa);
void freeze_tags(Tdfa& dfa);

} // namespace re2c

#endif // _RE2C_DFA_DFA_
