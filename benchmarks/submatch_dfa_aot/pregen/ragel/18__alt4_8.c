#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 96 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"



#line 13 "gen/ragel/18__alt4_8.c"
static const int m_start = 33;
static const int m_first_final = 33;
static const int m_error = 0;

static const int m_en_main = 33;


#line 98 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1, *c1, *d1, *e1, *f1, *g1, *h1,
	*a2, *b2, *c2, *d2, *e2, *f2, *g2, *h2,
	*a3, *b3, *c3, *d3, *e3, *f3, *g3, *h3,
	*a4, *b4, *c4, *d4, *e4, *f4, *g4, *h4,
	*a5, *b5, *c5, *d5, *e5, *f5, *g5, *h5,
	*a6, *b6, *c6, *d6, *e6, *f6, *g6, *h6,
	*a7, *b7, *c7, *d7, *e7, *f7, *g7, *h7,
	*a8, *b8, *c8, *d8, *e8, *f8, *g8, *h8;
	int cs;
	
	
#line 40 "gen/ragel/18__alt4_8.c"
	{
		cs = (int)m_start;
	}
	
#line 115 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
	
	
#line 48 "gen/ragel/18__alt4_8.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 33:
			goto st_case_33;
			case 0:
			goto st_case_0;
			case 1:
			goto st_case_1;
			case 2:
			goto st_case_2;
			case 3:
			goto st_case_3;
			case 4:
			goto st_case_4;
			case 5:
			goto st_case_5;
			case 6:
			goto st_case_6;
			case 7:
			goto st_case_7;
			case 8:
			goto st_case_8;
			case 9:
			goto st_case_9;
			case 10:
			goto st_case_10;
			case 11:
			goto st_case_11;
			case 12:
			goto st_case_12;
			case 13:
			goto st_case_13;
			case 14:
			goto st_case_14;
			case 15:
			goto st_case_15;
			case 16:
			goto st_case_16;
			case 17:
			goto st_case_17;
			case 18:
			goto st_case_18;
			case 19:
			goto st_case_19;
			case 20:
			goto st_case_20;
			case 21:
			goto st_case_21;
			case 22:
			goto st_case_22;
			case 23:
			goto st_case_23;
			case 24:
			goto st_case_24;
			case 25:
			goto st_case_25;
			case 26:
			goto st_case_26;
			case 27:
			goto st_case_27;
			case 28:
			goto st_case_28;
			case 29:
			goto st_case_29;
			case 30:
			goto st_case_30;
			case 31:
			goto st_case_31;
			case 32:
			goto st_case_32;
		}
		goto st_out;
		_ctr2:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 128 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 134 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 140 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 146 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 152 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 158 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 164 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 170 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 176 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 182 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 188 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 194 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 200 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 206 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 212 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 218 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 224 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 230 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 236 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 242 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 248 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 254 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 260 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 266 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 272 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 278 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 284 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 290 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 296 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 302 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 308 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 314 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 320 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 326 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 332 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 338 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 344 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 350 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 356 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 362 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 368 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 374 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 380 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 386 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 392 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 398 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 404 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 410 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 416 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 456 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr11:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 464 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 470 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 476 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 482 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 488 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 494 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 500 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 506 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 512 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 518 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 524 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 530 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 536 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 542 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 548 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 554 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 560 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 566 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 572 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 578 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 584 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 590 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 596 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 602 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 608 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 614 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 620 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 626 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 632 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 638 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 644 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 650 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 656 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 696 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr20:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 704 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 710 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 716 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 722 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 728 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 734 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 740 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 746 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 752 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 758 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 764 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 770 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 776 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 782 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 788 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 794 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 800 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 840 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr29:
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 848 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 888 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr31:
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 896 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 936 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr33:
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 944 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 984 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr35:
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 992 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 1032 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr37:
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1040 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 1080 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr39:
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 1088 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 1128 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr41:
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 1136 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 1176 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr43:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 1184 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 1190 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1196 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 1202 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1208 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 1214 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1220 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 1226 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1232 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 1238 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1244 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 1250 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 1256 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 1262 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 1268 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 1274 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1280 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 1320 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr52:
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1328 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 1368 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr54:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 1376 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 1382 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1388 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 1394 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1400 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 1406 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1412 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 1418 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1424 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 1430 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1436 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 1442 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 1448 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 1454 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 1460 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 1466 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1472 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 1512 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr63:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 1520 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 1526 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1532 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 1538 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1544 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 1550 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1556 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 1562 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1568 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 1574 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1580 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 1586 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 1592 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 1598 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 1604 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 1610 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1616 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 1656 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr72:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 1664 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 1670 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1676 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 1682 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1688 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 1694 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1700 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 1706 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1712 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 1718 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1724 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 1730 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 1736 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 1742 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 1748 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 1754 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1760 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 1800 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr81:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 1808 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 1814 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1820 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 1826 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1832 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 1838 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1844 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 1850 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1856 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 1862 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1868 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 1874 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 1880 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 1886 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 1892 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 1898 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1904 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 1944 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr90:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 1952 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 1958 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1964 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 1970 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1976 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 1982 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1988 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 1994 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2000 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 2006 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2012 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 2018 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 2024 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 2030 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 2036 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 2042 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2048 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 2088 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr99:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 2096 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 2102 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2108 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 2114 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2120 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 2126 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2132 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 2138 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2144 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 2150 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2156 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 2162 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 2168 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 2174 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 2180 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 2186 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2192 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 2198 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2204 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 2210 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2216 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 2222 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2228 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 2234 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2240 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 2246 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2252 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 2258 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 2264 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 2270 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 2276 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 2282 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2288 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 2328 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr108:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2336 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 2342 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2348 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 2354 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2360 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 2366 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2372 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 2378 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2384 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 2390 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2396 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 2402 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 2408 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 2414 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 2420 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 2426 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2432 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 2472 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr117:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 2480 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 2486 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2492 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 2498 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2504 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 2510 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2516 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 2522 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2528 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 2534 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2540 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 2546 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 2552 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 2558 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 2564 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 2570 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2576 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 2582 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2588 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 2594 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2600 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 2606 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2612 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 2618 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2624 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 2630 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2636 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 2642 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 2648 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 2654 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 2660 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 2666 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2672 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 2712 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr126:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 2720 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 2726 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2732 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 2738 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2744 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 2750 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2756 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 2762 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2768 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 2774 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2780 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 2786 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 2792 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 2798 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 2804 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 2810 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2816 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 2822 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2828 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 2834 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2840 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 2846 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2852 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 2858 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2864 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 2870 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2876 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 2882 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 2888 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 2894 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 2900 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 2906 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2912 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 2952 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr135:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 2960 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 2966 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2972 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 2978 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2984 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 2990 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2996 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 3002 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3008 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 3014 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3020 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 3026 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 3032 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 3038 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 3044 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 3050 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3056 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 3062 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3068 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 3074 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3080 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 3086 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3092 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 3098 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3104 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 3110 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3116 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 3122 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 3128 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 3134 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 3140 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 3146 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3152 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 3192 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr144:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 3200 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 3206 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3212 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 3218 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3224 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 3230 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3236 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 3242 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3248 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 3254 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3260 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 3266 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 3272 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 3278 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 3284 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 3290 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3296 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 3302 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3308 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 3314 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3320 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 3326 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3332 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 3338 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3344 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 3350 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3356 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 3362 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 3368 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 3374 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 3380 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 3386 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3392 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 3432 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr153:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 3440 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 3446 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3452 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 3458 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3464 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 3470 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3476 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 3482 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3488 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 3494 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3500 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 3506 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 3512 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 3518 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 3524 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 3530 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3536 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 3542 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3548 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 3554 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3560 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 3566 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3572 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 3578 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3584 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 3590 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3596 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 3602 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 3608 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 3614 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 3620 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 3626 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3632 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 3672 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr162:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 3680 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 3686 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 3692 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 3698 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 3704 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 3710 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 3716 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 3722 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 3728 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 3734 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 3740 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 3746 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 3752 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 3758 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 3764 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 3770 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 3776 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 3782 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3788 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 3794 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3800 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 3806 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3812 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 3818 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3824 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 3830 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3836 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 3842 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 3848 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 3854 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 3860 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 3866 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3872 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 3878 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3884 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 3890 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3896 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 3902 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3908 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 3914 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3920 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 3926 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3932 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 3938 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 3944 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 3950 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 3956 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 3962 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3968 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 4008 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr171:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4016 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 4022 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4028 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 4034 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4040 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 4046 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4052 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 4058 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4064 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 4070 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4076 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 4082 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 4088 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 4094 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 4100 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 4106 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4112 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 4118 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4124 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 4130 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4136 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 4142 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4148 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 4154 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4160 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 4166 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4172 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 4178 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 4184 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 4190 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 4196 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 4202 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4208 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 4248 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr180:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 4256 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 4262 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4268 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 4274 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4280 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 4286 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4292 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 4298 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4304 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 4310 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4316 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 4322 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 4328 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 4334 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 4340 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 4346 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4352 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 4358 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4364 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 4370 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4376 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 4382 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4388 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 4394 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4400 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 4406 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4412 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 4418 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 4424 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 4430 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 4436 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 4442 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4448 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 4454 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4460 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 4466 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4472 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 4478 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4484 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 4490 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4496 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 4502 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4508 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 4514 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 4520 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 4526 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 4532 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 4538 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4544 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 4584 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr189:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 4592 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 4598 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4604 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 4610 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4616 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 4622 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4628 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 4634 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4640 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 4646 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4652 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 4658 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 4664 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 4670 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 4676 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 4682 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4688 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 4694 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4700 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 4706 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4712 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 4718 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4724 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 4730 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4736 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 4742 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4748 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 4754 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 4760 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 4766 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 4772 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 4778 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4784 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 4790 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4796 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 4802 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4808 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 4814 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4820 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 4826 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4832 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 4838 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4844 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 4850 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 4856 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 4862 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 4868 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 4874 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4880 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 4920 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr198:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 4928 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 4934 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4940 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 4946 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4952 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 4958 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4964 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 4970 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4976 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 4982 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4988 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 4994 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 5000 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 5006 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 5012 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 5018 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5024 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 5030 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5036 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 5042 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5048 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 5054 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5060 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 5066 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5072 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 5078 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5084 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 5090 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 5096 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 5102 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 5108 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 5114 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5120 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 5126 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5132 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 5138 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5144 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 5150 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5156 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 5162 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5168 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 5174 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5180 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 5186 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 5192 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 5198 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 5204 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 5210 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5216 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 5256 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr207:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 5264 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 5270 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5276 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 5282 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5288 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 5294 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5300 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 5306 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5312 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 5318 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5324 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 5330 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 5336 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 5342 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 5348 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 5354 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5360 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 5366 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5372 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 5378 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5384 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 5390 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5396 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 5402 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5408 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 5414 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5420 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 5426 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 5432 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 5438 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 5444 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 5450 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5456 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 5462 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5468 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 5474 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5480 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 5486 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5492 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 5498 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5504 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 5510 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5516 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 5522 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 5528 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 5534 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 5540 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 5546 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5552 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 5592 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr216:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 5600 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 5606 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5612 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 5618 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5624 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 5630 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5636 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 5642 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5648 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 5654 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5660 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 5666 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 5672 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 5678 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 5684 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 5690 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5696 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 5702 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5708 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 5714 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5720 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 5726 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5732 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 5738 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5744 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 5750 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5756 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 5762 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 5768 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 5774 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 5780 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 5786 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5792 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 5798 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5804 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 5810 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5816 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 5822 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5828 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 5834 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5840 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 5846 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5852 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 5858 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 5864 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 5870 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 5876 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 5882 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5888 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 5928 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr225:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 5936 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 5942 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5948 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 5954 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5960 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 5966 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5972 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 5978 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5984 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 5990 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5996 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 6002 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 6008 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 6014 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 6020 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 6026 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6032 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 6038 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6044 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 6050 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6056 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 6062 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6068 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 6074 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6080 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 6086 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6092 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 6098 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 6104 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 6110 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 6116 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6122 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6128 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 6134 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6140 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 6146 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6152 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 6158 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6164 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 6170 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6176 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 6182 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6188 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 6194 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 6200 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 6206 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 6212 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 6218 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6224 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 6264 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr234:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b1 = p; }
		
