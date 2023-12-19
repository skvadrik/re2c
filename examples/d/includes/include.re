// re2d $INPUT -o $OUTPUT -i

/*!include:re2c "definitions.d" */

private Result lex(const(char)* s) {
    const(char)* cur = s, mar;
    /*!re2c
        re2c:define:YYCTYPE   = "char";
        re2c:define:YYPEEK    = "*cur";
        re2c:define:YYSKIP    = "++cur;";
        re2c:define:YYBACKUP  = "mar = cur;";
        re2c:define:YYRESTORE = "cur = mar;";
        re2c:yyfill:enable = 0;

        *      { return Result.FAIL; }
        number { return Result.OK; }
        !include "extra_rules.re.inc";
    */
}

void main() {
    assert(lex("123") == Result.OK);
    assert(lex("123.4567") == Result.OK);
}
