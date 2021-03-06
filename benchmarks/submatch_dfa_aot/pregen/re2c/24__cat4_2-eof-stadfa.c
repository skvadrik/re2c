/* Generated by re2c */
#line 1 "../../../benchmarks/submatch_dfa_aot/src/re2c/24__cat4_2.re"
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
    char *yyt1;
char *yyt10;
char *yyt11;
char *yyt12;
char *yyt13;
char *yyt14;
char *yyt15;
char *yyt16;
char *yyt17;
char *yyt18;
char *yyt19;
char *yyt2;
char *yyt20;
char *yyt21;
char *yyt22;
char *yyt23;
char *yyt24;
char *yyt25;
char *yyt26;
char *yyt27;
char *yyt28;
char *yyt29;
char *yyt3;
char *yyt30;
char *yyt31;
char *yyt32;
char *yyt33;
char *yyt34;
char *yyt35;
char *yyt36;
char *yyt37;
char *yyt38;
char *yyt39;
char *yyt4;
char *yyt40;
char *yyt41;
char *yyt42;
char *yyt43;
char *yyt44;
char *yyt45;
char *yyt46;
char *yyt47;
char *yyt48;
char *yyt49;
char *yyt5;
char *yyt50;
char *yyt51;
char *yyt52;
char *yyt6;
char *yyt7;
char *yyt8;
char *yyt9;

    
    taglistpool_t tlp;
    int eof;
} input_t;

static inline void taglistpool_clear(taglistpool_t *tlp, input_t *in)
{
    tlp->next = tlp->head;
    
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

#line 6 "../../../benchmarks/submatch_dfa_aot/src/re2c/include-eof/fill.re"


static inline int fill(input_t *in)
{
    size_t free;
    if (in->eof) return 1;

    free = in->tok - in->buf;
    assert(free > 0);

    memmove(in->buf, in->tok, in->lim - in->tok);
    in->lim -= free;
    in->cur -= free;
    in->mar -= free;
    in->tok -= free;
    if (in->yyt1) in->yyt1 -= free;
if (in->yyt10) in->yyt10 -= free;
if (in->yyt11) in->yyt11 -= free;
if (in->yyt12) in->yyt12 -= free;
if (in->yyt13) in->yyt13 -= free;
if (in->yyt14) in->yyt14 -= free;
if (in->yyt15) in->yyt15 -= free;
if (in->yyt16) in->yyt16 -= free;
if (in->yyt17) in->yyt17 -= free;
if (in->yyt18) in->yyt18 -= free;
if (in->yyt19) in->yyt19 -= free;
if (in->yyt2) in->yyt2 -= free;
if (in->yyt20) in->yyt20 -= free;
if (in->yyt21) in->yyt21 -= free;
if (in->yyt22) in->yyt22 -= free;
if (in->yyt23) in->yyt23 -= free;
if (in->yyt24) in->yyt24 -= free;
if (in->yyt25) in->yyt25 -= free;
if (in->yyt26) in->yyt26 -= free;
if (in->yyt27) in->yyt27 -= free;
if (in->yyt28) in->yyt28 -= free;
if (in->yyt29) in->yyt29 -= free;
if (in->yyt3) in->yyt3 -= free;
if (in->yyt30) in->yyt30 -= free;
if (in->yyt31) in->yyt31 -= free;
if (in->yyt32) in->yyt32 -= free;
if (in->yyt33) in->yyt33 -= free;
if (in->yyt34) in->yyt34 -= free;
if (in->yyt35) in->yyt35 -= free;
if (in->yyt36) in->yyt36 -= free;
if (in->yyt37) in->yyt37 -= free;
if (in->yyt38) in->yyt38 -= free;
if (in->yyt39) in->yyt39 -= free;
if (in->yyt4) in->yyt4 -= free;
if (in->yyt40) in->yyt40 -= free;
if (in->yyt41) in->yyt41 -= free;
if (in->yyt42) in->yyt42 -= free;
if (in->yyt43) in->yyt43 -= free;
if (in->yyt44) in->yyt44 -= free;
if (in->yyt45) in->yyt45 -= free;
if (in->yyt46) in->yyt46 -= free;
if (in->yyt47) in->yyt47 -= free;
if (in->yyt48) in->yyt48 -= free;
if (in->yyt49) in->yyt49 -= free;
if (in->yyt5) in->yyt5 -= free;
if (in->yyt50) in->yyt50 -= free;
if (in->yyt51) in->yyt51 -= free;
if (in->yyt52) in->yyt52 -= free;
if (in->yyt6) in->yyt6 -= free;
if (in->yyt7) in->yyt7 -= free;
if (in->yyt8) in->yyt8 -= free;
if (in->yyt9) in->yyt9 -= free;


    in->lim += fread(in->lim, 1, free, stdin);
    in->lim[0] = 0;

    if (in->lim < in->buf + SIZE) {
        in->eof = 1;
    }

    return 0;
}

static inline void init_input(input_t *in)
{
    in->buf = (char*) malloc(SIZE + 1);
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
in->yyt18 = 0;
in->yyt19 = 0;
in->yyt2 = 0;
in->yyt20 = 0;
in->yyt21 = 0;
in->yyt22 = 0;
in->yyt23 = 0;
in->yyt24 = 0;
in->yyt25 = 0;
in->yyt26 = 0;
in->yyt27 = 0;
in->yyt28 = 0;
in->yyt29 = 0;
in->yyt3 = 0;
in->yyt30 = 0;
in->yyt31 = 0;
in->yyt32 = 0;
in->yyt33 = 0;
in->yyt34 = 0;
in->yyt35 = 0;
in->yyt36 = 0;
in->yyt37 = 0;
in->yyt38 = 0;
in->yyt39 = 0;
in->yyt4 = 0;
in->yyt40 = 0;
in->yyt41 = 0;
in->yyt42 = 0;
in->yyt43 = 0;
in->yyt44 = 0;
in->yyt45 = 0;
in->yyt46 = 0;
in->yyt47 = 0;
in->yyt48 = 0;
in->yyt49 = 0;
in->yyt5 = 0;
in->yyt50 = 0;
in->yyt51 = 0;
in->yyt52 = 0;
in->yyt6 = 0;
in->yyt7 = 0;
in->yyt8 = 0;
in->yyt9 = 0;

    
    taglistpool_init(&in->tlp);
    in->eof = 0;
    fill(in);
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


static int lex(input_t *in, Output *out)
{
    const char
        *a0, *a1, *a2, *a3,
        *b0, *b1, *b2, *b3;
loop:
    in->tok = in->cur;

#line 315 "gen/re2c/24__cat4_2-eof-stadfa.c"
{
	char yych;
yyFillLabel3_0:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy4;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_0;
			goto yy57;
		}
		goto yy2;
	}
yy2:
	++in->cur;
yy3:
#line 11 "../../../benchmarks/submatch_dfa_aot/src/re2c/24__cat4_2.re"
	{ return 1; }
#line 334 "gen/re2c/24__cat4_2-eof-stadfa.c"
yy4:
	in->mar = ++in->cur;
	in->yyt8 = in->yyt9 = in->cur - 1;
yyFillLabel3_1:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy5;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_1;
		}
		goto yy3;
	}
