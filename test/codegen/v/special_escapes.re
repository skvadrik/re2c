// re2v $INPUT -o $OUTPUT -i

fn lex(yyinput string) {
    mut yycursor := 0
    mut yymarker := 0
    /*!re2c
        re2c:yyfill:enable = 0;

        "\a\b\f\n\r\t\v\\'\"" { return }
        * {
            _ := ['\a', '\b', '\f', '\n', '\r', '\t', '\v', '\\', '\'', '\"']
            panic("error!")
        }
    */
}

fn main() {
    lex("\x07\x08\x0c\x0a\x0d\x09\x0b\\'\"\x00")
}
