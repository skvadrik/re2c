// re2c $INPUT -o $OUTPUT -i
#include <assert.h>
#include <string.h>

/*!max:re2c*/

/*!rules:re2c:x
    re2c:YYCTYPE = char;
    re2c:api:style = free-form;

    $           { return 0; }
    *           { return 1; }
    [a] $       { return 2; }
    [a]         { return 3; }
    [b] $ | [b] { return 4; }
    [c]+ $      { return 5; }
*/

static int lex_simple(const char *str, unsigned int len) {
    const char *YYCURSOR = str, *YYLIMIT = str + len, *YYMARKER;
    /*!use:re2c:x
        re2c:yyfill:enable = 0;
    */
}

static int lex_eof(const char *str, unsigned int len) {
    const char *YYCURSOR = str, *YYLIMIT = str + len, *YYMARKER;
    /*!use:re2c:x
        re2c:eof = 0;
        re2c:YYFILL = "0"; // always fails
        re2c:YYEND = "YYCURSOR == YYLIMIT";
    */
}

static int lex_scc(const char *str, unsigned int len) {
    static char buf[256];
    char *end = buf + len, *YYCURSOR = buf, *YYLIMIT = end + YYMAXFILL, *YYMARKER;
    memcpy(buf, str, len);
    memset(end, 0, YYMAXFILL);
    /*!use:re2c:x
        re2c:YYFILL = "return -1;"; // always fails
        re2c:YYEND = "YYCURSOR == end";
    */
}

#define TEST(s, r) do { \
    assert(lex_simple(s, sizeof(s) - 1) == r); \
    assert(lex_eof(s, sizeof(s) - 1) == r); \
    assert(lex_scc(s, sizeof(s) - 1) == r); \
} while (0)

int main() {
    TEST("", 0);
    TEST("a", 2);
    TEST("ax", 3);
    TEST("b", 4);
    TEST("bx", 4);
    TEST("ccc", 5);
    return 0;
}
