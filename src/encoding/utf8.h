#ifndef _RE2C_RE_ENCODING_UTF8_
#define _RE2C_RE_ENCODING_UTF8_

#include <stdint.h>

namespace re2c {

class Range;
struct Regexp;
struct RESpec;

namespace utf8 {

using rune = uint32_t;

// Maximum characters per code point (rune).
static constexpr uint32_t MAX_RUNE_LENGTH = 4u;

// Decoding error.
static constexpr uint32_t ERROR = 0xFFFDu;

// Maximum values for UTF8 code points of length 1-4 bytes.
static constexpr rune MAX_1BYTE_RUNE = 0x7Fu;     // 0000 0000  0000 0000  0111 1111
static constexpr rune MAX_2BYTE_RUNE = 0x7FFu;    // 0000 0000  0000 0111  1111 1111
static constexpr rune MAX_3BYTE_RUNE = 0xFFFFu;   // 0000 0000  1111 1111  1111 1111
static constexpr rune MAX_4BYTE_RUNE = 0x1FFFFFu; // 0001 1111  1111 1111  1111 1111

// Maximum Unicode code point is U+10FFFF (it is less than the maximum 4-byte UTF8 code point).
static constexpr rune MAX_RUNE = 0x10FFFFu;

static constexpr uint32_t PREFIX_1BYTE = 0u;    // 0000 0000
static constexpr uint32_t INFIX        = 0x80u; // 1000 0000
static constexpr uint32_t PREFIX_2BYTE = 0xC0u; // 1100 0000
static constexpr uint32_t PREFIX_3BYTE = 0xE0u; // 1110 0000
static constexpr uint32_t PREFIX_4BYTE = 0xF0u; // 1111 0000
static constexpr uint32_t PREFIX_5BYTE = 0xF8u; // 1111 1000

static constexpr uint32_t SHIFT = 6u;
static constexpr uint32_t MASK = 0x3Fu; // 0011 1111

// UTF-8 bytestring for given Unicode code point.
uint32_t rune_to_bytes(uint32_t* s, rune r);

// Read Unicode code point for the given (pre-validated) UTF-8 bytestring.
uint32_t decode_unsafe(const uint8_t* str);

// Length of a UTF-8 bytestring for a given Unicode code point.
uint32_t rune_length(rune r);

// Maximum Unicode code point with a given length of UTF-8 bytestring.
rune max_rune(uint32_t i);

Regexp* range(RESpec& spec, const Range* r);

} // namespace utf8
} // namespace re2c

#endif // _RE2C_RE_ENCODING_UTF8_
