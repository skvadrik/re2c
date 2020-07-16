// re2c $INPUT -o $OUTPUT -i
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct taglist_t {
    struct taglist_t *pred;
    long dist;
} taglist_t;

typedef struct taglistpool_t {
    taglist_t *head;
    taglist_t *next;
    taglist_t *last;
} taglistpool_t;

typedef struct {
    FILE *file;
    char *buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    /*!stags:re2c format = "char *@@;\n"; */
    /*!mtags:re2c format = "taglist_t *@@;\n"; */
    taglistpool_t tlp;
    int eof;
} input_t;

static void taglistpool_clear(taglistpool_t *tlp, input_t *in)
{
    tlp->next = tlp->head;
    /*!mtags:re2c format = "in->@@ = 0;\n"; */
}

static void taglistpool_init(taglistpool_t *tlp)
{
    static const unsigned size = 1024 * 1024;
    tlp->head = (taglist_t*)malloc(size * sizeof(taglist_t));
    tlp->next = tlp->head;
    tlp->last = tlp->head + size;
}

static void taglistpool_free(taglistpool_t *tlp)
{
    free(tlp->head);
    tlp->head = tlp->next = tlp->last = NULL;
}

static taglist_t *taglistpool_next(taglistpool_t *tlp)
{
    if (tlp->next < tlp->last) {
        return tlp->next++;
    }

    const unsigned size = tlp->last - tlp->head;
    taglist_t *head = (taglist_t*)malloc(2 * size * sizeof(taglist_t));
    memcpy(head, tlp->head, size * sizeof(taglist_t));
    free(tlp->head);
    tlp->head = head;
    tlp->next = head + size;
    tlp->last = head + size * 2;
    return tlp->next++;
}

static void taglist(taglist_t **ptl, const char *b, const char *t, taglistpool_t *tlp)
{
    taglist_t *tl = taglistpool_next(tlp);
    tl->pred = *ptl;
    tl->dist = t - b;
    *ptl = tl;
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
    taglistpool_init(&in->tlp);
    in->eof = 0;
}

static void free_input(input_t *in)
{
    fclose(in->file);
    free(in->buf);
    taglistpool_free(&in->tlp);
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
    const taglist_t *h1, const taglist_t *h2,
    const taglist_t *h3, const taglist_t *h4,
    const taglist_t *h5)
{
    if (!h1 || !h2 || !h3 || !h4 || !h5) {
        assert(!h1 && !h2 && !h3 && !h4 && !h5);
        return;
    }
    print_headers(tok, h1->pred, h2->pred, h3->pred, h4->pred, h5->pred);
    printf("%.*s%.*s%.*s%.*s\n",
        (int)(h2->dist - h1->dist), tok + h1->dist,
        (int)(h3->dist - h2->dist), tok + h2->dist,
        (int)(h4->dist - h3->dist), tok + h3->dist,
        (int)(h5->dist - h4->dist), tok + h4->dist);
}

#define YYCTYPE        char
#define YYCURSOR       in->cur
#define YYMARKER       in->mar
#define YYLIMIT        in->lim
#define YYMTAGP(tl)    taglist(&tl, in->tok, in->cur, &in->tlp)
#define YYMTAGN(tl)    taglist(&tl, in->tok, NULL, &in->tlp)
#define YYFILL(n)      if (fill(in, n) != 0) return 2;

static int lex(input_t *in, long *count, long *total)
{
    const char *of, *au, *at,
        *hs1, *hs3, *m1, *p1, *p3, *p5, *q1, *q3,
        *hs2, *hs4, *m2, *p2, *p4, *p6, *q2, *q4,
        *r1, *r3, *rp1, *s1, *st1, *u1, *u3, *v1, *v3,
        *r2, *r4, *rp2, *s2, *st2, *u2, *u4, *v2, *v4;
    taglist_t *h1, *h2, *h3, *h4, *h5;
    long c, t;

    c = 0; t = 0;
    of = au = at
        = hs1 = hs3 = m1 = p1 = p3 = p5 = q1 = q3
        = hs2 = hs4 = m2 = p2 = p4 = p6 = q2 = q4
        = r1 = r3 = rp1 = s1 = st1 = u1 = u3 = v1 = v3
        = r2 = r4 = rp2 = s2 = st2 = u2 = u4 = v2 = v4 = NULL;
loop:
    in->tok = in->cur;
/*!re2c
    re2c:flags:tags = 1;
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
    end { *count = c; *total = t; return 0; }
    eol { goto loop; }
    message_head {
#ifndef VERIFY
        c += 1;
        if (st1) t += (v2 - v1) + (st2 - st1) + (rp2 - rp1);
        if (m1) {
            if (of) t += (p6 - p5) + (q4 - q3);
            if (au) t += (s2 - s1) + (u2 - u1) + (hs2 - hs1)
                + (r2 - r1) + (p2 - p1) + (p4 - p3) + (q2 - q1);
            if (at) t += (u4 - u3) + (hs4 - hs3) + (r4 - r3);
            t += (v4 - v3);
        }
        for (; h1 != 0; h1 = h1->pred, h2 = h2->pred,
            h3 = h3->pred, h4 = h4->pred, h5 = h5->pred) {
            t += (h2->dist - h1->dist) + (h3->dist - h2->dist)
                + (h4->dist - h3->dist) + (h5->dist - h4->dist);
        }
#else
        if (st1) {
            printf("%.*s %.*s %.*s\n",
                (int)(v2 - v1), v1,
                (int)(st2 - st1), st1,
                (int)(rp2 - rp1), rp1);
        } else if (m1) {
            printf("%.*s ", (int)(m2 - m1), m1);
            if (of) {
                printf("%.*s", (int)(p6 - p5), p5);
                if (q3) printf("?%.*s", (int)(q4 - q3), q3);
            } else if (au) {
                printf("%.*s:", (int)(s2 - s1), s1);
                if (p1) printf("//");
                if (u1) printf("%.*s@", (int)(u2 - u1), u1);
                printf("%.*s", (int)(hs2 - hs1), hs1);
                if (r1) printf(":%.*s", (int)(r2 - r1), r1);
                if (p1) printf("%.*s",  (int)(p2 - p1), p1);
                if (p3) printf("%.*s",  (int)(p4 - p3), p3);
                if (q1) printf("?%.*s", (int)(q2 - q1), q1);
            } else if (at) {
                if (u3) printf("%.*s@", (int)(u4 - u3), u3);
                printf("%.*s", (int)(hs4 - hs3), hs3);
                if (r3) printf(":%.*s", (int)(r4 - r3), r3);
            } else {
                printf("*");
            }
            printf(" %.*s\n", (int)(v4 - v3), v3);
        }
        print_headers(in->tok, h1, h2, h3, h4, h5);
        printf("\n");
#endif
        taglistpool_clear(&in->tlp, in);
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