#line 6272 "gen/ragel/18__alt4_8.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6278 "gen/ragel/18__alt4_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c1 = p; }
		
#line 6284 "gen/ragel/18__alt4_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6290 "gen/ragel/18__alt4_8.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d1 = p; }
		
#line 6296 "gen/ragel/18__alt4_8.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6302 "gen/ragel/18__alt4_8.c"
		
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e1 = p; }
		
#line 6308 "gen/ragel/18__alt4_8.c"
		
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6314 "gen/ragel/18__alt4_8.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f1 = p; }
		
#line 6320 "gen/ragel/18__alt4_8.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6326 "gen/ragel/18__alt4_8.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g1 = p; }
		
#line 6332 "gen/ragel/18__alt4_8.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 6338 "gen/ragel/18__alt4_8.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h1 = p; }
		
#line 6344 "gen/ragel/18__alt4_8.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 6350 "gen/ragel/18__alt4_8.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a1 = p; }
		
#line 6356 "gen/ragel/18__alt4_8.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6362 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6368 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6374 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 6380 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6386 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 6392 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6398 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 6404 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6410 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 6416 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6422 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 6428 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 6434 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 6440 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 6446 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 6452 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6458 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 6464 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6470 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 6476 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6482 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 6488 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6494 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 6500 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6506 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 6512 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6518 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 6524 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 6530 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 6536 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 6542 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6548 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6554 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 6560 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6566 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 6572 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6578 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 6584 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6590 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 6596 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6602 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 6608 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6614 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 6620 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 6626 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 6632 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 6638 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 6644 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6650 "gen/ragel/18__alt4_8.c"
		
		{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
			else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
			else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
			else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
			else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
			if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
			else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
			else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
			else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
			else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
			outc(out, '\n');
		}
		
