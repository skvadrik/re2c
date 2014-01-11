/* $Id$ */
#include <time.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <cctype>

#include "globals.h"
#include "parser.h"
#include "dfa.h"
#include "utf8_range.h"

namespace re2c
{

void Symbol::ClearTable()
{
	for (SymbolTable::iterator it = symbol_table.begin(); it != symbol_table.end(); ++it)
	{
		delete it->second;
	}
	
	symbol_table.clear();
}

Symbol::SymbolTable Symbol::symbol_table;

Symbol *Symbol::find(const SubStr &str)
{
	const std::string ss(str.to_string());
	SymbolTable::const_iterator it = symbol_table.find(ss);

	if (it == symbol_table.end())
	{
		return (*symbol_table.insert(SymbolTable::value_type(ss, new Symbol(str))).first).second;
	}
	
	return (*it).second;
}

const Ins* showIns(std::ostream &o, const Ins &i, const Ins &base)
{
	o.width(3);
	o << &i - &base << ": ";

	const Ins *ret = &(&i)[1];

	switch (i.i.tag)
	{

		case CHAR:
		{
			o << "match ";

			for (; ret < (Ins*) i.i.link; ++ret)
				prtCh(o, ret->c.value);

			break;
		}

		case GOTO:
		o << "goto " << ((Ins*) i.i.link - &base);
		break;

		case FORK:
		o << "fork " << ((Ins*) i.i.link - &base);
		break;

		case CTXT:
		o << "ctxt";
		break;

		case TERM:
		o << "term " << ((RuleOp*) i.i.link)->accept;
		break;
	}

	o << "\n";
	return ret;
}

uint RegExp::fixedLength()
{
	return ~0u;
}

uint compile_goto(Ins *ins, Ins *i)
{
	i->i.tag = GOTO;
	i->i.link = ins;
	return 1;
}

const char *NullOp::type = "NullOp";

void NullOp::calcSize(Char*)
{
	size = 0;
}

uint NullOp::fixedLength()
{
	return 0;
}

uint NullOp::compile(Char*, Ins*)
{
	return 0;
}

void NullOp::uncompile()
{
	;
}

void NullOp::split(CharSet&)
{
	;
}

std::ostream& operator<<(std::ostream &o, const Range &r)
{
	if ((r.ub - r.lb) == 1)
	{
		prtCh(o, r.lb);
	}
	else
	{
		prtCh(o, r.lb);
		o << "-";
		prtCh(o, r.ub - 1);
	}

	return o << r.next;
}

Range *doUnion(Range *r1, Range *r2)
{
	Range *r, **rP = &r;

	for (;;)
	{
		Range *s;

		if (r1->lb <= r2->lb)
		{
			s = new Range(*r1);
		}
		else
		{
			s = new Range(*r2);
		}

		*rP = s;
		rP = &s->next;

		for (;;)
		{
			if (r1->lb <= r2->lb)
			{
				if (r1->lb > s->ub)
					break;

				if (r1->ub > s->ub)
					s->ub = r1->ub;

				if (!(r1 = r1->next))
				{
					uint ub = 0;

					for (; r2 && r2->lb <= s->ub; r2 = r2->next)
						ub = r2->ub;

					if (ub > s->ub)
						s->ub = ub;

					*rP = r2;

					return r;
				}
			}
			else
			{
				if (r2->lb > s->ub)
					break;

				if (r2->ub > s->ub)
					s->ub = r2->ub;

				if (!(r2 = r2->next))
				{
					uint ub = 0;

					for (; r1 && r1->lb <= s->ub; r1 = r1->next)
						ub = r1->ub;

					if (ub > s->ub)
						s->ub = ub;

					*rP = r1;

					return r;
				}
			}
		}
	}

	*rP = NULL;
	return r;
}

Range *doDiff(Range *r1, Range *r2)
{
	Range *r, *s, **rP = &r;

	for (; r1; r1 = r1->next)
	{
		uint lb = r1->lb;

		for (; r2 && r2->ub <= r1->lb; r2 = r2->next)

			;
		for (; r2 && r2->lb < r1->ub; r2 = r2->next)
		{
			if (lb < r2->lb)
			{
				*rP = s = new Range(lb, r2->lb);
				rP = &s->next;
			}

			if ((lb = r2->ub) >= r1->ub)
				goto noMore;
		}

		*rP = s = new Range(lb, r1->ub);
		rP = &s->next;

noMore:
		;
	}

	*rP = NULL;
	return r;
}

MatchOp *merge(MatchOp *m1, MatchOp *m2)
{
	if (!m1)
		return m2;

	if (!m2)
		return m1;

	return new MatchOp(doUnion(m1->match, m2->match));
}

const char *MatchOp::type = "MatchOp";

void MatchOp::display(std::ostream &o) const
{
	o << match;
}

void MatchOp::calcSize(Char *rep)
{
	size = 1;

	for (Range *r = match; r; r = r->next)
		for (uint c = r->lb; c < r->ub; ++c)
			if (rep[c] == c)
				++size;
}

uint MatchOp::fixedLength()
{
	return 1;
}

uint MatchOp::compile(Char *rep, Ins *i)
{
	if (ins_cache)
		return compile_goto(ins_cache, i);
	else
	{
		ins_cache = i;

		i->i.tag = CHAR;
		i->i.link = &i[size];
		Ins *j = &i[1];
		uint bump = size;

		for (Range *r = match; r; r = r->next)
		{
			for (uint c = r->lb; c < r->ub; ++c)
			{
				if (rep[c] == c)
				{
					j->c.value = c;
					j->c.bump = --bump;
					j++;
				}
			}
		}

		if (must_recompile)
			uncompile();

		return size;
	}
}

void MatchOp::uncompile()
{
	ins_cache = NULL;
}

void MatchOp::split(CharSet &s)
{
	for (Range *r = match; r; r = r->next)
	{
		for (uint c = r->lb; c < r->ub; ++c)
		{
			CharPtn *x = s.rep[c], *a = x->nxt;

			if (!a)
			{
				if (x->card == 1)
					continue;

				x->nxt = a = s.freeHead;

				if (!(s.freeHead = s.freeHead->nxt))
					s.freeTail = &s.freeHead;

				a->nxt = NULL;

				x->fix = s.fix;

				s.fix = x;
			}

			if (--(x->card) == 0)
			{
				*s.freeTail = x;
				*(s.freeTail = &x->nxt) = NULL;
			}

			s.rep[c] = a;
			++(a->card);
		}
	}

	for (; s.fix; s.fix = s.fix->fix)
		if (s.fix->card)
			s.fix->nxt = NULL;
}

RegExp * mkDiff(RegExp *e1, RegExp *e2)
{
	MatchOp *m1, *m2;

	if (!(m1 = (MatchOp*) e1->isA(MatchOp::type)))
		return NULL;

	if (!(m2 = (MatchOp*) e2->isA(MatchOp::type)))
		return NULL;

	Range *r = doDiff(m1->match, m2->match);

	return r ? (RegExp*) new MatchOp(r) : (RegExp*) new NullOp;
}

RegExp *doAlt(RegExp *e1, RegExp *e2)
{
	if (!e1)
		return e2;

	if (!e2)
		return e1;

	return new AltOp(e1, e2);
}

RegExp *doCat(RegExp *e1, RegExp *e2)
{
	if (!e1)
		return e2;

	if (!e2)
		return e1;

	return new CatOp(e1, e2);
}

RegExp *mkAlt(RegExp *e1, RegExp *e2)
{
	AltOp *a;
	MatchOp *m1, *m2;

	if ((a = (AltOp*) e1->isA(AltOp::type)))
	{
		if ((m1 = (MatchOp*) a->exp1->isA(MatchOp::type)))
			e1 = a->exp2;
	}
	else if ((m1 = (MatchOp*) e1->isA(MatchOp::type)))
	{
		e1 = NULL;
	}

	if ((a = (AltOp*) e2->isA(AltOp::type)))
	{
		if ((m2 = (MatchOp*) a->exp1->isA(MatchOp::type)))
			e2 = a->exp2;
	}
	else if ((m2 = (MatchOp*) e2->isA(MatchOp::type)))
	{
		e2 = NULL;
	}

	return doAlt(merge(m1, m2), doAlt(e1, e2));
}

const char *AltOp::type = "AltOp";

void AltOp::calcSize(Char *rep)
{
	exp1->calcSize(rep);
	exp2->calcSize(rep);
	size = exp1->size + exp2->size + 2;
}

uint AltOp::fixedLength()
{
	uint l1 = exp1->fixedLength();
	uint l2 = exp1->fixedLength();

	if (l1 != l2 || l1 == ~0u)
		return ~0u;

	return l1;
}

uint AltOp::compile(Char *rep, Ins *i)
{
	if (ins_cache)
		return compile_goto(ins_cache, i);
	else
	{
		ins_cache = i;

		i->i.tag = FORK;
		const uint sz1 = exp1->compile(rep, &i[1]);
		Ins * const j = &i[sz1 + 1];
		i->i.link = &j[1];
		j->i.tag = GOTO;
		const uint sz2 = exp2->compile(rep, &j[1]);
		j->i.link = &j[sz2 + 1];

		if (must_recompile)
			uncompile();

		return sz1 + sz2 + 2;
	}
}

void AltOp::uncompile()
{
	if (ins_cache)
	{
		exp1->uncompile();
		exp2->uncompile();
		ins_cache = NULL;
	}
}

void AltOp::split(CharSet &s)
{
	exp1->split(s);
	exp2->split(s);
}

const char *CatOp::type = "CatOp";

void CatOp::calcSize(Char *rep)
{
	exp1->calcSize(rep);
	exp2->calcSize(rep);
	size = exp1->size + exp2->size;
}

uint CatOp::fixedLength()
{
	uint l1, l2;

	if ((l1 = exp1->fixedLength()) != ~0u )
		if ((l2 = exp2->fixedLength()) != ~0u)
			return l1 + l2;

	return ~0u;
}

uint CatOp::compile(Char *rep, Ins *i)
{
	if (ins_cache)
		return compile_goto(ins_cache, i);
	else
	{
		ins_cache = i;

		const uint sz1 = exp1->compile(rep, &i[0]);
		const uint sz2 = exp2->compile(rep, &i[sz1]);

		if (must_recompile)
			uncompile();

		return sz1 + sz2;
	}
}

void CatOp::uncompile()
{
	if (ins_cache)
	{
		exp1->uncompile();
		exp2->uncompile();
		ins_cache = NULL;
	}
}

void CatOp::split(CharSet &s)
{
	exp1->split(s);
	exp2->split(s);
}

const char *CloseOp::type = "CloseOp";

void CloseOp::calcSize(Char *rep)
{
	exp->calcSize(rep);
	size = exp->size + 1;
}

uint CloseOp::compile(Char *rep, Ins *i)
{
	if (ins_cache)
		return compile_goto(ins_cache, i);
	else
	{
		ins_cache = i;

		i += exp->compile(rep, &i[0]);
		i->i.tag = FORK;
		i->i.link = ins_cache;
		++i;

		const uint sz = i - ins_cache;
		if (must_recompile)
			uncompile();

		return sz;
	}
}

void CloseOp::uncompile()
{
	if (ins_cache)
	{
		exp->uncompile();
		ins_cache = NULL;
	}
}

void CloseOp::split(CharSet &s)
{
	exp->split(s);
}

const char *CloseVOp::type = "CloseVOp";

void CloseVOp::calcSize(Char *rep)
{
	exp->calcSize(rep);

	if (max >= 0)
	{
		size = (exp->size * min) + ((1 + exp->size) * (max - min));
	}
	else
	{
		size = (exp->size * min) + 1;
	}
}

uint CloseVOp::compile(Char *rep, Ins *i)
{
	if (ins_cache)
		return compile_goto(ins_cache, i);
	else
	{
		ins_cache = i;

		for (int st = min; st < max; st++)
		{
			const uint sz = exp->compile(rep, &i[1]);
			i->i.tag = FORK;
			i->i.link = ins_cache + (1 + sz) * (max - min);
			i += sz + 1;
		}

		for (int st = 0; st < min; st++)
		{
			const uint sz = exp->compile(rep, &i[0]);
			i += sz;
			if (max < 0 && st == 0)
			{
				i->i.tag = FORK;
				i->i.link = i - sz;
				i++;
			}
		}

		const uint sz = i - ins_cache;
		if (must_recompile)
			uncompile();

		return sz;
	}
}

void CloseVOp::uncompile()
{
	if (ins_cache)
	{
		exp->uncompile();
		ins_cache = NULL;
	}
}

void CloseVOp::split(CharSet &s)
{
	exp->split(s);
}

RegExp *expr(Scanner &);

uint Scanner::unescape(SubStr &s) const
{
	static const char * hex = "0123456789abcdef";
	static const char * oct = "01234567";

	s.len--;
	uint c, ucb = 0;

	if ((c = *s.str++) != '\\' || s.len == 0)
	{
		return c;
	}

	s.len--;

	switch (c = *s.str++)
	{
		case 'n': return '\n';
		case 't': return '\t';
		case 'v': return '\v';
		case 'b': return '\b';
		case 'r': return '\r';
		case 'f': return '\f';
		case 'a': return '\a';

		case 'x':
		{
			if (s.len < 2)
			{
				fatal(s.ofs()+s.len, "Illegal hexadecimal character code, two hexadecimal digits are required");
				return ~0u;
			}
			
			const char *p1 = strchr(hex, tolower(s.str[0]));
			const char *p2 = strchr(hex, tolower(s.str[1]));

			if (!p1 || !p2)
			{
				fatal(s.ofs()+(p1?1:0), "Illegal hexadecimal character code");
				return ~0u;
			}
			else
			{
				s.len -= 2;
				s.str += 2;
				
				uint v = (uint)((p1 - hex) << 4) 
				       + (uint)((p2 - hex));
	
				return v;
			}
		}

		case 'U':
		{
			if (s.len < 8)
			{
				fatal(s.ofs()+s.len, "Illegal unicode character, eight hexadecimal digits are required");
				return ~0u;
			}

			uint l = 0;
						
			if (s.str[0] == '0')
			{
				l++;
				if (s.str[1] == '0')
				{
					l++;
					if (s.str[2] == '0' || (s.str[2] == '1' && (encoding.szSymbol() == 4)))
					{
						l++;
						if (encoding.szSymbol() == 4) {
							const char *u3 = strchr(hex, tolower(s.str[2]));
							const char *u4 = strchr(hex, tolower(s.str[3]));
							if (u3 && u4)
							{
								ucb = (uint)((u3 - hex) << 20)
							        + (uint)((u4 - hex) << 16);
								l++;
							}
						}
						else if (s.str[3] == '0')
						{
							l++;
						}
					}
				}
			}

			if (l != 4)
			{
				fatal(s.ofs()+l, "Illegal unicode character, eight hexadecimal digits are required");
			}

			s.len -= 4;
			s.str += 4;
			
			// no break;
		}
		case 'X':
		case 'u':
		{
			if (s.len < 4)
			{
				fatal(s.ofs()+s.len, 
					c == 'X'
					? "Illegal hexadecimal character code, four hexadecimal digits are required"
					: "Illegal unicode character, four hexadecimal digits are required");
				return ~0u;
			}
			
			const char *p1 = strchr(hex, tolower(s.str[0]));
			const char *p2 = strchr(hex, tolower(s.str[1]));
			const char *p3 = strchr(hex, tolower(s.str[2]));
			const char *p4 = strchr(hex, tolower(s.str[3]));

			if (!p1 || !p2 || !p3 || !p4)
			{
				fatal(s.ofs()+(p1?1:0)+(p2?1:0)+(p3?1:0), 
					c == 'X'
					? "Illegal hexadecimal character code, non hexxdecimal digit found"
					: "Illegal unicode character, non hexadecimal digit found");
				return ~0u;
			}
			else
			{
				s.len -= 4;
				s.str += 4;
				
				uint v = (uint)((p1 - hex) << 12) 
				       + (uint)((p2 - hex) <<  8)
				       + (uint)((p3 - hex) <<  4)
				       + (uint)((p4 - hex))
				       + ucb;
	
				if (v >= encoding.nSymbols())
				{
					fatal(s.ofs(),
						c == 'X'
						? "Illegal hexadecimal character code, out of range"
						: "Illegal unicode character, out of range");
				}
	
				return v;
			}
		}

		case '4':
		case '5':
		case '6':
		case '7':
		{
			fatal(s.ofs()-1, "Illegal octal character code, first digit must be 0 thru 3");
			return ~0u;
		}

		case '0':
		case '1':
		case '2':
		case '3':
		{
			if (s.len < 2)
			{
				fatal(s.ofs()+s.len, "Illegal octal character code, three octal digits are required");
				return ~0u;
			}

			const char *p0 = strchr(oct, c);
			const char *p1 = strchr(oct, s.str[0]);
			const char *p2 = strchr(oct, s.str[1]);

			if (!p0 || !p1 || !p2)
			{
				fatal(s.ofs()+(p1?1:0), "Illegal octal character code, non octal digit found");
				return ~0u;
			}
			else
			{
				s.len -= 2;
				s.str += 2;
				
				uint v = (uint)((p0 - oct) << 6) + (uint)((p1 - oct) << 3) + (uint)(p2 - oct);
	
				return v;
			}
		}

		default:
		return c;
	}
}

std::string& Scanner::unescape(SubStr& str_in, std::string& str_out) const
{
	str_out.clear();

	while(str_in.len)
	{
		uint c = unescape(str_in);

		if (c > 0xFF)
		{
			fatal(str_in.ofs(), "Illegal character");
		}

		str_out += static_cast<char>(c);
	}

	return str_out;
}

Range * Scanner::getRange(SubStr &s) const
{
	uint lb = unescape(s), ub, xlb, xub;

	if (s.len < 2 || *s.str != '-')
	{
		ub = lb;
	}
	else
	{
		s.len--;
		s.str++;
		ub = unescape(s);
		if (ub < lb)
		{
			uint tmp = lb;
			lb = ub;
			ub = tmp;
		}
	}

	xlb = encoding.xlat(lb);
	xub = encoding.xlat(ub);

	if (encoding.isEBCDIC())
	{
		Range * r = new Range(xlb, xlb + 1);
		for (uint c = lb + 1; c <= ub; ++c)
		{
			uint xc = encoding.xlat(c);
			r = doUnion(r, new Range(xc, xc + 1));
		}
		return r;
	}
	else
	{
		return new Range(xlb, xub + 1);
	}
}

RegExp * Scanner::matchChar(uint c) const
{
	uint xc = encoding.xlat(c);
	return new MatchOp(new Range(xc, xc + 1));
}

RegExp * Scanner::matchSymbol(uint c) const
{
	RegExp *re = NULL;
	if (encoding.isUTF8())
	{
		uchar bytes[4];
		const int bytes_count = utf8::rune_to_bytes(bytes, c);
		re = matchChar(bytes[0]);
		for (int i = 1; i < bytes_count; ++i)
			re = new CatOp (re, matchChar(bytes[i]));
	}
	else
		re = matchChar(c);
	return re;
}

RegExp * Scanner::strToRE(SubStr s) const
{
	s.len -= 2;
	s.str += 1;

	if (s.len == 0)
		return new NullOp;

	RegExp *re = matchSymbol(unescape(s));

	while (s.len > 0)
		re = new CatOp(re, matchSymbol(unescape(s)));

	return re;
}

RegExp * Scanner::strToCaseInsensitiveRE(SubStr s) const
{
	s.len -= 2;
	s.str += 1;

	if (s.len == 0)
		return new NullOp;

	uint c = unescape(s);

	RegExp *re, *reL, *reU;

	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		reL = matchSymbol(tolower(c));
		reU = matchSymbol(toupper(c));
		re = mkAlt(reL, reU);
	}
	else
	{
		re = matchSymbol(c);
	}