yy5:
	++in->cur;
	in->yyt2 = in->yyt9;
	in->yyt11 = in->yyt9;
	in->yyt1 = in->yyt8;
	in->yyt10 = in->yyt8;
	in->yyt9 = in->cur - 1;
yyFillLabel3_2:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy7;
	case 'b':	goto yy8;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_2;
		}
		goto yy6;
	}
yy6:
	in->cur = in->mar;
	goto yy3;
yy7:
	++in->cur;
	in->yyt2 = in->yyt9;
	in->yyt15 = in->yyt11;
	in->yyt1 = in->yyt8;
	in->yyt14 = in->yyt10;
	in->yyt12 = in->yyt13 = in->cur - 1;
	in->yyt11 = in->yyt9;
	in->yyt10 = in->yyt8;
	in->yyt9 = in->cur - 1;
yyFillLabel3_3:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy10;
	case 'b':	goto yy8;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_3;
		}
		goto yy6;
	}
yy8:
	++in->cur;
	in->yyt11 = in->yyt2;
	in->yyt10 = in->yyt1;
yyFillLabel3_4:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy11;
	case 'b':	goto yy8;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_4;
		}
		goto yy6;
	}
yy10:
	++in->cur;
	in->yyt6 = in->yyt13;
	in->yyt19 = in->yyt13;
	in->yyt5 = in->yyt12;
	in->yyt18 = in->yyt12;
	in->yyt2 = in->yyt9;
	in->yyt4 = in->yyt15;
	in->yyt17 = in->yyt15;
	in->yyt1 = in->yyt8;
	in->yyt3 = in->yyt14;
	in->yyt16 = in->yyt14;
	in->yyt12 = in->yyt13 = in->cur - 1;
	in->yyt15 = in->yyt11;
	in->yyt14 = in->yyt10;
	in->yyt11 = in->yyt9;
	in->yyt10 = in->yyt8;
	in->yyt9 = in->cur - 1;
yyFillLabel3_5:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy12;
	case 'b':	goto yy13;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_5;
		}
		goto yy6;
	}
yy11:
	++in->cur;
	in->yyt15 = in->yyt11;
	in->yyt14 = in->yyt10;
	in->yyt8 = in->yyt12 = in->yyt13 = in->cur - 1;
	in->yyt11 = in->yyt2;
	in->yyt10 = in->yyt1;
yyFillLabel3_6:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy15;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_6;
		}
		goto yy6;
	}
yy12:
	++in->cur;
	in->yyt6 = in->yyt13;
	in->yyt25 = in->yyt19;
	in->yyt5 = in->yyt12;
	in->yyt24 = in->yyt18;
	in->yyt2 = in->yyt9;
	in->yyt4 = in->yyt15;
	in->yyt23 = in->yyt17;
	in->yyt1 = in->yyt8;
	in->yyt3 = in->yyt14;
	in->yyt22 = in->yyt16;
	in->yyt20 = in->yyt21 = in->cur - 1;
	in->yyt19 = in->yyt13;
	in->yyt18 = in->yyt12;
	in->yyt17 = in->yyt15;
	in->yyt16 = in->yyt14;
	in->yyt12 = in->yyt13 = in->cur - 1;
	in->yyt15 = in->yyt11;
	in->yyt14 = in->yyt10;
	in->yyt11 = in->yyt9;
	in->yyt10 = in->yyt8;
	in->yyt9 = in->cur - 1;
yyFillLabel3_7:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy16;
	case 'b':	goto yy13;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_7;
		}
		goto yy6;
	}
yy13:
	++in->cur;
	in->yyt19 = in->yyt6;
	in->yyt18 = in->yyt5;
	in->yyt11 = in->yyt2;
	in->yyt17 = in->yyt4;
	in->yyt10 = in->yyt1;
	in->yyt16 = in->yyt3;
yyFillLabel3_8:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy17;
	case 'b':	goto yy13;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_8;
		}
		goto yy6;
	}
