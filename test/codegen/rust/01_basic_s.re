// re2rust $INPUT -o $OUTPUT -s

fn lex(s: &[u8]) -> bool {
    let mut cursor = 0;
    /*!re2c
        re2c:define:YYCTYPE = u8;
        re2c:define:YYPEEK = "*s.get_unchecked(cursor)";
        re2c:define:YYSKIP = "cursor += 1;";
        re2c:define:YYDEBUG = "format!(\"lex: char '{}' in state {}\\n\", @@{char}, @@{state});";
        re2c:yyfill:enable = 0;

        number = [1-9][0-9]*;

        number { return true; }
        *      { return false; }
    */
}

fn main() {
    assert!(lex(b"1234\0"));
}
