#include "src/codegen/scc.h"
#include "src/codegen/go.h"
#include "src/ir/dfa/state.h"

namespace re2c {

SCC::SCC (uint32_t size)
	: top (new State * [size])
	, stk (top)
{}

SCC::~SCC ()
{
	delete [] stk;
}

void SCC::traverse (State * x)
{
	*top = x;
	const uint32_t k = static_cast<uint32_t> (++top - stk);
	x->depth = k;

	for (uint32_t i = 0; i < x->go.nSpans; ++i)
	{
		State *y = x->go.span[i].to;
		if (y)
		{
			if (y->depth == 0)
			{
				traverse(y);
			}
			if (y->depth < x->depth)
			{
				x->depth = y->depth;
			}
		}
	}

	if (x->depth == k)
	{
		do
		{
			(*--top)->depth = cInfinity;
			(*top)->link = x;
		}
		while (*top != x);
	}
}

bool state_is_in_non_trivial_SCC (const State * s)
{
	// does not link to self
	if (s->link != s)
	{
		return true;
	}

	// or exists i: (s->go.spans[i].to->link == s)
	//
	// Note: (s->go.spans[i].to == s) is allowed, corresponds to s
	// looping back to itself.
	//
	for (uint32_t i = 0; i < s->go.nSpans; ++i)
	{
		const State* t = s->go.span[i].to;
		if (t && t->link == s)
		{
			return true;
		}
	}
	// otherwise no
	return false;
}

uint32_t maxDist (State * s)
{
	if (s->depth != cInfinity)
	{
		// Already calculated, just return result.
		return s->depth;
	}
	uint32_t mm = 0;

	for (uint32_t i = 0; i < s->go.nSpans; ++i)
	{
		State *t = s->go.span[i].to;
		if (t)
		{
			uint32_t m = 1;
			if (!t->link) // marked as non-key state
			{
				if (t->depth == cInfinity)
				{
					t->depth = maxDist(t);
				}
				m += t->depth;
			}
			if (m > mm)
			{
				mm = m;
			}
		}
	}

	s->depth = mm;
	return mm;
}

void calcDepth (State * head)
{
	State * s;

	// mark non-key states by s->link = NULL ;
	for (s = head; s; s = s->next)
	{
		if (s != head && !state_is_in_non_trivial_SCC(s))
		{
			s->link = NULL;
		}
		//else: key state, leave alone
	}
	for (s = head; s; s = s->next)
	{
		s->depth = cInfinity;
	}

	// calculate max number of transitions before guarantied to reach
	// a key state.
	for (s = head; s; s = s->next)
	{
		maxDist(s);
	}
}

} // namespace re2c
