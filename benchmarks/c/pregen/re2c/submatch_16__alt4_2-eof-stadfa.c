/* Generated by re2c */
#line 1 "../../../benchmarks/c/src/re2c/submatch_16__alt4_2.re"
#line 1 "../../../benchmarks/c/src/re2c/common.re"
#include <assert.h>
#include <stdlib.h>
#include "common.h"

#line 15 "../../../benchmarks/c/src/re2c/common.re"


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
    
#line 30 "gen/re2c/submatch_16__alt4_2-eof-stadfa.c"
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
char *yyt4;
char *yyt5;
char *yyt6;
char *yyt7;
char *yyt8;
char *yyt9;
#line 34 "../../../benchmarks/c/src/re2c/common.re"

    
#line 70 "gen/re2c/submatch_16__alt4_2-eof-stadfa.c"
#line 35 "../../../benchmarks/c/src/re2c/common.re"

    taglistpool_t tlp;
    int eof;
} input_t;

static inline void taglistpool_clear(taglistpool_t *tlp, input_t *in)
{
    tlp->next = tlp->head;
    
#line 81 "gen/re2c/submatch_16__alt4_2-eof-stadfa.c"
#line 43 "../../../benchmarks/c/src/re2c/common.re"

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

#line 1 "../../../benchmarks/c/src/re2c/include-eof/fill.re"
#line 6 "../../../benchmarks/c/src/re2c/include-eof/fill.re"


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
    
#line 139 "gen/re2c/submatch_16__alt4_2-eof-stadfa.c"
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
if (in->yyt4) in->yyt4 -= free;
if (in->yyt5) in->yyt5 -= free;
if (in->yyt6) in->yyt6 -= free;
if (in->yyt7) in->yyt7 -= free;
if (in->yyt8) in->yyt8 -= free;
if (in->yyt9) in->yyt9 -= free;
#line 21 "../../../benchmarks/c/src/re2c/include-eof/fill.re"


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
    
#line 197 "gen/re2c/submatch_16__alt4_2-eof-stadfa.c"
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
in->yyt4 = 0;
in->yyt5 = 0;
in->yyt6 = 0;
in->yyt7 = 0;
in->yyt8 = 0;
in->yyt9 = 0;
#line 40 "../../../benchmarks/c/src/re2c/include-eof/fill.re"

    
#line 237 "gen/re2c/submatch_16__alt4_2-eof-stadfa.c"
#line 41 "../../../benchmarks/c/src/re2c/include-eof/fill.re"

    taglistpool_init(&in->tlp);
    in->eof = 0;
    fill(in);
}
#line 81 "../../../benchmarks/c/src/re2c/common.re"


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
#line 1 "../../../benchmarks/c/src/re2c/submatch_16__alt4_2.re"


static int lex(input_t *in, Output *out)
{
    const char
        *a1, *b1,
        *a2, *b2,
        *a3, *b3,
        *a4, *b4,
        *a5, *b5,
        *a6, *b6,
        *a7, *b7,
        *a8, *b8;
loop:
    in->tok = in->cur;

#line 295 "gen/re2c/submatch_16__alt4_2-eof-stadfa.c"
{
	char yych;
yyFillLabel0:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy3;
		case 'a': goto yy5;
		case 'b': goto yy6;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel0;
				goto yy25;
			}
			goto yy1;
	}
yy1:
	++in->cur;
yy2:
#line 17 "../../../benchmarks/c/src/re2c/submatch_16__alt4_2.re"
	{ return 1; }
