#include "dfa.h"
#include "go.h"
#include "print.h"

namespace re2c
{

uint Span::show (std::ostream & o, uint lb) const
{
	if (to)
	{
		printSpan(o, lb, ub);
		o << " " << to->label << "; ";
	}
	return ub;
}

Go::Go ()
	: nSpans (0)
	, hSpans (0)
	, span (NULL)
	, hspan (NULL)
	, nBitmaps (0)
	, bitmaps (NULL)
{}

Go::~Go ()
{
	delete [] bitmaps;
}

void Go::init ()
{
	// initialize high (wide) spans
	for (uint i = 0; i < nSpans; ++i)
	{
		if (span[i].ub > 0x100)
		{
			hspan = &span[i];
			hSpans = nSpans - i;
			break;
		}
	}
	// initialize bitmaps
	bitmaps = new const BitMap * [nSpans];
	memset (bitmaps, 0, nSpans * sizeof (BitMap *));
	for (uint i = 0; i < nSpans; ++i)
	{
		if (span[i].to && span[i].to->isBase)
		{
			const BitMap *b = BitMap::find (span[i].to);
			if (b && matches(b->go, b->on, this, span[i].to))
			{
				bitmaps[i] = b;
				nBitmaps++;
			}
		}
	}
}

// All spans in g1 that lead to s1 are pairwise equal to that in g2 leading to s2
bool matches(const Go * g1, const State * s1, const Go * g2, const State * s2)
{
	Span *b1 = g1->span, *e1 = &b1[g1->nSpans];
	uint lb1 = 0;
	Span *b2 = g2->span, *e2 = &b2[g2->nSpans];
	uint lb2 = 0;

	for (;;)
	{
		for (; b1 < e1 && b1->to != s1; ++b1)
		{
			lb1 = b1->ub;
		}
		for (; b2 < e2 && b2->to != s2; ++b2)
		{
			lb2 = b2->ub;
		}
		if (b1 == e1)
		{
			return b2 == e2;
		}
		if (b2 == e2)
		{
			return false;
		}
		if (lb1 != lb2 || b1->ub != b2->ub)
		{
			return false;
		}
		++b1;
		++b2;
	}
}

} // namespace re2c
