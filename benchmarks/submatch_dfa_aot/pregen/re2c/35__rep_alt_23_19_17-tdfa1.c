/* Generated by re2c */
#line 1 "../../../benchmarks/submatch_dfa_aot/src/re2c/35__rep_alt_23_19_17.re"
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
taglist_t *yyt18;
taglist_t *yyt19;
taglist_t *yyt2;
taglist_t *yyt20;
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
in->yyt18 = 0;
in->yyt19 = 0;
in->yyt2 = 0;
in->yyt20 = 0;
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


#define YYMAXFILL 140


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
in->yyt18 = 0;
in->yyt19 = 0;
in->yyt2 = 0;
in->yyt20 = 0;
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


static const char *print(Output *out, const char *tok, const taglist_t *t)
{
    if (!t) return tok;

    const char *s = print(out, tok, t->pred);
    const char *e = tok + t->dist;
    outs(out, s, e);
    outc(out, '.');
    return e;
}

static int lex(input_t *in, Output *out)
{
    taglist_t *t = NULL;

loop:
    in->tok = in->cur;

#line 232 "gen/re2c/35__rep_alt_23_19_17-tdfa1.c"
{
	char yych;
	if ((in->lim - in->cur) < 140) if (fill(in, 140) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case 0x00:	goto yy2;
	case '\n':
		taglist(&in->yyt1, in->tok, in->tok - 1, &in->tlp);
		goto yy6;
	case 'a':	goto yy8;
	default:	goto yy4;
	}
yy2:
	++in->cur;
#line 3 "../../../benchmarks/submatch_dfa_aot/src/re2c/include/fill.re"
	{ return 0; }
#line 249 "gen/re2c/35__rep_alt_23_19_17-tdfa1.c"
yy4:
	++in->cur;
yy5:
#line 23 "../../../benchmarks/submatch_dfa_aot/src/re2c/35__rep_alt_23_19_17.re"
	{ return 1; }
#line 255 "gen/re2c/35__rep_alt_23_19_17-tdfa1.c"
yy6:
	++in->cur;
	t = in->yyt1;
#line 24 "../../../benchmarks/submatch_dfa_aot/src/re2c/35__rep_alt_23_19_17.re"
	{
        print(out, in->tok, t);
        outc(out, '\n');
        taglistpool_clear(&in->tlp, in);
        goto loop;
    }
#line 266 "gen/re2c/35__rep_alt_23_19_17-tdfa1.c"
yy8:
	yych = *(in->mar = ++in->cur);
	switch (yych) {
	case 'a':	goto yy9;
	default:	goto yy5;
	}
yy9:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy11;
	default:	goto yy10;
	}
yy10:
	in->cur = in->mar;
	goto yy5;
yy11:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy12;
	default:	goto yy10;
	}
yy12:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy13;
	default:	goto yy10;
	}
yy13:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy14;
	default:	goto yy10;
	}
yy14:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy15;
	default:	goto yy10;
	}
yy15:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy16;
	default:	goto yy10;
	}
yy16:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy17;
	default:	goto yy10;
	}
yy17:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy18;
	default:	goto yy10;
	}
yy18:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy19;
	default:	goto yy10;
	}
yy19:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy20;
	default:	goto yy10;
	}
yy20:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy21;
	default:	goto yy10;
	}
yy21:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy22;
	default:	goto yy10;
	}
yy22:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy23;
	default:	goto yy10;
	}
yy23:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy24;
	default:	goto yy10;
	}
yy24:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy25;
	default:	goto yy10;
	}
yy25:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt2 = in->yyt1;
		taglist(&in->yyt2, in->tok, in->cur, &in->tlp);
		goto yy26;
	default:	goto yy10;
	}
yy26:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy27;
	default:	goto yy10;
	}
yy27:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt3 = in->yyt1;
		taglist(&in->yyt3, in->tok, in->cur, &in->tlp);
		goto yy28;
	default:	goto yy10;
	}
yy28:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy29;
	default:	goto yy10;
	}
yy29:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy30;
	default:	goto yy10;
	}
yy30:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy31;
	default:	goto yy10;
	}
yy31:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy32;
	default:	goto yy10;
	}
