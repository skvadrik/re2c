#include <map>
#include <utility>
#include <vector>

#include "src/conf/warn.h"
#include "src/globals.h"
#include "src/ir/rule_rank.h"
#include "src/ir/skeleton/path.h"
#include "src/ir/skeleton/skeleton.h"
#include "src/util/u32lim.h"

namespace re2c
{

// We don't need all patterns that cause undefined behaviour.
// We only need some examples, the shorter the better.
// See also note [counting skeleton edges].
void Node::naked_paths(
	path_t &prefix,
	std::vector<path_t> &paths,
	nakeds_t &size)
{
	if (rule) {
		return;
	} else if (end()) {
		paths.push_back(prefix);
		size = size + nakeds_t::from64(prefix.len());
	} else if (loop < 2) {
		local_inc _(loop);
		for (arcsets_t::iterator i = arcsets.begin();
			i != arcsets.end() && !size.overflow(); ++i) {
			prefix.push(i->first);
			i->first->naked_paths(prefix, paths, size);
			prefix.pop();
		}
	}
}

void Skeleton::warn_undefined_control_flow()
{
	path_t prefix(&nodes[0]);
	std::vector<path_t> paths;
	Node::nakeds_t size = Node::nakeds_t::from32(0u);

	nodes->naked_paths(prefix, paths, size);

	if (!paths.empty()) {
		warn.undefined_control_flow(line, cond, paths, size.overflow());
	} else if (size.overflow()) {
		warn.fail(Warn::UNDEFINED_CONTROL_FLOW, line,
			"DFA is too large to check undefined control flow");
	}
}

// define strict weak ordering on patterns:
// 1st criterion is length (short patterns go first)
// 2nd criterion is lexicographical order (applies to patterns of equal length)
bool compare_default_paths(const path_t &p1, const path_t &p2)
{
	const size_t l1 = p1.len();
	const size_t l2 = p2.len();
	if (l1 == l2) {
		for (size_t i = 0; i < l1; ++i) {
			const Node::arcset_t
				&a1 = p1.arcset(i),
				&a2 = p2.arcset(i);
			const size_t s1 = a1.size();
			const size_t s2 = a2.size();
			for (size_t j = 0; j < s1; ++j) {
				if (j == s2 || a2[j] < a1[j]) {
					return false;
				} else if (a1[j] < a2[j]) {
					return true;
				}
			}
		}
		return false;
	} else {
		return l1 < l2;
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

void fprint_default_path(FILE *f, const path_t &p)
{
	fprintf(f, "'");
	const size_t len = p.len();
	for (size_t i = 0; i < len; ++i) {
		if (i > 0) {
			fprintf(f, " ");
		}
		const Node::arcset_t &arc = p.arcset(i);
		fprint_default_arc(stderr, arc);
	}
	fprintf(f, "'");
}

} // namespace re2c
