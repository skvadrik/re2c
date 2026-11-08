// re2c $INPUT -o $OUTPUT -i --arch x86 --vectorize-loops --nested-ifs --bit-vectors
// Each of the two reflexive loops must own exactly one vector block. In
// particular, non-adjacent letter ranges must not duplicate the first block
// when bitmap dispatch is combined with nested IFs.
#include <immintrin.h>
#include <stddef.h>

static int lex(const unsigned char *input, size_t len) {
    const unsigned char *yycursor = input;
    const unsigned char *yylimit = input + len;
    const unsigned char *yymarker = input;
/*!re2c
        re2c:YYCTYPE = "unsigned char";
        re2c:YYCURSOR = yycursor;
        re2c:YYLIMIT = yylimit;
        re2c:YYMARKER = yymarker;
        re2c:YYFILL = "return -2;";
        re2c:YYFILL:naked = 1;
        [a-zA-Z]+[0-9]+ { return *yycursor == ';' ? 0 : 1; }
        *               { return 2; }
*/
}

int main(void) {
    static const unsigned char input[] =
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "1111111111111111111111111111111111111111;";
    return lex(input, sizeof(input) - 1);
}
