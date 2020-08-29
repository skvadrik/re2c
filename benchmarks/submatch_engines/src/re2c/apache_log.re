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
        *h1, *d1, *r1, *s1, *z1, *l1, *a1,
        *h2, *d2, *r2, *s2, *z2, *l2, *a2;
    int lc = 0;

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

    host    = @h1 [0-9.]+ @h2;
    user    = [a-zA-Z]+;
    date    = @d1 [^\]]+ @d2;
    request = @r1 [^"]+ @r2;
    status  = @s1 [0-9]+ @s2;
    size    = @z1 ([0-9]+ | [-]) @z2;
    url     = @l1 [^"]* @l2;
    agent   = @a1 [^"]* @a2;
    space   = [ ];
    line    =
        host            space
        [-]             space
        [-]             space
        "[" date "]"    space
        ["] request ["] space
        status          space
        size            space
        ["] url ["]     space
        ["] agent ["]   [\n];

    *    { return 1; }
    end  { fputs("\n]\n", stdout); return 0; }
    line {
        fputs(lc > 0 ? ",\n" : "[", stdout);
        fputs("{\"host\":\"", stdout);
        fwrite(h1, 1, h2 - h1, stdout);
        fputs("\",\"date\":\"", stdout);
        fwrite(d1, 1, d2 - d1, stdout);
        fputs("\",\"request\":\"", stdout);
        fwrite(r1, 1, r2 - r1, stdout);
        fputs("\",\"status\":\"", stdout);
        fwrite(s1, 1, s2 - s1, stdout);
        fputs("\",\"size\":\"", stdout);
        fwrite(z1, 1, z2 - z1, stdout);
        fputs("\",\"url\":\"", stdout);
        fwrite(l1, 1, l2 - l1, stdout);
        fputs("\",\"agent\":\"", stdout);
        fwrite(a1, 1, a2 - a1, stdout);
        fputs("\"}", stdout);
        ++lc;
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
