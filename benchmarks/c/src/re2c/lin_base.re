// Common driver for benchmarks of `--vectorize-linear` (`re2c:vectorize:linear` configuration).
//
// It is included by lin_*.re files, which define the lexer rules in a `rules:re2c:main` block. All
// lexers are generated from the same rules and differ only in the input model and in the value
// of `re2c:vectorize:linear`:
//
//   - `sentinel-{scalar,linear}`: the whole file is in memory, padded with YYMAXFILL zero bytes,
//     YYFILL is disabled and YYLIMIT is set to the end of the padded buffer.
//   - `bounded-{scalar,linear}`: the whole file is in memory, padded with YYMAXFILL zero bytes,
//     with bounds checks (YYFILL returns an error, it is never called on valid input).
//   - `buffered-{scalar,linear}`: the input is read in chunks into a fixed-size buffer with
//     YYFILL (padding with YYMAXFILL zero bytes at the end, as in base.re `buffered_scc`).
//
// Included inside a benchmark namespace after <stdint.h>, <stdio.h>, <stdlib.h>, and <string.h>.

/*!rules:re2c:linbase
    re2c:api:style = free-form;
    re2c:YYCTYPE   = "unsigned char";
*/

/*!max:re2c*/

struct input_t {
    FILE* file;
    const char *mem;
    size_t mem_pos;
    char *buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    size_t len;
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
    uint64_t value() const { return h; }
};

static inline void free_input(input_t *in) {
    free(in->buf);
    if (in->file) fclose(in->file);
}

static inline int fill_buffered(input_t *in, size_t need) {
    if (in->eof) return 1;

    size_t avail = in->tok - in->buf;
    if (avail < need) return 2;

    memmove(in->buf, in->tok, in->lim - in->tok);
    in->lim -= avail;
    in->cur -= avail;
    if (in->mar >= in->tok) in->mar -= avail;
    in->tok -= avail;

    size_t nread = 0;
    if (in->file) {
        nread = fread(in->lim, 1, avail, in->file);
    } else if (in->mem) {
        size_t rem = in->len - in->mem_pos;
        nread = rem < avail ? rem : avail;
        if (nread > 0) {
            memcpy(in->lim, in->mem + in->mem_pos, nread);
            in->mem_pos += nread;
        }
    }
    in->lim += nread;

    if (in->lim < in->buf + SIZE) {
        in->eof = 1;
        memset(in->lim, 0, YYMAXFILL);
        in->lim += YYMAXFILL;
    }

    return 0;
}

static inline void init_input_memory(input_t *in, const char* fname) {
    FILE* f = fopen(fname, "rb");
    if (!f) abort();

    if (fseek(f, 0, SEEK_END) != 0) abort();
    long pos = ftell(f);
    if (pos < 0) abort();
    size_t flen = (size_t) pos;
    if (fseek(f, 0, SEEK_SET) != 0) abort();

    in->file = nullptr;
    in->mem = nullptr;
    in->mem_pos = 0;
    in->buf = (char*) malloc(flen + YYMAXFILL);
    if (!in->buf) abort();
    in->lim = in->buf + flen + YYMAXFILL;
    in->cur = in->mar = in->tok = in->buf;
    in->len = flen;
    in->eof = 0;

    if (fread(in->buf, 1, flen, f) != flen) abort();
    memset(in->buf + flen, 0, YYMAXFILL);

    fclose(f);
}

static inline void init_input_buffered(input_t *in, const char* fname) {
    in->file = fopen(fname, "rb");
    if (!in->file) abort();
    in->mem = nullptr;
    in->mem_pos = 0;
    in->buf = (char*) malloc(SIZE + YYMAXFILL);
    if (!in->buf) abort();
    in->lim = in->buf + SIZE;
    in->cur = in->lim;
    in->mar = in->lim;
    in->tok = in->lim;
    in->len = 0;
    in->eof = 0;
}

