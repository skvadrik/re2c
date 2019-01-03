#include <string.h>

#include "src/debug/debug.h"
#include "src/dfa/tcmd.h"
#include "src/util/hash32.h"

namespace re2c
{

/* note [topological ordering of copy commands]
 *
 * The order in which copy commands are executed is important:
 * 'x = y; y = z;' is not the same as 'y = z; x = y;' (the latter
 * overwrites 'y' before its precious value is copied to 'x').
 *
 * To avoid overwrites, commands should be topologically sorted.
 * The algorithm detects cycles and terminates; non-trivial cycles
 * (induced by 2 or more nodes) are reported. We don't care about
 * trivial cycles (loopbacks), because they can be implemented without
 * temporary variable. Non-trivial cycles need a new temporary variable
 * local to the given basic block, which makes liveness analysis more
 * complex (so we simply forbid such mappings).
 *
 * For the purpose of topsort, we treat commands as arcs of directed
 * acyclic graph: command 'x = y' yields arc X -> Y. Topsort works
 * by iteratively removing arcs X -> Y such that X has zero in-degree
 * (they correspond to commands with no dependencies).
 * Commands in the order of removal are topologically sorted.
 *
 * The algorithm iterates graph and removes arcs with zero in-degree
 * until either the graph is empty or all remaining arcs belong to
 * cycles.
 *
 * The algorithm starts and ends with all-zero in-degree buffer.
 */


static uint32_t hash_tcmd(const tcmd_t *tcmd);


bool tcmd_t::equal(const tcmd_t &x, const tcmd_t &y)
{
    return x.lhs == y.lhs
        && x.rhs == y.rhs
        && equal_history(x.history, y.history);
}


bool tcmd_t::equal_history(const tagver_t *h, const tagver_t *g)
{
    for (;;) {
        if (*h != *g) return false;
        if (*h == TAGVER_ZERO) return true;
        ++h; ++g;
    }
}


bool tcmd_t::iscopy(const tcmd_t *x)
{
    return x->rhs != TAGVER_ZERO && x->history[0] == TAGVER_ZERO;
}


bool tcmd_t::isset(const tcmd_t *x)
{
    if (x->rhs == TAGVER_ZERO) {
        DASSERT(x->history[0] != TAGVER_ZERO);
        return true;
    }
    return false;
}


bool tcmd_t::isadd(const tcmd_t *x)
{
    return x->rhs != TAGVER_ZERO && x->history[0] != TAGVER_ZERO;
}


bool tcmd_t::topsort(tcmd_t **phead, uint32_t *indeg)
{
    tcmd_t *x0 = *phead, *x, *y0 = NULL, **py;
    bool nontrivial_cycles = false;

    // initialize in-degree
    for (x = x0; x; x = x->next) {
        indeg[x->lhs] = indeg[x->rhs] = 0;
    }
    for (x = x0; x; x = x->next) {
        ++indeg[x->rhs];
    }

    for (py = &y0;;) {
        // reached end of list
        if (!x0) break;

        tcmd_t **px = &x0, **py1 = py;
        for (x = x0; x; x = x->next) {
            if (indeg[x->lhs] == 0) {
                --indeg[x->rhs];
                *py = x;
                py = &x->next;
            } else {
                *px = x;
                px = &x->next;
            }
        }
        *px = NULL;

        // only cycles left
        if (py == py1) {
            // look for cycles of length 2 or more
            for (x = x0; x && x->lhs == x->rhs; x = x->next);
            nontrivial_cycles = x != NULL;
            break;
        }
    }
    *py = x0;

    *phead = y0;
    return nontrivial_cycles;
}


tcpool_t::tcpool_t()
    : alc()
    , index()
{
    // empty command must have static number zero
    insert(NULL);
    DASSERT(TCID0 == insert(NULL));
}


tcmd_t *tcpool_t::make_copy(tcmd_t *next, tagver_t lhs, tagver_t rhs)
{
    tcmd_t *p = alc.alloct<tcmd_t>(1);
    p->next = next;
    p->lhs = lhs;
    p->rhs = rhs;
    p->history[0] = TAGVER_ZERO;
    return p;
}


tcmd_t *tcpool_t::make_set(tcmd_t *next, tagver_t lhs, tagver_t set)
{
    const size_t size = sizeof(tcmd_t) + sizeof(tagver_t);
    tcmd_t *p = static_cast<tcmd_t*>(alc.alloc(size));
    p->next = next;
    p->lhs = lhs;
    p->rhs = TAGVER_ZERO;
    p->history[0] = set;
    p->history[1] = TAGVER_ZERO;
    return p;
}


tcmd_t *tcpool_t::make_add(tcmd_t *next, tagver_t lhs, tagver_t rhs,
    const tag_history_t &history, hidx_t hidx, size_t tag)
{
    size_t hlen = 0;
    for (hidx_t i = hidx; i != HROOT; i = history.pred(i)) {
        if (history.tag(i) == tag) ++hlen;
    }

    const size_t size = sizeof(tcmd_t) + hlen * sizeof(tagver_t);
    tcmd_t *p = static_cast<tcmd_t*>(alc.alloc(size));
    p->next = next;
    p->lhs = lhs;
    p->rhs = rhs;
    tagver_t *h = p->history;
    for (hidx_t i = hidx; i != HROOT; i = history.pred(i)) {
        if (history.tag(i) == tag) {
            *h++ = history.elem(i);
        }
    }
    *h++ = TAGVER_ZERO;
    return p;
}


tcmd_t *tcpool_t::copy_add(tcmd_t *next, tagver_t lhs, tagver_t rhs,
    const tagver_t *history)
{
    size_t hlen = 0;
    for (const tagver_t *h = history; *h != TAGVER_ZERO; ++h) ++hlen;

    const size_t size = sizeof(tcmd_t) + hlen * sizeof(tagver_t);
    tcmd_t *p = static_cast<tcmd_t*>(alc.alloc(size));
    p->next = next;
    p->lhs = lhs;
    p->rhs = rhs;
    memcpy(p->history, history, (hlen + 1) * sizeof(tagver_t));
    return p;
}


uint32_t hash_tcmd(const tcmd_t *tcmd)
{
    uint32_t h = 0;
    for (const tcmd_t *p = tcmd; p; p = p->next) {
        h = hash32(h, &p->lhs, sizeof(p->lhs));
        h = hash32(h, &p->rhs, sizeof(p->rhs));
        h = hash32(h, &p->history[0], sizeof(p->history[0]));
    }
    return h;
}


struct tcmd_eq_t
{
    bool operator()(const tcmd_t *x, const tcmd_t *y) const
    {
        for (;;) {
            if (!x && !y) return true;
            if (!x || !y) return false;
            if (!tcmd_t::equal(*x, *y)) return false;
            x = x->next;
            y = y->next;
        }
    }
};


tcid_t tcpool_t::insert(const tcmd_t *tcmd)
{
    const uint32_t h = hash_tcmd(tcmd);

    tcmd_eq_t eq;
    size_t id = index.find_with(h, tcmd, eq);
    if (id == index_t::NIL) {
        id = index.push(h, tcmd);
    }

    return static_cast<tcid_t>(id);
}


const tcmd_t *tcpool_t::operator[](tcid_t id) const
{
    return index[id];
}

} // namespace re2c
