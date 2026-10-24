// Hand-written reference lexers for the rules in re2c/vec_strings_rules.re.
//
// They produce exactly the same token stream as the re2c lexers in re2c/vec_base.re (the test
// compares digests of all (length, rule) pairs), using the whole-file-in-memory model with a NUL
// sentinel, like the re2c `sentinel` lexer. Two techniques that a C programmer would use:
//
// - `libc`: string and comment bodies are skipped with the C library (`strcspn` for string
//   literals and line comments, `strstr` for block comments, `strspn` for whitespace), which glibc
//   implements with SSE2/SSE4.2/AVX2 code selected at run time. Identifiers and numbers use a
//   character class table.
// - `switch`: a plain byte-at-a-time lexer with a switch on the first character and scalar loops.
//
// The code is C, compiled as C++ only to share the token sinks (templates) with vec_base.re.

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ref/vec_ref.h"

namespace ref_vec_strings {

enum { C_ID = 1, C_NUM = 2, C_WS = 4 };

// Character classes: C_ID for [a-zA-Z0-9_], C_NUM for [0-9a-zA-Z_.], C_WS for [ \t\r\n].
//
// The table is constant-initialized (a constexpr function expanded for all 256 code units) rather
// than filled by a constructor: this file is compiled with -mavx2, and a dynamic initializer would
// run before main checks that the CPU supports AVX2 (the compiler vectorizes it with AVX2).
static constexpr unsigned char cls_of(int c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
        ? C_ID | C_NUM
        : c == '.' ? C_NUM
        : (c == ' ' || c == '\t' || c == '\r' || c == '\n') ? C_WS
        : 0;
}
#define CLS4(c) cls_of(c), cls_of(c + 1), cls_of(c + 2), cls_of(c + 3)
#define CLS16(c) CLS4(c), CLS4(c + 4), CLS4(c + 8), CLS4(c + 12)
#define CLS64(c) CLS16(c), CLS16(c + 16), CLS16(c + 32), CLS16(c + 48)
static constexpr unsigned char CLS[256] = {CLS64(0), CLS64(64), CLS64(128), CLS64(192)};
#undef CLS64
#undef CLS16
#undef CLS4

// Token sinks, the same as in re2c/vec_base.re.
struct count_sink_t {
    long n = 0;
    inline void token(long k, const char* tok, const char* cur) { n += (cur - tok) * k; }
    long value() const { return n; }
};

struct digest_sink_t {
    uint64_t h = 14695981039346656037ull;
    inline void token(long k, const char* tok, const char* cur) {
        h = (h ^ ((uint64_t)(cur - tok) << 8 | (uint64_t)k)) * 1099511628211ull;
    }
    long value() const { return (long)h; }
};

static const size_t PAD = 64;

struct input_t {
    char *buf;
    size_t len;
};

// Read the whole file into memory and append PAD zero bytes (the first one is the sentinel).
static void init_input(input_t *in, const char *fname) {
    FILE *f = fopen(fname, "rb");
    if (!f) abort();
    fseek(f, 0, SEEK_END);
    size_t flen = (size_t) ftell(f);
    fseek(f, 0, SEEK_SET);
    in->buf = (char*) malloc(flen + PAD);
    in->len = flen;
    if (fread(in->buf, 1, flen, f) != flen) abort();
    memset(in->buf + flen, 0, PAD);
    fclose(f);
}

#define TOKEN(k, end) do { sink.token(k, tok, end); p = end; goto loop; } while (0)

// Lexer based on the C library string functions.
template<typename sink_t>
static int lex_libc(const char *buf, size_t len, sink_t &sink) {
    const char *p = buf, *tok, *q;
    const unsigned char *cls = CLS;
loop:
    tok = p;
    switch ((unsigned char) *p) {
    case 0:
        return p == buf + len ? 0 : -1;
    case '"':
        for (q = p + 1;;) {
            q += strcspn(q, "\"\\\n");
            if (*q == '"') TOKEN(1, q + 1);
            if (*q == '\\' && q[1] != '\n' && q[1] != 0) { q += 2; continue; }
            TOKEN(8, p + 1); // unterminated literal: a single character
        }
    case '\'':
        for (q = p + 1;;) {
            q += strcspn(q, "'\\\n");
            if (*q == '\'') TOKEN(2, q + 1);
            if (*q == '\\' && q[1] != '\n' && q[1] != 0) { q += 2; continue; }
            TOKEN(8, p + 1);
        }
    case '/':
        if (p[1] == '/') {
            q = p + 2;
            TOKEN(3, q + strcspn(q, "\n"));
        } else if (p[1] == '*') {
            q = strstr(p + 2, "*/");
            if (q) TOKEN(4, q + 2);
        }
        TOKEN(8, p + 1);
    case ' ': case '\t': case '\r': case '\n':
        TOKEN(5, p + strspn(p, " \t\r\n"));
    default:
        if (cls[(unsigned char) *p] & C_ID) {
            q = p + 1;
            if (*p >= '0' && *p <= '9') {
                while (cls[(unsigned char) *q] & C_NUM) ++q;
                TOKEN(7, q);
            }
            while (cls[(unsigned char) *q] & C_ID) ++q;
            TOKEN(6, q);
        }
        TOKEN(8, p + 1);
    }
}

// Plain scalar lexer: a switch on the first character and byte-at-a-time loops.
template<typename sink_t>
static int lex_switch(const char *buf, size_t len, sink_t &sink) {
    const char *p = buf, *tok, *q;
    const unsigned char *cls = CLS;
    char c;
loop:
    tok = p;
    switch ((unsigned char) *p) {
    case 0:
        return p == buf + len ? 0 : -1;
    case '"':
        for (q = p + 1;;) {
            c = *q;
            if (c == '"') TOKEN(1, q + 1);
            if (c == '\\') {
                if (q[1] == '\n' || q[1] == 0) break;
                q += 2;
            } else if (c == '\n' || c == 0) {
                break;
            } else {
                ++q;
            }
        }
        TOKEN(8, p + 1);
    case '\'':
        for (q = p + 1;;) {
            c = *q;
            if (c == '\'') TOKEN(2, q + 1);
            if (c == '\\') {
                if (q[1] == '\n' || q[1] == 0) break;
                q += 2;
            } else if (c == '\n' || c == 0) {
                break;
            } else {
                ++q;
            }
        }
        TOKEN(8, p + 1);
    case '/':
        if (p[1] == '/') {
            for (q = p + 2; *q != '\n' && *q != 0; ++q);
            TOKEN(3, q);
        } else if (p[1] == '*') {
            for (q = p + 2; *q != 0; ++q) {
                if (q[0] == '*' && q[1] == '/') TOKEN(4, q + 2);
            }
        }
        TOKEN(8, p + 1);
    case ' ': case '\t': case '\r': case '\n':
        for (q = p + 1; cls[(unsigned char) *q] & C_WS; ++q);
        TOKEN(5, q);
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i':
    case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
    case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I':
    case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
    case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
    case '_':
        for (q = p + 1; cls[(unsigned char) *q] & C_ID; ++q);
        TOKEN(6, q);
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        for (q = p + 1; cls[(unsigned char) *q] & C_NUM; ++q);
        TOKEN(7, q);
    default:
        TOKEN(8, p + 1);
    }
}

#undef TOKEN

bool oracle(const char* input, size_t len, long *count, long *digest) {
    count_sink_t c;
    digest_sink_t d;
    if (lex_switch(input, len, c) != 0 || lex_switch(input, len, d) != 0) return false;
    *count = c.value();
    *digest = d.value();
    return true;
}

// The input file is read once before the benchmark loop, as in re2c in-memory benchmarks.
#define FN_BENCH(suffix) \
void bench_##suffix::operator()( \
        benchmark::State &state, const char* input, long expected) const { \
    input_t in; \
    init_input(&in, input); \
    long count = 0; \
    int status = 0; \
    for (auto _ : state) { \
        count_sink_t sink; \
        status = lex_##suffix(in.buf, in.len, sink); \
        count = sink.value(); \
        benchmark::ClobberMemory(); \
    } \
    state.SetBytesProcessed((int64_t)state.iterations() * (int64_t)in.len); \
    free(in.buf); \
    if (status != 0 || count != expected) state.SkipWithError("ref: error"); \
}
FN_BENCH(libc)
FN_BENCH(switch)
#undef FN_BENCH

