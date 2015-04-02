#include "dfa.h"
#include "go.h"

namespace re2c
{

Cases::Cases (const Span * span, uint span_size)
	: def (span_size == 0 ? NULL : span[span_size - 1].to)
	, cases (new Case[span_size])
	, cases_size (0)
{
	for (uint i = 0, lb = 0; i < span_size; ++ i)
	{
		add (lb, span[i].ub, span[i].to);
		lb = span[i].ub;
	}
}

void Cases::add (uint lb, uint ub, State * to)
{
	for (uint i = 0; i < cases_size; ++i)
	{
		if (cases[i].to == to)
		{
			cases[i].ranges.push_back (std::make_pair (lb, ub));
			return;
		}
	}
	cases[cases_size].ranges.push_back (std::make_pair (lb, ub));
	cases[cases_size].to = to;
	++cases_size;
}

Cond::Cond (const std::string & cmp, uint val)
	: compare (cmp)
	, value (val)
{}

Binary::Binary (const Span * s, uint n, const State * next)
	: cond (NULL)
	, thn (NULL)
	, els (NULL)
{
	const uint l = n / 2;
	const uint h = n - l;
	cond = new Cond ("<=", s[l - 1].ub - 1);
	thn = new If (l > 4 ? If::BINARY : If::LINEAR, &s[0], l, next);
	els = new If (h > 4 ? If::BINARY : If::LINEAR, &s[l], h, next);
}

Linear::Linear (const Span * s, uint n, const State * next)
	: branches ()
{
	for (;;)
	{
		const State *bg = s[0].to;
		while (n >= 3 && s[2].to == bg && (s[1].ub - s[0].ub) == 1)
		{
			if (s[1].to == next && n == 3)
			{
				branches.push_back (std::make_pair (new Cond ("!=", s[0].ub), bg));
				return ;
			}
			else
			{
				branches.push_back (std::make_pair (new Cond ("==", s[0].ub), s[1].to));
			}
			n -= 2;
			s += 2;
		}
		if (n == 1)
		{
			if (next == NULL || s[0].to->label != next->label)
			{
				branches.push_back (std::make_pair (static_cast<const Cond *> (NULL), s[0].to));
			}
			return;
		}
		else if (n == 2 && bg == next)
		{
			branches.push_back (std::make_pair (new Cond (">=", s[0].ub), s[1].to));
			return;
		}
		else
		{
			branches.push_back (std::make_pair (new Cond ("<=", s[0].ub - 1), bg));
			n -= 1;
			s += 1;
		}
	}
}

If::If (type_t t, const Span * sp, uint nsp, const State * next)
	: type (t)
	, info ()
{
	switch (type)
	{
		case BINARY:
			info.binary = new Binary (sp, nsp, next);
			break;
		case LINEAR:
			info.linear = new Linear (sp, nsp, next);
			break;
	}
}

SwitchIf::SwitchIf (const Span * sp, uint nsp, const State * next)
	: type (IF)
	, info ()
{
	if ((!sFlag && nsp > 2) || (nsp > 8 && (sp[nsp - 2].ub - sp[0].ub <= 3 * (nsp - 2))))
	{
		type = SWITCH;
		info.cases = new Cases (sp, nsp);
	}
	else if (nsp > 5)
	{
		info.ifs = new If (If::BINARY, sp, nsp, next);
	}
	else
	{
		info.ifs = new If (If::LINEAR, sp, nsp, next);
	}
}

Bitmap::Bitmap (const Span * span, uint nSpans, const Span * hspan, uint hSpans, const BitMap * bm, const State * bm_state, const State * next)
	: bitmap (bm)
	, bitmap_state (bm_state)
	, hgo (hSpans == 0 ? NULL : new SwitchIf (hspan, hSpans, next))
	, lgo (NULL)
{
	Span * bspan = new Span [nSpans];
	uint bSpans = unmap (bspan, span, nSpans, bm_state);
	lgo = bSpans == 0
		? NULL
		:  new SwitchIf (bspan, bSpans, next);
	delete [] bspan;
}

const uint CpgotoTable::TABLE_SIZE = 0x100;

CpgotoTable::CpgotoTable (const Span * span, uint nSpans)
	: table (new const State * [TABLE_SIZE])
{
	uint c = 0;
	for (uint i = 0; i < nSpans; ++i)
	{
		for(; c < span[i].ub && c < TABLE_SIZE; ++c)
		{
			table[c] = span[i].to;
		}
	}
}

Cpgoto::Cpgoto (const Span * span, uint nSpans, const Span * hspan, uint hSpans, const State * next)
	: hgo (hSpans == 0 ? NULL : new SwitchIf (hspan, hSpans, next))
	, table (new CpgotoTable (span, nSpans))
{}

Dot::Dot (const Span * sp, uint nsp, const State * s)
	: from (s)
	, cases (new Cases (sp, nsp))
{}

Go::Go ()
	: nSpans (0)
	, span (NULL)
	, type (EMPTY)
	, info ()
{}

void Go::init (const State * from)
{
	if (nSpans == 0)
	{
		return;
	}

	// initialize high (wide) spans
	uint hSpans = 0;
	const Span * hspan = NULL;
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
	uint nBitmaps = 0;
	const BitMap * bitmap = NULL;
	const State * bitmap_state = NULL;
	for (uint i = 0; i < nSpans; ++i)
	{
		if (span[i].to->isBase)
		{
			const BitMap *b = BitMap::find (span[i].to);
			if (b && matches(b->go->span, b->go->nSpans, b->on, span, nSpans, span[i].to))
			{
				if (bitmap == NULL)
				{
					bitmap = b;
					bitmap_state = span[i].to;
				}
				nBitmaps++;
			}
		}
	}

	const uint dSpans = nSpans - hSpans - nBitmaps;
	if (DFlag)
	{
		type = DOT;
		info.dot = new Dot (span, nSpans, from);
	}
	else if (gFlag && (dSpans >= cGotoThreshold))
	{
		type = CPGOTO;
		info.cpgoto = new Cpgoto (span, nSpans, hspan, hSpans, from->next);
	}
	else if (bFlag && (nBitmaps > 0))
	{
		type = BITMAP;
		info.bitmap = new Bitmap (span, nSpans, hspan, hSpans, bitmap, bitmap_state, from->next);
		bUsedYYBitmap = true;
	}
	else
	{
		type = SWITCH_IF;
		info.switchif = new SwitchIf (span, nSpans, from->next);
	}
}

// All spans in b1 that lead to s1 are pairwise equal to that in b2 leading to s2
bool matches(const Span * b1, uint n1, const State * s1, const Span * b2, uint n2, const State * s2)
{
	const Span * e1 = &b1[n1];
	uint lb1 = 0;
	const Span * e2 = &b2[n2];
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

/*
 * Find all spans, that map to the given state. For each of them,
 * find upper adjacent span, that maps to another state (if such
 * span exists, otherwize try lower one).
 * If input contains single span that maps to the given state,
 * then output contains 0 spans.
 */
uint unmap (Span * new_span, const Span * old_span, uint old_nspans, const State * x)
{
	uint new_nspans = 0;
	for (uint i = 0; i < old_nspans; ++i)
	{
		if (old_span[i].to != x)
		{
			if (new_nspans > 0 && new_span[new_nspans - 1].to == old_span[i].to)
				new_span[new_nspans - 1].ub = old_span[i].ub;
			else
			{
				new_span[new_nspans].to = old_span[i].to;
				new_span[new_nspans].ub = old_span[i].ub;
				++new_nspans;
			}
		}
	}
	if (new_nspans > 0)
		new_span[new_nspans - 1].ub = old_span[old_nspans - 1].ub;
	return new_nspans;
}

} // namespace re2c
