// re2d $INPUT -o $OUTPUT -i
module main;

private bool lex(const(char)* yycursor) {
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        number = [1-9][0-9]*;
        number { return true; }
        *      { return false; }
    */
}

void main() {
    assert(lex("1234"));
}
