// re2rust $INPUT -o $OUTPUT --input-encoding utf8 --recursive-functions

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.
/*!rules:re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYPEEK    = "*_str.get_unchecked(_cur)";
    re2c:define:YYSKIP    = "_cur += 1;";
    re2c:define:YYBACKUP  = "_mar = _cur;";
    re2c:define:YYRESTORE = "_cur = _mar;";

    "∀x ∃y" { return Some(_cur); }
    *       { return None; }
*/

/*!use:re2c
    re2c:define:YYFN = [
        "lex_utf8;Option<usize>",
        "_str;&[u8]",
        "_cur;usize;mut",
        "_mar;usize;mut"
    ];

    re2c:encoding:utf8 = 1;
    re2c:define:YYCTYPE = u8;
*/

/*!use:re2c
    re2c:define:YYFN = [
        "lex_utf32;Option<usize>",
        "_str;&[u32]",
        "_cur;usize;mut",
        "_mar;usize;mut"
    ];

    re2c:encoding:utf32 = 1;
    re2c:define:YYCTYPE = u32;
*/

fn main() {
    let s8 = vec![0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79];
    assert_eq!(lex_utf8(&s8, 0, 0), Some(s8.len()));

    let s32 = vec![0x2200, 0x78, 0x20, 0x2203, 0x79];
    assert_eq!(lex_utf32(&s32, 0, 0), Some(s32.len()));
}
