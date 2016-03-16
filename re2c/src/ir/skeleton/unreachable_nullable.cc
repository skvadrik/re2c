#include "src/util/c99_stdint.h"
#include <set>

#include "src/conf/warn.h"
#include "src/globals.h"
#include "src/ir/rule_rank.h"
#include "src/ir/skeleton/path.h"
#include "src/ir/skeleton/skeleton.h"
#include "src/parse/rules.h"

namespace re2c
{

static void calc_reachable(
	const Skeleton &skel,
	std::vector<uint8_t> &loops,
	std::vector<std::set<RuleInfo*> > &reachs,
	size_t i)
{
	const Node &node = skel.nodes[i];
	uint8_t &loop = loops[i];
	std::set<RuleInfo*> &reach = reachs[i];

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
	std::vector<uint8_t> loops(skel.nodes_count);
	std::vector<std::set<RuleInfo*> > reachs(skel.nodes_count);
	calc_reachable(skel, loops, reachs, 0);

	for (uint32_t i = 0; i < skel.nodes_count; ++i) {
		RuleInfo *r1 = skel.nodes[i].rule;
		if (!r1) {
			continue;
		}
		std::set<RuleInfo*>::const_iterator
			rule = reachs[i].begin(),
			end = reachs[i].end();
		for (; rule != end; ++rule) {
			RuleInfo* r2 = *rule;
			if (!r2 || r1->rank == r2->rank) {
				r1->reachable = true;
			} else {
				r1->shadow.insert(r2->loc.line);
			}
		}
	}

	// warn about unreachable rules:
	//   - rules that are shadowed by other rules, e.g. rule '[a]' is shadowed by '[a] [^]'
	//   - infinite rules that consume infinitely many characters and fail on YYFILL, e.g. '[^]*'
	//   - rules that contain never-matching link, e.g. '[]' with option '--empty-class match-none'
	// default rule '*' should not be reported
	for (rules_t::const_iterator i = skel.rules.begin(); i != skel.rules.end(); ++i) {
		const RuleInfo *r = *i;
		if (!r->rank.is_def() && !r->reachable) {
			warn.unreachable_rule(skel.cond, r);
		}
	}

	// warn about nullable rules:
	//    - rules that match empty string
	//    - rules that match empty strins with nonempty trailing context
	// false positives on partially shadowed (yet reachable) rules, e.g.:
	//     [^]?
	for (rules_t::const_iterator i = skel.rules.begin(); i != skel.rules.end(); ++i) {
		const RuleInfo *r = *i;
		if (r->nullable && r->reachable) {
			warn.match_empty_string(r->loc.line);
		}
	}
}

} // namespace re2c
