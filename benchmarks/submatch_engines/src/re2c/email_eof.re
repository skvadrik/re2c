#include <stdlib.h>
#include "common.h"

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

static void free_input(input_t *in)
{
    free(in->buf);
}

static int fill(input_t *in)
{
    size_t free;
    if (in->eof) {
        return 1;
    }
    free = in->tok - in->buf;
    if (free < 1) {
        return 2;
    }
    memmove(in->buf, in->tok, in->lim - in->tok);
    in->lim -= free;
    in->cur -= free;
    in->mar -= free;
    in->tok -= free;
    /*!stags:re2c format = "if (in->@@) in->@@ -= free;\n"; */
    in->lim += fread(in->lim, 1, free, stdin);
    in->lim[0] = 0;
    in->eof |= in->lim < in->buf + SIZE;
    return 0;
}

static void init_input(input_t *in)
{
    in->buf = (char*) malloc(SIZE + 1);
    in->cur = in->mar = in->tok = in->lim = in->buf + SIZE;
    /*!stags:re2c format = "in->@@ = in->buf + SIZE;\n"; */
    in->eof = 0;
    fill(in);
}

static int lex(input_t *in)
{
loop:
    in->tok = in->cur;
/*!re2c
    re2c:define:YYCTYPE      = char;
    re2c:define:YYCURSOR     = in->cur;
    re2c:define:YYMARKER     = in->mar;
    re2c:define:YYLIMIT      = in->lim;
    re2c:define:YYFILL       = "fill(in) == 0";
    re2c:define:YYFILL:naked = 1;
    re2c:tags:expression     = "in->@@";
    re2c:eof                 = 0;

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
    $ { return 0; }
    email {
        fwrite(in->tok, 1, in->cur - in->tok, stdout);
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