static inline void init_input_buffered_mem(input_t *in, const char* data, size_t len) {
    in->file = nullptr;
    in->mem = data;
    in->mem_pos = 0;
    in->buf = (char*) malloc(SIZE + YYMAXFILL);
    if (!in->buf) abort();
    in->lim = in->buf + SIZE;
    in->cur = in->lim;
    in->mar = in->lim;
    in->tok = in->lim;
    in->len = len;
    in->eof = 0;
}

#define TOKEN(k) do { sink.token(k, YYTOKEN, YYCURSOR); goto loop; } while (0)

#define YYCURSOR cur
#define YYMARKER mar
#define YYLIMIT lim
#define YYTOKEN tok

template<typename sink_t>
int lex_sentinel_scalar(const input_t *in, sink_t &sink) {
    const char *cur = in->buf, *lim = in->lim, *mar, *tok;
    (void) lim;
    (void) mar;
loop:
    tok = cur;
    /*!local:re2c
        re2c:yyfill:enable = 0;
        re2c:YYLIMIT = lim;
        re2c:vectorize:linear = 0;

        "\x00" { return cur - 1 == in->buf + in->len ? 0 : -1; }

        !use:linbase;
        !use:main;
    */
}

template<typename sink_t>
int lex_sentinel_linear(const input_t *in, sink_t &sink) {
    const char *cur = in->buf, *lim = in->lim, *mar, *tok;
    (void) mar;
loop:
    tok = cur;
    /*!local:re2c
        re2c:yyfill:enable = 0;
        re2c:YYLIMIT = lim;
        re2c:vectorize:linear = 1;

        "\x00" { return cur - 1 == in->buf + in->len ? 0 : -1; }

        !use:linbase;
        !use:main;
    */
}

template<typename sink_t>
int lex_bounded_scalar(const input_t *in, sink_t &sink) {
    const char *cur = in->buf, *lim = in->lim, *mar, *tok;
    (void) mar;
loop:
    tok = cur;
    /*!local:re2c
        re2c:YYFILL = "return -2;";
        re2c:vectorize:linear = 0;

        "\x00" { return cur - 1 == in->buf + in->len ? 0 : -1; }

        !use:linbase;
        !use:main;
    */
}

template<typename sink_t>
int lex_bounded_linear(const input_t *in, sink_t &sink) {
    const char *cur = in->buf, *lim = in->lim, *mar, *tok;
    (void) mar;
loop:
    tok = cur;
    /*!local:re2c
        re2c:YYFILL = "return -2;";
        re2c:vectorize:linear = 1;

        "\x00" { return cur - 1 == in->buf + in->len ? 0 : -1; }

        !use:linbase;
        !use:main;
    */
}

#undef YYCURSOR
#undef YYMARKER
#undef YYLIMIT
#undef YYTOKEN

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
        re2c:vectorize:linear = 0;

        "\x00" { return (in->eof && in->cur - 1 == in->lim - YYMAXFILL) ? 0 : -1; }

        !use:linbase;
        !use:main;
    */
}

template<typename sink_t>
int lex_buffered_linear(input_t *in, sink_t &sink) {
loop:
    in->tok = in->cur;
    /*!local:re2c
        re2c:YYFILL = "if (fill_buffered(in, @@) != 0) return -2;";
        re2c:vectorize:linear = 1;

        "\x00" { return (in->eof && in->cur - 1 == in->lim - YYMAXFILL) ? 0 : -1; }

        !use:linbase;
        !use:main;
    */
}

#undef YYCURSOR
#undef YYMARKER
#undef YYLIMIT
#undef YYTOKEN
#undef TOKEN

