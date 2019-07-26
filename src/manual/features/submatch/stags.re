#include <assert.h>
#include <stdint.h>

static uint32_t num(const char *s, const char *e)
{
    uint32_t n = 0;
    for (; s < e; ++s) n = n * 10 + (*s - '0');
    return n;
}

static uint32_t lex(const char *YYCURSOR)
{
    const char *YYMARKER, *o1, *o2, *o3, *o4;
    /*!stags:re2c format = 'const char *@@;'; */

    /*!re2c
    re2c:define:YYCTYPE = char;
    re2c:yyfill:enable = 0;
    re2c:flags:tags = 1;

    oct = [0-9]{1,3};
    dot = [.];

    @o1 oct dot @o2 oct dot @o3 oct dot @o4 oct {
        return num(o4, YYCURSOR)
            + (num(o3, o4 - 1) << 8)
            + (num(o2, o3 - 1) << 16)
            + (num(o1, o2 - 1) << 24);
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
