#include <algorithm>
#include <string.h>

#include "src/ir/dfa/dfa.h"
#include "src/ir/skeleton/path.h"
#include "src/ir/skeleton/skeleton.h"

namespace re2c
{

Node::Node()
	: arcs()
	, rule(Rule::NONE)
	, trail(Tag::NONE)
	, trver(TAGVER_ZERO)
	, tags(ZERO_TAGS)
{}

Node::~Node()
{
	delete[] tags;
}

void Node::init(const bool *ts, size_t r, size_t tr, tagver_t tv,
	const std::vector<std::pair<size_t, uint32_t> > &a)
{
	rule = r;
	tags = ts;
	trail = tr;
	trver = tv;

	std::vector<std::pair<size_t, uint32_t> >::const_iterator
		i = a.begin(),
		e = a.end();
	for (uint32_t l = 0; i != e; ++i) {
		const uint32_t u = i->second;
		arcs[i->first].push_back(std::make_pair(l, u - 1));
		l = u;
	}
}

bool Node::end() const
{
	return arcs.size() == 0;
}

Skeleton::Skeleton(
	const dfa_t &dfa,
	const charset_t &cs,
	size_t def,
	const std::string &dfa_name,
	const std::string &dfa_cond,
	uint32_t dfa_line)
	: name(dfa_name)
	, cond(dfa_cond)
	, line(dfa_line)
	, nodes_count(dfa.states.size() + 1) // +1 for default state
	, nodes(new Node[nodes_count])
	, sizeof_key(8)
	, defrule(def)
	, tags(dfa.tags)
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

		// in skeleton we are only interested in trailing contexts
		// which may be attributed to states rather than transitions
		// trailing context also cannot have fallback tag
		bool *tags = new bool[static_cast<size_t>(dfa.maxtagver) + 1]();
		for (size_t c = 0; c <= nc; ++c) {
			for (tagsave_t *p = s->tcmd[c].save; p; p = p->next) {
				tags[p->ver] = true;
			}
		}

		size_t trail = Tag::NONE;
		tagver_t trver = TAGVER_ZERO;
		if (s->rule != Rule::NONE) {
			trail = dfa.rules[s->rule].trail;
			if (trail != Tag::NONE) {
				trver = dfa.rules[s->rule].tags[trail];
			}
		}

		nodes[i].init(tags, s->rule, trail, trver, arcs);
	}

	// initialize size of key
	const size_t maxlen = maxpath(*this);
	const size_t maxrule = dfa.rules.size() + 1; // +1 for none-rule
	const size_t max = std::max(maxlen, maxrule);
	if (max <= std::numeric_limits<uint8_t>::max()) {
		sizeof_key = 1;
	} else if (max <= std::numeric_limits<uint16_t>::max()) {
		sizeof_key = 2;
	} else if (max <= std::numeric_limits<uint32_t>::max()) {
		sizeof_key = 4;
	}
}

Skeleton::~Skeleton()
{
	delete[] nodes;
}

size_t Skeleton::rule2key(size_t r) const
{
	switch (sizeof_key) {
		default: // shouldn't happen
		case 8: return rule2key<uint64_t>(r, defrule);
		case 4: return rule2key<uint32_t>(r, defrule);
		case 2: return rule2key<uint16_t>(r, defrule);
		case 1: return rule2key<uint8_t>(r, defrule);
	}
}

} // namespace re2c
