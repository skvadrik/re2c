// re2c $INPUT -o $OUTPUT -i --api generic
// Parity and opacity of --vectorize-linear with the generic API (function-like and free-form
// styles, with and without bounds refill) over an opaque stream state, in exact-size allocations
// so that AddressSanitizer catches any read past the stream end.
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct OpaqueStream {
    const unsigned char *raw;
    size_t idx, end, saved;
};

static size_t g_wide_peeks_2 = 0;
static size_t g_wide_peeks_4 = 0;
static size_t g_wide_peeks_8 = 0;

static inline uint16_t opaque_peek2(const struct OpaqueStream *s) {
    ++g_wide_peeks_2;
    return (uint16_t)s->raw[s->idx]
        | (uint16_t)((uint16_t)s->raw[s->idx + 1] << 8);
}

static inline uint32_t opaque_peek4(const struct OpaqueStream *s) {
    ++g_wide_peeks_4;
    return (uint32_t)s->raw[s->idx]
        | ((uint32_t)s->raw[s->idx + 1] << 8)
        | ((uint32_t)s->raw[s->idx + 2] << 16)
        | ((uint32_t)s->raw[s->idx + 3] << 24);
}

static inline uint64_t opaque_peek8(const struct OpaqueStream *s) {
    ++g_wide_peeks_8;
    return (uint64_t)s->raw[s->idx]
        | ((uint64_t)s->raw[s->idx + 1] << 8)
        | ((uint64_t)s->raw[s->idx + 2] << 16)
        | ((uint64_t)s->raw[s->idx + 3] << 24)
        | ((uint64_t)s->raw[s->idx + 4] << 32)
        | ((uint64_t)s->raw[s->idx + 5] << 40)
        | ((uint64_t)s->raw[s->idx + 6] << 48)
        | ((uint64_t)s->raw[s->idx + 7] << 56);
}

/*!rules:re2c:headers
    "ok:"                { *out_pos = (int)s.idx; return 1; }
    "date:"              { *out_pos = (int)s.idx; return 2; }
    "content-length:"    { *out_pos = (int)s.idx; return 3; }
    "content-type:"      { *out_pos = (int)s.idx; return 4; }
    "transfer-encoding:" { *out_pos = (int)s.idx; return 5; }
    "connection:"        { *out_pos = (int)s.idx; return 6; }
    [a-z-]+ ":"          { *out_pos = (int)s.idx; return 7; }
    *                    { *out_pos = (int)s.idx; return 0; }
*/

static int lex_fn_scalar(const unsigned char *buf, size_t len, int *out_pos) {
    struct OpaqueStream s = {buf, 0, len, 0};
#define YYCTYPE unsigned char
#define YYPEEK() (s.idx < s.end ? s.raw[s.idx] : (unsigned char)0)
#define YYSKIP() (++s.idx)
#define YYBACKUP() (s.saved = s.idx)
#define YYRESTORE() (s.idx = s.saved)
    /*!local:re2c
        re2c:api:style = functions;
        re2c:yyfill:enable = 0;
        re2c:vectorize:linear = 0;
        !use:headers;
    */
#undef YYCTYPE
#undef YYPEEK
#undef YYSKIP
#undef YYBACKUP
#undef YYRESTORE
}

static int lex_fn_linear(const unsigned char *buf, size_t len, int *out_pos) {
    struct OpaqueStream s = {buf, 0, len, 0};
#define YYCTYPE unsigned char
#define YYPEEK() (s.idx < s.end ? s.raw[s.idx] : (unsigned char)0)
#define YYPEEK2() opaque_peek2(&s)
#define YYPEEK4() opaque_peek4(&s)
#define YYPEEK8() opaque_peek8(&s)
#define YYSKIP() (++s.idx)
#define YYBACKUP() (s.saved = s.idx)
#define YYRESTORE() (s.idx = s.saved)
#define YYLESSTHAN(n) ((s.end - s.idx) < (size_t)(n))
#define YYSHIFT(n) (s.idx += (size_t)(n))
    /*!local:re2c
        re2c:api:style = functions;
        re2c:yyfill:enable = 0;
        re2c:YYLESSTHAN = YYLESSTHAN;
        re2c:vectorize:linear = 1;
        !use:headers;
    */
#undef YYCTYPE
#undef YYPEEK
#undef YYPEEK2
#undef YYPEEK4
#undef YYPEEK8
#undef YYSKIP
#undef YYBACKUP
#undef YYRESTORE
#undef YYLESSTHAN
#undef YYSHIFT
}

static int lex_ff_scalar(const unsigned char *buf, size_t len, int *out_pos) {
    struct OpaqueStream s = {buf, 0, len, 0};
    /*!local:re2c
        re2c:api:style = free-form;
        re2c:yyfill:enable = 0;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYPEEK = "(s.idx < s.end ? s.raw[s.idx] : (unsigned char)0)";
        re2c:YYSKIP = "++s.idx;";
        re2c:YYBACKUP = "s.saved = s.idx;";
        re2c:YYRESTORE = "s.idx = s.saved;";
        re2c:vectorize:linear = 0;
        !use:headers;
    */
}