#line 6690 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_st33:
		p+= 1;
		if ( p == pe )
			goto _test_eof33;
		st_case_33:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr234;
			}
			case 97: {
				goto _ctr235;
			}
			case 98: {
				goto _ctr236;
			}
			case 99: {
				goto _ctr237;
			}
			case 100: {
				goto _ctr238;
			}
			case 101: {
				goto _ctr239;
			}
			case 102: {
				goto _ctr240;
			}
			case 103: {
				goto _ctr241;
			}
			case 104: {
				goto _ctr242;
			}
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr235:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a1 = p; }
		
#line 6739 "gen/ragel/18__alt4_8.c"
		
		goto _st1;
		_st1:
		p+= 1;
		if ( p == pe )
			goto _test_eof1;
		st_case_1:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr2;
			}
			case 97: {
				goto _st1;
			}
			case 98: {
				goto _ctr3;
			}
			case 99: {
				goto _ctr4;
			}
			case 100: {
				goto _ctr5;
			}
			case 101: {
				goto _ctr6;
			}
			case 102: {
				goto _ctr7;
			}
			case 103: {
				goto _ctr8;
			}
			case 104: {
				goto _ctr9;
			}
		}
		{
			goto _st0;
		}
		_ctr3:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6784 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6790 "gen/ragel/18__alt4_8.c"
		
		goto _st2;
		_ctr182:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6798 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6804 "gen/ragel/18__alt4_8.c"
		
		goto _st2;
		_ctr191:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6812 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6818 "gen/ragel/18__alt4_8.c"
		
		goto _st2;
		_ctr200:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6826 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6832 "gen/ragel/18__alt4_8.c"
		
		goto _st2;
		_ctr209:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6840 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6846 "gen/ragel/18__alt4_8.c"
		
		goto _st2;
		_ctr218:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 6854 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6860 "gen/ragel/18__alt4_8.c"
		
		goto _st2;
		_ctr227:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 6868 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6874 "gen/ragel/18__alt4_8.c"
		
		goto _st2;
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr11;
			}
			case 97: {
				goto _ctr12;
			}
			case 98: {
				goto _st2;
			}
			case 99: {
				goto _ctr13;
			}
			case 100: {
				goto _ctr14;
			}
			case 101: {
				goto _ctr15;
			}
			case 102: {
				goto _ctr16;
			}
			case 103: {
				goto _ctr17;
			}
			case 104: {
				goto _ctr18;
			}
		}
		{
			goto _st0;
		}
		_ctr12:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6919 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6925 "gen/ragel/18__alt4_8.c"
		
		goto _st3;
		_ctr100:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6933 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6939 "gen/ragel/18__alt4_8.c"
		
		goto _st3;
		_ctr118:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6947 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6953 "gen/ragel/18__alt4_8.c"
		
		goto _st3;
		_ctr127:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6961 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6967 "gen/ragel/18__alt4_8.c"
		
		goto _st3;
		_ctr136:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6975 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6981 "gen/ragel/18__alt4_8.c"
		
		goto _st3;
		_ctr145:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 6989 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6995 "gen/ragel/18__alt4_8.c"
		
		goto _st3;
		_ctr154:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 7003 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 7009 "gen/ragel/18__alt4_8.c"
		
		goto _st3;
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr20;
			}
			case 97: {
				goto _st3;
			}
			case 98: {
				goto _ctr21;
			}
			case 99: {
				goto _ctr22;
			}
			case 100: {
				goto _ctr23;
			}
			case 101: {
				goto _ctr24;
			}
			case 102: {
				goto _ctr25;
			}
			case 103: {
				goto _ctr26;
			}
			case 104: {
				goto _ctr27;
			}
		}
		{
			goto _st0;
		}
		_ctr21:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7054 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 7060 "gen/ragel/18__alt4_8.c"
		
		goto _st4;
		_ctr45:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7068 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 7074 "gen/ragel/18__alt4_8.c"
		
		goto _st4;
		_ctr56:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7082 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 7088 "gen/ragel/18__alt4_8.c"
		
		goto _st4;
		_ctr65:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7096 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 7102 "gen/ragel/18__alt4_8.c"
		
		goto _st4;
		_ctr74:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7110 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 7116 "gen/ragel/18__alt4_8.c"
		
		goto _st4;
		_ctr83:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 7124 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 7130 "gen/ragel/18__alt4_8.c"
		
		goto _st4;
		_ctr92:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 7138 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 7144 "gen/ragel/18__alt4_8.c"
		
		goto _st4;
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr29;
			}
			case 98: {
				goto _st4;
			}
		}
		{
			goto _st0;
		}
		_ctr22:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7168 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 7174 "gen/ragel/18__alt4_8.c"
		
		goto _st5;
		_ctr57:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7182 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 7188 "gen/ragel/18__alt4_8.c"
		
		goto _st5;
		_ctr66:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7196 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 7202 "gen/ragel/18__alt4_8.c"
		
		goto _st5;
		_ctr75:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7210 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 7216 "gen/ragel/18__alt4_8.c"
		
		goto _st5;
		_ctr84:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 7224 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 7230 "gen/ragel/18__alt4_8.c"
		
		goto _st5;
		_ctr93:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 7238 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 7244 "gen/ragel/18__alt4_8.c"
		
		goto _st5;
		_ctr110:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7252 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 7258 "gen/ragel/18__alt4_8.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr31;
			}
			case 99: {
				goto _st5;
			}
		}
		{
			goto _st0;
		}
		_ctr23:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7282 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 7288 "gen/ragel/18__alt4_8.c"
		
		goto _st6;
		_ctr46:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7296 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 7302 "gen/ragel/18__alt4_8.c"
		
		goto _st6;
		_ctr67:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7310 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 7316 "gen/ragel/18__alt4_8.c"
		
		goto _st6;
		_ctr76:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7324 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 7330 "gen/ragel/18__alt4_8.c"
		
		goto _st6;
		_ctr85:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 7338 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 7344 "gen/ragel/18__alt4_8.c"
		
		goto _st6;
		_ctr94:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 7352 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 7358 "gen/ragel/18__alt4_8.c"
		
		goto _st6;
		_ctr111:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7366 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 7372 "gen/ragel/18__alt4_8.c"
		
		goto _st6;
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr33;
			}
			case 100: {
				goto _st6;
			}
		}
		{
			goto _st0;
		}
		_ctr24:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7396 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 7402 "gen/ragel/18__alt4_8.c"
		
		goto _st7;
		_ctr47:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7410 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 7416 "gen/ragel/18__alt4_8.c"
		
		goto _st7;
		_ctr58:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7424 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 7430 "gen/ragel/18__alt4_8.c"
		
		goto _st7;
		_ctr77:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7438 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 7444 "gen/ragel/18__alt4_8.c"
		
		goto _st7;
		_ctr86:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 7452 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 7458 "gen/ragel/18__alt4_8.c"
		
		goto _st7;
		_ctr95:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 7466 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 7472 "gen/ragel/18__alt4_8.c"
		
		goto _st7;
		_ctr112:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7480 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 7486 "gen/ragel/18__alt4_8.c"
		
		goto _st7;
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr35;
			}
			case 101: {
				goto _st7;
			}
		}
		{
			goto _st0;
		}
		_ctr25:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7510 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 7516 "gen/ragel/18__alt4_8.c"
		
		goto _st8;
		_ctr48:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7524 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 7530 "gen/ragel/18__alt4_8.c"
		
		goto _st8;
		_ctr59:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7538 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 7544 "gen/ragel/18__alt4_8.c"
		
		goto _st8;
		_ctr68:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7552 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 7558 "gen/ragel/18__alt4_8.c"
		
		goto _st8;
		_ctr87:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 7566 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 7572 "gen/ragel/18__alt4_8.c"
		
		goto _st8;
		_ctr96:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 7580 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 7586 "gen/ragel/18__alt4_8.c"
		
		goto _st8;
		_ctr113:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7594 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 7600 "gen/ragel/18__alt4_8.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr37;
			}
			case 102: {
				goto _st8;
			}
		}
		{
			goto _st0;
		}
		_ctr26:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7624 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 7630 "gen/ragel/18__alt4_8.c"
		
		goto _st9;
		_ctr49:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7638 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 7644 "gen/ragel/18__alt4_8.c"
		
		goto _st9;
		_ctr60:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7652 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 7658 "gen/ragel/18__alt4_8.c"
		
		goto _st9;
		_ctr69:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7666 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 7672 "gen/ragel/18__alt4_8.c"
		
		goto _st9;
		_ctr78:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7680 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 7686 "gen/ragel/18__alt4_8.c"
		
		goto _st9;
		_ctr97:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 7694 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 7700 "gen/ragel/18__alt4_8.c"
		
		goto _st9;
		_ctr114:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7708 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 7714 "gen/ragel/18__alt4_8.c"
		
		goto _st9;
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
			}
			case 103: {
				goto _st9;
			}
		}
		{
			goto _st0;
		}
		_ctr27:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7738 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 7744 "gen/ragel/18__alt4_8.c"
		
		goto _st10;
		_ctr50:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7752 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 7758 "gen/ragel/18__alt4_8.c"
		
		goto _st10;
		_ctr61:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7766 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 7772 "gen/ragel/18__alt4_8.c"
		
		goto _st10;
		_ctr70:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7780 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 7786 "gen/ragel/18__alt4_8.c"
		
		goto _st10;
		_ctr79:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7794 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 7800 "gen/ragel/18__alt4_8.c"
		
		goto _st10;
		_ctr88:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 7808 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 7814 "gen/ragel/18__alt4_8.c"
		
		goto _st10;
		_ctr115:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7822 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 7828 "gen/ragel/18__alt4_8.c"
		
		goto _st10;
		_st10:
		p+= 1;
		if ( p == pe )
			goto _test_eof10;
		st_case_10:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr41;
			}
			case 104: {
				goto _st10;
			}
		}
		{
			goto _st0;
		}
		_ctr13:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 7852 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 7858 "gen/ragel/18__alt4_8.c"
		
		goto _st11;
		_ctr120:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 7866 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 7872 "gen/ragel/18__alt4_8.c"
		
		goto _st11;
		_ctr129:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 7880 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 7886 "gen/ragel/18__alt4_8.c"
		
		goto _st11;
		_ctr138:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 7894 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 7900 "gen/ragel/18__alt4_8.c"
		
		goto _st11;
		_ctr147:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 7908 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 7914 "gen/ragel/18__alt4_8.c"
		
		goto _st11;
		_ctr156:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 7922 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 7928 "gen/ragel/18__alt4_8.c"
		
		goto _st11;
		_ctr173:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 7936 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 7942 "gen/ragel/18__alt4_8.c"
		
		goto _st11;
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr43;
			}
			case 97: {
				goto _ctr44;
			}
			case 98: {
				goto _ctr45;
			}
			case 99: {
				goto _st11;
			}
			case 100: {
				goto _ctr46;
			}
			case 101: {
				goto _ctr47;
			}
			case 102: {
				goto _ctr48;
			}
			case 103: {
				goto _ctr49;
			}
			case 104: {
				goto _ctr50;
			}
		}
		{
			goto _st0;
		}
		_ctr44:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7987 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 7993 "gen/ragel/18__alt4_8.c"
		
		goto _st12;
		_ctr55:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 8001 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 8007 "gen/ragel/18__alt4_8.c"
		
		goto _st12;
		_ctr64:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 8015 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 8021 "gen/ragel/18__alt4_8.c"
		
		goto _st12;
		_ctr73:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 8029 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 8035 "gen/ragel/18__alt4_8.c"
		
		goto _st12;
		_ctr82:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 8043 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 8049 "gen/ragel/18__alt4_8.c"
		
		goto _st12;
		_ctr91:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 8057 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 8063 "gen/ragel/18__alt4_8.c"
		
		goto _st12;
		_ctr109:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 8071 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 8077 "gen/ragel/18__alt4_8.c"
		
		goto _st12;
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr52;
			}
			case 97: {
				goto _st12;
			}
		}
		{
			goto _st0;
		}
		_ctr14:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8101 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 8107 "gen/ragel/18__alt4_8.c"
		
		goto _st13;
		_ctr102:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8115 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 8121 "gen/ragel/18__alt4_8.c"
		
		goto _st13;
		_ctr130:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8129 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 8135 "gen/ragel/18__alt4_8.c"
		
		goto _st13;
		_ctr139:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8143 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 8149 "gen/ragel/18__alt4_8.c"
		
		goto _st13;
		_ctr148:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 8157 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 8163 "gen/ragel/18__alt4_8.c"
		
		goto _st13;
		_ctr157:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 8171 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 8177 "gen/ragel/18__alt4_8.c"
		
		goto _st13;
		_ctr174:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8185 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 8191 "gen/ragel/18__alt4_8.c"
		
		goto _st13;
		_st13:
		p+= 1;
		if ( p == pe )
			goto _test_eof13;
		st_case_13:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr54;
			}
			case 97: {
				goto _ctr55;
			}
			case 98: {
				goto _ctr56;
			}
			case 99: {
				goto _ctr57;
			}
			case 100: {
				goto _st13;
			}
			case 101: {
				goto _ctr58;
			}
			case 102: {
				goto _ctr59;
			}
			case 103: {
				goto _ctr60;
			}
			case 104: {
				goto _ctr61;
			}
		}
		{
			goto _st0;
		}
		_ctr15:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8236 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 8242 "gen/ragel/18__alt4_8.c"
		
		goto _st14;
		_ctr103:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8250 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 8256 "gen/ragel/18__alt4_8.c"
		
		goto _st14;
		_ctr121:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8264 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 8270 "gen/ragel/18__alt4_8.c"
		
		goto _st14;
		_ctr140:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8278 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 8284 "gen/ragel/18__alt4_8.c"
		
		goto _st14;
		_ctr149:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 8292 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 8298 "gen/ragel/18__alt4_8.c"
		
		goto _st14;
		_ctr158:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 8306 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 8312 "gen/ragel/18__alt4_8.c"
		
		goto _st14;
		_ctr175:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8320 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 8326 "gen/ragel/18__alt4_8.c"
		
		goto _st14;
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr63;
			}
			case 97: {
				goto _ctr64;
			}
			case 98: {
				goto _ctr65;
			}
			case 99: {
				goto _ctr66;
			}
			case 100: {
				goto _ctr67;
			}
			case 101: {
				goto _st14;
			}
			case 102: {
				goto _ctr68;
			}
			case 103: {
				goto _ctr69;
			}
			case 104: {
				goto _ctr70;
			}
		}
		{
			goto _st0;
		}
		_ctr16:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8371 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 8377 "gen/ragel/18__alt4_8.c"
		
		goto _st15;
		_ctr104:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8385 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 8391 "gen/ragel/18__alt4_8.c"
		
		goto _st15;
		_ctr122:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8399 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 8405 "gen/ragel/18__alt4_8.c"
		
		goto _st15;
		_ctr131:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8413 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 8419 "gen/ragel/18__alt4_8.c"
		
		goto _st15;
		_ctr150:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 8427 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 8433 "gen/ragel/18__alt4_8.c"
		
		goto _st15;
		_ctr159:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 8441 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 8447 "gen/ragel/18__alt4_8.c"
		
		goto _st15;
		_ctr176:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8455 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 8461 "gen/ragel/18__alt4_8.c"
		
		goto _st15;
		_st15:
		p+= 1;
		if ( p == pe )
			goto _test_eof15;
		st_case_15:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr72;
			}
			case 97: {
				goto _ctr73;
			}
			case 98: {
				goto _ctr74;
			}
			case 99: {
				goto _ctr75;
			}
			case 100: {
				goto _ctr76;
			}
			case 101: {
				goto _ctr77;
			}
			case 102: {
				goto _st15;
			}
			case 103: {
				goto _ctr78;
			}
			case 104: {
				goto _ctr79;
			}
		}
		{
			goto _st0;
		}
		_ctr17:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8506 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 8512 "gen/ragel/18__alt4_8.c"
		
		goto _st16;
		_ctr105:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8520 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 8526 "gen/ragel/18__alt4_8.c"
		
		goto _st16;
		_ctr123:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8534 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 8540 "gen/ragel/18__alt4_8.c"
		
		goto _st16;
		_ctr132:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8548 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 8554 "gen/ragel/18__alt4_8.c"
		
		goto _st16;
		_ctr141:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8562 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 8568 "gen/ragel/18__alt4_8.c"
		
		goto _st16;
		_ctr160:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 8576 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 8582 "gen/ragel/18__alt4_8.c"
		
		goto _st16;
		_ctr177:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8590 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 8596 "gen/ragel/18__alt4_8.c"
		
		goto _st16;
		_st16:
		p+= 1;
		if ( p == pe )
			goto _test_eof16;
		st_case_16:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr81;
			}
			case 97: {
				goto _ctr82;
			}
			case 98: {
				goto _ctr83;
			}
			case 99: {
				goto _ctr84;
			}
			case 100: {
				goto _ctr85;
			}
			case 101: {
				goto _ctr86;
			}
			case 102: {
				goto _ctr87;
			}
			case 103: {
				goto _st16;
			}
			case 104: {
				goto _ctr88;
			}
		}
		{
			goto _st0;
		}
		_ctr18:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8641 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 8647 "gen/ragel/18__alt4_8.c"
		
		goto _st17;
		_ctr106:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8655 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 8661 "gen/ragel/18__alt4_8.c"
		
		goto _st17;
		_ctr124:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8669 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 8675 "gen/ragel/18__alt4_8.c"
		
		goto _st17;
		_ctr133:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8683 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 8689 "gen/ragel/18__alt4_8.c"
		
		goto _st17;
		_ctr142:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8697 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 8703 "gen/ragel/18__alt4_8.c"
		
		goto _st17;
		_ctr151:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 8711 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 8717 "gen/ragel/18__alt4_8.c"
		
		goto _st17;
		_ctr178:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8725 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 8731 "gen/ragel/18__alt4_8.c"
		
		goto _st17;
		_st17:
		p+= 1;
		if ( p == pe )
			goto _test_eof17;
		st_case_17:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr90;
			}
			case 97: {
				goto _ctr91;
			}
			case 98: {
				goto _ctr92;
			}
			case 99: {
				goto _ctr93;
			}
			case 100: {
				goto _ctr94;
			}
			case 101: {
				goto _ctr95;
			}
			case 102: {
				goto _ctr96;
			}
			case 103: {
				goto _ctr97;
			}
			case 104: {
				goto _st17;
			}
		}
		{
			goto _st0;
		}
		_ctr4:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 8776 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 8782 "gen/ragel/18__alt4_8.c"
		
		goto _st18;
		_ctr164:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 8790 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 8796 "gen/ragel/18__alt4_8.c"
		
		goto _st18;
		_ctr192:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 8804 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 8810 "gen/ragel/18__alt4_8.c"
		
		goto _st18;
		_ctr201:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 8818 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 8824 "gen/ragel/18__alt4_8.c"
		
		goto _st18;
		_ctr210:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 8832 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 8838 "gen/ragel/18__alt4_8.c"
		
		goto _st18;
		_ctr219:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 8846 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 8852 "gen/ragel/18__alt4_8.c"
		
		goto _st18;
		_ctr228:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 8860 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 8866 "gen/ragel/18__alt4_8.c"
		
		goto _st18;
		_st18:
		p+= 1;
		if ( p == pe )
			goto _test_eof18;
		st_case_18:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr99;
			}
			case 97: {
				goto _ctr100;
			}
			case 98: {
				goto _ctr101;
			}
			case 99: {
				goto _st18;
			}
			case 100: {
				goto _ctr102;
			}
			case 101: {
				goto _ctr103;
			}
			case 102: {
				goto _ctr104;
			}
			case 103: {
				goto _ctr105;
			}
			case 104: {
				goto _ctr106;
			}
		}
		{
			goto _st0;
		}
		_ctr101:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8911 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 8917 "gen/ragel/18__alt4_8.c"
		
		goto _st19;
		_ctr119:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8925 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 8931 "gen/ragel/18__alt4_8.c"
		
		goto _st19;
		_ctr128:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8939 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 8945 "gen/ragel/18__alt4_8.c"
		
		goto _st19;
		_ctr137:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8953 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 8959 "gen/ragel/18__alt4_8.c"
		
		goto _st19;
		_ctr146:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 8967 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 8973 "gen/ragel/18__alt4_8.c"
		
		goto _st19;
		_ctr155:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 8981 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 8987 "gen/ragel/18__alt4_8.c"
		
		goto _st19;
		_ctr172:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8995 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 9001 "gen/ragel/18__alt4_8.c"
		
		goto _st19;
		_st19:
		p+= 1;
		if ( p == pe )
			goto _test_eof19;
		st_case_19:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr108;
			}
			case 97: {
				goto _ctr109;
			}
			case 98: {
				goto _st19;
			}
			case 99: {
				goto _ctr110;
			}
			case 100: {
				goto _ctr111;
			}
			case 101: {
				goto _ctr112;
			}
			case 102: {
				goto _ctr113;
			}
			case 103: {
				goto _ctr114;
			}
			case 104: {
				goto _ctr115;
			}
		}
		{
			goto _st0;
		}
		_ctr5:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9046 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 9052 "gen/ragel/18__alt4_8.c"
		
		goto _st20;
		_ctr165:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9060 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 9066 "gen/ragel/18__alt4_8.c"
		
		goto _st20;
		_ctr183:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9074 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 9080 "gen/ragel/18__alt4_8.c"
		
		goto _st20;
		_ctr202:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9088 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 9094 "gen/ragel/18__alt4_8.c"
		
		goto _st20;
		_ctr211:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9102 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 9108 "gen/ragel/18__alt4_8.c"
		
		goto _st20;
		_ctr220:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 9116 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 9122 "gen/ragel/18__alt4_8.c"
		
		goto _st20;
		_ctr229:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 9130 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 9136 "gen/ragel/18__alt4_8.c"
		
		goto _st20;
		_st20:
		p+= 1;
		if ( p == pe )
			goto _test_eof20;
		st_case_20:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr117;
			}
			case 97: {
				goto _ctr118;
			}
			case 98: {
				goto _ctr119;
			}
			case 99: {
				goto _ctr120;
			}
			case 100: {
				goto _st20;
			}
			case 101: {
				goto _ctr121;
			}
			case 102: {
				goto _ctr122;
			}
			case 103: {
				goto _ctr123;
			}
			case 104: {
				goto _ctr124;
			}
		}
		{
			goto _st0;
		}
		_ctr6:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9181 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 9187 "gen/ragel/18__alt4_8.c"
		
		goto _st21;
		_ctr166:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9195 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 9201 "gen/ragel/18__alt4_8.c"
		
		goto _st21;
		_ctr184:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9209 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 9215 "gen/ragel/18__alt4_8.c"
		
		goto _st21;
		_ctr193:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9223 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 9229 "gen/ragel/18__alt4_8.c"
		
		goto _st21;
		_ctr212:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9237 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 9243 "gen/ragel/18__alt4_8.c"
		
		goto _st21;
		_ctr221:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 9251 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 9257 "gen/ragel/18__alt4_8.c"
		
		goto _st21;
		_ctr230:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 9265 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 9271 "gen/ragel/18__alt4_8.c"
		
		goto _st21;
		_st21:
		p+= 1;
		if ( p == pe )
			goto _test_eof21;
		st_case_21:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr126;
			}
			case 97: {
				goto _ctr127;
			}
			case 98: {
				goto _ctr128;
			}
			case 99: {
				goto _ctr129;
			}
			case 100: {
				goto _ctr130;
			}
			case 101: {
				goto _st21;
			}
			case 102: {
				goto _ctr131;
			}
			case 103: {
				goto _ctr132;
			}
			case 104: {
				goto _ctr133;
			}
		}
		{
			goto _st0;
		}
		_ctr7:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9316 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 9322 "gen/ragel/18__alt4_8.c"
		
		goto _st22;
		_ctr167:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9330 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 9336 "gen/ragel/18__alt4_8.c"
		
		goto _st22;
		_ctr185:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9344 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 9350 "gen/ragel/18__alt4_8.c"
		
		goto _st22;
		_ctr194:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9358 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 9364 "gen/ragel/18__alt4_8.c"
		
		goto _st22;
		_ctr203:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9372 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 9378 "gen/ragel/18__alt4_8.c"
		
		goto _st22;
		_ctr222:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 9386 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 9392 "gen/ragel/18__alt4_8.c"
		
		goto _st22;
		_ctr231:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 9400 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 9406 "gen/ragel/18__alt4_8.c"
		
		goto _st22;
		_st22:
		p+= 1;
		if ( p == pe )
			goto _test_eof22;
		st_case_22:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr135;
			}
			case 97: {
				goto _ctr136;
			}
			case 98: {
				goto _ctr137;
			}
			case 99: {
				goto _ctr138;
			}
			case 100: {
				goto _ctr139;
			}
			case 101: {
				goto _ctr140;
			}
			case 102: {
				goto _st22;
			}
			case 103: {
				goto _ctr141;
			}
			case 104: {
				goto _ctr142;
			}
		}
		{
			goto _st0;
		}
		_ctr8:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9451 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 9457 "gen/ragel/18__alt4_8.c"
		
		goto _st23;
		_ctr168:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9465 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 9471 "gen/ragel/18__alt4_8.c"
		
		goto _st23;
		_ctr186:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9479 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 9485 "gen/ragel/18__alt4_8.c"
		
		goto _st23;
		_ctr195:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9493 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 9499 "gen/ragel/18__alt4_8.c"
		
		goto _st23;
		_ctr204:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9507 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 9513 "gen/ragel/18__alt4_8.c"
		
		goto _st23;
		_ctr213:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9521 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 9527 "gen/ragel/18__alt4_8.c"
		
		goto _st23;
		_ctr232:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 9535 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 9541 "gen/ragel/18__alt4_8.c"
		
		goto _st23;
		_st23:
		p+= 1;
		if ( p == pe )
			goto _test_eof23;
		st_case_23:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr144;
			}
			case 97: {
				goto _ctr145;
			}
			case 98: {
				goto _ctr146;
			}
			case 99: {
				goto _ctr147;
			}
			case 100: {
				goto _ctr148;
			}
			case 101: {
				goto _ctr149;
			}
			case 102: {
				goto _ctr150;
			}
			case 103: {
				goto _st23;
			}
			case 104: {
				goto _ctr151;
			}
		}
		{
			goto _st0;
		}
		_ctr9:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9586 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 9592 "gen/ragel/18__alt4_8.c"
		
		goto _st24;
		_ctr169:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9600 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 9606 "gen/ragel/18__alt4_8.c"
		
		goto _st24;
		_ctr187:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9614 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 9620 "gen/ragel/18__alt4_8.c"
		
		goto _st24;
		_ctr196:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9628 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 9634 "gen/ragel/18__alt4_8.c"
		
		goto _st24;
		_ctr205:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9642 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 9648 "gen/ragel/18__alt4_8.c"
		
		goto _st24;
		_ctr214:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9656 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 9662 "gen/ragel/18__alt4_8.c"
		
		goto _st24;
		_ctr223:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 9670 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 9676 "gen/ragel/18__alt4_8.c"
		
		goto _st24;
		_st24:
		p+= 1;
		if ( p == pe )
			goto _test_eof24;
		st_case_24:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr153;
			}
			case 97: {
				goto _ctr154;
			}
			case 98: {
				goto _ctr155;
			}
			case 99: {
				goto _ctr156;
			}
			case 100: {
				goto _ctr157;
			}
			case 101: {
				goto _ctr158;
			}
			case 102: {
				goto _ctr159;
			}
			case 103: {
				goto _ctr160;
			}
			case 104: {
				goto _st24;
			}
		}
		{
			goto _st0;
		}
		_ctr236:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b1 = p; }
		
