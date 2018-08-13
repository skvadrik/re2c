#ifndef _RE2C_DFA_TAG_HISTORY_
#define _RE2C_DFA_TAG_HISTORY_

#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <sys/types.h>
#include <vector>

#include "src/re/tag.h"
#include "src/util/forbid_copy.h"

namespace re2c
{

typedef uint32_t hidx_t;
typedef int32_t prectable_t;
struct clos_t;

static const hidx_t HROOT = ~0u;

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

    // reconstruct paths for comparison
    tag_path_t path1;
    tag_path_t path2;

    tag_history_t(): nodes(), path1(), path2() {}
    hidx_t pred(hidx_t i) const { return nodes[i].pred; }
    tag_info_t info(hidx_t i) const { return nodes[i].info; }
    tagver_t elem(hidx_t i) const { return nodes[i].info.neg ? TAGVER_BOTTOM : TAGVER_CURSOR; }
    size_t tag(hidx_t i) const { return nodes[i].info.idx; }
    hidx_t push(hidx_t i, tag_info_t info);
    tagver_t last(hidx_t i, size_t t) const;
    int32_t compare_reversed(hidx_t x, hidx_t y, size_t t) const;
    FORBID_COPY(tag_history_t);
};

} // namespace re2c

#endif // _RE2C_DFA_TAG_HISTORY_
