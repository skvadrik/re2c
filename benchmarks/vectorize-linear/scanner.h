#ifndef LINEAR_SCANNER_H
#define LINEAR_SCANNER_H
#include <stddef.h>
#include <string.h>
enum { PAD = 64 };
typedef struct {
    const unsigned char *src;
    size_t size, pos, capacity, fills;
    unsigned char *buf, *cur, *tok, *mar, *lim;
    int eof;
} Input;

static inline int fill(Input *in, size_t need) {
    if (in->eof) return 1;
    size_t used = (size_t)(in->lim - in->tok);
    size_t cursor = (size_t)(in->cur - in->tok);
    size_t marker = (size_t)(in->mar - in->tok);
    if (used + need > in->capacity) return 1;
    memmove(in->buf, in->tok, used);
    in->tok = in->buf;
    in->cur = in->buf + cursor;
    in->mar = in->buf + marker;
    size_t n = in->capacity - used;
    if (n > in->size - in->pos) n = in->size - in->pos;
    memcpy(in->buf + used, in->src + in->pos, n);
    in->pos += n;
    in->lim = in->buf + used + n;
    if (in->pos == in->size) {
        memset(in->lim, 0, PAD);
        in->lim += PAD;
        in->eof = 1;
    }
    ++in->fills;
    return 0;
}
#endif
