#include "src/util/c99_stdint.h"
#include <set>

#include "src/conf/warn.h"
#include "src/globals.h"
#include "src/ir/skeleton/path.h"
#include "src/ir/skeleton/skeleton.h"

namespace re2c
{

static void calc_reachable(
	const Skeleton &skel,
	std::vector<uint8_t> &loops,
	std::vector<std::set<size_t> > &reachs,
	size_t i)
{
	const Node &node = skel.nodes[i];
	uint8_t &loop = loops[i];
	std::set<size_t> &reach = reachs[i];

	if (!reach.empty()) {
		return;
	} else if (node.end()) {
		reach.insert(node.rule);
	} else if (loop < 2) {
		local_inc _(loop);
		Node::arcs_t::const_iterator
			arc = node.arcs.begin(),
			end = node.arcs.end();
		for (; arc != end; ++arc) {
			const size_t j = arc->first;
			calc_reachable(skel, loops, reachs, j);
			reach.insert(reachs[j].begin(), reachs[j].end());
		}
	}
}

void warn_unreachable_nullable_rules(const Skeleton &skel)
{
	// calculate reachable rules
	const size_t nnodes = skel.nodes_count;
	std::vector<uint8_t> loops(nnodes);
	std::vector<std::set<size_t> > reachs(nnodes);
	calc_reachable(skel, loops, reachs, 0);

	std::vector<Rule> &rules = skel.rules;
	const size_t nrules = rules.size();

	for (size_t i = 0; i < nnodes; ++i) {
		const size_t r1 = skel.nodes[i].rule;
		if (r1 == Rule::NONE) {
			continue;
		}
		std::set<size_t>::const_iterator
			rule = reachs[i].begin(),
			end = reachs[i].end();
		for (; rule != end; ++rule) {
			const size_t r2 = *rule;
			if (r2 == Rule::NONE || r1 == r2) {
				rules[r1].reachable = true;
			} else {
				rules[r1].shadow.insert(rules[r2].info->loc.line);
			}
		}
	}

	// warn about unreachable rules:
	//   - rules that are shadowed by other rules, e.g. rule '[a]' is shadowed by '[a] [^]'
	//   - infinite rules that consume infinitely many characters and fail on YYFILL, e.g. '[^]*'
	//   - rules that contain never-matching link, e.g. '[]' with option '--empty-class match-none'
	// default rule '*' should not be reported
	for (size_t i = 0; i < nrules; ++i) {
		const Rule &rule = rules[i];
		if (i != skel.defrule && !rule.reachable) {
			warn.unreachable_rule(skel.cond, rule);
		}
	}

	// warn about nullable rules:
	//    - rules that match empty string
	//    - rules that match empty strins with nonempty trailing context
	// false positives on partially shadowed (yet reachable) rules, e.g.:
	//     [^]?
	for (size_t i = 0; i < nrules; ++i) {
		const Rule &rule = rules[i];
		if (rule.nullable && rule.reachable) {
			warn.match_empty_string(rule.info->loc.line);
		}
	}
}

} // namespace re2c
