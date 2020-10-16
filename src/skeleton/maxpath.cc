#include <stddef.h>
#include "src/util/c99_stdint.h"
#include <algorithm>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "src/debug/debug.h"
#include "src/msg/msg.h"
#include "src/skeleton/skeleton.h"


namespace re2c {
namespace {

// 0 < DIST_MAX < DIST_ERROR <= std::numeric_limits<uint32_t>::max()
static const uint32_t DIST_ERROR = std::numeric_limits<uint32_t>::max();
static const uint32_t DIST_MAX = DIST_ERROR - 1;

struct StackItem {
    uint32_t node;
    uint32_t dist;
    Node::arcs_t::const_iterator arc;
};

} // anonymous namespace

// Calculate maximal path length (check overflow).
// Maximal distance to end node (assuming one iteration per loop) is different
// from YYMAXFILL calculation in the way it handles loops and empty regexp.
uint32_t maxpath(const Skeleton &skel)
{
    std::vector<uint8_t> loops(skel.nodes_count);
    std::vector<uint32_t> dists(skel.nodes_count, DIST_ERROR);
    std::vector<StackItem> stack;
    stack.reserve(skel.nodes_count);

    // DFS "return value"
    uint32_t dist = 0;

    const StackItem i0 = {0, 0, skel.nodes[0].arcs.begin()};
    stack.push_back(i0);

    while (!stack.empty()) {
        StackItem i = stack.back();
        stack.pop_back();
        const Node &node = skel.nodes[i.node];

        if (i.arc == node.arcs.begin()) {
            // DFS recursive enter
            if (dists[i.node] != DIST_ERROR) {
                // already computed distance for this node
            }
            else if (node.end() || loops[i.node] > 1) {
                // terminate recursion, set zero distance (loops are unrolled
                // once, which must be in sync with skeleton data generation)
                dists[i.node] = 0;
            }
            else {
                ++loops[i.node];
                DASSERT(i.dist == 0);

                const uint32_t succ = static_cast<uint32_t>(i.arc->first);

                // reschedule this node with the next successor
                StackItem k = {i.node, 0, ++i.arc};
                stack.push_back(k);

                // schedule the first successor node
                StackItem j = {succ, 0, skel.nodes[succ].arcs.begin()};
                stack.push_back(j);
            }
            dist = dists[i.node];
        }
        else if (i.arc == node.arcs.end()) {
            // DFS recursive return
            --loops[i.node];

            // use last successor's distance
            DASSERT(dist != DIST_ERROR);
            dist = std::max(i.dist, dist);

            // all successors traversed, set this node's distance
            DASSERT(dist < DIST_MAX);
            dist = dists[i.node] = dist + 1;
            if (dist == DIST_MAX) break;
        }
        else {
            // use he previous successor's distance
            DASSERT(dist != DIST_ERROR);
            dist = std::max(i.dist, dist);

            const uint32_t succ = static_cast<uint32_t>(i.arc->first);

            // reschedule this node with the next successor and updated distance
            StackItem k = {i.node, dist, ++i.arc};
            stack.push_back(k);

            // schedule the current successor node
            StackItem j = {succ, 0, skel.nodes[succ].arcs.begin()};
            stack.push_back(j);
        }
    }

    if (dist == DIST_MAX) {
        error("DFA path %sis too long", incond(skel.cond).c_str());
        exit(1);
    }
    return dist;
}

} // namespace re2c
