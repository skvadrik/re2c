// re2c $INPUT -o $OUTPUT -i
// Verify that user-requested `re2c:vectorize:linear = 1` survives `Opt::snapshot`, `Opt::restore`,
// and `Opt::merge` across `rules:re2c`, `use:re2c`, `!use:`, and `local:re2c` blocks even when an
// earlier block lacked `YYLIMIT`, and that free-form generic `YYPEEK2`/`YYPEEK4`/`YYPEEK8`
// expressions with unparenthesized bitwise `|` operators are parenthesized safely in `==` tests.
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!rules:re2c:shared
    re2c:yyfill:enable = 0;
    re2c:vectorize:linear = 1;
    "ab"          { *end = (int)(YYCURSOR - start); return 1; }
    "abcd"        { *end = (int)(YYCURSOR - start); return 2; }
    "abcdefgh"    { *end = (int)(YYCURSOR - start); return 3; }
    "abcdefghijk" { *end = (int)(YYCURSOR - start); return 4; }
    *             { *end = (int)(YYCURSOR - start); return 0; }
*/

static int lex_use_block(const unsigned char *YYCURSOR, const unsigned char *YYLIMIT, int *end) {
    const unsigned char *const start = YYCURSOR;
    const unsigned char *YYMARKER = YYCURSOR;
    (void)YYMARKER;
    /*!use:re2c:shared
        re2c:YYCTYPE = "unsigned char";
        re2c:YYLIMIT = YYLIMIT;
    */
}

static int lex_use_directive(
        const unsigned char *YYCURSOR, const unsigned char *YYLIMIT, int *end) {
    const unsigned char *const start = YYCURSOR;
    const unsigned char *YYMARKER = YYCURSOR;
    (void)YYMARKER;
    /*!local:re2c
        !use:shared;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYLIMIT = YYLIMIT;
    */
}

// Global configuration sets `re2c:vectorize:linear = 1` with `re2c:yyfill:enable = 0` before
// `YYLIMIT` is configured, so `accum_opts` has `real.vectorize_linear == false` while preserving
// `user.vectorize_linear == true`.
/*!re2c
    re2c:YYCTYPE = "unsigned char";
    re2c:yyfill:enable = 0;
    re2c:vectorize:linear = 1;
*/

static int lex_local_scalar(const unsigned char *YYCURSOR, const unsigned char *YYLIMIT, int *end) {
    const unsigned char *const start = YYCURSOR;
    const unsigned char *YYMARKER = YYCURSOR;
    (void)YYLIMIT;
    (void)YYMARKER;
    /*!local:re2c
        re2c:yyfill:enable = 0;
        re2c:vectorize:linear = 0;
        "ab"          { *end = (int)(YYCURSOR - start); return 1; }
        "abcd"        { *end = (int)(YYCURSOR - start); return 2; }
        "abcdefgh"    { *end = (int)(YYCURSOR - start); return 3; }
        "abcdefghijk" { *end = (int)(YYCURSOR - start); return 4; }
        *             { *end = (int)(YYCURSOR - start); return 0; }
    */
}

static int lex_local_block(const unsigned char *YYCURSOR, const unsigned char *YYLIMIT, int *end) {
    const unsigned char *const start = YYCURSOR;
    const unsigned char *YYMARKER = YYCURSOR;
    (void)YYMARKER;
    /*!local:re2c
        re2c:yyfill:enable = 0;
        re2c:vectorize:linear = 1;
        re2c:YYLIMIT = YYLIMIT;
        "ab"          { *end = (int)(YYCURSOR - start); return 1; }
        "abcd"        { *end = (int)(YYCURSOR - start); return 2; }
        "abcdefgh"    { *end = (int)(YYCURSOR - start); return 3; }
        "abcdefghijk" { *end = (int)(YYCURSOR - start); return 4; }
        *             { *end = (int)(YYCURSOR - start); return 0; }
    */
}

// Ordinary block following `local:re2c`: `Opt::restore(accum_opts)` must keep
// `user.vectorize_linear == true` so that supplying `re2c:YYLIMIT` re-enables wide reads.
static int lex_after_local(const unsigned char *YYCURSOR, const unsigned char *YYLIMIT, int *end) {
    const unsigned char *const start = YYCURSOR;
    const unsigned char *YYMARKER = YYCURSOR;
    (void)YYMARKER;
    /*!re2c
        re2c:YYLIMIT = YYLIMIT;
        "ab"          { *end = (int)(YYCURSOR - start); return 1; }
        "abcd"        { *end = (int)(YYCURSOR - start); return 2; }
        "abcdefgh"    { *end = (int)(YYCURSOR - start); return 3; }
        "abcdefghijk" { *end = (int)(YYCURSOR - start); return 4; }
        *             { *end = (int)(YYCURSOR - start); return 0; }
    */
}

