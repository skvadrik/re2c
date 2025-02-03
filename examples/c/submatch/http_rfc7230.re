// re2c $INPUT -o $OUTPUT -i
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*!re2c re2c:flags:tags = 1; */

typedef struct mtag_t {
    struct mtag_t *pred;
    long dist;
} mtag_t;

typedef struct mtagpool_t {
    mtag_t *head;
    mtag_t *next;
    mtag_t *last;
} mtagpool_t;

typedef struct {
    FILE *file;
    char *buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    /*!stags:re2c format = "char *@@;\n"; */
    /*!mtags:re2c format = "mtag_t *@@;\n"; */
    mtagpool_t mtp;
    int eof;
} input_t;

static void mtagpool_clear(mtagpool_t *mtp, input_t *in)
{
    mtp->next = mtp->head;
    /*!mtags:re2c format = "in->@@ = 0;\n"; */
}

static void mtagpool_init(mtagpool_t *mtp)
{
    static const unsigned size = 1024 * 1024;
    mtp->head = (mtag_t*)malloc(size * sizeof(mtag_t));
    mtp->next = mtp->head;
    mtp->last = mtp->head + size;
}

static void mtagpool_free(mtagpool_t *mtp)
{
    free(mtp->head);
    mtp->head = mtp->next = mtp->last = NULL;
}

static mtag_t *mtagpool_next(mtagpool_t *mtp)
{
    unsigned size;
    mtag_t *head;

    if (mtp->next < mtp->last) return mtp->next++;

    size = mtp->last - mtp->head;
    head = (mtag_t*)malloc(2 * size * sizeof(mtag_t));
    memcpy(head, mtp->head, size * sizeof(mtag_t));
    free(mtp->head);
    mtp->head = head;
    mtp->next = head + size;
    mtp->last = head + size * 2;
    return mtp->next++;
}

static void mtag(mtag_t **pmt, const char *b, const char *t, mtagpool_t *mtp)
{
    mtag_t *mt = mtagpool_next(mtp);
    mt->pred = *pmt;
    mt->dist = t - b;
    *pmt = mt;
}

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
    /*!stags:re2c format = "in->@@ = 0;\n"; */
    /*!mtags:re2c format = "in->@@ = 0;\n"; */
    mtagpool_init(&in->mtp);
    in->eof = 0;
}