yy15:
	++in->cur;
	in->yyt6 = in->yyt13;
	in->yyt19 = in->yyt13;
	in->yyt5 = in->yyt12;
	in->yyt18 = in->yyt12;
	in->yyt4 = in->yyt15;
	in->yyt17 = in->yyt15;
	in->yyt3 = in->yyt14;
	in->yyt16 = in->yyt14;
	in->yyt13 = in->cur - 1;
	in->yyt12 = in->yyt8;
	in->yyt15 = in->yyt11;
	in->yyt14 = in->yyt10;
	in->yyt11 = in->yyt2;
	in->yyt10 = in->yyt1;
yyFillLabel3_9:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy18;
	case 'b':	goto yy19;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_9;
		}
		goto yy6;
	}
yy16:
	++in->cur;
	in->yyt36 = in->yyt21;
	in->yyt35 = in->yyt21;
	in->yyt34 = in->yyt20;
	in->yyt33 = in->yyt20;
	in->yyt6 = in->yyt13;
	in->yyt32 = in->yyt25;
	in->yyt31 = in->yyt25;
	in->yyt5 = in->yyt12;
	in->yyt30 = in->yyt24;
	in->yyt29 = in->yyt24;
	in->yyt2 = in->yyt9;
	in->yyt4 = in->yyt15;
	in->yyt28 = in->yyt23;
	in->yyt27 = in->yyt23;
	in->yyt1 = in->yyt8;
	in->yyt3 = in->yyt14;
	in->yyt7 = in->yyt22;
	in->yyt26 = in->yyt22;
	in->yyt20 = in->yyt21 = in->cur - 1;
	in->yyt25 = in->yyt19;
	in->yyt24 = in->yyt18;
	in->yyt23 = in->yyt17;
	in->yyt22 = in->yyt16;
	in->yyt19 = in->yyt13;
	in->yyt18 = in->yyt12;
	in->yyt17 = in->yyt15;
	in->yyt16 = in->yyt14;
	in->yyt12 = in->yyt13 = in->cur - 1;
	in->yyt15 = in->yyt11;
	in->yyt14 = in->yyt10;
	in->yyt11 = in->yyt9;
	in->yyt10 = in->yyt8;
	in->yyt9 = in->cur - 1;
yyFillLabel3_10:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy21;
	case 'b':	goto yy22;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_10;
		}
		goto yy6;
	}
yy17:
	++in->cur;
	in->yyt25 = in->yyt19;
	in->yyt24 = in->yyt18;
	in->yyt15 = in->yyt11;
	in->yyt23 = in->yyt17;
	in->yyt14 = in->yyt10;
	in->yyt22 = in->yyt16;
	in->yyt8 = in->yyt12 = in->yyt13 = in->yyt20 = in->yyt21 = in->cur - 1;
	in->yyt19 = in->yyt6;
	in->yyt18 = in->yyt5;
	in->yyt11 = in->yyt2;
	in->yyt17 = in->yyt4;
	in->yyt10 = in->yyt1;
	in->yyt16 = in->yyt3;
yyFillLabel3_11:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy24;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_11;
		}
		goto yy6;
	}
yy18:
	++in->cur;
	in->yyt6 = in->yyt13;
	in->yyt25 = in->yyt19;
	in->yyt5 = in->yyt12;
	in->yyt24 = in->yyt18;
	in->yyt4 = in->yyt15;
	in->yyt23 = in->yyt17;
	in->yyt3 = in->yyt14;
	in->yyt22 = in->yyt16;
	in->yyt20 = in->yyt21 = in->cur - 1;
	in->yyt19 = in->yyt13;
	in->yyt18 = in->yyt12;
	in->yyt17 = in->yyt15;
	in->yyt16 = in->yyt14;
	in->yyt13 = in->cur - 1;
	in->yyt12 = in->yyt8;
	in->yyt15 = in->yyt11;
	in->yyt14 = in->yyt10;
	in->yyt11 = in->yyt2;
	in->yyt10 = in->yyt1;
yyFillLabel3_12:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy25;
	case 'b':	goto yy19;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_12;
		}
		goto yy6;
	}
yy19:
	++in->cur;
	in->yyt19 = in->yyt6;
	in->yyt18 = in->yyt5;
	in->yyt17 = in->yyt4;
	in->yyt16 = in->yyt3;
yyFillLabel3_13:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy26;
	case 'b':	goto yy19;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_13;
		}
		goto yy6;
	}
yy21:
	++in->cur;
	in->yyt36 = in->yyt21;
	in->yyt44 = in->yyt35;
	in->yyt34 = in->yyt20;
	in->yyt43 = in->yyt33;
	in->yyt6 = in->yyt13;
	in->yyt32 = in->yyt25;
	in->yyt42 = in->yyt31;
	in->yyt5 = in->yyt12;
	in->yyt30 = in->yyt24;
	in->yyt41 = in->yyt29;
	in->yyt2 = in->yyt9;
	in->yyt4 = in->yyt15;
	in->yyt28 = in->yyt23;
	in->yyt40 = in->yyt27;
	in->yyt1 = in->yyt8;
	in->yyt3 = in->yyt14;
	in->yyt7 = in->yyt22;
	in->yyt39 = in->yyt26;
	in->yyt37 = in->yyt38 = in->cur - 1;
	in->yyt35 = in->yyt21;
	in->yyt33 = in->yyt20;
	in->yyt31 = in->yyt25;
	in->yyt29 = in->yyt24;
	in->yyt27 = in->yyt23;
	in->yyt26 = in->yyt22;
	in->yyt20 = in->yyt21 = in->cur - 1;
	in->yyt25 = in->yyt19;
	in->yyt24 = in->yyt18;
	in->yyt23 = in->yyt17;
	in->yyt22 = in->yyt16;
	in->yyt19 = in->yyt13;
	in->yyt18 = in->yyt12;
	in->yyt17 = in->yyt15;
	in->yyt16 = in->yyt14;
	in->yyt12 = in->yyt13 = in->cur - 1;
	in->yyt15 = in->yyt11;
	in->yyt14 = in->yyt10;
	in->yyt11 = in->yyt9;
	in->yyt10 = in->yyt8;
	in->yyt9 = in->cur - 1;
