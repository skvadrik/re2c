// re2c $INPUT -o $OUTPUT -i --vectorize-loops
// The vector block of the default `code:vector_loop` is entered only if the
// current code unit is in the loop class, so that runs that end right away are
// left to the scalar dispatcher. The scalar test uses the class complement,
// which here contains single code units (0x00, '"', 0xFF) and a range that
// crosses 0x80 (0x7F-0x9F). The program checks that the vector and the scalar
// lexers produce the expected tokens for runs of every length up to 100 that
// end with every code unit of the complement, including runs of length one.
// A third lexer (the vector one with YYDEBUG) counts the states it visits, and
// the program checks that the vector block moves the cursor to the exit code
// unit: the scalar loop state must not be visited again for the rest of the run.
#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lexer status: token kinds, and a refill error for unpadded input.
enum { T_END = 0, T_RUN = 1, T_OTHER = 2, E_FILL = -1 };

/*!rules:re2c:common
    re2c:api:style = free-form;
    re2c:YYCTYPE = "unsigned char";
    re2c:YYCURSOR = cur;
    re2c:YYLIMIT = lim;
    re2c:YYFILL = "{ ret = E_FILL; goto done; }";
    re2c:YYFILL:naked = 1;

    [^\x00"\x7F-\x9F\xFF]+ { ret = T_RUN; goto done; }
    [\x00]                 { ret = T_END; goto done; }
    *                      { ret = T_OTHER; goto done; }
*/

__attribute__((target("avx2")))
static int lex_vector(const unsigned char *str, const unsigned char *lim, const unsigned char **pos) {
    const unsigned char *cur = str;
    int ret;
    /*!use:re2c:common
        re2c:vectorize:loops = 1;
    */
done:
    *pos = cur;
    return ret;
}

static int lex_scalar(const unsigned char *str, const unsigned char *lim, const unsigned char **pos) {
    const unsigned char *cur = str;
    int ret;
    /*!use:re2c:common
        re2c:vectorize:loops = 0;
    */
done:
    *pos = cur;
    return ret;
}

// The number of states visited by the lexer below.
static unsigned steps;

#define YYDEBUG(state, c) ++steps

__attribute__((target("avx2")))
static int lex_vector_debug(const unsigned char *str, const unsigned char *lim, const unsigned char **pos) {
    const unsigned char *cur = str;
    int ret;
    /*!use:re2c:common
        re2c:vectorize:loops = 1;
        re2c:debug-output = 1;
    */
done:
    *pos = cur;
    return ret;
}

typedef int (*lexer_t)(const unsigned char*, const unsigned char*, const unsigned char**);

// Lex the whole input with the lexer and compare the tokens (the status and
// the end offset of each one) with the expected ones.
static int test(const char *name, lexer_t lex, const unsigned char *str, size_t len,
        const int *kinds, const size_t *ends, int ntoks) {
    const unsigned char *lim = str + len, *cur = str;
    for (int i = 0;; ++i) {
        const unsigned char *pos;
        const int ret = lex(cur, lim, &pos);
        if (i == ntoks || ret != kinds[i] || (size_t)(pos - str) != ends[i]) {
            fprintf(stderr, "%s lexer: token %d is (%d, %u), expected ", name, i, ret,
                (unsigned)(pos - str));
            if (i == ntoks) {
                fprintf(stderr, "none");
            } else {
                fprintf(stderr, "(%d, %u)", kinds[i], (unsigned)ends[i]);
            }
            fprintf(stderr, " on input of length %u\n", (unsigned)len);
            return 1;
        }
        if (ret == T_END) return i + 1 == ntoks ? 0 : 1;
        cur = pos;
    }
}

int main() {
    if (!__builtin_cpu_supports("avx2")) return 0;

    static const unsigned char runs[] = {'a', 0x01, 0x7E, 0xA0, 0xFE};
    static const unsigned char exits[] = {0x00, '"', 0x7F, 0x80, 0x9F, 0xFF};
    unsigned char str[256];
    int failures = 0;

    for (size_t r = 0; r < sizeof(runs); ++r) {
        for (size_t e = 0; e < sizeof(exits); ++e) {
            for (size_t n = 0; n <= 100; ++n) {
                // A run, an exit code unit, a one-unit run, the same exit code
                // unit, then the terminating null and padding for the vector
                // length guard.
                const size_t len = n + 3 + 64;
                memset(str, 0, sizeof(str));
                memset(str, runs[r], n);
                str[n] = exits[e];
                str[n + 1] = runs[r];
                str[n + 2] = exits[e];

                // The expected tokens: the run (if not empty), then either the
                // end (if the exit code unit is null), or the exit code unit,
                // the one-unit run, the exit code unit again and the end.
                int kinds[5], ntoks = 0;
                size_t ends[5];
                if (n > 0) { kinds[ntoks] = T_RUN; ends[ntoks++] = n; }
                if (exits[e] == 0x00) {
                    kinds[ntoks] = T_END; ends[ntoks++] = n + 1;
                } else {
                    kinds[ntoks] = T_OTHER; ends[ntoks++] = n + 1;
                    kinds[ntoks] = T_RUN; ends[ntoks++] = n + 2;
                    kinds[ntoks] = T_OTHER; ends[ntoks++] = n + 3;
                    kinds[ntoks] = T_END; ends[ntoks++] = n + 4;
                }

                failures += test("vector", lex_vector, str, len, kinds, ends, ntoks);
                failures += test("scalar", lex_scalar, str, len, kinds, ends, ntoks);
                failures += test("debug vector", lex_vector_debug, str, len, kinds, ends, ntoks);

                // The run token alone: the lexer visits the initial state, the
                // loop state once (the vector block skips the rest of the run)
                // and the final state.
                if (n > 0) {
                    const unsigned char *pos;
                    steps = 0;
                    lex_vector_debug(str, str + len, &pos);
                    if (steps != 3) {
                        fprintf(stderr, "the lexer visited %u states on a run of length %u"
                            " (expected 3)\n", steps, (unsigned)n);
                        ++failures;
                    }
                }
            }
        }
    }

    // No padding: ASan must catch even a one-byte read beyond YYLIMIT. Check
    // both YYFILL at the exact end and every exit position in an actual vector.
    static const lexer_t lexers[] = {lex_vector, lex_scalar, lex_vector_debug};
    for (size_t n = 0; n <= 200; ++n) {
        unsigned char *buf = (unsigned char*)malloc(n ? n : 1);
        if (!buf) return 1;
        for (size_t e = 0; e < sizeof(exits); ++e) {
            for (size_t p = 0; p <= n; ++p) {
                memset(buf, 'a', n);
                if (p < n) buf[p] = exits[e];
                const int want = p == n ? E_FILL : p > 0 ? T_RUN
                    : exits[e] == 0 ? T_END : T_OTHER;
                const size_t end = p < n && p == 0 ? 1 : p;
                for (size_t l = 0; l < sizeof(lexers) / sizeof(lexers[0]); ++l) {
                    const unsigned char *pos;
                    const int ret = lexers[l](buf, buf + n, &pos);
                    if (ret != want || (size_t)(pos - buf) != end) {
                        fprintf(stderr, "boundary mismatch: n=%u p=%u exit=%u lexer=%u\n",
                            (unsigned)n, (unsigned)p, exits[e], (unsigned)l);
                        ++failures;
                    }
                }
            }
        }
        free(buf);
    }

    return failures == 0 ? 0 : 1;
}
