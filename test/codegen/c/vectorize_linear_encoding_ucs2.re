// re2c $INPUT -o $OUTPUT -i -w --vectorize-linear -Wno-vectorize-linear-disabled
// Even sizeof(*YYCURSOR) == 1 cannot make a wide target encoding byte-safe.
// Packing U+6362 overlaps the following 'c', falsely matching the bytes "bc".
#include <stdint.h>
#include <stdio.h>

typedef unsigned char code_unit;

static int lex(const code_unit *YYCURSOR, const code_unit *YYLIMIT, const code_unit **end) {
    const code_unit *YYMARKER;
    (void)YYLIMIT;
    /*!re2c
        re2c:YYCTYPE = code_unit;
        re2c:YYLIMIT = YYLIMIT;
        re2c:yyfill:enable = 0;
        "a\u6362cdefgh" { *end = YYCURSOR; return 1; }
        *          { *end = YYCURSOR; return 0; }
    */
}

int main(void) {
    for (int pos = -1; pos < 8; ++pos) {
        code_unit input[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 0};
        if (pos >= 0) input[pos] ^= 1;
        const code_unit *end = NULL;
        const int rule = lex(input, input + 8, &end);
        const int want_rule = 0;
        const int want_length = 1;
        if (rule != want_rule || end - input != want_length) {
            fprintf(stderr, "position %d: rule %d, length %ld; expected %d, %d\n",
                pos, rule, (long)(end - input), want_rule, want_length);
            return 1;
        }
    }
    return 0;
}
