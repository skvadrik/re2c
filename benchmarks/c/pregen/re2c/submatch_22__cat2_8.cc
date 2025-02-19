/* Generated by re2c */
#include "re2c/base.h"

namespace re2c_submatch_22__cat2_8 {





#define YYMAXFILL 16


struct input_t {
    FILE* file;
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
char *yyt4;
char *yyt5;
char *yyt6;
char *yyt7;
char *yyt8;
char *yyt9;

    
    taglistpool_t tlp;
    int eof;
};

static inline void free_input(input_t *in) {
    free(in->buf);
    taglistpool_free(&in->tlp);
    if (in->file) fclose(in->file);
}

static inline int fill_buffered_eof(input_t *in) {
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
if (in->yyt4) in->yyt4 -= free;
if (in->yyt5) in->yyt5 -= free;
if (in->yyt6) in->yyt6 -= free;
if (in->yyt7) in->yyt7 -= free;
if (in->yyt8) in->yyt8 -= free;
if (in->yyt9) in->yyt9 -= free;


    in->lim += fread(in->lim, 1, free, in->file);
    in->lim[0] = 0;

    if (in->lim < in->buf + SIZE) {
        in->eof = 1;
    }

    return 0;
}

static inline int fill_buffered_scc(input_t *in, size_t need) {
    size_t free;
    if (in->eof) return 1;

    free = in->tok - in->buf;
    assert(free >= need);

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
if (in->yyt4) in->yyt4 -= free;
if (in->yyt5) in->yyt5 -= free;
if (in->yyt6) in->yyt6 -= free;
if (in->yyt7) in->yyt7 -= free;
if (in->yyt8) in->yyt8 -= free;
if (in->yyt9) in->yyt9 -= free;


    in->lim += fread(in->lim, 1, free, in->file);

    if (in->lim < in->buf + SIZE) {
        in->eof = 1;
        memset(in->lim, 0, YYMAXFILL);
        in->lim += YYMAXFILL;
    }

    return 0;
}

static inline void init_input_simple(input_t *in, const char* fname) {
    FILE* f = fopen(fname, "rb");

    fseek(f, 0, SEEK_END);
    size_t flen = (size_t) ftell(f);
    fseek(f, 0, SEEK_SET);

    in->file = nullptr; // unused
    in->buf = (char*) malloc(flen + 1);
    in->lim = nullptr; // unused
    in->cur = in->mar = in->tok = in->buf;
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
in->yyt4 = 0;
in->yyt5 = 0;
in->yyt6 = 0;
in->yyt7 = 0;
in->yyt8 = 0;
in->yyt9 = 0;

    
    taglistpool_init(&in->tlp);
    in->eof = 0; // unused

    fread(in->buf, 1, flen, f);
    in->buf[flen] = 0;

    fclose(f);
}

static inline void init_input_buffered_eof(input_t *in, const char* fname) {
    in->file = fopen(fname, "rb");
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
in->yyt4 = 0;
in->yyt5 = 0;
in->yyt6 = 0;
in->yyt7 = 0;
in->yyt8 = 0;
in->yyt9 = 0;

    
    taglistpool_init(&in->tlp);
    in->eof = 0;
    fill_buffered_eof(in);
}

static inline void init_input_buffered_scc(input_t *in, const char* fname) {
    in->file = fopen(fname, "rb");
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
in->yyt4 = 0;
in->yyt5 = 0;
in->yyt6 = 0;
in->yyt7 = 0;
in->yyt8 = 0;
in->yyt9 = 0;

    
    taglistpool_init(&in->tlp);
    in->eof = 0;
}

#define YYCURSOR cur
#define YYMARKER mar
#define YYTOKEN tok
#define TLP_CLEAR() do { \
    in->tlp.next = in->tlp.head; \
     \
} while (0)

