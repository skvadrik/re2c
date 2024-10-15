// re2rust $INPUT -o $OUTPUT

fn lex(yyinput: &[u8]) -> bool {
    let mut yycursor = 0;
    /*!re2c
        re2c:api = simple;
        re2c:define:YYCTYPE = i8;
        re2c:yyfill:enable = 0;
        re2c:yych:conversion = 1;

        number = [1-9][0-9]*;

        number { return true; }
        *      { return false; }
    */
}

fn main() {
    assert!(lex(b"1234\0"));
}
