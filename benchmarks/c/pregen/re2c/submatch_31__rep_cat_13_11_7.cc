/* Generated by re2c */
#include "re2c/base.h"

namespace re2c_submatch_31__rep_cat_13_11_7 {



static const char *print(long& count,
        const char *tok, const taglist_t *t1, const taglist_t *t2, const taglist_t *t3) {
    if (!t1) return tok;

    const char *p0 = print(count, tok, t1->pred, t2->pred, t3->pred);
    const char *p1 = tok + t1->dist;
    const char *p2 = tok + t2->dist;
    const char *p3 = tok + t3->dist;

    OUTS(p0, p1);
    OUTC('.');
    OUTS(p1, p2);
    OUTC('.');
    OUTS(p2, p3);
    OUTC(';');

    return p3;
}



#define YYMAXFILL 2


struct input_t {
    FILE* file;
    char *buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    
    taglist_t *yytm1;
taglist_t *yytm2;
taglist_t *yytm3;

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
    
    in->yytm1 = 0;
in->yytm2 = 0;
in->yytm3 = 0;

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
    
    in->yytm1 = 0;
in->yytm2 = 0;
in->yytm3 = 0;

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
    
    in->yytm1 = 0;
in->yytm2 = 0;
in->yytm3 = 0;

    taglistpool_init(&in->tlp);
    in->eof = 0;
}

#define YYCURSOR cur
#define YYMARKER mar
#define YYTOKEN tok
#define TLP_CLEAR() do { \
    in->tlp.next = in->tlp.head; \
    yytm1 = 0;yytm2 = 0;yytm3 = 0; \
} while (0)

int lex_simple(input_t *in) {
    char *cur = in->buf, *mar, *tok;
    (void) tok; // may be unused
    
    taglist_t *yytm1 = nullptr;
taglist_t *yytm2 = nullptr;
taglist_t *yytm3 = nullptr;

    
    taglist_t* t1;taglist_t* t2;taglist_t* t3;
    long count = 0;
loop:
    tok = cur;
    
{
	char yych;
	yych = *YYCURSOR;
	switch (yych) {
		case 0x00: goto yy1;
		case '\n':
			taglist(&yytm3, YYTOKEN, YYTOKEN - 1, &in->tlp);
			taglist(&yytm2, YYTOKEN, YYTOKEN - 1, &in->tlp);
			taglist(&yytm1, YYTOKEN, YYTOKEN - 1, &in->tlp);
			goto yy4;
		case 'a': goto yy5;
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
	++YYCURSOR;
	t1 = yytm1;
	t2 = yytm2;
	t3 = yytm3;
	{
        print(count, YYTOKEN, t1, t2, t3);
        OUTC('\n');
        TLP_CLEAR();
        goto loop;
    }
yy5:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 'a': goto yy6;
		default: goto yy3;
	}
yy6:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy8;
		default: goto yy7;
	}
yy7:
	YYCURSOR = YYMARKER;
	goto yy3;
yy8:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy9;
		default: goto yy7;
	}
yy9:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy10;
		default: goto yy7;
	}
yy10:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy11;
		default: goto yy7;
	}
yy11:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy12;
		default: goto yy7;
	}
yy12:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy13;
		default: goto yy7;
	}
yy13:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy14;
		default: goto yy7;
	}
yy14:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy15;
		default: goto yy7;
	}
yy15:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy16;
		default: goto yy7;
	}
yy16:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy17;
		default: goto yy7;
	}
yy17:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy18;
		default: goto yy7;
	}
yy18:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			taglist(&yytm1, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy19;
		default: goto yy7;
	}
yy19:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy20;
		default: goto yy7;
	}
yy20:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy21;
		default: goto yy7;
	}
yy21:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy22;
		default: goto yy7;
	}
yy22:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy23;
		default: goto yy7;
	}
yy23:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy24;
		default: goto yy7;
	}
yy24:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy25;
		default: goto yy7;
	}
yy25:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy26;
		default: goto yy7;
	}
yy26:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy27;
		default: goto yy7;
	}
yy27:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy28;
		default: goto yy7;
	}
yy28:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy29;
		default: goto yy7;
	}
yy29:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a':
			taglist(&yytm2, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy30;
		default: goto yy7;
	}
yy30:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy31;
		default: goto yy7;
	}
yy31:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy32;
		default: goto yy7;
	}
yy32:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy33;
		default: goto yy7;
	}
yy33:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy34;
		default: goto yy7;
	}
yy34:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy35;
		default: goto yy7;
	}
yy35:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy36;
		default: goto yy7;
	}
