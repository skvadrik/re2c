// re2c $INPUT -o $OUTPUT -i --arch x86 --vectorize-loops
// Exhaustive 256-byte check across all signed-bias range shapes in widths 16 and 32:
//   1. singleton [b, b]           (xrange = ['x', 'x'])
//   2. [0, 127]                   (xrange = [0x00, 0x7f], 1-op cmpgt)
//   3. [lo, 127] with lo > 0      (xrange = [0x20, 0x7f], 1-op cmpgt)
//   4. [128, 255]                 (xrange = [0x80, 0xff], 1-op cmpgt)
//   5. [128, hi] with hi < 255    (xrange = [0x80, 0xbf], 1-op cmpgt)
//   6. interior [lo, hi] < 128    (xrange = [0x61, 0x7a], 2-op sub + cmpgt)
//   7. cross-0x80 [lo, hi]        (xrange = [0x60, 0x9f], 2-op sub + cmpgt)
#include <assert.h>
#include <immintrin.h>
#include <stddef.h>
#include <string.h>

/*!re2c
    re2c:YYCTYPE = "unsigned char";
    re2c:YYFILL = "return -2;";
    re2c:YYFILL:naked = 1;
*/

// 1. singleton ['x', 'x']
static int lex_singleton_sc(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 0;
        [^x]+ { return (int)(YYCURSOR - s); }
        *     { return -1; }
    */
}
static int lex_singleton_v16(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 1;
        re2c:vectorize:size = 16;
        [^x]+ { return (int)(YYCURSOR - s); }
        *     { return -1; }
    */
}
static int lex_singleton_v32(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 1;
        re2c:vectorize:size = 32;
        [^x]+ { return (int)(YYCURSOR - s); }
        *     { return -1; }
    */
}

// 2. [0, 127]
static int lex_0_127_sc(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 0;
        [\x80-\xff]+ { return (int)(YYCURSOR - s); }
        *            { return -1; }
    */
}
static int lex_0_127_v16(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 1;
        re2c:vectorize:size = 16;
        [\x80-\xff]+ { return (int)(YYCURSOR - s); }
        *            { return -1; }
    */
}
static int lex_0_127_v32(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 1;
        re2c:vectorize:size = 32;
        [\x80-\xff]+ { return (int)(YYCURSOR - s); }
        *            { return -1; }
    */
}

// 3. [lo, 127] with lo > 0
static int lex_lo_127_sc(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 0;
        [\x00-\x1f\x80-\xff]+ { return (int)(YYCURSOR - s); }
        *                     { return -1; }
    */
}
static int lex_lo_127_v16(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 1;
        re2c:vectorize:size = 16;
        [\x00-\x1f\x80-\xff]+ { return (int)(YYCURSOR - s); }
        *                     { return -1; }
    */
}
static int lex_lo_127_v32(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 1;
        re2c:vectorize:size = 32;
        [\x00-\x1f\x80-\xff]+ { return (int)(YYCURSOR - s); }
        *                     { return -1; }
    */
}

// 4. [128, 255]
static int lex_128_255_sc(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 0;
        [\x00-\x7f]+ { return (int)(YYCURSOR - s); }
        *            { return -1; }
    */
}
static int lex_128_255_v16(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 1;
        re2c:vectorize:size = 16;
        [\x00-\x7f]+ { return (int)(YYCURSOR - s); }
        *            { return -1; }
    */
}
static int lex_128_255_v32(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 1;
        re2c:vectorize:size = 32;
        [\x00-\x7f]+ { return (int)(YYCURSOR - s); }
        *            { return -1; }
    */
}

// 5. [128, hi] with hi < 255
static int lex_128_hi_sc(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 0;
        [\x00-\x7f\xc0-\xff]+ { return (int)(YYCURSOR - s); }
        *                     { return -1; }
    */
}
static int lex_128_hi_v16(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 1;
        re2c:vectorize:size = 16;
        [\x00-\x7f\xc0-\xff]+ { return (int)(YYCURSOR - s); }
        *                     { return -1; }
    */
}
static int lex_128_hi_v32(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 1;
        re2c:vectorize:size = 32;
        [\x00-\x7f\xc0-\xff]+ { return (int)(YYCURSOR - s); }
        *                     { return -1; }
    */
}

// 6. interior [lo, hi] < 128
static int lex_interior_sc(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 0;
        [^a-z]+ { return (int)(YYCURSOR - s); }
        *       { return -1; }
    */
}
static int lex_interior_v16(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 1;
        re2c:vectorize:size = 16;
        [^a-z]+ { return (int)(YYCURSOR - s); }
        *       { return -1; }
    */
}
static int lex_interior_v32(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 1;
        re2c:vectorize:size = 32;
        [^a-z]+ { return (int)(YYCURSOR - s); }
        *       { return -1; }
    */
}

// 7. cross-0x80 [lo, hi]
static int lex_cross80_sc(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 0;
        [^\x60-\x9f]+ { return (int)(YYCURSOR - s); }
        *             { return -1; }
    */
}
static int lex_cross80_v16(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 1;
        re2c:vectorize:size = 16;
        [^\x60-\x9f]+ { return (int)(YYCURSOR - s); }
        *             { return -1; }
    */
}
static int lex_cross80_v32(const unsigned char *s, size_t n) {
    const unsigned char *YYCURSOR = s, *YYLIMIT = s + n;
    /*!local:re2c
        re2c:vectorize:loops = 1;
        re2c:vectorize:size = 32;
        [^\x60-\x9f]+ { return (int)(YYCURSOR - s); }
        *             { return -1; }
    */
}

typedef int (*range_fn_t)(const unsigned char *, size_t);

int main(void) {
    struct {
        unsigned char fill_in;
        unsigned char pad_exit;
        range_fn_t sc, v16, v32;
    } cases[7] = {
        {'a', 'x',  lex_singleton_sc, lex_singleton_v16, lex_singleton_v32},
        {0x80, 'A', lex_0_127_sc,     lex_0_127_v16,     lex_0_127_v32},
        {0x10, 'A', lex_lo_127_sc,    lex_lo_127_v16,    lex_lo_127_v32},
        {'A', 0x80, lex_128_255_sc,   lex_128_255_v16,   lex_128_255_v32},
        {'A', 0x90, lex_128_hi_sc,    lex_128_hi_v16,    lex_128_hi_v32},
        {'A', 'm',  lex_interior_sc,  lex_interior_v16,  lex_interior_v32},
        {'A', 0x80, lex_cross80_sc,   lex_cross80_v16,   lex_cross80_v32},
    };

    unsigned char buf[160];
    for (int c = 0; c < 7; ++c) {
        for (size_t pos = 0; pos <= 70; ++pos) {
            for (int b = 0; b < 256; ++b) {
                memset(buf, cases[c].fill_in, pos);
                buf[pos] = (unsigned char)b;
                memset(buf + pos + 1, cases[c].pad_exit, 64);
                size_t total = pos + 1 + 64;
                int want = cases[c].sc(buf, total);
                int g16 = cases[c].v16(buf, total);
                int g32 = cases[c].v32(buf, total);
                assert(g16 == want);
                assert(g32 == want);
            }
        }
    }
    return 0;
}
