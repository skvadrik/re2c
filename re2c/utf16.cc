#include "utf16.h"

namespace re2c {

const uint utf16::MAX_1WORD_RUNE	= 0xFFFF;
const uint utf16::MIN_LEAD_SURR		= 0xD800;
const uint utf16::MIN_TRAIL_SURR	= 0xDC00;
const uint utf16::MAX_TRAIL_SURR	= 0xDFFF;

} // namespace re2c
