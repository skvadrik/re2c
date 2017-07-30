#ifndef _RE2C_RE_ENCODING_UTF8_REGEXP_
#define _RE2C_RE_ENCODING_UTF8_REGEXP_

#include "src/re/re.h"
#include "src/re/encoding/utf8/utf8.h"

namespace re2c {

class Range;

RE *UTF8Symbol(RE::alc_t &alc, utf8::rune r);
RE *UTF8Range(RE::alc_t &alc, const Range *r);

} // namespace re2c

#endif // _RE2C_RE_ENCODING_UTF8_REGEXP_
