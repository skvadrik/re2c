// re2v $INPUT -o $OUTPUT -s

fn lex(str string) {
    mut cursor := 0
    /*!re2c
        re2c:define:YYCTYPE = u8;
        re2c:define:YYPEEK = "str[cursor]";
        re2c:define:YYSKIP = "cursor += 1";
        re2c:yyfill:enable = 0;

        number = [1-9][0-9]*;

        number { return }
        *      { panic("error!") }
    */
}

fn main() {
    lex("1234\x00")
}
