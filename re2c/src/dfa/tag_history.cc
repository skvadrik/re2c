#include "src/dfa/tag_history.h"


namespace re2c
{

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
    // compare in reverse, from tail to head: direction makes
    // no difference when comparing for exact coincidence
    for (;;) {
        for (; x != HROOT && tag(x) != t; x = pred(x));
        for (; y != HROOT && tag(y) != t; y = pred(y));
        if (x == HROOT && y == HROOT) return 0;
        if (x == HROOT) return -1;
        if (y == HROOT) return 1;
        if (elem(x) > elem(y)) return -1;
        if (elem(x) < elem(y)) return 1;
        x = pred(x);
        y = pred(y);
    }
}

} // namespace re2c
