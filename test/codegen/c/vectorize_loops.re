// re2c $INPUT -o $OUTPUT -i --vectorize-loops
// Check that lexers with vectorized loops produce the expected tokens when the
// input is read in chunks into a small buffer with YYFILL, so that buffer
// refills land inside tokens at every position relative to a vector block.
//
// Each input consists of a prefix of short tokens, a long token (a number, an
// identifier, whitespace, a string literal with or without escapes, or an
// unterminated string literal) and a suffix (nothing, a valid token, an invalid
// character or an embedded null). The expected token stream and status are
// built together with the input, independently of the lexers. The prefix
// length takes all values from 0 to BUFSIZE - 1, so the long token starts at
// every position modulo the vector size, and the test checks that for every
// kind of long token and every such position the vector lexer has refilled the
// buffer in the middle of the token at least once.
#include <immintrin.h>
#include <stdio.h>
#include <string.h>

/*!max:re2c*/
#define BUFSIZE 128
#define VECSIZE 32
#define MAXTOKS 128
#define MAXSPLITS 16
#define STRSIZE 512

// Token kinds.
enum { K_NUM = 1, K_ID, K_WS, K_STR };

// Lexer status: the number of tokens on success, or one of these errors.
enum { ERR_FILL = -1, ERR_CHAR = -2, ERR_NUL = -3, ERR_MANY = -4 };

typedef struct {
    int kind;
    size_t pos, len;
} Token;

typedef struct {
    const unsigned char *str;
    size_t len, pos; // input string, its length and the number of bytes read
    unsigned char buf[BUFSIZE + YYMAXFILL], *lim, *cur, *mar, *tok;
    size_t offset; // offset of `buf` in the input string
    int eof;
    Token *toks; // output tokens
    int ntoks, maxtoks;
    // Start positions of tokens during which the buffer was refilled after the
    // lexer had read a part of the token.
    size_t splits[MAXSPLITS];
    int nsplits;
} Input;

static void init(Input *in, const unsigned char *str, size_t len, Token *toks, int maxtoks) {
    in->str = str;
    in->len = len;
    in->pos = 0;
    in->cur = in->mar = in->tok = in->lim = in->buf;
    in->offset = 0;
    in->eof = 0;
    in->toks = toks;
    in->ntoks = 0;
    in->maxtoks = maxtoks;
    in->nsplits = 0;
}

static int fill(Input *in, size_t need) {
    if (in->eof) return 1;

    const size_t shift = in->tok - in->buf;
    const size_t used = in->lim - in->tok;

    // Error: lexeme too long.
    if (BUFSIZE - used < need) return 2;

    // Record a refill in the middle of a token.
    if (in->cur > in->tok && in->nsplits < MAXSPLITS) {
        in->splits[in->nsplits++] = in->offset + shift;
    }

    // Shift buffer contents (discard everything up to the current token). The
    // marker is only rebased if it is in the kept part of the buffer.
    memmove(in->buf, in->tok, used);
    in->lim -= shift;
    in->cur -= shift;
    if (in->mar >= in->tok) in->mar -= shift;
    in->tok -= shift;
    in->offset += shift;

    // Fill free space at the end of buffer with new data from the string.
    size_t n = BUFSIZE - used;
    if (n > in->len - in->pos) n = in->len - in->pos;
    memcpy(in->lim, in->str + in->pos, n);
    in->pos += n;
    in->lim += n;

    // If the whole string has been read, this is end of input => add zero
    // padding so that the lexer can access characters at the end of buffer.
    if (in->pos == in->len) {
        in->eof = 1;
        memset(in->lim, 0, YYMAXFILL);
        in->lim += YYMAXFILL;
    }

    return 0;
}

/*!rules:re2c:common
    re2c:api:style = free-form;
    re2c:YYCTYPE = "unsigned char";
    re2c:YYCURSOR = in->cur;
    re2c:YYLIMIT = in->lim;
    re2c:YYMARKER = in->mar;
    re2c:YYFILL = "if (fill(in, @@) != 0) return ERR_FILL;";

    str = ["] ([^"\\\x00] | [\\][^\x00])* ["];

    [\x00] {
        // Check that it is the sentinel, not some unexpected null.
        return in->eof && in->tok == in->lim - YYMAXFILL ? in->ntoks : ERR_NUL;
    }
    [0-9]+                 { kind = K_NUM; goto token; }
    [a-zA-Z_][a-zA-Z0-9_]* { kind = K_ID; goto token; }
    [ \t]+                 { kind = K_WS; goto token; }
    str                    { kind = K_STR; goto token; }
    *                      { return ERR_CHAR; }
*/

