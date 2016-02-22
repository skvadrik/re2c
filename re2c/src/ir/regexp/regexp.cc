#include <stddef.h>

#include "src/conf/opt.h"
#include "src/conf/warn.h"
#include "src/globals.h"
#include "src/ir/regexp/empty_class_policy.h"
#include "src/ir/regexp/encoding/case.h"
#include "src/ir/regexp/encoding/enc.h"
#include "src/ir/regexp/encoding/utf16/utf16_regexp.h"
#include "src/ir/regexp/encoding/utf8/utf8_regexp.h"
#include "src/ir/regexp/regexp.h"
#include "src/parse/scanner.h"
#include "src/util/range.h"

namespace re2c
{

free_list<RegExp*> RegExp::flist;

const RegExp *doAlt(const RegExp *re1, const RegExp *re2)
{
	if (!re1) {
		return re2;
	}
	if (!re2) {
		return re1;
	}
	return RegExp::alt(re1, re2);
}

static const RegExp *merge(const RegExp *sym1, const RegExp *sym2)
{
	if (!sym1) {
		return sym2;
	}
	if (!sym2) {
		return sym1;
	}
	return RegExp::sym(Range::add(
		sym1->pld.sym.range,
		sym2->pld.sym.range));
}

static const RegExp *lift_sym(const RegExp *&re)
{
	if (!re) {
		return NULL;
	}
	if (re->tag == RegExp::SYM) {
		const RegExp *sym = re;
		re = NULL;
		return sym;
	}
	if (re->tag == RegExp::ALT) {
		// second alternative cannot be SYM by construction
		const RegExp *alt1 = re->pld.alt.re1;
		if (alt1 && alt1->tag == RegExp::SYM) {
			re = re->pld.alt.re2;
			return alt1;
		}
	}
	return NULL;
}

const RegExp *mkAlt(const RegExp *re1, const RegExp *re2)
{
	const RegExp *sym1 = lift_sym(re1);
	const RegExp *sym2 = lift_sym(re2);
	return doAlt(
		merge(sym1, sym2),
		doAlt(re1, re2));
}

const RegExp *doCat(const RegExp *re1, const RegExp *re2)
{
	if (!re1) {
		return re2;
	}
	if (!re2) {
		return re1;
	}
	return RegExp::cat(re1, re2);
}

const RegExp *Scanner::schr(uint32_t c) const
{
	if (!opts->encoding.encode(c)) {
		fatalf("Bad code point: '0x%X'", c);
	}
	switch (opts->encoding.type ()) {
		case Enc::UTF16: return UTF16Symbol(c);
		case Enc::UTF8:  return UTF8Symbol(c);
		default:         return RegExp::sym(Range::sym(c));
	}
}

const RegExp *Scanner::ichr(uint32_t c) const
{
	if (is_alpha(c)) {
		const RegExp *l = schr(to_lower_unsafe(c));
		const RegExp *u = schr(to_upper_unsafe(c));
		return mkAlt(l, u);
	} else {
		return schr(c);
	}
}

const RegExp *Scanner::cls(const Range *r) const
{
	if (!r) {
		switch (opts->empty_class_policy) {
			case EMPTY_CLASS_MATCH_EMPTY:
				warn.empty_class(get_line());
				return RegExp::nil();
			case EMPTY_CLASS_MATCH_NONE:
				warn.empty_class(get_line());
				break;
			case EMPTY_CLASS_ERROR:
				fatal("empty character class");
				break;
		}
	}

	switch (opts->encoding.type()) {
		case Enc::UTF16: return UTF16Range(r);
		case Enc::UTF8:  return UTF8Range(r);
		default:         return RegExp::sym(r);
	}
}

const RegExp *Scanner::mkDiff(const RegExp *re1, const RegExp *re2) const
{
	if (re1 && re2
		&& re1->tag == RegExp::SYM
		&& re2->tag == RegExp::SYM) {
		return cls(Range::sub(
			re1->pld.sym.range,
			re2->pld.sym.range));
	}
	fatal("can only difference char sets");
	return NULL;
}

const RegExp *Scanner::mkDot() const
{
	uint32_t c = '\n';
	if (!opts->encoding.encode(c)) {
		fatalf("Bad code point: '0x%X'", c);
	}
	return cls(Range::sub(
		opts->encoding.fullRange(),
		Range::sym(c)));
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
const RegExp *Scanner::mkDefault() const
{
	return RegExp::sym(Range::ran(0,
		opts->encoding.nCodeUnits()));
}

/*
 * note [counted repetition expansion]
 *
 * r{0} ;;= <empty regexp>
 * r{n} ::= r{n-1} r
 * r{n,m} ::= r{n} (r{0} | ... | r{m-n})
 * r{n,} ::= r{n} r*
 */

// see note [counted repetition expansion]
const RegExp *repeat(const RegExp *re, uint32_t n)
{
	const RegExp *r = NULL;
	for (uint32_t i = 0; i < n; ++i) {
		r = doCat(r, re);
	}
	return r;
}

// see note [counted repetition expansion]
const RegExp *repeat_from_to(const RegExp *re, uint32_t n, uint32_t m)
{
	const RegExp *r1 = repeat(re, n);
	const RegExp *r2 = NULL;
	for (uint32_t i = n; i < m; ++i) {
		r2 = mkAlt(
			RegExp::nil(),
			doCat(re, r2));
	}
	return doCat(r1, r2);
}

// see note [counted repetition expansion]
const RegExp *repeat_from(const RegExp *re, uint32_t n)
{
	return doCat(
		repeat(re, n),
		RegExp::iter(re));
}

} // namespace re2c
