// re2c $INPUT -o $OUTPUT --recursive-functions -i
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/*!max:re2c*/

struct State {
    const char* cur;
    const char* lim;
    int count;
};

/*!re2c
    re2c:api:style = free-form;
    re2c:define:YYCTYPE  = char;
    re2c:define:YYFN     = ["lex;int", "st;State&"];
    re2c:define:YYCURSOR = "st.cur";
    re2c:define:YYLIMIT  = "st.lim";
    re2c:define:YYFILL   = "return -1;";

    *                           { return -1; }
    [\x00]                      { return st.cur + YYMAXFILL - 1 == st.lim ? st.count : -1; }
    ['] ([^'\\] | [\\][^])* ['] { ++st.count; return lex(st); }
    [ ]+                        { return lex(st); }
*/

// make a copy of the string with YYMAXFILL zeroes at the end
static void test(const char *str, unsigned int len, int res) {
    char *s = (char*) malloc(len + YYMAXFILL);
    memcpy(s, str, len);
    memset(s + len, 0, YYMAXFILL);
    State st{s, s + len + YYMAXFILL, 0};
    int r = lex(st);
    free(s);
    assert(r == res);
}

#define TEST(s, r) test(s, sizeof(s) - 1, r)
int main() {
    TEST("", 0);
    TEST("'qu\0tes' 'are' 'fine: \\'' ", 3);
    TEST("'unterminated\\'", -1);
    return 0;
}
