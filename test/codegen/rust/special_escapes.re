// re2rust $INPUT -o $OUTPUT --no-unsafe --api simple

fn lex(yyinput: &[u8]) -> bool {
    let mut yycursor = 0;
    let mut yymarker = 0;
    /*!re2c
        re2c:YYCTYPE = u8;
        re2c:yyfill:enable = 0;

        "\a\b\f\n\r\t\v\\'\"" { return true; }
        * {
            let _ = ['\n', '\r', '\t', '\\', '\'', '\"'];
            return false;
        }
    */
}

fn main() {
    assert!(lex(b"\x07\x08\x0c\x0a\x0d\x09\x0b\\'\"\0"));
}
