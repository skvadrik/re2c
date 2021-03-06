/* Generated by re2c */
#line 1 "../../../benchmarks/submatch_dfa_aot/src/re2c/36__rep_5_rep_3_rep_2.re"
#include <assert.h>
#include <stdlib.h>
#include "common.h"

#line 15 "../../../benchmarks/submatch_dfa_aot/src/re2c/common.re"


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
    char *buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    
    taglist_t *yyt1;
taglist_t *yyt10;
taglist_t *yyt11;
taglist_t *yyt12;
taglist_t *yyt13;
taglist_t *yyt14;
taglist_t *yyt15;
taglist_t *yyt16;
taglist_t *yyt17;
taglist_t *yyt2;
taglist_t *yyt3;
taglist_t *yyt4;
taglist_t *yyt5;
taglist_t *yyt6;
taglist_t *yyt7;
taglist_t *yyt8;
taglist_t *yyt9;

    taglistpool_t tlp;
    int eof;
} input_t;

static inline void taglistpool_clear(taglistpool_t *tlp, input_t *in)
{
    tlp->next = tlp->head;
    in->yyt1 = 0;
in->yyt10 = 0;
in->yyt11 = 0;
in->yyt12 = 0;
in->yyt13 = 0;
in->yyt14 = 0;
in->yyt15 = 0;
in->yyt16 = 0;
in->yyt17 = 0;
in->yyt2 = 0;
in->yyt3 = 0;
in->yyt4 = 0;
in->yyt5 = 0;
in->yyt6 = 0;
in->yyt7 = 0;
in->yyt8 = 0;
in->yyt9 = 0;

}

static inline void taglistpool_init(taglistpool_t *tlp)
{
    static const unsigned size = 1024 * 1024;
    tlp->head = (taglist_t*)malloc(size * sizeof(taglist_t));
    tlp->next = tlp->head;
    tlp->last = tlp->head + size;
}

static inline void taglistpool_free(taglistpool_t *tlp)
{
    free(tlp->head);
    tlp->head = tlp->next = tlp->last = NULL;
}

static inline void taglist(taglist_t **ptl, const char *b, const char *t, taglistpool_t *tlp)
{
#ifdef GROW_MTAG_LIST
    if (tlp->next >= tlp->last) {
        const unsigned size = tlp->last - tlp->head;
        taglist_t *head = (taglist_t*)malloc(2 * size * sizeof(taglist_t));
        memcpy(head, tlp->head, size * sizeof(taglist_t));
        free(tlp->head);
        tlp->head = head;
        tlp->next = head + size;
        tlp->last = head + size * 2;
    }
#else
    assert(tlp->next < tlp->last);
#endif
    taglist_t *tl = tlp->next++;
    tl->pred = *ptl;
    tl->dist = t - b;
    *ptl = tl;
}

#line 4 "../../../benchmarks/submatch_dfa_aot/src/re2c/include/fill.re"


#define YYMAXFILL 10


static inline int fill(input_t *in, size_t need)
{
    size_t free;
    if (in->eof) return 1;

    free = in->tok - in->buf;
    assert(free >= need);

    memmove(in->buf, in->tok, in->lim - in->tok);
    in->lim -= free;
    in->cur -= free;
    in->mar -= free;
    in->tok -= free;
    

    in->lim += fread(in->lim, 1, free, stdin);

    if (in->lim < in->buf + SIZE) {
        in->eof = 1;
        memset(in->lim, 0, YYMAXFILL);
        in->lim += YYMAXFILL;
    }

    return 0;
}

static inline void init_input(input_t *in)
{
    in->buf = (char*) malloc(SIZE + YYMAXFILL);
    in->lim = in->buf + SIZE;
    in->cur = in->lim;
    in->mar = in->lim;
    in->tok = in->lim;
    
    in->yyt1 = 0;
in->yyt10 = 0;
in->yyt11 = 0;
in->yyt12 = 0;
in->yyt13 = 0;
in->yyt14 = 0;
in->yyt15 = 0;
in->yyt16 = 0;
in->yyt17 = 0;
in->yyt2 = 0;
in->yyt3 = 0;
in->yyt4 = 0;
in->yyt5 = 0;
in->yyt6 = 0;
in->yyt7 = 0;
in->yyt8 = 0;
in->yyt9 = 0;

    taglistpool_init(&in->tlp);
    in->eof = 0;
}


