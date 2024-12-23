// re2c $INPUT -o $OUTPUT -i
#include <assert.h>

int lex(const char *s) {
    const char *YYCURSOR = s, *YYMARKER;
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = char;

        "\a\b\f\n\r\t\v\\'\"" { return 0; }
        * { return 1; }
    */
}

int main() {
    assert(lex("\x07\x08\x0c\x0a\x0d\x09\x0b\\'\"") == 0);
    return 0;
}