yyFillLabel3_14:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy27;
	case 'b':	goto yy22;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_14;
		}
		goto yy6;
	}
yy22:
	++in->cur;
	in->yyt35 = in->yyt36;
	in->yyt33 = in->yyt34;
	in->yyt19 = in->yyt6;
	in->yyt31 = in->yyt32;
	in->yyt18 = in->yyt5;
	in->yyt29 = in->yyt30;
	in->yyt11 = in->yyt2;
	in->yyt17 = in->yyt4;
	in->yyt27 = in->yyt28;
	in->yyt10 = in->yyt1;
	in->yyt16 = in->yyt3;
	in->yyt26 = in->yyt7;
yyFillLabel3_15:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy29;
	case 'b':	goto yy22;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_15;
		}
		goto yy6;
	}
yy24:
	++in->cur;
	in->yyt36 = in->yyt21;
	in->yyt35 = in->yyt21;
	in->yyt34 = in->yyt20;
	in->yyt33 = in->yyt20;
	in->yyt6 = in->yyt13;
	in->yyt32 = in->yyt25;
	in->yyt31 = in->yyt25;
	in->yyt5 = in->yyt12;
	in->yyt30 = in->yyt24;
	in->yyt29 = in->yyt24;
	in->yyt4 = in->yyt15;
	in->yyt28 = in->yyt23;
	in->yyt27 = in->yyt23;
	in->yyt3 = in->yyt14;
	in->yyt7 = in->yyt22;
	in->yyt26 = in->yyt22;
	in->yyt21 = in->cur - 1;
	in->yyt20 = in->yyt8;
	in->yyt25 = in->yyt19;
	in->yyt24 = in->yyt18;
	in->yyt23 = in->yyt17;
	in->yyt22 = in->yyt16;
	in->yyt19 = in->yyt13;
	in->yyt18 = in->yyt12;
	in->yyt17 = in->yyt15;
	in->yyt16 = in->yyt14;
	in->yyt13 = in->cur - 1;
	in->yyt12 = in->yyt8;
	in->yyt15 = in->yyt11;
	in->yyt14 = in->yyt10;
	in->yyt11 = in->yyt2;
	in->yyt10 = in->yyt1;
yyFillLabel3_16:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy30;
	case 'b':	goto yy31;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_16;
		}
		goto yy6;
	}
yy25:
	++in->cur;
	in->yyt36 = in->yyt21;
	in->yyt35 = in->yyt21;
	in->yyt34 = in->yyt20;
	in->yyt33 = in->yyt20;
	in->yyt6 = in->yyt13;
	in->yyt32 = in->yyt25;
	in->yyt31 = in->yyt25;
	in->yyt5 = in->yyt12;
	in->yyt30 = in->yyt24;
	in->yyt29 = in->yyt24;
	in->yyt4 = in->yyt15;
	in->yyt28 = in->yyt23;
	in->yyt27 = in->yyt23;
	in->yyt3 = in->yyt14;
	in->yyt7 = in->yyt22;
	in->yyt26 = in->yyt22;
	in->yyt20 = in->yyt21 = in->cur - 1;
	in->yyt25 = in->yyt19;
	in->yyt24 = in->yyt18;
	in->yyt23 = in->yyt17;
	in->yyt22 = in->yyt16;
	in->yyt19 = in->yyt13;
	in->yyt18 = in->yyt12;
	in->yyt17 = in->yyt15;
	in->yyt16 = in->yyt14;
	in->yyt13 = in->cur - 1;
	in->yyt12 = in->yyt8;
	in->yyt15 = in->yyt11;
	in->yyt14 = in->yyt10;
	in->yyt11 = in->yyt2;
	in->yyt10 = in->yyt1;
yyFillLabel3_17:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy30;
	case 'b':	goto yy31;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_17;
		}
		goto yy6;
	}
yy26:
	++in->cur;
	in->yyt25 = in->yyt19;
	in->yyt24 = in->yyt18;
	in->yyt23 = in->yyt17;
	in->yyt22 = in->yyt16;
	in->yyt8 = in->yyt20 = in->yyt21 = in->cur - 1;
	in->yyt19 = in->yyt6;
	in->yyt18 = in->yyt5;
	in->yyt17 = in->yyt4;
	in->yyt16 = in->yyt3;
yyFillLabel3_18:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy33;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_18;
		}
		goto yy6;
	}
yy27:
	++in->cur;
	in->yyt52 = in->yyt38;
	in->yyt51 = in->yyt37;
	in->yyt36 = in->yyt21;
	in->yyt50 = in->yyt44;
	in->yyt34 = in->yyt20;
	in->yyt49 = in->yyt43;
	in->yyt6 = in->yyt13;
	in->yyt32 = in->yyt25;
	in->yyt48 = in->yyt42;
	in->yyt5 = in->yyt12;
	in->yyt30 = in->yyt24;
	in->yyt47 = in->yyt41;
	in->yyt2 = in->yyt9;
	in->yyt4 = in->yyt15;
	in->yyt28 = in->yyt23;
	in->yyt46 = in->yyt40;
	in->yyt1 = in->yyt8;
	in->yyt3 = in->yyt14;
	in->yyt7 = in->yyt22;
	in->yyt45 = in->yyt39;
	in->yyt37 = in->yyt38 = in->cur - 1;
	in->yyt44 = in->yyt35;
	in->yyt43 = in->yyt33;
	in->yyt42 = in->yyt31;
	in->yyt41 = in->yyt29;
	in->yyt40 = in->yyt27;
	in->yyt39 = in->yyt26;
	in->yyt35 = in->yyt21;
	in->yyt33 = in->yyt20;
	in->yyt31 = in->yyt25;
	in->yyt29 = in->yyt24;
	in->yyt27 = in->yyt23;
	in->yyt26 = in->yyt22;
	in->yyt20 = in->yyt21 = in->cur - 1;
	in->yyt25 = in->yyt19;
	in->yyt24 = in->yyt18;
	in->yyt23 = in->yyt17;
	in->yyt22 = in->yyt16;
	in->yyt19 = in->yyt13;
	in->yyt18 = in->yyt12;
	in->yyt17 = in->yyt15;
	in->yyt16 = in->yyt14;
	in->yyt12 = in->yyt13 = in->cur - 1;
	in->yyt15 = in->yyt11;
	in->yyt14 = in->yyt10;
	in->yyt11 = in->yyt9;
	in->yyt10 = in->yyt8;
	in->yyt9 = in->cur - 1;
