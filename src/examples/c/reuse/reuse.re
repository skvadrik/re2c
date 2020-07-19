// re2c $INPUT -o $OUTPUT -r --input-encoding utf8
#include <assert.h>
#include <stdint.h>

/*!rules:re2c
    re2c:yyfill:enable = 0;

    "∀x ∃y: p(x, y)" { return 0; }
    *                { return 1; }
*/

static int lex_utf8(const uint8_t *YYCURSOR)
{
    const uint8_t *YYMARKER;
    /*!use:re2c
    re2c:define:YYCTYPE = uint8_t;
    re2c:flags:8 = 1;
    */
}

static int lex_utf32(const uint32_t *YYCURSOR)
{
    const uint32_t *YYMARKER;
    /*!use:re2c
    re2c:define:YYCTYPE = uint32_t;
    re2c:flags:8 = 0;
    re2c:flags:u = 1;
    */
}

int main()
{
    static const uint8_t s8[] = // UTF-8
        { 0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79
        , 0x3a, 0x20, 0x70, 0x28, 0x78, 0x2c, 0x20, 0x79, 0x29 };

    static const uint32_t s32[] = // UTF32
        { 0x00002200, 0x00000078, 0x00000020, 0x00002203
        , 0x00000079, 0x0000003a, 0x00000020, 0x00000070
        , 0x00000028, 0x00000078, 0x0000002c, 0x00000020
        , 0x00000079, 0x00000029 };

    assert(lex_utf8(s8) == 0);
    assert(lex_utf32(s32) == 0);
    return 0;
}

