#include <limits>
#include <stddef.h>

#include "src/conf/msg.h"
#include "src/conf/opt.h"
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

const RegExp *RegExp::make_schar(uint32_t line, uint32_t column, uint32_t c, Opt &opts)
{
	if (!opts->encoding.encode(c)) {
		fatal_error(line, column, "bad code point: '0x%X'", c);
	}
	switch (opts->encoding.type ()) {
		case Enc::UTF16: return UTF16Symbol(line, column, c);
		case Enc::UTF8:  return UTF8Symbol(line, column, c);
		default:         return RegExp::make_sym(line, column, Range::sym(c));
	}
}

const RegExp *RegExp::make_ichar(uint32_t line, uint32_t column, uint32_t c, Opt &opts)
{
	if (is_alpha(c)) {
		const RegExp *l = RegExp::make_schar(line, column, to_lower_unsafe(c), opts);
		const RegExp *u = RegExp::make_schar(line, column, to_upper_unsafe(c), opts);
		return RegExp::make_alt(l, u);
	} else {
		return RegExp::make_schar(line, column, c, opts);
	}
}

const RegExp *RegExp::make_class(uint32_t line, uint32_t column, const Range *r, Opt &opts, Warn &warn)
{
	if (!r) {
		switch (opts->empty_class_policy) {
			case EMPTY_CLASS_MATCH_EMPTY:
				warn.empty_class(line);
				return RegExp::make_nil(line, column);
			case EMPTY_CLASS_MATCH_NONE:
				warn.empty_class(line);
				break;
			case EMPTY_CLASS_ERROR:
				fatal_error(line, column, "empty character class");
				break;
		}
	}

	switch (opts->encoding.type()) {
		case Enc::UTF16: return UTF16Range(line, column, r);
		case Enc::UTF8:  return UTF8Range(line, column, r);
		default:         return RegExp::make_sym(line, column, r);
	}
}

const RegExp *RegExp::make_diff(const RegExp *re1, const RegExp *re2, Opt &opts, Warn &warn)
{
	if (re1 && re2
		&& re1->type == RegExp::SYM
		&& re2->type == RegExp::SYM) {
		return RegExp::make_class(re1->line, re1->column,
			Range::sub(re1->sym, re2->sym), opts, warn);
	}
	fatal_error(re1->line, re1->column, "can only difference char sets");
	return NULL;
}

const RegExp *RegExp::make_dot(uint32_t line, uint32_t column, Opt &opts, Warn &warn)
{
	uint32_t c = '\n';
	if (!opts->encoding.encode(c)) {
		fatal_error(line, column, "bad code point: '0x%X'", c);
	}
	return RegExp::make_class(line, column,
		Range::sub(opts->encoding.fullRange(), Range::sym(c)), opts, warn);
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
const RegExp *RegExp::make_default(uint32_t line, uint32_t column, Opt &opts)
{
	return RegExp::make_sym(line, column, Range::ran(0,
		opts->encoding.nCodeUnits()));
}

bool RegExp::need_wrap(const RegExp *re)
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
