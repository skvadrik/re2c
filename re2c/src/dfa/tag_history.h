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
struct clos_t;

static const hidx_t HROOT = -1;

typedef std::vector<tag_info_t> tag_path_t;

struct tag_history_t
{
    // the whole tree of tags found by the epsilon-closure
    // (a bunch of separate subtrees for each tag with common root)
    struct node_t {
        hidx_t pred;
        tag_info_t info;
    };
    std::vector<node_t> nodes;

    inline tag_history_t(): nodes() {};
    inline const node_t &at(hidx_t i) const { return nodes[static_cast<uint32_t>(i)]; }
    inline tag_info_t info(hidx_t i) const { return at(i).info; }
    inline hidx_t pred(hidx_t i) const { return at(i).pred; }
    inline tagver_t elem(hidx_t i) const { return at(i).info.neg ? TAGVER_BOTTOM : TAGVER_CURSOR; }
    inline size_t tag(hidx_t i) const { return at(i).info.idx; }
    inline hidx_t push(hidx_t i, tag_info_t info);
    inline tagver_t last(hidx_t i, size_t t) const;
    inline int32_t compare_reversed(hidx_t x, hidx_t y, size_t t) const;
    FORBID_COPY(tag_history_t);
};

hidx_t tag_history_t::push(hidx_t idx, tag_info_t info)
{
    node_t x = {idx, info};
    nodes.push_back(x);
    return static_cast<hidx_t>(nodes.size() - 1);
}

tagver_t tag_history_t::last(hidx_t i, size_t t) const
{
    for (; i != HROOT; i = pred(i)) {
        if (tag(i) == t) return elem(i);
    }
    return TAGVER_ZERO;
}

int32_t tag_history_t::compare_reversed(hidx_t x, hidx_t y, size_t t) const
{
    if (x == y) return 0;

    // compare in reverse, from tail to head: direction makes
    // no difference when comparing for exact coincidence
    for (;;) {
        for (; x != HROOT && tag(x) != t; x = pred(x));
        for (; y != HROOT && tag(y) != t; y = pred(y));
        if (x == y) return 0;
        if (x == HROOT) return -1;
        if (y == HROOT) return 1;
        if (elem(x) > elem(y)) return -1;
        if (elem(x) < elem(y)) return 1;
        x = pred(x);
        y = pred(y);
    }
}

} // namespace re2c

#endif // _RE2C_DFA_TAG_HISTORY_
