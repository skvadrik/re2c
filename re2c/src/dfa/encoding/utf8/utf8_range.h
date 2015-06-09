#ifndef _RE2C_DFA_ENCODING_UTF8_RANGE_
#define _RE2C_DFA_ENCODING_UTF8_RANGE_

#include "src/dfa/encoding/range_suffix.h"
#include "src/dfa/encoding/utf8/utf8.h"

namespace re2c {

void UTF8addContinuous(RangeSuffix * & p, utf8::rune l, utf8::rune h, uint32_t n);
void UTF8splitByContinuity(RangeSuffix * & p, utf8::rune l, utf8::rune h, uint32_t n);
void UTF8splitByRuneLength(RangeSuffix * & p, utf8::rune l, utf8::rune h);

} // namespace re2c

#endif // _RE2C_DFA_ENCODING_UTF8_RANGE_
