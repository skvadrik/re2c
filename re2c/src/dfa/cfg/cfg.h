#ifndef _RE2C_DFA_CFG_CFG_
#define _RE2C_DFA_CFG_CFG_

#include "src/util/c99_stdint.h"

#include "src/dfa/dfa.h"
#include "src/re/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c {

struct Rule;
struct dfa_t;
struct tcmd_t;

typedef uint32_t cfg_ix_t;

// basic block
struct cfg_bb_t
{
    cfg_ix_t *succb;
    cfg_ix_t *succe;
    tcmd_t *&cmd;
    const Rule *rule;

    cfg_bb_t(const cfg_ix_t *sb, const cfg_ix_t *se, tcmd_t *&c, const Rule *r);
    FORBID_COPY(cfg_bb_t);
};

// control flow graph
struct cfg_t
{
    dfa_t &dfa;
    cfg_bb_t *bblocks;
    cfg_ix_t nbbarc;
    cfg_ix_t nbbfin;
    cfg_ix_t nbbfall;

    explicit cfg_t(dfa_t &a);
    ~cfg_t();
    static tagver_t compact(const cfg_t &cfg, tagver_t *ver2new);
    static void liveness_analysis(const cfg_t &cfg, bool *live);
    static void live_through_bblock(const tcmd_t *cmd, bool *live);
    static void dead_code_elimination(cfg_t &cfg, const bool *live);
    static void interference(const cfg_t &cfg, const bool *live, bool *interf);
    static tagver_t variable_allocation(const cfg_t &cfg, const bool *interf, tagver_t *ver2new);
    static void renaming(cfg_t &cfg, const tagver_t *ver2new, tagver_t maxver);
    static void normalization(cfg_t &cfg);
    FORBID_COPY(cfg_t);
};

void dump_cfg(const cfg_t &cfg, const bool *live);
void dump_interf(const cfg_t &cfg, const bool *interf);

} // namespace re2c

#endif // _RE2C_DFA_CFG_CFG_
