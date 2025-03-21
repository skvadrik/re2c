// re2c $INPUT -o $OUTPUT --case-ranges --recursive-functions -i

#include <assert.h>

/*!re2c
    re2c:define:YYCTYPE = char;
    re2c:define:YYFN    = ["lex;int;__attribute__((noinline))", "YYCURSOR;const char*"];
    re2c:yyfill:enable  = 0;

    alpha = [a-zA-Z];
    ident = alpha (alpha | [0-9])*;

    ident { return 0; }
    *     { return 1; }
*/

int main() {
    assert(lex("qwerty42") == 0);
    assert(lex("??") == 1);
}
