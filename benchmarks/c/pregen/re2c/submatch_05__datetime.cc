/* Generated by re2c */
#include "re2c/base.h"

namespace re2c_submatch_05__datetime {





#define YYMAXFILL 26


struct input_t {
    FILE* file;
    char *buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    char *yyt1;
char *yyt2;

    
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
if (in->yyt2) in->yyt2 -= free;


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
if (in->yyt2) in->yyt2 -= free;


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
in->yyt2 = 0;

    
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
in->yyt2 = 0;

    
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
in->yyt2 = 0;

    
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
char *yyt2;

    
    const char* M1;const char* M2;const char* d1;const char* d2;const char* h1;const char* h2;const char* m1;const char* m2;const char* s1;const char* s2;const char* y1;const char* y2;const char* z1;const char* z2;
    
    long count = 0;
loop:
    tok = cur;
    
{
	char yych;
	yych = *YYCURSOR;
	switch (yych) {
		case 0x00: goto yy1;
		case '0':
			yyt1 = YYCURSOR;
			goto yy4;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			yyt1 = YYCURSOR;
			goto yy5;
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
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy6;
		default: goto yy3;
	}
yy5:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy8;
		default: goto yy3;
	}
yy6:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy9;
		default: goto yy7;
	}
yy7:
	YYCURSOR = YYMARKER;
	goto yy3;
yy8:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy10;
		default: goto yy7;
	}
yy9:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy11;
		default: goto yy7;
	}
yy10:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy12;
		default: goto yy7;
	}
yy11:
	yych = *++YYCURSOR;
	switch (yych) {
		case '-': goto yy13;
		default: goto yy7;
	}
yy12:
	yych = *++YYCURSOR;
	switch (yych) {
		case '-': goto yy13;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy12;
		default: goto yy7;
	}
yy13:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0': goto yy14;
		case '1': goto yy15;
		default: goto yy7;
	}
yy14:
	yych = *++YYCURSOR;
	switch (yych) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy16;
		default: goto yy7;
	}
yy15:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2': goto yy16;
		default: goto yy7;
	}
yy16:
	yych = *++YYCURSOR;
	switch (yych) {
		case '-': goto yy17;
		default: goto yy7;
	}
yy17:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0': goto yy18;
		case '1':
		case '2': goto yy19;
		case '3': goto yy20;
		default: goto yy7;
	}
yy18:
	yych = *++YYCURSOR;
	switch (yych) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy21;
		default: goto yy7;
	}
yy19:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy21;
		default: goto yy7;
	}
yy20:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1': goto yy21;
		default: goto yy7;
	}
yy21:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'T': goto yy22;
		default: goto yy7;
	}
yy22:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1': goto yy23;
		case '2': goto yy24;
		default: goto yy7;
	}
yy23:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy25;
		default: goto yy7;
	}
yy24:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3': goto yy25;
		default: goto yy7;
	}
yy25:
	yych = *++YYCURSOR;
	switch (yych) {
		case ':': goto yy26;
		default: goto yy7;
	}
yy26:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5': goto yy27;
		default: goto yy7;
	}
yy27:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy28;
		default: goto yy7;
	}
yy28:
	yych = *++YYCURSOR;
	switch (yych) {
		case ':': goto yy29;
		default: goto yy7;
	}
yy29:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5': goto yy30;
		default: goto yy7;
	}
yy30:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy31;
		default: goto yy7;
	}
yy31:
	yych = *++YYCURSOR;
	switch (yych) {
		case '+':
		case '-':
			yyt2 = YYCURSOR;
			goto yy32;
		case 'Z':
			yyt2 = YYCURSOR;
			goto yy33;
		default: goto yy7;
	}
yy32:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1': goto yy34;
		case '2': goto yy35;
		default: goto yy7;
	}
yy33:
	yych = *++YYCURSOR;
	switch (yych) {
		case '\n': goto yy36;
		default: goto yy7;
	}
yy34:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy37;
		default: goto yy7;
	}
yy35:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3': goto yy37;
		default: goto yy7;
	}