yy32:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy33;
	default:	goto yy10;
	}
yy33:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy34;
	default:	goto yy10;
	}
yy34:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy35;
	default:	goto yy10;
	}
yy35:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy36;
	default:	goto yy10;
	}
yy36:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy37;
	default:	goto yy10;
	}
yy37:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy38;
	default:	goto yy10;
	}
yy38:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy39;
	default:	goto yy10;
	}
yy39:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy40;
	default:	goto yy10;
	}
yy40:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy41;
	default:	goto yy10;
	}
yy41:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy42;
	default:	goto yy10;
	}
yy42:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt2;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt2, in->tok, in->cur, &in->tlp);
		goto yy43;
	default:	goto yy10;
	}
yy43:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy44;
	default:	goto yy10;
	}
yy44:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt3;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt4 = in->yyt3;
		taglist(&in->yyt4, in->tok, in->cur, &in->tlp);
		goto yy45;
	default:	goto yy10;
	}
yy45:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy46;
	default:	goto yy10;
	}
yy46:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt3;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt3, in->tok, in->cur, &in->tlp);
		goto yy47;
	default:	goto yy10;
	}
yy47:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy48;
	default:	goto yy10;
	}
yy48:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt5 = in->yyt1;
		taglist(&in->yyt5, in->tok, in->cur, &in->tlp);
		goto yy49;
	default:	goto yy10;
	}
yy49:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy50;
	default:	goto yy10;
	}
yy50:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt6 = in->yyt1;
		taglist(&in->yyt6, in->tok, in->cur, &in->tlp);
		goto yy51;
	default:	goto yy10;
	}
yy51:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy52;
	default:	goto yy10;
	}
yy52:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy53;
	default:	goto yy10;
	}
yy53:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy54;
	default:	goto yy10;
	}
yy54:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy55;
	default:	goto yy10;
	}
yy55:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy56;
	default:	goto yy10;
	}
yy56:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy57;
	default:	goto yy10;
	}
yy57:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy58;
	default:	goto yy10;
	}
yy58:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy59;
	default:	goto yy10;
	}
yy59:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt2;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt2, in->tok, in->cur, &in->tlp);
		goto yy60;
	default:	goto yy10;
	}
yy60:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy61;
	default:	goto yy10;
	}
yy61:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt4;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt4, in->tok, in->cur, &in->tlp);
		goto yy62;
	default:	goto yy10;
	}
yy62:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy63;
	default:	goto yy10;
	}
yy63:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt3;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt3, in->tok, in->cur, &in->tlp);
		goto yy64;
	default:	goto yy10;
	}
yy64:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy65;
	default:	goto yy10;
	}
yy65:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt5;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt5, in->tok, in->cur, &in->tlp);
		goto yy66;
	default:	goto yy10;
	}
yy66:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy67;
	default:	goto yy10;
	}
yy67:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt6;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt7 = in->yyt6;
		taglist(&in->yyt7, in->tok, in->cur, &in->tlp);
		goto yy68;
	default:	goto yy10;
	}
yy68:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy69;
	default:	goto yy10;
	}
yy69:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt6;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt6, in->tok, in->cur, &in->tlp);
		goto yy70;
	default:	goto yy10;
	}
yy70:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy71;
	default:	goto yy10;
	}
yy71:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt8 = in->yyt1;
		taglist(&in->yyt8, in->tok, in->cur, &in->tlp);
		goto yy72;
	default:	goto yy10;
	}
yy72:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy73;
	default:	goto yy10;
	}
yy73:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt9 = in->yyt1;
		taglist(&in->yyt9, in->tok, in->cur, &in->tlp);
		goto yy74;
	default:	goto yy10;
	}
yy74:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy75;
	default:	goto yy10;
	}
yy75:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy76;
	default:	goto yy10;
	}
yy76:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt2;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt2, in->tok, in->cur, &in->tlp);
		goto yy77;
	default:	goto yy10;
	}
yy77:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy78;
	default:	goto yy10;
	}
yy78:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt4;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt4, in->tok, in->cur, &in->tlp);
		goto yy79;
	default:	goto yy10;
	}