int lex_simple(input_t *in) {
    char *cur = in->buf, *mar, *tok;
    (void) mar; // maybe unused
    (void) tok; // maybe unused
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
char *yyt4;
char *yyt5;
char *yyt6;
char *yyt7;
char *yyt8;
char *yyt9;

    
    const char* a0;const char* a1;const char* b0;const char* b1;
    
    long count = 0;
loop:
    tok = cur;
    
{
	char yych;
	yych = *YYCURSOR;
	switch (yych) {
		case 0x00: goto yy1;
		case 'a':
			yyt1 = YYCURSOR;
			yyt2 = YYCURSOR;
			goto yy4;
		default: goto yy2;
	}
yy1:
	++YYCURSOR;
	{ return count; }
yy2:
	++YYCURSOR;
yy3:
	{ return -1; }
yy4:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 'a':
			yyt3 = YYCURSOR;
			goto yy5;
		default: goto yy3;
	}
yy5:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt4 = YYCURSOR;
			goto yy7;
		default: goto yy6;
	}
yy6:
	YYCURSOR = YYMARKER;
	goto yy3;
yy7:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt5 = YYCURSOR;
			goto yy8;
		default: goto yy6;
	}
yy8:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt6 = YYCURSOR;
			goto yy9;
		default: goto yy6;
	}
yy9:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt7 = YYCURSOR;
			goto yy10;
		default: goto yy6;
	}
yy10:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt8 = YYCURSOR;
			goto yy11;
		default: goto yy6;
	}
yy11:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt9 = YYCURSOR;
			goto yy12;
		default: goto yy6;
	}
yy12:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt10 = YYCURSOR;
			yyt11 = YYCURSOR;
			yyt12 = YYCURSOR;
			goto yy13;
		default: goto yy15;
	}
yy13:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt13 = YYCURSOR;
			yyt14 = YYCURSOR;
			yyt15 = YYCURSOR;
			goto yy16;
		case 'b':
			yyt2 = yyt3;
			goto yy14;
		default: goto yy6;
	}
yy14:
	yych = *++YYCURSOR;
yy15:
	switch (yych) {
		case 'a':
			yyt11 = YYCURSOR;
			yyt12 = YYCURSOR;
			goto yy17;
		case 'b': goto yy14;
		default: goto yy6;
	}
yy16:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt16 = YYCURSOR;
			yyt17 = YYCURSOR;
			yyt18 = YYCURSOR;
			goto yy18;
		case 'b':
			yyt2 = yyt4;
			goto yy14;
		default: goto yy6;
	}
yy17:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt3 = YYCURSOR;
			goto yy19;
		default: goto yy6;
	}
yy18:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt19 = YYCURSOR;
			yyt20 = YYCURSOR;
			yyt21 = YYCURSOR;
			goto yy20;
		case 'b':
			yyt2 = yyt5;
			goto yy14;
		default: goto yy6;
	}
yy19:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt4 = YYCURSOR;
			goto yy21;
		default: goto yy6;
	}
yy20:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt22 = YYCURSOR;
			yyt23 = YYCURSOR;
			yyt24 = YYCURSOR;
			goto yy22;
		case 'b':
			yyt2 = yyt6;
			goto yy14;
		default: goto yy6;
	}
yy21:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt5 = YYCURSOR;
			goto yy23;
		default: goto yy6;
	}
yy22:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt25 = YYCURSOR;
			yyt26 = YYCURSOR;
			yyt27 = YYCURSOR;
			goto yy24;
		case 'b':
			yyt2 = yyt7;
			goto yy14;
		default: goto yy6;
	}
yy23:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt6 = YYCURSOR;
			goto yy25;
		default: goto yy6;
	}
yy24:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt28 = YYCURSOR;
			yyt29 = YYCURSOR;
			goto yy26;
		case 'b':
			yyt2 = yyt8;
			goto yy14;
		default: goto yy6;
	}
yy25:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt7 = YYCURSOR;
			goto yy27;
		default: goto yy6;
	}
yy26:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt30 = YYCURSOR;
			yyt31 = YYCURSOR;
			goto yy28;
		case 'b':
			yyt2 = yyt9;
			goto yy14;
		default: goto yy6;
	}
yy27:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt8 = YYCURSOR;
			goto yy29;
		default: goto yy6;
	}
