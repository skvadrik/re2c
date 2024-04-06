#include <iostream>

#include "src/codegen/helpers.h"
#include "src/options/opt.h"

namespace re2c {

static inline char hex(uint32_t c) {
    static const char* HEX_TABLE = "0123456789ABCDEF";
    return HEX_TABLE[c & 0x0F];
}

static void print_char(std::ostream& o, uint32_t c, const opt_t* opts) {
    bool dot = opts->target == Target::DOT;
    switch (c) {
    case '\'':
        o << (dot ? "'" : "\\'");
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
        if (is_print(c) || is_space(c)) {
            o << static_cast<char> (c);
        } else {
            CHECK(opts->encoding.cunit_size() == 1);
            o << (dot ? "\\\\x" : "\\x") << hex(c >> 4u) << hex(c);
        }
        break;
    }
}

void print_hex(std::ostream& o, uint32_t c, const opt_t* opts) {
    uint32_t szcunit = opts->encoding.cunit_size();
    o << "0x";
    if (szcunit >= 4) {
        o << hex(c >> 28u) << hex(c >> 24u) << hex(c >> 20u) << hex(c >> 16u);
    }
    if (szcunit >= 2) {
        o << hex(c >> 12u) << hex(c >> 8u);
    }
    o << hex(c >> 4u) << hex(c);
}

static bool print_as_char(uint32_t c, const opt_t* opts) {
    switch (opts->char_literals) {
    case CharLit::CHAR:
        return opts->encoding.cunit_size() == 1;
    case CharLit::HEX:
        return false;
    case CharLit::CHAR_OR_HEX:
        return (is_print(c) || is_space(c)) && opts->encoding.type() != Enc::Type::EBCDIC;
    }
    UNREACHABLE();
    return false;
}

void print_char_or_hex(std::ostream& o, uint32_t c, const opt_t* opts) {
    if (print_as_char(c, opts)) {
        o << '\'';
        print_char(o, c, opts);
        o << '\'';
    } else {
        print_hex(o, c, opts);
    }
}

static void print_char_for_span(std::ostream& o, uint32_t c, const opt_t* opts) {
    if (opts->encoding.type() != Enc::Type::EBCDIC && c != ']' && is_print(c)) {
        print_char(o, c, opts);
    } else {
        print_hex(o, c, opts);
    }
}

void print_span(std::ostream& o, uint32_t l, uint32_t u, const opt_t* opts) {
    o << "[";
    print_char_for_span(o, l, opts);
    if (u - l > 1) {
        o << "-";
        print_char_for_span(o, u - 1, opts);
    }
    o << "]";
}

const char* sprint_null(const opt_t* opts) {
    return print_as_char(0, opts) ? "'\x00'" : "0";
}

} // namespace re2c
