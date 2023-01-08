// re2d $INPUT -o $OUTPUT -8 --case-ranges -i

/*!include:re2c "unicode_categories.re" */

int lex(const char *s) {
    size_t cursor, backup, marker;
    /*!re2c
        re2c:define:YYCTYPE = char;
		re2c:define:YYPEEK = "s[cursor]";
		re2c:define:YYSKIP = "cursor ++;";
        re2c:define:YYBACKUP = "backup=cursor;";
        re2c:define:YYRESTORE = 'cursor=backup;';
        re2c:define:YYMARKER = 'marker';
        re2c:yyfill:enable = 0;

        // Simplified "Unicode Identifier and Pattern Syntax"
        // (see https://unicode.org/reports/tr31)
        id_start    = L | Nl | [$_];
        id_continue = id_start | Mn | Mc | Nd | Pc | [\u200D\u05F3];
        identifier  = id_start id_continue*;

        identifier { return 0; }
        *          { return 1; }
    */
}



unittest{
    assert(lex("_Ыдентификатор") == 0);
    assert(lex("!!!")==1);
}

extern(C) void main()
{
    static foreach(u; __traits(getUnitTests, __traits(parent, main)))
        u();
}
