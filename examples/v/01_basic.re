// re2v $INPUT -o $OUTPUT -i

fn lex(yyinput string) {
    mut yycursor := 0
    /*!re2c
        re2c:yyfill:enable = 0;

        number = [1-9][0-9]*;

        number { return }
        *      { panic("error!") }
    */
}

fn main() {
    lex("1234\x00")
}
