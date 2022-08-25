#include <iostream>

#include "src/codegen/helpers.h"

namespace re2c {

static bool is_space(uint32_t c) {
    switch (c) {
    case '\t':
    case '\f':
    case '\v':
    case '\n':
    case '\r':
    case ' ':
        return true;
    default:
        return false;
    }
}

static inline char hex(uint32_t c) {
    static const char* HEX_TABLE = "0123456789ABCDEF";
    return HEX_TABLE[c & 0x0F];
}

static void print_char(std::ostream& o, uint32_t c, bool dot) {
    switch (c) {
    case '\'':
        o << (dot ? "'"     : "\\'");
        break;
    case '"':
        o << (dot ? "\\\""  : "\"");
        break;
    case '\n':
        o << (dot ? "\\\\n" : "\\n");
        break;
    case '\t':
        o << (dot ? "\\\\t" : "\\t");
        break;
    case '\v':
        o << (dot ? "\\\\v" : "\\v");
        break;
    case '\b':
        o << (dot ? "\\\\b" : "\\b");
        break;
    case '\r':
        o << (dot ? "\\\\r" : "\\r");
        break;
    case '\f':
        o << (dot ? "\\\\f" : "\\f");
        break;
    case '\a':
        o << (dot ? "\\\\a" : "\\a");
        break;
    case '\\':
        o << "\\\\"; // both .dot and C/C++ code expect "\\"
        break;
    default:
        o << static_cast<char> (c);
        break;
    }
}

bool is_print(uint32_t c) {
    return c >= 0x20 && c < 0x7F;
}

void print_hex(std::ostream& o, uint32_t c, uint32_t szcunit) {
    o << "0x";

    if (szcunit >= 4) {
        o << hex(c >> 28u) << hex(c >> 24u) << hex(c >> 20u) << hex(c >> 16u);
    }

    if (szcunit >= 2) {
        o << hex(c >> 12u) << hex(c >> 8u);
    }

    o << hex(c >> 4u) << hex(c);
}

void print_char_or_hex(std::ostream& o, uint32_t c, uint32_t szcunit, bool hex, bool dot) {
    if (!hex && (is_print(c) || is_space(c))) {
        o << '\'';
        print_char(o, c, dot);
        o << '\'';
    } else {
        print_hex(o, c, szcunit);
    }
}

static void print_char_for_span(
        std::ostream& o, uint32_t c, uint32_t szcunit, bool ebcdic, bool dot) {
    if (!ebcdic && c != ']' && is_print(c)) {
        print_char(o, c, dot);
    } else {
        print_hex(o, c, szcunit);
    }
}

void print_span(std::ostream& o, uint32_t l, uint32_t u, uint32_t szcunit, bool ebcdic, bool dot) {
    o << "[";
    print_char_for_span(o, l, szcunit, ebcdic, dot);
    if (u - l > 1) {
        o << "-";
        print_char_for_span(o, u - 1, szcunit, ebcdic, dot);
    }
    o << "]";
}

} // namespace re2c
