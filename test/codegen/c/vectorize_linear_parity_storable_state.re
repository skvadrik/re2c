// re2c $INPUT -o $OUTPUT -i -f
// Parity of --vectorize-linear with the ordinary DFA with YYFILL and storable state (push model):
// the lexer returns -2 when it needs more input, the driver refills and calls it again, and the
// lexer resumes from the saved state. A stream of tokens is lexed
// through a small buffer refilled from memory, for many buffer sizes, so that tokens are split at
// every position by refills. The buffer is allocated with its exact size (BUFSIZE + YYMAXFILL) and
// padded with YYMAXFILL zeroes at the end of input, as YYFILL requires; an out-of-bounds read is
// detected by AddressSanitizer.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!max:re2c*/

typedef struct {
    const unsigned char* src;
    size_t srclen, srcpos, bufsize;
    unsigned char *buf, *lim, *cur, *tok, *mar;
    unsigned int yyaccept;
    int eof;
    int state;
    size_t need;
} Input;

static int fill(Input* in, size_t need) {
    if (in->eof) return 1;
    const size_t shift = (size_t)(in->tok - in->buf);
    const size_t used = (size_t)(in->lim - in->tok);
    if (shift < need) return 2;
    memmove(in->buf, in->tok, used);
    in->lim -= shift;
    in->cur -= shift;
    in->tok -= shift;
    if (in->mar >= in->tok) {
        in->mar -= shift;
    } else {
        in->mar = in->buf;
    }
    size_t n = in->bufsize - used;
    if (n > in->srclen - in->srcpos) n = in->srclen - in->srcpos;
    memcpy(in->lim, in->src + in->srcpos, n);
    in->srcpos += n;
    in->lim += n;
    if (in->srcpos == in->srclen) {
        in->eof = 1;
        memset(in->lim, 0, YYMAXFILL);
        in->lim += YYMAXFILL;
    }
    return 0;
}

// Returns the rule number, 100 at the end of input, -1 on error; `*len` is the token length.
typedef int (*lex_t)(Input*, size_t*);
struct word { const char* str; size_t len; };

/*!rules:re2c:backtrack
    "ab"                         { *len = (size_t)(in->cur - in->tok); return 1; }
    "abcd"                       { *len = (size_t)(in->cur - in->tok); return 2; }
    "abcdefgh"                   { *len = (size_t)(in->cur - in->tok); return 3; }
    "abcdefghijk"                { *len = (size_t)(in->cur - in->tok); return 4; }
    "abcx"                       { *len = (size_t)(in->cur - in->tok); return 5; }
    "bcdefghi"                   { *len = (size_t)(in->cur - in->tok); return 6; }
    "xyzzyxyzzy"                 { *len = (size_t)(in->cur - in->tok); return 7; }
    "q" [0-9]+ "end"             { *len = (size_t)(in->cur - in->tok); return 8; }
    *                            { *len = (size_t)(in->cur - in->tok); return 0; }
*/

static int backtrack_0(Input* in, size_t* len) {
    unsigned char yych;
    if (in->state < 0) {
        in->tok = in->cur;
        in->mar = in->cur;
        in->yyaccept = 0;
    }
    /*!use:re2c:backtrack
        re2c:api:style = free-form;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYCURSOR = in->cur;
        re2c:YYMARKER = in->mar;
        re2c:YYLIMIT = in->lim;
        re2c:variable:yyaccept = in->yyaccept;
        re2c:YYGETSTATE = in->state;
        re2c:YYSETSTATE = "in->state = @@;";
        re2c:YYFILL = "{ in->need = @@; return -2; }";
        re2c:vectorize:linear = 0;

        [\x00] { *len = 0; return in->eof && in->tok == in->lim - YYMAXFILL ? 100 : -1; }
    */
}