yy28:
	yych = *++YYCURSOR;
	switch (yych) {
		case '\n': goto yy30;
		case 'a':
			yyt2 = yyt3;
			yyt3 = yyt4;
			yyt4 = yyt5;
			yyt5 = yyt6;
			yyt6 = yyt7;
			yyt7 = yyt8;
			yyt8 = yyt9;
			yyt11 = yyt14;
			yyt12 = yyt15;
			yyt14 = yyt17;
			yyt15 = yyt18;
			yyt17 = yyt20;
			yyt18 = yyt21;
			yyt20 = yyt23;
			yyt21 = yyt24;
			yyt23 = yyt26;
			yyt24 = yyt27;
			yyt26 = yyt29;
			yyt27 = yyt29;
			yyt29 = yyt31;
			yyt31 = YYCURSOR;
			yyt9 = yyt10;
			yyt10 = yyt13;
			yyt13 = yyt16;
			yyt16 = yyt19;
			yyt19 = yyt22;
			yyt22 = yyt25;
			yyt25 = yyt28;
			yyt28 = yyt30;
			yyt30 = YYCURSOR;
			goto yy28;
		case 'b': goto yy31;
		default: goto yy6;
	}
yy29:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			yyt9 = YYCURSOR;
			goto yy32;
		default: goto yy6;
	}
yy30:
	++YYCURSOR;
	a0 = yyt1;
	b0 = yyt2;
	a1 = yyt11;
	b1 = yyt12;
	{
        OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
        OUTS(a1, b1); OUTC('.'); OUTS(b1, YYCURSOR);
        goto loop;
    }
yy31:
	yych = *++YYCURSOR;
	switch (yych) {
		case '\n': goto yy30;
		case 'a':
			yyt2 = yyt10;
			yyt11 = YYCURSOR;
			yyt12 = YYCURSOR;
			goto yy17;
		case 'b': goto yy31;
		default: goto yy6;
	}
yy32:
	yych = *++YYCURSOR;
	switch (yych) {
		case '\n': goto yy30;
		case 'a':
			yyt12 = yyt3;
			yyt3 = yyt4;
			yyt4 = yyt5;
			yyt5 = yyt6;
			yyt6 = yyt7;
			yyt7 = yyt8;
			yyt8 = yyt9;
			yyt9 = YYCURSOR;
			goto yy32;
		case 'b': goto yy33;
		default: goto yy6;
	}
yy33:
	yych = *++YYCURSOR;
	switch (yych) {
		case '\n': goto yy30;
		case 'b': goto yy33;
		default: goto yy6;
	}
}

}

#undef YYCURSOR
#undef YYMARKER
#undef YYTOKEN
#undef TLP_CLEAR

#define YYCURSOR in->cur
#define YYMARKER in->mar
#define YYLIMIT in->lim
#define YYTOKEN in->tok
#define TLP_CLEAR() do { \
    in->tlp.next = in->tlp.head; \
     \
} while (0)

int lex_buffered_eof(input_t *in) {
    const char* a0;const char* a1;const char* b0;const char* b1;
    
    long count = 0;
loop:
    in->tok = in->cur;
    
{
	char yych;
yyFillLabel0:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt1 = YYCURSOR;
			in->yyt2 = YYCURSOR;
			goto yy37;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel0;
				goto yy67;
			}
			goto yy35;
	}
yy35:
	++YYCURSOR;
yy36:
	{ return -1; }
yy37:
	YYMARKER = ++YYCURSOR;
yyFillLabel1:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt3 = YYCURSOR;
			goto yy38;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel1;
			}
			goto yy36;
	}
yy38:
	++YYCURSOR;
yyFillLabel2:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt4 = YYCURSOR;
			goto yy40;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel2;
			}
			goto yy39;
	}
yy39:
	YYCURSOR = YYMARKER;
	goto yy36;
yy40:
	++YYCURSOR;
yyFillLabel3:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt5 = YYCURSOR;
			goto yy41;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel3;
			}
			goto yy39;
	}
yy41:
	++YYCURSOR;
yyFillLabel4:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt6 = YYCURSOR;
			goto yy42;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel4;
			}
			goto yy39;
	}
yy42:
	++YYCURSOR;
