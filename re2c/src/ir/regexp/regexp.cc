#include "src/ir/regexp/encoding/utf16/utf16_regexp.h"
#include "src/ir/regexp/encoding/utf8/utf8_regexp.h"
#include "src/ir/regexp/regexp.h"
#include "src/ir/regexp/regexp_alt.h"
#include "src/ir/regexp/regexp_cat.h"
#include "src/ir/regexp/regexp_match.h"
#include "src/ir/regexp/regexp_null.h"
#include "src/parse/scanner.h"
#include "src/util/range.h"

namespace re2c
{

static MatchOp * merge (MatchOp * m1, MatchOp * m2);

RegExp * doAlt (RegExp * e1, RegExp * e2)
{
	if (!e1)
	{
		return e2;
	}
	if (!e2)
	{
		return e1;
	}
	return new AltOp (e1, e2);
}

RegExp * mkAlt (RegExp * e1, RegExp * e2)
{
	AltOp * a;
	MatchOp * m1;
	MatchOp * m2;

	a = dynamic_cast<AltOp*> (e1);
	if (a != NULL)
	{
		m1 = dynamic_cast<MatchOp*> (a->exp1);
		if (m1 != NULL)
		{
			m1->ins_access = e1->ins_access;
			a->exp2->ins_access = e1->ins_access;
			e1 = a->exp2;
		}
	}
	else
	{
		m1 = dynamic_cast<MatchOp*> (e1);
		if (m1 != NULL)
		{
			e1 = NULL;
		}
	}
	a = dynamic_cast<AltOp*> (e2);
	if (a != NULL)
	{
		m2 = dynamic_cast<MatchOp*> (a->exp1);
		if (m2 != NULL)
		{
			m2->ins_access = e2->ins_access;
			a->exp2->ins_access = e2->ins_access;
			e2 = a->exp2;
		}
	}
	else
	{
		m2 = dynamic_cast<MatchOp*> (e2);
		if (m2 != NULL)
		{
			e2 = NULL;
		}
	}

	return doAlt (merge (m1, m2), doAlt (e1, e2));
}

MatchOp * merge (MatchOp * m1, MatchOp * m2)
{
	if (!m1)
	{
		return m2;
	}
	if (!m2)
	{
		return m1;
	}
	MatchOp * m = new MatchOp (doUnion (m1->match, m2->match));
	if (m1->ins_access == RegExp::PRIVATE
		|| m2->ins_access == RegExp::PRIVATE)
	{
		m->ins_access = RegExp::PRIVATE;
	}
	return m;
}

RegExp * doCat (RegExp * e1, RegExp * e2)
{
	if (!e1)
	{
		return e2;
	}
	if (!e2)
	{
		return e1;
	}
	return new CatOp (e1, e2);
}

RegExp * mkDiff (RegExp * e1, RegExp * e2)
{
	MatchOp * m1 = dynamic_cast<MatchOp *> (e1);
	MatchOp * m2 = dynamic_cast<MatchOp *> (e2);
	if (m1 == NULL || m2 == NULL)
	{
		return NULL;
	}
	Range * r = doDiff (m1->match, m2->match);
	return r
		? (RegExp *) new MatchOp(r)
		: (RegExp *) new NullOp;
}

Range * Scanner::getRange(SubStr &s) const
{
	uint32_t lb = unescape(s), ub;

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
			uint32_t tmp = lb;
			lb = ub;
			ub = tmp;
		}
	}

	Range * r = encoding.encodeRange(lb, ub);
	if (r == NULL)
		fatalf("Bad code point range: '0x%X - 0x%X'", lb, ub);
	return r;
}

RegExp * Scanner::matchSymbol(uint32_t c) const
{
	if (!encoding.encode(c))
		fatalf("Bad code point: '0x%X'", c);

	if (encoding.is(Enc::UTF16))
		return UTF16Symbol(c);
	else if (encoding.is(Enc::UTF8))
		return UTF8Symbol(c);
	else
		return new MatchOp(new Range(c, c + 1));
}

RegExp * Scanner::strToRE (SubStr & s) const
{
	if (s.len == 0)
		return new NullOp;

	RegExp *re = matchSymbol(unescape(s));

	while (s.len > 0)
		re = new CatOp(re, matchSymbol(unescape(s)));

	return re;
}

RegExp * Scanner::strToCaseInsensitiveRE (SubStr & s) const
{
	if (s.len == 0)
		return new NullOp;

	uint32_t c = unescape(s);

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
		c = unescape(s);

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

RegExp * Scanner::matchSymbolRange(Range * r) const
{
	if (encoding.is(Enc::UTF16))
		return UTF16Range(r);
	else if (encoding.is(Enc::UTF8))
		return UTF8Range(r);
	else
		return new MatchOp(r);
}

RegExp * Scanner::ranToRE (SubStr & s) const
{
	s.len -= 2;
	s.str += 1;

	if (s.len == 0)
		return new NullOp;

	return matchSymbolRange(mkRange(s));
}

RegExp * Scanner::invToRE (SubStr & s) const
{
	s.len -= 3;
	s.str += 2;

	Range * full = encoding.fullRange();

	Range * r = s.len == 0
		? full
		: doDiff(full, mkRange (s));

	return matchSymbolRange(r);
}

RegExp * Scanner::mkDot() const
{
	Range * full = encoding.fullRange();
	uint32_t c = '\n';
	if (!encoding.encode(c))
		fatalf("Bad code point: '0x%X'", c);
	Range * ran = new Range(c, c + 1);
	Range * inv = doDiff(full, ran);

	return matchSymbolRange(inv);
}

/*
 * Create a byte range that includes all possible input characters.
 * This may include characters, which do not map to any valid symbol
 * in current encoding. For encodings, which directly map symbols to
 * input characters (ASCII, EBCDIC, UTF-32), it equals [^]. For other
 * encodings (UTF-16, UTF-8), [^] and this range are different.
 *
 * Also note that default range doesn't respect encoding policy
 * (the way invalid code points are treated).
 */
RegExp * Scanner::mkDefault() const
{
	Range * def = new Range(0, encoding.nCodeUnits());
	return new MatchOp(def);
}

} // namespace re2c
