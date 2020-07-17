// re2c $INPUT -o $OUTPUT -i
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
    /*!stags:re2c format = "char *@@;\n"; */
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
    /*!stags:re2c format = "in->@@ = 0;\n"; */
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
    /*!stags:re2c format = "if (in->@@) in->@@ -= free;\n"; */
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
    const char
        *s1, *u1, *h1, *r1, *p1, *q1, *f1,
        *s2, *u2, *h2, *r2, *p2, *q2, *f2;
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
    re2c:flags:tags = 1;
    re2c:tags:expression = "in->@@";

    end       = "\x00";
    eol       = "\n";
    char      = [-._~%!$&'()*+,;=a-zA-Z0-9];
    scheme    = @s1 [-+.a-zA-Z0-9]+ @s2;
    userinfo  = @u1 (char | [:])+ @u2;
    host      = @h1 (char | [:[\]])+ @h2;
    port      = @r1 [0-9]* @r2;
    path      = @p1 (char | [:@/])* @p2;
    query     = @q1 (char | [:@?/])* @q2;
    fragment  = @f1 (char | [:@?/])* @f2;
    uri       = scheme ":" ("//" (userinfo "@")? host (":" port)?)? path ("?" query)? ("#" fragment)?;

    *   { return 1; }
    end { *count = c; *total = t; return 0; }
    eol { goto loop; }
    uri {
#ifndef VERIFY
        c += 1;
        t += (s2 - s1) + (u2 - u1) + (h2 - h1)
            + (r2 - r1) + (p2 - p1) + (q2 - q1) + (f2 - f1);
#else
                printf("%.*s:", (int)(s2 - s1), s1);
        if (h1) printf("//");
        if (u1) printf("%.*s@", (int)(u2 - u1), u1);
        if (h1) printf("%.*s",  (int)(h2 - h1), h1);
        if (r1) printf(":%.*s", (int)(r2 - r1), r1);
                printf("%.*s",  (int)(p2 - p1), p1);
        if (q1) printf("?%.*s", (int)(q2 - q1), q1);
        if (f1) printf("#%.*s", (int)(f2 - f1), f1);
        printf("\n");
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
