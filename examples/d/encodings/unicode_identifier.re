// re2d $INPUT -o $OUTPUT -8 -i
module main;

/*!include:re2c "unicode_categories.re" */

private int lex(const(char)* s) {
    const(char)* cur = s, mar;
    /*!re2c
        re2c:define:YYCTYPE   = "char";
        re2c:define:YYPEEK    = "*cur";
        re2c:define:YYSKIP    = "++cur;";
        re2c:define:YYBACKUP  = "mar = cur;";
        re2c:define:YYRESTORE = "cur = mar;";
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

void main() {
    assert(lex("_Ыдентификатор") == 0);
    assert(lex("!!!")==1);
}