static int lex_ff_linear(const unsigned char *buf, size_t len, int *out_pos) {
    struct OpaqueStream s = {buf, 0, len, 0};
    /*!local:re2c
        re2c:api:style = free-form;
        re2c:yyfill:enable = 0;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYPEEK = "(s.idx < s.end ? s.raw[s.idx] : (unsigned char)0)";
        re2c:YYPEEK2 = "opaque_peek2(&s)";
        re2c:YYPEEK4 = "opaque_peek4(&s)";
        re2c:YYPEEK8 = "opaque_peek8(&s)";
        re2c:YYSKIP = "++s.idx;";
        re2c:YYBACKUP = "s.saved = s.idx;";
        re2c:YYRESTORE = "s.idx = s.saved;";
        re2c:YYLESSTHAN = "(s.end - s.idx) < (size_t)(@@)";
        re2c:YYSHIFT = "s.idx += (size_t)(@@);";
        re2c:vectorize:linear = 1;
        !use:headers;
    */
}

static int lex_fill_fn_scalar(const unsigned char *buf, size_t len, int *out_pos) {
    struct OpaqueStream s = {buf, 0, len, 0};
#define YYCTYPE unsigned char
#define YYPEEK() (s.idx < s.end ? s.raw[s.idx] : (unsigned char)0)
#define YYSKIP() (++s.idx)
#define YYBACKUP() (s.saved = s.idx)
#define YYRESTORE() (s.idx = s.saved)
#define YYLESSTHAN(n) ((s.end - s.idx) < (size_t)(n))
#define YYFILL(n) ((void)(n))
    /*!local:re2c
        re2c:api:style = functions;
        re2c:yyfill:enable = 1;
        re2c:YYFILL:naked = 0;
        re2c:vectorize:linear = 0;
        !use:headers;
    */
#undef YYCTYPE
#undef YYPEEK
#undef YYSKIP
#undef YYBACKUP
#undef YYRESTORE
#undef YYLESSTHAN
#undef YYFILL
}

static int lex_fill_fn_linear(const unsigned char *buf, size_t len, int *out_pos) {
    struct OpaqueStream s = {buf, 0, len, 0};
#define YYCTYPE unsigned char
#define YYPEEK() (s.idx < s.end ? s.raw[s.idx] : (unsigned char)0)
#define YYPEEK2() opaque_peek2(&s)
#define YYPEEK4() opaque_peek4(&s)
#define YYPEEK8() opaque_peek8(&s)
#define YYSKIP() (++s.idx)
#define YYBACKUP() (s.saved = s.idx)
#define YYRESTORE() (s.idx = s.saved)
#define YYLESSTHAN(n) ((s.end - s.idx) < (size_t)(n))
#define YYSHIFT(n) (s.idx += (size_t)(n))
#define YYFILL(n) ((void)(n))
    /*!local:re2c
        re2c:api:style = functions;
        re2c:yyfill:enable = 1;
        re2c:YYFILL:naked = 0;
        re2c:vectorize:linear = 1;
        !use:headers;
    */
#undef YYCTYPE
#undef YYPEEK
#undef YYPEEK2
#undef YYPEEK4
#undef YYPEEK8
#undef YYSKIP
#undef YYBACKUP
#undef YYRESTORE
#undef YYLESSTHAN
#undef YYSHIFT
#undef YYFILL
}

static int lex_fill_ff_scalar(const unsigned char *buf, size_t len, int *out_pos) {
    struct OpaqueStream s = {buf, 0, len, 0};
    /*!local:re2c
        re2c:api:style = free-form;
        re2c:yyfill:enable = 1;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYPEEK = "(s.idx < s.end ? s.raw[s.idx] : (unsigned char)0)";
        re2c:YYSKIP = "++s.idx;";
        re2c:YYBACKUP = "s.saved = s.idx;";
        re2c:YYRESTORE = "s.idx = s.saved;";
        re2c:YYLESSTHAN = "(s.end - s.idx) < (size_t)(@@)";
        re2c:YYFILL = "(void)@@;";
        re2c:YYFILL:naked = 1;
        re2c:vectorize:linear = 0;
        !use:headers;
    */
}

static int lex_fill_ff_linear(const unsigned char *buf, size_t len, int *out_pos) {
    struct OpaqueStream s = {buf, 0, len, 0};
    /*!local:re2c
        re2c:api:style = free-form;
        re2c:yyfill:enable = 1;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYPEEK = "(s.idx < s.end ? s.raw[s.idx] : (unsigned char)0)";
        re2c:YYPEEK2 = "opaque_peek2(&s)";
        re2c:YYPEEK4 = "opaque_peek4(&s)";
        re2c:YYPEEK8 = "opaque_peek8(&s)";
        re2c:YYSKIP = "++s.idx;";
        re2c:YYBACKUP = "s.saved = s.idx;";
        re2c:YYRESTORE = "s.idx = s.saved;";
        re2c:YYLESSTHAN = "(s.end - s.idx) < (size_t)(@@)";
        re2c:YYSHIFT = "s.idx += (size_t)(@@);";
        re2c:YYFILL = "(void)@@;";
        re2c:YYFILL:naked = 1;
        re2c:vectorize:linear = 1;
        !use:headers;
    */
}

