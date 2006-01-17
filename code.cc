/* $Id$ */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iomanip>
#include <iostream>
#include "substr.h"
#include "globals.h"
#include "dfa.h"
#include "parser.h"
#include "code.h"

namespace re2c
{

// there must be at least one span in list;  all spans must cover
// same range

std::string indent(uint ind)
{
	std::string str;

	while (ind-- > 0)
	{
		str += indString;
	}
	return str;
}

void Go::compact()
{
	// arrange so that adjacent spans have different targets
	uint i = 0;

	for (uint j = 1; j < nSpans; ++j)
	{
		if (span[j].to != span[i].to)
		{
			++i;
			span[i].to = span[j].to;
		}

		span[i].ub = span[j].ub;
	}

	nSpans = i + 1;
}

void Go::unmap(Go *base, const State *x)
{
	Span *s = span, *b = base->span, *e = &b[base->nSpans];
	uint lb = 0;
	s->ub = 0;
	s->to = NULL;

	for (; b != e; ++b)
	{
		if (b->to == x)
		{
			if ((s->ub - lb) > 1)
			{
				s->ub = b->ub;
			}
		}
		else
		{
			if (b->to != s->to)
			{
				if (s->ub)
				{
					lb = s->ub;
					++s;
				}

				s->to = b->to;
			}

			s->ub = b->ub;
		}
	}

	s->ub = e[ -1].ub;
	++s;
	nSpans = s - span;
}

void doGen(const Go *g, const State *s, uint *bm, uint f, uint m)
{
	Span *b = g->span, *e = &b[g->nSpans];
	uint lb = 0;

	for (; b < e; ++b)
	{
		if (b->to == s)
		{
			for (; lb < b->ub && lb < 256; ++lb)
			{
				bm[lb-f] |= m;
			}
		}

		lb = b->ub;
	}
}

void prt(std::ostream& o, const Go *g, const State *s)
{
	Span *b = g->span, *e = &b[g->nSpans];
	uint lb = 0;

	for (; b < e; ++b)
	{
		if (b->to == s)
		{
			printSpan(o, lb, b->ub);
		}

		lb = b->ub;
	}
}

bool matches(const Go *g1, const State *s1, const Go *g2, const State *s2)
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

BitMap *BitMap::first = NULL;

BitMap::BitMap(const Go *g, const State *x)
	: go(g)
	, on(x)
	, next(first)
	, i(0)
	, m(0)
{
	first = this;
}

BitMap::~BitMap()
{
	if (next)
	{
		delete next;
	}
}

const BitMap *BitMap::find(const Go *g, const State *x)
{
	for (const BitMap *b = first; b; b = b->next)
	{
		if (matches(b->go, b->on, g, x))
		{
			return b;
		}
	}

	return new BitMap(g, x);
}

const BitMap *BitMap::find(const State *x)
{
	for (const BitMap *b = first; b; b = b->next)
	{
		if (b->on == x)
		{
			return b;
		}
	}

	return NULL;
}

void BitMap::gen(std::ostream &o, uint ind, uint lb, uint ub)
{
	BitMap *b = first;

	if (b)
	{
		o << indent(ind) << "static unsigned char yybm[] = {";
		uint n = ub - lb;
		uint *bm = new uint[n];
		memset(bm, 0, n);

		for (uint i = 0; b; i += n)
		{
			for (uint m = 0x80; b && m; b = const_cast<BitMap*>(b->next), m >>= 1)
			{
				b->i = i;
				b->m = m;
				doGen(b->go, b->on, bm, lb, m);
			}

			for (uint j = 0; j < n; ++j)
			{
				if (j % 8 == 0)
				{
					o << "\n" << indent(ind+1);
					++oline;
				}

				if (yybmHexTable)
				{
					prtHex(o, bm[j], false);
				}
				else
				{
					o << std::setw(3) << (uint)bm[j];
				}
				o  << ", ";
			}
		}

		o << "\n" << indent(ind) << "};\n";
		oline += 2;
	}
}

void BitMap::stats()
{
	uint n = 0;

	for (const BitMap *b = first; b; b = b->next)
	{
		prt(std::cerr, b->go, b->on);
		std::cerr << std::endl;
		++n;
	}

	std::cerr << n << " bitmaps\n";
	first = NULL;
}

void genGoTo(std::ostream &o, uint ind, const State *from, const State *to, bool & readCh)
{
	if (readCh && from->label + 1 != to->label)
	{
		o << indent(ind) << "yych = *YYCURSOR;\n";
		++oline;
		readCh = false;
	}

	o << indent(ind) << "goto yy" << to->label << ";\n";
	++oline;
	vUsedLabels.insert(to->label);
}

void genIf(std::ostream &o, uint ind, const char *cmp, uint v, bool &readCh)
{
	if (readCh)
	{
		o << indent(ind) << "if((yych = *YYCURSOR) ";
		readCh = false;
	}
	else
	{
		o << indent(ind) << "if(yych ";
	}

	o << cmp << " ";
	prtChOrHex(o, v);
	o << ") ";
}

static void need(std::ostream &o, uint ind, uint n, bool & readCh)
{
	uint fillIndex;
	bool hasFillIndex = (0<=vFillIndexes);

	if (hasFillIndex)
	{
		fillIndex = vFillIndexes++;
		o << indent(ind) << "YYSETSTATE(" << fillIndex << ");\n";
		++oline;
	}
	else
	{
		fillIndex = ~0;
	}

	if (n == 1)
	{
		o << indent(ind) << "if(YYLIMIT == YYCURSOR) YYFILL(1);\n";
		++oline;
	}
	else
	{
		o << indent(ind) << "if((YYLIMIT - YYCURSOR) < " << n << ") YYFILL(" << n << ");\n";
		++oline;
	}

	if ( hasFillIndex == true )
	{
		o << "yyFillLabel" << fillIndex << ":\n";
		++oline;
	}

	o << indent(ind) << "yych = *YYCURSOR;\n";
	readCh = false;
	++oline;
}

void Match::emit(std::ostream &o, uint ind, bool &readCh) const
{
	if (state->link)
	{
		o << indent(ind) << "++YYCURSOR;\n";
	}
	else if (!readAhead())
	{
		/* do not read next char if match */
		o << indent(ind) << "++YYCURSOR;\n";
		readCh = true;
	}
	else
	{
		o << indent(ind) << "yych = *++YYCURSOR;\n";
		readCh = false;
	}

	++oline;

	if (state->link)
	{
		need(o, ind, state->depth, readCh);
	}
}

void Enter::emit(std::ostream &o, uint ind, bool &readCh) const
{
	if (state->link)
	{
		o << indent(ind) << "++YYCURSOR;\n";
		o << "yy" << label << ":\n";
		oline += 2;
		need(o, ind, state->depth, readCh);
	}
	else
	{
		/* we shouldn't need 'rule-following' protection here */
		o << indent(ind) << "yych = *++YYCURSOR;\n";
		o << "yy" << label << ":\n";
		oline += 2;
		readCh = false;
	}
}

void Save::emit(std::ostream &o, uint ind, bool &readCh) const
{
	if (bUsedYYAccept)
	{
		o << indent(ind) << "yyaccept = " << selector << ";\n";
		++oline;
	}

	if (state->link)
	{
		o << indent(ind) << "YYMARKER = ++YYCURSOR;\n";
		++oline;
		need(o, ind, state->depth, readCh);
	}
	else
	{
		o << indent(ind) << "yych = *(YYMARKER = ++YYCURSOR);\n";
		++oline;
		readCh = false;
	}
}

Move::Move(State *s) : Action(s)
{
	;
}

void Move::emit(std::ostream &, uint, bool &) const
{
	;
}

Accept::Accept(State *x, uint n, uint *s, State **r)
		: Action(x), nRules(n), saves(s), rules(r)
{
	;
}

void Accept::emit(std::ostream &o, uint ind, bool &readCh) const
{
	bool first = true;

	for (uint i = 0; i < nRules; ++i)
		if (saves[i] != ~0u)
		{
			if (first)
			{
				first = false;
				bUsedYYAccept = true;
				o << indent(ind) << "YYCURSOR = YYMARKER;\n";
				o << indent(ind) << "switch(yyaccept){\n";
				oline += 2;
			}

			o << indent(ind) << "case " << saves[i] << ":";
			genGoTo(o, 1, state, rules[i], readCh);
		}

	if (!first)
	{
		o << indent(ind) << "}\n";
		++oline;
	}
}

Rule::Rule(State *s, RuleOp *r) : Action(s), rule(r)
{
	;
}

void Rule::emit(std::ostream &o, uint ind, bool &) const
{
	uint back = rule->ctx->fixedLength();

	if (back != ~0u && back > 0u)
	{
		o << indent(ind) << "YYCURSOR -= " << back << ";";
	}

	line_source(rule->code->line, o);
	o << indent(ind);
	o << rule->code->text;
	// Counting the oline's is done by SubStr::out()
	o << "\n";
	if (!iFlag)
	{
		++oline;
		o << "#line " << oline++ << " \"" << outputFileName << "\"\n";
		//    o << "\n#line " << rule->code->line
		//      << "\n\t" << rule->code->text << "\n";
	}
}

void doLinear(std::ostream &o, uint ind, Span *s, uint n, const State *from, const State *next, bool &readCh, uint mask)
{
	for (;;)
	{
		State *bg = s[0].to;

		while (n >= 3 && s[2].to == bg && (s[1].ub - s[0].ub) == 1)
		{
			if (s[1].to == next && n == 3)
			{
				if (!mask || (s[0].ub > 0x00FF))
				{
					genIf(o, ind, "!=", s[0].ub, readCh);
					genGoTo(o, 0, from, bg, readCh);
				}
				if (next->label != from->label + 1)
				{
					genGoTo(o, ind, from, next, readCh);
				}
				return ;
			}
			else
			{
				if (!mask || (s[0].ub > 0x00FF))
				{
					genIf(o, ind, "==", s[0].ub, readCh);
					genGoTo(o, 0, from, s[1].to, readCh);
				}
			}

			n -= 2;
			s += 2;
		}

		if (n == 1)
		{
			//	    	if(bg != next){
			if (s[0].to->label != from->label + 1)
			{
				genGoTo(o, ind, from, s[0].to, readCh);
			}
			//	    	}
			return ;
		}
		else if (n == 2 && bg == next)
		{
			if (!mask || (s[0].ub > 0x00FF))
			{
				genIf(o, ind, ">=", s[0].ub, readCh);
				genGoTo(o, 0, from, s[1].to, readCh);
			}
			if (next->label != from->label + 1)
			{
				genGoTo(o, ind, from, next, readCh);
			}
			return ;
		}
		else
		{
			if (!mask || ((s[0].ub - 1) > 0x00FF))
			{
				genIf(o, ind, "<=", s[0].ub - 1, readCh);
				genGoTo(o, 0, from, bg, readCh);
			}
			n -= 1;
			s += 1;
		}
	}

	if (next->label != from->label + 1)
	{
		genGoTo(o, ind, from, next, readCh);
	}
}

void Go::genLinear(std::ostream &o, uint ind, const State *from, const State *next, bool &readCh, uint mask) const
{
	doLinear(o, ind, span, nSpans, from, next, readCh, mask);
}

bool genCases(std::ostream &o, uint ind, uint lb, Span *s, bool &newLine, uint mask)
{
	bool used = false;

	if (!newLine)
	{
		o << "\n";
	}
	newLine = true;
	if (lb < s->ub)
	{
		for (;;)
		{
			if (!mask || lb > 0x00FF)
			{
				o << indent(ind) << "case ";
				prtChOrHex(o, lb);
				o << ":";
				newLine = false;
				used = true;
			}

			if (++lb == s->ub)
			{
				break;
			}

			o << "\n";
			++oline;
			newLine = true;
		}
	}
	return used;
}

void Go::genSwitch(std::ostream &o, uint ind, const State *from, const State *next, bool &readCh, uint mask) const
{
	bool newLine = true;

	if ((mask ? wSpans : nSpans) <= 2)
	{
		genLinear(o, ind, from, next, readCh, mask);
	}
	else
	{
		State *def = span[nSpans - 1].to;
		Span **sP = new Span * [nSpans - 1], **r, **s, **t;

		t = &sP[0];

		for (uint i = 0; i < nSpans; ++i)
		{
			if (span[i].to != def)
			{
				*(t++) = &span[i];
			}
		}

		if (dFlag)
		{
			o << indent(ind) << "YYDEBUG(-1, yych);\n";
		}

		if (readCh)
		{
			o << indent(ind) << "switch((yych = *YYCURSOR)) {\n";
			readCh = false;
		}
		else
		{
			o << indent(ind) << "switch(yych){\n";
		}

		++oline;

		while (t != &sP[0])
		{
			bool used = false;

			r = s = &sP[0];

			if (*s == &span[0])
			{
				used |= genCases(o, ind, 0, *s, newLine, mask);
			}
			else
			{
				used |= genCases(o, ind, (*s)[ -1].ub, *s, newLine, mask);
			}

			State *to = (*s)->to;

			while (++s < t)
			{
				if ((*s)->to == to)
				{
					used |= genCases(o, ind, (*s)[ -1].ub, *s, newLine, mask);
				}
				else
				{
					*(r++) = *s;
				}
			}

			if (used)
			{
				genGoTo(o, newLine ? ind+1 : 1, from, to, readCh);
				newLine = true;
			}
			t = r;
		}

		o << indent(ind) << "default:";
		genGoTo(o, 1, from, def, readCh);
		o << indent(ind) << "}\n";
		++oline;

		delete [] sP;
	}
}

void doBinary(std::ostream &o, uint ind, Span *s, uint n, const State *from, const State *next, bool &readCh, uint mask)
{
	if (n <= 4)
	{
		doLinear(o, ind, s, n, from, next, readCh, mask);
	}
	else
	{
		uint h = n / 2;

		genIf(o, ind, "<=", s[h - 1].ub - 1, readCh);
		o << "{\n";
		++oline;
		doBinary(o, ind+1, &s[0], h, from, next, readCh, mask);
		o << indent(ind) << "} else {\n";
		++oline;
		doBinary(o, ind+1, &s[h], n - h, from, next, readCh, mask);
		o << indent(ind) << "}\n";
		++oline;
	}
}

void Go::genBinary(std::ostream &o, uint ind, const State *from, const State *next, bool &readCh, uint mask) const
{
	if (mask)
	{
		Span * sc = new Span[wSpans];
		
		for (uint i = 0, j = 0; i < nSpans; i++)
		{
			if (span[i].ub > 0xFF)
			{
				sc[j++] = span[i];
			}
		}

		doBinary(o, ind, sc, wSpans, from, next, readCh, mask);

		delete[] sc;
	}
	else
	{
		doBinary(o, ind, span, nSpans, from, next, readCh, mask);
	}
}

void Go::genBase(std::ostream &o, uint ind, const State *from, const State *next, bool &readCh, uint mask) const
{
	if ((mask ? wSpans : nSpans) == 0)
	{
		return ;
	}

	if (!sFlag)
	{
		genSwitch(o, ind, from, next, readCh, mask);
		return ;
	}

	if ((mask ? wSpans : nSpans) > 8)
	{
		Span *bot = &span[0], *top = &span[nSpans - 1];
		uint util;

		if (bot[0].to == top[0].to)
		{
			util = (top[ -1].ub - bot[0].ub) / (nSpans - 2);
		}
		else
		{
			if (bot[0].ub > (top[0].ub - top[ -1].ub))
			{
				util = (top[0].ub - bot[0].ub) / (nSpans - 1);
			}
			else
			{
				util = top[ -1].ub / (nSpans - 1);
			}
		}

		if (util <= 2)
		{
			genSwitch(o, ind, from, next, readCh, mask);
			return ;
		}
	}

	if ((mask ? wSpans : nSpans) > 5)
	{
		genBinary(o, ind, from, next, readCh, mask);
	}
	else
	{
		genLinear(o, ind, from, next, readCh, mask);
	}
}

void Go::genGoto(std::ostream &o, uint ind, const State *from, const State *next, bool &readCh)
{
	if (bFlag)
	{
		if (wSpans == ~0u && wFlag)
		{
			wSpans = 0;
			for (uint p = 0; p < nSpans; p++)
			{
				if (span[p].ub > 0xFF)
				{
					wSpans++;
				}
			}
		}

		for (uint i = 0; i < nSpans; ++i)
		{
			State *to = span[i].to;

			if (to && to->isBase)
			{
				const BitMap *b = BitMap::find(to);
				const char * sYych;

				if (b && matches(b->go, b->on, this, to))
				{
					Go go;
					go.span = new Span[nSpans];
					go.unmap(this, to);
					if (wFlag)
					{
						if (readCh)
						{
							o << indent(ind) << "yych = *YYCURSOR;\n";
							oline++;
							readCh = false;
						}
						sYych = "yych";
						o << indent(ind) << "if(yyh & 0xFF00) {\n";
						oline++;
						/* here we need to reduce to those having high byte set */
						genBase(o, ind+1, from, next, readCh, 1);
						o << indent(ind) << "} else ";
					}
					else if (readCh)
					{
						sYych = "(yych = *YYCURSOR)";
						readCh = false;
						o << indent(ind);
					}
					else
					{
						sYych = "yych";
						o << indent(ind);
					}
					o << "if(yybm[" << b->i << "+" << sYych << "] & ";
					if (yybmHexTable)
					{
						prtHex(o, b->m, false);
					}
					else
					{
						o << (uint) b->m;
					}
					o << ") {\n";
					oline++;
					genGoTo(o, ind+1, from, to, readCh);
					o << indent(ind) << "}\n";
					oline++;
					go.genBase(o, ind, from, next, readCh, 0);
					delete [] go.span;
					return ;
				}
			}
		}
	}

	genBase(o, ind, from, next, readCh, 0);
}

void State::emit(std::ostream &o, uint ind, bool &readCh) const
{
	if (vUsedLabels.count(label))
	{
		o << "yy" << label << ":\n";
		oline++;
	}
	if (dFlag)
	{
		o << indent(ind) << "YYDEBUG(" << label << ", *YYCURSOR);\n";
		oline++;
	}
	action->emit(o, ind, readCh);
}

uint merge(Span *x0, State *fg, State *bg)
{
	Span *x = x0, *f = fg->go.span, *b = bg->go.span;
	uint nf = fg->go.nSpans, nb = bg->go.nSpans;
	State *prev = NULL, *to;
	// NB: we assume both spans are for same range

	for (;;)
	{
		if (f->ub == b->ub)
		{
			to = f->to == b->to ? bg : f->to;

			if (to == prev)
			{
				--x;
			}
			else
			{
				x->to = prev = to;
			}

			x->ub = f->ub;
			++x;
			++f;
			--nf;
			++b;
			--nb;

			if (nf == 0 && nb == 0)
			{
				return x - x0;
			}
		}

		while (f->ub < b->ub)
		{
			to = f->to == b->to ? bg : f->to;

			if (to == prev)
			{
				--x;
			}
			else
			{
				x->to = prev = to;
			}

			x->ub = f->ub;
			++x;
			++f;
			--nf;
		}

		while (b->ub < f->ub)
		{
			to = b->to == f->to ? bg : f->to;

			if (to == prev)
			{
				--x;
			}
			else
			{
				x->to = prev = to;
			}

			x->ub = b->ub;
			++x;
			++b;
			--nb;
		}
	}
}

const uint cInfinity = ~0;

class SCC
{

public:
	State	**top, **stk;

public:
	SCC(uint);
	~SCC();
	void traverse(State*);

#ifdef PEDANTIC
private:
	SCC(const SCC& oth)
		: top(oth.top)
		, stk(oth.stk)
	{
	}
	SCC& operator = (const SCC& oth)
	{
		new(this) SCC(oth);
		return *this;
	}
#endif
};

SCC::SCC(uint size)
	: top(new State * [size])
	, stk(top)
{
}

SCC::~SCC()
{
	delete [] stk;
}

void SCC::traverse(State *x)
{
	*top = x;
	uint k = ++top - stk;
	x->depth = k;

	for (uint i = 0; i < x->go.nSpans; ++i)
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

static bool state_is_in_non_trivial_SCC( const State* s )
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
	for (uint i = 0; i < s->go.nSpans; ++i)
	{
		const State* t = s->go.span[i].to;
	
		if (t &&  t->link == s)
		{
			return true;
		}
	}
	// otherwise no
	return false;
}

uint maxDist(State *s)
{
	if (s->depth != cInfinity)
	{
		// Already calculated, just return result.
    	return s->depth;
	}
	uint mm = 0;

	for (uint i = 0; i < s->go.nSpans; ++i)
	{
		State *t = s->go.span[i].to;

		if (t)
		{
			uint m = 1;

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

void calcDepth(State *head)
{
	// mark non-key states by s->link = NULL ;
	for (State* s = head; s; s = s->next)
	{
		if ( (s!=head) &&  !state_is_in_non_trivial_SCC(s) )
		{
			s->link=NULL;
		} else {
				// key state, leave alone
		}
	}
	
	for (State* s = head; s; s = s->next)
	{
		s->depth = cInfinity;
	}

	// calculate max number of transitions before guarantied to reach
	// a key state.
	for (State* s = head; s; s = s->next)
	{
		maxDist(s);
	}
}

void DFA::findSCCs()
{
	SCC scc(nStates);
	State *s;

	for (s = head; s; s = s->next)
	{
		s->depth = 0;
		s->link = NULL;
	}

	for (s = head; s; s = s->next)
	{
		if (!s->depth)
		{
			scc.traverse(s);
		}
	}

	calcDepth(head);
}

void DFA::split(State *s)
{
	State *move = new State;
	(void) new Move(move);
	addState(&s->next, move);
	move->link = s->link;
	move->rule = s->rule;
	move->go = s->go;
	s->rule = NULL;
	s->go.nSpans = 1;
	s->go.span = new Span[1];
	s->go.span[0].ub = ubChar;
	s->go.span[0].to = move;
}

void DFA::findBaseState()
{
	Span *span = new Span[ubChar - lbChar];

	for (State *s = head; s; s = s->next)
	{
		if (!s->link)
		{
			for (uint i = 0; i < s->go.nSpans; ++i)
			{
				State *to = s->go.span[i].to;

				if (to && to->isBase)
				{
					to = to->go.span[0].to;
					uint nSpans = merge(span, s, to);

					if (nSpans < s->go.nSpans)
					{
						delete [] s->go.span;
						s->go.nSpans = nSpans;
						s->go.span = new Span[nSpans];
						memcpy(s->go.span, span, nSpans*sizeof(Span));
					}

					break;
				}
			}
		}
	}

	delete [] span;
}

void DFA::emit(std::ostream &o, uint ind)
{
	static uint label = 0;
	State *s;
	uint i, bitmap_brace = 0;

	bool hasFillLabels = (0<=vFillIndexes);
	if (hasFillLabels==true && label!=0)
	{
		std::cerr << "re2c : error : multiple /*!re2c blocks aren't supported when -f is specified\n";
		exit(1);
	}


	findSCCs();
	head->link = head;

	uint nRules = 0;

	maxFill = 1;
	for (s = head; s; s = s->next)
	{
		s->depth = maxDist(s);
		if (maxFill < s->depth)
		{
			maxFill = s->depth;
		}
		if (s->rule && s->rule->accept >= nRules)
		{
			nRules = s->rule->accept + 1;
		}
	}

	uint nSaves = 0;
	uint *saves = new uint[nRules];
	memset(saves, ~0, (nRules)*sizeof(*saves));

	// mark backtracking points

	for (s = head; s; s = s->next)
	{
		RuleOp * ignore = NULL;

		if (s->rule)
		{
			for (i = 0; i < s->go.nSpans; ++i)
			{
				if (s->go.span[i].to && !s->go.span[i].to->rule)
				{
					delete s->action;

					if (saves[s->rule->accept] == ~0u)
					{
						saves[s->rule->accept] = nSaves++;
					}

					(void) new Save(s, saves[s->rule->accept]);
					continue;
				}
			}

			ignore = s->rule;
		}
	}

	// insert actions
	State **rules = new State * [nRules];

	memset(rules, 0, (nRules)*sizeof(*rules));

	State *accept = NULL;

	for (s = head; s; s = s->next)
	{
		State * ow;

		if (!s->rule)
		{
			ow = accept;
		}
		else
		{
			if (!rules[s->rule->accept])
			{
				State *n = new State;
				(void) new Rule(n, s->rule);
				rules[s->rule->accept] = n;
				addState(&s->next, n);
			}

			ow = rules[s->rule->accept];
		}

		for (i = 0; i < s->go.nSpans; ++i)
		{
			if (!s->go.span[i].to)
			{
				if (!ow)
				{
					ow = accept = new State;
					(void) new Accept(accept, nRules, saves, rules);
					addState(&s->next, accept);
				}

				s->go.span[i].to = ow;
			}
		}
	}

	// split ``base'' states into two parts
	for (s = head; s; s = s->next)
	{
		s->isBase = false;

		if (s->link)
		{
			for (i = 0; i < s->go.nSpans; ++i)
			{
				if (s->go.span[i].to == s)
				{
					s->isBase = true;
					split(s);

					if (bFlag)
					{
						BitMap::find(&s->next->go, s);
					}

					s = s->next;
					break;
				}
			}
		}
	}

	// find ``base'' state, if possible
	findBaseState();

	delete head->action;

	if (bFlag)
	{
		o << indent(ind++) << "{\n";
		++oline;
		bitmap_brace = 1;
		BitMap::gen(o, ind, lbChar, ubChar <= 256 ? ubChar : 256);
	}

	bUsedYYAccept = false;
	
	uint start_label = label;

	vUsedLabels.insert(label);
	(void) new Enter(head, label++);

	for (s = head; s; s = s->next)
	{
		s->label = label++;
	}

	null_stream noWhere;
	unsigned int nOrgOline = oline;
	uint maxFillIndexes = vFillIndexes;
	uint orgVFillIndexes = vFillIndexes;

	for (s = head; s; s = s->next)
	{
		bool readCh = false;
		s->emit(noWhere, ind, readCh);
		s->go.genGoto(noWhere, ind, s, s->next, readCh);
	}
	maxFillIndexes = vFillIndexes;
	vFillIndexes = orgVFillIndexes;
	oline = nOrgOline;

	oline++;
	o << "\n";
	if (!iFlag)
	{
		o << "#line " << oline++ << " \"" << outputFileName << "\"\n";
	}

	if ( hasFillLabels == false )
	{
		o << indent(ind++) << "{\n";
		o << indent(ind) << "YYCTYPE yych;\n";
		oline += 2;
		if (bUsedYYAccept)
		{
			o << indent(ind) << "unsigned int yyaccept = 0;\n";
			oline++;
		}
	}
	else
	{
		o << indent(ind++) << "{\n\n";
		oline += 2;
	}

	if ( hasFillLabels == false )
	{
		o << indent(ind) << "goto yy" << start_label << ";\n";
		++oline;
	}

	if (hasFillLabels == true )
	{
		o << indent(ind) << "switch(YYGETSTATE())\n";
		o << indent(ind) << "{\n";
		o << indent(ind) << "case -1: goto yy0;\n";

		for (size_t i=0; i<maxFillIndexes; ++i)
		{
			o << indent(ind) << "case " << i << ": goto yyFillLabel" << i << ";\n";
		}

		o << indent(ind) << "default: /* abort() */;\n";
		o << indent(ind) << "}\n";
		o << "yyNext:\n";

		oline += maxFillIndexes;
		oline += 6;
	}

	for (s = head; s; s = s->next)
	{
		bool readCh = false;
		s->emit(o, ind, readCh);
		s->go.genGoto(o, ind, s, s->next, readCh);
	}

	o << indent(--ind) << "}\n";
	if (bitmap_brace)
	{
		o << indent(--ind) << "}\n";
		++oline;
	}
	++oline;

	if (BitMap::first)
	{
		delete BitMap::first;
		BitMap::first = NULL;
	}

	delete [] saves;
	delete [] rules;
}

} // end namespace re2c