yyFillLabel5:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt7 = YYCURSOR;
			goto yy43;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel5;
			}
			goto yy39;
	}
yy43:
	++YYCURSOR;
yyFillLabel6:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt8 = YYCURSOR;
			goto yy44;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel6;
			}
			goto yy39;
	}
yy44:
	++YYCURSOR;
yyFillLabel7:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt9 = YYCURSOR;
			goto yy45;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel7;
			}
			goto yy39;
	}
yy45:
	++YYCURSOR;
yyFillLabel8:
	yych = *YYCURSOR;
	switch (yych) {
		case 0x00:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel8;
			}
			goto yy39;
		case 'a':
			in->yyt10 = YYCURSOR;
			in->yyt11 = YYCURSOR;
			in->yyt12 = YYCURSOR;
			goto yy46;
		default: goto yy48;
	}
yy46:
	++YYCURSOR;
yyFillLabel9:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt13 = YYCURSOR;
			in->yyt14 = YYCURSOR;
			in->yyt15 = YYCURSOR;
			goto yy49;
		case 'b':
			in->yyt2 = in->yyt3;
			goto yy47;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel9;
			}
			goto yy39;
	}
yy47:
	++YYCURSOR;
yyFillLabel10:
	yych = *YYCURSOR;
yy48:
	switch (yych) {
		case 'a':
			in->yyt11 = YYCURSOR;
			in->yyt12 = YYCURSOR;
			goto yy50;
		case 'b': goto yy47;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel10;
			}
			goto yy39;
	}
yy49:
	++YYCURSOR;
yyFillLabel11:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt16 = YYCURSOR;
			in->yyt17 = YYCURSOR;
			in->yyt18 = YYCURSOR;
			goto yy51;
		case 'b':
			in->yyt2 = in->yyt4;
			goto yy47;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel11;
			}
			goto yy39;
	}
yy50:
	++YYCURSOR;
yyFillLabel12:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt3 = YYCURSOR;
			goto yy52;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel12;
			}
			goto yy39;
	}
yy51:
	++YYCURSOR;
yyFillLabel13:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt19 = YYCURSOR;
			in->yyt20 = YYCURSOR;
			in->yyt21 = YYCURSOR;
			goto yy53;
		case 'b':
			in->yyt2 = in->yyt5;
			goto yy47;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel13;
			}
			goto yy39;
	}
yy52:
	++YYCURSOR;
yyFillLabel14:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt4 = YYCURSOR;
			goto yy54;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel14;
			}
			goto yy39;
	}
yy53:
	++YYCURSOR;
yyFillLabel15:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt22 = YYCURSOR;
			in->yyt23 = YYCURSOR;
			in->yyt24 = YYCURSOR;
			goto yy55;
		case 'b':
			in->yyt2 = in->yyt6;
			goto yy47;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel15;
			}
			goto yy39;
	}
yy54:
	++YYCURSOR;
yyFillLabel16:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt5 = YYCURSOR;
			goto yy56;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel16;
			}
			goto yy39;
	}
yy55:
	++YYCURSOR;
yyFillLabel17:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt25 = YYCURSOR;
			in->yyt26 = YYCURSOR;
			in->yyt27 = YYCURSOR;
			goto yy57;
		case 'b':
			in->yyt2 = in->yyt7;
			goto yy47;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel17;
			}
			goto yy39;
	}
yy56:
	++YYCURSOR;
yyFillLabel18:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt6 = YYCURSOR;
			goto yy58;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel18;
			}
			goto yy39;
	}
yy57:
	++YYCURSOR;
yyFillLabel19:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt28 = YYCURSOR;
			in->yyt29 = YYCURSOR;
			goto yy59;
		case 'b':
			in->yyt2 = in->yyt8;
			goto yy47;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel19;
			}
			goto yy39;
	}
yy58:
	++YYCURSOR;
yyFillLabel20:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt7 = YYCURSOR;
			goto yy60;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel20;
			}
			goto yy39;
	}
yy59:
	++YYCURSOR;
