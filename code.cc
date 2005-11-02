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

namespace re2c
{

// there must be at least one span in list;  all spans must cover
// same range

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

void Go::unmap(Go *base, State *x)
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

void doGen(Go *g, State *s, uchar *bm, uchar m)
{
	Span *b = g->span, *e = &b[g->nSpans];
	uint lb = 0;

	for (; b < e; ++b)
	{
		if (b->to == s)
		{
			for (; lb < b->ub; ++lb)
			{
				bm[lb] |= m;
			}
		}

		lb = b->ub;
	}
}

void prt(std::ostream& o, Go *g, State *s)
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

bool matches(Go *g1, State *s1, Go *g2, State *s2)
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

class BitMap
{

public:
	static BitMap	*first;
	Go	*go;
	State	*on;
	BitMap	*next;
	uint	i;
	uchar	m;

public:
	static BitMap *find(Go*, State*);
	static BitMap *find(State*);
	static void gen(std::ostream&, uint, uint);
	static void stats();
	BitMap(Go*, State*);
};

BitMap *BitMap::first = NULL;

BitMap::BitMap(Go *g, State *x) : go(g), on(x), next(first)
{
	first = this;
}

BitMap *BitMap::find(Go *g, State *x)
{
	for (BitMap *b = first; b; b = b->next)
	{
		if (matches(b->go, b->on, g, x))
		{
			return b;
		}
	}

	return new BitMap(g, x);
}

BitMap *BitMap::find(State *x)
{
	for (BitMap *b = first; b; b = b->next)
	{
		if (b->on == x)
		{
			return b;
		}
	}

	return NULL;
}

void BitMap::gen(std::ostream &o, uint lb, uint ub)
{
	BitMap *b = first;

	if (b)
	{
		o << "\tstatic unsigned char yybm[] = {";
		uint n = ub - lb;
		uchar *bm = new uchar[n];
		memset(bm, 0, n);

		for (uint i = 0; b; i += n)
		{
			for (uchar m = 0x80; b && m; b = b->next, m >>= 1)
			{
				b->i = i;
				b->m = m;
				doGen(b->go, b->on, bm - lb, m);
			}

			for (uint j = 0; j < n; ++j)
			{
				if (j % 8 == 0)
				{
					o << "\n\t";
					++oline;
				}

				o << std::setw(3) << (uint) bm[j] << ", ";
			}
		}

		o << "\n\t};\n";
		oline += 2;
	}
}

void BitMap::stats()
{
	uint n = 0;

	for (BitMap *b = first; b; b = b->next)
	{
		prt(std::cerr, b->go, b->on);
		std::cerr << std::endl;
		++n;
	}

	std::cerr << n << " bitmaps\n";
	first = NULL;
}

void genGoTo(std::ostream &o, State *from, State *to, bool & readCh, const char *indent = "\t")
{
	if (readCh && from->label + 1 != to->label)
	{
		o << indent << "yych = *YYCURSOR;\n";
		++oline;
		readCh = false;
	}

	o << indent << "goto yy" << to->label << ";\n";
	++oline;
	vUsedLabels.append(to->label);
}

void genIf(std::ostream &o, char *cmp, uint v, bool &readCh)
{
	if (readCh)
	{
		o << "\tif((yych = *YYCURSOR) ";
		readCh = false;
	}
	else
	{
		o << "\tif(yych ";
	}

	o << cmp << " ";
	prtChOrHex(o, v);
	o << ")";
}

void indent(std::ostream &o, uint i)
{
	while (i-- > 0)
	{
		o << "\t";
	}
}

static void need(std::ostream &o, uint n, bool & readCh)
{
	uint fillIndex;
	bool hasFillIndex = (0<=vFillIndexes);
	if ( hasFillIndex == true )
	{
		fillIndex = vFillIndexes++;
		o << "\tYYSETSTATE(" << fillIndex << ");\n";
		++oline;
	}

	if (n == 1)
	{
		o << "\tif(YYLIMIT == YYCURSOR) YYFILL(1);\n";
		++oline;
	}
	else
	{
		o << "\tif((YYLIMIT - YYCURSOR) < " << n << ") YYFILL(" << n << ");\n";
		++oline;
	}

	if ( hasFillIndex == true )
	{
		o << "yyFillLabel" << fillIndex << ":\n";
		++oline;
	}

	o << "\tyych = *YYCURSOR;\n";
	readCh = false;
	++oline;
}

void Match::emit(std::ostream &o, bool &readCh)
{
	if (state->link)
	{
		o << "\t++YYCURSOR;\n";
	}
	else if (!readAhead())
	{
		/* do not read next char if match */
		o << "\t++YYCURSOR;\n";
		readCh = true;
	}
	else
	{
		o << "\tyych = *++YYCURSOR;\n";
		readCh = false;
	}

	++oline;

	if (state->link)
	{
		need(o, state->depth, readCh);
	}
}

void Enter::emit(std::ostream &o, bool &readCh)
{
	if (state->link)
	{
		o << "\t++YYCURSOR;\n";
		o << "yy" << label << ":\n";
		oline += 2;
		need(o, state->depth, readCh);
	}
	else
	{
		/* we shouldn't need 'rule-following' protection here */
		o << "\tyych = *++YYCURSOR;\n";
		o << "yy" << label << ":\n";
		oline += 2;
		readCh = false;
	}
}

void Save::emit(std::ostream &o, bool &readCh)
{
	if (bUsedYYAccept)
	{
		o << "\tyyaccept = " << selector << ";\n";
		++oline;
	}

	if (state->link)
	{
		o << "\tYYMARKER = ++YYCURSOR;\n";
		++oline;
		need(o, state->depth, readCh);
	}
	else
	{
		o << "\tyych = *(YYMARKER = ++YYCURSOR);\n";
		++oline;
		readCh = false;
	}
}

Move::Move(State *s) : Action(s)
{
	;
}

void Move::emit(std::ostream &o, bool &readCh)
{
	;
}

Accept::Accept(State *x, uint n, uint *s, State **r)
		: Action(x), nRules(n), saves(s), rules(r)
{
	;
}

void Accept::emit(std::ostream &o, bool &readCh)
{
	bool first = true;

	for (uint i = 0; i < nRules; ++i)
		if (saves[i] != ~0u)
		{
			if (first)
			{
				first = false;
				bUsedYYAccept = true;
				o << "\tYYCURSOR = YYMARKER;\n";
				o << "\tswitch(yyaccept){\n";
				oline += 2;
			}

			o << "\tcase " << saves[i] << ":";
			genGoTo(o, state, rules[i], readCh);
		}

	if (!first)
	{
		o << "\t}\n";
		++oline;
	}
}

Rule::Rule(State *s, RuleOp *r) : Action(s), rule(r)
{
	;
}

void Rule::emit(std::ostream &o, bool &readCh)
{
	uint back = rule->ctx->fixedLength();

	if (back != ~0u && back > 0u)
	{
		o << "\tYYCURSOR -= " << back << ";";
	}

	o << "\n";
	++oline;
	line_source(rule->code->line, o);
	o << rule->code->text;
	// not sure if we need this or not.    oline += std::count(rule->code->text, rule->code->text + ::strlen(rule->code->text), '\n');
	o << "\n";
	if (!iFlag)
	{
		++oline;
		o << "#line " << oline++ << " \"" << outputFileName << "\"\n";
		//    o << "\n#line " << rule->code->line
		//      << "\n\t" << rule->code->text << "\n";
	}
}

void doLinear(std::ostream &o, uint i, Span *s, uint n, State *from, State *next, bool &readCh)
{
	for (;;)
	{
		State *bg = s[0].to;

		while (n >= 3 && s[2].to == bg && (s[1].ub - s[0].ub) == 1)
		{
			if (s[1].to == next && n == 3)
			{
				indent(o, i);
				genIf(o, "!=", s[0].ub, readCh);
				genGoTo(o, from, bg, readCh);
				indent(o, i);
				genGoTo(o, from, next, readCh);
				return ;
			}
			else
			{
				indent(o, i);
				genIf(o, "==", s[0].ub, readCh);
				genGoTo(o, from, s[1].to, readCh);
			}

			n -= 2;
			s += 2;
		}

		if (n == 1)
		{
			//	    	if(bg != next){
			indent(o, i);
			genGoTo(o, from, s[0].to, readCh);
			//	    	}
			return ;
		}
		else if (n == 2 && bg == next)
		{
			indent(o, i);
			genIf(o, ">=", s[0].ub, readCh);
			genGoTo(o, from, s[1].to, readCh);
			indent(o, i);
			genGoTo(o, from, next, readCh);
			return ;
		}
		else
		{
			indent(o, i);
			genIf(o, "<=", s[0].ub - 1, readCh);
			genGoTo(o, from, bg, readCh);
			n -= 1;
			s += 1;
		}
	}

	indent(o, i);
	genGoTo(o, from, next, readCh);
}

void Go::genLinear(std::ostream &o, State *from, State *next, bool &readCh)
{
	doLinear(o, 0, span, nSpans, from, next, readCh);
}

void genCases(std::ostream &o, uint lb, Span *s)
{
	if (lb < s->ub)
	{
		for (;;)
		{
			o << "\tcase ";
			prtChOrHex(o, lb);
			o << ":";

			if (++lb == s->ub)
			{
				break;
			}

			o << "\n";
			++oline;
		}
	}
}

void Go::genSwitch(std::ostream &o, State *from, State *next, bool &readCh)
{
	if (nSpans <= 2)
	{
		genLinear(o, from, next, readCh);
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
			o << "\tYYDEBUG(-1, yych);\n";
		}

		if (readCh)
		{
			o << "\tswitch((yych = *YYCURSOR)) {\n";
			readCh = false;
		}
		else
		{
			o << "\tswitch(yych){\n";
		}

		++oline;

		while (t != &sP[0])
		{
			r = s = &sP[0];

			if (*s == &span[0])
				genCases(o, 0, *s);
			else
				genCases(o, (*s)[ -1].ub, *s);

			State *to = (*s)->to;

			while (++s < t)
			{
				if ((*s)->to == to)
				{
					genCases(o, (*s)[ -1].ub, *s);
				}
				else
				{
					*(r++) = *s;
				}
			}

			genGoTo(o, from, to, readCh);
			t = r;
		}

		o << "\tdefault:";
		genGoTo(o, from, def, readCh);
		o << "\t}\n";
		++oline;

		delete [] sP;
	}
}