yyFillLabel3_19:
	yych = *in->cur;
	switch (yych) {
	case '\n':	goto yy34;
	case 'a':	goto yy27;
	case 'b':	goto yy36;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_19;
		}
		goto yy6;
	}
yy29:
	++in->cur;
	in->yyt44 = in->yyt35;
	in->yyt43 = in->yyt33;
	in->yyt25 = in->yyt19;
	in->yyt42 = in->yyt31;
	in->yyt24 = in->yyt18;
	in->yyt41 = in->yyt29;
	in->yyt15 = in->yyt11;
	in->yyt23 = in->yyt17;
	in->yyt40 = in->yyt27;
	in->yyt14 = in->yyt10;
	in->yyt22 = in->yyt16;
	in->yyt39 = in->yyt26;
	in->yyt8 = in->yyt12 = in->yyt13 = in->yyt20 = in->yyt21 = in->yyt37 = in->yyt38 = in->cur - 1;
	in->yyt35 = in->yyt36;
	in->yyt33 = in->yyt34;
	in->yyt19 = in->yyt6;
	in->yyt31 = in->yyt32;
	in->yyt18 = in->yyt5;
	in->yyt29 = in->yyt30;
	in->yyt11 = in->yyt2;
	in->yyt17 = in->yyt4;
	in->yyt27 = in->yyt28;
	in->yyt10 = in->yyt1;
	in->yyt16 = in->yyt3;
	in->yyt26 = in->yyt7;
yyFillLabel3_20:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy38;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_20;
		}
		goto yy6;
	}
yy30:
	++in->cur;
	in->yyt36 = in->yyt21;
	in->yyt44 = in->yyt35;
	in->yyt34 = in->yyt20;
	in->yyt43 = in->yyt33;
	in->yyt6 = in->yyt13;
	in->yyt32 = in->yyt25;
	in->yyt42 = in->yyt31;
	in->yyt5 = in->yyt12;
	in->yyt30 = in->yyt24;
	in->yyt41 = in->yyt29;
	in->yyt4 = in->yyt15;
	in->yyt28 = in->yyt23;
	in->yyt40 = in->yyt27;
	in->yyt3 = in->yyt14;
	in->yyt7 = in->yyt22;
	in->yyt39 = in->yyt26;
	in->yyt37 = in->yyt38 = in->cur - 1;
	in->yyt35 = in->yyt21;
	in->yyt33 = in->yyt20;
	in->yyt31 = in->yyt25;
	in->yyt29 = in->yyt24;
	in->yyt27 = in->yyt23;
	in->yyt26 = in->yyt22;
	in->yyt20 = in->yyt21 = in->cur - 1;
	in->yyt25 = in->yyt19;
	in->yyt24 = in->yyt18;
	in->yyt23 = in->yyt17;
	in->yyt22 = in->yyt16;
	in->yyt19 = in->yyt13;
	in->yyt18 = in->yyt12;
	in->yyt17 = in->yyt15;
	in->yyt16 = in->yyt14;
	in->yyt13 = in->cur - 1;
	in->yyt12 = in->yyt8;
	in->yyt15 = in->yyt11;
	in->yyt14 = in->yyt10;
	in->yyt11 = in->yyt2;
	in->yyt10 = in->yyt1;
yyFillLabel3_21:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy39;
	case 'b':	goto yy31;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_21;
		}
		goto yy6;
	}
yy31:
	++in->cur;
	in->yyt35 = in->yyt36;
	in->yyt33 = in->yyt34;
	in->yyt19 = in->yyt6;
	in->yyt31 = in->yyt32;
	in->yyt18 = in->yyt5;
	in->yyt29 = in->yyt30;
	in->yyt17 = in->yyt4;
	in->yyt27 = in->yyt28;
	in->yyt16 = in->yyt3;
	in->yyt26 = in->yyt7;
yyFillLabel3_22:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy41;
	case 'b':	goto yy31;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_22;
		}
		goto yy6;
	}
yy33:
	++in->cur;
	in->yyt36 = in->yyt21;
	in->yyt35 = in->yyt21;
	in->yyt34 = in->yyt20;
	in->yyt33 = in->yyt20;
	in->yyt32 = in->yyt25;
	in->yyt31 = in->yyt25;
	in->yyt30 = in->yyt24;
	in->yyt29 = in->yyt24;
	in->yyt28 = in->yyt23;
	in->yyt27 = in->yyt23;
	in->yyt7 = in->yyt22;
	in->yyt26 = in->yyt22;
	in->yyt21 = in->cur - 1;
	in->yyt20 = in->yyt8;
	in->yyt25 = in->yyt19;
	in->yyt24 = in->yyt18;
	in->yyt23 = in->yyt17;
	in->yyt22 = in->yyt16;
	in->yyt19 = in->yyt6;
	in->yyt18 = in->yyt5;
	in->yyt17 = in->yyt4;
	in->yyt16 = in->yyt3;
