#include <assert.h>
#include <stdint.h>

static uint32_t num(const char *s, const char *e)
{
    uint32_t n = 0;
    for (; s < e; ++s) n = n * 10 + (*s - '0');
    return n;
}

/*!maxnmatch:re2c*/

static uint32_t lex(const char *YYCURSOR)
{
    const char *YYMARKER;
    const char *yypmatch[YYMAXNMATCH * 2];
    uint32_t yynmatch;
    /*!stags:re2c format = 'const char *@@;'; */

    /*!re2c
    re2c:define:YYCTYPE = char;
    re2c:yyfill:enable = 0;
    re2c:flags:posix-captures = 1;

    oct = [0-9]{1,3};
    dot = [.];

    (oct) dot (oct) dot (oct) dot (oct) {
        return num(yypmatch[8], yypmatch[9])
            + (num(yypmatch[6], yypmatch[7]) << 8)
            + (num(yypmatch[4], yypmatch[5]) << 16)
            + (num(yypmatch[2], yypmatch[3]) << 24);
    }
    * { return 0; }

    */
}

int main()
{
    assert(lex("1.2.3.4") == 0x01020304);
    assert(lex("127.0.0.1") == 0x7f000001);
    assert(lex("255.255.255.255") == 0xffffffff);
    return 0;
}
