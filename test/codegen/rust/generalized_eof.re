// re2rust $INPUT -o $OUTPUT --api simple

/*!rules:re2c:x
    re2c:YYCTYPE = u8;
    re2c:api:style = free-form;

    $           { return 0; }
    *           { return 1; }
    [a] $       { return 2; }
    [a]         { return 3; }
    [b] $ | [b] { return 4; }
    [c]+ $      { return 5; }
*/

fn lex_simple(yyinput: &[u8]) -> isize {
    let mut yycursor = 0;
    let mut yymarker = 0;
    let yylimit = yyinput.len() - 1;
    /*!use:re2c:x
        re2c:yyfill:enable = 0;
    */
}

fn lex_eof(yyinput: &[u8]) -> isize {
    let mut yycursor = 0;
    let mut yymarker = 0;
    let yylimit = yyinput.len() - 1;
    /*!use:re2c:x
        re2c:eof = 0;
        re2c:YYFILL = "false";
        re2c:YYEND = "yycursor == yylimit";
    */
}

/*!max:re2c*/

fn lex_scc(s: &[u8]) -> isize {
    let mut yycursor = 0;
    let mut yymarker = 0;
    let yylimit = s.len() + YYMAXFILL;
    let end = s.len() - 1;

    // Copy string to a buffer and add YYMAXFILL zero padding.
    let mut yyinput = Vec::with_capacity(yylimit);
    yyinput.extend_from_slice(s);
    yyinput.extend([0 as u8; YYMAXFILL]);

    /*!use:re2c:x
        re2c:YYFILL = "return -1;";
        re2c:YYEND = "yycursor == end";
    */
}

fn test(s: &[u8], r: isize) {
    assert_eq!(lex_simple(s), r);
    assert_eq!(lex_eof(s), r);
    assert_eq!(lex_scc(s), r);
}

fn main() {
    test(b"\x00", 0);
    test(b"a\x00", 2);
    test(b"ax\x00", 3);
    test(b"b\x00", 4);
    test(b"bx\x00", 4);
    test(b"ccc\x00", 5);
}