static void free_input(input_t *in)
{
    fclose(in->file);
    free(in->buf);
    mtagpool_free(&in->mtp);
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

static void print_headers(const char *tok,
    const mtag_t *h1, const mtag_t *h2,
    const mtag_t *h3, const mtag_t *h4,
    const mtag_t *h5)
{
    if (!h1) return;
    print_headers(tok, h1->pred, h2->pred, h3->pred, h4->pred, h5->pred);
    fprintf(stderr, "%.*s%.*s%.*s%.*s\n",
        (int)(h2->dist - h1->dist), tok + h1->dist,
        (int)(h3->dist - h2->dist), tok + h2->dist,
        (int)(h4->dist - h3->dist), tok + h3->dist,
        (int)(h5->dist - h4->dist), tok + h4->dist);
}

#define YYCTYPE        char
#define YYCURSOR       in->cur
#define YYMARKER       in->mar
#define YYLIMIT        in->lim
#define YYMTAGP(mt)    mtag(&mt, in->tok, in->cur, &in->mtp)
#define YYMTAGN(mt)    mtag(&mt, in->tok, NULL, &in->mtp)
#define YYFILL(n)      if (fill(in, n) != 0) return 2;

static int lex(input_t *in, long *count)
{
    const char *of, *au, *at,
        *hs1, *hs3, *m1, *p1, *p3, *p5, *q1, *q3,
        *hs2, *hs4, *m2, *p2, *p4, *p6, *q2, *q4,
        *r1, *r3, *rp1, *s1, *st1, *u1, *u3, *v1, *v3,
        *r2, *r4, *rp2, *s2, *st2, *u2, *u4, *v2, *v4;
    mtag_t *h1, *h2, *h3, *h4, *h5;
    long c;

    c = 0;;
    of = au = at
        = hs1 = hs3 = m1 = p1 = p3 = p5 = q1 = q3
        = hs2 = hs4 = m2 = p2 = p4 = p6 = q2 = q4
        = r1 = r3 = rp1 = s1 = st1 = u1 = u3 = v1 = v3
        = r2 = r4 = rp2 = s2 = st2 = u2 = u4 = v2 = v4 = NULL;
loop:
    in->tok = in->cur;
/*!re2c
    re2c:tags:expression = "in->@@";

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
    header_field   = #h1 field_name #h2 ":" ows #h3 field_value #h4 ows #h5;
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
    absolute_uri   = @s1 scheme @s2 ":"
        ( "//" (@u1 userinfo @u2 "@")? @hs1 host @hs2 (":" @r1 port @r2)? @p1 path_abempty @p2
        | @p3 (path_absolute | path_rootless | path_empty) @p4
        ) ("?" @q1 query @q2)?;
    authority      = (@u3 userinfo @u4 "@")? @hs3 host @hs4 (":" @r3 port @r4)?;
    origin_form    = @p5 path_abempty @p6 ("?" @q3 query @q4)?;
    http_name      = "HTTP";
    http_version   = http_name "/" digit "." digit;
    request_target
        = @at authority
        | @au absolute_uri
        | @of origin_form
        | "*";
    method         = tchar+;
    request_line   = @m1 method @m2 sp request_target sp @v3 http_version @v4 crlf;
    status_code    = digit{3};
    reason_phrase  = (htab | sp | vchar | obs_text)*;
    status_line    = @v1 http_version @v2 sp @st1 status_code @st2 sp @rp1 reason_phrase @rp2 crlf;
    start_line     = (request_line | status_line);
    message_head   = start_line (header_field crlf)* crlf;

    *   { return 1; }
    end { *count = c; return 0; }
    eol { goto loop; }
    message_head {
        ++c;
        if (st1) {
            fprintf(stderr, "%.*s %.*s %.*s\n",
                (int)(v2 - v1), v1,
                (int)(st2 - st1), st1,
                (int)(rp2 - rp1), rp1);
        } else if (m1) {
            fprintf(stderr, "%.*s ", (int)(m2 - m1), m1);
            if (of) {
                fprintf(stderr, "%.*s", (int)(p6 - p5), p5);
                if (q3) fprintf(stderr, "?%.*s", (int)(q4 - q3), q3);
            } else if (au) {
                fprintf(stderr, "%.*s:", (int)(s2 - s1), s1);
                if (p1) fprintf(stderr, "//");
                if (u1) fprintf(stderr, "%.*s@", (int)(u2 - u1), u1);
                fprintf(stderr, "%.*s", (int)(hs2 - hs1), hs1);
                if (r1) fprintf(stderr, ":%.*s", (int)(r2 - r1), r1);
                if (p1) fprintf(stderr, "%.*s",  (int)(p2 - p1), p1);
                if (p3) fprintf(stderr, "%.*s",  (int)(p4 - p3), p3);
                if (q1) fprintf(stderr, "?%.*s", (int)(q2 - q1), q1);
            } else if (at) {
                if (u3) fprintf(stderr, "%.*s@", (int)(u4 - u3), u3);
                fprintf(stderr, "%.*s", (int)(hs4 - hs3), hs3);
                if (r3) fprintf(stderr, ":%.*s", (int)(r4 - r3), r3);
            } else {
                fprintf(stderr, "*");
            }
            fprintf(stderr, " %.*s\n", (int)(v4 - v3), v3);
        }
        print_headers(in->tok, h1, h2, h3, h4, h5);
        fprintf(stderr, "\n");
        mtagpool_clear(&in->mtp, in);
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
        "GET /index.html HTTP/1.1\n"
        "Host: www.example.com\n"
        "User-Agent: Mozilla/5.0\n"
        "Accept: text/xml,application/xml,application/xhtml+xml,text/html*/*\n"
        "Accept-Language: en-us\n"
        "Accept-Charset: ISO-8859-1,utf-8\n"
        "Connection: keep-alive\n"
        "\n"
        "HTTP/1.1 200 OK\n"
        "Date: Thu, 24 Jul 2008 17:36:27 GMT\n"
        "Server: Apache-Coyote/1.1\n"
        "Content-Type: text/html;charset=UTF-8\n"
        "Content-Length: 1846\n"
        "\n");
    fclose(f);

    // read input into buffer
    input_t in;
    init_input(&in, fname);
    long count;

    assert(lex(&in, &count) == 0 && count == 2);

    // cleanup
    remove(fname);
    free_input(&in);
    return 0;
}
