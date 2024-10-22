// re2d $INPUT -o $OUTPUT
module main;

// Expect a null-terminated string.
private int lex(immutable char[] s) {
    const(char)* yycursor = s.ptr, yylimit = s.ptr + s.length, yymarker;
    int count = 0;

    for (;;) {
    /*!re2c
        re2c:YYCTYPE = char;
        re2c:yyfill:enable = 0;
        re2c:eof = 0;

        str = ['] ([^'\\] | [\\][^])* ['];

        *    { return -1; }
        $    { return count; }
        str  { ++count; continue; }
        [ ]+ { continue; }
    */
    }
    assert(0); // unreachable
}

void main() {
    assert(lex("") == 0);
    assert(lex("'qu\0tes' 'are' 'fine: \\'' ") == 3);
    assert(lex("'unterminated\\'") == -1);
}
