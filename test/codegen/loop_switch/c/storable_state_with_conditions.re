// re2c $INPUT -o $OUTPUT -cfi --loop-switch -Wno-nondeterministic-tags

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!types:re2c*/

struct mtag {
    struct mtag* prev;
    int          dist;
};

struct mtagpool {
    struct mtag* head;
    struct mtag* next;
    struct mtag* last;
};

enum con_status {
    CON_STATUS_WAITING,
    CON_STATUS_DONE,
    CON_STATUS_END,
    CON_STATUS_ERROR
};

#define CON_STATE_SIZE  (4096-32)
typedef struct con_state {
    unsigned char*  cur;
    unsigned char*  mar;
    unsigned char*  tok;
    unsigned char*  lim;
    int             cond;
    int             state;
    struct mtagpool mtp;
    /*!stags:re2c format = "\tunsigned char*\t\t@@;\n"; */
    /*!mtags:re2c format = "\tstruct mtag\t\t\t\t*@@;\n"; */
    size_t          buf_size;
    unsigned char*  buf;
    unsigned char   static_buf[];
} con_state;
#define CON_READ_BUF_LEN  (CON_STATE_SIZE - sizeof(struct con_state) - 1) // -1: ensure a sentinel at the end of buf

static void mtagpool_init(struct mtagpool* mtp)
{
    static const unsigned size = 1024 * 1024;
    mtp->head = (struct mtag*)malloc(size * sizeof(struct mtag));
    mtp->next = mtp->head;
    mtp->last = mtp->head + size;
}

static void mtagpool_free(struct mtagpool* mtp)
{
    free(mtp->head);
    mtp->head = mtp->next = mtp->last = NULL;
}

static struct mtag* mtagpool_next(struct mtagpool* mtp)
{
    unsigned     size;
    struct mtag* head;

    if (mtp->next < mtp->last) return mtp->next++;

    size = mtp->last - mtp->head;
    head = (struct mtag*)malloc(2 * size * sizeof(struct mtag));
    memcpy(head, mtp->head, size * sizeof(struct mtag));
    free(mtp->head);
    mtp->head = head;
    mtp->next = head + size;
    mtp->last = head + size * 2;

    return mtp->next++;
}

static void mtag(struct mtag** pmt, const unsigned char* b, const unsigned char* t, struct mtagpool* mtp)
{
    struct mtag* mt = mtagpool_next(mtp);
    mt->prev = *pmt;
    mt->dist = t - b;
    *pmt = mt;
}

static enum con_status parse_con_req(struct con_state* c)
{
    unsigned int        yych, yyaccept;
    const unsigned char *l1, *l2;
    struct mtag         *f1, *f2, *p1, *p2, *p3, *p4;

