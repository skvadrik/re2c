#ifndef _utf16_range_h
#define _utf16_range_h

#include "range_suffix.h"
#include "utf16.h"

namespace re2c {

void UTF16addContinuous1(RangeSuffix * & root, ushort l, ushort h);
void UTF16addContinuous2(RangeSuffix * & root, ushort l_ld, ushort h_ld, ushort l_tr, ushort h_tr);
void UTF16splitByContinuity(RangeSuffix * & root, ushort l_ld, ushort h_ld, ushort l_tr, ushort h_tr);
void UTF16splitByRuneLength(RangeSuffix * & root, utf16::rune l, utf16::rune h);

} // namespace re2c

#endif // _utf16_range_h
