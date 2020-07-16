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
    const taglist_t *h1, const taglist_t *h2, const taglist_t *h3)
{
    if (!h1 || !h2 || !h3) {
        assert(!h1 && !h2 && !h3);
        return;
    }
    print_headers(tok, h1->pred, h2->pred, h3->pred);
    printf("%.*s%.*s\n",
        (int)(h2->dist - h1->dist), tok + h1->dist,
        (int)(h3->dist - h2->dist), tok + h2->dist);
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
    const char *s1, *s2, *v1, *v2, *v3, *v4, *m1, *m2, *rp1, *rp2, *rt1, *rt2;
    taglist_t *h1, *h2, *h3;
    long c, t;

    c = 0; t = 0;
loop:
    in->tok = in->cur;
/*!re2c
    re2c:flags:tags = 1;
    re2c:tags:expression = "in->@@";

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
    header_field   = #h1 tchar+ ":" #h2 ows (field_content | obs_fold)* ows #h3;
    authority      = (userinfo "@")? host (":" port)?;
    absolute_uri   = scheme ":" ("//" (userinfo "@")? host (":" port)?)? path ("?" query)?;
    origin_form    = "/" path ("?" query)?;
    http_version   = "HTTP/" [0-9] "." [0-9];
    request_target = authority | absolute_uri | origin_form | "*";
    method         = tchar+;
    request_line   = @m1 method @m2 sp @rt1 request_target @rt2 sp @v3 http_version @v4 eol;
    status_code    = [0-9]{3};
    reason_phrase  = (htab | sp | vchar)*;
    status_line    = @v1 http_version @v2 sp @s1 status_code @s2 sp @rp1 reason_phrase @rp2 eol;
    start_line     = (request_line | status_line);
    message_head   = start_line (header_field eol)* eol;

    *   { return 1; }
    end { *count = c; *total = t; return 0; }
    eol { goto loop; }
    message_head {
#ifndef VERIFY
        c += 1;
        t += (v2 - v1) + (s2 - s1) + (rp2 - rp1)
            + (m2 - m1) + (rt2 - rt1) + (v4 - v3);
        for (; h1 != 0; h1 = h1->pred, h2 = h2->pred, h3 = h3->pred) {
            t += (h2->dist - h1->dist) + (h3->dist - h2->dist);
        }
#else
        if (s1) printf("%.*s %.*s %.*s\n",
            (int)(v2 - v1), v1,
            (int)(s2 - s1), s1,
            (int)(rp2 - rp1), rp1);
        if (m1) printf("%.*s %.*s %.*s\n",
            (int)(m2 - m1), m1,
            (int)(rt2 - rt1), rt1,
            (int)(v4 - v3), v3);
        print_headers(in->tok, h1, h2, h3);
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