void doBinary(std::ostream &o, uint i, Span *s, uint n, State *from, State *next, bool &readCh)
{
	if (n <= 4)
	{
		doLinear(o, i, s, n, from, next, readCh);
	}
	else
	{
		uint h = n / 2;
		indent(o, i);
		genIf(o, "<=", s[h - 1].ub - 1, readCh);
		o << "{\n";
		++oline;
		doBinary(o, i + 1, &s[0], h, from, next, readCh);
		indent(o, i);
		o << "\t} else {\n";
		++oline;
		doBinary(o, i + 1, &s[h], n - h, from, next, readCh);
		indent(o, i);
		o << "\t}\n";
		++oline;
	}
}

void Go::genBinary(std::ostream &o, State *from, State *next, bool &readCh)
{
	doBinary(o, 0, span, nSpans, from, next, readCh);
}

void Go::genBase(std::ostream &o, State *from, State *next, bool &readCh)
{
	if (nSpans == 0)
	{
		return ;
	}

	if (!sFlag)
	{
		genSwitch(o, from, next, readCh);
		return ;
	}

	if (nSpans > 8)
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
			genSwitch(o, from, next, readCh);
			return ;
		}
	}

	if (nSpans > 5)
	{
		genBinary(o, from, next, readCh);
	}
	else
	{
		genLinear(o, from, next, readCh);
	}
}

