// re2c $INPUT -o $OUTPUT -i --vectorize-loops -Wno-unreachable-rules
// The loop class contains all code units, so its complement (the `xrange` list)
// is empty and the vector loop has no exit comparisons: it skips whole vectors
// while the length guard holds, and the scalar code handles the rest.
// The loop only ends at the end of input (YYFILL returns 1), so the action of
// the rule is unreachable; the test compares the final cursor positions.
#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>

/*!rules:re2c:common
    re2c:api:style = free-form;
    re2c:YYCTYPE = "unsigned char";
    re2c:YYCURSOR = cur;
    re2c:YYLIMIT = lim;
    re2c:YYFILL = "{ ret = 1; goto done; }";
    re2c:YYFILL:naked = 1;

    "a" [\x00-\xff]* { ret = 2; goto done; }
    *                { ret = -1; goto done; }
*/

__attribute__((target("avx2")))
static int lex_vector(const unsigned char *str, size_t len, size_t *pos) {
    const unsigned char *cur = str, *lim = str + len;
    int ret;
    /*!use:re2c:common
        re2c:vectorize:loops = 1;
    */
done:
    *pos = (size_t)(cur - str);
    return ret;
}

static int lex_scalar(const unsigned char *str, size_t len, size_t *pos) {
    const unsigned char *cur = str, *lim = str + len;
    int ret;
    /*!use:re2c:common
        re2c:vectorize:loops = 0;
    */
done:
    *pos = (size_t)(cur - str);
    return ret;
}

int main() {
    if (!__builtin_cpu_supports("avx2")) return 0;

    int failures = 0;
    for (size_t n = 0; n <= 200; ++n) {
        unsigned char *str = (unsigned char*)malloc(n ? n : 1);
        if (!str) return 1;
        for (size_t i = 0; i < n; ++i) str[i] = (unsigned char)(i * 37);
        if (n > 0) str[0] = 'a';
        size_t pos_v, pos_s;
        const int ret_v = lex_vector(str, n, &pos_v);
        const int ret_s = lex_scalar(str, n, &pos_s);
        if (ret_v != 1 || ret_s != 1 || pos_v != n || pos_s != n) {
            fprintf(stderr, "mismatch on input of length %u\n", (unsigned)n);
            ++failures;
        }
        free(str);
    }
    return failures == 0 ? 0 : 1;
}