    /*!re2c
        re2c:api:style             = free-form;
        re2c:eof                   = 0;
        re2c:flags:tags            = 1;
        re2c:tags:expression       = "c->@@";
        re2c:define:YYCTYPE        = "unsigned char";
        re2c:define:YYCURSOR       = "c->cur";
        re2c:define:YYMARKER       = "c->mar";
        re2c:define:YYLIMIT        = "c->lim";
        re2c:define:YYGETSTATE     = "c->state";
        re2c:define:YYSETSTATE     = "c->state = @@;";
        re2c:define:YYFILL         = "return CON_STATUS_WAITING;";
        re2c:define:YYGETCONDITION = "c->cond";
        re2c:define:YYSETCONDITION = "c->cond = @@;";
        re2c:define:YYMTAGP        = "mtag(&@@, c->tok, c->cur, &c->mtp);";
        re2c:define:YYMTAGN        = "mtag(&@@, c->tok, NULL, &c->mtp);";

        crlf  = '\r\n';
        sp    = ' ';
        htab  = '\t';
        ows   = (sp | htab)*;
        digit = [0-9];
        alpha = [a-zA-Z];
        vchar = [\x1f-\x7e];
        tchar = [-!#$%&'*+.^_`|~] | digit | alpha;

        obs_fold            = #f1 crlf (sp | htab)+ #f2;
        obs_text            = [\x80-\xff];
        field_name          = tchar+;
        field_vchar         = vchar | obs_text;
        field_content       = field_vchar ((sp | htab)+ field_vchar)?;
        field_value_folded  = (field_content* obs_fold field_content*)+;
        header_field_folded = field_value_folded ows;
        token               = tchar+;
        qdtext
            = htab
            | sp
            | [\x21-\x5B\x5D-\x7E] \ '"'
            | obs_text;
        quoted_pair         = '\\' ( htab | sp | vchar | obs_text );
        quoted_string       = '"' ( qdtext | quoted_pair )* '"';
        parameter           = #p1 token #p2 '=' #p3 ( token | quoted_string ) #p4;
        media_type          = @l1 token '/' token @l2 ( ows ';' ows parameter )*;


        <media_type> media_type ows crlf {
            struct mtag*    pname_start = p1;
            struct mtag*    pname_end   = p2;
            struct mtag*    pval_start  = p3;
            struct mtag*    pval_end    = p4;

            printf("media type: %.*s\n", (int)(l2-l1), l1);

            while (0 && pname_start) {
                printf("\t(%.*s) = (%.*s)\n",
                    pname_end->dist - pname_start->dist, c->tok + pname_start->dist,
                    pval_end->dist - pval_start->dist, c->tok + pval_start->dist);

                pname_start = pname_start->prev;
                pname_end = pname_end->prev;
                pval_start = pval_start->prev;
                pval_end = pval_end->prev;
            }

            return CON_STATUS_DONE;
        }

        <header> header_field_folded crlf {
            struct mtag*    fold_start  = f1;
            struct mtag*    fold_end    = f2;

            while (fold_start) {
                memset(c->tok + fold_start->dist, ' ', fold_end->dist - fold_start->dist);
                fold_start  = fold_start->prev;
                fold_end    = fold_end->prev;
            }

            return CON_STATUS_DONE;
        }

        <*> $ { return CON_STATUS_END; }
        <*> * { return CON_STATUS_ERROR; }
    */
}

int feed(struct con_state* c, const unsigned char* chunk, int len)
{
    const size_t shift = c->tok - c->buf;
    const size_t free = c->buf_size - (c->lim - c->tok);

    if (free < len) {
        fprintf(stderr, "Token too long for receive buffer: %ld\n", c->buf_size);
        return 1;
    }

    if (shift) {
        memmove(c->buf, c->tok, c->buf_size - shift);
        c->lim -= shift;
        c->cur -= shift;
        c->mar -= shift;
        c->tok -= shift;
        /*!stags:re2c format = "\t\t\tif (c->@@) c->@@ -= shift;\n"; */
    }

    memcpy(c->lim, chunk, len);

    c->lim += len;
    c->lim[0] = 0;  // Append sentinel

    return 0;
}

int main(int argc, char** argv)
{
    int rc = 0;
    int i;
    struct con_state* c = NULL;
    static const char* chunks[] = {
        "ap",
        "plication/j",
        "son;",
        " charset=\"",
        "utf\\\"-8\"\r",
        "\n",
        "",
        NULL
    };

    c = (con_state*)malloc(CON_STATE_SIZE);
    c->buf = c->static_buf;
    c->cur = c->mar = c->tok = c->lim = c->buf + CON_READ_BUF_LEN;
    c->lim[0] = 0; // sentinel
    c->state = -1;
    c->buf_size = CON_READ_BUF_LEN;
    /*!stags:re2c format = "\tc->@@ = 0;\n"; */
    /*!mtags:re2c format = "\tc->@@ = NULL;\n"; */
    mtagpool_init(&c->mtp);

    for (i=0;;) {
        switch (parse_con_req(c)) {
            case CON_STATUS_WAITING:
                printf("waiting\n");
                rc = feed(c, (const unsigned char*)chunks[i], strlen(chunks[i]));
                ++i;
                if (rc) goto finally;
                break;
            case CON_STATUS_DONE:
                printf("done\n");
                break;
            case CON_STATUS_END:
                printf("end\n");
                goto finally;
            case CON_STATUS_ERROR:
                printf("error\n");
                rc = 1;
                goto finally;
        }
    }

finally:
    if (c) {
        mtagpool_free(&c->mtp);
        free(c);
        c = NULL;
    }
    if (rc) fprintf(stderr, "Error exit: %d\n", rc);
    return rc;
}
