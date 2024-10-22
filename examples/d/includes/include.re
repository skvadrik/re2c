// re2d $INPUT -o $OUTPUT -i

/*!include:re2c "definitions.d" */

private Result lex(const(char)* s) {
    const(char)* yycursor = s, yymarker;
    /*!re2c
        re2c:YYCTYPE = "char";
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
