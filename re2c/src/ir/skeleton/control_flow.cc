#include <vector>

#include "src/conf/warn.h"
#include "src/globals.h"
#include "src/ir/rule_rank.h"
#include "src/ir/skeleton/path.h"
#include "src/ir/skeleton/skeleton.h"
#include "src/util/u32lim.h"

namespace re2c
{

// See note [counting skeleton edges].
// Type for counting arcs in paths that cause undefined behaviour.
// These paths are stored on heap, so the limit should be low.
// Most real-world cases have only a few short paths.
// We don't need all paths anyway, just some examples.
typedef u32lim_t<1024> nakeds_t; // ~1Kb

// We don't need all patterns that cause undefined behaviour.
// We only need some examples, the shorter the better.
static void naked_paths(
	Skeleton &skel,
	std::vector<path_t> &paths,
	path_t &prefix,
	nakeds_t &size,
	size_t i)
{
	const Node &node = skel.nodes[i];
	uint8_t &loop = skel.loops[i];

	if (node.rule) {
		return;
	} else if (node.end()) {
		paths.push_back(prefix);
		size = size + nakeds_t::from64(prefix.len());
	} else if (loop < 2) {
		local_inc _(loop);
		Node::arcsets_t::const_iterator
			arc = node.arcsets.begin(),
			end = node.arcsets.end();
		for (; arc != end && !size.overflow(); ++arc) {
			const size_t j = arc->first;
			prefix.push(j);
			naked_paths(skel, paths, prefix, size, j);
			prefix.pop();
		}
	}
}

void warn_undefined_control_flow(Skeleton &skel)
{
	path_t prefix(0);
	std::vector<path_t> paths;
	nakeds_t size = nakeds_t::from32(0u);

	naked_paths(skel, paths, prefix, size, 0);

	if (!paths.empty()) {
		warn.undefined_control_flow(skel, paths, size.overflow());
	} else if (size.overflow()) {
		warn.fail(Warn::UNDEFINED_CONTROL_FLOW, skel.line,
			"DFA is too large to check undefined control flow");
	}
}

static void fprint_default_arc(FILE *f, const Node::arcset_t &arc)
{
	const size_t ranges = arc.size();
	if (ranges == 1 && arc[0].first == arc[0].second) {
		fprintf(f, "\\x%X", arc[0].first);
	} else {
		fprintf(f, "[");
		for (size_t i = 0; i < ranges; ++i) {
			const uint32_t l = arc[i].first;
			const uint32_t u = arc[i].second;
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
		const Node::arcset_t &arc = p.arcset(skel, i);
		fprint_default_arc(stderr, arc);
	}
	fprintf(f, "'");
}

} // namespace re2c
