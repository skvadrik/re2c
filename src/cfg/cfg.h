#ifndef _RE2C_DFA_CFG_CFG_
#define _RE2C_DFA_CFG_CFG_

#include <stdint.h>
#include <vector>

#include "src/regexp/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c {

struct Rule;
struct Tdfa;
struct tcmd_t;
struct opt_t;

using cfg_ix_t = uint32_t;

// basic block
struct cfg_bb_t {
    cfg_ix_t* succb;
    cfg_ix_t* succe;
    tcmd_t*& cmd; // non-constant, as optimizations need to change operations
    const Rule* rule;

    cfg_bb_t(const cfg_ix_t* sb, const cfg_ix_t* se, tcmd_t*& c, const Rule* r);
    FORBID_COPY(cfg_bb_t);
};

// helper structure used in control flow graph construction
struct cfg_context_t {
    static constexpr uint32_t MAX_MARK = ~0u;

    Tdfa& dfa;
    const size_t nstate;
    const size_t nsym;

    cfg_ix_t* trans2bb;
    cfg_ix_t* final2bb;
    cfg_ix_t* fback2bb;

    uint32_t* state_mark;
    uint32_t* trans_mark;
    uint32_t* final_mark;
    uint32_t mark;

    cfg_ix_t* succb;
    cfg_ix_t* succe;

    std::vector<size_t> worklist;

    explicit cfg_context_t(Tdfa& dfa);
    ~cfg_context_t();
    FORBID_COPY(cfg_context_t);
};

// control flow graph
struct cfg_t {
    Tdfa& dfa;
    cfg_bb_t* bblocks;
    cfg_ix_t nbbarc;
    cfg_ix_t nbbfin;
    cfg_ix_t nbbfall;

    // mock operations for the root state, as TDFA(1) has no initializer operations
    tcmd_t* tcmd0;

    explicit cfg_t(Tdfa& a);
    ~cfg_t();
    static tagver_t compact(const cfg_t& cfg, tagver_t* ver2new);
    static void liveness_analysis(const cfg_t& cfg, bool* live);
    static void live_through_bblock(const tcmd_t* cmd, bool* live);
    static tcmd_t* dce_for_bblock(tcmd_t* cmd, bool* live);
    static void dead_code_elimination(cfg_t& cfg, const bool* live);
    static void interference(const cfg_t& cfg, const bool* live, bool* interf);
    static tagver_t variable_allocation(const cfg_t& cfg, const bool* interf, tagver_t* ver2new);
    static void renaming(cfg_t& cfg, const tagver_t* ver2new, tagver_t maxver);
    static void normalization(cfg_t& cfg);

  private:
    void map_actions_to_bblocks(cfg_context_t& ctx);
    void create_bblocks(cfg_context_t& ctx);
    FORBID_COPY(cfg_t);
};

} // namespace re2c

#endif // _RE2C_DFA_CFG_CFG_