	while (s.len > 0)
	{
		uint c = unescape(s);

		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			reL = matchSymbol(tolower(c));
			reU = matchSymbol(toupper(c));
			re = new CatOp(re, mkAlt(reL, reU));
		}
		else
		{
			re = new CatOp(re, matchSymbol(c));
		}
	}

	return re;
}

Range * Scanner::mkRange(SubStr &s) const
{
	Range *r = getRange(s);
	while (s.len > 0)
		r = doUnion(r, getRange(s));

	return r;
}

RegExp * Scanner::ranToRE(SubStr s) const
{
	s.len -= 2;
	s.str += 1;

	if (s.len == 0)
		return new NullOp;

	Range *r = mkRange(s);
	return encoding.isUTF8()
		? UTF8Range(r)
		: new MatchOp(r);
}

RegExp * Scanner::invToRE(SubStr s) const
{
	s.len -= 3;
	s.str += 2;

	Range * any = new Range(0, encoding.nSymbols());

	Range * r = s.len == 0
		? any
		: doDiff(any, mkRange (s));

	return encoding.isUTF8()
		? UTF8Range(r)
		: new MatchOp(r);
}

RegExp * Scanner::mkDot() const
{
	Range * any = new Range(0, encoding.nSymbols());
	const uint c = encoding.xlat('\n');
	Range * ran = new Range(c, c + 1);
	Range * inv = doDiff(any, ran);

	return encoding.isUTF8()
		? UTF8Range(inv)
		: new MatchOp(inv);
}