#line 9721 "gen/ragel/18__alt4_8.c"
		
		goto _st25;
		_st25:
		p+= 1;
		if ( p == pe )
			goto _test_eof25;
		st_case_25:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr162;
			}
			case 97: {
				goto _ctr163;
			}
			case 98: {
				goto _st25;
			}
			case 99: {
				goto _ctr164;
			}
			case 100: {
				goto _ctr165;
			}
			case 101: {
				goto _ctr166;
			}
			case 102: {
				goto _ctr167;
			}
			case 103: {
				goto _ctr168;
			}
			case 104: {
				goto _ctr169;
			}
		}
		{
			goto _st0;
		}
		_ctr163:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9766 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 9772 "gen/ragel/18__alt4_8.c"
		
		goto _st26;
		_ctr181:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9780 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 9786 "gen/ragel/18__alt4_8.c"
		
		goto _st26;
		_ctr190:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9794 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 9800 "gen/ragel/18__alt4_8.c"
		
		goto _st26;
		_ctr199:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9808 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 9814 "gen/ragel/18__alt4_8.c"
		
		goto _st26;
		_ctr208:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9822 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 9828 "gen/ragel/18__alt4_8.c"
		
		goto _st26;
		_ctr217:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 9836 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 9842 "gen/ragel/18__alt4_8.c"
		
		goto _st26;
		_ctr226:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 9850 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 9856 "gen/ragel/18__alt4_8.c"
		
		goto _st26;
		_st26:
		p+= 1;
		if ( p == pe )
			goto _test_eof26;
		st_case_26:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr171;
			}
			case 97: {
				goto _st26;
			}
			case 98: {
				goto _ctr172;
			}
			case 99: {
				goto _ctr173;
			}
			case 100: {
				goto _ctr174;
			}
			case 101: {
				goto _ctr175;
			}
			case 102: {
				goto _ctr176;
			}
			case 103: {
				goto _ctr177;
			}
			case 104: {
				goto _ctr178;
			}
		}
		{
			goto _st0;
		}
		_ctr237:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c1 = p; }
		
