// re2d $INPUT -o $OUTPUT
module main;

bool lex(const(char)* yycursor) {
    /*!re2c
        re2c:define:YYCTYPE = byte; // signed 8-bit
        re2c:yych:conversion = 1;
        re2c:yyfill:enable = 0;

        number = [1-9][0-9]*;
        number { return true; }
        *      { return false; }
    */
}

void main() {
    assert(lex("1234"));
}