const char *RuleOp::type = "RuleOp";

RuleOp::RuleOp(RegExp *e, RegExp *c, Token *t, uint a, bool b)
	: exp(e)
	, ctx(c)
	, ins(NULL)
	, accept(a)
	, code(t)
	, line(0)
{
	must_recompile = b;
}

RuleOp* RuleOp::copy(uint a) const
{
	Token *token = new Token(*code);
	return new RuleOp(exp, ctx, token, a, must_recompile);
}

void RuleOp::calcSize(Char *rep)
{
	exp->calcSize(rep);
	ctx->calcSize(rep);
	size = exp->size + (ctx->size ? ctx->size + 2 : 1);
}

uint RuleOp::compile(Char *rep, Ins *i)
{
	if (ins_cache)
		return compile_goto(ins_cache, i);
	else
	{
		ins_cache = i;

		i += exp->compile(rep, &i[0]);
		if (ctx->size)
		{
			i->i.tag = CTXT;
			i->i.link = &i[1];
			++i;
			i += ctx->compile(rep, &i[0]);
		}
		i->i.tag = TERM;
		i->i.link = this;
		++i;

		const uint sz = i - ins_cache;
		if (must_recompile)
			uncompile();

		return sz;
	}
}

void RuleOp::uncompile()
{
	if (ins_cache)
	{
		exp->uncompile();
		ctx->uncompile();
		ins_cache = NULL;
	}
}