yy79:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy80;
	default:	goto yy10;
	}
yy80:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt3;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt3, in->tok, in->cur, &in->tlp);
		goto yy81;
	default:	goto yy10;
	}
yy81:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy82;
	default:	goto yy10;
	}
yy82:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt5;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt5, in->tok, in->cur, &in->tlp);
		goto yy83;
	default:	goto yy10;
	}
yy83:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy84;
	default:	goto yy10;
	}
yy84:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt7;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt7, in->tok, in->cur, &in->tlp);
		goto yy85;
	default:	goto yy10;
	}
yy85:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy86;
	default:	goto yy10;
	}
yy86:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt6;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt6, in->tok, in->cur, &in->tlp);
		goto yy87;
	default:	goto yy10;
	}
yy87:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy88;
	default:	goto yy10;
	}
yy88:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt8;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt8, in->tok, in->cur, &in->tlp);
		goto yy89;
	default:	goto yy10;
	}
yy89:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy90;
	default:	goto yy10;
	}
yy90:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt9;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt10 = in->yyt9;
		taglist(&in->yyt10, in->tok, in->cur, &in->tlp);
		goto yy91;
	default:	goto yy10;
	}
yy91:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy92;
	default:	goto yy10;
	}
yy92:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt9;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt9, in->tok, in->cur, &in->tlp);
		goto yy93;
	default:	goto yy10;
	}
yy93:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt2;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt2, in->tok, in->cur, &in->tlp);
		goto yy94;
	default:	goto yy10;
	}
yy94:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt11 = in->yyt1;
		taglist(&in->yyt11, in->tok, in->cur, &in->tlp);
		goto yy95;
	default:	goto yy10;
	}
yy95:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt4;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt4, in->tok, in->cur, &in->tlp);
		goto yy96;
	default:	goto yy10;
	}
yy96:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt12 = in->yyt1;
		taglist(&in->yyt12, in->tok, in->cur, &in->tlp);
		goto yy97;
	default:	goto yy10;
	}
yy97:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt3;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt3, in->tok, in->cur, &in->tlp);
		goto yy98;
	default:	goto yy10;
	}
yy98:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy99;
	default:	goto yy10;
	}
yy99:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt5;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt5, in->tok, in->cur, &in->tlp);
		goto yy100;
	default:	goto yy10;
	}
yy100:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy101;
	default:	goto yy10;
	}
yy101:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt7;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt7, in->tok, in->cur, &in->tlp);
		goto yy102;
	default:	goto yy10;
	}
yy102:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy103;
	default:	goto yy10;
	}
yy103:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt6;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt6, in->tok, in->cur, &in->tlp);
		goto yy104;
	default:	goto yy10;
	}
yy104:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy105;
	default:	goto yy10;
	}
yy105:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt8;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt8, in->tok, in->cur, &in->tlp);
		goto yy106;
	default:	goto yy10;
	}
yy106:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy107;
	default:	goto yy10;
	}
yy107:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt10;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt10, in->tok, in->cur, &in->tlp);
		goto yy108;
	default:	goto yy10;
	}
yy108:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy109;
	default:	goto yy10;
	}
yy109:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt9;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt9, in->tok, in->cur, &in->tlp);
		goto yy110;
	default:	goto yy10;
	}
yy110:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt2;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt2, in->tok, in->cur, &in->tlp);
		goto yy111;
	default:	goto yy10;
	}
yy111:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt11;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt11, in->tok, in->cur, &in->tlp);
		goto yy112;
	default:	goto yy10;
	}
yy112:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt4;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt4, in->tok, in->cur, &in->tlp);
		goto yy113;
	default:	goto yy10;
	}
yy113:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt12;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt13 = in->yyt12;
		taglist(&in->yyt13, in->tok, in->cur, &in->tlp);
		goto yy114;
	default:	goto yy10;
	}
yy114:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt3;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt3, in->tok, in->cur, &in->tlp);
		goto yy115;
	default:	goto yy10;
	}
yy115:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt12;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt12, in->tok, in->cur, &in->tlp);
		goto yy116;
	default:	goto yy10;
	}