yyFillLabel21:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt30 = YYCURSOR;
			in->yyt31 = YYCURSOR;
			goto yy61;
		case 'b':
			in->yyt2 = in->yyt9;
			goto yy47;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel21;
			}
			goto yy39;
	}
yy60:
	++YYCURSOR;
yyFillLabel22:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt8 = YYCURSOR;
			goto yy62;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel22;
			}
			goto yy39;
	}
yy61:
	++YYCURSOR;
yyFillLabel23:
	yych = *YYCURSOR;
	switch (yych) {
		case '\n': goto yy63;
		case 'a':
			in->yyt2 = in->yyt3;
			in->yyt3 = in->yyt4;
			in->yyt4 = in->yyt5;
			in->yyt5 = in->yyt6;
			in->yyt6 = in->yyt7;
			in->yyt7 = in->yyt8;
			in->yyt8 = in->yyt9;
			in->yyt11 = in->yyt14;
			in->yyt12 = in->yyt15;
			in->yyt14 = in->yyt17;
			in->yyt15 = in->yyt18;
			in->yyt17 = in->yyt20;
			in->yyt18 = in->yyt21;
			in->yyt20 = in->yyt23;
			in->yyt21 = in->yyt24;
			in->yyt23 = in->yyt26;
			in->yyt24 = in->yyt27;
			in->yyt26 = in->yyt29;
			in->yyt27 = in->yyt29;
			in->yyt29 = in->yyt31;
			in->yyt31 = YYCURSOR;
			in->yyt9 = in->yyt10;
			in->yyt10 = in->yyt13;
			in->yyt13 = in->yyt16;
			in->yyt16 = in->yyt19;
			in->yyt19 = in->yyt22;
			in->yyt22 = in->yyt25;
			in->yyt25 = in->yyt28;
			in->yyt28 = in->yyt30;
			in->yyt30 = YYCURSOR;
			goto yy61;
		case 'b': goto yy64;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel23;
			}
			goto yy39;
	}
yy62:
	++YYCURSOR;
yyFillLabel24:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt9 = YYCURSOR;
			goto yy65;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel24;
			}
			goto yy39;
	}
yy63:
	++YYCURSOR;
	a0 = in->yyt1;
	b0 = in->yyt2;
	a1 = in->yyt11;
	b1 = in->yyt12;
	{
        OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
        OUTS(a1, b1); OUTC('.'); OUTS(b1, YYCURSOR);
        goto loop;
    }
yy64:
	++YYCURSOR;
yyFillLabel25:
	yych = *YYCURSOR;
	switch (yych) {
		case '\n': goto yy63;
		case 'a':
			in->yyt2 = in->yyt10;
			in->yyt11 = YYCURSOR;
			in->yyt12 = YYCURSOR;
			goto yy50;
		case 'b': goto yy64;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel25;
			}
			goto yy39;
	}
yy65:
	++YYCURSOR;
yyFillLabel26:
	yych = *YYCURSOR;
	switch (yych) {
		case '\n': goto yy63;
		case 'a':
			in->yyt12 = in->yyt3;
			in->yyt3 = in->yyt4;
			in->yyt4 = in->yyt5;
			in->yyt5 = in->yyt6;
			in->yyt6 = in->yyt7;
			in->yyt7 = in->yyt8;
			in->yyt8 = in->yyt9;
			in->yyt9 = YYCURSOR;
			goto yy65;
		case 'b': goto yy66;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel26;
			}
			goto yy39;
	}
yy66:
	++YYCURSOR;
yyFillLabel27:
	yych = *YYCURSOR;
	switch (yych) {
		case '\n': goto yy63;
		case 'b': goto yy66;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel27;
			}
			goto yy39;
	}
yy67:
	{ return count; }
}

}

int lex_buffered_scc(input_t *in) {
    const char* a0;const char* a1;const char* b0;const char* b1;
    
    long count = 0;
loop:
    in->tok = in->cur;
    
{
	char yych;
	if ((YYLIMIT - YYCURSOR) < 16) if (fill_buffered_scc(in, 16) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 0x00: goto yy69;
		case 'a':
			in->yyt1 = YYCURSOR;
			in->yyt2 = YYCURSOR;
			goto yy72;
		default: goto yy70;
	}
yy69:
	++YYCURSOR;
	{ return count; }
yy70:
	++YYCURSOR;
yy71:
	{ return -1; }
yy72:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 'a':
			in->yyt3 = YYCURSOR;
			goto yy73;
		default: goto yy71;
	}
yy73:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt4 = YYCURSOR;
			goto yy75;
		default: goto yy74;
	}
