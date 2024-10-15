#ifndef _RE2C_CODEGEN_HELPERS_
#define _RE2C_CODEGEN_HELPERS_

#include <stdint.h>
#include <string.h>
#include <sstream>

#include "src/util/check.h"

namespace re2c {

struct opt_t;

void print_hex(std::ostream& o, uint32_t c, const opt_t* opts);
void print_char_or_hex(std::ostream& o, uint32_t c, const opt_t* opts);
void print_span(std::ostream& o, uint32_t l, uint32_t u, const opt_t* opts);
const char* sprint_null(const opt_t* opts);

inline bool is_print(uint32_t c) {
    return c >= 0x20 && c < 0x7F;
}

inline bool is_space(uint32_t c) {
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

inline bool is_space_nonl(uint32_t c) {
    switch (c) {
    case '\t':
    case '\f':
    case '\v':
    case '\r':
    case ' ':
        return true;
    default:
        return false;
    }
}

template<typename T>
void argsubst(std::ostringstream& os,
              const std::string& str,
              const std::string& stub,
              const char* arg,
              bool allow_unnamed,
              T val) {
    CHECK(!stub.empty());
    DCHECK(arg != nullptr);

    const char* s = str.c_str(), *e = s + str.length(), *p, *q;
    const size_t l = strlen(arg);

    while ((p = strstr(s, stub.c_str()))) {
        os.write(s, p - s);
        s = p;
        p += stub.length();
        q = *p == '{' ? strchr(p + 1, '}') : nullptr;

        if (q && l == static_cast<size_t>(q - p - 1) && memcmp(p + 1, arg, l) == 0) {
            // named substitution of the form @@{arg}
            os << val;
            s = q + 1;
        } else if (allow_unnamed) {
            // unnamed substitution of the form @@
            os << val;
            s = p;
        } else {
            // none of the above, skip one character (and not the whole
            // placeholder) to allow cases like @@@{arg} to find @@{arg}
            os.write(s, 1);
            ++s;
        }
    }
    os.write(s, e - s);
}

template<typename T>
void argsubst(std::ostringstream& os,
              const std::string& stub,
              const char* arg,
              bool allow_unnamed,
              T val) {
    const std::string str = os.str();
    os.str("");
    argsubst(os, str, stub, arg, allow_unnamed, val);
}

inline std::string indent(uint32_t n, const std::string& s) {
    std::string ind;
    for (; n --> 0; ind += s);
    return ind;
}

} // namespace re2c

#endif // _RE2C_CODEGEN_HELPERS_
