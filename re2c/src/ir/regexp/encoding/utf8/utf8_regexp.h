#ifndef _RE2C_IR_REGEXP_ENCODING_UTF8_REGEXP_
#define _RE2C_IR_REGEXP_ENCODING_UTF8_REGEXP_

#include "src/ir/regexp/encoding/utf8/utf8.h"

namespace re2c {

class Range;
struct RegExp;

const RegExp * UTF8Symbol(uint32_t l, uint32_t c, utf8::rune r);
const RegExp * UTF8Range(uint32_t l, uint32_t c, const Range * r);

} // namespace re2c

#endif // _RE2C_IR_REGEXP_ENCODING_UTF8_REGEXP_
