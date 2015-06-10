#include "src/ir/regexp/encoding/utf16/utf16.h"

namespace re2c {

const uint32_t utf16::MAX_1WORD_RUNE	= 0xFFFF;
const uint32_t utf16::MIN_LEAD_SURR	= 0xD800;
const uint32_t utf16::MIN_TRAIL_SURR	= 0xDC00;
const uint32_t utf16::MAX_TRAIL_SURR	= 0xDFFF;

} // namespace re2c
