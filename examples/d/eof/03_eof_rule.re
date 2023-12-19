// re2d $INPUT -o $OUTPUT
module main;

// Expect a null-terminated string.
private int lex(immutable char[] s) {
    const(char)* cur = s.ptr, lim = s.ptr + s.length, mar;
    int count = 0;

    for (;;) {
    /*!re2c
        re2c:define:YYCTYPE    = char;
        re2c:define:YYPEEK     = '*cur';
        re2c:define:YYSKIP     = '++cur;';
        re2c:define:YYRESTORE  = 'cur = mar;';
        re2c:define:YYBACKUP   = 'mar = cur;';
        re2c:define:YYLESSTHAN = 'lim <= cur';
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
