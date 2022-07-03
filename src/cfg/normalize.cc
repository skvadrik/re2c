#include <stdint.h>
#include <string.h>
#include <utility>

#include "src/cfg/cfg.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/options/opt.h"
#include "src/regexp/tag.h"
#include "src/util/check.h"

namespace re2c {

template<typename cmd_t> void normalize(cmd_t* cmd);

// note [tag normalization]
//
// After optimizations different commands may become equal up to reordering and removing duplicates.
// Such commands should be deduplicated (duplicate "set" and "copy" commands are redundant and may
// prohibit further optimizations like minimization and tunneling, and duplicate "add" commands are
// incorrect altogether.
//
// Consequently, tag commands are "normalized": the sequence of commands is split into continuous
// subsequnces of "set", "copy" and "add" commands, and within each subsequence duplicate commands
// are removed. Additionally, "set" subsequences are sorted lexicographically (the relative order of
// "set" commands doesn't matter), and "copy" subsequences are first sorted lexicographically and
// then topologically.

static void sort(tcmd_t* head, tcmd_t* end);
static void uniq(tcmd_t* head, tcmd_t* end);
static void dedup(tcmd_t* head, tcmd_t* end);

void cfg_t::normalization(cfg_t& cfg) {
    const size_t nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1;
    uint32_t* indeg = new uint32_t[nver];

    cfg_bb_t* b = cfg.bblocks, *e = b + cfg.nbbfall;
    for (; b < e; ++b) {
        for (tcmd_t** px = &b->cmd, *x; (x = *px);) {

            if (tcmd_t::iscopy(x)) {
                for (; x && tcmd_t::iscopy(x); x = x->next);
                // sort, remove adjacent duplicates, topsort
                sort(*px, x);
                uniq(*px, x);
                tcmd_t::topsort(px, x, indeg);
            } else if (tcmd_t::isset(x)) {
                // sort, remove adjacent duplicates
                for (; x && tcmd_t::isset(x); x = x->next);
                sort(*px, x);
                uniq(*px, x);
            } else {
                // remove duplicates
                for (; x && tcmd_t::isadd(x); x = x->next);
                dedup(*px, x);
            }

            // Find tail of the current copy/set/add subsequence (need to reiterate it as the former
            // tail might have been removed).
            for (; *px != x; px = &(*px)->next);
        }
    }

    delete[] indeg;
}

static void swap(tcmd_t& x, tcmd_t& y) {
    DCHECK(!tcmd_t::isadd(&x) && !tcmd_t::isadd(&y));
    std::swap(x.lhs, y.lhs);
    std::swap(x.rhs, y.rhs);
    std::swap(x.history[0], y.history[0]);
}

static bool less(const tcmd_t& x, const tcmd_t& y) {
    DCHECK(!tcmd_t::isadd(&x) && !tcmd_t::isadd(&y));
    tagver_t u, v;

    u = x.lhs; v = y.lhs;
    if (u < v) return true;
    if (u > v) return false;

    u = x.rhs; v = y.rhs;
    if (u < v) return true;
    if (u > v) return false;

    u = x.history[0]; v = y.history[0];
    if (u < v) return true;
    if (u > v) return false;

    return false;
}

void sort(tcmd_t* head, tcmd_t* end) {
    // sort: O(n^2)
    for (tcmd_t* p = head; p != end; p = p->next) {
        for (tcmd_t* q = p->next; q != end; q = q->next) {
            if (less(*q, *p)) {
                swap(*p, *q);
            }
        }
    }
}

void uniq(tcmd_t* head, tcmd_t* end) {
    // remove adjacent duplicates: O(n)
    for (tcmd_t* p = head; p != end;) {
        tcmd_t* q = p->next;
        if (q != end && tcmd_t::equal(*p, *q)) {
            p->next = q->next;
        } else {
            p = q;
        }
    }
}

void dedup(tcmd_t* head, tcmd_t* end) {
    // remove duplicates: O(n^2)
    for (tcmd_t* p = head; p != end; p = p->next) {
        for (tcmd_t** qq = &p->next; *qq != end; ) {
            if (tcmd_t::equal(*p, **qq)) {
                *qq = (*qq)->next;
            } else {
                qq = &(*qq)->next;
            }
        }
    }
}

} // namespace re2c