yyFillLabel3_23:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy42;
	case 'b':	goto yy43;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_23;
		}
		goto yy6;
	}
yy34:
	++in->cur;
	in->yyt7 = in->yyt52;
	in->yyt6 = in->yyt51;
	in->yyt5 = in->yyt50;
	in->yyt4 = in->yyt49;
	in->yyt3 = in->yyt48;
	in->yyt2 = in->yyt47;
	in->yyt1 = in->yyt46;
	in->yyt8 = in->yyt45;
	a0 = in->yyt8;
	b0 = in->yyt1;
	a1 = in->yyt2;
	b1 = in->yyt3;
	a2 = in->yyt4;
	b2 = in->yyt5;
	a3 = in->yyt6;
	b3 = in->yyt7;
#line 17 "../../../benchmarks/submatch_dfa_aot/src/re2c/24__cat4_2.re"
	{
        outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
        outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
        outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
        outs(out, a3, b3); outc(out, '.'); outs(out, b3, in->cur);
        goto loop;
    }
#line 1073 "gen/re2c/24__cat4_2-eof-stadfa.c"
yy36:
	++in->cur;
	in->yyt35 = in->yyt36;
	in->yyt33 = in->yyt34;
	in->yyt19 = in->yyt6;
	in->yyt31 = in->yyt32;
	in->yyt18 = in->yyt5;
	in->yyt29 = in->yyt30;
	in->yyt11 = in->yyt2;
	in->yyt17 = in->yyt4;
	in->yyt27 = in->yyt28;
	in->yyt10 = in->yyt1;
	in->yyt16 = in->yyt3;
	in->yyt26 = in->yyt7;
yyFillLabel3_24:
	yych = *in->cur;
	switch (yych) {
	case '\n':	goto yy34;
	case 'a':	goto yy29;
	case 'b':	goto yy36;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_24;
		}
		goto yy6;
	}
yy38:
	++in->cur;
	in->yyt52 = in->yyt38;
	in->yyt51 = in->yyt37;
	in->yyt36 = in->yyt21;
	in->yyt50 = in->yyt44;
	in->yyt34 = in->yyt20;
	in->yyt49 = in->yyt43;
	in->yyt6 = in->yyt13;
	in->yyt32 = in->yyt25;
	in->yyt48 = in->yyt42;
	in->yyt5 = in->yyt12;
	in->yyt30 = in->yyt24;
	in->yyt47 = in->yyt41;
	in->yyt4 = in->yyt15;
	in->yyt28 = in->yyt23;
	in->yyt46 = in->yyt40;
	in->yyt3 = in->yyt14;
	in->yyt7 = in->yyt22;
	in->yyt45 = in->yyt39;
	in->yyt38 = in->cur - 1;
	in->yyt37 = in->yyt8;
	in->yyt44 = in->yyt35;
	in->yyt43 = in->yyt33;
	in->yyt42 = in->yyt31;
	in->yyt41 = in->yyt29;
	in->yyt40 = in->yyt27;
	in->yyt39 = in->yyt26;
	in->yyt35 = in->yyt21;
	in->yyt33 = in->yyt20;
	in->yyt31 = in->yyt25;
	in->yyt29 = in->yyt24;
	in->yyt27 = in->yyt23;
	in->yyt26 = in->yyt22;
	in->yyt21 = in->cur - 1;
	in->yyt20 = in->yyt8;
	in->yyt25 = in->yyt19;
	in->yyt24 = in->yyt18;
	in->yyt23 = in->yyt17;
	in->yyt22 = in->yyt16;
	in->yyt19 = in->yyt13;
	in->yyt18 = in->yyt12;
	in->yyt17 = in->yyt15;
	in->yyt16 = in->yyt14;
	in->yyt13 = in->cur - 1;
	in->yyt12 = in->yyt8;
	in->yyt15 = in->yyt11;
	in->yyt14 = in->yyt10;
	in->yyt11 = in->yyt2;
	in->yyt10 = in->yyt1;
yyFillLabel3_25:
	yych = *in->cur;
	switch (yych) {
	case '\n':	goto yy34;
	case 'a':	goto yy39;
	case 'b':	goto yy45;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_25;
		}
		goto yy6;
	}
yy39:
	++in->cur;
	in->yyt52 = in->yyt38;
	in->yyt51 = in->yyt37;
	in->yyt36 = in->yyt21;
	in->yyt50 = in->yyt44;
	in->yyt34 = in->yyt20;
	in->yyt49 = in->yyt43;
	in->yyt6 = in->yyt13;
	in->yyt32 = in->yyt25;
	in->yyt48 = in->yyt42;
	in->yyt5 = in->yyt12;
	in->yyt30 = in->yyt24;
	in->yyt47 = in->yyt41;
	in->yyt4 = in->yyt15;
	in->yyt28 = in->yyt23;
	in->yyt46 = in->yyt40;
	in->yyt3 = in->yyt14;
	in->yyt7 = in->yyt22;
	in->yyt45 = in->yyt39;
	in->yyt37 = in->yyt38 = in->cur - 1;
	in->yyt44 = in->yyt35;
	in->yyt43 = in->yyt33;
	in->yyt42 = in->yyt31;
	in->yyt41 = in->yyt29;
	in->yyt40 = in->yyt27;
	in->yyt39 = in->yyt26;
	in->yyt35 = in->yyt21;
	in->yyt33 = in->yyt20;
	in->yyt31 = in->yyt25;
	in->yyt29 = in->yyt24;
	in->yyt27 = in->yyt23;
	in->yyt26 = in->yyt22;
	in->yyt20 = in->yyt21 = in->cur - 1;
	in->yyt25 = in->yyt19;
	in->yyt24 = in->yyt18;
	in->yyt23 = in->yyt17;
	in->yyt22 = in->yyt16;
	in->yyt19 = in->yyt13;
	in->yyt18 = in->yyt12;
	in->yyt17 = in->yyt15;
	in->yyt16 = in->yyt14;
	in->yyt13 = in->cur - 1;
	in->yyt12 = in->yyt8;
	in->yyt15 = in->yyt11;
	in->yyt14 = in->yyt10;
	in->yyt11 = in->yyt2;
	in->yyt10 = in->yyt1;
