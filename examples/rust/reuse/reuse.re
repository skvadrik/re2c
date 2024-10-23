// re2rust $INPUT -o $OUTPUT --input-encoding utf8 --api simple

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.
/*!rules:re2c
    re2c:yyfill:enable = 0;

    "∀x ∃y" { return Some(yycursor); }
    *       { return None; }
*/

fn lex_utf8(yyinput: &[u8]) -> Option<usize> {
    assert!(yyinput.len() > 0); // expect nonempty input
    let (mut yycursor, mut yymarker) = (0, 0);
    /*!use:re2c
        re2c:encoding:utf8 = 1;
        re2c:YYCTYPE = u8;
    */
}

fn lex_utf32(yyinput: &[u32]) -> Option<usize> {
    assert!(yyinput.len() > 0); // expect nonempty input
    let (mut yycursor, mut yymarker) = (0, 0);
    /*!use:re2c
        re2c:encoding:utf32 = 1;
        re2c:YYCTYPE = u32;
    */
}

fn main() {
    let s8 = vec![0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79];
    assert_eq!(lex_utf8(&s8), Some(s8.len()));

    let s32 = vec![0x2200, 0x78, 0x20, 0x2203, 0x79];
    assert_eq!(lex_utf32(&s32), Some(s32.len()));
}
