// re2c $INPUT -o $OUTPUT -i -b
// Parity of --vectorize-linear with the ordinary DFA, sentinel method without YYFILL.
// Each rule set is compiled twice, with and without the option; both lexers must return the same
// rule and the same cursor for every prefix and near miss of the literals, with the limit at the
// sentinel, after it, and before trailing padding. Buffers are allocated with their exact size, so
// that an out-of-bounds read is detected by AddressSanitizer.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*lex_t)(const unsigned char*, const unsigned char*, const unsigned char**);
struct word { const char* str; size_t len; };

#define RET(n) do { *end = YYCURSOR; return n; } while (0)

/*!rules:re2c:backtrack
    "ab"                         { RET(1); }
    "abcd"                       { RET(2); }
    "abcdefgh"                   { RET(3); }
    "abcdefghijk"                { RET(4); }
    "abcx"                       { RET(5); }
    "bcdefghi"                   { RET(6); }
    "xyzzyxyzzy"                 { RET(7); }
    "q" [0-9]+ "end"             { RET(8); }
    *                            { RET(0); }
*/

static int backtrack_0(
        const unsigned char* YYCURSOR, const unsigned char* YYLIMIT, const unsigned char** end) {
    const unsigned char* YYMARKER;
    (void)YYLIMIT;
    /*!use:re2c:backtrack
        re2c:yyfill:enable = 0;
        re2c:vectorize:linear = 0;
        re2c:YYCTYPE = "unsigned char";
    */
}

static int backtrack_1(
        const unsigned char* YYCURSOR, const unsigned char* YYLIMIT, const unsigned char** end) {
    const unsigned char* YYMARKER;
    (void)YYLIMIT;
/*!use:re2c:backtrack
        re2c:yyfill:enable = 0;
        re2c:vectorize:linear = 1;
        re2c:YYLIMIT = YYLIMIT;
        re2c:YYCTYPE = "unsigned char";
    */
}

static const struct word backtrack_words[] = {
    {"\x61\x62", 2},
    {"\x61\x62\x63\x64", 4},
    {"\x61\x62\x63\x64\x65\x66\x67\x68", 8},
    {"\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b", 11},
    {"\x61\x62\x63\x78", 4},
    {"\x62\x63\x64\x65\x66\x67\x68\x69", 8},
    {"\x78\x79\x7a\x7a\x79\x78\x79\x7a\x7a\x79", 10},
    {"\x71\x31\x32\x33\x65\x6e\x64", 7},
    {"\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a", 10},
    {"\x78\x79\x7a\x7a\x79\x78\x79\x7a\x7a", 9},
    {NULL, 0}
};

/*!rules:re2c:anchored
    "GIF89a"                     { RET(1); }
    "GIF87a"                     { RET(2); }
    [\x00\x01]                   { RET(3); }
    [^\x00\x01] [\x00\x01]       { RET(3); }
    [^\x00\x01] [^\x00\x01]      { RET(0); }
*/

static int anchored_0(
        const unsigned char* YYCURSOR, const unsigned char* YYLIMIT, const unsigned char** end) {
    const unsigned char* YYMARKER;
    (void)YYLIMIT;
/*!use:re2c:anchored
        re2c:yyfill:enable = 0;
        re2c:vectorize:linear = 0;
        re2c:YYCTYPE = "unsigned char";
    */
}

static int anchored_1(
        const unsigned char* YYCURSOR, const unsigned char* YYLIMIT, const unsigned char** end) {
    const unsigned char* YYMARKER;
    (void)YYLIMIT;
    /*!use:re2c:anchored
        re2c:yyfill:enable = 0;
        re2c:vectorize:linear = 1;
        re2c:YYLIMIT = YYLIMIT;
        re2c:YYCTYPE = "unsigned char";
    */
}

static const struct word anchored_words[] = {
    {"\x47\x49\x46\x38\x39\x61", 6},
    {"\x47\x49\x46\x38\x37\x61", 6},
    {"\x47\x49\x46\x38", 4},
    {"\x47\x49", 2},
    {"\x47", 1},
    {"\x47\x4a", 2},
    {NULL, 0}
};

static int failures = 0;
static long checks = 0;

static void check1(lex_t f, lex_t g, const unsigned char* in, size_t len, size_t pad, size_t lim) {
    unsigned char* buf = (unsigned char*)malloc(len + 1 + pad);
    if (len > 0) memcpy(buf, in, len);
    buf[len] = 0;
    for (size_t i = 0; i < pad; ++i) buf[len + 1 + i] = len > 0 ? in[i % len] : 'a';
    const unsigned char *e1 = NULL, *e2 = NULL;
    const int r1 = f(buf, buf + lim, &e1);
    const int r2 = g(buf, buf + lim, &e2);
    ++checks;
    if (r1 != r2 || e1 != e2) {
        fprintf(stderr, "mismatch on input of length %d: rule %d/%d, length %d/%d\n",
            (int)len, r1, r2, (int)(e1 - buf), (int)(e2 - buf));
        ++failures;
    }
    free(buf);
}

static void check(lex_t f, lex_t g, const unsigned char* in, size_t len) {
    check1(f, g, in, len, 0, len);           // limit at the sentinel
    check1(f, g, in, len, 0, len + 1);       // limit after the sentinel
    check1(f, g, in, len, 16, len + 1 + 16); // limit after padding
}

static void check_set(lex_t f, lex_t g, const struct word* ws) {
    static const unsigned char alt[] = {0x00, 0x01, 'a', 'z', 'A', 'Z', ':', '-', ' ', '_', '0',
        0x7f, 0x80, 0xfe, 0xff};
    unsigned char t[128];
    for (const struct word* w = ws; w->str; ++w) {
        const unsigned char* s = (const unsigned char*)w->str;
        for (size_t i = 0; i <= w->len; ++i) {
            memcpy(t, s, i);
            check(f, g, t, i);
            for (size_t k = 0; k < sizeof(alt); ++k) {
                t[i] = alt[k];
                check(f, g, t, i + 1);
            }
            if (i < w->len) {
                t[i] = (unsigned char)(s[i] + 1);
                check(f, g, t, i + 1);
                t[i] = (unsigned char)(s[i] - 1);
                check(f, g, t, i + 1);
            }
        }
        for (const struct word* v = ws; v->str; ++v) {
            memcpy(t, s, w->len);
            memcpy(t + w->len, v->str, v->len);
            check(f, g, t, w->len + v->len);
        }
    }
}

int main() {
    check_set(backtrack_0, backtrack_1, backtrack_words);
    check_set(anchored_0, anchored_1, anchored_words);
    if (failures > 0) {
        fprintf(stderr, "%d of %ld checks failed\n", failures, checks);
        return 1;
    }
    return 0;
}
