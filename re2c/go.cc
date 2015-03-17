#include "dfa.h"
#include "go.h"
#include "indent.h"
#include "print.h"

namespace re2c
{

static std::string space(uint this_label)
{
	int nl = next_label > 999999 ? 6 : next_label > 99999 ? 5 : next_label > 9999 ? 4 : next_label > 999 ? 3 : next_label > 99 ? 2 : next_label > 9 ? 1 : 0;
	int tl = this_label > 999999 ? 6 : this_label > 99999 ? 5 : this_label > 9999 ? 4 : this_label > 999 ? 3 : this_label > 99 ? 2 : this_label > 9 ? 1 : 0;
	return std::string(std::max(1, nl - tl + 1), ' ');
}

static std::string output_yych (bool & readCh)
{
	if (readCh)
	{
		readCh = false;
		return "(" + input_api.expr_peek_save () + ")";
	}
	else
	{
		return mapCodeName["yych"];
	}
}

static void output_if (OutputFile & o, uint ind, bool & readCh, const std::string & compare, uint value)
{
	o << indent(ind) << "if (" << output_yych (readCh) << " " << compare << " ";
	o.write_char_hex (value);
	o << ") ";
}

static void output_goto (OutputFile & o, uint ind, bool & readCh, uint to)
{
	if (readCh)
	{
		o << input_api.stmt_peek (ind);
		readCh = false;
	}
	o << indent (ind) << "goto " << labelPrefix << to << ";\n";
	vUsedLabels.insert(to);
}

static std::string output_hgo (OutputFile & o, uint ind, bool & readCh, SwitchIf * hgo)
{
	std::string yych = output_yych (readCh);
	if (hgo != NULL)
	{
		o << indent (ind) << "if (" << yych <<" & ~0xFF) {\n";
		hgo->emit (o, ind + 1, readCh);
		o << indent (ind) << "} else ";
		yych = mapCodeName["yych"];
	}
	else
	{
		o << indent (ind);
	}
	return yych;
}

uint Span::show (std::ostream & o, uint lb) const
{
	if (to)
	{
		printSpan(o, lb, ub);
		o << " " << to->label << "; ";
	}
	return ub;
}

void Case::emit (OutputFile & o, uint ind)
{
	for (uint i = 0; i < ranges.size (); ++i)
	{
		for (uint b = ranges[i].first; b < ranges[i].second; ++b)
		{
			o << indent (ind) << "case ";
			o.write_char_hex (b);
			o << ":";
			if (dFlag && encoding.is (Enc::EBCDIC))
			{
				const uint c = encoding.decodeUnsafe (b);
				if (isprint (c))
					o << " /* " << std::string (1, c) << " */";
			}
			bool last_case = i == ranges.size () - 1 && b == ranges[i].second - 1;
			if (!last_case)
			{
				o << "\n";
			}
		}
	}
}

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

Cases::~Cases ()
{
	delete [] cases;
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

void Cases::emit (OutputFile & o, uint ind, bool & readCh)
{
	o << indent(ind) << "switch (" << output_yych (readCh) << ") {\n";
	for (uint i = 0; i < cases_size; ++i)
	{
		if (cases[i].to != def)
		{
			cases[i].emit (o, ind);
			output_goto (o, 1, readCh, cases[i].to->label);
		}
	}
	o << indent (ind) << "default:";
	output_goto (o, 1, readCh, def->label);
	o << indent (ind) << "}\n";
}

Cond::Cond (const std::string & cmp, uint val)
	: compare (cmp)
	, value (val)
{}

Binary::Binary (const Span * s, uint n, const State * next)
	: cond (new Cond ("<=", s[n / 2 - 1].ub - 1))
	, thn (new If (n / 2 > 4 ? If::BINARY : If::LINEAR, &s[0], n / 2, next))
	, els (new If (n - n / 2 > 4 ? If::BINARY : If::LINEAR, &s[n / 2], n - n / 2, next))
{}

void Binary::emit (OutputFile & o, uint ind, bool & readCh)
{
	output_if (o, ind, readCh, cond->compare, cond->value);
	o << "{\n";
	thn->emit (o, ind + 1, readCh);
	o << indent (ind) << "} else {\n";
	els->emit (o, ind + 1, readCh);
	o << indent (ind) << "}\n";
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

void Linear::emit (OutputFile & o, uint ind, bool & readCh)
{
	for (uint i = 0; i < branches.size (); ++i)
	{
		if (branches[i].first != NULL)
		{
			output_if (o, ind, readCh, branches[i].first->compare, branches[i].first->value);
			output_goto (o, 0, readCh, branches[i].second->label);
		}
		else
		{
			output_goto (o, ind, readCh, branches[i].second->label);
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

void If::emit (OutputFile & o, uint ind, bool & readCh)
{
	switch (type)
	{
		case BINARY:
			info.binary->emit (o, ind, readCh);
			break;
		case LINEAR:
			info.linear->emit (o, ind, readCh);
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

void SwitchIf::emit (OutputFile & o, uint ind, bool & readCh)
{
	switch (type)
	{
		case SWITCH:
			info.cases->emit (o, ind, readCh);
			break;
		case IF:
			info.ifs->emit (o, ind, readCh);
			break;
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
	delete bspan;
}

void Bitmap::emit (OutputFile & o, uint ind, bool & readCh)
{
	std::string yych = output_hgo (o, ind, readCh, hgo);
	o << "if (" << mapCodeName["yybm"] << "[" << bitmap->i << "+" << yych << "] & ";
	if (yybmHexTable)
	{
		o.write_hex (bitmap->m);
	}
	else
	{
		o << (uint) bitmap->m;
	}
	o << ") {\n";
	output_goto (o, ind + 1, readCh, bitmap_state->label);
	o << indent (ind) << "}\n";
	if (lgo != NULL)
	{
		lgo->emit (o, ind, readCh);
	}
}

CpgotoTable::CpgotoTable (const Span * span, uint nSpans)
	: table (new uint [0x100])
{
	uint c = 0;
	for (uint i = 0; i < nSpans; ++i)
	{
		vUsedLabels.insert(span[i].to->label);
		for(; c < span[i].ub && c < 0x100; ++c)
		{
			table[c] = span[i].to->label;
		}
	}
}

void CpgotoTable::emit (OutputFile & o, uint ind)
{
	o << indent (ind) << "static void *" << mapCodeName["yytarget"] << "[256] = {\n";
	o << indent (++ind);
	for (uint i = 0; i <= 0xFF; ++i)
	{
		o << "&&" << labelPrefix << table[i];
		if (i == 0xFF)
		{
			o << "\n";
		}
		else if (i % 8 == 7)
		{
			o << ",\n" << indent (ind);
		}
		else
		{
			o << "," << space (table[i]);
		}
	}
	o << indent (--ind) << "};\n";
}

Cpgoto::Cpgoto (const Span * span, uint nSpans, const Span * hspan, uint hSpans, const State * next)
	: hgo (hSpans == 0 ? NULL : new SwitchIf (hspan, hSpans, next))
	, table (new CpgotoTable (span, nSpans))
{}

void Cpgoto::emit (OutputFile & o, uint ind, bool & readCh)
{
	std::string yych = output_hgo (o, ind, readCh, hgo);
	o << "{\n";
	table->emit (o, ++ind);
	o << indent(ind) << "goto *" << mapCodeName["yytarget"] << "[" << yych << "];\n";
	o << indent(--ind) << "}\n";
}

Dot::Dot (const Span * sp, uint nsp, const State * s)
	: from (s)
	, cases (new Cases (sp, nsp))
{}

void Dot::emit (OutputFile & o)
{
	const uint n = cases->cases_size;
	if (n == 1)
	{
		o << from->label << " -> " << cases->cases[0].to->label << "\n";
	}
	else
	{
		for (uint i = 0; i < n; ++i)
		{
			o << from->label << " -> " << cases->cases[i].to->label << " [label=\"";
			for (uint j = 0; j < cases->cases[i].ranges.size (); ++j)
			{
				o.write_range (cases->cases[i].ranges[j].first, cases->cases[i].ranges[j].second);
			}
			o << "\"]\n";
		}
	}
}

Go::Go ()
	: nSpans (0)
	, span (NULL)
	, type (NONE)
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
		if (span[i].to && span[i].to->isBase)
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

void Go::emit (OutputFile & o, uint ind, bool & readCh)
{
	switch (type)
	{
		case NONE:
			break;
		case SWITCH_IF:
			info.switchif->emit (o, ind, readCh);
			break;
		case BITMAP:
			info.bitmap->emit (o, ind, readCh);
			break;
		case CPGOTO:
			info.cpgoto->emit (o, ind, readCh);
			break;
		case DOT:
			info.dot->emit (o);
			break;
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
