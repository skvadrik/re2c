// re2c $INPUT -o $OUTPUT -i --vectorize-linear -Werror
#include <assert.h>
#include <string.h>

// EOF in a definitions-only block must not trigger a disabled-vectorization warning.
/*!re2c
    re2c:eof = 0;
    word = [a-z]+;
*/

static int lex(const char *s, int *cursor) {
    const char *YYCURSOR = s, *YYMARKER, *YYLIMIT = s + strlen(s);
    int rule;
    (void)YYLIMIT;
    /*!re2c
        re2c:eof = -1;
        re2c:yyfill:enable = 0;
        re2c:YYCTYPE = char;
        re2c:YYLIMIT = YYLIMIT;
        "content-length" { rule = 2; goto done; }
        word             { rule = 1; goto done; }
        *                { rule = 0; goto done; }
    */
done:
    *cursor = (int)(YYCURSOR - s);
    return rule;
}

int main(void) {
    int cursor;
    assert(lex("content-length", &cursor) == 2 && cursor == 14);
    assert(lex("abc", &cursor) == 1 && cursor == 3);
    assert(lex("!", &cursor) == 0 && cursor == 1);
    return 0;
}
