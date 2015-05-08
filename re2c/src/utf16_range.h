#ifndef _utf16_range_h
#define _utf16_range_h

#include "src/range_suffix.h"
#include "src/utf16.h"

namespace re2c {

void UTF16addContinuous1(RangeSuffix * & root, uint16_t l, uint16_t h);
void UTF16addContinuous2(RangeSuffix * & root, uint16_t l_ld, uint16_t h_ld, uint16_t l_tr, uint16_t h_tr);
void UTF16splitByContinuity(RangeSuffix * & root, uint16_t l_ld, uint16_t h_ld, uint16_t l_tr, uint16_t h_tr);
void UTF16splitByRuneLength(RangeSuffix * & root, utf16::rune l, utf16::rune h);

} // namespace re2c

#endif // _utf16_range_h