yy36:
	++YYCURSOR;
	y1 = yyt1;
	z1 = yyt2;
	y2 = yyt2;
	y2 -= 15;
	m1 = yyt2;
	m1 -= 14;
	m2 = yyt2;
	m2 -= 12;
	d1 = yyt2;
	d1 -= 11;
	d2 = yyt2;
	d2 -= 9;
	h1 = yyt2;
	h1 -= 8;
	h2 = yyt2;
	h2 -= 6;
	M1 = yyt2;
	M1 -= 5;
	M2 = yyt2;
	M2 -= 3;
	s1 = yyt2;
	s1 -= 2;
	s2 = yyt2;
	z2 = YYCURSOR;
	z2 -= 1;
	{
        OUT("year: ",    y1, y2);
        OUT("month: ",   m1, m2);
        OUT("day: ",     d1, d2);
        OUT("hours: ",   h1, h2);
        OUT("minutes: ", M1, M2);
        OUT("seconds: ", s1, s2);
        OUT("tz: ",      z1, z2);
        OUTC('\n');
        goto loop;
    }
yy37:
	yych = *++YYCURSOR;
	switch (yych) {
		case ':': goto yy38;
		default: goto yy7;
	}
yy38:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5': goto yy39;
		default: goto yy7;
	}
yy39:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy33;
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
     \
} while (0)

int lex_buffered_eof(input_t *in) {
    const char* M1;const char* M2;const char* d1;const char* d2;const char* h1;const char* h2;const char* m1;const char* m2;const char* s1;const char* s2;const char* y1;const char* y2;const char* z1;const char* z2;
    
    long count = 0;
loop:
    in->tok = in->cur;
    
{
	char yych;
yyFillLabel0:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
			in->yyt1 = YYCURSOR;
			goto yy43;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			in->yyt1 = YYCURSOR;
			goto yy44;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel0;
				goto yy79;
			}
			goto yy41;
	}
yy41:
	++YYCURSOR;
yy42:
	{ return -1; }
yy43:
	YYMARKER = ++YYCURSOR;
yyFillLabel1:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy45;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel1;
			}
			goto yy42;
	}
yy44:
	YYMARKER = ++YYCURSOR;
yyFillLabel2:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy47;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel2;
			}
			goto yy42;
	}
yy45:
	++YYCURSOR;
yyFillLabel3:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy48;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel3;
			}
			goto yy46;
	}
yy46:
	YYCURSOR = YYMARKER;
	goto yy42;
yy47:
	++YYCURSOR;
yyFillLabel4:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy49;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel4;
			}
			goto yy46;
	}
yy48:
	++YYCURSOR;
yyFillLabel5:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy50;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel5;
			}
			goto yy46;
	}
yy49:
	++YYCURSOR;
yyFillLabel6:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy51;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel6;
			}
			goto yy46;
	}
yy50:
	++YYCURSOR;
yyFillLabel7:
	yych = *YYCURSOR;
	switch (yych) {
		case '-': goto yy52;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel7;
			}
			goto yy46;
	}
yy51:
	++YYCURSOR;
yyFillLabel8:
	yych = *YYCURSOR;
	switch (yych) {
		case '-': goto yy52;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy51;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel8;
			}
			goto yy46;
	}
yy52:
	++YYCURSOR;
yyFillLabel9:
	yych = *YYCURSOR;
	switch (yych) {
		case '0': goto yy53;
		case '1': goto yy54;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel9;
			}
			goto yy46;
	}
yy53:
	++YYCURSOR;
yyFillLabel10:
	yych = *YYCURSOR;
	switch (yych) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy55;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel10;
			}
			goto yy46;
	}
yy54:
	++YYCURSOR;
yyFillLabel11:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2': goto yy55;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel11;
			}
			goto yy46;
	}
yy55:
	++YYCURSOR;
yyFillLabel12:
	yych = *YYCURSOR;
	switch (yych) {
		case '-': goto yy56;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel12;
			}
			goto yy46;
	}
yy56:
	++YYCURSOR;
yyFillLabel13:
	yych = *YYCURSOR;
	switch (yych) {
		case '0': goto yy57;
		case '1':
		case '2': goto yy58;
		case '3': goto yy59;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel13;
			}
			goto yy46;
	}
yy57:
	++YYCURSOR;
yyFillLabel14:
	yych = *YYCURSOR;
	switch (yych) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy60;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel14;
			}
			goto yy46;
	}
yy58:
	++YYCURSOR;
yyFillLabel15:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy60;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel15;
			}
			goto yy46;
	}
yy59:
	++YYCURSOR;
yyFillLabel16:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1': goto yy60;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel16;
			}
			goto yy46;
	}
yy60:
	++YYCURSOR;
yyFillLabel17:
	yych = *YYCURSOR;
	switch (yych) {
		case 'T': goto yy61;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel17;
			}
			goto yy46;
	}
yy61:
	++YYCURSOR;
yyFillLabel18:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1': goto yy62;
		case '2': goto yy63;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel18;
			}
			goto yy46;
	}
