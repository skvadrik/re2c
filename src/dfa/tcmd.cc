#include <string.h>

#include "src/dfa/tcmd.h"
#include "src/util/check.h"
#include "src/util/hash32.h"

namespace re2c {

// note [topological ordering of copy commands]
//
// The order in which copy commands are executed is important: 'x = y; y = z;' is not the same as
// 'y = z; x = y;' (the latter overwrites 'y' before its value is copied to 'x').
//
// To avoid overwrites, commands should be topologically sorted. The algorithm automatically moves
// all cycles to the end of the list and returns a pointer to the first non-trivial cycle (induced
// by 2 or more nodes). Trivial cycles may occur in "add" commands (if the current position or nil
// is appended to the history of some tag); such cases are not problematic because they do not
// require a temporary variable. Non-trivial cycles need a temporary variable (local to the basic
// block), which complicates liveness analysis. TDFA simply rejects mappings with cycles.
//
// For the purpose of topsort, we treat commands as arcs of directed acyclic graph: command 'x = y'
// yields arc X -> Y. Topsort works by iteratively removing an arc X -> Y that X has zero in-degree
// (such arcs correspond to commands with no dependencies) and decrementing Y's in-degree. Commands
// in the order of removal are added to the new (topologically sorted) list. This continues until
// either the list is empty, or none of the remainig commands has a zero in-degree. In this case all
// remaining commands are cycles; they cannot be topsorted and are appended at the end of the list.

// explicit instantiation for history types
template tcmd_t* tcpool_t::make_add<phistory_t>(tcmd_t* next,
                                                tagver_t lhs,
                                                tagver_t rhs,
                                                const phistory_t& history,
                                                hidx_t hidx,
                                                size_t tag);
template tcmd_t* tcpool_t::make_add<lhistory_t>(tcmd_t* next,
                                                tagver_t lhs,
                                                tagver_t rhs,
                                                const lhistory_t& history,
                                                hidx_t hidx,
                                                size_t tag);

static uint32_t hash_tcmd(const tcmd_t* tcmd);

bool tcmd_t::equal(const tcmd_t& x, const tcmd_t& y) {
    return x.lhs == y.lhs
           && x.rhs == y.rhs
           && equal_history(x.history, y.history);
}

bool tcmd_t::equal_history(const tagver_t* h, const tagver_t* g) {
    for (;;) {
        if (*h != *g) return false;
        if (*h == TAGVER_ZERO) return true;
        ++h; ++g;
    }
}

tcmd_t** tcmd_t::topsort(tcmd_t** phead, tcmd_t* end, uint32_t* indeg) {
    tcmd_t* head = *phead, **ptail;

    // initialize in-degree
    for (tcmd_t* x = head; x != end; x = x->next) {
        indeg[x->lhs] = indeg[x->rhs] = 0;
    }
    for (tcmd_t* x = head; x != end; x = x->next) {
        ++indeg[x->rhs];
    }

    for (ptail = phead;;) {
        // reached end of list, stop
        if (head == end) break;

        // topsorted commands are pushed on y-list, the rest on x-list
        tcmd_t** px = &head, **py = ptail;
        for (tcmd_t* x = head; x != end; x = x->next) {
            if (indeg[x->lhs] == 0) {
                --indeg[x->rhs];
                *py = x;
                py = &x->next;
            } else {
                *px = x;
                px = &x->next;
            }
        }
        *px = end;

        // nothing added on the y-list => only cycles left, stop
        if (ptail == py) break;
        ptail = py;
    }

    // append cycles at the end, or just set last 'next' pointer to end
    *ptail = head;

    // return the first non-trivial cycle on x-list (if any), or nil
    for (tcmd_t* x; (x = *ptail) != end && x->lhs == x->rhs; ptail = &x->next);
    return *ptail == end ? nullptr : ptail;
}

tcpool_t::tcpool_t(DfaAllocator& alc): alc(alc), index() {
    // empty command must have static number zero
    insert(nullptr);
    CHECK(TCID0 == insert(nullptr));
}

tcmd_t* tcpool_t::make_copy(tcmd_t* next, tagver_t lhs, tagver_t rhs) {
    tcmd_t* p = alc.alloct<tcmd_t>(1);
    p->next = next;
    p->lhs = lhs;
    p->rhs = rhs;
    p->history[0] = TAGVER_ZERO;
    return p;
}

tcmd_t* tcpool_t::make_set(tcmd_t* next, tagver_t lhs, tagver_t set) {
    const size_t size = sizeof(tcmd_t) + sizeof(tagver_t);
    tcmd_t* p = static_cast<tcmd_t*>(alc.alloc(size));
    p->next = next;
    p->lhs = lhs;
    p->rhs = TAGVER_ZERO;
    p->history[0] = set;
    p->history[1] = TAGVER_ZERO;
    return p;
}

template<typename history_t>
tcmd_t* tcpool_t::make_add(tcmd_t* next,
                           tagver_t lhs,
                           tagver_t rhs,
                           const history_t& history,
                           hidx_t hidx,
                           size_t tag) {
    size_t hlen = 0;
    for (hidx_t i = hidx; i != HROOT; ) {
        const typename history_t::node_t& n = history.node(i);
        if (n.info.idx == tag) ++hlen;
        i = n.pred;
    }

    const size_t size = sizeof(tcmd_t) + hlen * sizeof(tagver_t);
    tcmd_t* p = static_cast<tcmd_t*>(alc.alloc(size));
    p->next = next;
    p->lhs = lhs;
    p->rhs = rhs;
    tagver_t* h = p->history;
    for (hidx_t i = hidx; i != HROOT; ) {
        const typename history_t::node_t& n = history.node(i);
        if (n.info.idx == tag) {
            *h++ = n.info.neg ? TAGVER_BOTTOM : TAGVER_CURSOR;
        }
        i = n.pred;
    }
    *h++ = TAGVER_ZERO;
    return p;
}

tcmd_t* tcpool_t::copy_add(tcmd_t* next,
                           tagver_t lhs,
                           tagver_t rhs,
                           const tagver_t* history) {
    size_t hlen = 0;
    for (const tagver_t* h = history; *h != TAGVER_ZERO; ++h) ++hlen;

    const size_t size = sizeof(tcmd_t) + hlen * sizeof(tagver_t);
    tcmd_t* p = static_cast<tcmd_t*>(alc.alloc(size));
    p->next = next;
    p->lhs = lhs;
    p->rhs = rhs;
    memcpy(p->history, history, (hlen + 1) * sizeof(tagver_t));
    return p;
}

uint32_t hash_tcmd(const tcmd_t* tcmd) {
    uint32_t h = 0;
    for (const tcmd_t* p = tcmd; p; p = p->next) {
        h = hash32(h, &p->lhs, sizeof(p->lhs));
        h = hash32(h, &p->rhs, sizeof(p->rhs));
        h = hash32(h, &p->history[0], sizeof(p->history[0]));
    }
    return h;
}

struct tcmd_eq_t {
    bool operator()(const tcmd_t* x, const tcmd_t* y) const {
        for (;;) {
            if (!x && !y) return true;
            if (!x || !y) return false;
            if (!tcmd_t::equal(*x, *y)) return false;
            x = x->next;
            y = y->next;
        }
    }
};

tcid_t tcpool_t::insert(const tcmd_t* tcmd) {
    const uint32_t h = hash_tcmd(tcmd);

    tcmd_eq_t eq;
    size_t id = index.find_with(h, tcmd, eq);
    if (id == index_t::NIL) {
        id = index.push(h, tcmd);
    }

    return static_cast<tcid_t>(id);
}

const tcmd_t* tcpool_t::operator[](tcid_t id) const {
    return index[id];
}

} // namespace re2c
