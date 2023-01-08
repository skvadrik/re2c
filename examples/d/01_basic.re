// re2d $INPUT -o $OUTPUT -i --case-ranges
module basic01;
bool lex(const char *s) {
    size_t cursor;
    /*!re2c
        re2c:define:YYCTYPE = char;
		re2c:define:YYPEEK = "s[cursor]";
		re2c:define:YYSKIP = "cursor ++;";
		re2c:yyfill:enable = 0;

        number = [1-9][0-9]*;

        number { return true; }
        *      { return false; }
    */
}

unittest{
    assert(lex("1234"));
}

extern(C) void main()
{
    static foreach(u; __traits(getUnitTests, __traits(parent, main)))
        u();
}