yy116:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt5;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt5, in->tok, in->cur, &in->tlp);
		goto yy117;
	default:	goto yy10;
	}
yy117:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt14 = in->yyt1;
		taglist(&in->yyt14, in->tok, in->cur, &in->tlp);
		goto yy118;
	default:	goto yy10;
	}
yy118:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt7;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt7, in->tok, in->cur, &in->tlp);
		goto yy119;
	default:	goto yy10;
	}
yy119:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt15 = in->yyt1;
		taglist(&in->yyt15, in->tok, in->cur, &in->tlp);
		goto yy120;
	default:	goto yy10;
	}
yy120:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt6;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt6, in->tok, in->cur, &in->tlp);
		goto yy121;
	default:	goto yy10;
	}
yy121:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy122;
	default:	goto yy10;
	}
yy122:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt8;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt8, in->tok, in->cur, &in->tlp);
		goto yy123;
	default:	goto yy10;
	}
yy123:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy124;
	default:	goto yy10;
	}
yy124:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt10;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt10, in->tok, in->cur, &in->tlp);
		goto yy125;
	default:	goto yy10;
	}
yy125:
	yych = *++in->cur;
	switch (yych) {
	case 'a':	goto yy126;
	default:	goto yy10;
	}
yy126:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt9;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt9, in->tok, in->cur, &in->tlp);
		goto yy127;
	default:	goto yy10;
	}
yy127:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt2;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt2, in->tok, in->cur, &in->tlp);
		goto yy128;
	default:	goto yy10;
	}
yy128:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt11;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt11, in->tok, in->cur, &in->tlp);
		goto yy129;
	default:	goto yy10;
	}
yy129:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt4;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':	goto yy130;
	default:	goto yy10;
	}
yy130:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt13;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt13, in->tok, in->cur, &in->tlp);
		goto yy131;
	default:	goto yy10;
	}
yy131:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt3;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt3, in->tok, in->cur, &in->tlp);
		goto yy132;
	default:	goto yy10;
	}
yy132:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt12;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt12, in->tok, in->cur, &in->tlp);
		goto yy133;
	default:	goto yy10;
	}
yy133:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt5;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt5, in->tok, in->cur, &in->tlp);
		goto yy134;
	default:	goto yy10;
	}
yy134:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt14;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt14, in->tok, in->cur, &in->tlp);
		goto yy135;
	default:	goto yy10;
	}
yy135:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt7;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt7, in->tok, in->cur, &in->tlp);
		goto yy136;
	default:	goto yy10;
	}
yy136:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt15;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt4 = in->yyt15;
		taglist(&in->yyt4, in->tok, in->cur, &in->tlp);
		goto yy137;
	default:	goto yy10;
	}
yy137:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt6;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt6, in->tok, in->cur, &in->tlp);
		goto yy138;
	default:	goto yy10;
	}
yy138:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt15;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt15, in->tok, in->cur, &in->tlp);
		goto yy139;
	default:	goto yy10;
	}
yy139:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt8;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt8, in->tok, in->cur, &in->tlp);
		goto yy140;
	default:	goto yy10;
	}
yy140:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt16 = in->yyt1;
		taglist(&in->yyt16, in->tok, in->cur, &in->tlp);
		goto yy141;
	default:	goto yy10;
	}
yy141:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt10;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt10, in->tok, in->cur, &in->tlp);
		goto yy142;
	default:	goto yy10;
	}
yy142:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt17 = in->yyt1;
		taglist(&in->yyt17, in->tok, in->cur, &in->tlp);
		goto yy143;
	default:	goto yy10;
	}
yy143:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt9;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt9, in->tok, in->cur, &in->tlp);
		goto yy144;
	default:	goto yy10;
	}
yy144:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt2;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':	goto yy145;
	default:	goto yy10;
	}
yy145:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt11;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt11, in->tok, in->cur, &in->tlp);
		goto yy146;
	default:	goto yy10;
	}
yy146:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy147;
	default:	goto yy10;
	}
yy147:
	yych = *++in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt13;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt13, in->tok, in->cur, &in->tlp);
		goto yy148;
	default:	goto yy10;
	}
yy148:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt3;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':	goto yy149;
	default:	goto yy10;
	}