// Check that the reference lexers produce the same token stream as the re2c lexers (`*ref` is the
// digest computed by re2c lexers on the same input, or 0 if they have not been tested).
bool test(const char* input, long expected, long *ref) {
    static const char* names[] = {"libc", "switch"};
    input_t in;
    init_input(&in, input);
    int status[2];
    long digest[2], count[2];
    {
        digest_sink_t d; count_sink_t c;
        status[0] = lex_libc(in.buf, in.len, d); digest[0] = d.value();
        lex_libc(in.buf, in.len, c); count[0] = c.value();
    }
    {
        digest_sink_t d; count_sink_t c;
        status[1] = lex_switch(in.buf, in.len, d); digest[1] = d.value();
        lex_switch(in.buf, in.len, c); count[1] = c.value();
    }
    free(in.buf);

    bool ok = true;
    if (*ref == 0) *ref = digest[0];
    for (int i = 0; i < 2; ++i) {
        if (status[i] != 0) {
            fprintf(stderr, "ref %s: syntax error on %s\n", names[i], input);
            ok = false;
        }
        if (digest[i] != *ref) {
            fprintf(stderr, "ref %s: token stream differs from reference on %s"
                " (digest %lx, expected %lx)\n", names[i], input, digest[i], *ref);
            ok = false;
        }
        if (count[i] != expected) {
            fprintf(stderr, "ref %s: wrong count on %s, expected %ld, got %ld\n", names[i],
                input, expected, count[i]);
            ok = false;
        }
    }
    return ok;
}

} // namespace ref_vec_strings
