// re2rust $INPUT -o $OUTPUT --no-unsafe --api simple

fn lex(yyinput: &[u8]) -> bool {
    let mut yycursor = 0;
    /*!re2c
        re2c:YYCTYPE = u8;
        re2c:yyfill:enable = 0;

        [1-9][0-9]* { return true; }
        *           { return false; }
    */
}

fn main() {
    assert!(lex(b"1234\0"));
}
