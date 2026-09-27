// Common driver for benchmarks of `--vectorize-loops` (`re2c:vectorize:loops` configuration).
//
// It is included by vec_*.re files, which define the lexer rules in a `rules:re2c:main` block. All
// lexers are generated from the same rules and differ only in the input model and in the value
// of `re2c:vectorize:loops`:
//
//   - `sentinel`: the whole file is in memory, the end of input is a NUL sentinel and there are
//     no bounds checks (YYFILL is disabled). This is the fastest scalar lexer and a baseline for
//     the others; it cannot be vectorized, as vectorization needs bounds checks.
//   - `bounded-{scalar,vector}`: the whole file is in memory, padded with YYMAXFILL zero bytes,
//     with bounds checks (YYFILL returns an error, it is never called on valid input).
//   - `buffered-{scalar,vector}`: the input is read in chunks into a fixed-size buffer with
//     YYFILL (padding with YYMAXFILL zero bytes at the end, as in base.re `buffered_scc`).
//
// The generated code uses AVX2 intrinsics (see `code:vector_loop` in include/syntax/c), so the
// file must be compiled with `-mavx2`, and the benchmark must not be run on a CPU without AVX2.
//
// Semantic actions use the TOKEN(k) macro, where `k` is the rule identifier. Lexers are templates
// parameterized with a token sink: benchmarks use a cheap counter (sum of token lengths
// multiplied by `k`), the test uses an order-sensitive digest of all (length, rule) pairs, which
// determines the tokenization completely.

#include <immintrin.h>

/*!rules:re2c:vecbase
    re2c:api:style = free-form;
    re2c:YYCTYPE   = char;
*/

/*!max:re2c*/

struct input_t {
    FILE* file;
    char *buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    size_t len; // file length (in-memory models only)
    int eof;
};

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

static inline void free_input(input_t *in) {
    free(in->buf);
    if (in->file) fclose(in->file);
}

static inline int fill_buffered(input_t *in, size_t need) {
    size_t free;
    if (in->eof) return 1;

    // The current token and the `need` code units that the lexer wants to read after it must fit
    // into the buffer, otherwise the token is too long (this is an error, not an assertion, so
    // that it is also checked with NDEBUG).
    free = in->tok - in->buf;
    if (free < need) return 2;

    memmove(in->buf, in->tok, in->lim - in->tok);
    in->lim -= free;
    in->cur -= free;
    // The marker is rebased only if it points into the kept part of the buffer (it may be left
    // over from a previous token, and moving it before the buffer would be undefined behavior).
    if (in->mar >= in->tok) in->mar -= free;
    in->tok -= free;

    in->lim += fread(in->lim, 1, free, in->file);

    if (in->lim < in->buf + SIZE) {
        in->eof = 1;
        memset(in->lim, 0, YYMAXFILL);
        in->lim += YYMAXFILL;
    }

    return 0;
}

// Read the whole file into memory and append YYMAXFILL zero bytes (the first one is the sentinel).
static inline void init_input_memory(input_t *in, const char* fname) {
    FILE* f = fopen(fname, "rb");

    fseek(f, 0, SEEK_END);
    size_t flen = (size_t) ftell(f);
    fseek(f, 0, SEEK_SET);

    in->file = nullptr; // unused
    in->buf = (char*) malloc(flen + YYMAXFILL);
    in->lim = in->buf + flen + YYMAXFILL;
    in->cur = in->mar = in->tok = in->buf;
    in->len = flen;
    in->eof = 0; // unused

    if (fread(in->buf, 1, flen, f) != flen) abort();
    memset(in->buf + flen, 0, YYMAXFILL);

    fclose(f);
}

static inline void init_input_buffered(input_t *in, const char* fname) {
    in->file = fopen(fname, "rb");
    in->buf = (char*) malloc(SIZE + YYMAXFILL);
    in->lim = in->buf + SIZE;
    in->cur = in->lim;
    in->mar = in->lim;
    in->tok = in->lim;
    in->len = 0; // unused
    in->eof = 0;
}