void RuleOp::split(CharSet &s)
{
	exp->split(s);
	ctx->split(s);
}

void optimize(Ins *i)
{
	while (!isMarked(i))
	{
		mark(i);

		if (i->i.tag == CHAR)
		{
			i = (Ins*) i->i.link;
		}
		else if (i->i.tag == GOTO || i->i.tag == FORK)
		{
			Ins *target = (Ins*) i->i.link;
			optimize(target);

			if (target->i.tag == GOTO)
				i->i.link = target->i.link == target ? i : target;

			if (i->i.tag == FORK)
			{
				Ins *follow = (Ins*) & i[1];
				optimize(follow);

				if (follow->i.tag == GOTO && follow->i.link == follow)
				{
					i->i.tag = GOTO;
				}
				else if (i->i.link == i)
				{
					i->i.tag = GOTO;
					i->i.link = follow;
				}
			}

			return ;
		}
		else
		{
			++i;
		}
	}
}

CharSet::CharSet()
	: fix(0)
	, freeHead(0)
	, freeTail(0)
	, rep(new CharPtr[encoding.nChars()])
	, ptn(new CharPtn[encoding.nChars()])
{
	for (uint j = 0; j < encoding.nChars(); ++j)
	{
		rep[j] = &ptn[0];
		ptn[j].nxt = &ptn[j + 1]; /* wrong for j=encoding.nChars() but will be corrected below */
		ptn[j].card = 0;
	}

	freeHead = &ptn[1];
	*(freeTail = &ptn[encoding.nChars() - 1].nxt) = NULL;
	ptn[0].card = encoding.nChars();
	ptn[0].nxt = NULL;
}
	
