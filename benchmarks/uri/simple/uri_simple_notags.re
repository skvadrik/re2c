#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*!max:re2c*/
static const size_t SIZE = 4096;

typedef struct {
    FILE *file;
    char *buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    int eof;
} input_t;

static void init_input(input_t *in, const char *fname)
{
    in->file = fopen(fname, "r");
    in->buf = (char*) malloc(SIZE + YYMAXFILL);
    in->lim = in->buf + SIZE;
    in->cur = in->lim;
    in->mar = in->lim;
    in->tok = in->lim;
    in->eof = 0;
}

static void free_input(input_t *in)
{
    free(in->buf);
    fclose(in->file);
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
    in->lim += fread(in->lim, 1, free, in->file);
    if (in->lim < in->buf + SIZE) {
        in->eof = 1;
        memset(in->lim, 0, YYMAXFILL);
        in->lim += YYMAXFILL;
    }
    return 0;
}

static int lex(input_t *in, long *count, long *total)
{
    long c, t;

    c = 0; t = 0;
loop:
    in->tok = in->cur;
/*!re2c
    re2c:define:YYCTYPE = char;
    re2c:define:YYCURSOR = in->cur;
    re2c:define:YYMARKER = in->mar;
    re2c:define:YYLIMIT = in->lim;
    re2c:define:YYFILL = "if (fill(in, @@) != 0) return 2;";
    re2c:define:YYFILL:naked = 1;

    end       = "\x00";
    eol       = "\n";
    char      = [-._~%!$&'()*+,;=a-zA-Z0-9];
    scheme    = [-+.a-zA-Z0-9]+;
    userinfo  = (char | [:])+;
    host      = (char | [:[\]])+;
    port      = [0-9]*;
    path      = (char | [:@/])*;
    query     = (char | [:@?/])*;
    fragment  = (char | [:@?/])*;
    uri       = scheme ":" ("//" (userinfo "@")? host (":" port)?)? path ("?" query)? ("#" fragment)?;

    *   { return 1; }
    end { *count = c; *total = t; return 0; }
    eol { goto loop; }
    uri {
#ifndef VERIFY
        c += 1;
        t += in->cur - in->tok;
#else
        printf("%.*s\n", (int)(in->cur - in->tok), in->tok);
#endif
        goto loop;
    }
*/
}

int main(int argc, char **argv)
{
    long count, total;
    input_t in;
    init_input(&in, argv[1]);

    switch (lex(&in, &count, &total)) {
        case 0: fprintf(stderr, "ok, parsed %ld URIs, peeked %ld chars\n", count, total); break;
        case 1: fprintf(stderr, "syntax error\n"); break;
        case 2: fprintf(stderr, "yyfill failed\n"); break;
        default: fprintf(stderr, "panic!\n"); break;
    }

    free_input(&in);
    return 0;
}