yy149:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt12;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt12, in->tok, in->cur, &in->tlp);
		goto yy150;
	default:	goto yy10;
	}
yy150:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt5;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt5, in->tok, in->cur, &in->tlp);
		goto yy151;
	default:	goto yy10;
	}
yy151:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt14;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt14, in->tok, in->cur, &in->tlp);
		goto yy152;
	default:	goto yy10;
	}
yy152:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt7;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':	goto yy153;
	default:	goto yy10;
	}
yy153:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt4;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt2 = in->yyt4;
		taglist(&in->yyt2, in->tok, in->cur, &in->tlp);
		goto yy154;
	default:	goto yy10;
	}
yy154:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt6;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt3 = in->yyt6;
		taglist(&in->yyt3, in->tok, in->cur, &in->tlp);
		goto yy155;
	default:	goto yy10;
	}
yy155:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt15;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt18 = in->yyt15;
		taglist(&in->yyt18, in->tok, in->cur, &in->tlp);
		goto yy156;
	default:	goto yy10;
	}
yy156:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt8;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt19 = in->yyt8;
		taglist(&in->yyt19, in->tok, in->cur, &in->tlp);
		goto yy157;
	default:	goto yy10;
	}
yy157:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt16;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt20 = in->yyt16;
		taglist(&in->yyt20, in->tok, in->cur, &in->tlp);
		goto yy158;
	default:	goto yy10;
	}
yy158:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt10;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt7 = in->yyt10;
		taglist(&in->yyt7, in->tok, in->cur, &in->tlp);
		goto yy159;
	default:	goto yy10;
	}
yy159:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt17;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt4 = in->yyt17;
		taglist(&in->yyt4, in->tok, in->cur, &in->tlp);
		goto yy160;
	default:	goto yy10;
	}
yy160:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt9;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt6 = in->yyt9;
		taglist(&in->yyt6, in->tok, in->cur, &in->tlp);
		goto yy161;
	default:	goto yy10;
	}
yy161:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt17;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt15 = in->yyt17;
		taglist(&in->yyt15, in->tok, in->cur, &in->tlp);
		goto yy162;
	default:	goto yy10;
	}
yy162:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt11;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt8 = in->yyt11;
		taglist(&in->yyt8, in->tok, in->cur, &in->tlp);
		goto yy163;
	default:	goto yy10;
	}
yy163:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt16 = in->yyt1;
		taglist(&in->yyt16, in->tok, in->cur, &in->tlp);
		goto yy164;
	default:	goto yy10;
	}
yy164:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt13;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt13, in->tok, in->cur, &in->tlp);
		goto yy165;
	default:	goto yy10;
	}
yy165:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt17 = in->yyt1;
		taglist(&in->yyt17, in->tok, in->cur, &in->tlp);
		goto yy166;
	default:	goto yy10;
	}
yy166:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt12;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt12, in->tok, in->cur, &in->tlp);
		goto yy167;
	default:	goto yy10;
	}
yy167:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt5;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':	goto yy168;
	default:	goto yy10;
	}
yy168:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt14;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt14, in->tok, in->cur, &in->tlp);
		goto yy169;
	default:	goto yy10;
	}
yy169:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy170;
	default:	goto yy10;
	}
yy170:
	++in->cur;
	if (in->lim <= in->cur) if (fill(in, 1) != 0) return 1;
	yych = *in->cur;
	switch (yych) {
	case '\n':
		in->yyt1 = in->yyt2;
		taglist(&in->yyt1, in->tok, in->cur, &in->tlp);
		goto yy6;
	case 'a':
		in->yyt5 = in->yyt19;
		in->yyt9 = in->yyt12;
		in->yyt10 = in->yyt13;
		in->yyt11 = in->yyt14;
		in->yyt12 = in->yyt18;
		in->yyt14 = in->yyt20;
		in->yyt13 = in->yyt2;
		taglist(&in->yyt13, in->tok, in->cur, &in->tlp);
		goto yy148;
	default:	goto yy10;
	}
}
#line 30 "../../../benchmarks/submatch_dfa_aot/src/re2c/35__rep_alt_23_19_17.re"

}