// Free-form generic API with unparenthesized bitwise-OR `YYPEEK2`/`YYPEEK4`/`YYPEEK8` expressions.
static int lex_generic_unparen(const unsigned char *s, size_t len, int *end) {
    size_t idx = 0;
    size_t saved = 0;
    /*!local:re2c
        re2c:api = generic;
        re2c:api:style = free-form;
        re2c:yyfill:enable = 0;
        re2c:vectorize:linear = 1;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYPEEK = "idx < len ? s[idx] : (unsigned char)0";
        re2c:YYPEEK2 = "(uint16_t)s[idx] | (uint16_t)((uint16_t)s[idx + 1] << 8)";
        re2c:YYPEEK4 = "(uint32_t)s[idx] | ((uint32_t)s[idx + 1] << 8) | ((uint32_t)s[idx + 2] << 16) | ((uint32_t)s[idx + 3] << 24)";
        re2c:YYPEEK8 = "(uint64_t)s[idx] | ((uint64_t)s[idx + 1] << 8) | ((uint64_t)s[idx + 2] << 16) | ((uint64_t)s[idx + 3] << 24) | ((uint64_t)s[idx + 4] << 32) | ((uint64_t)s[idx + 5] << 40) | ((uint64_t)s[idx + 6] << 48) | ((uint64_t)s[idx + 7] << 56)";
        re2c:YYSKIP = "++idx;";
        re2c:YYBACKUP = "saved = idx;";
        re2c:YYRESTORE = "idx = saved;";
        re2c:YYLESSTHAN = "(len - idx) < (size_t)(@@)";
        re2c:YYSHIFT = "idx += (size_t)(@@);";
        "ab"          { *end = (int)idx; return 1; }
        "abcd"        { *end = (int)idx; return 2; }
        "abcdefgh"    { *end = (int)idx; return 3; }
        "abcdefghijk" { *end = (int)idx; return 4; }
        *             { *end = (int)idx; return 0; }
    */
}

static int check_input(const unsigned char *in, size_t len) {
    unsigned char *buf = (unsigned char *)malloc(len + 1);
    unsigned char *obuf = (unsigned char *)malloc(len ? len : 1);
    if (!buf || !obuf) {
        free(buf);
        free(obuf);
        return 1;
    }
    if (len > 0) {
        memcpy(buf, in, len);
        memcpy(obuf, in, len);
    }
    buf[len] = 0;

    int e_ref = -1, e1 = -1, e2 = -1, e3 = -1, e4 = -1, e5 = -1;
    const int r_ref = lex_local_scalar(buf, buf + len, &e_ref);
    const int r1 = lex_use_block(buf, buf + len, &e1);
    const int r2 = lex_use_directive(buf, buf + len, &e2);
    const int r3 = lex_local_block(buf, buf + len, &e3);
    const int r4 = lex_after_local(buf, buf + len, &e4);
    const int r5 = lex_generic_unparen(obuf, len, &e5);

    free(buf);
    free(obuf);

    if (r1 != r_ref || e1 != e_ref
            || r2 != r_ref || e2 != e_ref
            || r3 != r_ref || e3 != e_ref
            || r4 != r_ref || e4 != e_ref
            || r5 != r_ref || e5 != e_ref) {
        fprintf(stderr,
            "mismatch on len=%zu: ref=(%d,%d) use=(%d,%d) !use=(%d,%d) local=(%d,%d) "
            "after_local=(%d,%d) generic=(%d,%d)\n",
            len, r_ref, e_ref, r1, e1, r2, e2, r3, e3, r4, e4, r5, e5);
        return 1;
    }
    return 0;
}

int main(void) {
    static const char *const words[] = {
        "ab",
        "abcd",
        "abcdefgh",
        "abcdefghijk",
        "axcd",
        "abxd",
        "axcdefgh",
        "abcdxfgh",
        "abcdefghxjk",
    };
    for (size_t i = 0; i < sizeof(words) / sizeof(words[0]); ++i) {
        const unsigned char *w = (const unsigned char *)words[i];
        const size_t n = strlen(words[i]);
        for (size_t p = 0; p <= n; ++p) {
            if (check_input(w, p)) return 1;
            unsigned char mut[32];
            memcpy(mut, w, p);
            mut[p] = 'z';
            if (check_input(mut, p + 1)) return 1;
            if (p < n) {
                memcpy(mut, w, n);
                mut[p] = (unsigned char)(w[p] ^ 1u);
                if (mut[p] == 0) mut[p] = 2;
                if (check_input(mut, n)) return 1;
            }
        }
    }
    return 0;
}
