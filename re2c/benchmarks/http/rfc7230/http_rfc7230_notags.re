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

#define YYCTYPE   char
#define YYCURSOR  in->cur
#define YYMARKER  in->mar
#define YYLIMIT   in->lim
#define YYFILL(n) if (fill(in, n) != 0) return 2;

static int lex(input_t *in, long *count, long *total)
{
    long c, t;

    c = 0; t = 0;
loop:
    in->tok = in->cur;
/*!re2c

    end = "\x00";
    eol = "\n";

    crlf        = eol;
    sp          = " ";
    htab        = "\t";
    ows         = (sp | htab)*;
    digit       = [0-9];
    alpha       = [a-zA-Z];
    hexdigit    = [0-9a-fA-F];
    unreserved  = alpha | digit | [-._~];
    pct_encoded = "%" hexdigit{2};
    sub_delims  = [!$&'()*+,;=];
    pchar       = unreserved | pct_encoded | sub_delims | [:@];
    vchar       = [\x1f-\x7e];
    tchar       = [-!#$%&'*+.^_`|~] | digit | alpha;

    obs_fold       = crlf (sp | htab)+;
    obs_text       = [\x80-\xff];
    field_name     = tchar+;
    field_vchar    = vchar | obs_text;
    field_content  = field_vchar ((sp | htab)+ field_vchar)?;
    field_value    = (field_content | obs_fold)*;
    header_field   = field_name ":" ows field_value ows;
    scheme         = alpha (alpha | digit | [-+.])*;
    userinfo       = (unreserved | pct_encoded | sub_delims | ":")*;
    dec_octet
        = digit
        | [\x31-\x39] digit
        | "1" digit{2}
        | "2" [\x30-\x34] digit
        | "25" [\x30-\x35];
    ipv4address    = dec_octet "." dec_octet "." dec_octet "." dec_octet;
    h16            = hexdigit{1,4};
    ls32           = h16 ":" h16 | ipv4address;
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
    ipvfuture      = "v" hexdigit+ "." (unreserved | sub_delims | ":" )+;
    ip_literal     = "[" ( ipv6address | ipvfuture ) "]";
    reg_name       = (unreserved | pct_encoded | sub_delims)*;
    path_abempty   = ("/" pchar*)*;
    path_absolute  = "/" (pchar+ ("/" pchar*)*)?;
    path_rootless  = pchar+ ("/" pchar*)*;
    path_empty     = "";
    host           = ip_literal | ipv4address | reg_name;
    port           = digit*;
    query          = (pchar | [/?])*;
    absolute_uri   =  scheme  ":"
        ( "//" (userinfo "@")? host (":" port)? path_abempty
        | (path_absolute | path_rootless | path_empty)
        ) ("?" query)?;
    authority      = (userinfo "@")? host (":" port)?;
    origin_form    = path_abempty ("?" query)?;
    http_name      = "HTTP";
    http_version   = http_name "/" digit "." digit;
    request_target
        = authority
        | absolute_uri
        | origin_form
        | "*";
    method         = tchar+;
    request_line   = method sp request_target sp http_version crlf;
    status_code    = digit{3};
    reason_phrase  = (htab | sp | vchar | obs_text)*;
    status_line    = http_version sp status_code sp reason_phrase crlf;
    start_line     = (request_line | status_line);
    message_head   = start_line (header_field crlf)* crlf;

    *   { return 1; }
    end { *count = c; return 0; }
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
