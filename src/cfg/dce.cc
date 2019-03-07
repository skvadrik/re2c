#include "src/cfg/cfg.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/tag.h"

namespace re2c
{

void cfg_t::dead_code_elimination(cfg_t &cfg, const bool *live)
{
    const tagver_t nver = cfg.dfa.maxtagver + 1;
    // final and fallback tags can't be dead by construction
    cfg_bb_t *b = cfg.bblocks, *e = b + cfg.nbbarc;

    // ignore possible local liveness inside of bblock:
    // by construction we have no versions local to bblock
    for (; b < e; ++b, live += nver) {
        for (tcmd_t *p, **pp = &b->cmd; (p = *pp);) {
            if (!live[p->lhs]) {
                *pp = p->next;
            } else {
                pp = &p->next;
            }
        }
    }
}

} // namespace re2c

