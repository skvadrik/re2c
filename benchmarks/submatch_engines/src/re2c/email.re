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
    int lc = 0;

loop:
    in->tok = in->cur;
/*!re2c
    re2c:define:YYCTYPE      = char;
    re2c:define:YYCURSOR     = in->cur;
    re2c:define:YYMARKER     = in->mar;
    re2c:define:YYLIMIT      = in->lim;
    re2c:define:YYFILL       = "if (fill(in, @@) != 0) return 0;";  // YYFILL failure is not an error
    re2c:define:YYFILL:naked = 1;
    re2c:tags:expression     = "in->@@";

    end = "\x00";

    estr     = [a-z0-9!#$%&'*+/=?^_`{|}~-];
    beforeAt = estr+ ([.] estr+)*;
    az09     = [a-z0-9];
    az09dash = [a-z0-9-]* [a-z0-9];
    part     = az09 az09dash? [.];
    afterAt  = part+ az09 az09dash?;
    email    = beforeAt [@] afterAt [\n];
    fb       = [^\n]* [\n];

    * { return 1; }
    email {
        fwrite(in->tok, 1, in->cur - in->tok, stdout);
        ++lc;
        goto loop;
    }
    fb { goto loop; }
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
