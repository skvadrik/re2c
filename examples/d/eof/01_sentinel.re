// re2d $INPUT -o $OUTPUT
module main;

// Expect a null-terminated string.
private int lex(const(char)* yycursor) {
    uint count = 0;

    for (;;) {
    /*!re2c
        re2c:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        *      { return -1; }
        [\x00] { return count; }
        [a-z]+ { ++count; continue; }
        [ ]+   { continue; }
    */
    }
    assert(0); // unreachable
}

void main() {
    assert(lex("") == 0);
    assert(lex("one two three") == 3);
    assert(lex("f0ur") == -1);
}
