#include "src/util/c99_stdint.h"
#include <stdio.h>
#include <algorithm>
#include <map>
#include <memory>
#include <utility>
#include <valarray>
#include <vector>

#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/regexp/rule.h"
#include "src/skeleton/path.h"
#include "src/skeleton/skeleton.h"
#include "src/util/u32lim.h"


namespace re2c {

// See note [counting skeleton edges].
// Type for counting arcs in paths that cause undefined behaviour.
// These paths are stored on heap, so the limit should be low.
// Most real-world cases have only a few short paths.
// We don't need all paths anyway, just some examples.
typedef u32lim_t<1024> ucf_size_t; // ~1Kb

// UCF stands for 'undefined control flow'
struct ucf_t
{
    std::valarray<bool> loops;
    std::vector<path_t> paths;
    path_t prefix;
    ucf_size_t size;

    explicit ucf_t(size_t nnodes): loops(nnodes), paths(),
        prefix(0), size(ucf_size_t::from32(0u)) {}
};

// We don't need all patterns that cause undefined behaviour.
// We only need some examples, the shorter the better.
static void naked_paths(
    const Skeleton &skel,
    ucf_t &ucf,
    size_t i)
{
    const Node &node = skel.nodes[i];
    bool &loop = ucf.loops[i];
    path_t &prefix = ucf.prefix;
    ucf_size_t &size = ucf.size;

    if (node.rule != Rule::NONE) {
        return;
    } else if (node.end()) {
        ucf.paths.push_back(prefix);
        size = size + ucf_size_t::from64(prefix.len());
    } else if (!loop) {
        loop = true;
        Node::arcs_t::const_iterator
            arc = node.arcs.begin(),
            end = node.arcs.end();
        for (; arc != end && !size.overflow(); ++arc) {
            const size_t j = arc->first;
            prefix.push(j);
            naked_paths(skel, ucf, j);
            prefix.pop();
        }
    }
}

void warn_undefined_control_flow(const Skeleton &skel)
{
    ucf_t ucf(skel.nodes_count);
    naked_paths(skel, ucf, 0);
    if (!ucf.paths.empty()) {
        skel.msg.warn.undefined_control_flow(skel, ucf.paths, ucf.size.overflow());
    } else if (ucf.size.overflow()) {
        skel.msg.warn.fail(Warn::UNDEFINED_CONTROL_FLOW, skel.loc,
            "DFA is too large to check undefined control flow");
    }
}

static void fprint_default_arc(FILE *f, const Node::arc_t &arc)
{
    const size_t ranges = arc.size();
    if (ranges == 1 && arc[0].lower == arc[0].upper) {
        fprintf(f, "\\x%X", arc[0].lower);
    } else {
        fprintf(f, "[");
        for (size_t i = 0; i < ranges; ++i) {
            const uint32_t
                l = arc[i].lower,
                u = arc[i].upper;
            fprintf(f, "\\x%X", l);
            if (l != u) {
                fprintf(f, "-\\x%X", u);
            }
        }
        fprintf(f, "]");
    }
}

void fprint_default_path(
    FILE *f,
    const Skeleton &skel,
    const path_t &p)
{
    fprintf(f, "'");
    const size_t len = p.len();
    for (size_t i = 0; i < len; ++i) {
        if (i > 0) {
            fprintf(f, " ");
        }
        const Node::arc_t &arc = p.arc(skel, i);
        fprint_default_arc(stderr, arc);
    }
    fprintf(f, "'");
}

} // namespace re2c