yy36:
	yych = *++YYCURSOR;
	switch (yych) {
		case '\n':
			taglist(&yytm3, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy4;
		case 'a':
			taglist(&yytm3, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy37;
		default: goto yy7;
	}
yy37:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy6;
		default: goto yy7;
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
    in->yytm1 = 0;in->yytm2 = 0;in->yytm3 = 0; \
} while (0)

int lex_buffered_eof(input_t *in) {
    
    taglist_t* t1;taglist_t* t2;taglist_t* t3;
    long count = 0;
loop:
    in->tok = in->cur;
    
{
	char yych;
yyFillLabel0:
	yych = *YYCURSOR;
	switch (yych) {
		case '\n':
			taglist(&in->yytm3, YYTOKEN, YYTOKEN - 1, &in->tlp);
			taglist(&in->yytm2, YYTOKEN, YYTOKEN - 1, &in->tlp);
			taglist(&in->yytm1, YYTOKEN, YYTOKEN - 1, &in->tlp);
			goto yy41;
		case 'a': goto yy42;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel0;
				goto yy75;
			}
			goto yy39;
	}
yy39:
	++YYCURSOR;
yy40:
	{ return -1; }
yy41:
	++YYCURSOR;
	t1 = in->yytm1;
	t2 = in->yytm2;
	t3 = in->yytm3;
	{
        print(count, YYTOKEN, t1, t2, t3);
        OUTC('\n');
        TLP_CLEAR();
        goto loop;
    }
yy42:
	YYMARKER = ++YYCURSOR;
yyFillLabel1:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy43;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel1;
			}
			goto yy40;
	}
yy43:
	++YYCURSOR;
yyFillLabel2:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy45;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel2;
			}
			goto yy44;
	}
yy44:
	YYCURSOR = YYMARKER;
	goto yy40;
yy45:
	++YYCURSOR;
yyFillLabel3:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy46;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel3;
			}
			goto yy44;
	}
yy46:
	++YYCURSOR;
yyFillLabel4:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy47;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel4;
			}
			goto yy44;
	}
yy47:
	++YYCURSOR;
yyFillLabel5:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy48;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel5;
			}
			goto yy44;
	}
yy48:
	++YYCURSOR;
yyFillLabel6:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy49;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel6;
			}
			goto yy44;
	}
yy49:
	++YYCURSOR;
yyFillLabel7:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy50;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel7;
			}
			goto yy44;
	}
yy50:
	++YYCURSOR;
yyFillLabel8:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy51;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel8;
			}
			goto yy44;
	}
yy51:
	++YYCURSOR;
yyFillLabel9:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy52;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel9;
			}
			goto yy44;
	}
yy52:
	++YYCURSOR;
yyFillLabel10:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy53;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel10;
			}
			goto yy44;
	}
yy53:
	++YYCURSOR;
yyFillLabel11:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy54;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel11;
			}
			goto yy44;
	}
yy54:
	++YYCURSOR;
yyFillLabel12:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy55;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel12;
			}
			goto yy44;
	}
yy55:
	++YYCURSOR;
yyFillLabel13:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			taglist(&in->yytm1, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy56;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel13;
			}
			goto yy44;
	}
yy56:
	++YYCURSOR;
yyFillLabel14:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy57;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel14;
			}
			goto yy44;
	}
yy57:
	++YYCURSOR;
yyFillLabel15:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy58;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel15;
			}
			goto yy44;
	}
yy58:
	++YYCURSOR;
yyFillLabel16:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy59;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel16;
			}
			goto yy44;
	}
yy59:
	++YYCURSOR;
yyFillLabel17:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy60;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel17;
			}
			goto yy44;
	}
yy60:
	++YYCURSOR;
yyFillLabel18:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy61;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel18;
			}
			goto yy44;
	}
yy61:
	++YYCURSOR;
yyFillLabel19:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy62;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel19;
			}
			goto yy44;
	}
yy62:
	++YYCURSOR;
yyFillLabel20:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy63;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel20;
			}
			goto yy44;
	}
yy63:
	++YYCURSOR;
yyFillLabel21:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy64;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel21;
			}
			goto yy44;
	}
yy64:
	++YYCURSOR;
yyFillLabel22:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy65;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel22;
			}
			goto yy44;
	}
yy65:
	++YYCURSOR;
yyFillLabel23:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy66;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel23;
			}
			goto yy44;
	}
yy66:
	++YYCURSOR;
yyFillLabel24:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			taglist(&in->yytm2, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy67;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel24;
			}
			goto yy44;
	}
yy67:
	++YYCURSOR;
yyFillLabel25:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy68;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel25;
			}
			goto yy44;
	}
yy68:
	++YYCURSOR;
yyFillLabel26:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy69;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel26;
			}
			goto yy44;
	}
yy69:
	++YYCURSOR;
