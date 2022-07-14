#include <stddef.h>
#include <algorithm>
#include <vector>

#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/options/opt.h"
#include "src/regexp/tag.h"

namespace re2c {

// note [fallback tags]
//
// We need to backup tags in fallback states, because they may be overwritten on some non-accepting
// path from fallback state. Two different things may cause overwrites:
//
//   (1) self-overlapping rules: if TDFA has tagged cycles, new iteration may overwrite tags from
//       previous iteration and then fail
//
//   (2) overlapping rules: intially all rules have different tags, but optiizations may merge them;
//       then shorter rule's tags may be overwritten by an unsuccessful attempt to match the longer
//       rule
//
// In case (2) we can prevent merging by propagating tag liveness on all non-accepting paths from
// fallback state. Case (1) is not so easy: overwrites are already embedded in TDFA. We have to
// create backup copies for all potentially overwritten tags. If tag is overwritten on just one
// path, it should be backed up on all non-accepting paths from fallback state (because paths may
// join later along the way and they need common tag version). However, redundant backups cause
// artificial interference, so we only create backup if the origin is overwritten on some path.

static void find_overwritten_tags(const Tdfa& dfa, size_t state, bool* been, bool* owrt) {
    if (been[state]) return;
    been[state] = true;

    const TdfaState* s = dfa.states[state];
    for (size_t c = 0; c < dfa.nchars; ++c) {
        for (const tcmd_t* p = s->tcmd[c]; p; p = p->next) {
            owrt[p->lhs] = true;
        }

        size_t dest = s->arcs[c];
        if (dest != Tdfa::NIL && dfa.states[dest]->fallthru) {
            find_overwritten_tags(dfa, dest, been, owrt);
        }
    }
}


// Overwritten tags need 'copy' on all outgoing non-accepting paths ('copy' commands must go first,
// before potential overwrites).
static void backup(Tdfa& dfa, TdfaState* s, tagver_t l, tagver_t r) {
    for (size_t c = 0; c < dfa.nchars; ++c) {
        size_t i = s->arcs[c];
        if (i != Tdfa::NIL && dfa.states[i]->fallthru) {
            tcmd_t*& p = s->tcmd[c];
            p = dfa.tcpool.make_copy(p, l, r);
        }
    }
}


// WARNING: this function assumes that falthrough and fallback attributes of TDFA states have
// already been calculated, see note [fallback states].
void insert_fallback_tags(Tdfa& dfa) {
    tcpool_t& pool = dfa.tcpool;
    const size_t
    nstates = dfa.states.size(),
    nsym = dfa.nchars,
    nver = static_cast<size_t>(dfa.maxtagver) + 1;
    bool* been = new bool[nstates];
    bool* owrt = new bool[nver];

    for (size_t i = 0; i < nstates; ++i) {
        TdfaState* s = dfa.states[i];
        if (!s->fallback) continue;

        std::fill(been, been + nstates, false);
        std::fill(owrt, owrt + nver, false);
        find_overwritten_tags(dfa, i, been, owrt);

        tcmd_t* p = s->tcmd[nsym];
        tcmd_t* save = nullptr, **ps = &save;
        tcmd_t** pc = &s->tcmd[nsym + 1];

        for (; p; p = p->next) {
            const tagver_t l = p->lhs, r = p->rhs, *h = p->history;

            if (tcmd_t::iscopy(p)) { // 'copy' commands
                if (!owrt[r]) {
                    *pc = pool.make_copy(nullptr, l, r);
                    pc = &(*pc)->next;
                } else {
                    backup(dfa, s, l, r);
                }
            } else if (tcmd_t::isset(p)) { // 'save without history' commands
                *ps = pool.make_set(*ps, l, h[0]);
                ps = &(*ps)->next;
            } else { // 'save with history' commands
                if (!owrt[r]) {
                    *ps = pool.copy_add(nullptr, l, r, h);
                } else {
                    *ps = pool.copy_add(nullptr, l, l, h);
                    backup(dfa, s, l, r);
                }
                ps = &(*ps)->next;
            }
        }

        // join 'copy' (fallback) and 'save' commands
        *pc = save;
    }

    delete[] been;
    delete[] owrt;
}

} // namespace re2c
