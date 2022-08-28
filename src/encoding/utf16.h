#ifndef _RE2C_RE_ENCODING_UTF16_
#define _RE2C_RE_ENCODING_UTF16_

#include <stdint.h>

namespace re2c {

class Range;
struct Regexp;
struct RESpec;

namespace utf16 {

using rune = uint32_t;

static constexpr uint32_t MAX_1WORD_RUNE = 0xFFFFu;
static constexpr uint32_t MIN_LEAD_SURR = 0xD800u;
static constexpr uint32_t MIN_TRAIL_SURR = 0xDC00u;
static constexpr uint32_t MAX_TRAIL_SURR = 0xDFFFu;

// leading surrogate of UTF-16 symbol
inline constexpr uint32_t lead_surr(rune r) {
    return ((r - 0x10000u) / 0x400u) + MIN_LEAD_SURR;
}

// trailing surrogate of UTF-16 symbol
inline constexpr uint32_t trail_surr(rune r) {
    return ((r - 0x10000u) % 0x400u) + MIN_TRAIL_SURR;
}

Regexp* range(RESpec& spec, const Range* r);

} // namespace utf16
} // namespace re2c

#endif // _RE2C_RE_ENCODING_UTF16_
