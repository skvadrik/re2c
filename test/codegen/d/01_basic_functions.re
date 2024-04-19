// re2d $INPUT -o $OUTPUT -d
module main;

import core.stdc.stdio;

private bool lex(const char *s) {
    size_t cursor;
    auto YYPEEK = delegate char() { return s[cursor]; };
    auto YYSKIP = delegate void() { ++cursor; };
    auto YYDEBUG = delegate void() { debug{printf("lex2: char '%c'\n", s[cursor]);} };
    /*!re2c
        re2c:api:style = functions;
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable = 0;

        number = [1-9][0-9]*;
        number { return true; }
        *      { return false; }
    */
}

void main() {
    assert(lex("1234"));
}
