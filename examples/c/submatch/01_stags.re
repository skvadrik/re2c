// re2c $INPUT -o $OUTPUT
#include <assert.h>
#include <stdint.h>

static uint32_t num(const char *s, const char *e)
{
    uint32_t n = 0;
    for (; s < e; ++s) n = n * 10 + (*s - '0');
    return n;
}

static const uint64_t ERROR = ~0lu;

static uint64_t lex(const char *YYCURSOR)
{
    const char *YYMARKER, *o1, *o2, *o3, *o4;
    /*!stags:re2c format = 'const char *@@;\n'; */

    /*!re2c
    re2c:yyfill:enable = 0;
    re2c:flags:tags = 1;
    re2c:define:YYCTYPE = char;

    octet = [0-9] | [1-9][0-9] | [1][0-9][0-9] | [2][0-4][0-9] | [2][5][0-5];
    dot = [.];
    end = [\x00];

    @o1 octet dot @o2 octet dot @o3 octet dot @o4 octet end {
        return num(o4, YYCURSOR - 1)
            + (num(o3, o4 - 1) << 8)
            + (num(o2, o3 - 1) << 16)
            + (num(o1, o2 - 1) << 24);
    }
    * { return ERROR; }
    */
}

int main()
{
    assert(lex("1.2.3.4") == 0x01020304);
    assert(lex("127.0.0.1") == 0x7f000001);
    assert(lex("255.255.255.255") == 0xffffffff);
    assert(lex("1.2.3.") == ERROR);
    assert(lex("1.2.3.256") == ERROR);
    return 0;
}
