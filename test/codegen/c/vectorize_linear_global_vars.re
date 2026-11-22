// re2c $INPUT -o $OUTPUT -i --vectorize-linear --syntax vectorize_linear_global_vars.inc
// Global syntax file variables (nl, indent, dedent, topindent) are allowed in any code template,
// including atomic wide-peek expression templates (code:yypeek2, code:yypeek4, code:yypeek8).
#include <assert.h>
#include <string.h>

static int lex(const char *YYCURSOR, const char *YYLIMIT) {
    const char *YYMARKER;
    (void)YYLIMIT;
    (void)YYMARKER;
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:YYLIMIT = YYLIMIT;
        re2c:define:YYCTYPE = char;

        "abcdefghij" { return 3; }
        "abcdefgh"   { return 1; }
        "ab"         { return 2; }
        "0123456789" { return 4; }
        *            { return 0; }
    */
}

static int run_lex(const char *s) {
    return lex(s, s + strlen(s));
}

int main(void) {
    assert(run_lex("abcdefghij") == 3);
    assert(run_lex("abcdefgh") == 1);
    assert(run_lex("ab") == 2);
    assert(run_lex("0123456789") == 4);
    assert(run_lex("012345678x") == 0);
    assert(run_lex("xyz") == 0);
    return 0;
}
