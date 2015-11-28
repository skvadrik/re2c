#include <limits>
#include <stdlib.h> // exit

#include "src/codegen/skeleton/skeleton.h"
#include "src/conf/msg.h"
#include "src/ir/regexp/regexp_rule.h"

namespace re2c
{

Node::Node ()
	: arcs ()
	, arcsets ()
	, loop (0)
	, rule (rule_rank_t::none (), false)
	, ctx (false)
	, dist (DIST_ERROR)
	, reachable ()
	, suffix (NULL)
{}

void Node::init (const State * s, const s2n_map & s2n)
{
	const bool is_accepting = s && s->rule;
	if (is_accepting)
	{
		rule.rank = s->rule->rank;
		rule.restorectx = s->rule->ctx->fixedLength () != 0;
	}

	ctx = s && s->isPreCtxt;

	const bool is_final = !s || (s->go.nSpans == 1 && !s->go.span[0].to);
	if (!is_final)
	{
		uint32_t lb = 0;
		for (uint32_t i = 0; i < s->go.nSpans; ++i)
		{
			const Span & span = s->go.span[i];
			Node * n = s2n.find (span.to)->second;
			const uint32_t ub = span.ub - 1;
			arcs[n].push_back (lb);
			if (lb != ub)
			{
				arcs[n].push_back (ub);
			}
			arcsets[n].push_back (std::make_pair (lb, ub));
			lb = span.ub;
		}
	}
}

Node::~Node ()
{
	delete suffix;
}

bool Node::end () const
{
	return arcs.size () == 0;
}

Skeleton::Skeleton (const DFA & dfa, const rules_t & rs)
	// +1 for default DFA state (NULL)
	: name (dfa.name)
	, cond (dfa.cond)
	, line (dfa.line)
	, nodes_count (dfa.nStates + 1) // +1 for default state
	, nodes (new Node [nodes_count])
	, sizeof_key (4)
	, rules (rs)
{
	Node * n;

	// map DFA states to skeleton nodes
	Node::s2n_map s2n;
	n = nodes;
	for (State * s = dfa.head; s; s = s->next, ++n)
	{
		s2n[s] = n;
	}
	s2n[NULL] = n;

	// initialize skeleton nodes
	n = nodes;
	for (State * s = dfa.head; s; s = s->next, ++n)
	{
		n->init (s, s2n);
	}
	n->init (NULL, s2n);

	// calculate maximal path length, check overflow
	nodes->calc_dist ();
	const uint32_t maxlen = nodes->dist;
	if (maxlen == Node::DIST_MAX)
	{
		error ("DFA path %sis too long", incond (cond).c_str ());
		exit (1);
	}

	// calculate maximal rule rank (disregarding default and none rules)
	uint32_t maxrule = 0;
	for (uint32_t i = 0; i < nodes_count; ++i)
	{
		const rule_rank_t r = nodes[i].rule.rank;
		if (!r.is_none () && !r.is_def ())
		{
			maxrule = std::max (maxrule, r.uint32 ());
		}
	}
	// two upper values reserved for default and none rules)
	maxrule += 2;

	// initialize size of key
	const uint32_t max = std::max (maxlen, maxrule);
	if (max <= std::numeric_limits<uint8_t>::max())
	{
		sizeof_key = 1;
	}
	else if (max <= std::numeric_limits<uint16_t>::max())
	{
		sizeof_key = 2;
	}
}

Skeleton::~Skeleton ()
{
	delete [] nodes;
}

template <> uint32_t Skeleton::none<uint32_t> () { return std::numeric_limits<uint32_t>::max(); }
template <> uint16_t Skeleton::none<uint16_t> () { return std::numeric_limits<uint16_t>::max(); }
template <> uint8_t  Skeleton::none<uint8_t>  () { return std::numeric_limits<uint8_t >::max(); }

template <> uint32_t Skeleton::def<uint32_t> () { return std::numeric_limits<uint32_t>::max() - 1; }
template <> uint16_t Skeleton::def<uint16_t> () { return std::numeric_limits<uint16_t>::max() - 1; }
template <> uint8_t  Skeleton::def<uint8_t>  () { return std::numeric_limits<uint8_t >::max() - 1; }

uint32_t Skeleton::rule2key (rule_rank_t r) const
{
	switch (sizeof_key)
	{
		default: // shouldn't happen
		case 4: return rule2key<uint32_t> (r);
		case 2: return rule2key<uint16_t> (r);
		case 1: return rule2key<uint8_t>  (r);
	}
}

} // namespace re2c
