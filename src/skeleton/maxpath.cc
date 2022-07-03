#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "src/msg/msg.h"
#include "src/skeleton/skeleton.h"
#include "src/util/check.h"

namespace re2c {
namespace {

// 0 < DIST_MAX < DIST_ERROR <= std::numeric_limits<uint32_t>::max()
static constexpr uint32_t DIST_ERROR = std::numeric_limits<uint32_t>::max();
static constexpr uint32_t DIST_MAX = DIST_ERROR - 1;

struct StackItem {
    uint32_t node;
    uint32_t dist;
    Node::arcs_t::const_iterator arc;
};

} // anonymous namespace

// Calculate maximal path length (check overflow). Maximal distance to end node (assuming one
// iteration per loop) is different from YYMAXFILL calculation in the way it handles loops and
// empty regexp.
Ret maxpath(const Skeleton& skel, uint32_t& dist) {
    std::vector<uint8_t> loops(skel.nodes_count);
    std::vector<uint32_t> dists(skel.nodes_count, DIST_ERROR);
    std::vector<StackItem> stack;
    stack.reserve(skel.nodes_count);

    // DFS "return value"
    dist = 0;

    stack.push_back({0, 0, skel.nodes[0].arcs.begin()});

    while (!stack.empty()) {
        StackItem i = stack.back();
        stack.pop_back();
        const Node& node = skel.nodes[i.node];

        if (i.arc == node.arcs.begin()) {
            // DFS recursive enter
            if (dists[i.node] != DIST_ERROR) {
                // already computed distance for this node
            } else if (node.end() || loops[i.node] > 1) {
                // terminate recursion, set zero distance (loops are unrolled once, which must be in
                // sync with skeleton data generation)
                dists[i.node] = 0;
            } else {
                ++loops[i.node];
                DCHECK(i.dist == 0);

                const uint32_t succ = static_cast<uint32_t>(i.arc->first);

                // reschedule this node with the next successor
                stack.push_back({i.node, 0, ++i.arc});

                // schedule the first successor node
                stack.push_back({succ, 0, skel.nodes[succ].arcs.begin()});
            }
            dist = dists[i.node];
        } else if (i.arc == node.arcs.end()) {
            // DFS recursive return
            --loops[i.node];

            // use last successor's distance
            DCHECK(dist != DIST_ERROR);
            dist = std::max(i.dist, dist);

            // all successors traversed, set this node's distance
            DCHECK(dist < DIST_MAX);
            dist = dists[i.node] = dist + 1;
            if (dist == DIST_MAX) break;
        } else {
            // use he previous successor's distance
            DCHECK(dist != DIST_ERROR);
            dist = std::max(i.dist, dist);

            const uint32_t succ = static_cast<uint32_t>(i.arc->first);

            // reschedule this node with the next successor and updated distance
            stack.push_back({i.node, dist, ++i.arc});

            // schedule the current successor node
            stack.push_back({succ, 0, skel.nodes[succ].arcs.begin()});
        }
    }

    if (dist == DIST_MAX) {
        RET_FAIL(error("DFA path %sis too long", incond(skel.cond).c_str()));
    }
    return Ret::OK;
}

} // namespace re2c
