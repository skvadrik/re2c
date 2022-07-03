#include <string.h>
#include <vector>

#include "src/cfg/cfg.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/regexp/rule.h"
#include "src/regexp/tag.h"
#include "src/util/check.h"

namespace re2c {

// Calculates deep-first search postorder of transition nodes, skips final and fallback nodes (they
// have no successors anyway).
static cfg_ix_t* postorder(const cfg_t& cfg, bool* done, cfg_ix_t* ord, cfg_ix_t i) {
    if (i >= cfg.nbbarc || done[i]) {
        return ord;
    }
    done[i] = true;

    const cfg_bb_t* b = cfg.bblocks + i;
    for (cfg_ix_t* j = b->succb; j < b->succe; ++j) {
        ord = postorder(cfg, done, ord, *j);
    }

    *ord = i;
    return ++ord;
}

void cfg_t::live_through_bblock(const tcmd_t* cmd, bool* live) {
    if (!cmd) return;

    live_through_bblock(cmd->next, live);

    const tagver_t l = cmd->lhs, r = cmd->rhs;
    if (live[l]) {
        // first reset, than set: LHS might be equal to history
        live[l] = false;
        if (r != TAGVER_ZERO) {
            live[r] = true;
        }
    }
}


// note [control flow equations for tag liveness]
//
// Liveness in bblock B is given by control flow equations:
//     live-out(B) = union of live-in(C), for all successors C
//     live-in(B)  = live-out(B) except defined(B)
// Equations are solved by iteration until fix point.
//
// Live set can only grow on each iteration, it never shrinks. Initially all final tag versions
// used in rules are alive, then more versions become alive as liveness is propagated backwards on
// transitions.
//
// note [fallback tag liveness]
//
// Liveness of fallback tag is propagated forward from fallback state (see note [fallback states])
// and until there remain any fallthrough paths from current state.
//
// Fallback version of tag is either backup copy of tag's final version, or (if there's no backup)
// the final version itself. Absence of backup means that final version is not overwritten, but
// still we should prevent it from merging with other tags (otherwise it may become overwritten).

void cfg_t::liveness_analysis(const cfg_t& cfg, bool* live) {
    const std::vector<Tag>& tags = cfg.dfa.tags;
    const size_t nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1;
    const cfg_ix_t
    narc = cfg.nbbarc,
    nfin = cfg.nbbfin,
    nfall = cfg.nbbfall;
    const tagver_t* fins = cfg.dfa.finvers;
    bool* buf1 = new bool[nver];
    bool* buf2 = new bool[nver];
    bool* done = new bool[narc];
    cfg_ix_t* pord = new cfg_ix_t[narc];
    memset(live, 0, nfall * nver * sizeof(bool));

    for (cfg_ix_t i = narc; i < nfin; ++i) {
        const cfg_bb_t* b = cfg.bblocks + i;
        const Rule* r = b->rule;
        bool* l = &live[i * nver];

        // all final bblocks have USE tags, but no successors
        DCHECK(r && b->succb == b->succe);

        for (size_t t = r->ltag; t < r->htag; ++t) {
            l[fins[t]] = !fixed(tags[t]);
        }
    }

    memset(done, 0, narc * sizeof(bool));
    postorder(cfg, done, pord, 0);

    for (bool loop = true; loop;) {
        loop = false;

        // iterate nodes in postorder
        for (cfg_ix_t a = 0; a < narc; ++a) {
            const cfg_ix_t i = pord[a];
            const cfg_bb_t* b = cfg.bblocks + i;
            bool* old = &live[i * nver];

            // transition bblocks have no USE tags
            DCHECK(!b->rule);

            memcpy(buf1, old, nver * sizeof(bool));
            for (cfg_ix_t* j = b->succb; j < b->succe; ++j) {
                const bool* l = &live[*j * nver];
                const tcmd_t* cmd = cfg.bblocks[*j].cmd;
                memcpy(buf2, l, nver * sizeof(bool));

                cfg_t::live_through_bblock(cmd, buf2);

                for (size_t v = 0; v < nver; ++v) {
                    buf1[v] |= buf2[v];
                }
            }

            if (memcmp(old, buf1, nver * sizeof(bool)) != 0) {
                memcpy(old, buf1, nver * sizeof(bool));
                loop = true;
            }
        }
    }
    
    for (cfg_ix_t i = nfin; i < nfall; ++i) {
        const cfg_bb_t* b = cfg.bblocks + i;
        const Rule* r = b->rule;
        bool* l = &live[i * nver];

        // all fallback bblocks have USE tags
        DCHECK(r);

        for (size_t t = r->ltag; t < r->htag; ++t) {
            l[fins[t]] = !fixed(tags[t]);
        }

        // Need two passes: same version may occur as both LHS and RHS (this is not the same as
        // backward propagation of liveness through bblock).
        memcpy(buf1, l, nver * sizeof(bool));
        for (const tcmd_t* p = b->cmd; p; p = p->next) {
            buf1[p->lhs] = false;
        }
        for (const tcmd_t* p = b->cmd; p; p = p->next) {
            const tagver_t v = p->rhs;
            if (v != TAGVER_ZERO) {
                buf1[v] = true;
            }
        }

        for (cfg_ix_t* j = b->succb; j < b->succe; ++j) {
            bool* liv = &live[*j * nver];
            for (size_t v = 0; v < nver; ++v) {
                liv[v] |= buf1[v];
            }
        }
    }

    delete[] buf1;
    delete[] buf2;
    delete[] done;
    delete[] pord;
}

} // namespace re2c

