#ifndef _RE2C_BENCHMARKS_C_RAGEL_BASE_
#define _RE2C_BENCHMARKS_C_RAGEL_BASE_

// turn off some warnings for ragel-generated code that we don't control
#pragma GCC diagnostic ignored "-Wmisleading-indentation"

#include <assert.h>
#include <benchmark/benchmark.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

struct Input {
    FILE *file;
    char *buf, *p, *pe, *end, *ts, *te;
    int act;
};

static inline bool init_input_simple(Input *in, const char *fname) {
    FILE* f = fopen(fname, "rb");
    if (f == nullptr) {
        in->p = in->pe = in->end = in->buf = nullptr;
        return false;
    }

    fseek(f, 0, SEEK_END);
    size_t flen = (size_t) ftell(f);
    fseek(f, 0, SEEK_SET);

    in->file = nullptr; // unused
    in->buf = (char*) malloc(flen + 1);
    in->p = in->ts = in->te = in->buf;
    in->pe = in->end = in->buf + flen;
    in->act = 0;

    fread(in->buf, 1, flen, f);
    in->buf[flen] = 0;

    fclose(f);
    return true;
}

static inline bool init_input_buffered(Input *in, const char *fname) {
    in->file = fopen(fname, "rb");
    if (in->file == nullptr) {
        in->p = in->ts = in->te = in->pe = in->end = in->buf = nullptr;
        return false;
    }
    in->buf = (char*) malloc(SIZE);
    in->p = in->ts = in->te = in->pe = in->end = in->buf;
    return true;
}

static inline void free_input(Input *in) {
    if (in->file) fclose(in->file);
    free(in->buf);
}

#define RUN_simple() \
    count = lex(&in, 0); \
    /* assert(in.pe == in.p); */ \
    assert(in.pe[0] == '\0');

#define RUN_buffered() \
    const size_t ndelim = strlen(delim); \
    count = 0; \
    while (1) { \
        size_t space = SIZE - (in.end - in.buf); \
        if (space == 0) { \
            error = "no space in buffer"; \
            goto end; \
        } \
        in.end += fread(in.end, 1, space, in.file); \
        \
        /* Find the last delimiter string by searching backwards. */ \
        for (in.pe = in.end; ; --in.pe) { \
            if (in.pe - in.p < (long) ndelim) { \
                error = "can't find delimiter"; \
                goto end; \
            } else if (memcmp(in.pe - ndelim, delim, ndelim) == 0) { \
                break; \
            } \
        } \
        count = lex(&in, count); \
        \
        /* If the buffer is not full, this is the end of input. */ \
        if (in.end < in.buf + SIZE) { \
            if (in.pe != in.end) { \
                error = "text left at the end of buffer"; \
                goto end; \
            } \
            break; \
        } \
        /* Shift the remaining tail to the beginning of buffer. */ \
        size_t left = in.end - in.pe; \
        memmove(in.buf, in.pe, left); \
        in.p = in.ts = in.te = in.buf; \
        in.pe = in.end = in.buf + left; \
    } \
end:

#define RAGEL_BENCH(suffix) \
void bench_##suffix::operator()(benchmark::State &state, const char* input, long expected) const { \
    long count = 0; \
    const char *error = nullptr; \
    for (auto _ : state) { \
        Input in; \
        if (!init_input_##suffix(&in, input)) { \
            state.SkipWithError("ragel: cannot open file"); \
        } \
        RUN_##suffix() \
        free_input(&in); \
    } \
    if (error != nullptr) state.SkipWithError(error); \
    if (count != expected) state.SkipWithError("ragel: wrong count"); \
}

#define RAGEL_TEST(suffix) \
bool test_##suffix(const char* input, long expected) { \
    long count = 0; \
    const char *error = nullptr; \
    Input in; \
    if (!init_input_##suffix(&in, input)) { \
        fprintf(stderr, "ragel: cannot open file"); \
        return false; \
    } \
    RUN_##suffix() \
    free_input(&in); \
    if (error != nullptr) { \
        fprintf(stderr, "ragel: error: %s\n", error); \
        return false; \
    } \
    if (count != expected) { \
        fprintf(stderr, "ragel: wrong count: %ld\n", count); \
        return false; \
    } \
    return true; \
}

// turn off some warnings for ragel-generated code that we don't control
#pragma GCC diagnostic ignored "-Wmisleading-indentation"

#define RAGEL_BENCH_AND_TEST() \
    RAGEL_BENCH(simple) \
    RAGEL_BENCH(buffered) \
    RAGEL_TEST(simple) \
    RAGEL_TEST(buffered)

#define BENCH(name) \
namespace ragel_##name { \
    struct bench_simple { \
        void operator()(benchmark::State &state, const char* input, long expected) const; \
    }; \
    struct bench_buffered { \
        void operator()(benchmark::State &state, const char* input, long expected) const; \
    }; \
    bool test_simple(const char* input, long expected); \
    bool test_buffered(const char* input, long expected); \
}
BENCH(lex_00__numbers1)
BENCH(lex_01__numbers2)
BENCH(lex_02__words1)
BENCH(lex_03__words2)
BENCH(lex_04__words3)
BENCH(submatch_00__http_rfc7230)
BENCH(submatch_01__http_simple)
BENCH(submatch_02__uri_rfc3986)
BENCH(submatch_03__uri_simple)
BENCH(submatch_04__apache_log)
BENCH(submatch_05__datetime)
BENCH(submatch_06__email)
BENCH(submatch_07__ipv4)
BENCH(submatch_10__alt1_2)
BENCH(submatch_11__alt1_4)
BENCH(submatch_12__alt1_8)
BENCH(submatch_13__alt2_2)
BENCH(submatch_14__alt2_4)
BENCH(submatch_15__alt2_8)
BENCH(submatch_16__alt4_2)
BENCH(submatch_17__alt4_4)
BENCH(submatch_18__alt4_8)
BENCH(submatch_20__cat2_0)
BENCH(submatch_21__cat2_4)
BENCH(submatch_22__cat2_8)
BENCH(submatch_23__cat4_0)
BENCH(submatch_24__cat4_2)
BENCH(submatch_25__cat4_4)
BENCH(submatch_26__cat8_0)
BENCH(submatch_27__cat8_1)
BENCH(submatch_28__cat8_2)
BENCH(submatch_30__rep_cat_5_3_2)
BENCH(submatch_31__rep_cat_13_11_7)
BENCH(submatch_32__rep_cat_23_19_17)
BENCH(submatch_33__rep_alt_5_3_2)
BENCH(submatch_34__rep_alt_13_11_7)
BENCH(submatch_35__rep_alt_23_19_17)
BENCH(submatch_36__rep_5_rep_3_rep_2)
BENCH(submatch_37__rep_13_rep_11_rep_7)
BENCH(submatch_38__rep_23_rep_19_rep_17)
#undef BENCH

#endif // _RE2C_BENCHMARKS_C_RAGEL_BASE_
