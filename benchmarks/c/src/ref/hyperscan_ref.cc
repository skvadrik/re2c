// Hyperscan (https://github.com/intel/hyperscan) block-mode scanning of the vec_* data sets with
// the token regular expressions of re2c/vec_strings_rules.re, as a reference for a SIMD regular
// expression engine. This is NOT the same task as the vec_* lexers: Hyperscan reports the end
// offset of every match of every pattern (e.g. every prefix of an identifier matches `id`, and a
// string literal matches wherever it ends), it does not choose the longest match at the current
// position and does not restart after it, so it does not produce a token stream. The number of
// reported matches is not comparable with the number of tokens.
//
// Built only with -DRE2C_BENCH_HYPERSCAN=ON (Hyperscan or Vectorscan is found with pkg-config as
// `libhs`).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hs.h>

#include "ref/vec_ref.h"

namespace ref_hyperscan {

// The same regular expressions as in re2c/vec_strings_rules.re, except the default rule `*`.
static const char* PATTERNS[] = {
    "\"([^\"\\\\\\n\\x00]|\\\\[^\\n\\x00])*\"",         // str
    "'([^'\\\\\\n\\x00]|\\\\[^\\n\\x00])*'",            // chr
    "//[^\\n\\x00]*",                                    // line_comment
    "/\\*([^*\\x00]|\\*+[^/*\\x00])*\\*+/",              // block_comment
    "[ \\t\\r\\n]+",                                     // ws
    "[a-zA-Z_][a-zA-Z0-9_]*",                            // id
    "[0-9][0-9a-zA-Z_.]*",                               // num
};
static const unsigned NPATTERNS = sizeof(PATTERNS) / sizeof(PATTERNS[0]);

struct db_t {
    hs_database_t *db = nullptr;
    hs_scratch_t *scratch = nullptr;

    db_t() {
        unsigned flags[NPATTERNS], ids[NPATTERNS];
        for (unsigned i = 0; i < NPATTERNS; ++i) {
            flags[i] = 0;
            ids[i] = i + 1;
        }
        hs_compile_error_t *cerr = nullptr;
        if (hs_compile_multi(PATTERNS, flags, ids, NPATTERNS, HS_MODE_BLOCK, nullptr, &db, &cerr)
                != HS_SUCCESS) {
            fprintf(stderr, "hyperscan: cannot compile pattern %d: %s\n",
                cerr->expression, cerr->message);
            hs_free_compile_error(cerr);
            abort();
        }
        if (hs_alloc_scratch(db, &scratch) != HS_SUCCESS) abort();
    }
    ~db_t() {
        hs_free_scratch(scratch);
        hs_free_database(db);
    }
};

struct result_t {
    long matches;
    long sum; // sum of pattern ids, so that the callback cannot be optimized away
};

static int on_match(unsigned id, unsigned long long, unsigned long long, unsigned, void *ctx) {
    result_t *r = static_cast<result_t*>(ctx);
    ++r->matches;
    r->sum += id;
    return 0;
}

static char* load(const char *input, size_t *len) {
    FILE *f = fopen(input, "rb");
    if (!f) abort();
    fseek(f, 0, SEEK_END);
    *len = (size_t) ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = (char*) malloc(*len);
    if (fread(buf, 1, *len, f) != *len) abort();
    fclose(f);
    return buf;
}

static hs_error_t scan(const db_t &db, const char *buf, size_t len, result_t *r) {
    r->matches = r->sum = 0;
    return hs_scan(db.db, buf, (unsigned) len, 0, db.scratch, on_match, r);
}

void bench_block::operator()(benchmark::State &state, const char* input, long) const {
    db_t db;
    size_t len;
    char *buf = load(input, &len);
    result_t r;
    hs_error_t err = HS_SUCCESS;
    for (auto _ : state) {
        err = scan(db, buf, len, &r);
        benchmark::DoNotOptimize(r);
    }
    state.SetBytesProcessed((int64_t)state.iterations() * (int64_t)len);
    state.counters["matches"] = (double) r.matches;
    free(buf);
    if (err != HS_SUCCESS) state.SkipWithError("hyperscan: error");
}

bool test(const char* input) {
    db_t db;
    size_t len;
    char *buf = load(input, &len);
    result_t r;
    hs_error_t err = scan(db, buf, len, &r);
    free(buf);
    if (err != HS_SUCCESS) {
        fprintf(stderr, "hyperscan: scan error %d on %s\n", err, input);
        return false;
    }
    fprintf(stderr, "hyperscan %s: %ld matches on %s\n", hs_version(), r.matches, input);
    return true;
}

} // namespace ref_hyperscan