static int backtrack_1(Input* in, size_t* len) {
    unsigned char yych;
    if (in->state < 0) {
        in->tok = in->cur;
        in->mar = in->cur;
        in->yyaccept = 0;
    }
    /*!use:re2c:backtrack
        re2c:api:style = free-form;
        re2c:YYCTYPE = "unsigned char";
        re2c:YYCURSOR = in->cur;
        re2c:YYMARKER = in->mar;
        re2c:YYLIMIT = in->lim;
        re2c:variable:yyaccept = in->yyaccept;
        re2c:YYGETSTATE = in->state;
        re2c:YYSETSTATE = "in->state = @@;";
        re2c:YYFILL = "{ in->need = @@; return -2; }";
        re2c:vectorize:linear = 1;

        [\x00] { *len = 0; return in->eof && in->tok == in->lim - YYMAXFILL ? 100 : -1; }
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
    {"\x71\x31\x32\x33\x34\x35\x36\x37\x38\x39\x30\x31\x32\x33\x21", 15},
    {"\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a", 10},
    {"\x78\x79\x7a\x7a\x79\x78\x79\x7a\x7a", 9},
    {NULL, 0}
};

static int failures = 0;

static void run(lex_t f, Input* in, const unsigned char* src, size_t len, size_t bufsize,
        int* rules, size_t* lens, size_t* ntok) {
    in->src = src;
    in->srclen = len;
    in->srcpos = 0;
    in->bufsize = bufsize;
    in->buf = (unsigned char*)malloc(bufsize + YYMAXFILL);
    in->cur = in->tok = in->mar = in->lim = in->buf + bufsize;
    in->yyaccept = 0;
    in->eof = 0;
    in->state = -1;
    *ntok = 0;
    for (;;) {
        size_t l = 0;
        int r = f(in, &l);
        while (r == -2) {
            if (fill(in, in->need) != 0) { r = -1; break; }
            r = f(in, &l);
        }
        in->state = -1;
        rules[*ntok] = r;
        lens[*ntok] = l;
        ++*ntok;
        if (r == 100 || r == -1) break;
    }
    free(in->buf);
}

static void check_stream(lex_t f, lex_t g, const unsigned char* src, size_t len,
        size_t bufsize, int* r1, int* r2, size_t* l1, size_t* l2, const char* name) {
    Input in;
    size_t n1, n2;
    run(f, &in, src, len, bufsize, r1, l1, &n1);
    run(g, &in, src, len, bufsize, r2, l2, &n2);
    if (n1 != n2 || r1[n1 - 1] != 100) {
        fprintf(stderr, "%s, buffer %d: %d/%d tokens, last rule %d\n",
            name, (int)bufsize, (int)n1, (int)n2, r1[n1 - 1]);
        ++failures;
        return;
    }
    for (size_t i = 0; i < n1; ++i) {
        if (r1[i] != r2[i] || l1[i] != l2[i]) {
            fprintf(stderr, "%s, buffer %d, token %d: rule %d/%d, length %d/%d\n",
                name, (int)bufsize, (int)i, r1[i], r2[i], (int)l1[i], (int)l2[i]);
            ++failures;
            return;
        }
    }
}

static void check_set(lex_t f, lex_t g, const struct word* ws, const char* name) {
    // Build a stream of words, their prefixes and near misses, separated by a few characters.
    static const char seps[] = " :-\t";
    unsigned char* src = (unsigned char*)malloc(1 << 18);
    size_t len = 0, k = 0;
    for (const struct word* w = ws; w->str; ++w) {
        for (size_t i = 1; i <= w->len; ++i) {
            memcpy(src + len, w->str, i);
            len += i;
            src[len++] = (unsigned char)seps[k++ % (sizeof(seps) - 1)];
            memcpy(src + len, w->str, i);
            len += i;
            if (i < w->len) src[len++] = (unsigned char)(w->str[i] + 1);
            src[len++] = (unsigned char)seps[k++ % (sizeof(seps) - 1)];
        }
        for (size_t i = 0; i < w->len; ++i) {
            unsigned char alt = (unsigned char)(w->str[i] ^ 1);
            if (alt == 0) alt = 2;
            memcpy(src + len, w->str, w->len);
            src[len + i] = alt;
            len += w->len;
            src[len++] = (unsigned char)seps[k++ % (sizeof(seps) - 1)];
        }
        for (const struct word* v = ws; v->str; ++v) {
            memcpy(src + len, w->str, w->len);
            len += w->len;
            memcpy(src + len, v->str, v->len);
            len += v->len;
            src[len++] = (unsigned char)seps[k++ % (sizeof(seps) - 1)];
        }
    }
    int* r1 = (int*)malloc(sizeof(int) * (len + 64));
    int* r2 = (int*)malloc(sizeof(int) * (len + 64));
    size_t* l1 = (size_t*)malloc(sizeof(size_t) * (len + 64));
    size_t* l2 = (size_t*)malloc(sizeof(size_t) * (len + 64));
    // Retain a partial token as well as YYMAXFILL units of lookahead.
    for (size_t bufsize = 2 * YYMAXFILL; bufsize <= 3 * YYMAXFILL + 3; ++bufsize) {
        check_stream(f, g, src, len, bufsize, r1, r2, l1, l2, name);
        // Exercise exact buffer-boundary end-of-stream (`srcpos == srclen` with `lim == buf + bufsize`).
        unsigned char exact[256];
        exact[0] = 'q';
        memset(exact + 1, '9', bufsize - 4);
        memcpy(exact + bufsize - 3, "end", 3);
        check_stream(f, g, exact, bufsize, bufsize, r1, r2, l1, l2, name);
    }
    free(r1); free(r2); free(l1); free(l2); free(src);
}

int main(void) {
    check_set(backtrack_0, backtrack_1, backtrack_words, "backtrack");
    return failures > 0 ? 1 : 0;
}
