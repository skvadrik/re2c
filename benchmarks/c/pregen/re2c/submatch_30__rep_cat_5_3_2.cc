/* Generated by re2c */
#include "re2c/base.h"

namespace re2c_submatch_30__rep_cat_5_3_2 {



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
		case 'a':
			taglist(&yytm1, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy11;
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
		case 'a':
			taglist(&yytm2, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy14;
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
		case '\n':
			taglist(&yytm3, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy4;
		case 'a':
			taglist(&yytm3, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy16;
		default: goto yy7;
	}
yy16:
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
			goto yy20;
		case 'a': goto yy21;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel0;
				goto yy33;
			}
			goto yy18;
	}
yy18:
	++YYCURSOR;
yy19:
	{ return -1; }
yy20:
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
yy21:
	YYMARKER = ++YYCURSOR;
yyFillLabel1:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy22;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel1;
			}
			goto yy19;
	}
yy22:
	++YYCURSOR;
yyFillLabel2:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy24;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel2;
			}
			goto yy23;
	}
yy23:
	YYCURSOR = YYMARKER;
	goto yy19;
yy24:
	++YYCURSOR;
yyFillLabel3:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy25;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel3;
			}
			goto yy23;
	}
yy25:
	++YYCURSOR;
yyFillLabel4:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy26;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel4;
			}
			goto yy23;
	}
yy26:
	++YYCURSOR;
yyFillLabel5:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			taglist(&in->yytm1, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy27;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel5;
			}
			goto yy23;
	}
yy27:
	++YYCURSOR;
yyFillLabel6:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy28;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel6;
			}
			goto yy23;
	}
yy28:
	++YYCURSOR;
yyFillLabel7:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy29;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel7;
			}
			goto yy23;
	}
yy29:
	++YYCURSOR;
yyFillLabel8:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			taglist(&in->yytm2, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy30;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel8;
			}
			goto yy23;
	}
yy30:
	++YYCURSOR;
yyFillLabel9:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy31;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel9;
			}
			goto yy23;
	}
yy31:
	++YYCURSOR;
yyFillLabel10:
	yych = *YYCURSOR;
	switch (yych) {
		case '\n':
			taglist(&in->yytm3, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy20;
		case 'a':
			taglist(&in->yytm3, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy32;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel10;
			}
			goto yy23;
	}
yy32:
	++YYCURSOR;
yyFillLabel11:
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy22;
		default:
			if (YYLIMIT <= YYCURSOR) {
				if (fill_buffered_eof(in) == 0) goto yyFillLabel11;
			}
			goto yy23;
	}
yy33:
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
		case 0x00: goto yy35;
		case '\n':
			taglist(&in->yytm3, YYTOKEN, YYTOKEN - 1, &in->tlp);
			taglist(&in->yytm2, YYTOKEN, YYTOKEN - 1, &in->tlp);
			taglist(&in->yytm1, YYTOKEN, YYTOKEN - 1, &in->tlp);
			goto yy38;
		case 'a': goto yy39;
		default: goto yy36;
	}
yy35:
	++YYCURSOR;
	{ return count; }
yy36:
	++YYCURSOR;
yy37:
	{ return -1; }
yy38:
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
yy39:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 'a': goto yy40;
		default: goto yy37;
	}
yy40:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy42;
		default: goto yy41;
	}
yy41:
	YYCURSOR = YYMARKER;
	goto yy37;
yy42:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy43;
		default: goto yy41;
	}
yy43:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy44;
		default: goto yy41;
	}
yy44:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			taglist(&in->yytm1, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy45;
		default: goto yy41;
	}
yy45:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy46;
		default: goto yy41;
	}
yy46:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy47;
		default: goto yy41;
	}
yy47:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			taglist(&in->yytm2, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy48;
		default: goto yy41;
	}
yy48:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy49;
		default: goto yy41;
	}
yy49:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case '\n':
			taglist(&in->yytm3, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy38;
		case 'a':
			taglist(&in->yytm3, YYTOKEN, YYCURSOR, &in->tlp);
			goto yy50;
		default: goto yy41;
	}
yy50:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) if (fill_buffered_scc(in, 1) != 0) return -2;
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy40;
		default: goto yy41;
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


} // namespace re2c_submatch_30__rep_cat_5_3_2