#line 316 "gen/re2c/submatch_16__alt4_2-eof-stadfa.c"
yy3:
	++in->cur;
	in->yyt3 = in->yyt13 = in->yyt27 = in->yyt28 = in->yyt31 = in->yyt32 = in->yyt35 = in->yyt36 = NULL;
	in->yyt4 = in->yyt11 = in->yyt25 = in->yyt26 = in->yyt29 = in->yyt30 = in->yyt33 = in->yyt34 = in->cur - 1;
	in->yyt12 = in->yyt3;
	in->yyt10 = in->yyt4;
	in->yyt9 = in->yyt36;
	in->yyt8 = in->yyt35;
	in->yyt7 = in->yyt34;
	in->yyt6 = in->yyt33;
	in->yyt5 = in->yyt32;
	in->yyt4 = in->yyt31;
	in->yyt22 = in->yyt30;
	in->yyt3 = in->yyt29;
	in->yyt19 = in->yyt28;
	in->yyt2 = in->yyt27;
	in->yyt17 = in->yyt26;
	in->yyt1 = in->yyt25;
yy4:
	a1 = in->yyt1;
	a2 = in->yyt17;
	b1 = in->yyt2;
	b2 = in->yyt19;
	a3 = in->yyt3;
	a4 = in->yyt22;
	b3 = in->yyt4;
	b4 = in->yyt5;
	a5 = in->yyt6;
	a6 = in->yyt7;
	b5 = in->yyt8;
	b6 = in->yyt9;
	a7 = in->yyt10;
	a8 = in->yyt11;
	b7 = in->yyt12;
	b8 = in->yyt13;
#line 31 "../../../benchmarks/c/src/re2c/submatch_16__alt4_2.re"
	{
        if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
        else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
        if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
        else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
        if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
        else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
        if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
        else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
        outc(out, '\n');
        goto loop;
    }
#line 365 "gen/re2c/submatch_16__alt4_2-eof-stadfa.c"
yy5:
	in->mar = ++in->cur;
	in->yyt1 = in->yyt15 = in->yyt25 = in->cur - 1;
yyFillLabel1:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy7;
		case 'a': goto yy8;
		case 'b': goto yy10;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel1;
			}
			goto yy2;
	}
yy6:
	in->mar = ++in->cur;
	in->yyt4 = in->yyt9 = in->yyt11 = in->yyt12 = in->yyt18 = in->yyt19 = in->yyt20 = in->yyt21 = in->yyt22 = in->yyt24 = in->yyt27 = in->yyt28 = in->yyt31 = in->yyt32 = in->yyt35 = in->yyt36 = NULL;
	in->yyt1 = in->yyt2 = in->yyt3 = in->yyt5 = in->yyt6 = in->yyt7 = in->yyt8 = in->yyt10 = in->yyt13 = in->yyt14 = in->yyt15 = in->yyt16 = in->yyt17 = in->yyt23 = in->yyt25 = in->yyt26 = in->yyt29 = in->yyt30 = in->yyt33 = in->yyt34 = in->cur - 1;
yyFillLabel2:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy11;
		case 'a': goto yy12;
		case 'b': goto yy13;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel2;
			}
			goto yy2;
	}
yy7:
	++in->cur;
	in->yyt3 = in->yyt13 = in->yyt27 = in->yyt28 = in->yyt31 = in->yyt32 = in->yyt35 = in->yyt36 = NULL;
	in->yyt4 = in->yyt11 = in->yyt26 = in->yyt29 = in->yyt30 = in->yyt33 = in->yyt34 = in->cur - 1;
	in->yyt12 = in->yyt3;
	in->yyt10 = in->yyt4;
	in->yyt9 = in->yyt36;
	in->yyt8 = in->yyt35;
	in->yyt7 = in->yyt34;
	in->yyt6 = in->yyt33;
	in->yyt5 = in->yyt32;
	in->yyt4 = in->yyt31;
	in->yyt22 = in->yyt30;
	in->yyt3 = in->yyt29;
	in->yyt19 = in->yyt28;
	in->yyt2 = in->yyt27;
	in->yyt17 = in->yyt26;
	in->yyt1 = in->yyt25;
	goto yy4;
yy8:
	++in->cur;
	in->yyt15 = in->yyt1;
	in->yyt25 = in->yyt1;
yyFillLabel3:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy7;
		case 'a': goto yy8;
		case 'b': goto yy10;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel3;
			}
			goto yy9;
	}