yy74:
	YYCURSOR = YYMARKER;
	goto yy71;
yy75:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt5 = YYCURSOR;
			goto yy76;
		default: goto yy74;
	}
yy76:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt6 = YYCURSOR;
			goto yy77;
		default: goto yy74;
	}
yy77:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt7 = YYCURSOR;
			goto yy78;
		default: goto yy74;
	}
yy78:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt8 = YYCURSOR;
			goto yy79;
		default: goto yy74;
	}
yy79:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt9 = YYCURSOR;
			goto yy80;
		default: goto yy74;
	}
yy80:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt10 = YYCURSOR;
			in->yyt11 = YYCURSOR;
			in->yyt12 = YYCURSOR;
			goto yy81;
		default: goto yy83;
	}
yy81:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt13 = YYCURSOR;
			in->yyt14 = YYCURSOR;
			in->yyt15 = YYCURSOR;
			goto yy84;
		case 'b':
			in->yyt2 = in->yyt3;
			goto yy82;
		default: goto yy74;
	}
yy82:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 8) if (fill_buffered_scc(in, 8) != 0) return -2;
	yych = *YYCURSOR;
yy83:
	switch (yych) {
		case 'a':
			in->yyt11 = YYCURSOR;
			in->yyt12 = YYCURSOR;
			goto yy85;
		case 'b': goto yy82;
		default: goto yy74;
	}
yy84:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt16 = YYCURSOR;
			in->yyt17 = YYCURSOR;
			in->yyt18 = YYCURSOR;
			goto yy86;
		case 'b':
			in->yyt2 = in->yyt4;
			goto yy82;
		default: goto yy74;
	}
yy85:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt3 = YYCURSOR;
			goto yy87;
		default: goto yy74;
	}
yy86:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt19 = YYCURSOR;
			in->yyt20 = YYCURSOR;
			in->yyt21 = YYCURSOR;
			goto yy88;
		case 'b':
			in->yyt2 = in->yyt5;
			goto yy82;
		default: goto yy74;
	}
yy87:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt4 = YYCURSOR;
			goto yy89;
		default: goto yy74;
	}
yy88:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt22 = YYCURSOR;
			in->yyt23 = YYCURSOR;
			in->yyt24 = YYCURSOR;
			goto yy90;
		case 'b':
			in->yyt2 = in->yyt6;
			goto yy82;
		default: goto yy74;
	}
yy89:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt5 = YYCURSOR;
			goto yy91;
		default: goto yy74;
	}
yy90:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt25 = YYCURSOR;
			in->yyt26 = YYCURSOR;
			in->yyt27 = YYCURSOR;
			goto yy92;
		case 'b':
			in->yyt2 = in->yyt7;
			goto yy82;
		default: goto yy74;
	}
yy91:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt6 = YYCURSOR;
			goto yy93;
		default: goto yy74;
	}
yy92:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt28 = YYCURSOR;
			in->yyt29 = YYCURSOR;
			goto yy94;
		case 'b':
			in->yyt2 = in->yyt8;
			goto yy82;
		default: goto yy74;
	}
yy93:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt7 = YYCURSOR;
			goto yy95;
		default: goto yy74;
	}
yy94:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt30 = YYCURSOR;
			in->yyt31 = YYCURSOR;
			goto yy96;
		case 'b':
			in->yyt2 = in->yyt9;
			goto yy82;
		default: goto yy74;
	}
yy95:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt8 = YYCURSOR;
			goto yy97;
		default: goto yy74;
	}