#line 9901 "gen/ragel/18__alt4_8.c"
		
		goto _st27;
		_st27:
		p+= 1;
		if ( p == pe )
			goto _test_eof27;
		st_case_27:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr180;
			}
			case 97: {
				goto _ctr181;
			}
			case 98: {
				goto _ctr182;
			}
			case 99: {
				goto _st27;
			}
			case 100: {
				goto _ctr183;
			}
			case 101: {
				goto _ctr184;
			}
			case 102: {
				goto _ctr185;
			}
			case 103: {
				goto _ctr186;
			}
			case 104: {
				goto _ctr187;
			}
		}
		{
			goto _st0;
		}
		_ctr238:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d1 = p; }
		
#line 9946 "gen/ragel/18__alt4_8.c"
		
		goto _st28;
		_st28:
		p+= 1;
		if ( p == pe )
			goto _test_eof28;
		st_case_28:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr189;
			}
			case 97: {
				goto _ctr190;
			}
			case 98: {
				goto _ctr191;
			}
			case 99: {
				goto _ctr192;
			}
			case 100: {
				goto _st28;
			}
			case 101: {
				goto _ctr193;
			}
			case 102: {
				goto _ctr194;
			}
			case 103: {
				goto _ctr195;
			}
			case 104: {
				goto _ctr196;
			}
		}
		{
			goto _st0;
		}
		_ctr239:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e1 = p; }
		
