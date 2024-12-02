#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>
#include <inttypes.h>

#define PRE \
    int print_timing = argc == 2 && strcmp(argv[1], "-t") == 0 ? 1 : 0; \
    uint64_t start = getTimeMs();

#define POST \
    uint64_t stop = getTimeMs(); \
    if (print_timing) { \
        fprintf(stderr, "time (ms): %" PRIu64 "\n", stop - start); \
    }

static inline uint64_t getTimeMs()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_usec / 1000 + tv.tv_sec * 1000;
}

static const size_t SIZE = 4096 * 16;

typedef struct {
    char *buf;
    char *pos;
} Output;

static inline void init_output(Output *out)
{
    out->buf = (char*) malloc(SIZE);
    out->pos = out->buf;
}

static inline void free_output(Output *out)
{
    free(out->buf);
}

static inline void flush(Output *out)
{
    fwrite(out->buf, 1, out->pos - out->buf, stdout);
    out->pos = out->buf;
}

// define as macro to enforce inlining
#define outs(out, s, e) do {                 \
    long n = (e) - (s);                      \
    if ((out->pos - out->buf) + n >= SIZE) { \
        flush(out);                          \
    }                                        \
    memcpy(out->pos, s, n);                  \
    out->pos += n;                           \
} while (0)

// define as macro to enforce inlining
#define outc(out, c) do {                  \
    if (out->pos + 1 - out->buf >= SIZE) { \
        flush(out);                        \
    }                                      \
    *out->pos++ = c;                       \
} while (0)

// define as macro to enforce inlining
// first argument must be a string literal
#define OUT(s, p1, p2) do {          \
    const char *p = s;               \
    outs(out, p, p + sizeof(s) - 1); \
    outs(out, p1, p2);               \
    outc(out, '\n');                 \
} while (0)
