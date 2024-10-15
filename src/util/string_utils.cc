#include <limits>

#include "src/util/string_utils.h"

namespace re2c {

// expected characters: [0-9a-zA-Z]
static inline uint32_t hex_digit(const uint8_t c) {
    switch (c) {
    case '0'_u8: return 0;
    case '1'_u8: return 1;
    case '2'_u8: return 2;
    case '3'_u8: return 3;
    case '4'_u8: return 4;
    case '5'_u8: return 5;
    case '6'_u8: return 6;
    case '7'_u8: return 7;
    case '8'_u8: return 8;
    case '9'_u8: return 9;
    case 'a'_u8:
    case 'A'_u8: return 0xA;
    case 'b'_u8:
    case 'B'_u8: return 0xB;
    case 'c'_u8:
    case 'C'_u8: return 0xC;
    case 'd'_u8:
    case 'D'_u8: return 0xD;
    case 'e'_u8:
    case 'E'_u8: return 0xE;
    case 'f'_u8:
    case 'F'_u8: return 0xF;
    default:
        return ~0u; // unexpected
    }
}

// expected string format: "\" [xXuU] [0-9a-zA-Z]*
uint32_t unesc_hex(const uint8_t* s, const uint8_t* s_end) {
    uint32_t n = 0;
    for (s += 2; s != s_end; ++s) {
        n <<= 4;
        n += hex_digit(*s);
    }
    return n;
}

// expected string format: "\" [0-7]*
uint32_t unesc_oct(const uint8_t* s, const uint8_t* s_end) {
    uint32_t n = 0;
    for (++s; s != s_end; ++s) {
        n <<= 3;
        n += *s - 0x30u;
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
bool s_to_u32_unsafe(const uint8_t* s, const uint8_t* s_end, uint32_t& number) {
    uint64_t u = 0;
    for (; s != s_end; ++s) {
        u *= 10;
        u += *s - 0x30u;
        if (u >= std::numeric_limits<uint32_t>::max()) {
            return false;
        }
    }
    number = static_cast<uint32_t>(u);
    return true;
}

// Assumes that string matches regexp `"-"? [0-9]+`. Returns false on underflow/overflow.
bool s_to_i32_unsafe(const uint8_t* s, const uint8_t* s_end, int32_t& number) {
    int64_t i = 0;
    if (*s == '-') {
        ++s;
        for (; s != s_end; ++s) {
            i *= 10;
            i -= *s - 0x30u;
            if (i < std::numeric_limits<int32_t>::min()) {
                return false;
            }
        }
    } else {
        for (; s != s_end; ++s) {
            i *= 10;
            i += *s - 0x30u;
            if (i > std::numeric_limits<int32_t>::max()) {
                return false;
            }
        }
    }
    number = static_cast<int32_t>(i);
    return true;
}

void strrreplace(std::string& s, const std::string& s1, const std::string& s2) {
    const size_t l1 = s1.length(), l2 = s2.length();
    if (l1 != 0) {
        std::string::size_type pos = s.find(s1);
        while (pos != std::string::npos) {
            s.replace(pos, l1, s2);
            pos = s.find(s1, pos + l2);
        }
    }
}

} // namespace re2c