#define TOKEN() \
    if (in->ntoks == in->maxtoks) return ERR_MANY; \
    in->toks[in->ntoks].kind = kind; \
    in->toks[in->ntoks].pos = in->offset + (in->tok - in->buf); \
    in->toks[in->ntoks].len = in->cur - in->tok; \
    ++in->ntoks

__attribute__((target("avx2")))
static int lex_vector(Input *in) {
    int kind;
loop:
    in->tok = in->cur;
    /*!use:re2c:common
        re2c:vectorize:loops = 1;
    */
token:
    TOKEN();
    goto loop;
}

static int lex_scalar(Input *in) {
    int kind;
loop:
    in->tok = in->cur;
    /*!use:re2c:common
        re2c:vectorize:loops = 0;
    */
token:
    TOKEN();
    goto loop;
}

// A test case: the input string with the expected tokens and status.
typedef struct {
    unsigned char str[STRSIZE];
    size_t len;
    Token toks[MAXTOKS];
    int ntoks;
    int status; // 0 while the input is valid, then an error
    size_t probe; // start of the long token (or of the failing lexeme)
} Case;

static void init_case(Case *c) {
    c->len = 0;
    c->ntoks = 0;
    c->status = 0;
    c->probe = 0;
}

// Append raw bytes that do not form a token.
static void put_raw(Case *c, const unsigned char *s, size_t n) {
    memcpy(c->str + c->len, s, n);
    c->len += n;
}

// Append a token. Adjacent whitespace, adjacent numbers, and an identifier
// followed by an identifier or a number form a single token.
static void put(Case *c, int kind, const unsigned char *s, size_t n) {
    Token *last = c->ntoks > 0 ? &c->toks[c->ntoks - 1] : NULL;
    const int merge = last != NULL && last->pos + last->len == c->len
        && ((last->kind == K_WS && kind == K_WS)
            || (last->kind == K_NUM && kind == K_NUM)
            || (last->kind == K_ID && (kind == K_ID || kind == K_NUM)));
    if (merge) {
        last->len += n;
    } else {
        Token *t = &c->toks[c->ntoks++];
        t->kind = kind;
        t->pos = c->len;
        t->len = n;
    }
    put_raw(c, s, n);
}

static void put_str(Case *c, int kind, const char *s) {
    put(c, kind, (const unsigned char*)s, strlen(s));
}

// Append a prefix of exactly `len` bytes made of short tokens separated by
// whitespace; `seed` selects the first token.
static void put_prefix(Case *c, size_t len, size_t seed) {
    static const char *strs[] = {"7", "ab", "\"q\"", "\"\\\"\"", "_x9", "42", "\"\""};
    static const int kinds[] = {K_NUM, K_ID, K_STR, K_STR, K_ID, K_NUM, K_STR};
    static const size_t n = sizeof(strs) / sizeof(strs[0]);
    const size_t end = c->len + len;
    for (size_t i = seed; c->len < end; ++i) {
        const size_t l = strlen(strs[i % n]), left = end - c->len;
        if (l + 1 <= left) {
            put_str(c, kinds[i % n], strs[i % n]);
            put_str(c, K_WS, (i & 1) ? "\t" : " ");
        } else {
            for (size_t j = 0; j < left; ++j) put_str(c, K_WS, " ");
        }
    }
}

// Kinds of the long token.
enum { L_NUM, L_ID, L_WS, L_STR, L_ESC, L_UNTERM, L_KINDS };
static const char *long_names[] = {
    "number", "identifier", "whitespace", "string", "escaped string", "unterminated string"
};

// Code units of a string literal body: letters, digits, punctuation, control
// characters and code units above 0x7F (all but '"', '\\' and 0x00).
static const unsigned char body[] = "abcXYZ019 _-.:,;!?\n\t\x01\x7f\x80\xc3\xa9\xfe\xff";