void Go::genGoto(std::ostream &o, State *from, State *next, bool &readCh)
{
	if (bFlag)
	{
		for (uint i = 0; i < nSpans; ++i)
		{
			State *to = span[i].to;

			if (to && to->isBase)
			{
				BitMap *b = BitMap::find(to);

				if (b && matches(b->go, b->on, this, to))
				{
					Go go;
					go.span = new Span[nSpans];
					go.unmap(this, to);
					o << "\tif(yybm[" << b->i << "+";

					if (readCh)
					{
						o << "(yych = *YYCURSOR)";
					}
					else
					{
						o << "yych";
					}

					o << "] & " << (uint) b->m << ") {\n";
					oline++;
					genGoTo(o, from, to, readCh, "\t\t");
					o << "\t}\n";
					oline++;
					go.genBase(o, from, next, readCh);
					delete [] go.span;
					return ;
				}
			}
		}
	}

	genBase(o, from, next, readCh);
}

void State::emit(std::ostream &o, bool &readCh)
{
	if (vUsedLabels.contains(label))
	{
		o << "yy" << label << ":";
	}
	if (dFlag)
	{
		o << "\n\tYYDEBUG(" << label << ", *YYCURSOR);\n";
	}
	action->emit(o, readCh);
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
};

SCC::SCC(uint size)
{
	top = stk = new State * [size];
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

static
bool state_is_in_non_trivial_SCC( const State* s )
{

  // does not link to self
  if (  s->link != s ){
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

      if (t &&  t->link == s){
	return true;
      }
    }
  // otherwise no
  return false;
}

uint maxDist(State *s)
{
  if ( s->depth != cInfinity ){
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
				if (t->depth == -1)
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
	for (State* s = head; s; s = s->next )
	{
		if ( (s!=head) &&  !state_is_in_non_trivial_SCC(s) )
		{
			s->link=NULL;
		} else {
				// key state, leave alone
		}
	}
	
	for (State* s = head; s; s = s->next )
	{
		s->depth = cInfinity;
	}

	// calculate max number of transitions before guarantied to reach
	// a key state.
	for (State* s = head; s; s = s->next ){
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

class null_stream: public std::ostream
{
public:
	null_stream()
		: std::ostream(&ns)
	{
	}

	null_stream& put(char_type)
	{
		// nothing to do
		return *this;
	}
	
	null_stream& write(const char_type *, std::streamsize)
	{
		// nothing to do
		return *this;
	}

protected:
	class null_streambuf: public std::streambuf
	{
	public:
		null_streambuf()
			: std::streambuf()
		{
		}	
	};
	null_streambuf   ns;
};

void DFA::emit(std::ostream &o)
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
	Span *span = new Span[ubChar - lbChar];

	for (s = head; s; s = s->next)
	{
		if (!s->link)
		{
			for (i = 0; i < s->go.nSpans; ++i)
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

	delete head->action;

	if (bFlag)
	{
		o << "{\n";
		++oline;
		bitmap_brace = 1;
		BitMap::gen(o, lbChar, ubChar);
	}

	bUsedYYAccept = false;
	
	uint start_label = label;

	vUsedLabels.append(label);
	(void) new Enter(head, label++);

	for (s = head; s; s = s->next)
	{
		s->label = label++;
	}

	null_stream noWhere;
	unsigned int nOrgOline = oline;
	int maxFillIndexes = vFillIndexes;
	int orgVFillIndexes = vFillIndexes;

	for (s = head; s; s = s->next)
	{
		bool readCh = false;
		s->emit(noWhere, readCh);
		s->go.genGoto(noWhere, s, s->next, readCh);
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
		o << "{\n\tYYCTYPE yych;\n";
		oline += 2;
		if (bUsedYYAccept) {
			o << "\tunsigned int yyaccept = 0;\n";
			oline++;
		}
	}
	else
	{
		o << "{\n\n";
		oline += 2;
	}

	if ( hasFillLabels == false )
	{
		o << "\tgoto yy" << start_label << ";\n";
		++oline;
	}

	if (hasFillLabels == true )
	{
		o << "        switch(YYGETSTATE())\n";
		o << "        {\n";
		o << "            case -1: goto yy0;\n";

		for (size_t i=0; i<maxFillIndexes; ++i)
		{
			o << "            case " << i << ": goto yyFillLabel" << i << ";\n";
		}

		o << "            default: /* abort() */;\n";
		o << "        }\n";
		o << "yyNext:\n";

		oline += maxFillIndexes;
		oline += 6;
	}

	for (s = head; s; s = s->next)
	{
		bool readCh = false;
		s->emit(o, readCh);
		s->go.genGoto(o, s, s->next, readCh);
	}

	o << "}\n";
	if (bitmap_brace) {
		o << "}\n";
		++oline;
	}
	++oline;

	BitMap::first = NULL;

	delete [] saves;
	delete [] rules;
}

} // end namespace re2c

