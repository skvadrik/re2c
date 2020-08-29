#include <stdlib.h>
#include "common.h"

/*!max:re2c*/
static const size_t SIZE = 4096 * 16;

typedef struct {
    char *buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    /*!stags:re2c format = "char *@@;\n"; */
    int eof;
} input_t;

static void init_input(input_t *in)
{
    in->buf = (char*) malloc(SIZE + YYMAXFILL);
    in->lim = in->buf + SIZE;
    in->cur = in->lim;
    in->mar = in->lim;
    in->tok = in->lim;
    /*!stags:re2c format = "in->@@ = 0;\n"; */
    in->eof = 0;
}

static void free_input(input_t *in)
{
    free(in->buf);
}

static int fill(input_t *in, size_t need)
{
    size_t free;
    if (in->eof) return 1;

    free = in->tok - in->buf;
    if (free < need) return 2;

    memmove(in->buf, in->tok, in->lim - in->tok);
    in->lim -= free;
    in->cur -= free;
    in->mar -= free;
    in->tok -= free;
    /*!stags:re2c format = "if (in->@@) in->@@ -= free;\n"; */
    in->lim += fread(in->lim, 1, free, stdin);
    if (in->lim < in->buf + SIZE) {
        in->eof = 1;
        memset(in->lim, 0, YYMAXFILL);
        in->lim += YYMAXFILL;
    }
    return 0;
}

static int lex(input_t *in)
{
    const char
        *s1, *y1, *h1, *m1, *d1, *M1, *z1,
        *s2, *y2, *h2, *m2, *d2, *M2, *z2;

loop:
    in->tok = in->cur;
/*!re2c

    re2c:define:YYCTYPE      = char;
    re2c:define:YYCURSOR     = in->cur;
    re2c:define:YYMARKER     = in->mar;
    re2c:define:YYLIMIT      = in->lim;
    re2c:define:YYFILL       = "if (fill(in, @@) != 0) return 2;";
    re2c:define:YYFILL:naked = 1;
    re2c:tags:expression     = "in->@@";

    end = "\x00";

    year     = @y1 (([1-9][0-9]*)? [0-9]{4}) @y2;
    month    = @m1 ([1][0-2] | [0][1-9]) @m2;
    day      = @d1 ([3][0-1] | [0][1-9] | [1-2][0-9]) @d2;
    hours    = @h1 ([2][0-3] | [0-1][0-9]) @h2;
    minutes  = @M1 [0-5][0-9] @M2;
    seconds  = @s1 [0-5][0-9] @s2;
    timezone = @z1 ([Z] | [+-]([2][0-3] | [0-1][0-9])[:][0-5][0-9]) @z2;
    date     = year [-] month [-] day [T] hours [:] minutes [:] seconds timezone [\n];

    *    { return 1; }
    end  { return 0; }
    date {
        fputs("{'year'='", stdout);
        fwrite(y1, 1, y2 - y1, stdout);
        fputs("', 'month'='", stdout);
        fwrite(m1, 1, m2 - m1, stdout);
        fputs("', 'day'='", stdout);
        fwrite(d1, 1, d2 - d1, stdout);
        fputs("', 'hours'='", stdout);
        fwrite(h1, 1, h2 - h1, stdout);
        fputs("', 'minutes'='", stdout);
        fwrite(M1, 1, M2 - M1, stdout);
        fputs("', 'seconds'='", stdout);
        fwrite(s1, 1, s2 - s1, stdout);
        fputs("', 'tz'='", stdout);
        fwrite(z1, 1, z2 - z1, stdout);
        fputs("'}\n", stdout);
        goto loop;
    }
*/
}

int main(int argc, char **argv)
{
    PRE;
    input_t in;
    init_input(&in);

    switch (lex(&in)) {
        case 0:  break;
        case 1:  fprintf(stderr, "syntax error\n"); break;
        case 2:  fprintf(stderr, "yyfill error\n"); break;
        default: fprintf(stderr, "panic\n"); break;
    }

    free_input(&in);
    POST;
    return 0;
}
