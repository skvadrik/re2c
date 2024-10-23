// re2rust $INPUT -o $OUTPUT --utf8 --api simple

/*!include:re2c "unicode_categories.re" */

fn lex(yyinput: &[u8]) -> bool {
    assert_eq!(yyinput.last(), Some(&0)); // expect null-terminated input

    let (mut yycursor, mut yymarker) = (0, 0);
    /*!re2c
        re2c:YYCTYPE = u8;
        re2c:yyfill:enable = 0;

        // Simplified "Unicode Identifier and Pattern Syntax"
        // (see https://unicode.org/reports/tr31)
        id_start    = L | Nl | [$_];
        id_continue = id_start | Mn | Mc | Nd | Pc | [\u200D\u05F3];
        identifier  = id_start id_continue*;

        identifier { return true; }
        *          { return false; }
    */
}

fn main() {
    assert!(lex("_Ыдентификатор\0".as_bytes()));
}
