// re2d $INPUT -o $OUTPUT -d
module main;

import core.stdc.stdio;

bool lex(const char *s) {
    size_t cursor;
    /*!re2c
        re2c:api = custom;
        re2c:define:YYCTYPE = char;
        re2c:define:YYPEEK = "s[cursor]";
        re2c:define:YYSKIP = "++cursor;";
        re2c:define:YYDEBUG =
            "debug{printf(\"lex1: char '%c' at state %u\\n\", @@{char}, @@{state});}";
        re2c:yyfill:enable = 0;

        number = [1-9][0-9]*;
        number { return true; }
        *      { return false; }
    */
}

void main() {
    assert(lex("1234"));
}
