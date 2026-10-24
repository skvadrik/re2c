// re2c $INPUT -o $OUTPUT -i --vectorize-loops -Wno-unreachable-rules
// With an 8-bit encoding and a code unit wider than one byte (`unsigned int`), the
// vector block would compare the bytes of each code unit and advance the cursor by
// 32 code units (128 bytes) per block. re2c cannot see the width of a user-defined
// YYCTYPE, so the block starts with a compile-time check: this generated file must
// not compile (`size of unnamed array is negative` with GCC and Clang). The width of
// the encoding's code units is checked by re2c itself (see vectorize_loops_utf32).
#include <immintrin.h>
#include <stdio.h>

/*!rules:re2c:common
    re2c:api:style = free-form;
    re2c:YYCTYPE = "unsigned int";
    re2c:YYCURSOR = cur;
    re2c:YYLIMIT = lim;
    re2c:YYFILL = "{ ret = 0; goto done; }";
    re2c:YYFILL:naked = 1;

    [^ ]+ { ret = 1; goto done; }
    *     { ret = -1; goto done; }
*/

__attribute__((target("avx2")))
static int lex_vector(const unsigned int *str, const unsigned int *lim, size_t *pos) {
    const unsigned int *cur = str;
    int ret;
    /*!use:re2c:common
        re2c:vectorize:loops = 1;
    */
done:
    *pos = (size_t)(cur - str);
    return ret;
}

static int lex_scalar(const unsigned int *str, const unsigned int *lim, size_t *pos) {
    const unsigned int *cur = str;
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

    enum { SIZE = 256 };
    unsigned int buf[SIZE];
    int failures = 0;
    for (size_t n = 1; n < SIZE; ++n) {
        for (size_t i = 0; i < SIZE; ++i) buf[i] = i < n ? 'a' + i % 26 : ' ';
        size_t pos_v, pos_s;
        const int ret_v = lex_vector(buf, buf + SIZE, &pos_v);
        const int ret_s = lex_scalar(buf, buf + SIZE, &pos_s);
        if (ret_v != 1 || ret_s != 1 || pos_v != n || pos_s != n) {
            fprintf(stderr, "mismatch on run of length %u: vector %u, scalar %u\n",
                (unsigned)n, (unsigned)pos_v, (unsigned)pos_s);
            ++failures;
        }
    }
    return failures == 0 ? 0 : 1;
}
