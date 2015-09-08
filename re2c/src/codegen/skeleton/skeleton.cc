#include "src/codegen/skeleton/skeleton.h"
#include "src/ir/regexp/regexp_rule.h"
#include "src/util/allocate.h"

namespace re2c
{

Node::Node (const State * s, const s2n_map & s2n)
	: arcs ()
	, arcsets ()
	, loop (0)
	, rule (rule_rank_t::none ())
	, suffix (NULL)
{
	const bool is_accepting = s && s->rule;
	if (is_accepting)
	{
		rule = s->rule->rank;
	}

	const bool is_final = !s || (s->go.nSpans == 1 && !s->go.span[0].to);
	if (is_final)
	{
		suffix = new path_t (rule);
	}
	else
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
	: nodes (allocate<Node> (dfa.nStates + 1))
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
		new (n) Node (s, s2n);
	}
	new (n) Node (NULL, s2n);
}

Skeleton::~Skeleton ()
{
	operator delete (nodes);
}

} // namespace re2c