yy9:
	in->cur = in->mar;
	goto yy2;
yy10:
	++in->cur;
	in->yyt14 = in->yyt1;
	in->yyt25 = in->yyt15;
	in->yyt4 = in->yyt9 = in->yyt11 = in->yyt12 = in->yyt18 = in->yyt19 = in->yyt20 = in->yyt21 = in->yyt22 = in->yyt24 = in->yyt27 = in->yyt28 = in->yyt31 = in->yyt32 = in->yyt35 = in->yyt36 = NULL;
	in->yyt2 = in->yyt3 = in->yyt5 = in->yyt6 = in->yyt7 = in->yyt8 = in->yyt10 = in->yyt13 = in->yyt16 = in->yyt17 = in->yyt23 = in->yyt26 = in->yyt29 = in->yyt30 = in->yyt33 = in->yyt34 = in->cur - 1;
yyFillLabel4:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy11;
		case 'a': goto yy14;
		case 'b': goto yy15;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel4;
			}
			goto yy9;
	}
yy11:
	++in->cur;
	in->yyt4 = in->yyt11 = NULL;
	in->yyt13 = in->cur - 1;
	in->yyt12 = in->yyt3;
	in->yyt10 = in->yyt4;
	in->yyt9 = in->yyt36;
	in->yyt8 = in->yyt35;
	in->yyt7 = in->yyt34;
	in->yyt6 = in->yyt33;
	in->yyt5 = in->yyt32;
	in->yyt4 = in->yyt31;
	in->yyt22 = in->yyt30;
	in->yyt3 = in->yyt29;
	in->yyt19 = in->yyt28;
	in->yyt2 = in->yyt27;
	in->yyt17 = in->yyt26;
	in->yyt1 = in->yyt25;
	goto yy4;
yy12:
	++in->cur;
	in->yyt35 = in->yyt3;
	in->yyt32 = in->yyt11;
	in->yyt24 = in->yyt10;
	in->yyt31 = in->yyt9;
	in->yyt30 = in->yyt7;
	in->yyt29 = in->yyt23;
	in->yyt28 = in->yyt21;
	in->yyt20 = in->yyt3;
	in->yyt27 = in->yyt18;
	in->yyt26 = in->yyt16;
	in->yyt15 = in->yyt14;
	in->yyt25 = in->yyt14;
	in->yyt1 = in->yyt2 = in->yyt5 = in->yyt8 = in->yyt33 = in->yyt34 = NULL;
	in->yyt4 = in->yyt6 = in->yyt12 = in->yyt13 = in->yyt36 = in->cur - 1;
yyFillLabel5:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy16;
		case 'a': goto yy17;
		case 'b': goto yy18;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel5;
			}
			goto yy9;
	}
yy13:
	++in->cur;
	in->yyt33 = in->yyt13;
	in->yyt32 = in->yyt12;
	in->yyt31 = in->yyt24;
	in->yyt30 = in->yyt8;
	in->yyt23 = in->yyt6;
	in->yyt29 = in->yyt5;
	in->yyt21 = in->yyt4;
	in->yyt28 = in->yyt22;
	in->yyt18 = in->yyt20;
	in->yyt27 = in->yyt19;
	in->yyt16 = in->yyt2;
	in->yyt26 = in->yyt17;
	in->yyt14 = in->yyt1;
	in->yyt25 = in->yyt15;
yyFillLabel6:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy11;
		case 'a': goto yy12;
		case 'b': goto yy13;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel6;
			}
			goto yy9;
	}
yy14:
	++in->cur;
	in->yyt35 = in->yyt3;
	in->yyt32 = in->yyt11;
	in->yyt24 = in->yyt10;
	in->yyt31 = in->yyt9;
	in->yyt30 = in->yyt7;
	in->yyt29 = in->yyt23;
	in->yyt28 = in->yyt21;
	in->yyt27 = in->yyt18;
	in->yyt26 = in->yyt16;
	in->yyt15 = in->yyt14;
	in->yyt25 = in->yyt14;
	in->yyt5 = in->yyt8 = in->yyt33 = in->yyt34 = NULL;
	in->yyt4 = in->yyt12 = in->yyt13 = in->yyt36 = in->cur - 1;