yy62:
	++YYCURSOR;
yyFillLabel19:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy64;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel19;
			}
			goto yy46;
	}
yy63:
	++YYCURSOR;
yyFillLabel20:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3': goto yy64;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel20;
			}
			goto yy46;
	}
yy64:
	++YYCURSOR;
yyFillLabel21:
	yych = *YYCURSOR;
	switch (yych) {
		case ':': goto yy65;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel21;
			}
			goto yy46;
	}
yy65:
	++YYCURSOR;
yyFillLabel22:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5': goto yy66;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel22;
			}
			goto yy46;
	}
yy66:
	++YYCURSOR;
yyFillLabel23:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy67;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel23;
			}
			goto yy46;
	}
yy67:
	++YYCURSOR;
yyFillLabel24:
	yych = *YYCURSOR;
	switch (yych) {
		case ':': goto yy68;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel24;
			}
			goto yy46;
	}
yy68:
	++YYCURSOR;
yyFillLabel25:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5': goto yy69;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel25;
			}
			goto yy46;
	}
yy69:
	++YYCURSOR;
yyFillLabel26:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy70;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel26;
			}
			goto yy46;
	}
yy70:
	++YYCURSOR;
yyFillLabel27:
	yych = *YYCURSOR;
	switch (yych) {
		case '+':
		case '-':
			in->yyt2 = YYCURSOR;
			goto yy71;
		case 'Z':
			in->yyt2 = YYCURSOR;
			goto yy72;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel27;
			}
			goto yy46;
	}
yy71:
	++YYCURSOR;
yyFillLabel28:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1': goto yy73;
		case '2': goto yy74;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel28;
			}
			goto yy46;
	}
yy72:
	++YYCURSOR;
yyFillLabel29:
	yych = *YYCURSOR;
	switch (yych) {
		case '\n': goto yy75;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel29;
			}
			goto yy46;
	}
yy73:
	++YYCURSOR;
yyFillLabel30:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy76;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel30;
			}
			goto yy46;
	}
yy74:
	++YYCURSOR;
yyFillLabel31:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3': goto yy76;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel31;
			}
			goto yy46;
	}
yy75:
	++YYCURSOR;
	y1 = in->yyt1;
	z1 = in->yyt2;
	y2 = in->yyt2;
	y2 -= 15;
	m1 = in->yyt2;
	m1 -= 14;
	m2 = in->yyt2;
	m2 -= 12;
	d1 = in->yyt2;
	d1 -= 11;
	d2 = in->yyt2;
	d2 -= 9;
	h1 = in->yyt2;
	h1 -= 8;
	h2 = in->yyt2;
	h2 -= 6;
	M1 = in->yyt2;
	M1 -= 5;
	M2 = in->yyt2;
	M2 -= 3;
	s1 = in->yyt2;
	s1 -= 2;
	s2 = in->yyt2;
	z2 = YYCURSOR;
	z2 -= 1;
	{
        OUT("year: ",    y1, y2);
        OUT("month: ",   m1, m2);
        OUT("day: ",     d1, d2);
        OUT("hours: ",   h1, h2);
        OUT("minutes: ", M1, M2);
        OUT("seconds: ", s1, s2);
        OUT("tz: ",      z1, z2);
        OUTC('\n');
        goto loop;
    }
yy76:
	++YYCURSOR;
yyFillLabel32:
	yych = *YYCURSOR;
	switch (yych) {
		case ':': goto yy77;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel32;
			}
			goto yy46;
	}
yy77:
	++YYCURSOR;
yyFillLabel33:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5': goto yy78;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel33;
			}
			goto yy46;
	}
yy78:
	++YYCURSOR;
yyFillLabel34:
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy72;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel34;
			}
			goto yy46;
	}
yy79:
	{ return count; }
}

}

int lex_buffered_scc(input_t *in) {
    const char* M1;const char* M2;const char* d1;const char* d2;const char* h1;const char* h2;const char* m1;const char* m2;const char* s1;const char* s2;const char* y1;const char* y2;const char* z1;const char* z2;
    
    long count = 0;
loop:
    in->tok = in->cur;
    
{
	char yych;
	if ((YYLIMIT - YYCURSOR) < 26) if (fill_buffered_scc(in, 26) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 0x00: goto yy81;
		case '0':
			in->yyt1 = YYCURSOR;
			goto yy84;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			in->yyt1 = YYCURSOR;
			goto yy85;
		default: goto yy82;
	}
yy81:
	++YYCURSOR;
	{ return count; }
yy82:
	++YYCURSOR;
yy83:
	{ return -1; }
yy84:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy86;
		default: goto yy83;
	}
yy85:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy88;
		default: goto yy83;
	}