#define FN_BENCH_MEMORY(suffix) \
void bench_##suffix::operator()( \
        benchmark::State &state, const char* input, long expected) const { \
    input_t in; \
    init_input_memory(&in, input); \
    long count = 0; \
    int status = 0; \
    for (auto _ : state) { \
        count_sink_t sink; \
        status |= lex_##suffix(&in, sink); \
        count = sink.value(); \
        benchmark::DoNotOptimize(count); \
        benchmark::ClobberMemory(); \
    } \
    state.SetBytesProcessed((int64_t)state.iterations() * (int64_t)in.len); \
    free_input(&in); \
    if (status != 0 || count != expected) state.SkipWithError("re2c: error"); \
}
FN_BENCH_MEMORY(sentinel_scalar)
FN_BENCH_MEMORY(sentinel_linear)
FN_BENCH_MEMORY(bounded_scalar)
FN_BENCH_MEMORY(bounded_linear)
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
        status |= lex_##suffix(&in, sink); \
        count = sink.value(); \
        benchmark::DoNotOptimize(count); \
        if (fseek(in.file, 0, SEEK_END) != 0) abort(); \
        long pos = ftell(in.file); \
        if (pos < 0) abort(); \
        len = (size_t) pos; \
        free_input(&in); \
    } \
    state.SetBytesProcessed((int64_t)state.iterations() * (int64_t)len); \
    if (status != 0 || count != expected) state.SkipWithError("re2c: error"); \
}
FN_BENCH_BUFFERED(buffered_scalar)
FN_BENCH_BUFFERED(buffered_linear)
#undef FN_BENCH_BUFFERED

bool test(const char* input, long expected) {
    static const char* names[] = {
        "sentinel-scalar", "sentinel-linear",
        "bounded-scalar", "bounded-linear",
        "buffered-scalar", "buffered-linear"
    };
    int status[6];
    uint64_t digest[6];
    long count[6];
    input_t in;

    init_input_memory(&in, input);
    {
        digest_sink_t d; count_sink_t c;
        int s = lex_sentinel_scalar(&in, d);
        int sc = lex_sentinel_scalar(&in, c);
        status[0] = s != 0 ? s : sc;
        digest[0] = d.value(); count[0] = c.value();
    }
    {
        digest_sink_t d; count_sink_t c;
        int s = lex_sentinel_linear(&in, d);
        int sc = lex_sentinel_linear(&in, c);
        status[1] = s != 0 ? s : sc;
        digest[1] = d.value(); count[1] = c.value();
    }
    {
        digest_sink_t d; count_sink_t c;
        int s = lex_bounded_scalar(&in, d);
        int sc = lex_bounded_scalar(&in, c);
        status[2] = s != 0 ? s : sc;
        digest[2] = d.value(); count[2] = c.value();
    }
    {
        digest_sink_t d; count_sink_t c;
        int s = lex_bounded_linear(&in, d);
        int sc = lex_bounded_linear(&in, c);
        status[3] = s != 0 ? s : sc;
        digest[3] = d.value(); count[3] = c.value();
    }
    free_input(&in);

    {
        digest_sink_t d; count_sink_t c;
        init_input_buffered(&in, input);
        int s = lex_buffered_scalar(&in, d); digest[4] = d.value();
        free_input(&in);
        init_input_buffered(&in, input);
        int sc = lex_buffered_scalar(&in, c); count[4] = c.value();
        free_input(&in);
        status[4] = s != 0 ? s : sc;
    }
    {
        digest_sink_t d; count_sink_t c;
        init_input_buffered(&in, input);
        int s = lex_buffered_linear(&in, d); digest[5] = d.value();
        free_input(&in);
        init_input_buffered(&in, input);
        int sc = lex_buffered_linear(&in, c); count[5] = c.value();
        free_input(&in);
        status[5] = s != 0 ? s : sc;
    }

    bool ok = true;
    for (int i = 0; i < 6; ++i) {
        if (status[i] != 0) {
            fprintf(stderr, "re2c %s: %s error on %s\n", names[i],
                status[i] == -2 ? "yyfill" : "syntax", input);
            ok = false;
        }
        if (digest[i] != digest[0]) {
            fprintf(stderr, "re2c %s: token stream differs from sentinel-scalar on %s"
                " (digest %llx, expected %llx)\n", names[i], input,
                (unsigned long long)digest[i], (unsigned long long)digest[0]);
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