static inline void free_input(input_t *in)
{
    free(in->buf);
    taglistpool_free(&in->tlp);
}

static int lex(input_t *in, Output *out);

int main(int argc, char **argv)
{
    PRE;
    input_t in;
    Output out;

    init_input(&in);
    init_output(&out);

    switch (lex(&in, &out)) {
        case 0:  break;
        case 1:  fprintf(stderr, "*** %s: syntax error\n", argv[0]); break;
        case 2:  fprintf(stderr, "*** %s: yyfill error\n", argv[0]); break;
        default: fprintf(stderr, "*** %s: panic\n", argv[0]); break;
    }

    flush(&out);
    free_output(&out);
    free_input(&in);

    POST;
    return 0;
}


static const char *print(Output *out, const char *tok, const char *start,
    const taglist_t *t)
{
    if (!t) return start;

    const char *s = print(out, tok, start, t->pred);
    if (t->dist > 0) {
        const char *e = tok + t->dist;
        outs(out, s, e);
        outc(out, '.');
        return e;
    } else {
        return s;
    }
}

static int lex(input_t *in, Output *out)
{
    taglist_t *t1 = NULL, *t2 = NULL, *t3 = NULL;

loop:
    in->tok = in->cur;

#line 228 "gen/re2c/36__rep_5_rep_3_rep_2-stadfa.c"
{
	char yych;
	if ((in->lim - in->cur) < 10) if (fill(in, 10) != 0) return 1;
	yych = *in->cur;
	in->yyt10 = in->yyt6;
	in->yyt3 = in->yyt6;
	in->yyt8 = in->yyt5;
	in->yyt2 = in->yyt5;
	in->yyt7 = in->yyt4;
	in->yyt1 = in->yyt4;
	switch (yych) {
	case 0x00:	goto yy2;
	case '\n':	goto yy6;
	case 'a':	goto yy8;
	default:	goto yy4;
	}
yy2:
	++in->cur;
#line 3 "../../../benchmarks/submatch_dfa_aot/src/re2c/include/fill.re"
	{ return 0; }
#line 249 "gen/re2c/36__rep_5_rep_3_rep_2-stadfa.c"
yy4:
	++in->cur;
yy5:
#line 28 "../../../benchmarks/submatch_dfa_aot/src/re2c/36__rep_5_rep_3_rep_2.re"
	{ return 1; }
#line 255 "gen/re2c/36__rep_5_rep_3_rep_2-stadfa.c"
yy6:
	++in->cur;
	taglist(&in->yyt3, in->tok, in->tok - 1, &in->tlp);
	taglist(&in->yyt2, in->tok, in->tok - 1, &in->tlp);
	taglist(&in->yyt1, in->tok, in->tok - 1, &in->tlp);
yy7:
	t1 = in->yyt1;
	t2 = in->yyt2;
	t3 = in->yyt3;
#line 29 "../../../benchmarks/submatch_dfa_aot/src/re2c/36__rep_5_rep_3_rep_2.re"
	{
        const char *p = in->tok;
        p = print(out, in->tok, p, t1);
        p = print(out, in->tok, p, t2);
        p = print(out, in->tok, p, t3);
        outc(out, '\n');
        taglistpool_clear(&in->tlp, in);
        goto loop;
    }
#line 275 "gen/re2c/36__rep_5_rep_3_rep_2-stadfa.c"
yy8:
	yych = *(in->mar = ++in->cur);
	in->yyt17 = in->yyt6;
	in->yyt11 = in->yyt6;
	in->yyt15 = in->yyt5;
	in->yyt9 = in->yyt5;
	in->yyt13 = in->yyt4;
	taglist(&in->yyt8, in->tok, in->tok - 1, &in->tlp);
	in->yyt12 = in->yyt4;
	taglist(&in->yyt12, in->tok, in->tok - 1, &in->tlp);
	taglist(&in->yyt7, in->tok, in->tok - 1, &in->tlp);
	switch (yych) {
	case 'a':	goto yy9;
	default:	goto yy5;
	}
yy9:
	yych = *++in->cur;
	in->yyt16 = in->yyt11;
	in->yyt3 = in->yyt10;
	in->yyt14 = in->yyt9;
	in->yyt2 = in->yyt8;
	in->yyt1 = in->yyt7;
	switch (yych) {
	case '\n':	goto yy11;
	case 'a':	goto yy12;
	default:	goto yy10;
	}
yy10:
	in->cur = in->mar;
	goto yy5;
yy11:
	++in->cur;
	taglist(&in->yyt3, in->tok, in->cur, &in->tlp);
	in->yyt3->dist += -1;
	goto yy7;
yy12:
	yych = *++in->cur;
	in->yyt6 = in->yyt16;
	in->yyt3 = in->yyt16;
	in->yyt5 = in->yyt14;
	in->yyt2 = in->yyt14;
	in->yyt4 = in->yyt12;
	in->yyt1 = in->yyt12;
	taglist(&in->yyt10, in->tok, in->cur, &in->tlp);
	in->yyt10->dist += -1;
	switch (yych) {
	case '\n':	goto yy13;
	case 'a':	goto yy14;
	default:	goto yy10;
	}
yy13:
	++in->cur;
	taglist(&in->yyt3, in->tok, in->tok - 1, &in->tlp);
	taglist(&in->yyt2, in->tok, in->cur, &in->tlp);
	in->yyt2->dist += -1;
	goto yy7;
yy14:
	yych = *++in->cur;
	in->yyt11 = in->yyt6;
	in->yyt3 = in->yyt10;
	in->yyt2 = in->yyt8;
	in->yyt12 = in->yyt4;
	in->yyt1 = in->yyt7;
	in->yyt9 = in->yyt5;
	taglist(&in->yyt9, in->tok, in->cur, &in->tlp);
	in->yyt9->dist += -1;
	switch (yych) {
	case '\n':	goto yy11;
	case 'a':	goto yy15;
	default:	goto yy10;
	}
yy15:
	yych = *++in->cur;
	in->yyt6 = in->yyt17;
	in->yyt16 = in->yyt11;
	in->yyt3 = in->yyt17;
	in->yyt5 = in->yyt15;
	in->yyt14 = in->yyt9;
	in->yyt2 = in->yyt15;
	in->yyt4 = in->yyt13;
	in->yyt1 = in->yyt13;
	in->yyt10 = in->yyt17;
	in->yyt8 = in->yyt15;
	in->yyt7 = in->yyt13;
	switch (yych) {
	case '\n':	goto yy16;
	case 'a':	goto yy17;
	default:	goto yy10;
	}
yy16:
	++in->cur;
	taglist(&in->yyt3, in->tok, in->tok - 1, &in->tlp);
	taglist(&in->yyt2, in->tok, in->tok - 1, &in->tlp);
	taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
	in->yyt1->dist += -1;
	goto yy7;
yy17:
	yych = *++in->cur;
	in->yyt17 = in->yyt6;
	in->yyt11 = in->yyt6;
	in->yyt3 = in->yyt16;
	in->yyt15 = in->yyt5;
	in->yyt9 = in->yyt5;
	in->yyt2 = in->yyt14;
	in->yyt1 = in->yyt12;
	taglist(&in->yyt8, in->tok, in->tok - 1, &in->tlp);
	in->yyt13 = in->yyt4;
	taglist(&in->yyt13, in->tok, in->cur, &in->tlp);
	in->yyt13->dist += -1;
	in->yyt12 = in->yyt4;
	taglist(&in->yyt12, in->tok, in->cur, &in->tlp);
	in->yyt12->dist += -1;
	taglist(&in->yyt7, in->tok, in->cur, &in->tlp);
	in->yyt7->dist += -1;
	switch (yych) {
	case '\n':	goto yy13;
	case 'a':	goto yy18;
	default:	goto yy10;
	}
yy18:
	yych = *++in->cur;
	in->yyt16 = in->yyt11;
	in->yyt3 = in->yyt10;
	in->yyt14 = in->yyt9;
	in->yyt2 = in->yyt8;
	in->yyt1 = in->yyt7;
	switch (yych) {
	case '\n':	goto yy11;
	case 'a':	goto yy19;
	default:	goto yy10;
	}
yy19:
	yych = *++in->cur;
	in->yyt6 = in->yyt16;
	in->yyt3 = in->yyt16;
	in->yyt5 = in->yyt14;
	in->yyt2 = in->yyt14;
	in->yyt4 = in->yyt12;
	in->yyt1 = in->yyt12;
	taglist(&in->yyt10, in->tok, in->cur, &in->tlp);
	in->yyt10->dist += -1;
	switch (yych) {
	case '\n':	goto yy13;
	case 'a':	goto yy20;
	default:	goto yy10;
	}
yy20:
	yych = *++in->cur;
	in->yyt11 = in->yyt6;
	in->yyt3 = in->yyt10;
	in->yyt2 = in->yyt8;
	in->yyt12 = in->yyt4;
	in->yyt1 = in->yyt7;
	in->yyt9 = in->yyt5;
	taglist(&in->yyt9, in->tok, in->cur, &in->tlp);
	in->yyt9->dist += -1;
	switch (yych) {
	case '\n':	goto yy11;
	case 'a':	goto yy21;
	default:	goto yy10;
	}
yy21:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	in->yyt6 = in->yyt17;
	in->yyt16 = in->yyt11;
	in->yyt3 = in->yyt17;
	in->yyt5 = in->yyt15;
	in->yyt14 = in->yyt9;
	in->yyt2 = in->yyt15;
	in->yyt4 = in->yyt13;
	in->yyt1 = in->yyt13;
	in->yyt10 = in->yyt17;
	in->yyt8 = in->yyt15;
	in->yyt7 = in->yyt13;
	switch (yych) {
	case '\n':	goto yy16;
	case 'a':	goto yy22;
	default:	goto yy10;
	}
yy22:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	in->yyt17 = in->yyt6;
	in->yyt3 = in->yyt16;
	in->yyt15 = in->yyt5;
	in->yyt2 = in->yyt14;
	in->yyt1 = in->yyt12;
	taglist(&in->yyt8, in->tok, in->tok - 1, &in->tlp);
	in->yyt13 = in->yyt4;
	taglist(&in->yyt13, in->tok, in->cur, &in->tlp);
	in->yyt13->dist += -1;
	taglist(&in->yyt7, in->tok, in->cur, &in->tlp);
	in->yyt7->dist += -1;
	in->yyt11 = in->yyt6;
	in->yyt9 = in->yyt5;
	in->yyt12 = in->yyt4;
	taglist(&in->yyt12, in->tok, in->cur, &in->tlp);
	in->yyt12->dist += -1;
	switch (yych) {
	case '\n':	goto yy13;
	case 'a':	goto yy23;
	default:	goto yy10;
	}
yy23:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	in->yyt3 = in->yyt10;
	in->yyt2 = in->yyt8;
	in->yyt1 = in->yyt7;
	in->yyt16 = in->yyt11;
	in->yyt14 = in->yyt9;
	switch (yych) {
	case '\n':	goto yy11;
	case 'a':	goto yy24;
	default:	goto yy10;
	}
yy24:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	in->yyt3 = in->yyt16;
	in->yyt2 = in->yyt14;
	in->yyt1 = in->yyt12;
	taglist(&in->yyt10, in->tok, in->cur, &in->tlp);
	in->yyt10->dist += -1;
	in->yyt6 = in->yyt16;
	in->yyt5 = in->yyt14;
	in->yyt4 = in->yyt12;
	switch (yych) {
	case '\n':	goto yy13;
	case 'a':	goto yy25;
	default:	goto yy10;
	}
yy25:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	in->yyt3 = in->yyt10;
	in->yyt2 = in->yyt8;
	in->yyt1 = in->yyt7;
	in->yyt11 = in->yyt6;
	in->yyt9 = in->yyt5;
	taglist(&in->yyt9, in->tok, in->cur, &in->tlp);
	in->yyt9->dist += -1;
	in->yyt12 = in->yyt4;
	switch (yych) {
	case '\n':	goto yy11;
	case 'a':	goto yy21;
	default:	goto yy10;
	}
}
#line 38 "../../../benchmarks/submatch_dfa_aot/src/re2c/36__rep_5_rep_3_rep_2.re"

}