static int check_one(const char *src, size_t len) {
    unsigned char *buf = (unsigned char *)malloc(len ? len : 1);
    if (!buf) return 1;
    if (len) memcpy(buf, src, len);
    int e[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    int r[8];
    r[0] = lex_fn_scalar(buf, len, &e[0]);
    r[1] = lex_fn_linear(buf, len, &e[1]);
    r[2] = lex_ff_scalar(buf, len, &e[2]);
    r[3] = lex_ff_linear(buf, len, &e[3]);
    r[4] = lex_fill_fn_scalar(buf, len, &e[4]);
    r[5] = lex_fill_fn_linear(buf, len, &e[5]);
    r[6] = lex_fill_ff_scalar(buf, len, &e[6]);
    r[7] = lex_fill_ff_linear(buf, len, &e[7]);
    free(buf);
    for (int i = 1; i < 8; ++i) {
        if (r[i] != r[0] || e[i] != e[0]) {
            fprintf(stderr, "mismatch at variant %d on \"%.*s\": got (%d,%d), want (%d,%d)\n",
                i, (int)len, src, r[i], e[i], r[0], e[0]);
            return 1;
        }
    }
    return 0;
}

typedef int (*lex_variant_fn)(const unsigned char *, size_t, int *);

static int check_variant_hits(const char *name, lex_variant_fn fn,
        const char *const *words, size_t nwords, int expect_wide) {
    g_wide_peeks_2 = 0;
    g_wide_peeks_4 = 0;
    g_wide_peeks_8 = 0;
    for (size_t i = 0; i < nwords; ++i) {
        const size_t n = strlen(words[i]);
        unsigned char *buf = (unsigned char *)malloc(n ? n : 1);
        if (!buf) return 1;
        if (n) memcpy(buf, words[i], n);
        int pos = -1;
        (void)fn(buf, n, &pos);
        free(buf);
    }
    if (expect_wide) {
        if (g_wide_peeks_2 == 0 || g_wide_peeks_4 == 0 || g_wide_peeks_8 == 0) {
            fprintf(stderr, "%s: expected positive wide peek counts, got (%zu, %zu, %zu)\n",
                name, g_wide_peeks_2, g_wide_peeks_4, g_wide_peeks_8);
            return 1;
        }
    } else {
        if (g_wide_peeks_2 != 0 || g_wide_peeks_4 != 0 || g_wide_peeks_8 != 0) {
            fprintf(stderr, "%s: expected zero wide peek counts, got (%zu, %zu, %zu)\n",
                name, g_wide_peeks_2, g_wide_peeks_4, g_wide_peeks_8);
            return 1;
        }
    }
    return 0;
}

int main(void) {
    static const char *const words[] = {
        "ok:",
        "date:",
        "content-length:",
        "content-type:",
        "transfer-encoding:",
        "connection:",
        "content-language:",
        "x-custom:",
    };
    const size_t nwords = sizeof(words) / sizeof(words[0]);
    for (size_t i = 0; i < nwords; ++i) {
        const char *w = words[i];
        const size_t n = strlen(w);
        for (size_t p = 0; p <= n; ++p) {
            if (check_one(w, p)) return 1;
            char mut[32];
            memcpy(mut, w, p);
            mut[p] = 'z';
            if (check_one(mut, p + 1)) return 1;
            mut[p] = ':';
            if (check_one(mut, p + 1)) return 1;
            mut[p] = '!';
            if (check_one(mut, p + 1)) return 1;
            if (p < n) {
                memcpy(mut, w, n);
                mut[p] = (char)((unsigned char)w[p] ^ 1u);
                if (check_one(mut, n)) return 1;
            }
        }
    }
    if (check_variant_hits("lex_fn_scalar", lex_fn_scalar, words, nwords, 0)) return 1;
    if (check_variant_hits("lex_ff_scalar", lex_ff_scalar, words, nwords, 0)) return 1;
    if (check_variant_hits("lex_fill_fn_scalar", lex_fill_fn_scalar, words, nwords, 0)) return 1;
    if (check_variant_hits("lex_fill_ff_scalar", lex_fill_ff_scalar, words, nwords, 0)) return 1;
    if (check_variant_hits("lex_fn_linear", lex_fn_linear, words, nwords, 1)) return 1;
    if (check_variant_hits("lex_ff_linear", lex_ff_linear, words, nwords, 1)) return 1;
    if (check_variant_hits("lex_fill_fn_linear", lex_fill_fn_linear, words, nwords, 1)) return 1;
    if (check_variant_hits("lex_fill_ff_linear", lex_fill_ff_linear, words, nwords, 1)) return 1;
    return 0;
}
