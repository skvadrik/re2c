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

    end = "\x00";
    eol = "\n";

    alpha         = [a-zA-Z];
    digit         = [0-9];
    hexdigit      = [0-9a-fA-F];
    unreserved    = alpha | digit | [-._~];
    pct_encoded   = "%" hexdigit{2};
    sub_delims    = [!$&'()*+,;=];
    pchar         = unreserved | pct_encoded | sub_delims | [:@];

    scheme        = alpha (alpha | digit | [-+.])*;
    userinfo      = (unreserved | pct_encoded | sub_delims | ":")*;
    dec_octet
        = digit
        | [\x31-\x39] digit
        | "1" digit{2}
        | "2" [\x30-\x34] digit
        | "25" [\x30-\x35];
    ipv4address   = dec_octet "." dec_octet "." dec_octet "." dec_octet;
    h16           = hexdigit{1,4};
    ls32          = h16 ":" h16 | ipv4address;
    ipv6address
        =                            (h16 ":"){6} ls32
        |                       "::" (h16 ":"){5} ls32
        | (               h16)? "::" (h16 ":"){4} ls32
        | ((h16 ":"){0,1} h16)? "::" (h16 ":"){3} ls32
        | ((h16 ":"){0,2} h16)? "::" (h16 ":"){2} ls32
        | ((h16 ":"){0,3} h16)? "::"  h16 ":"     ls32
        | ((h16 ":"){0,4} h16)? "::"              ls32
        | ((h16 ":"){0,5} h16)? "::"              h16
        | ((h16 ":"){0,6} h16)? "::";
    ipvfuture     = "v" hexdigit+ "." (unreserved | sub_delims | ":" )+;
    ip_literal    = "[" ( ipv6address | ipvfuture ) "]";
    reg_name      = (unreserved | pct_encoded | sub_delims)*;
    host          = ip_literal | ipv4address | reg_name;
    port          = digit*;
    authority     = (userinfo "@")? host (":" port)?;
    path_abempty  = ("/" pchar*)*;
    path_absolute = "/" (pchar+ ("/" pchar*)*)?;
    path_rootless = pchar+ ("/" pchar*)*;
    path_empty    = "";
    hier_part
        = "//" authority path_abempty
        | (path_absolute | path_rootless | path_empty);
    query         = (pchar | [/?])*;
    fragment      = (pchar | [/?])*;
    uri           = scheme ":" hier_part ("?" query)? ("#" fragment)?;

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
