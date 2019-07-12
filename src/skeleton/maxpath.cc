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

// 0 < DIST_MAX < DIST_ERROR <= std::numeric_limits<uint32_t>::max()
static const uint32_t DIST_ERROR = std::numeric_limits<uint32_t>::max();
static const uint32_t DIST_MAX = DIST_ERROR - 1;

// maximal distance to end node (assuming one iteration per loop)
// different from YYMAXFILL calculation
// in the way it handles loops and empty regexp
static uint32_t calc_dist(const Skeleton &skel
    , std::vector<uint8_t> &loops
    , std::vector<uint32_t> &dists
    , size_t i)
{
    const Node &node = skel.nodes[i];
    uint32_t dist = dists[i];

    if (dist != DIST_ERROR) {
        return dist;
    }

    else if (node.end()) {
        return dists[i] = 0;
    }

    // we cut the looping path, so the current node is like
    // the "end" node; but the actual value for this node
    // is yet to be calculated on the recursive return
    else if (loops[i] > 1) {
        return 0;
    }

    // unroll one iteration of loops
    // (must be consistent with skeleton data generation)
    else {
        local_inc _(loops[i]);

        Node::arcs_t::const_iterator
            arc = node.arcs.begin(),
            end = node.arcs.end();

        // handle all child states before setting this state's suffix
        for (; arc != end; ++arc) {
            const uint32_t d = calc_dist(skel, loops, dists, arc->first);

            // not necessarily true for dists[arc->first]
            DASSERT (d != DIST_ERROR);

            dist = (dist == DIST_ERROR) ? d : std::max(dist, d);
        }

        return dists[i] = std::min(dist + 1, DIST_MAX);
    }
}

// calculate maximal path length, check overflow
uint32_t maxpath(const Skeleton &skel)
{
    std::vector<uint8_t> loops(skel.nodes_count);
    std::vector<uint32_t> dists(skel.nodes_count, DIST_ERROR);
    const uint32_t maxlen = calc_dist(skel, loops, dists, 0);
    if (maxlen == DIST_MAX) {
        fatal("DFA path %sis too long", incond(skel.cond).c_str());
    }
    return maxlen;
}

} // namespace re2c