yyFillLabel7:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy16;
		case 'a': goto yy19;
		case 'b': goto yy20;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel7;
			}
			goto yy9;
	}
yy15:
	++in->cur;
	in->yyt33 = in->yyt13;
	in->yyt32 = in->yyt12;
	in->yyt31 = in->yyt24;
	in->yyt30 = in->yyt8;
	in->yyt23 = in->yyt6;
	in->yyt29 = in->yyt5;
	in->yyt21 = in->yyt4;
	in->yyt28 = in->yyt22;
	in->yyt18 = in->yyt20;
	in->yyt27 = in->yyt19;
	in->yyt16 = in->yyt2;
	in->yyt26 = in->yyt17;
	in->yyt14 = in->yyt1;
	in->yyt25 = in->yyt15;
yyFillLabel8:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy11;
		case 'a': goto yy14;
		case 'b': goto yy15;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel8;
			}
			goto yy9;
	}
yy16:
	++in->cur;
	in->yyt3 = in->yyt13 = NULL;
	in->yyt11 = in->cur - 1;
	in->yyt12 = in->yyt3;
	in->yyt10 = in->yyt4;
	in->yyt9 = in->yyt36;
	in->yyt8 = in->yyt35;
	in->yyt7 = in->yyt34;
	in->yyt6 = in->yyt33;
	in->yyt5 = in->yyt32;
	in->yyt4 = in->yyt31;
	in->yyt22 = in->yyt30;
	in->yyt3 = in->yyt29;
	in->yyt19 = in->yyt28;
	in->yyt2 = in->yyt27;
	in->yyt17 = in->yyt26;
	in->yyt1 = in->yyt25;
	goto yy4;
yy17:
	++in->cur;
	in->yyt35 = in->yyt3;
	in->yyt32 = in->yyt11;
	in->yyt24 = in->yyt10;
	in->yyt31 = in->yyt9;
	in->yyt30 = in->yyt7;
	in->yyt29 = in->yyt23;
	in->yyt28 = in->yyt21;
	in->yyt20 = in->yyt3;
	in->yyt27 = in->yyt18;
	in->yyt26 = in->yyt16;
	in->yyt15 = in->yyt14;
	in->yyt25 = in->yyt14;
yyFillLabel9:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy16;
		case 'a': goto yy17;
		case 'b': goto yy18;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel9;
			}
			goto yy9;
	}
yy18:
	++in->cur;
	in->yyt33 = in->yyt13;
	in->yyt32 = in->yyt12;
	in->yyt31 = in->yyt24;
	in->yyt30 = in->yyt8;
	in->yyt23 = in->yyt6;
	in->yyt29 = in->yyt5;
	in->yyt21 = in->yyt4;
	in->yyt28 = in->yyt22;
	in->yyt18 = in->yyt20;
	in->yyt27 = in->yyt19;
	in->yyt16 = in->yyt2;
	in->yyt26 = in->yyt17;
	in->yyt14 = in->yyt1;
	in->yyt25 = in->yyt15;
	in->yyt9 = in->yyt11 = in->yyt35 = in->yyt36 = NULL;
	in->yyt3 = in->yyt7 = in->yyt34 = in->cur - 1;
yyFillLabel10:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy11;
		case 'a': goto yy21;
		case 'b': goto yy22;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel10;
			}
			goto yy9;
	}
yy19:
	++in->cur;
	in->yyt35 = in->yyt3;
	in->yyt32 = in->yyt11;
	in->yyt24 = in->yyt10;
	in->yyt31 = in->yyt9;
	in->yyt30 = in->yyt7;
	in->yyt29 = in->yyt23;
	in->yyt28 = in->yyt21;
	in->yyt27 = in->yyt18;
	in->yyt26 = in->yyt16;
	in->yyt15 = in->yyt14;
	in->yyt25 = in->yyt14;