yy86:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy89;
		default: goto yy87;
	}
yy87:
	YYCURSOR = YYMARKER;
	goto yy83;
yy88:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy90;
		default: goto yy87;
	}
yy89:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy91;
		default: goto yy87;
	}
yy90:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy92;
		default: goto yy87;
	}
yy91:
	yych = *++YYCURSOR;
	switch (yych) {
		case '-': goto yy93;
		default: goto yy87;
	}
yy92:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 22) if (fill_buffered_scc(in, 22) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case '-': goto yy93;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy92;
		default: goto yy87;
	}
yy93:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0': goto yy94;
		case '1': goto yy95;
		default: goto yy87;
	}
yy94:
	yych = *++YYCURSOR;
	switch (yych) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy96;
		default: goto yy87;
	}
yy95:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2': goto yy96;
		default: goto yy87;
	}
yy96:
	yych = *++YYCURSOR;
	switch (yych) {
		case '-': goto yy97;
		default: goto yy87;
	}
yy97:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0': goto yy98;
		case '1':
		case '2': goto yy99;
		case '3': goto yy100;
		default: goto yy87;
	}
yy98:
	yych = *++YYCURSOR;
	switch (yych) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy101;
		default: goto yy87;
	}
yy99:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy101;
		default: goto yy87;
	}
yy100:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1': goto yy101;
		default: goto yy87;
	}
yy101:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'T': goto yy102;
		default: goto yy87;
	}
yy102:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1': goto yy103;
		case '2': goto yy104;
		default: goto yy87;
	}
yy103:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy105;
		default: goto yy87;
	}
yy104:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3': goto yy105;
		default: goto yy87;
	}
yy105:
	yych = *++YYCURSOR;
	switch (yych) {
		case ':': goto yy106;
		default: goto yy87;
	}
yy106:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5': goto yy107;
		default: goto yy87;
	}
yy107:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy108;
		default: goto yy87;
	}
yy108:
	yych = *++YYCURSOR;
	switch (yych) {
		case ':': goto yy109;
		default: goto yy87;
	}
yy109:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5': goto yy110;
		default: goto yy87;
	}
yy110:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy111;
		default: goto yy87;
	}
yy111:
	yych = *++YYCURSOR;
	switch (yych) {
		case '+':
		case '-':
			in->yyt2 = YYCURSOR;
			goto yy112;
		case 'Z':
			in->yyt2 = YYCURSOR;
			goto yy113;
		default: goto yy87;
	}
yy112:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1': goto yy114;
		case '2': goto yy115;
		default: goto yy87;
	}
yy113:
	yych = *++YYCURSOR;
	switch (yych) {
		case '\n': goto yy116;
		default: goto yy87;
	}
yy114:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy117;
		default: goto yy87;
	}
yy115:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3': goto yy117;
		default: goto yy87;
	}
yy116:
	++YYCURSOR;
	y1 = in->yyt1;
	z1 = in->yyt2;
	y2 = in->yyt2;
	y2 -= 15;
	m1 = in->yyt2;
	m1 -= 14;
	m2 = in->yyt2;
	m2 -= 12;
	d1 = in->yyt2;
	d1 -= 11;
	d2 = in->yyt2;
	d2 -= 9;
	h1 = in->yyt2;
	h1 -= 8;
	h2 = in->yyt2;
	h2 -= 6;
	M1 = in->yyt2;
	M1 -= 5;
	M2 = in->yyt2;
	M2 -= 3;
	s1 = in->yyt2;
	s1 -= 2;
	s2 = in->yyt2;
	z2 = YYCURSOR;
	z2 -= 1;
	{
        OUT("year: ",    y1, y2);
        OUT("month: ",   m1, m2);
        OUT("day: ",     d1, d2);
        OUT("hours: ",   h1, h2);
        OUT("minutes: ", M1, M2);
        OUT("seconds: ", s1, s2);
        OUT("tz: ",      z1, z2);
        OUTC('\n');
        goto loop;
    }
yy117:
	yych = *++YYCURSOR;
	switch (yych) {
		case ':': goto yy118;
		default: goto yy87;
	}
yy118:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5': goto yy119;
		default: goto yy87;
	}
yy119:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy113;
		default: goto yy87;
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


} // namespace re2c_submatch_05__datetime
