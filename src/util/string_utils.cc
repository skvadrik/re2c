#include <limits>

#include "src/util/string_utils.h"

namespace re2c {

// expected characters: [0-9a-zA-Z]
static inline uint32_t hex_digit(const char c) {
    switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a':
    case 'A': return 0xA;
    case 'b':
    case 'B': return 0xB;
    case 'c':
    case 'C': return 0xC;
    case 'd':
    case 'D': return 0xD;
    case 'e':
    case 'E': return 0xE;
    case 'f':
    case 'F': return 0xF;
    default:
        return ~0u; // unexpected
    }
}

// expected string format: "\" [xXuU] [0-9a-zA-Z]*
uint32_t unesc_hex(const char* s, const char* s_end) {
    uint32_t n = 0;
    for (s += 2; s != s_end; ++s) {
        n <<= 4;
        n += hex_digit (*s);
    }
    return n;
}

// expected string format: "\" [0-7]*
uint32_t unesc_oct(const char* s, const char* s_end) {
    uint32_t n = 0;
    for (++s; s != s_end; ++s) {
        n <<= 3;
        n += static_cast<uint8_t> (*s - '0');
    }
    return n;
}

std::string escape_backslashes(const std::string& str) {
    const size_t len = str.length();
    std::string escaped;
    escaped.reserve(len * 2);

    for (size_t i = 0; i < len;) {
        char c = str[i++];
        escaped += c;
        if (c == '\\') {
            // escape backslash
            escaped += '\\';
            // if already escaped, skip next character
            if (i < len && str[i] == '\\') ++i;
        }
    }

    return escaped;
}

// Assumes that string matches regexp `[0-9]+`. Returns false on overflow.
bool s_to_u32_unsafe(const char* s, const char* s_end, uint32_t& number) {
    uint64_t u = 0;
    for (; s != s_end; ++s) {
        u *= 10;
        u += static_cast<uint32_t> (*s) - 0x30;
        if (u >= std::numeric_limits<uint32_t>::max()) {
            return false;
        }
    }
    number = static_cast<uint32_t> (u);
    return true;
}

// Assumes that string matches regexp `"-"? [0-9]+`. Returns false on underflow/overflow.
bool s_to_i32_unsafe(const char* s, const char* s_end, int32_t& number) {
    int64_t i = 0;
    if (*s == '-') {
        ++s;
        for (; s != s_end; ++s) {
            i *= 10;
            i -= *s - 0x30;
            if (i < std::numeric_limits<int32_t>::min()) {
                return false;
            }
        }
    } else {
        for (; s != s_end; ++s) {
            i *= 10;
            i += *s - 0x30;
            if (i > std::numeric_limits<int32_t>::max()) {
                return false;
            }
        }
    }
    number = static_cast<int32_t> (i);
    return true;
}

} // namespace re2c
