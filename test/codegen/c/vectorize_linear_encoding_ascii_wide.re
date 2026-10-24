// re2c $INPUT -o $OUTPUT -i --vectorize-linear
// Even in ASCII mode YYCTYPE may be wider than one byte.
#include <stdint.h>
#include <stdio.h>

typedef uint16_t code_unit;

/*!rules:re2c:literal
    "abcdefgh" { *end = YYCURSOR; return 1; }
    *          { *end = YYCURSOR; return 0; }
*/

static int lex(const code_unit *YYCURSOR, const code_unit *YYLIMIT, const code_unit **end) {
    const code_unit *YYMARKER;
    (void)YYLIMIT;
    /*!use:re2c:literal
        re2c:YYCTYPE = code_unit;
        re2c:YYLIMIT = YYLIMIT;
        re2c:yyfill:enable = 0;
    */
}

static int lex_fill(const code_unit *YYCURSOR, const code_unit *YYLIMIT, const code_unit **end) {
    const code_unit *YYMARKER;
    /*!use:re2c:literal
        re2c:YYCTYPE = code_unit;
        re2c:yyfill:enable = 1;
        re2c:YYFILL = "return -1";
        re2c:yyfill:parameter = 0;
    */
}

typedef struct { const code_unit *yycursor, *yymarker, *yylimit; } Record;

static int lex_record(const code_unit *input, const code_unit *limit, const code_unit **end) {
    Record state = {input, input, limit}, *yyrecord = &state;
    /*!re2c
        re2c:api = record;
        re2c:YYCTYPE = code_unit;
        re2c:YYLIMIT = "yyrecord->yylimit";
        re2c:yyfill:enable = 0;
        "abcdefgh" { *end = yyrecord->yycursor; return 1; }
        *          { *end = yyrecord->yycursor; return 0; }
    */
}

static int lex_record_fill(const code_unit *input, const code_unit *limit, const code_unit **end) {
    Record state = {input, input, limit}, *yyrecord = &state;
    /*!re2c
        re2c:api = record;
        re2c:YYCTYPE = code_unit;
        re2c:yyfill:enable = 1;
        re2c:YYFILL = "return -1;";
        re2c:yyfill:parameter = 0;
        "abcdefgh" { *end = yyrecord->yycursor; return 1; }
        *          { *end = yyrecord->yycursor; return 0; }
    */
}

int main(void) {
    typedef int (*lexer)(const code_unit*, const code_unit*, const code_unit**);
    const lexer lexers[] = {lex, lex_fill, lex_record, lex_record_fill};
    for (unsigned int i = 0; i < sizeof(lexers) / sizeof(lexers[0]); ++i) {
        for (int pos = -1; pos < 8; ++pos) {
            code_unit input[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 0};
            if (pos >= 0) input[pos] |= 0x100;
            const code_unit *end = NULL;
            const int rule = lexers[i](input, input + 8, &end);
            const int want_rule = pos < 0 ? 1 : 0;
            const int want_length = pos < 0 ? 8 : 1;
            if (rule != want_rule || end - input != want_length) {
                fprintf(stderr, "lexer %u, position %d: rule %d, length %ld; expected %d, %d\n",
                    i, pos, rule, (long)(end - input), want_rule, want_length);
                return 1;
            }
        }
    }
    return 0;
}
