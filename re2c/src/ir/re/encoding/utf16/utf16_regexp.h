#ifndef _RE2C_IR_RE_ENCODING_UTF16_REGEXP_
#define _RE2C_IR_RE_ENCODING_UTF16_REGEXP_

#include "src/ir/re/re.h"
#include "src/ir/re/encoding/utf16/utf16.h"

namespace re2c {

class Range;

RE *UTF16Symbol(RE::alc_t &alc, utf16::rune r);
RE *UTF16Range(RE::alc_t &alc, const Range *r);

} // namespace re2c

#endif // _RE2C_IR_RE_ENCODING_UTF16_REGEXP_
