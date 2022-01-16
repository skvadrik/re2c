// re2rust $INPUT -o $OUTPUT --input-encoding utf8

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.
/*!rules:re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYPEEK    = "*str.get_unchecked(cur)";
    re2c:define:YYSKIP    = "cur += 1;";
    re2c:define:YYBACKUP  = "mar = cur;";
    re2c:define:YYRESTORE = "cur = mar;";

    "∀x ∃y" { return Some(cur); }
    *       { return None; }
*/

fn lex_utf8(str: &[u8]) -> Option<usize> {
    let (mut cur, mut mar) = (0, 0);
    /*!use:re2c
        re2c:encoding:utf8 = 1;
        re2c:define:YYCTYPE = u8;
    */
}

fn lex_utf32(str: &[u32]) -> Option<usize> {
    let (mut cur, mut mar) = (0, 0);
    /*!use:re2c
        re2c:encoding:utf32 = 1;
        re2c:define:YYCTYPE = u32;
    */
}

fn main() {
    let s8 = vec![0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79];
    assert_eq!(lex_utf8(&s8), Some(s8.len()));

    let s32 = vec![0x2200, 0x78, 0x20, 0x2203, 0x79];
    assert_eq!(lex_utf32(&s32), Some(s32.len()));
}