#line 9991 "gen/ragel/18__alt4_8.c"
		
		goto _st29;
		_st29:
		p+= 1;
		if ( p == pe )
			goto _test_eof29;
		st_case_29:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr198;
			}
			case 97: {
				goto _ctr199;
			}
			case 98: {
				goto _ctr200;
			}
			case 99: {
				goto _ctr201;
			}
			case 100: {
				goto _ctr202;
			}
			case 101: {
				goto _st29;
			}
			case 102: {
				goto _ctr203;
			}
			case 103: {
				goto _ctr204;
			}
			case 104: {
				goto _ctr205;
			}
		}
		{
			goto _st0;
		}
		_ctr240:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f1 = p; }
		
#line 10036 "gen/ragel/18__alt4_8.c"
		
		goto _st30;
		_st30:
		p+= 1;
		if ( p == pe )
			goto _test_eof30;
		st_case_30:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr207;
			}
			case 97: {
				goto _ctr208;
			}
			case 98: {
				goto _ctr209;
			}
			case 99: {
				goto _ctr210;
			}
			case 100: {
				goto _ctr211;
			}
			case 101: {
				goto _ctr212;
			}
			case 102: {
				goto _st30;
			}
			case 103: {
				goto _ctr213;
			}
			case 104: {
				goto _ctr214;
			}
		}
		{
			goto _st0;
		}
		_ctr241:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g1 = p; }
		
