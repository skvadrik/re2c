// re2c $INPUT -o $OUTPUT -i --vectorize-loops
#include <assert.h>
#include <immintrin.h>
#include <string.h>

static int fill(int need) { (void)need; return 0; }

static int lex_vector(const unsigned char *input, size_t limit)
{
    const unsigned char *YYCURSOR = input;
    const unsigned char *YYLIMIT = input + limit;
    const unsigned char *YYMARKER = input;
    /*!re2c
    re2c:vectorize:loops = 1;
    re2c:define:YYCTYPE = "unsigned char";
    re2c:YYFILL = "fill(0);";
    re2c:YYFILL:naked = 1;

    [0-9]+                 { return 1; }
    [a-zA-Z_][a-zA-Z0-9_]* { return 2; }
    [ \t]+                 { return 3; }
    "\x00"                 { return 0; }
    *                      { return -1; }
    */
}

static int lex_scalar(const unsigned char *input, size_t limit)
{
    const unsigned char *YYCURSOR = input;
    const unsigned char *YYLIMIT = input + limit;
    const unsigned char *YYMARKER = input;
    /*!re2c
    re2c:vectorize:loops = 0;
    re2c:define:YYCTYPE = "unsigned char";
    re2c:YYFILL = "fill(0);";
    re2c:YYFILL:naked = 1;

    [0-9]+                 { return 1; }
    [a-zA-Z_][a-zA-Z0-9_]* { return 2; }
    [ \t]+                 { return 3; }
    "\x00"                 { return 0; }
    *                      { return -1; }
    */
}

int main(void)
{
    unsigned char buf[256];
    memset(buf, 'A', sizeof(buf));

    for (size_t n = 1; n < 120; ++n) {
        buf[n] = 0;
        int res_v = lex_vector(buf, n + 1);
        int res_s = lex_scalar(buf, n + 1);
        assert(res_v == res_s);
        assert(res_v == 2);
        buf[n] = 'A';
    }

    memset(buf, '5', sizeof(buf));
    for (size_t n = 1; n < 120; ++n) {
        buf[n] = 0;
        int res_v = lex_vector(buf, n + 1);
        int res_s = lex_scalar(buf, n + 1);
        assert(res_v == res_s);
        assert(res_v == 1);
        buf[n] = '5';
    }

    memset(buf, ' ', sizeof(buf));
    for (size_t n = 1; n < 120; ++n) {
        buf[n] = 0;
        int res_v = lex_vector(buf, n + 1);
        int res_s = lex_scalar(buf, n + 1);
        assert(res_v == res_s);
        assert(res_v == 3);
        buf[n] = ' ';
    }

    return 0;
}