yyFillLabel27:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy70;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel27;
			}
			goto yy44;
	}
yy70:
	++YYCURSOR;
yyFillLabel28:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy71;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel28;
			}
			goto yy44;
	}
yy71:
	++YYCURSOR;
yyFillLabel29:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy72;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel29;
			}
			goto yy44;
	}
yy72:
	++YYCURSOR;
yyFillLabel30:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy73;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel30;
			}
			goto yy44;
	}
yy73:
	++YYCURSOR;
yyFillLabel31:
	yych = *YYCURSOR;
	switch (yych) {
		case '\n':
			taglist(&in->yytm3, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy41;
		case 'a':
			taglist(&in->yytm3, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy74;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel31;
			}
			goto yy44;
	}
yy74:
	++YYCURSOR;
yyFillLabel32:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy43;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel32;
			}
			goto yy44;
	}
yy75:
	{ return count; }
}

}

int lex_buffered_scc(input_t *in) {
    
    taglist_t* t1;taglist_t* t2;taglist_t* t3;
    long count = 0;
loop:
    in->tok = in->cur;
    
{
	char yych;
	if ((YYLIMIT - YYCURSOR) < 2) if (fill_buffered_scc(in, 2) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 0x00: goto yy77;
		case '\n':
			taglist(&in->yytm3, YYTOKEN, YYTOKEN - 1, &in->tlp);
			taglist(&in->yytm2, YYTOKEN, YYTOKEN - 1, &in->tlp);
			taglist(&in->yytm1, YYTOKEN, YYTOKEN - 1, &in->tlp);
			goto yy80;
		case 'a': goto yy81;
		default: goto yy78;
	}
yy77:
	++YYCURSOR;
	{ return count; }
yy78:
	++YYCURSOR;
yy79:
	{ return -1; }
yy80:
	++YYCURSOR;
	t1 = in->yytm1;
	t2 = in->yytm2;
	t3 = in->yytm3;
	{
        print(count, YYTOKEN, t1, t2, t3);
        OUTC('\n');
        TLP_CLEAR();
        goto loop;
    }
yy81:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 'a': goto yy82;
		default: goto yy79;
	}
yy82:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy84;
		default: goto yy83;
	}
yy83:
	YYCURSOR = YYMARKER;
	goto yy79;
yy84:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy85;
		default: goto yy83;
	}
yy85:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy86;
		default: goto yy83;
	}
yy86:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy87;
		default: goto yy83;
	}
yy87:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy88;
		default: goto yy83;
	}
yy88:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy89;
		default: goto yy83;
	}
yy89:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy90;
		default: goto yy83;
	}
yy90:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy91;
		default: goto yy83;
	}
yy91:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy92;
		default: goto yy83;
	}
yy92:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy93;
		default: goto yy83;
	}
yy93:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy94;
		default: goto yy83;
	}
yy94:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			taglist(&in->yytm1, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy95;
		default: goto yy83;
	}
yy95:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy96;
		default: goto yy83;
	}
yy96:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy97;
		default: goto yy83;
	}
yy97:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy98;
		default: goto yy83;
	}
yy98:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy99;
		default: goto yy83;
	}
yy99:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy100;
		default: goto yy83;
	}
yy100:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy101;
		default: goto yy83;
	}
yy101:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy102;
		default: goto yy83;
	}
yy102:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy103;
		default: goto yy83;
	}
yy103:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy104;
		default: goto yy83;
	}
yy104:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy105;
		default: goto yy83;
	}
yy105:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			taglist(&in->yytm2, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy106;
		default: goto yy83;
	}
yy106:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy107;
		default: goto yy83;
	}
yy107:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy108;
		default: goto yy83;
	}
yy108:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy109;
		default: goto yy83;
	}
yy109:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy110;
		default: goto yy83;
	}
yy110:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy111;
		default: goto yy83;
	}
yy111:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy112;
		default: goto yy83;
	}
yy112:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case '\n':
			taglist(&in->yytm3, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy80;
		case 'a':
			taglist(&in->yytm3, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy113;
		default: goto yy83;
	}
yy113:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy82;
		default: goto yy83;
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
    if (count != expected) state.SkipWithError("error"); \
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
            fprintf(stderr, "wrong count, expected %ld, got %ld\n", expected, count); \
        } \
        break; \
    case -1: \
        fprintf(stderr, "syntax error\n"); \
        break; \
    case -2: \
        fprintf(stderr, "yyfill error\n"); \
        break; \
    } \
    free_input(&in); \
    return count == expected; \
}
FN_TEST(simple)
FN_TEST(buffered_eof)
FN_TEST(buffered_scc)
#undef FN_TEST


} // namespace re2c_submatch_31__rep_cat_13_11_7
