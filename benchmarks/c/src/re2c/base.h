#ifndef _RE2C_BENCHMARKS_C_RE2C_BASE_
#define _RE2C_BENCHMARKS_C_RE2C_BASE_

#include <assert.h>
#include <benchmark/benchmark.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

struct taglist_t {
    struct taglist_t *pred;
    long dist;
};

struct taglistpool_t {
    taglist_t *head;
    taglist_t *next;
    taglist_t *last;
};

static inline void taglistpool_init(taglistpool_t *tlp) {
    static const unsigned size = 1024 * 1024;
    tlp->head = (taglist_t*)malloc(size * sizeof(taglist_t));
    tlp->next = tlp->head;
    tlp->last = tlp->head + size;
}

static inline void taglistpool_free(taglistpool_t *tlp) {
    free(tlp->head);
    tlp->head = tlp->next = tlp->last = NULL;
}

static inline void taglist(taglist_t **ptl, const char *b, const char *t, taglistpool_t *tlp) {
#ifdef GROW_MTAG_LIST
    if (tlp->next >= tlp->last) {
        const unsigned size = tlp->last - tlp->head;
        taglist_t *head = (taglist_t*)malloc(2 * size * sizeof(taglist_t));
        memcpy(head, tlp->head, size * sizeof(taglist_t));
        free(tlp->head);
        tlp->head = head;
        tlp->next = head + size;
        tlp->last = head + size * 2;
    }
#else
    assert(tlp->next < tlp->last);
#endif
    taglist_t *tl = tlp->next++;
    tl->pred = *ptl;
    tl->dist = t - b;
    *ptl = tl;
}

#define BENCH(name) \
namespace re2c_##name { \
    struct bench_simple { \
        void operator()(benchmark::State &state, const char* input, long expected) const; \
    }; \
    struct bench_buffered_eof { \
        void operator()(benchmark::State &state, const char* input, long expected) const; \
    }; \
    struct bench_buffered_scc { \
        void operator()(benchmark::State &state, const char* input, long expected) const; \
    }; \
    bool test_simple(const char* input, long expected); \
    bool test_buffered_eof(const char* input, long expected); \
    bool test_buffered_scc(const char* input, long expected); \
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

#endif // _RE2C_BENCHMARKS_C_RE2C_BASE_
