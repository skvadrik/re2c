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
	, rule (rule_rank_t::none ())
	, restorectx (false)
	, ctx (false)
	, dist (DIST_ERROR)
	, suffix (NULL)
{}

void Node::init (const State * s, const s2n_map & s2n)
{
	const bool is_accepting = s && s->rule;
	if (is_accepting)
	{
		rule = s->rule->rank;
		restorectx = s->rule->ctx->fixedLength () != 0;
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

Skeleton::Skeleton (const DFA & dfa)
	// +1 for default DFA state (NULL)
	: name (dfa.name)
	, cond (dfa.cond)
	, line (dfa.line)
	, nodes_count (dfa.nStates + 1) // +1 for default state
	, nodes (new Node [nodes_count])
	, sizeof_key (4)
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

	// calculate maximal rule rank
	uint32_t maxrule = 0;
	for (uint32_t i = 0; i < nodes_count; ++i)
	{
		const rule_rank_t r = nodes[i].rule;
		if (!r.is_none ())
		{
			maxrule = std::max (maxrule, r.uint32 ());
		}
	}

	// initialize size of key
	const uint32_t max = std::max (maxlen, maxrule);
	if (max < UINT8_MAX)
	{
		sizeof_key = 1;
	}
	else if (max < UINT16_MAX)
	{
		sizeof_key = 2;
	}
}

Skeleton::~Skeleton ()
{
	delete [] nodes;
}

template <> uint32_t Skeleton::maxkey<uint32_t> () { return UINT32_MAX; }
template <> uint16_t Skeleton::maxkey<uint16_t> () { return UINT16_MAX; }
template <> uint8_t  Skeleton::maxkey<uint8_t>  () { return UINT8_MAX;  }

uint32_t Skeleton::maxkey () const
{
	switch (sizeof_key)
	{
		default: // shouldn't happen
		case 4: return maxkey<uint32_t> ();
		case 2: return maxkey<uint16_t> ();
		case 1: return maxkey<uint8_t>  ();
	}
}

} // namespace re2c