yyFillLabel3_26:
	yych = *in->cur;
	switch (yych) {
	case '\n':	goto yy34;
	case 'a':	goto yy39;
	case 'b':	goto yy45;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_26;
		}
		goto yy6;
	}
yy41:
	++in->cur;
	in->yyt44 = in->yyt35;
	in->yyt43 = in->yyt33;
	in->yyt25 = in->yyt19;
	in->yyt42 = in->yyt31;
	in->yyt24 = in->yyt18;
	in->yyt41 = in->yyt29;
	in->yyt23 = in->yyt17;
	in->yyt40 = in->yyt27;
	in->yyt22 = in->yyt16;
	in->yyt39 = in->yyt26;
	in->yyt8 = in->yyt20 = in->yyt21 = in->yyt37 = in->yyt38 = in->cur - 1;
	in->yyt35 = in->yyt36;
	in->yyt33 = in->yyt34;
	in->yyt19 = in->yyt6;
	in->yyt31 = in->yyt32;
	in->yyt18 = in->yyt5;
	in->yyt29 = in->yyt30;
	in->yyt17 = in->yyt4;
	in->yyt27 = in->yyt28;
	in->yyt16 = in->yyt3;
	in->yyt26 = in->yyt7;
yyFillLabel3_27:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy47;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_27;
		}
		goto yy6;
	}
yy42:
	++in->cur;
	in->yyt36 = in->yyt21;
	in->yyt44 = in->yyt35;
	in->yyt34 = in->yyt20;
	in->yyt43 = in->yyt33;
	in->yyt32 = in->yyt25;
	in->yyt42 = in->yyt31;
	in->yyt30 = in->yyt24;
	in->yyt41 = in->yyt29;
	in->yyt28 = in->yyt23;
	in->yyt40 = in->yyt27;
	in->yyt7 = in->yyt22;
	in->yyt39 = in->yyt26;
	in->yyt37 = in->yyt38 = in->cur - 1;
	in->yyt35 = in->yyt21;
	in->yyt33 = in->yyt20;
	in->yyt31 = in->yyt25;
	in->yyt29 = in->yyt24;
	in->yyt27 = in->yyt23;
	in->yyt26 = in->yyt22;
	in->yyt21 = in->cur - 1;
	in->yyt20 = in->yyt8;
	in->yyt25 = in->yyt19;
	in->yyt24 = in->yyt18;
	in->yyt23 = in->yyt17;
	in->yyt22 = in->yyt16;
	in->yyt19 = in->yyt6;
	in->yyt18 = in->yyt5;
	in->yyt17 = in->yyt4;
	in->yyt16 = in->yyt3;
yyFillLabel3_28:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy48;
	case 'b':	goto yy43;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_28;
		}
		goto yy6;
	}
yy43:
	++in->cur;
	in->yyt35 = in->yyt36;
	in->yyt33 = in->yyt34;
	in->yyt31 = in->yyt32;
	in->yyt29 = in->yyt30;
	in->yyt27 = in->yyt28;
	in->yyt26 = in->yyt7;
yyFillLabel3_29:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy50;
	case 'b':	goto yy43;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_29;
		}
		goto yy6;
	}
yy45:
	++in->cur;
	in->yyt35 = in->yyt36;
	in->yyt33 = in->yyt34;
	in->yyt19 = in->yyt6;
	in->yyt31 = in->yyt32;
	in->yyt18 = in->yyt5;
	in->yyt29 = in->yyt30;
	in->yyt17 = in->yyt4;
	in->yyt27 = in->yyt28;
	in->yyt16 = in->yyt3;
	in->yyt26 = in->yyt7;
yyFillLabel3_30:
	yych = *in->cur;
	switch (yych) {
	case '\n':	goto yy34;
	case 'a':	goto yy41;
	case 'b':	goto yy45;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_30;
		}
		goto yy6;
	}
yy47:
	++in->cur;
	in->yyt52 = in->yyt38;
	in->yyt51 = in->yyt37;
	in->yyt36 = in->yyt21;
	in->yyt50 = in->yyt44;
	in->yyt34 = in->yyt20;
	in->yyt49 = in->yyt43;
	in->yyt32 = in->yyt25;
	in->yyt48 = in->yyt42;
	in->yyt30 = in->yyt24;
	in->yyt47 = in->yyt41;
	in->yyt28 = in->yyt23;
	in->yyt46 = in->yyt40;
	in->yyt7 = in->yyt22;
	in->yyt45 = in->yyt39;
	in->yyt38 = in->cur - 1;
	in->yyt37 = in->yyt8;
	in->yyt44 = in->yyt35;
	in->yyt43 = in->yyt33;
	in->yyt42 = in->yyt31;
	in->yyt41 = in->yyt29;
	in->yyt40 = in->yyt27;
	in->yyt39 = in->yyt26;
	in->yyt35 = in->yyt21;
	in->yyt33 = in->yyt20;
	in->yyt31 = in->yyt25;
	in->yyt29 = in->yyt24;
	in->yyt27 = in->yyt23;
	in->yyt26 = in->yyt22;
	in->yyt21 = in->cur - 1;
	in->yyt20 = in->yyt8;
	in->yyt25 = in->yyt19;
	in->yyt24 = in->yyt18;
	in->yyt23 = in->yyt17;
	in->yyt22 = in->yyt16;
	in->yyt19 = in->yyt6;
	in->yyt18 = in->yyt5;
	in->yyt17 = in->yyt4;
	in->yyt16 = in->yyt3;