yyFillLabel11:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy16;
		case 'a': goto yy19;
		case 'b': goto yy20;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel11;
			}
			goto yy9;
	}
yy20:
	++in->cur;
	in->yyt33 = in->yyt13;
	in->yyt32 = in->yyt12;
	in->yyt31 = in->yyt24;
	in->yyt30 = in->yyt8;
	in->yyt29 = in->yyt5;
	in->yyt28 = in->yyt22;
	in->yyt27 = in->yyt19;
	in->yyt26 = in->yyt17;
	in->yyt25 = in->yyt15;
	in->yyt35 = in->yyt36 = NULL;
	in->yyt3 = in->yyt34 = in->cur - 1;
yyFillLabel12:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy11;
		case 'b': goto yy23;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel12;
			}
			goto yy9;
	}
yy21:
	++in->cur;
	in->yyt35 = in->yyt3;
	in->yyt32 = in->yyt11;
	in->yyt31 = in->yyt9;
	in->yyt30 = in->yyt7;
	in->yyt29 = in->yyt23;
	in->yyt28 = in->yyt21;
	in->yyt27 = in->yyt18;
	in->yyt26 = in->yyt16;
	in->yyt25 = in->yyt14;
	in->yyt33 = in->yyt34 = NULL;
	in->yyt4 = in->yyt36 = in->cur - 1;
yyFillLabel13:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy16;
		case 'a': goto yy24;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel13;
			}
			goto yy9;
	}
yy22:
	++in->cur;
	in->yyt33 = in->yyt13;
	in->yyt32 = in->yyt12;
	in->yyt31 = in->yyt24;
	in->yyt30 = in->yyt8;
	in->yyt23 = in->yyt6;
	in->yyt29 = in->yyt5;
	in->yyt21 = in->yyt4;
	in->yyt28 = in->yyt22;
	in->yyt18 = in->yyt20;
	in->yyt27 = in->yyt19;
	in->yyt16 = in->yyt2;
	in->yyt26 = in->yyt17;
	in->yyt14 = in->yyt1;
	in->yyt25 = in->yyt15;
yyFillLabel14:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy11;
		case 'a': goto yy21;
		case 'b': goto yy22;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel14;
			}
			goto yy9;
	}
yy23:
	++in->cur;
	in->yyt33 = in->yyt13;
	in->yyt32 = in->yyt12;
	in->yyt31 = in->yyt24;
	in->yyt30 = in->yyt8;
	in->yyt29 = in->yyt5;
	in->yyt28 = in->yyt22;
	in->yyt27 = in->yyt19;
	in->yyt26 = in->yyt17;
	in->yyt25 = in->yyt15;
yyFillLabel15:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy11;
		case 'b': goto yy23;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel15;
			}
			goto yy9;
	}
yy24:
	++in->cur;
	in->yyt35 = in->yyt3;
	in->yyt32 = in->yyt11;
	in->yyt31 = in->yyt9;
	in->yyt30 = in->yyt7;
	in->yyt29 = in->yyt23;
	in->yyt28 = in->yyt21;
	in->yyt27 = in->yyt18;
	in->yyt26 = in->yyt16;
	in->yyt25 = in->yyt14;
yyFillLabel16:
	yych = *in->cur;
	switch (yych) {
		case '\n': goto yy16;
		case 'a': goto yy24;
		default:
			if (in->lim <= in->cur) {
				if (fill(in) == 0) goto yyFillLabel16;
			}
			goto yy9;
	}
yy25:
#line 5 "../../../benchmarks/c/src/re2c/include-eof/fill.re"
	{ return 0; }
#line 806 "gen/re2c/submatch_16__alt4_2-eof-stadfa.c"
}
#line 43 "../../../benchmarks/c/src/re2c/submatch_16__alt4_2.re"

}
