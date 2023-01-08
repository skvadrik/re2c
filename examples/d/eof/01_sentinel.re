// re2d $INPUT -o $OUTPUT
module sentinel01;


// Expect a null-terminated string.
static int lex(const(char) *YYCURSOR) {
    int count = 0;

    for (;;) {
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:define:YYPEEK = '*YYCURSOR';
        re2c:define:YYSKIP = 'YYCURSOR++;';
        re2c:yyfill:enable = 0;

        *      { return -1; }
        [\x00] { return count; }
        [a-z]+ { ++count; continue; }
        [ ]+   { continue; }
    */
    }
    assert(0);
}


unittest{
    assert(lex("") == 0);
    assert(lex("one two three") == 3);
    assert(lex("f0ur") == -1);
}

extern(C) void main()
{
    static foreach(u; __traits(getUnitTests, __traits(parent, main)))
        u();
}

