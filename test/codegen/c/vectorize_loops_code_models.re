// re2c $INPUT -o $OUTPUT -i --loop-switch --eager-skip -f --arch x86 --vectorize-loops
#include <assert.h>
#include <immintrin.h>
#include <stddef.h>
#include <string.h>

typedef struct {
    const char *yycursor;
    const char *yylimit;
    const char *yymarker;
    unsigned char yych;
    int yystate;
} LexState;

static int lex_storable(LexState *st) {
    /*!re2c
        re2c:api = record;
        re2c:yyrecord = st;
        re2c:YYCTYPE = "unsigned char";
        re2c:yych = "st->yych";
        re2c:YYFILL = "return -2;";
        re2c:YYFILL:naked = 1;

        [a-zA-Z_][a-zA-Z0-9_]* ";" { return 1; }
        *                          { return -1; }
    */
}

int main(void) {
    char buf[256];
    memset(buf, 'x', 80);
    buf[80] = ';';
    memset(buf + 81, 0, sizeof(buf) - 81);

    LexState st;
    st.yycursor = buf;
    st.yylimit = buf + 40;
    st.yymarker = buf;
    st.yych = 0;
    st.yystate = -1;

    assert(lex_storable(&st) == -2);
    st.yylimit = buf + sizeof(buf);
    assert(lex_storable(&st) == 1);
    assert(st.yycursor - buf == 81);
    return 0;
}
