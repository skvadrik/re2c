#include "src/cfg/cfg.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/tag.h"


namespace re2c {

// Takes into account local liveness. Variables local to basic block may occur
// as a result of breaking cycles in a sequence of tag commands by introducing
// temporary variables. TDFA mappings have no cycles (such mappings are
// rejected), but staDFA transfer actions often do, because the indices used in
// the actions are bound to TNFA substates, which may be flipped in the origin
// and target staDFA states.
tcmd_t *cfg_t::dce_for_bblock(tcmd_t *cmd, bool *live)
{
    if (!cmd) return NULL;

    cmd->next = dce_for_bblock(cmd->next, live);

    const tagver_t l = cmd->lhs, r = cmd->rhs;
    if (live[l]) {
        // first reset, than set: LHS might be equal to history
        live[l] = false;
        if (r != TAGVER_ZERO) {
            live[r] = true;
        }
        // LHS is alive => this command remains
        return cmd;
    }

    // LHS is dead => this command is deleted
    return cmd->next;
}

void cfg_t::dead_code_elimination(cfg_t &cfg, const bool *live)
{
    const size_t nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1;
    // final and fallback tags can't be dead by construction
    cfg_bb_t *b = cfg.bblocks, *e = b + cfg.nbbarc;
    bool *live_local = new bool[nver];

    for (; b < e; ++b, live += nver) {
        memcpy(live_local, live, nver * sizeof(bool));
        b->cmd = dce_for_bblock(b->cmd, live_local);
    }

    delete[] live_local;
}

} // namespace re2c

