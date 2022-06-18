#include "lib/test_helper.h"

static inline regoff_t parse_offset(const char* s, const char* e) {
    regoff_t n = 0;
    for (; s < e; ++s) {
        n = n * 10 + (*s - '0');
    }
    return n;
}

bool parse_submatch(const char* s, std::vector<std::vector<regoff_t> >& result) {
    result.clear();
    if (!s) return true;

    std::vector<regoff_t>* v;
    const char* n1, *n2, *m1, *m2, *YYMARKER, *YYCURSOR = s;
    /*!stags:re2c format = "const char *@@;"; */

next:
    result.push_back(std::vector<regoff_t>());
    v = &result.back();

loop: /*!re2c
    re2c:define:YYCTYPE = char;
    re2c:yyfill:enable = 0;
    re2c:flags:tags = 1;

    *      { return false; }
    "\x00" { return true; }
    ","    { goto next; }

    "(?,?)" {
        v->push_back(-1);
        v->push_back(-1);
        goto loop;
    }

    "(" @n1 [0-9]+ @n2 "," @m1 [0-9]+ @m2 ")" {
        v->push_back(parse_offset(n1, n2));
        v->push_back(parse_offset(m1, m2));
        goto loop;
    }
*/
}
