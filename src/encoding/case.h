#ifndef _RE2C_RE_ENCODING_CASE_
#define _RE2C_RE_ENCODING_CASE_

#include <stdint.h>

namespace re2c {

// TODO: support non-ASCII encodings
bool is_alpha(uint32_t c);
uint32_t to_lower_unsafe(uint32_t c);
uint32_t to_upper_unsafe(uint32_t c);

inline bool is_alpha(uint32_t c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

inline uint32_t to_lower_unsafe(uint32_t c) {
    return c | 0x20u;
}

inline uint32_t to_upper_unsafe(uint32_t c) {
    return c & ~0x20u;
}

} // namespace re2c

#endif // _RE2C_RE_ENCODING_CASE_
