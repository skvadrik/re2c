// re2c $INPUT -o $OUTPUT -i
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*!re2c re2c:flags:tags = 1; */
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

static int lex(input_t *in, long *count)
{
    const char
        *s1, *u1, *h1, *h3, *h5, *r1, *p1, *p3, *q1, *f1,
        *s2, *u2, *h2, *h4, *h6, *r2, *p2, *p4, *q2, *f2;
    long c;

    c = 0;
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
    eol = "\n";

    alpha       = [a-zA-Z];
    digit       = [0-9];
    hexdigit    = [0-9a-fA-F];
    unreserved  = alpha | digit | [-._~];
    pct_encoded = "%" hexdigit{2};
    sub_delims  = [!$&'()*+,;=];
    pchar       = unreserved | pct_encoded | sub_delims | [:@];

    scheme = @s1 alpha (alpha | digit | [-+.])* @s2;
    userinfo = @u1 (unreserved | pct_encoded | sub_delims | ":")* @u2;
    dec_octet
        = digit
        | [\x31-\x39] digit
        | "1" digit{2}
        | "2" [\x30-\x34] digit
        | "25" [\x30-\x35];
    ipv4address = dec_octet "." dec_octet "." dec_octet "." dec_octet;
    h16         = hexdigit{1,4};
    ls32        = h16 ":" h16 | ipv4address;
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
    ipvfuture   = "v" hexdigit+ "." (unreserved | sub_delims | ":" )+;
    ip_literal  = "[" ( ipv6address | ipvfuture ) "]";
    reg_name    = (unreserved | pct_encoded | sub_delims)*;
    host
        = @h1 ip_literal  @h2
        | @h3 ipv4address @h4
        | @h5 reg_name    @h6;
    port      = @r1 digit* @r2;
    authority = (userinfo "@")? host (":" port)?;
    path_abempty  = ("/" pchar*)*;
    path_absolute = "/" (pchar+ ("/" pchar*)*)?;
    path_rootless = pchar+ ("/" pchar*)*;
    path_empty    = "";
    hier_part
        = "//" authority @p1 path_abempty @p2
        | @p3 (path_absolute | path_rootless | path_empty) @p4;
    query    = @q1 (pchar | [/?])* @q2;
    fragment = @f1 (pchar | [/?])* @f2;
    uri = scheme ":" hier_part ("?" query)? ("#" fragment)?;

    *   { return 1; }
    end { *count = c; return 0; }
    eol { goto loop; }
    uri {
        ++c;
        fprintf(stderr, "URI %ld:\n", c);
        fprintf(stderr, "  scheme:   %.*s\n", (int)(s2 - s1), s1);
        if (u1) fprintf(stderr, "  userinfo: %.*s\n", (int)(u2 - u1), u1);
        if (h1) fprintf(stderr, "  host:     %.*s (IP literal)\n", (int)(h2 - h1), h1);
        if (h3) fprintf(stderr, "  host:     %.*s (IPv4)\n", (int)(h4 - h3), h3);
        if (h5) fprintf(stderr, "  host:     %.*s (name)\n", (int)(h6 - h5), h5);
        if (r1) fprintf(stderr, "  port:     %.*s\n", (int)(r2 - r1), r1);
        if (p1) fprintf(stderr, "  path:     %.*s\n", (int)(p2 - p1), p1);
        if (p3) fprintf(stderr, "  path:     %.*s\n", (int)(p4 - p3), p3);
        if (q1) fprintf(stderr, "  query:    %.*s\n", (int)(q2 - q1), q1);
        if (f1) fprintf(stderr, "  fragment: %.*s\n", (int)(f2 - f1), f1);
        fprintf(stderr, "\n");
        goto loop;
    }
*/
}

int main(int argc, char **argv)
{
    const char *fname = "input";
    FILE *f;

    // prepare input file
    f = fopen(fname, "w");
    fprintf(f,
        "http://user:pass@127.0.0.1:8000/path/data?key=val&key2=val2#frag1\n"
        "rsync://rsync.kernel.org/pub/\n"
        "http://re2c.org/manual/syntax/syntax.html#rules\n"
        "ssh://[2001:db8:85a3::8a2e:370:7334]/\n");
    fclose(f);

    // read input into buffer
    input_t in;
    init_input(&in, fname);
    long count;

    assert(lex(&in, &count) == 0 && count == 4);

    // cleanup
    remove(fname);
    free_input(&in);
    return 0;
}
