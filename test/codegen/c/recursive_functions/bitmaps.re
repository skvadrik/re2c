// re2c $INPUT -o $OUTPUT --recursive-functions -b

#include <assert.h>

/*!re2c
    re2c:define:YYCTYPE = char;
    re2c:define:YYFN    = ["lex;int", "YYCURSOR;const char*"];
    re2c:yyfill:enable  = 0;

    number = [1-9][0-9]*;
    word   = [a-z]+;

    number { return 0; }
    word   { return 1; }
    *      { return 2; }
*/

int main() {
    assert(lex("42") == 0);
    assert(lex("qwerty") == 1);
    assert(lex("??") == 2);
}
