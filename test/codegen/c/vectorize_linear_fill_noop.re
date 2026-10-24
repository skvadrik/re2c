// re2c $INPUT -o $OUTPUT -i
// Parity of --vectorize-linear with the ordinary DFA with a YYFILL that does not refill: the input
// is terminated by a zero sentinel and is not padded with YYMAXFILL units, so the YYFILL check does
// not reserve input for the chain. Every prefix of every word is lexed from a buffer allocated with
// its exact size; the multi-character reads must stay within YYLIMIT, and an out-of-bounds read is
// detected by AddressSanitizer.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char *lim, *cur, *tok, *mar;
} Input;

// Returns the rule number, 100 at the end of input; `*len` is the token length.
typedef int (*lex_t)(Input*, size_t*);

/*!rules:re2c:noop
    "ab"                         { *len = (size_t)(in->cur - in->tok); return 1; }
    "abcd"                       { *len = (size_t)(in->cur - in->tok); return 2; }
    "abcdefgh"                   { *len = (size_t)(in->cur - in->tok); return 3; }
    "abcdefghijk"                { *len = (size_t)(in->cur - in->tok); return 4; }
    "xyzzyxyzzy"                 { *len = (size_t)(in->cur - in->tok); return 5; }
    [\x00]                       { *len = 0; return 100; }
    *                            { *len = (size_t)(in->cur - in->tok); return 0; }
*/

static int noop_0(Input* in, size_t* len) {
    in->tok = in->cur;
    /*!use:re2c:noop
        re2c:api:style = free-form;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYCURSOR = in->cur;
        re2c:YYMARKER = in->mar;
        re2c:YYLIMIT = in->lim;
        re2c:YYFILL = "/* no refill */";
        re2c:vectorize:linear = 0;
    */
}

static int noop_1(Input* in, size_t* len) {
    in->tok = in->cur;
    /*!use:re2c:noop
        re2c:api:style = free-form;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYCURSOR = in->cur;
        re2c:YYMARKER = in->mar;
        re2c:YYLIMIT = in->lim;
        re2c:YYFILL = "/* no refill */";
        re2c:vectorize:linear = 1;
    */
}

static const char* const words[] = {"abcdefghijk", "xyzzyxyzzy", NULL};

static int failures = 0;

static size_t run(lex_t f, const char* s, size_t n, int* rules, size_t* lens) {
    // Exact size: the input and the sentinel, without YYMAXFILL padding.
    unsigned char* buf = (unsigned char*)malloc(n + 1);
    memcpy(buf, s, n);
    buf[n] = 0;
    Input in;
    in.cur = in.tok = in.mar = buf;
    in.lim = buf + n + 1;
    size_t ntok = 0;
    for (;;) {
        size_t l = 0;
        const int r = f(&in, &l);
        rules[ntok] = r;
        lens[ntok] = l;
        ++ntok;
        if (r == 100 || in.cur >= in.lim) break;
    }
    free(buf);
    return ntok;
}

int main() {
    int r1[32], r2[32];
    size_t l1[32], l2[32];
    for (const char* const* w = words; *w; ++w) {
        for (size_t n = 0; n <= strlen(*w); ++n) {
            const size_t n1 = run(noop_0, *w, n, r1, l1);
            const size_t n2 = run(noop_1, *w, n, r2, l2);
            if (n1 != n2 || memcmp(r1, r2, n1 * sizeof(int)) != 0
                    || memcmp(l1, l2, n1 * sizeof(size_t)) != 0) {
                fprintf(stderr, "%s, prefix %d: tokens differ\n", *w, (int)n);
                ++failures;
            }
        }
    }
    return failures > 0 ? 1 : 0;
}
