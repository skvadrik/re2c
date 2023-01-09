// re2c $INPUT -o $OUTPUT -i

/*!include:re2c "definitions.d" */

Result lex(const(char) *s) {
    const(char) *YYCURSOR = s, YYMARKER;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;
        re2c:define:YYSKIP = 'YYCURSOR++;';
        re2c:define:YYBACKUP = 'YYMARKER = YYCURSOR;';
        re2c:define:YYRESTORE = 'YYCURSOR = YYMARKER;';
        re2c:define:YYPEEK = '*YYCURSOR';

        *      { return Result.FAIL; }
        number { return Result.OK; }
        !include "extra_rules.re.inc";
    */
}

unittest{
    assert(lex("123") == Result.OK);
    assert(lex("123.4567") == Result.OK);
}

extern(C) void main()
{
    static foreach(u; __traits(getUnitTests, __traits(parent, main)))
        u();
}
