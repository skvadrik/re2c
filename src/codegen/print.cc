#include <iostream>

#include "src/codegen/print.h"


namespace re2c {

static bool is_space(uint32_t c)
{
    switch (c) {
    case '\t':
    case '\f':
    case '\v':
    case '\n':
    case '\r':
    case ' ':  return true;
    default:   return false;
    }
}

static inline char hex(uint32_t c)
{
    static const char * sHex = "0123456789ABCDEF";
    return sHex[c & 0x0F];
}

static void prtCh(std::ostream& o, uint32_t c, bool dot)
{
    switch (c) {
    case '\'': o << (dot ? "'"     : "\\'"); break;
    case '"':  o << (dot ? "\\\""  : "\"");  break;
    case '\n': o << (dot ? "\\\\n" : "\\n"); break;
    case '\t': o << (dot ? "\\\\t" : "\\t"); break;
    case '\v': o << (dot ? "\\\\v" : "\\v"); break;
    case '\b': o << (dot ? "\\\\b" : "\\b"); break;
    case '\r': o << (dot ? "\\\\r" : "\\r"); break;
    case '\f': o << (dot ? "\\\\f" : "\\f"); break;
    case '\a': o << (dot ? "\\\\a" : "\\a"); break;
    case '\\': o << "\\\\";                  break; // both .dot and C/C++ code expect "\\"
    default:   o << static_cast<char> (c);   break;
    }
}

bool is_print(uint32_t c)
{
    return c >= 0x20 && c < 0x7F;
}

void prtHex(std::ostream& o, uint32_t c, uint32_t szcunit)
{
    o << "0x";

    if (szcunit >= 4) {
        o << hex(c >> 28u) << hex(c >> 24u) << hex(c >> 20u) << hex(c >> 16u);
    }

    if (szcunit >= 2) {
        o << hex(c >> 12u) << hex(c >> 8u);
    }

    o << hex(c >> 4u) << hex(c);
}

void prtChOrHex(std::ostream& o, uint32_t c, uint32_t szcunit, bool ebcdic, bool dot)
{
    if (!ebcdic && (is_print(c) || is_space(c))) {
        o << '\'';
        prtCh(o, c, dot);
        o << '\'';
    } else {
        prtHex(o, c, szcunit);
    }
}

static void prtChOrHexForSpan(std::ostream& o, uint32_t c, uint32_t szcunit, bool ebcdic, bool dot)
{
    if (!ebcdic && c != ']' && is_print(c)) {
        prtCh(o, c, dot);
    } else {
        prtHex(o, c, szcunit);
    }
}

void printSpan(std::ostream& o, uint32_t l, uint32_t u, uint32_t szcunit, bool ebcdic, bool dot)
{
    o << "[";
    prtChOrHexForSpan(o, l, szcunit, ebcdic, dot);
    if (u - l > 1) {
        o << "-";
        prtChOrHexForSpan(o, u - 1, szcunit, ebcdic, dot);
    }
    o << "]";
}

} // end namespace re2c

