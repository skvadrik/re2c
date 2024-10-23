// re2v $INPUT -o $OUTPUT --input-encoding utf8

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.
/*!rules:re2c
    re2c:yyfill:enable = 0;

    "∀x ∃y" { return 0 }
    *       { return 1 }
*/

fn lex_utf8(yyinput []u8) int {
    mut yycursor, mut yymarker := 0, 0
    /*!use:re2c
        re2c:encoding:utf8 = 1;
        re2c:YYCTYPE = u8; // the default
    */
}

fn lex_utf32(yyinput []u32) int {
    mut yycursor, mut yymarker := 0, 0
    /*!use:re2c
        re2c:encoding:utf32 = 1;
        re2c:YYCTYPE = u32;
    */
}

fn main() {
    s8 := [u8(0xe2), u8(0x88), u8(0x80), u8(0x78), u8(0x20), u8(0xe2), u8(0x88), u8(0x83), u8(0x79)]
    s32 := [u32(0x2200), u32(0x78), u32(0x20), u32(0x2203), u32(0x79)]
    assert lex_utf8(s8) == 0
    assert lex_utf32(s32) == 0
}
