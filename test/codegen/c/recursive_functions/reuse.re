// re2c $INPUT -o $OUTPUT --input-encoding utf8 --recursive-functions -i

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.

#include <assert.h>
#include <stdint.h>

/*!rules:re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYCURSOR = st.cur;
    re2c:define:YYMARKER = st.mar;

    "∀x ∃y" { return 0; }
    *       { return 1; }
*/

struct State8 {
    const uint8_t* cur;
    const uint8_t* mar;
};

/*!use:re2c
    re2c:define:YYFN = ["lex_utf8;int", "st;State8&"];
    re2c:define:YYCTYPE = uint8_t;
    re2c:flags:8 = 1;
*/

struct State32 {
    const uint32_t* cur;
    const uint32_t* mar;
};

/*!use:re2c
    re2c:define:YYFN = ["lex_utf32;int", "st;State32&"];
    re2c:define:YYCTYPE = uint32_t;
    re2c:flags:8 = 0;
    re2c:flags:u = 1;
*/

int main() {
    static const uint8_t s8[] = // UTF-8
        { 0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79 };
    State8 st8 = {s8, nullptr};

    static const uint32_t s32[] = // UTF32
        { 0x00002200, 0x00000078, 0x00000020, 0x00002203, 0x00000079 };
    State32 st32 = {s32, nullptr};

    assert(lex_utf8(st8) == 0);
    assert(lex_utf32(st32) == 0);
    return 0;
}

