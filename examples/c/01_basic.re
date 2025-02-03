// re2c $INPUT -o $OUTPUT -i --case-ranges
#include <assert.h>

int lex(const char *s) {
    const char *YYCURSOR = s;
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = char;

        [1-9][0-9]* { return 0; }
        *           { return 1; }
    */
}

int main() {
    assert(lex("1234") == 0);
    return 0;
}
