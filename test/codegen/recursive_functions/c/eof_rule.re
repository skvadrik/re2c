// re2c $INPUT -o $OUTPUT --recursive-functions -i
#include <assert.h>

struct State {
    const char* cur;
    const char* mar;
    const char* lim;
    int count;
};

/*!re2c
    re2c:define:YYCTYPE  = char;
    re2c:define:YYFN     = ["lex", "int", "st", "State&"];
    re2c:define:YYCURSOR = "st.cur";
    re2c:define:YYMARKER = "st.mar";
    re2c:define:YYLIMIT  = "st.lim";
    re2c:yyfill:enable = 0;
    re2c:eof = 0;

    *                           { return -1; }
    $                           { return st.count; }
    ['] ([^'\\] | [\\][^])* ['] { ++st.count; return lex(st); }
    [ ]+                        { return lex(st); }
*/

#define TEST(s, r) do { \
    State st{s, s, s + sizeof(s) - 1, 0}; \
    assert(lex(st) == r); \
} while(0)

int main() {
    TEST("", 0);
    TEST("'qu\0tes' 'are' 'fine: \\'' ", 3);
    TEST("'unterminated\\'", -1);
    return 0;
}
