// re2c $INPUT -o $OUTPUT -i --type-header src/lexer/lexer.h
#include <assert.h>
#include "src/lexer/lexer.h" // generated by re2c

/*!header:re2c:on*/

typedef struct {
    const char *str, *cur, *mar;
    /*!stags:re2c format = "const char *@@{tag}; "; */
} LexerState;

/*!header:re2c:off*/

int lex(LexerState *st)
{
    /*!re2c
    re2c:flags:type-header = "src/lexer/lexer.h";
    re2c:yyfill:enable = 0;
    re2c:flags:tags = 1;
    re2c:define:YYCTYPE  = char;
    re2c:define:YYCURSOR = "st->cur";
    re2c:define:YYMARKER = "st->mar";
    re2c:tags:expression = "st->@@{tag}";

    [x]{1,4} / [x]{3,5} { return 0; } // ambiguous trailing context
    *                   { return 1; }
    */
}

int main()
{
    LexerState st;
    st.str = st.cur = "xxxxxxxx";
    assert(lex(&st) == 0 && st.cur - st.str == 4);
    return 0;
}