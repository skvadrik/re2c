// re2rust $INPUT -o $OUTPUT --utf8

/*!include:re2c "unicode_categories.re" */

fn lex(str: &[u8]) -> bool {
    let (mut cur, mut mar) = (0, 0);
    /*!re2c
        re2c:define:YYCTYPE   = u8;
        re2c:define:YYPEEK    = "*str.get_unchecked(cur)";
        re2c:define:YYSKIP    = "cur += 1;";
        re2c:define:YYBACKUP  = "mar = cur;";
        re2c:define:YYRESTORE = "cur = mar;";
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
