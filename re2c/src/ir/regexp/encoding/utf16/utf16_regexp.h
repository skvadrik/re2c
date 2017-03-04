#ifndef _RE2C_IR_REGEXP_ENCODING_UTF16_REGEXP_
#define _RE2C_IR_REGEXP_ENCODING_UTF16_REGEXP_

#include "src/ir/regexp/encoding/utf16/utf16.h"

namespace re2c {

class Range;
struct RegExp;

const RegExp * UTF16Symbol(uint32_t l, uint32_t c, utf16::rune r);
const RegExp * UTF16Range(uint32_t l, uint32_t c, const Range * r);

} // namespace re2c

#endif // _RE2C_IR_REGEXP_ENCODING_UTF16_REGEXP_