// Append a long token of kind `k` with `n` code units in the loop class.
static void put_long(Case *c, int k, size_t n) {
    unsigned char s[STRSIZE];
    size_t l = 0;
    switch (k) {
    case L_NUM:
        for (size_t i = 0; i < n; ++i) s[l++] = (unsigned char)('0' + (i * 7 + 3) % 10);
        break;
    case L_ID:
        s[l++] = 'k';
        for (size_t i = 1; i < n; ++i) {
            static const char id[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
            s[l++] = (unsigned char)id[(i * 11) % (sizeof(id) - 1)];
        }
        break;
    case L_WS:
        for (size_t i = 0; i < n; ++i) s[l++] = (i % 5 == 3) ? '\t' : ' ';
        break;
    case L_STR:
    case L_UNTERM:
        s[l++] = '"';
        for (size_t i = 0; i < n; ++i) s[l++] = body[(i * 5) % (sizeof(body) - 1)];
        if (k == L_STR) s[l++] = '"';
        break;
    case L_ESC:
        // Escapes at varying distances, so that they fall at different offsets
        // in vector blocks and across refills.
        s[l++] = '"';
        for (size_t i = 0; i < n; ++i) {
            if (i % 9 == 4 || i % 13 == 11) {
                static const unsigned char esc[] = {'"', '\\', 'n', 0xff};
                s[l++] = '\\';
                s[l++] = esc[i % sizeof(esc)];
            } else {
                s[l++] = body[(i * 3) % (sizeof(body) - 1)];
            }
        }
        s[l++] = '"';
        break;
    }
    c->probe = c->len;
    if (k == L_UNTERM) {
        // The lexer backtracks to the opening quote and fails on it.
        put_raw(c, s, l);
        c->status = ERR_CHAR;
    } else {
        put(c, k == L_NUM ? K_NUM : k == L_ID ? K_ID : k == L_WS ? K_WS : K_STR, s, l);
        c->probe = c->toks[c->ntoks - 1].pos; // it may have merged with the prefix
    }
}

// Suffixes after the long token.
enum { S_EOF, S_TOKEN, S_BADCHAR, S_NUL, S_KINDS };

static void put_suffix(Case *c, int s) {
    if (c->status != 0) {
        // The input is already invalid; the suffix is part of the failing lexeme.
        if (s == S_TOKEN) put_raw(c, (const unsigned char*)" end", 4);
        if (s == S_BADCHAR) put_raw(c, (const unsigned char*)"-", 1);
        if (s == S_NUL) put_raw(c, (const unsigned char*)"\0x", 2);
        return;
    }
    switch (s) {
    case S_EOF:
        break;
    case S_TOKEN:
        put_str(c, K_WS, " ");
        put_str(c, K_ID, "end");
        break;
    case S_BADCHAR:
        put_raw(c, (const unsigned char*)"-", 1);
        c->status = ERR_CHAR;
        break;
    case S_NUL:
        put_raw(c, (const unsigned char*)"\0x", 2);
        c->status = ERR_NUL;
        break;
    }
}

// Run a lexer on the test case and compare its tokens and status with the
// expected ones. Returns 1 on failure. Sets `*split` if the buffer was refilled
// in the middle of the long token.
static int run(const char *name, int (*lex)(Input*), const Case *c, int *split) {
    Input in;
    Token toks[MAXTOKS];
    init(&in, c->str, c->len, toks, MAXTOKS);
    const int status = lex(&in);
    const int expected = c->status != 0 ? c->status : c->ntoks;

    int ok = status == expected && in.ntoks == c->ntoks;
    for (int i = 0; ok && i < c->ntoks; ++i) {
        ok = toks[i].kind == c->toks[i].kind
            && toks[i].pos == c->toks[i].pos
            && toks[i].len == c->toks[i].len;
    }
    if (!ok) {
        fprintf(stderr, "%s lexer: status %d (expected %d), %d tokens (expected %d) on input"
            " of length %u:\n", name, status, expected, in.ntoks, c->ntoks, (unsigned)c->len);
        for (int i = 0; i < in.ntoks || i < c->ntoks; ++i) {
            if (i < in.ntoks) {
                fprintf(stderr, "  got (%d, %u, %u)", toks[i].kind, (unsigned)toks[i].pos,
                    (unsigned)toks[i].len);
            } else {
                fprintf(stderr, "  got none");
            }
            if (i < c->ntoks) {
                fprintf(stderr, ", expected (%d, %u, %u)\n", c->toks[i].kind,
                    (unsigned)c->toks[i].pos, (unsigned)c->toks[i].len);
            } else {
                fprintf(stderr, ", expected none\n");
            }
        }
        return 1;
    }

    *split = 0;
    for (int i = 0; i < in.nsplits; ++i) {
        if (in.splits[i] == c->probe) *split = 1;
    }
    return 0;
}

static int test(const Case *c, int *split_v, int *split_s) {
    return run("vector", lex_vector, c, split_v) | run("scalar", lex_scalar, c, split_s);
}

int main() {
    if (!__builtin_cpu_supports("avx2")) return 0;

    // Lengths of the long token (code units in the loop class): around one,
    // two and three vector sizes.
    static const size_t lens[] = {1, 2, 3, 31, 32, 33, 34, 35, 63, 64, 65, 66, 97, 100};
    int covered[L_KINDS][VECSIZE];
    long splits_v = 0, splits_s = 0;
    int failures = 0;
    Case c;

    memset(covered, 0, sizeof(covered));
    for (int k = 0; k < L_KINDS; ++k) {
        for (size_t l = 0; l < sizeof(lens) / sizeof(lens[0]); ++l) {
            for (size_t p = 0; p < BUFSIZE; ++p) {
                for (int s = 0; s < S_KINDS; ++s) {
                    int split_v, split_s;
                    init_case(&c);
                    put_prefix(&c, p, p + l);
                    put_long(&c, k, lens[l]);
                    put_suffix(&c, s);
                    if (test(&c, &split_v, &split_s) != 0) {
                        fprintf(stderr, "  (%s of length %u after a prefix of %u bytes)\n",
                            long_names[k], (unsigned)lens[l], (unsigned)p);
                        if (++failures > 10) return 1;
                        continue;
                    }
                    splits_v += split_v;
                    splits_s += split_s;
                    if (split_v) covered[k][c.probe % VECSIZE] = 1;
                }
            }
        }
    }

    // Every kind of long token must have been split by a refill at every
    // position modulo the vector size.
    for (int k = 0; k < L_KINDS; ++k) {
        for (int m = 0; m < VECSIZE; ++m) {
            if (!covered[k][m]) {
                fprintf(stderr, "no refill inside a %s that starts at %d modulo %d\n",
                    long_names[k], m, VECSIZE);
                ++failures;
            }
        }
    }
    if (splits_v == 0 || splits_s == 0) {
        fprintf(stderr, "no refills in the middle of a token\n");
        ++failures;
    }

    // Two long lexemes separated by a space do not fit into the buffer
    // together, so the second one is refilled in the middle.
    for (size_t n = 0; n <= 100; ++n) {
        unsigned char s[100];
        int split_v, split_s;
        init_case(&c);
        memset(s, 'a', n);
        if (n > 0) put(&c, K_ID, s, n);
        put_str(&c, K_WS, " ");
        memset(s, '9', 100);
        put(&c, K_NUM, s, 100);
        c.probe = c.toks[c.ntoks - 1].pos;
        failures += test(&c, &split_v, &split_s);
        if (n >= 30 && !split_v) {
            fprintf(stderr, "no refill inside the number after an identifier of length %u\n",
                (unsigned)n);
            ++failures;
        }
    }

    // A lexeme longer than the buffer is an error.
    for (int k = 0; k < L_KINDS; ++k) {
        int split_v, split_s;
        init_case(&c);
        put_str(&c, K_ID, "x");
        put_str(&c, K_WS, " ");
        put_long(&c, k, 2 * BUFSIZE);
        put_suffix(&c, S_TOKEN);
        // The tokens before the long one: "x" and the space (unless the long
        // token is whitespace and includes the space).
        c.status = ERR_FILL;
        c.ntoks = k == L_WS ? 1 : 2;
        failures += test(&c, &split_v, &split_s);
    }

    return failures == 0 ? 0 : 1;
}
