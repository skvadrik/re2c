#ifndef _RE2C_DFA_TAG_HISTORY_
#define _RE2C_DFA_TAG_HISTORY_

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <map>
#include <vector>

#include "src/regexp/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c {

using hidx_t = int32_t;
using tag_path_t = std::vector<tag_info_t>;

static constexpr hidx_t HROOT = 0;
static constexpr tag_info_t NOINFO{~0u, 0};
static constexpr uint32_t NONFIN = ~0u;
static constexpr uint32_t USED = NONFIN - 1;

// tag history for POSIX semantics
struct phistory_t {
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
    inline node_t& node(hidx_t i) { return nodes[static_cast<uint32_t>(i)]; }
    inline const node_t& node(hidx_t i) const { return nodes[static_cast<uint32_t>(i)]; }
    inline arc_t& arc(hidx_t i) { return arcs[static_cast<uint32_t>(i)]; }
    inline const arc_t& arc(hidx_t i) const { return arcs[static_cast<uint32_t>(i)]; }

    template<typename ctx_t> inline hidx_t link(ctx_t& ctx, const typename ctx_t::conf_t& conf);
    template<typename ctx_t> static int32_t precedence(ctx_t& ctx,
                                                       const typename ctx_t::conf_t& x,
                                                       const typename ctx_t::conf_t& y,
                                                       int32_t& prec1,
                                                       int32_t& prec2);

    FORBID_COPY(phistory_t);
};

// tag history for leftmost greedy semantics
struct lhistory_t {
    struct node_t {
        tag_info_t info;
        hidx_t pred;

        inline node_t(tag_info_t info, hidx_t pred): info(info), pred(pred) {}
    };

    std::vector<node_t> nodes;

    inline lhistory_t(): nodes() { init(); }
    inline void init();
    inline node_t& node(hidx_t i) { return nodes[static_cast<uint32_t>(i)]; }
    inline const node_t& node(hidx_t i) const { return nodes[static_cast<uint32_t>(i)]; }
    template<typename ctx_t> inline hidx_t link(ctx_t& ctx, const typename ctx_t::conf_t& conf);
    FORBID_COPY(lhistory_t);
};

void phistory_t::init() {
    nodes.clear();
    arcs.clear();
    nodes.push_back(node_t(NOINFO, -1, -1, -1));
}

void lhistory_t::init() {
    nodes.clear();
    nodes.push_back(node_t(NOINFO, -1));
}

void phistory_t::detach() {
    // Don't delete existing tree, just detach it from root pointers to old tree are still valid,
    // but traversals will ignore it.
    node_t& n = node(0);
    n.last = n.next = -1;
    n.finidx = NONFIN;
}

template<typename ctx_t>
hidx_t phistory_t::link(ctx_t& /*ctx*/, const typename ctx_t::conf_t& conf) {
    const hidx_t idx = conf.thist;
    const int32_t i = static_cast<int32_t>(nodes.size());
    if (idx != -1) {
        node_t& n = node(idx);
        const int32_t a = static_cast<int32_t>(arcs.size());
        arcs.push_back(arc_t(i, n.last, -1));
        if (n.next == -1) {
            n.next = a;
        } else {
            arc(n.last).next = a;
        }
        n.last = a;
    }
    nodes.push_back(node_t(conf.state->tag, idx, -1, -1));
    return i;
}

template<typename ctx_t>
hidx_t lhistory_t::link(ctx_t& /*ctx*/, const typename ctx_t::conf_t& conf) {
    const int32_t i = static_cast<int32_t>(nodes.size());
    nodes.push_back(node_t(conf.state->tag, conf.thist));
    return i;
}

template<typename history_t>
tagver_t last(const history_t& h, hidx_t i, size_t t) {
    for (; i != HROOT; ) {
        const typename history_t::node_t& n = h.node(i);
        if (n.info.idx == t) {
            return n.info.neg ? TAGVER_BOTTOM : TAGVER_CURSOR;
        }
        i = n.pred;
    }
    return TAGVER_ZERO;
}

template<typename history_t>
int32_t compare_reversed(const history_t& h, hidx_t x, hidx_t y, size_t t) {
    if (x == y) return 0;

    // Compare in reverse, from tail to head: direction makes no difference when comparing for exact
    // coincidence.
    for (;;) {
        for (; x != HROOT && h.node(x).info.idx != t; x = h.node(x).pred);
        for (; y != HROOT && h.node(y).info.idx != t; y = h.node(y).pred);

        if (x == y) return 0;
        if (x == HROOT) return -1;
        if (y == HROOT) return 1;

        const typename history_t::node_t& nx = h.node(x), &ny = h.node(y);

        if (nx.info.neg > ny.info.neg) return -1;
        if (nx.info.neg < ny.info.neg) return 1;

        x = nx.pred;
        y = ny.pred;
    }
}

} // namespace re2c

#endif // _RE2C_DFA_TAG_HISTORY_