#line 10081 "gen/ragel/18__alt4_8.c"
		
		goto _st31;
		_st31:
		p+= 1;
		if ( p == pe )
			goto _test_eof31;
		st_case_31:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr216;
			}
			case 97: {
				goto _ctr217;
			}
			case 98: {
				goto _ctr218;
			}
			case 99: {
				goto _ctr219;
			}
			case 100: {
				goto _ctr220;
			}
			case 101: {
				goto _ctr221;
			}
			case 102: {
				goto _ctr222;
			}
			case 103: {
				goto _st31;
			}
			case 104: {
				goto _ctr223;
			}
		}
		{
			goto _st0;
		}
		_ctr242:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h1 = p; }
		
#line 10126 "gen/ragel/18__alt4_8.c"
		
		goto _st32;
		_st32:
		p+= 1;
		if ( p == pe )
			goto _test_eof32;
		st_case_32:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr225;
			}
			case 97: {
				goto _ctr226;
			}
			case 98: {
				goto _ctr227;
			}
			case 99: {
				goto _ctr228;
			}
			case 100: {
				goto _ctr229;
			}
			case 101: {
				goto _ctr230;
			}
			case 102: {
				goto _ctr231;
			}
			case 103: {
				goto _ctr232;
			}
			case 104: {
				goto _st32;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof33: cs = 33; goto _test_eof; 
		_test_eof1: cs = 1; goto _test_eof; 
		_test_eof2: cs = 2; goto _test_eof; 
		_test_eof3: cs = 3; goto _test_eof; 
		_test_eof4: cs = 4; goto _test_eof; 
		_test_eof5: cs = 5; goto _test_eof; 
		_test_eof6: cs = 6; goto _test_eof; 
		_test_eof7: cs = 7; goto _test_eof; 
		_test_eof8: cs = 8; goto _test_eof; 
		_test_eof9: cs = 9; goto _test_eof; 
		_test_eof10: cs = 10; goto _test_eof; 
		_test_eof11: cs = 11; goto _test_eof; 
		_test_eof12: cs = 12; goto _test_eof; 
		_test_eof13: cs = 13; goto _test_eof; 
		_test_eof14: cs = 14; goto _test_eof; 
		_test_eof15: cs = 15; goto _test_eof; 
		_test_eof16: cs = 16; goto _test_eof; 
		_test_eof17: cs = 17; goto _test_eof; 
		_test_eof18: cs = 18; goto _test_eof; 
		_test_eof19: cs = 19; goto _test_eof; 
		_test_eof20: cs = 20; goto _test_eof; 
		_test_eof21: cs = 21; goto _test_eof; 
		_test_eof22: cs = 22; goto _test_eof; 
		_test_eof23: cs = 23; goto _test_eof; 
		_test_eof24: cs = 24; goto _test_eof; 
		_test_eof25: cs = 25; goto _test_eof; 
		_test_eof26: cs = 26; goto _test_eof; 
		_test_eof27: cs = 27; goto _test_eof; 
		_test_eof28: cs = 28; goto _test_eof; 
		_test_eof29: cs = 29; goto _test_eof; 
		_test_eof30: cs = 30; goto _test_eof; 
		_test_eof31: cs = 31; goto _test_eof; 
		_test_eof32: cs = 32; goto _test_eof; 
		
		_test_eof: {}
		if ( cs >= 33 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 116 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
	
	
	in->p = p;
	in->pe = pe;
}
