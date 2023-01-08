// re2c $INPUT -o $OUTPUT --input-encoding utf8
#include <assert.h>
#include <stdint.h>

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.
/*!rules:re2c
    re2c:yyfill:enable = 0;

    "∀x ∃y" { return 0; }
    *       { return 1; }
*/

static int lex_utf8(const uint8_t *s) {
    const uint8_t *YYCURSOR = s, *YYMARKER;
    /*!use:re2c
        re2c:define:YYCTYPE = uint8_t;
        re2c:encoding:utf8 = 1;
    */
}

static int lex_utf32(const uint32_t *s) {
    const uint32_t *YYCURSOR = s, *YYMARKER;
    /*!use:re2c
        re2c:define:YYCTYPE = uint32_t;
        re2c:encoding:utf32 = 1;
    */
}

int main() {
    static const uint8_t s8[] = // UTF-8
        { 0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79 };

    static const uint32_t s32[] = // UTF32
        { 0x00002200, 0x00000078, 0x00000020, 0x00002203, 0x00000079 };

    assert(lex_utf8(s8) == 0);
    assert(lex_utf32(s32) == 0);
    return 0;
}

