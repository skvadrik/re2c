#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>
#include <inttypes.h>

#define BUFFER_SIZE (200*1024*1024)
char buffer[BUFFER_SIZE] = {0};

#define PRE \
    char *eof; \
    int cs; \
    int print_timing = argc == 2 && strcmp(argv[1], "-t") == 0 ? 1 : 0; \
    uint64_t start = getTimeMs();

#define POST \
    uint64_t stop = getTimeMs(); \
    if (print_timing) { \
        fprintf(stderr, "time (ms): %" PRIu64 "\n", stop - start); \
    }

#define FAIL \
    fprintf(stderr, "matching failed (%p %p)!\n", p, pe); \
    return 1;

#define INIT_LINE \
    char *p = &buffer[0]; \
    char *pe = p + strlen(buffer);

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

static inline void outs(Output *out, const char *s, const char *e)
{
    if ((out->pos - out->buf) + (e - s) >= SIZE) {
        flush(out);
    }
    for (; s < e; ) {
        *out->pos++ = *s++;
    }
}

static inline void outstr(Output *out, const char *s)
{
    for (; *s; ) {
        if (out->pos + 1 - out->buf >= SIZE) {
            flush(out);
        }
        *out->pos++ = *s++;
    }
}

static inline void outc(Output *out, char c)
{
    if (out->pos + 1 - out->buf >= SIZE) {
        flush(out);
    }
    *out->pos++ = c;
}

