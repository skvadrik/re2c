#ifndef _RE2C_CODEGEN_HELPERS_
#define _RE2C_CODEGEN_HELPERS_

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <sstream>

#include "src/debug/debug.h"


namespace re2c {

bool is_print(uint32_t c);
void prtHex(std::ostream &o, uint32_t c, uint32_t szcunit);
void prtChOrHex(std::ostream &o, uint32_t c, uint32_t szcunit, bool ebcdic, bool dot);
void printSpan(std::ostream &o, uint32_t l, uint32_t u, uint32_t szcunit, bool ebcdic,
    bool dot);

template<typename T>
void argsubst(std::ostringstream &os, const std::string &stub, const char *arg,
    bool allow_unnamed, T val)
{
    assert(!stub.empty());
    DASSERT(arg != NULL);

    const std::string str = os.str();
    os.str("");

    const char *s = str.c_str(), *e = s + str.length(), *p, *q;
    const size_t l = strlen(arg);

    while ((p = strstr(s, stub.c_str()))) {
        os.write(s, p - s);
        s = p;
        p += stub.length();
        q = *p == '{' ? strchr(p + 1, '}') : NULL;

        if (q && l == (size_t)(q - p - 1) && memcmp(p + 1, arg, l) == 0) {
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

inline std::string indent(uint32_t n, const std::string &s)
{
    std::string ind;
    for (; n --> 0; ind += s);
    return ind;
}

} // namespace re2c

#endif // _RE2C_CODEGEN_HELPERS_
