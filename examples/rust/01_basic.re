// re2rust $INPUT -o $OUTPUT --no-unsafe

fn lex(yyinput: &[u8]) -> bool {
    let mut yycursor = 0;
    /*!re2c
        re2c:api = default;
        re2c:define:YYCTYPE = u8;
        re2c:yyfill:enable = 0;

        number = [1-9][0-9]*;

        number { return true; }
        *      { return false; }
    */
}

fn main() {
    assert!(lex(b"1234\0"));
}
