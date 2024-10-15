// re2c $INPUT -o $OUTPUT -i --header lexer/state.h
#include <assert.h>
#include <stddef.h>
#include "lexer/state.h" // the header is generated by re2c

/*!header:re2c:on*/
struct LexerState {
    const char *str, *yycursor;
    /*!stags:re2c format = "const char *@@;"; */
};
/*!header:re2c:off*/

long lex(LexerState* yyrecord) {
    const char *t;
    /*!re2c
        re2c:header = "lexer/state.h";
        re2c:api = record;
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = char;
        re2c:tags = 1;

        [a]* @t [b]* { return t - yyrecord->str; }
    */
}

int main() {
    const char *s = "ab";
    LexerState st = { s, s /*!stags:re2c format = ", NULL"; */ };
    assert(lex(&st) == 1);
    return 0;
}