yyFillLabel3_31:
	yych = *in->cur;
	switch (yych) {
	case '\n':	goto yy34;
	case 'a':	goto yy48;
	case 'b':	goto yy51;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_31;
		}
		goto yy6;
	}
yy48:
	++in->cur;
	in->yyt52 = in->yyt38;
	in->yyt51 = in->yyt37;
	in->yyt36 = in->yyt21;
	in->yyt50 = in->yyt44;
	in->yyt34 = in->yyt20;
	in->yyt49 = in->yyt43;
	in->yyt32 = in->yyt25;
	in->yyt48 = in->yyt42;
	in->yyt30 = in->yyt24;
	in->yyt47 = in->yyt41;
	in->yyt28 = in->yyt23;
	in->yyt46 = in->yyt40;
	in->yyt7 = in->yyt22;
	in->yyt45 = in->yyt39;
	in->yyt37 = in->yyt38 = in->cur - 1;
	in->yyt44 = in->yyt35;
	in->yyt43 = in->yyt33;
	in->yyt42 = in->yyt31;
	in->yyt41 = in->yyt29;
	in->yyt40 = in->yyt27;
	in->yyt39 = in->yyt26;
	in->yyt35 = in->yyt21;
	in->yyt33 = in->yyt20;
	in->yyt31 = in->yyt25;
	in->yyt29 = in->yyt24;
	in->yyt27 = in->yyt23;
	in->yyt26 = in->yyt22;
	in->yyt21 = in->cur - 1;
	in->yyt20 = in->yyt8;
	in->yyt25 = in->yyt19;
	in->yyt24 = in->yyt18;
	in->yyt23 = in->yyt17;
	in->yyt22 = in->yyt16;
	in->yyt19 = in->yyt6;
	in->yyt18 = in->yyt5;
	in->yyt17 = in->yyt4;
	in->yyt16 = in->yyt3;
yyFillLabel3_32:
	yych = *in->cur;
	switch (yych) {
	case '\n':	goto yy34;
	case 'a':	goto yy48;
	case 'b':	goto yy51;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_32;
		}
		goto yy6;
	}
yy50:
	++in->cur;
	in->yyt44 = in->yyt35;
	in->yyt43 = in->yyt33;
	in->yyt42 = in->yyt31;
	in->yyt41 = in->yyt29;
	in->yyt40 = in->yyt27;
	in->yyt39 = in->yyt26;
	in->yyt8 = in->yyt37 = in->yyt38 = in->cur - 1;
	in->yyt35 = in->yyt36;
	in->yyt33 = in->yyt34;
	in->yyt31 = in->yyt32;
	in->yyt29 = in->yyt30;
	in->yyt27 = in->yyt28;
	in->yyt26 = in->yyt7;
yyFillLabel3_33:
	yych = *in->cur;
	switch (yych) {
	case 'a':	goto yy53;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_33;
		}
		goto yy6;
	}
yy51:
	++in->cur;
	in->yyt35 = in->yyt36;
	in->yyt33 = in->yyt34;
	in->yyt31 = in->yyt32;
	in->yyt29 = in->yyt30;
	in->yyt27 = in->yyt28;
	in->yyt26 = in->yyt7;
yyFillLabel3_34:
	yych = *in->cur;
	switch (yych) {
	case '\n':	goto yy34;
	case 'a':	goto yy50;
	case 'b':	goto yy51;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_34;
		}
		goto yy6;
	}
yy53:
	++in->cur;
	in->yyt52 = in->yyt38;
	in->yyt51 = in->yyt37;
	in->yyt50 = in->yyt44;
	in->yyt49 = in->yyt43;
	in->yyt48 = in->yyt42;
	in->yyt47 = in->yyt41;
	in->yyt46 = in->yyt40;
	in->yyt45 = in->yyt39;
	in->yyt38 = in->cur - 1;
	in->yyt37 = in->yyt8;
	in->yyt44 = in->yyt35;
	in->yyt43 = in->yyt33;
	in->yyt42 = in->yyt31;
	in->yyt41 = in->yyt29;
	in->yyt40 = in->yyt27;
	in->yyt39 = in->yyt26;
	in->yyt35 = in->yyt36;
	in->yyt33 = in->yyt34;
	in->yyt31 = in->yyt32;
	in->yyt29 = in->yyt30;
	in->yyt27 = in->yyt28;
	in->yyt26 = in->yyt7;
yyFillLabel3_35:
	yych = *in->cur;
	switch (yych) {
	case '\n':	goto yy34;
	case 'a':	goto yy53;
	case 'b':	goto yy55;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_35;
		}
		goto yy6;
	}
yy55:
	++in->cur;
yyFillLabel3_36:
	yych = *in->cur;
	switch (yych) {
	case '\n':	goto yy34;
	case 'b':	goto yy55;
	default:
		if (in->lim <= in->cur) {
			if (fill(in) == 0) goto yyFillLabel3_36;
		}
		goto yy6;
	}
yy57:
#line 5 "../../../benchmarks/submatch_dfa_aot/src/re2c/include-eof/fill.re"
	{ return 0; }
#line 1540 "gen/re2c/24__cat4_2-eof-stadfa.c"
}
#line 24 "../../../benchmarks/submatch_dfa_aot/src/re2c/24__cat4_2.re"

}