#define TOKEN(k) do { sink.token(k, YYTOKEN, YYCURSOR); goto loop; } while (0)

// In-memory lexers: local variables for the cursor, marker and limit.
#define YYCURSOR cur
#define YYMARKER mar
#define YYLIMIT lim
#define YYTOKEN tok

template<typename sink_t>
int lex_sentinel(const input_t *in, sink_t &sink) {
    const char *cur = in->buf, *mar, *tok;
    (void) mar; // maybe unused
loop:
    tok = cur;
    /*!local:re2c
        re2c:yyfill:enable = 0;
        re2c:vectorize:loops = 0;

        "\x00" { return cur - 1 == in->buf + in->len ? 0 : -1; }

        !use:vecbase;
        !use:main;
    */
}

template<typename sink_t>
int lex_bounded_scalar(const input_t *in, sink_t &sink) {
    const char *cur = in->buf, *lim = in->lim, *mar, *tok;
    (void) mar; // maybe unused
loop:
    tok = cur;
    /*!local:re2c
        re2c:YYFILL = "return -2;";
        re2c:vectorize:loops = 0;

        "\x00" { return cur - 1 == in->buf + in->len ? 0 : -1; }

        !use:vecbase;
        !use:main;
    */
}

template<typename sink_t>
int lex_bounded_vector(const input_t *in, sink_t &sink) {
    const char *cur = in->buf, *lim = in->lim, *mar, *tok;
    (void) mar; // maybe unused
loop:
    tok = cur;
    /*!local:re2c
        re2c:YYFILL = "return -2;";
        re2c:vectorize:loops = 1;

        "\x00" { return cur - 1 == in->buf + in->len ? 0 : -1; }

        !use:vecbase;
        !use:main;
    */
}

#undef YYCURSOR
#undef YYMARKER
#undef YYLIMIT
#undef YYTOKEN

// Buffered lexers: the cursor, marker and limit are stored in the input structure.
#define YYCURSOR in->cur
#define YYMARKER in->mar
#define YYLIMIT in->lim
#define YYTOKEN in->tok

template<typename sink_t>
int lex_buffered_scalar(input_t *in, sink_t &sink) {
loop:
    in->tok = in->cur;
    /*!local:re2c
        re2c:YYFILL = "if (fill_buffered(in, @@) != 0) return -2;";
        re2c:vectorize:loops = 0;

        "\x00" { return 0; }

        !use:vecbase;
        !use:main;
    */
}

template<typename sink_t>
int lex_buffered_vector(input_t *in, sink_t &sink) {
loop:
    in->tok = in->cur;
    /*!local:re2c
        re2c:YYFILL = "if (fill_buffered(in, @@) != 0) return -2;";
        re2c:vectorize:loops = 1;

        "\x00" { return 0; }

        !use:vecbase;
        !use:main;
    */
}

#undef YYCURSOR
#undef YYMARKER
#undef YYLIMIT
#undef YYTOKEN
#undef TOKEN

// In-memory benchmarks exclude reading the file from the measurement (it is read once before the
// benchmark loop), so that they measure only the lexer. Buffered benchmarks include reading the
// file in chunks, as in base.re.
#define FN_BENCH_MEMORY(suffix) \
void bench_##suffix::operator()( \
        benchmark::State &state, const char* input, long expected) const { \
    input_t in; \
    init_input_memory(&in, input); \
    long count = 0; \
    int status = 0; \
    for (auto _ : state) { \
        count_sink_t sink; \
        status = lex_##suffix(&in, sink); \
        count = sink.value(); \
        benchmark::ClobberMemory(); /* the lexer must be rerun in each iteration */ \
    } \
    state.SetBytesProcessed((int64_t)state.iterations() * (int64_t)in.len); \
    free_input(&in); \
    if (status != 0 || count != expected) state.SkipWithError("re2c: error"); \
}
FN_BENCH_MEMORY(sentinel)
FN_BENCH_MEMORY(bounded_scalar)
FN_BENCH_MEMORY(bounded_vector)
#undef FN_BENCH_MEMORY

