// re2c $INPUT -o $OUTPUT -i --vectorize-linear -Wno-vectorize-linear-disabled
// A sentinel-only lexer has no limit variable or record field. Vectorization must fall back.
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static int simple(const char *YYCURSOR) {
    const char *YYMARKER;
    /*!re2c
        re2c:YYCTYPE = char;
        re2c:yyfill:enable = 0;
        "abcdefgh" { return 1; }
        *          { return 0; }
    */
}

static int record(const char *input) {
    struct { const char *yycursor, *yymarker; } state = {input, input}, *yyrecord = &state;
    /*!re2c
        re2c:api = record;
        re2c:YYCTYPE = char;
        re2c:yyfill:enable = 0;
        "abcdefgh" { return 1; }
        *          { return 0; }
    */
}

int main(void) {
    for (size_t n = 0; n <= 8; ++n) {
        char *input = (char*)malloc(n + 1);
        assert(input);
        memcpy(input, "abcdefgh", n);
        input[n] = 0;
        assert(simple(input) == (n == 8));
        assert(record(input) == (n == 8));
        free(input);
    }
    return 0;
}
