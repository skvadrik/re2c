// re2c $INPUT -o $OUTPUT -i
#include <assert.h>
#include <stddef.h>

/*!re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE = char;
*/

/*!rules:re2c:r1
    re2c:tags = 1;
    ([b] @x [a] @y)? { return x == NULL ? -1 : (y - x); }
*/

static int lex_tags_generic(const char *str) {
    const char *s = str, *m, *x, *y;
    /*!stags:re2c:b1 format = 'const char *@@;\n'; */
    /*!local:re2c:b1
        re2c:api = custom;
        re2c:api:style = free-form;
        re2c:define:YYPEEK = "*s";
        re2c:define:YYSKIP = "++s;";
        re2c:define:YYBACKUP = "m = s;";
        re2c:define:YYRESTORE = "s = m;";
        re2c:define:YYSTAGP = "@@ = s;";
        re2c:define:YYSTAGN = "@@ = NULL;";
        re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift};";
        !use:r1;
    */
    return -2;
}

static int lex_tags_default(const char *str) {
    const char *YYCURSOR = str, *YYMARKER, *x, *y;
    /*!stags:re2c:b2 format = 'const char *@@;\n'; */
    /*!local:re2c:b2
        re2c:api = default;
        !use:r1;
    */
}

/*!rules:re2c:r2
    re2c:posix-captures = 1;
    (([a]))? {
        assert(yynmatch == 3);
        return yypmatch[4] == NULL ? -1 : yypmatch[4] - str;
    }
*/

/*!maxnmatch:re2c*/

static int lex_captures_generic(const char *str) {
    const char *s = str;
    /*!stags:re2c:b3 format = 'const char *@@;\n'; */
    size_t yynmatch;
    const char* yypmatch[2*YYMAXNMATCH];
    /*!local:re2c:b3
        re2c:api = custom;
        re2c:api:style = free-form;
        re2c:define:YYPEEK = "*s";
        re2c:define:YYSKIP = "++s;";
        re2c:define:YYSTAGP = "@@ = s;";
        re2c:define:YYSTAGN = "@@ = NULL;";
        re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift};";
        !use:r2;
    */
}

static int lex_captures_default(const char *str) {
    const char *YYCURSOR = str;
    /*!stags:re2c:b4 format = 'const char *@@;\n'; */
    size_t yynmatch;
    const char* yypmatch[2*YYMAXNMATCH];
    /*!local:re2c:b4
        re2c:api = default;
        !use:r2;
    */
}

int main() {
    assert(lex_tags_generic("") == -1);
    assert(lex_tags_generic("ba") == 1);
    assert(lex_tags_default("") == -1);
    assert(lex_tags_default("ba") == 1);
    assert(lex_captures_generic("") == -1);
    assert(lex_captures_generic("a") == 0);
    assert(lex_captures_default("") == -1);
    assert(lex_captures_default("a") == 0);
    return 0;
}