yy96:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case '\n': goto yy98;
		case 'a':
			in->yyt2 = in->yyt3;
			in->yyt3 = in->yyt4;
			in->yyt4 = in->yyt5;
			in->yyt5 = in->yyt6;
			in->yyt6 = in->yyt7;
			in->yyt7 = in->yyt8;
			in->yyt8 = in->yyt9;
			in->yyt11 = in->yyt14;
			in->yyt12 = in->yyt15;
			in->yyt14 = in->yyt17;
			in->yyt15 = in->yyt18;
			in->yyt17 = in->yyt20;
			in->yyt18 = in->yyt21;
			in->yyt20 = in->yyt23;
			in->yyt21 = in->yyt24;
			in->yyt23 = in->yyt26;
			in->yyt24 = in->yyt27;
			in->yyt26 = in->yyt29;
			in->yyt27 = in->yyt29;
			in->yyt29 = in->yyt31;
			in->yyt31 = YYCURSOR;
			in->yyt9 = in->yyt10;
			in->yyt10 = in->yyt13;
			in->yyt13 = in->yyt16;
			in->yyt16 = in->yyt19;
			in->yyt19 = in->yyt22;
			in->yyt22 = in->yyt25;
			in->yyt25 = in->yyt28;
			in->yyt28 = in->yyt30;
			in->yyt30 = YYCURSOR;
			goto yy96;
		case 'b': goto yy99;
		default: goto yy74;
	}
yy97:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			in->yyt9 = YYCURSOR;
			goto yy100;
		default: goto yy74;
	}
yy98:
	++YYCURSOR;
	a0 = in->yyt1;
	b0 = in->yyt2;
	a1 = in->yyt11;
	b1 = in->yyt12;
	{
        OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
        OUTS(a1, b1); OUTC('.'); OUTS(b1, YYCURSOR);
        goto loop;
    }
yy99:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 8) if (fill_buffered_scc(in, 8) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case '\n': goto yy98;
		case 'a':
			in->yyt2 = in->yyt10;
			in->yyt11 = YYCURSOR;
			in->yyt12 = YYCURSOR;
			goto yy85;
		case 'b': goto yy99;
		default: goto yy74;
	}
yy100:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case '\n': goto yy98;
		case 'a':
			in->yyt12 = in->yyt3;
			in->yyt3 = in->yyt4;
			in->yyt4 = in->yyt5;
			in->yyt5 = in->yyt6;
			in->yyt6 = in->yyt7;
			in->yyt7 = in->yyt8;
			in->yyt8 = in->yyt9;
			in->yyt9 = YYCURSOR;
			goto yy100;
		case 'b': goto yy101;
		default: goto yy74;
	}
yy101:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case '\n': goto yy98;
		case 'b': goto yy101;
		default: goto yy74;
	}
}

}

#undef YYCURSOR
#undef YYMARKER
#undef YYLIMIT
#undef YYTOKEN
#undef TLP_CLEAR

#define FN_BENCH(suffix) \
void bench_##suffix::operator()( \
        benchmark::State &state, const char* input, long expected) const { \
    long count = 0; \
    for (auto _ : state) { \
        input_t in; \
        init_input_##suffix(&in, input); \
        count = lex_##suffix(&in); \
        free_input(&in); \
    } \
    if (count != expected) state.SkipWithError("re2c: error"); \
}
FN_BENCH(simple)
FN_BENCH(buffered_eof)
FN_BENCH(buffered_scc)
#undef FN_BENCH

#define FN_TEST(suffix) \
bool test_##suffix(const char* input, long expected) { \
    input_t in; \
    init_input_##suffix(&in, input); \
    long count = lex_##suffix(&in); \
    switch (count) { \
    default: \
        if (count != expected) { \
            fprintf(stderr, "re2c: wrong count, expected %ld, got %ld\n", expected, count); \
        } \
        break; \
    case -1: \
        fprintf(stderr, "re2c: syntax error\n"); \
        break; \
    case -2: \
        fprintf(stderr, "re2c: yyfill error\n"); \
        break; \
    } \
    free_input(&in); \
    return count == expected; \
}
FN_TEST(simple)
FN_TEST(buffered_eof)
FN_TEST(buffered_scc)
#undef FN_TEST


} // namespace re2c_submatch_22__cat2_8
