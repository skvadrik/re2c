#ifndef _RE2C_BENCHMARKS_C_COMMON_
#define _RE2C_BENCHMARKS_C_COMMON_

#include <stdio.h>
#include <stdint.h>

static const size_t SIZE = 4096 * 16;

extern bool verbose;

#ifdef RUN_IN_TEST_MODE

#define OUTS(p1, p2) do { \
    count += (p2) - (p1); \
    if (verbose) printf("%.*s", (int)((p2) - (p1)), p1); \
} while (0)

#define OUTC(c) do { \
    if (verbose) printf("%c", c); \
} while (0)

#define OUT(s, p1, p2) do { \
    count += (p2) - (p1); \
    if (verbose) printf("%s%.*s\n", s, (int)((p2) - (p1)), p1); \
} while (0)

#else

#define OUTS(p1, p2) do { count += (p2) - (p1); } while(0)
#define OUTC(c)
#define OUT(_, p1, p2) do { count += (p2) - (p1); } while(0)

#endif // RUN_IN_TEST_MODE

#endif // _RE2C_BENCHMARKS_C_COMMON_
