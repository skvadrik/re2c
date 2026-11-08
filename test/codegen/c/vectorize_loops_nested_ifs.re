// re2c $INPUT -o $OUTPUT -i --arch x86 --vectorize-loops --nested-ifs
// The vector block must be emitted only once for the reflexive loop transition,
// even though nested IFs would otherwise duplicate it on each matching branch.
#include <immintrin.h>
#include <stddef.h>

static int lex(const unsigned char *input, size_t len) {
    const unsigned char *yycursor = input;
    const unsigned char *yylimit = input + len;
/*!re2c
        re2c:YYCTYPE = "unsigned char";
        re2c:YYCURSOR = yycursor;
        re2c:YYLIMIT = yylimit;
        re2c:YYFILL = "return -2;";
        re2c:YYFILL:naked = 1;
        [a-z]+ { return *yycursor == ';' ? 0 : 1; }
        *      { return 2; }
*/
}

int main(void) {
    static const unsigned char input[] =
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa;";
    return lex(input, sizeof(input) - 1);
}
