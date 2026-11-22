// re2c $INPUT -o $OUTPUT -i --arch x86 --api generic --vectorize-loops
#include <assert.h>
#include <immintrin.h>
#include <stddef.h>
#include <string.h>

typedef struct {
    const unsigned char *ptr;
    const unsigned char *end;
    const unsigned char *bak;
} OpaqueStream;

static int lex_fn_32(const unsigned char *str, size_t len) {
    OpaqueStream s = {str, str + len, str};

#define YYPEEK()       (*s.ptr)
#define YYPEEK32()     _mm256_loadu_si256((const __m256i *)s.ptr)
#define YYSKIP()       (++s.ptr)
#define YYBACKUP()     (s.bak = s.ptr)
#define YYRESTORE()    (s.ptr = s.bak)
#define YYSHIFT(n)     (s.ptr += (n))
#define YYLESSTHAN(n)  ((size_t)(s.end - s.ptr) < (size_t)(n))
#define YYFILL(n)      return -2

    /*!re2c
        re2c:api = generic;
        re2c:api:style = functions;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYFILL:naked = 0;
        re2c:vectorize:size = 32;

        [a-zA-Z_][a-zA-Z0-9_]* { return (int)(s.ptr - str); }
        *                      { return -1; }
    */

#undef YYPEEK
#undef YYPEEK32
#undef YYSKIP
#undef YYBACKUP
#undef YYRESTORE
#undef YYSHIFT
#undef YYLESSTHAN
#undef YYFILL
}

static int lex_fn_16(const unsigned char *str, size_t len) {
    OpaqueStream s = {str, str + len, str};

#define YYPEEK()       (*s.ptr)
#define YYPEEK16()     _mm_loadu_si128((const __m128i *)s.ptr)
#define YYSKIP()       (++s.ptr)
#define YYBACKUP()     (s.bak = s.ptr)
#define YYRESTORE()    (s.ptr = s.bak)
#define YYSHIFT(n)     (s.ptr += (n))
#define YYLESSTHAN(n)  ((size_t)(s.end - s.ptr) < (size_t)(n))
#define YYFILL(n)      return -2

    /*!re2c
        re2c:api = generic;
        re2c:api:style = functions;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYFILL:naked = 0;
        re2c:vectorize:size = 16;

        [a-zA-Z_][a-zA-Z0-9_]* { return (int)(s.ptr - str); }
        *                      { return -1; }
    */

#undef YYPEEK
#undef YYPEEK16
#undef YYSKIP
#undef YYBACKUP
#undef YYRESTORE
#undef YYSHIFT
#undef YYLESSTHAN
#undef YYFILL
}

static int lex_freeform_32(const unsigned char *str, size_t len) {
    OpaqueStream s = {str, str + len, str};

    /*!re2c
        re2c:api = generic;
        re2c:api:style = free-form;
        re2c:api:sigil = "@@";
        re2c:YYCTYPE = "unsigned char";
        re2c:YYPEEK = "*s.ptr";
        re2c:YYPEEK32 = "_mm256_loadu_si256((const __m256i *)s.ptr)";
        re2c:YYSKIP = "++s.ptr;";
        re2c:YYBACKUP = "s.bak = s.ptr;";
        re2c:YYRESTORE = "s.ptr = s.bak;";
        re2c:YYSHIFT = "s.ptr += @@;";
        re2c:YYLESSTHAN = "(size_t)(s.end - s.ptr) < (size_t)(@@)";
        re2c:YYFILL = "return -2;";
        re2c:YYFILL:naked = 1;
        re2c:vectorize:size = 32;

        [a-zA-Z_][a-zA-Z0-9_]* { return (int)(s.ptr - str); }
        *                      { return -1; }
    */
}

static int lex_freeform_16(const unsigned char *str, size_t len) {
    OpaqueStream s = {str, str + len, str};

    /*!re2c
        re2c:api = generic;
        re2c:api:style = free-form;
        re2c:api:sigil = "@@";
        re2c:YYCTYPE = "unsigned char";
        re2c:YYPEEK = "*s.ptr";
        re2c:YYPEEK16 = "_mm_loadu_si128((const __m128i *)s.ptr)";
        re2c:YYSKIP = "++s.ptr;";
        re2c:YYBACKUP = "s.bak = s.ptr;";
        re2c:YYRESTORE = "s.ptr = s.bak;";
        re2c:YYSHIFT = "s.ptr += @@;";
        re2c:YYLESSTHAN = "(size_t)(s.end - s.ptr) < (size_t)(@@)";
        re2c:YYFILL = "return -2;";
        re2c:YYFILL:naked = 1;
        re2c:vectorize:size = 16;

        [a-zA-Z_][a-zA-Z0-9_]* { return (int)(s.ptr - str); }
        *                      { return -1; }
    */
}

int main(void) {
    unsigned char buf[256];
    for (size_t n = 0; n <= 160; ++n) {
        memset(buf, 'a', n);
        buf[n] = '!';
        memset(buf + n + 1, 0, sizeof(buf) - n - 1);
        int want = n == 0 ? -1 : (int)n;
        assert(lex_fn_32(buf, sizeof(buf)) == want);
        assert(lex_fn_16(buf, sizeof(buf)) == want);
        assert(lex_freeform_32(buf, sizeof(buf)) == want);
        assert(lex_freeform_16(buf, sizeof(buf)) == want);
    }
    return 0;
}
