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
typedef int32_t prectable_t;
typedef std::vector<tag_info_t> tag_path_t;

static const hidx_t HROOT = 0;
const tag_info_t NOINFO = {0x3fffFFFF, 0};
static const uint32_t NONFIN = ~0u;
static const uint32_t USED = NONFIN - 1;

// Different algorithms need to keep slightly different data in history.
// We store main data in one array, and auxilary data in separate arrays
// (this allows to avoid overhead in algorithms that don't need it).
struct tag_history_t
{
    struct node_t {
        tag_info_t info;
        hidx_t pred;

        inline node_t(tag_info_t info, hidx_t pred)
            : info(info), pred(pred) {}
    };

    struct arc_t {
        hidx_t node;
        hidx_t prev;
        hidx_t next;

        inline arc_t(hidx_t node, hidx_t prev, hidx_t next)
            : node(node), prev(prev), next(next) {}
    };

    struct node1_t {
        hidx_t last;
        hidx_t next;
        uint32_t finidx;

        inline node1_t(hidx_t last, hidx_t next)
            : last(last), next(next), finidx(NONFIN) {}
    };

    struct node2_t {
        uint32_t step;
        uint32_t orig;

        inline node2_t(uint32_t step, uint32_t orig)
            : step(step), orig(orig) {}
    };

    // main history in the form of a backward-linked trie
    std::vector<node_t> nodes;

    // forward-linked history used by POSIX disambiguation
    std::vector<node1_t> nodes1;
    std::vector<arc_t> arcs;

    // auxilary data used by lazy POSIX disambiguation
    std::vector<node2_t> nodes2;

    inline tag_history_t();
    inline void init();
    inline void detach();

    inline node_t &node(hidx_t i) { return nodes[static_cast<uint32_t>(i)]; }
    inline node1_t &node1(hidx_t i) { return nodes1[static_cast<uint32_t>(i)]; }
    inline node2_t &node2(hidx_t i) { return nodes2[static_cast<uint32_t>(i)]; }
    inline arc_t &arc(hidx_t i) { return arcs[static_cast<uint32_t>(i)]; }
    inline const node_t &node(hidx_t i) const { return nodes[static_cast<uint32_t>(i)]; }
    inline const node1_t &node1(hidx_t i) const { return nodes1[static_cast<uint32_t>(i)]; }
    inline const node2_t &node2(hidx_t i) const { return nodes2[static_cast<uint32_t>(i)]; }
    inline const arc_t &arc(hidx_t i) const { return arcs[static_cast<uint32_t>(i)]; }

    inline hidx_t push(hidx_t idx, tag_info_t info);
    inline hidx_t push1(hidx_t idx, tag_info_t info);
    inline hidx_t push2(hidx_t idx, uint32_t step, tag_info_t info, uint32_t orig);

    inline tagver_t last(hidx_t i, size_t t) const;
    inline int32_t compare_reversed(hidx_t x, hidx_t y, size_t t) const;

    FORBID_COPY(tag_history_t);
};

tag_history_t::tag_history_t()
    : nodes()
    , nodes1()
    , arcs()
    , nodes2()
{
    init();
}

void tag_history_t::init()
{
    nodes.clear();
    nodes1.clear();
    arcs.clear();
    nodes2.clear();

    nodes.push_back(node_t(NOINFO, -1));
    nodes1.push_back(node1_t(-1, -1));
    nodes2.push_back(node2_t(0, 0));
}

void tag_history_t::detach()
{
    // don't delete existing tree, just detach it from root
    // pointers to old tree are still valid, but traversals will ignore it
    node1_t &n = node1(0);
    n.last = n.next = -1;
    n.finidx = NONFIN;
}

tagver_t tag_history_t::last(hidx_t i, size_t t) const
{
    for (; i != HROOT; ) {
        const node_t &n = node(i);
        if (n.info.idx == t) {
            return n.info.neg ? TAGVER_BOTTOM : TAGVER_CURSOR;
        }
        i = n.pred;
    }
    return TAGVER_ZERO;
}

int32_t tag_history_t::compare_reversed(hidx_t x, hidx_t y, size_t t) const
{
    if (x == y) return 0;

    // compare in reverse, from tail to head: direction makes
    // no difference when comparing for exact coincidence
    for (;;) {
        for (; x != HROOT && node(x).info.idx != t; x = node(x).pred);
        for (; y != HROOT && node(y).info.idx != t; y = node(y).pred);

        if (x == y) return 0;
        if (x == HROOT) return -1;
        if (y == HROOT) return 1;

        const node_t &nx = node(x), &ny = node(y);

        if (nx.info.neg > ny.info.neg) return -1;
        if (nx.info.neg < ny.info.neg) return 1;

        x = nx.pred;
        y = ny.pred;
    }
}

int32_t tag_history_t::push(int32_t idx, tag_info_t info)
{
    const int32_t i = static_cast<int32_t>(nodes.size());
    nodes.push_back(node_t(info, idx));
    return i;
}

int32_t tag_history_t::push1(int32_t idx, tag_info_t info)
{
    const int32_t i = static_cast<int32_t>(nodes.size());
    if (idx != -1) {
        node1_t &n = node1(idx);
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
    nodes.push_back(node_t(info, idx));
    nodes1.push_back(node1_t(-1, -1));
    return i;
}

int32_t tag_history_t::push2(int32_t idx, uint32_t step, tag_info_t info, uint32_t orig)
{
    const int32_t i = static_cast<int32_t>(nodes.size());
    nodes.push_back(node_t(info, idx));
    nodes2.push_back(node2_t(step, orig));
    return i;
}

} // namespace re2c

#endif // _RE2C_DFA_TAG_HISTORY_
