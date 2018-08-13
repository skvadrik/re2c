#include <assert.h>
#include "src/util/c99_stdint.h"
#include <string.h>
#include <algorithm>

#include "src/dfa/cfg/cfg.h"
#include "src/dfa/dfa.h"
#include "src/dfa/tcmd.h"
#include "src/re/tag.h"

namespace re2c
{

template<typename cmd_t> void normalize(cmd_t *cmd);

/* note [tag normalization]
 *
 * After optimizations different commands may become equal
 * up to reordering and removing duplicates. Such commands
 * should be recognized as equal by further optimizations
 * like minimization, hoisting, tunnelling, etc.
 * For that reason all commands are normalized.
 */

static tcmd_t **normalize(tcmd_t **ps, tcmd_t *e);

void cfg_t::normalization(cfg_t &cfg)
{
    const size_t nver = static_cast<size_t>(cfg.dfa.maxtagver) + 1;
    uint32_t *indeg = new uint32_t[nver];
    memset(indeg, 0, nver * sizeof(uint32_t));

    cfg_bb_t *b = cfg.bblocks, *e = b + cfg.nbbfall;
    for (; b < e; ++b) {

        // We cannot normalize the list of commands as a whole: the
        // relative order of some commands might be significant.
        // Therefore we split the list in continuous sublists of
        // 'copy', 'save without history' and 'save with history'
        // commands and normalize each sublist in a proper way.
        tcmd_t **px, *x;
        for (px = &b->cmd; (x = *px);) {
            if (tcmd_t::iscopy(x)) {
                for (x = *px; x && tcmd_t::iscopy(x); x = x->next);
                *normalize(px, x) = NULL; // topsort expects NULL terminator
                tcmd_t::topsort(px, indeg);
                for (; *px; px = &(*px)->next); // find tail
                *px = x; // restore tail
            } else if (tcmd_t::isset(x)) {
                for (x = *px; x && tcmd_t::isset(x); x = x->next);
                px = normalize(px, x);
            } else {
                for (; (x = *px) && tcmd_t::isadd(x); px = &x->next);
                // don't normalize, histories may have complex dependencies
            }
        }
    }

    delete[] indeg;
}

static void swap(tcmd_t &x, tcmd_t &y)
{
    assert(!tcmd_t::isadd(&x) && !tcmd_t::isadd(&y));
    std::swap(x.lhs, y.lhs);
    std::swap(x.rhs, y.rhs);
    std::swap(x.history[0], y.history[0]);
}

static bool less(const tcmd_t &x, const tcmd_t &y)
{
    assert(!tcmd_t::isadd(&x) && !tcmd_t::isadd(&y));
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

tcmd_t **normalize(tcmd_t **ps, tcmd_t *e)
{
    // sort lexicographically
    for (tcmd_t *p = *ps; p != e; p = p->next) {
        for (tcmd_t *q = p->next; q != e; q = q->next) {
            if (less(*q, *p)) {
                swap(*p, *q);
            }
        }
    }

    // delete duplicates
    for (tcmd_t *p = *ps; p != e;) {
        tcmd_t *q = p->next;
        if (q != e && tcmd_t::equal(*p, *q)) {
            p->next = q->next;
        } else {
            p = q;
        }
    }

    for (; *ps != e; ps = &(*ps)->next);
    return ps;
}

} // namespace re2c