CharSet::~CharSet()
{
	delete[] rep;
	delete[] ptn;
}

smart_ptr<DFA> genCode(RegExp *re)
{
	CharSet cs;
	uint j;

	re->split(cs);
	/*
	    for(uint k = 0; k < encoding.nChars();){
		for(j = k; ++k < encoding.nChars() && cs.rep[k] == cs.rep[j];);
		printSpan(cerr, j, k);
		cerr << "\t" << cs.rep[j] - &cs.ptn[0] << endl;
	    }
	*/
	Char *rep = new Char[encoding.nChars()];

	for (j = 0; j < encoding.nChars(); ++j)
	{
		if (!cs.rep[j]->nxt)
			cs.rep[j]->nxt = &cs.ptn[j];

		rep[j] = (Char) (cs.rep[j]->nxt - &cs.ptn[0]);
	}

	re->calcSize(rep);
	Ins *ins = new Ins[re->size + 1];
	memset(ins, 0, (re->size + 1)*sizeof(Ins));
	const uint size = re->compile(rep, ins);
	Ins *eoi = &ins[size];
	eoi->i.tag = GOTO;
	eoi->i.link = eoi;

	optimize(ins);

	/*
	for (const Ins *inst = &ins[0]; inst < &ins[size]; ) {
		inst = showIns(std::cout, *inst, ins[0]);
	}
	*/

	for (j = 0; j < size;)
	{
		unmark(&ins[j]);

		if (ins[j].i.tag == CHAR)
		{
			j = (Ins*) ins[j].i.link - ins;
		}
		else
		{
			j++;
		}
	}

	return make_smart_ptr(new DFA(ins, size, 0, encoding.nChars(), rep));
}

} // end namespace re2c

