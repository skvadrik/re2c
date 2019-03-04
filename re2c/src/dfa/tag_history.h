#ifndef _RE2C_DFA_TAG_HISTORY_
#define _RE2C_DFA_TAG_HISTORY_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <sys/types.h>
#include <vector>

#include "src/regexp/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

typedef int32_t hidx_t;
typedef std::vector<tag_info_t> tag_path_t;

static const hidx_t HROOT = 0;
const tag_info_t NOINFO = {0x3fffFFFF, 0};
static const uint32_t NONFIN = ~0u;
static const uint32_t USED = NONFIN - 1;

enum sema_t {POSIX, LEFTMOST};
enum eval_t {STRICT, LAZY};

// tag history for POSIX semantics
struct phistory_t
{
    struct node_t {
        tag_info_t info;
        hidx_t pred;
        hidx_t last;
        hidx_t next;
        uint32_t finidx;

        inline node_t(tag_info_t info, hidx_t pred, hidx_t last, hidx_t next)
            : info(info), pred(pred), last(last), next(next), finidx(NONFIN) {}
    };

    struct arc_t {
        hidx_t node;
        hidx_t prev;
        hidx_t next;

        inline arc_t(hidx_t node, hidx_t prev, hidx_t next)
            : node(node), prev(prev), next(next) {}
    };

    std::vector<node_t> nodes;
    std::vector<arc_t> arcs;

    inline phistory_t(): nodes(), arcs() { init(); }
    inline void init();
    inline void detach();
    inline node_t &node(hidx_t i) { return nodes[static_cast<uint32_t>(i)]; }
    inline const node_t &node(hidx_t i) const { return nodes[static_cast<uint32_t>(i)]; }
    inline arc_t &arc(hidx_t i) { return arcs[static_cast<uint32_t>(i)]; }
    inline const arc_t &arc(hidx_t i) const { return arcs[static_cast<uint32_t>(i)]; }
    inline hidx_t push(hidx_t idx, tag_info_t info);
    FORBID_COPY(phistory_t);
};

// tag history for leftmost greedy semantics
struct lhistory_t
{
    struct node_t {
        tag_info_t info;
        hidx_t pred;

        inline node_t(tag_info_t info, hidx_t pred)
            : info(info), pred(pred) {}
    };

    std::vector<node_t> nodes;

    inline lhistory_t(): nodes() { init(); }
    inline void init();
    inline node_t &node(hidx_t i) { return nodes[static_cast<uint32_t>(i)]; }
    inline const node_t &node(hidx_t i) const { return nodes[static_cast<uint32_t>(i)]; }
    inline hidx_t push(hidx_t idx, tag_info_t info);
    FORBID_COPY(lhistory_t);
};

// tag history for lazy disambiguation (both POSIX and leftmost greedy)
struct zhistory_t
{
    struct node_t {
        tag_info_t info;
        hidx_t pred;
        uint32_t step;
        uint32_t orig;

        inline node_t(tag_info_t info, hidx_t pred, uint32_t step, uint32_t orig)
            : info(info), pred(pred), step(step), orig(orig) {}
    };

    std::vector<node_t> nodes;

    inline zhistory_t(): nodes() { init(); }
    inline void init();
    inline node_t &node(hidx_t i) { return nodes[static_cast<uint32_t>(i)]; }
    inline const node_t &node(hidx_t i) const { return nodes[static_cast<uint32_t>(i)]; }
    inline hidx_t push(hidx_t idx, uint32_t step, tag_info_t info, uint32_t orig);
    FORBID_COPY(zhistory_t);
};

void phistory_t::init()
{
    nodes.clear();
    arcs.clear();
    nodes.push_back(node_t(NOINFO, -1, -1, -1));
}

void lhistory_t::init()
{
    nodes.clear();
    nodes.push_back(node_t(NOINFO, -1));
}

void zhistory_t::init()
{
    nodes.clear();
    nodes.push_back(node_t(NOINFO, -1, 0, 0));
}

void phistory_t::detach()
{
    // don't delete existing tree, just detach it from root
    // pointers to old tree are still valid, but traversals will ignore it
    node_t &n = node(0);
    n.last = n.next = -1;
    n.finidx = NONFIN;
}

int32_t phistory_t::push(int32_t idx, tag_info_t info)
{
    const int32_t i = static_cast<int32_t>(nodes.size());
    if (idx != -1) {
        node_t &n = node(idx);
        const int32_t a = static_cast<int32_t>(arcs.size());
        arcs.push_back(arc_t(i, n.last, -1));
        if (n.next == -1) {
            n.next = a;
        }
        else {
            arc(n.last).next = a;
        }
        n.last = a;
    }
    nodes.push_back(node_t(info, idx, -1, -1));
    return i;
}

int32_t lhistory_t::push(int32_t idx, tag_info_t info)
{
    const int32_t i = static_cast<int32_t>(nodes.size());
    nodes.push_back(node_t(info, idx));
    return i;
}

int32_t zhistory_t::push(int32_t idx, uint32_t step, tag_info_t info, uint32_t orig)
{
    const int32_t i = static_cast<int32_t>(nodes.size());
    nodes.push_back(node_t(info, idx, step, orig));
    return i;
}

// history type selector
template<sema_t SEMA, eval_t EVAL> struct history_type_t;
template<> struct history_type_t<POSIX, STRICT> {typedef phistory_t type;};
template<> struct history_type_t<LEFTMOST, STRICT> {typedef lhistory_t type;};
template<sema_t SEMA> struct history_type_t<SEMA, LAZY> {typedef zhistory_t type;};

template<typename history_t>
tagver_t last(const history_t &h, hidx_t i, size_t t)
{
    for (; i != HROOT; ) {
        const typename history_t::node_t &n = h.node(i);
        if (n.info.idx == t) {
            return n.info.neg ? TAGVER_BOTTOM : TAGVER_CURSOR;
        }
        i = n.pred;
    }
    return TAGVER_ZERO;
}

template<typename history_t>
int32_t compare_reversed(const history_t &h, hidx_t x, hidx_t y, size_t t)
{
    if (x == y) return 0;

    // compare in reverse, from tail to head: direction makes
    // no difference when comparing for exact coincidence
    for (;;) {
        for (; x != HROOT && h.node(x).info.idx != t; x = h.node(x).pred);
        for (; y != HROOT && h.node(y).info.idx != t; y = h.node(y).pred);

        if (x == y) return 0;
        if (x == HROOT) return -1;
        if (y == HROOT) return 1;

        const typename history_t::node_t &nx = h.node(x), &ny = h.node(y);

        if (nx.info.neg > ny.info.neg) return -1;
        if (nx.info.neg < ny.info.neg) return 1;

        x = nx.pred;
        y = ny.pred;
    }
}

} // namespace re2c

#endif // _RE2C_DFA_TAG_HISTORY_