#define FN_BENCH_BUFFERED(suffix) \
void bench_##suffix::operator()( \
        benchmark::State &state, const char* input, long expected) const { \
    long count = 0; \
    int status = 0; \
    size_t len = 0; \
    for (auto _ : state) { \
        input_t in; \
        init_input_buffered(&in, input); \
        count_sink_t sink; \
        status = lex_##suffix(&in, sink); \
        count = sink.value(); \
        fseek(in.file, 0, SEEK_END); \
        len = (size_t) ftell(in.file); \
        free_input(&in); \
    } \
    state.SetBytesProcessed((int64_t)state.iterations() * (int64_t)len); \
    if (status != 0 || count != expected) state.SkipWithError("re2c: error"); \
}
FN_BENCH_BUFFERED(buffered_scalar)
FN_BENCH_BUFFERED(buffered_vector)
#undef FN_BENCH_BUFFERED

// Run all lexers on the given input and check that they produce exactly the same sequence of
// tokens (the same digest), no errors, and the expected count (the same as in benchmarks).
// If `*ref` is nonzero, it is the digest of a lexer tested before on the same input (possibly by a
// different implementation of the same rules), and all digests must be equal to it; otherwise it
// is set to the digest of the sentinel lexer.
bool test(const char* input, long expected, long *ref) {
    static const char* names[] = {
        "sentinel", "bounded-scalar", "bounded-vector", "buffered-scalar", "buffered-vector"
    };
    int status[5];
    long digest[5], count[5];
    input_t in;

    init_input_memory(&in, input);
    {
        digest_sink_t d; count_sink_t c;
        status[0] = lex_sentinel(&in, d); digest[0] = d.value();
        lex_sentinel(&in, c); count[0] = c.value();
    }
    {
        digest_sink_t d; count_sink_t c;
        status[1] = lex_bounded_scalar(&in, d); digest[1] = d.value();
        lex_bounded_scalar(&in, c); count[1] = c.value();
    }
    {
        digest_sink_t d; count_sink_t c;
        status[2] = lex_bounded_vector(&in, d); digest[2] = d.value();
        lex_bounded_vector(&in, c); count[2] = c.value();
    }
    free_input(&in);

    {
        digest_sink_t d; count_sink_t c;
        init_input_buffered(&in, input);
        status[3] = lex_buffered_scalar(&in, d); digest[3] = d.value();
        free_input(&in);
        init_input_buffered(&in, input);
        lex_buffered_scalar(&in, c); count[3] = c.value();
        free_input(&in);
    }
    {
        digest_sink_t d; count_sink_t c;
        init_input_buffered(&in, input);
        status[4] = lex_buffered_vector(&in, d); digest[4] = d.value();
        free_input(&in);
        init_input_buffered(&in, input);
        lex_buffered_vector(&in, c); count[4] = c.value();
        free_input(&in);
    }

    bool ok = true;
    if (*ref == 0) *ref = digest[0];
    for (int i = 0; i < 5; ++i) {
        if (status[i] != 0) {
            fprintf(stderr, "re2c %s: %s error on %s\n", names[i],
                status[i] == -2 ? "yyfill" : "syntax", input);
            ok = false;
        }
        if (digest[i] != *ref) {
            fprintf(stderr, "re2c %s: token stream differs from reference on %s"
                " (digest %lx, expected %lx)\n", names[i], input, digest[i], *ref);
            ok = false;
        }
        if (count[i] != expected) {
            fprintf(stderr, "re2c %s: wrong count on %s, expected %ld, got %ld\n", names[i],
                input, expected, count[i]);
            ok = false;
        }
    }
    return ok;
}
