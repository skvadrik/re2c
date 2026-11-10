// re2c $INPUT -o $OUTPUT -i -x --vectorize-linear -Wno-vectorize-linear-disabled
// Wide target encodings disable linear vectorization.
#include <stdint.h>
#include <stdio.h>

typedef uint16_t code_unit;

static int lex(const code_unit *YYCURSOR, const code_unit *YYLIMIT, const code_unit **end) {
    const code_unit *YYMARKER;
    (void)YYMARKER;
    (void)YYLIMIT;
    /*!re2c
        re2c:YYCTYPE = code_unit;
        re2c:YYLIMIT = YYLIMIT;
        re2c:yyfill:enable = 0;
        "abcdefgh" { *end = YYCURSOR; return 1; }
        *          { *end = YYCURSOR; return 0; }
    */
}

int main(void) {
    for (int pos = -1; pos < 7; ++pos) {
        code_unit input[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 0};
        if (pos >= 0) {
            // The high byte overlaps the next character in a packed OR comparison.
            input[pos] |= (code_unit)(input[pos + 1] << 8);
        }
        const int want_rule = pos < 0 ? 1 : 0;
        const int want_length = pos < 0 ? 8 : 1;
        const code_unit *end = NULL;
        const int rule = lex(input, input + 8, &end);
        if (rule != want_rule || end - input != want_length) {
            fprintf(stderr, "position %d: rule %d, length %ld; expected %d, %d\n",
                pos, rule, (long)(end - input), want_rule, want_length);
            return 1;
        }
    }
    return 0;
}
