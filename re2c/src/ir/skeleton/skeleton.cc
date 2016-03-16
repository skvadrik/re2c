#include <algorithm>

#include "src/ir/dfa/dfa.h"
#include "src/ir/skeleton/path.h"
#include "src/ir/skeleton/skeleton.h"

namespace re2c
{

Node::Node() :
	arcs(),
	arcsets(),
	rule(NULL),
	ctx(false)
{}

void Node::init(
	bool c,
	RuleInfo *r,
	const std::vector<std::pair<size_t, uint32_t> > &a)
{
	rule = r;
	ctx = c;

	uint32_t lb = 0;
	std::vector<std::pair<size_t, uint32_t> >::const_iterator
		i = a.begin(),
		e = a.end();
	for (; i != e; ++i) {
		const size_t n = i->first;
		const uint32_t ub = i->second - 1;

		// pick at most 0x100 unique edges from this range
		// (for 1-byte code units this covers the whole range: [0 - 0xFF])
		//   - range bounds must be included
		//   - values should be evenly distributed
		//   - values should be deterministic
		const uint32_t step = 1 + (ub - lb) / 0x100;
		for (uint32_t c = lb; c < ub; c += step) {
			arcs[n].push_back(c);
		}
		arcs[n].push_back(ub);

		arcsets[n].push_back(std::make_pair(lb, ub));
		lb = ub + 1;
	}
}

bool Node::end() const
{
	return arcs.size() == 0;
}

Skeleton::Skeleton(
	const dfa_t &dfa,
	const charset_t &cs,
	const rules_t &rs,
	const std::string &dfa_name,
	const std::string &dfa_cond,
	uint32_t dfa_line) :
		name(dfa_name),
		cond(dfa_cond),
		line(dfa_line),
		nodes_count(dfa.states.size() + 1), // +1 for default state
		nodes(new Node[nodes_count]),
		sizeof_key(4),
		rules(rs)
{
	const size_t nc = cs.size() - 1;

	// initialize skeleton nodes
	for (size_t i = 0; i < nodes_count - 1; ++i) {
		dfa_state_t *s = dfa.states[i];
		std::vector<std::pair<size_t, uint32_t> > arcs;
		for (size_t c = 0; c < nc;) {
			const size_t j = s->arcs[c];
			for (;++c < nc && s->arcs[c] == j;);
			const size_t to = j == dfa_t::NIL
				? nodes_count - 1
				: j;
			arcs.push_back(std::make_pair(to, cs[c]));
		}
		// all arcs go to default node => this node is final, drop arcs
		if (arcs.size() == 1 && arcs[0].first == nodes_count - 1) {
			arcs.clear();
		}
		nodes[i].init(s->ctx, s->rule, arcs);
	}

	const uint32_t maxlen = maxpath(*this);

	// calculate maximal rule rank (disregarding default and none rules)
	uint32_t maxrule = 0;
	for (uint32_t i = 0; i < nodes_count; ++i) {
		const RuleInfo *r = nodes[i].rule;
		if (r && !r->rank.is_def()) {
			maxrule = std::max(maxrule, r->rank.uint32());
		}
	}
	// two upper values reserved for default and none rules)
	maxrule += 2;

	// initialize size of key
	const uint32_t max = std::max(maxlen, maxrule);
	if (max <= std::numeric_limits<uint8_t>::max()) {
		sizeof_key = 1;
	} else if (max <= std::numeric_limits<uint16_t>::max()) {
		sizeof_key = 2;
	}
}

Skeleton::~Skeleton()
{
	delete[] nodes;
}

uint32_t Skeleton::rule2key(rule_rank_t r) const
{
	switch (sizeof_key) {
		default: // shouldn't happen
		case 4: return rule2key<uint32_t>(r);
		case 2: return rule2key<uint16_t>(r);
		case 1: return rule2key<uint8_t>(r);
	}
}

} // namespace re2c
