#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    FILE *file;
    char *buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    int eof;
} input_t;

/*!max:re2c*/
static const size_t SIZE = 4096;

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
    fclose(in->file);
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
    in->lim += fread(in->lim, 1, free, in->file);
    if (in->lim < in->buf + SIZE) {
        in->eof = 1;
        memset(in->lim, 0, YYMAXFILL);
        in->lim += YYMAXFILL;
    }
    return 0;
}

#define YYCTYPE            char
#define YYCURSOR           in->cur
#define YYMARKER           in->mar
#define YYLIMIT            in->lim
#define YYFILL(n)          if (fill(in, n) != 0) return 2;

static int lex(input_t *in, long *count, long *total)
{
    long c, t;

    c = 0; t = 0;
loop:
    in->tok = in->cur;
/*!re2c
    end            = "\x00";
    eol            = "\n";
    sp             = " ";
    htab           = "\t";
    ows            = (sp | htab)*;
    char           = [-._~%!$&'()*+,;=a-zA-Z0-9];
    tchar          = [-._~%!$&'*+#^`|a-zA-Z0-9];
    vchar          = [\x1f-\x7e\x80-\xff];
    scheme         = [-+.a-zA-Z0-9]+;
    userinfo       = (char | [:])+;
    host           = (char | [:[\]])+;
    port           = [0-9]*;
    path           = (char | [:@/])*;
    query          = (char | [:@?/])*;
    obs_fold       = eol (sp | htab)+;
    field_content  = vchar ((sp | htab)+ vchar)?;
    header_field   = tchar+ ":" ows (field_content | obs_fold)* ows;
    authority      = (userinfo "@")? host (":" port)?;
    absolute_uri   = scheme ":" ("//" (userinfo "@")? host (":" port)?)? path ("?" query)?;
    origin_form    = "/" path ("?" query)?;
    http_version   = "HTTP/" [0-9] "." [0-9];
    request_target = authority | absolute_uri | origin_form | "*";
    method         = tchar+;
    request_line   = method sp request_target sp http_version eol;
    status_code    = [0-9]{3};
    reason_phrase  = (htab | sp | vchar)*;
    status_line    = http_version sp status_code sp reason_phrase eol;
    start_line     = (request_line | status_line);
    message_head   = start_line (header_field eol)* eol;

    *   { return 1; }
    end { *count = c; *total = t; return 0; }
    eol { goto loop; }
    message_head {
#ifndef VERIFY
        c += 1;
        t += in->cur - in->tok;
#else
        printf("%.*s", (int)(in->cur - in->tok), in->tok);
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
        case 0: fprintf(stderr, "ok, parsed %ld HTTPs, peeked %ld chars\n", count, total); break;
        case 1: fprintf(stderr, "syntax error: %s\n", in.cur); break;
        case 2: fprintf(stderr, "fill failed\n"); break;
        default: fprintf(stderr, "panic!\n"); break;
    }

    free_input(&in);
    return 0;
}
