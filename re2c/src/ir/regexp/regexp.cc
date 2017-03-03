#include <limits>
#include <stddef.h>

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

const uint32_t RegExp::MANY = std::numeric_limits<uint32_t>::max();

const RegExp *doAlt(const RegExp *re1, const RegExp *re2)
{
	if (!re1) {
		return re2;
	}
	if (!re2) {
		return re1;
	}
	return RegExp::make_alt(re1, re2);
}

const RegExp *mkAlt(const RegExp *re1, const RegExp *re2)
{
	if (!re1) return re2;
	if (!re2) return re1;
	if (re1->type == RegExp::SYM && re2->type == RegExp::SYM) {
		return RegExp::make_sym(Range::add(re1->sym, re2->sym));
	}
	return RegExp::make_alt(re1, re2);
}

const RegExp *doCat(const RegExp *re1, const RegExp *re2)
{
	if (!re1) {
		return re2;
	}
	if (!re2) {
		return re1;
	}
	return RegExp::make_cat(re1, re2);
}

const RegExp *Scanner::schr(uint32_t c) const
{
	if (!opts->encoding.encode(c)) {
		fatalf("Bad code point: '0x%X'", c);
	}
	switch (opts->encoding.type ()) {
		case Enc::UTF16: return UTF16Symbol(c);
		case Enc::UTF8:  return UTF8Symbol(c);
		default:         return RegExp::make_sym(Range::sym(c));
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
				warn.empty_class(cline);
				return RegExp::make_nil();
			case EMPTY_CLASS_MATCH_NONE:
				warn.empty_class(cline);
				break;
			case EMPTY_CLASS_ERROR:
				fatal("empty character class");
		}
	}

	switch (opts->encoding.type()) {
		case Enc::UTF16: return UTF16Range(r);
		case Enc::UTF8:  return UTF8Range(r);
		default:         return RegExp::make_sym(r);
	}
}

const RegExp *Scanner::mkDiff(const RegExp *re1, const RegExp *re2) const
{
	if (re1 && re2
		&& re1->type == RegExp::SYM
		&& re2->type == RegExp::SYM) {
		return cls(Range::sub(re1->sym, re2->sym));
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
	return cls(Range::sub(opts->encoding.fullRange(),
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
	return RegExp::make_sym(Range::ran(0,
		opts->encoding.nCodeUnits()));
}

bool need_wrap(const RegExp *re)
{
	switch (re->type) {
		case RegExp::ITER:
		case RegExp::NIL:
		case RegExp::SYM:
		case RegExp::TAG:
		case RegExp::CAP:
			return false;
		case RegExp::ALT:
		case RegExp::CAT:
		case RegExp::REF:
		default:
			return true;
	}
}

} // namespace re2c
