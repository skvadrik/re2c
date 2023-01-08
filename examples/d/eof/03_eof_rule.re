// re2c $INPUT -o $OUTPUT
module eof_rule03;

// Expect a null-terminated string.
int lex(in string str, ulong len) {
    const(char) *YYCURSOR = str.ptr, YYLIMIT = str.ptr + len, YYMARKER;
    int count = 0;

    for (;;) {
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:define:YYPEEK = '*YYCURSOR';
        re2c:define:YYSKIP = 'YYCURSOR++;';
        re2c:define:YYRESTORE = 'YYCURSOR = YYMARKER;';
        re2c:define:YYBACKUP = 'YYMARKER = YYCURSOR;';
        re2c:define:YYLESSTHAN = 'YYLIMIT <= YYCURSOR';
        re2c:yyfill:enable = 0;
        re2c:eof = 0;

        str = ['] ([^'\\] | [\\][^])* ['];

        *    { return -1; }
        $    { return count; }
        str  { ++count; continue; }
        [ ]+ { continue; }
    */
    }
    assert(0);
}

void TEST(immutable char[] s, int r){
    assert(lex(s,s.length)==r);
}

unittest{
    TEST("", 0);
    TEST("'qu\0tes' 'are' 'fine: \\'' ", 3);
    TEST("'unterminated\\'", -1);
}

extern(C) void main()
{
    static foreach(u; __traits(getUnitTests, __traits(parent, main)))
        u();
}
