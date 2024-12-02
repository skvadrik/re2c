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
		_ctr2:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 125 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 131 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 137 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 143 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 149 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 155 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 161 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 167 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 173 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 179 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 185 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 191 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 197 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 203 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 209 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 215 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 221 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 227 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 233 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 239 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 245 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 251 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 257 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 263 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 269 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 275 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 281 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 287 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 293 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 299 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 305 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 311 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 317 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 323 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 329 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 335 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 341 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 347 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 353 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 359 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 365 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 371 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 377 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 383 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 389 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 395 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 401 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 407 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 413 "gen/ragel/18__alt4_8.c"
		
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
		
#line 453 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr11:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 461 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 467 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 473 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 479 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 485 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 491 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 497 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 503 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 509 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 515 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 521 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 527 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 533 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 539 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 545 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 551 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 557 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 563 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 569 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 575 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 581 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 587 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 593 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 599 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 605 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 611 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 617 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 623 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 629 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 635 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 641 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 647 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 653 "gen/ragel/18__alt4_8.c"
		
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
		
#line 693 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr20:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 701 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 707 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 713 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 719 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 725 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 731 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 737 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 743 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 749 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 755 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 761 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 767 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 773 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 779 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 785 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 791 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 797 "gen/ragel/18__alt4_8.c"
		
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
		
#line 837 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr29:
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 845 "gen/ragel/18__alt4_8.c"
		
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
		
#line 885 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr31:
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 893 "gen/ragel/18__alt4_8.c"
		
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
		
#line 933 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr33:
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 941 "gen/ragel/18__alt4_8.c"
		
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
		
#line 981 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr35:
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 989 "gen/ragel/18__alt4_8.c"
		
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
		
#line 1029 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr37:
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1037 "gen/ragel/18__alt4_8.c"
		
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
		
#line 1077 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr39:
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 1085 "gen/ragel/18__alt4_8.c"
		
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
		
#line 1125 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr41:
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 1133 "gen/ragel/18__alt4_8.c"
		
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
		
#line 1173 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr43:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 1181 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 1187 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1193 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 1199 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1205 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 1211 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1217 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 1223 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1229 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 1235 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1241 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 1247 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 1253 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 1259 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 1265 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 1271 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1277 "gen/ragel/18__alt4_8.c"
		
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
		
#line 1317 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr52:
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1325 "gen/ragel/18__alt4_8.c"
		
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
		
#line 1365 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr54:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 1373 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 1379 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1385 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 1391 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1397 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 1403 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1409 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 1415 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1421 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 1427 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1433 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 1439 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 1445 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 1451 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 1457 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 1463 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1469 "gen/ragel/18__alt4_8.c"
		
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
		
#line 1509 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr63:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 1517 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 1523 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1529 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 1535 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1541 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 1547 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1553 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 1559 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1565 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 1571 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1577 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 1583 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 1589 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 1595 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 1601 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 1607 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1613 "gen/ragel/18__alt4_8.c"
		
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
		
#line 1653 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr72:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 1661 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 1667 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1673 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 1679 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1685 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 1691 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1697 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 1703 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1709 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 1715 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1721 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 1727 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 1733 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 1739 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 1745 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 1751 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1757 "gen/ragel/18__alt4_8.c"
		
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
		
#line 1797 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr81:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 1805 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 1811 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1817 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 1823 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1829 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 1835 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1841 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 1847 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1853 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 1859 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1865 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 1871 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 1877 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 1883 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 1889 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 1895 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1901 "gen/ragel/18__alt4_8.c"
		
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
		
#line 1941 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr90:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 1949 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 1955 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1961 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 1967 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1973 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 1979 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1985 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 1991 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 1997 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 2003 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2009 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 2015 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 2021 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 2027 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 2033 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 2039 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2045 "gen/ragel/18__alt4_8.c"
		
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
		
#line 2085 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr99:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 2093 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 2099 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2105 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 2111 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2117 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 2123 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2129 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 2135 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2141 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 2147 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2153 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 2159 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 2165 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 2171 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 2177 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 2183 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2189 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 2195 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2201 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 2207 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2213 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 2219 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2225 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 2231 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2237 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 2243 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2249 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 2255 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 2261 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 2267 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 2273 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 2279 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2285 "gen/ragel/18__alt4_8.c"
		
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
		
#line 2325 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr108:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2333 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 2339 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2345 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 2351 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2357 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 2363 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2369 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 2375 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2381 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 2387 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2393 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 2399 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 2405 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 2411 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 2417 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 2423 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2429 "gen/ragel/18__alt4_8.c"
		
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
		
#line 2469 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr117:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 2477 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 2483 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2489 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 2495 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2501 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 2507 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2513 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 2519 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2525 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 2531 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2537 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 2543 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 2549 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 2555 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 2561 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 2567 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2573 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 2579 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2585 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 2591 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2597 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 2603 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2609 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 2615 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2621 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 2627 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2633 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 2639 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 2645 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 2651 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 2657 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 2663 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2669 "gen/ragel/18__alt4_8.c"
		
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
		
#line 2709 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr126:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 2717 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 2723 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2729 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 2735 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2741 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 2747 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2753 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 2759 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2765 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 2771 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2777 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 2783 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 2789 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 2795 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 2801 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 2807 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2813 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 2819 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2825 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 2831 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2837 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 2843 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2849 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 2855 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2861 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 2867 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2873 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 2879 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 2885 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 2891 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 2897 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 2903 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 2909 "gen/ragel/18__alt4_8.c"
		
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
		
#line 2949 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr135:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 2957 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 2963 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2969 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 2975 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2981 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 2987 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 2993 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 2999 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3005 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 3011 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3017 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 3023 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 3029 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 3035 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 3041 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 3047 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3053 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 3059 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3065 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 3071 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3077 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 3083 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3089 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 3095 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3101 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 3107 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3113 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 3119 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 3125 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 3131 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 3137 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 3143 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3149 "gen/ragel/18__alt4_8.c"
		
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
		
#line 3189 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr144:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 3197 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 3203 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3209 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 3215 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3221 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 3227 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3233 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 3239 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3245 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 3251 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3257 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 3263 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 3269 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 3275 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 3281 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 3287 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3293 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 3299 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3305 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 3311 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3317 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 3323 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3329 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 3335 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3341 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 3347 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3353 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 3359 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 3365 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 3371 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 3377 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 3383 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3389 "gen/ragel/18__alt4_8.c"
		
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
		
#line 3429 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr153:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 3437 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 3443 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3449 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 3455 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3461 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 3467 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3473 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 3479 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3485 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 3491 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3497 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 3503 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 3509 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 3515 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 3521 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 3527 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3533 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 3539 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3545 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 3551 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3557 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 3563 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3569 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 3575 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3581 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 3587 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3593 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 3599 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 3605 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 3611 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 3617 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 3623 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3629 "gen/ragel/18__alt4_8.c"
		
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
		
#line 3669 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr162:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 3677 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 3683 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 3689 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 3695 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 3701 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 3707 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 3713 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 3719 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 3725 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 3731 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 3737 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 3743 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 3749 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 3755 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 3761 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 3767 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 3773 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 3779 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3785 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 3791 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3797 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 3803 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3809 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 3815 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3821 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 3827 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3833 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 3839 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 3845 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 3851 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 3857 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 3863 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 3869 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 3875 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3881 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 3887 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3893 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 3899 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3905 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 3911 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3917 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 3923 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3929 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 3935 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 3941 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 3947 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 3953 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 3959 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 3965 "gen/ragel/18__alt4_8.c"
		
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
		
#line 4005 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr171:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4013 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 4019 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4025 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 4031 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4037 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 4043 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4049 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 4055 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4061 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 4067 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4073 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 4079 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 4085 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 4091 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 4097 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 4103 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4109 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 4115 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4121 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 4127 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4133 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 4139 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4145 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 4151 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4157 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 4163 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4169 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 4175 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 4181 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 4187 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 4193 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 4199 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4205 "gen/ragel/18__alt4_8.c"
		
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
		
#line 4245 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr180:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 4253 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 4259 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4265 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 4271 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4277 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 4283 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4289 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 4295 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4301 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 4307 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4313 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 4319 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 4325 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 4331 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 4337 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 4343 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4349 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 4355 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4361 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 4367 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4373 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 4379 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4385 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 4391 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4397 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 4403 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4409 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 4415 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 4421 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 4427 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 4433 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 4439 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4445 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 4451 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4457 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 4463 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4469 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 4475 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4481 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 4487 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4493 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 4499 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4505 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 4511 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 4517 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 4523 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 4529 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 4535 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4541 "gen/ragel/18__alt4_8.c"
		
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
		
#line 4581 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr189:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 4589 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 4595 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4601 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 4607 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4613 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 4619 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4625 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 4631 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4637 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 4643 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4649 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 4655 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 4661 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 4667 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 4673 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 4679 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4685 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 4691 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4697 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 4703 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4709 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 4715 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4721 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 4727 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4733 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 4739 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4745 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 4751 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 4757 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 4763 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 4769 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 4775 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 4781 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 4787 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4793 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 4799 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4805 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 4811 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4817 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 4823 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4829 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 4835 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4841 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 4847 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 4853 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 4859 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 4865 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 4871 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 4877 "gen/ragel/18__alt4_8.c"
		
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
		
#line 4917 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr198:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 4925 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 4931 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4937 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 4943 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4949 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 4955 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4961 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 4967 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4973 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 4979 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 4985 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 4991 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 4997 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 5003 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 5009 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 5015 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5021 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 5027 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5033 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 5039 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5045 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 5051 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5057 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 5063 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5069 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 5075 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5081 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 5087 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 5093 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 5099 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 5105 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 5111 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5117 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 5123 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5129 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 5135 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5141 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 5147 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5153 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 5159 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5165 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 5171 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5177 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 5183 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 5189 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 5195 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 5201 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 5207 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5213 "gen/ragel/18__alt4_8.c"
		
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
		
#line 5253 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr207:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 5261 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 5267 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5273 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 5279 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5285 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 5291 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5297 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 5303 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5309 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 5315 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5321 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 5327 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 5333 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 5339 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 5345 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 5351 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5357 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 5363 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5369 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 5375 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5381 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 5387 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5393 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 5399 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5405 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 5411 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5417 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 5423 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 5429 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 5435 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 5441 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 5447 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5453 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 5459 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5465 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 5471 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5477 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 5483 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5489 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 5495 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5501 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 5507 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5513 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 5519 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 5525 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 5531 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 5537 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 5543 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5549 "gen/ragel/18__alt4_8.c"
		
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
		
#line 5589 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr216:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 5597 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 5603 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5609 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 5615 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5621 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 5627 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5633 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 5639 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5645 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 5651 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5657 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 5663 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 5669 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 5675 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 5681 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 5687 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5693 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 5699 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5705 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 5711 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5717 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 5723 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5729 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 5735 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5741 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 5747 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5753 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 5759 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 5765 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 5771 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 5777 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 5783 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 5789 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 5795 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5801 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 5807 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5813 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 5819 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5825 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 5831 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5837 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 5843 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5849 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 5855 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 5861 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 5867 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 5873 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 5879 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 5885 "gen/ragel/18__alt4_8.c"
		
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
		
#line 5925 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr225:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 5933 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 5939 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5945 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 5951 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5957 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 5963 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5969 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 5975 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5981 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 5987 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 5993 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 5999 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 6005 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 6011 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 6017 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 6023 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6029 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 6035 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6041 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 6047 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6053 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 6059 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6065 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 6071 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6077 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 6083 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6089 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 6095 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 6101 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 6107 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 6113 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6119 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6125 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 6131 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6137 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 6143 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6149 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 6155 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6161 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 6167 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6173 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 6179 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6185 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 6191 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 6197 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 6203 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 6209 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 6215 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6221 "gen/ragel/18__alt4_8.c"
		
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
		
#line 6261 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_ctr234:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b1 = p; }
		
#line 6269 "gen/ragel/18__alt4_8.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6275 "gen/ragel/18__alt4_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c1 = p; }
		
#line 6281 "gen/ragel/18__alt4_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6287 "gen/ragel/18__alt4_8.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d1 = p; }
		
#line 6293 "gen/ragel/18__alt4_8.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6299 "gen/ragel/18__alt4_8.c"
		
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e1 = p; }
		
#line 6305 "gen/ragel/18__alt4_8.c"
		
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6311 "gen/ragel/18__alt4_8.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f1 = p; }
		
#line 6317 "gen/ragel/18__alt4_8.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6323 "gen/ragel/18__alt4_8.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g1 = p; }
		
#line 6329 "gen/ragel/18__alt4_8.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 6335 "gen/ragel/18__alt4_8.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h1 = p; }
		
#line 6341 "gen/ragel/18__alt4_8.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 6347 "gen/ragel/18__alt4_8.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a1 = p; }
		
#line 6353 "gen/ragel/18__alt4_8.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6359 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6365 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6371 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 6377 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6383 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 6389 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6395 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 6401 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6407 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 6413 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6419 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 6425 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 6431 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 6437 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 6443 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 6449 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6455 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 6461 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6467 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 6473 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6479 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 6485 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6491 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 6497 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6503 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 6509 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6515 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 6521 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 6527 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 6533 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 6539 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6545 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 6551 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 6557 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6563 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 6569 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6575 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 6581 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6587 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 6593 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6599 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 6605 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6611 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 6617 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
		
#line 6623 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 6629 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
		
#line 6635 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 6641 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
		
#line 6647 "gen/ragel/18__alt4_8.c"
		
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
		
#line 6687 "gen/ragel/18__alt4_8.c"
		
		goto _st33;
		_st33:
		p+= 1;
		st_case_33:
		if ( p == pe )
			goto _out33;
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
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr235:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a1 = p; }
		
#line 6733 "gen/ragel/18__alt4_8.c"
		
		goto _st1;
		_st1:
		p+= 1;
		st_case_1:
		if ( p == pe )
			goto _out1;
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
		goto _st0;
		_ctr3:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6776 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6782 "gen/ragel/18__alt4_8.c"
		
		goto _st2;
		_ctr182:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6790 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6796 "gen/ragel/18__alt4_8.c"
		
		goto _st2;
		_ctr191:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6804 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6810 "gen/ragel/18__alt4_8.c"
		
		goto _st2;
		_ctr200:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6818 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6824 "gen/ragel/18__alt4_8.c"
		
		goto _st2;
		_ctr209:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 6832 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6838 "gen/ragel/18__alt4_8.c"
		
		goto _st2;
		_ctr218:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 6846 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6852 "gen/ragel/18__alt4_8.c"
		
		goto _st2;
		_ctr227:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 6860 "gen/ragel/18__alt4_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b3 = p; }
		
#line 6866 "gen/ragel/18__alt4_8.c"
		
		goto _st2;
		_st2:
		p+= 1;
		st_case_2:
		if ( p == pe )
			goto _out2;
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
		goto _st0;
		_ctr12:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6909 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6915 "gen/ragel/18__alt4_8.c"
		
		goto _st3;
		_ctr100:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6923 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6929 "gen/ragel/18__alt4_8.c"
		
		goto _st3;
		_ctr118:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6937 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6943 "gen/ragel/18__alt4_8.c"
		
		goto _st3;
		_ctr127:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6951 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6957 "gen/ragel/18__alt4_8.c"
		
		goto _st3;
		_ctr136:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 6965 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6971 "gen/ragel/18__alt4_8.c"
		
		goto _st3;
		_ctr145:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 6979 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6985 "gen/ragel/18__alt4_8.c"
		
		goto _st3;
		_ctr154:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 6993 "gen/ragel/18__alt4_8.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a5 = p; }
		
#line 6999 "gen/ragel/18__alt4_8.c"
		
		goto _st3;
		_st3:
		p+= 1;
		st_case_3:
		if ( p == pe )
			goto _out3;
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
		goto _st0;
		_ctr21:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7042 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 7048 "gen/ragel/18__alt4_8.c"
		
		goto _st4;
		_ctr45:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7056 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 7062 "gen/ragel/18__alt4_8.c"
		
		goto _st4;
		_ctr56:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7070 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 7076 "gen/ragel/18__alt4_8.c"
		
		goto _st4;
		_ctr65:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7084 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 7090 "gen/ragel/18__alt4_8.c"
		
		goto _st4;
		_ctr74:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7098 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 7104 "gen/ragel/18__alt4_8.c"
		
		goto _st4;
		_ctr83:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 7112 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 7118 "gen/ragel/18__alt4_8.c"
		
		goto _st4;
		_ctr92:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 7126 "gen/ragel/18__alt4_8.c"
		
		{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b7 = p; }
		
#line 7132 "gen/ragel/18__alt4_8.c"
		
		goto _st4;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr29;
			}
			case 98: {
				goto _st4;
			}
		}
		goto _st0;
		_ctr22:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7154 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 7160 "gen/ragel/18__alt4_8.c"
		
		goto _st5;
		_ctr57:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7168 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 7174 "gen/ragel/18__alt4_8.c"
		
		goto _st5;
		_ctr66:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7182 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 7188 "gen/ragel/18__alt4_8.c"
		
		goto _st5;
		_ctr75:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7196 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 7202 "gen/ragel/18__alt4_8.c"
		
		goto _st5;
		_ctr84:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 7210 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 7216 "gen/ragel/18__alt4_8.c"
		
		goto _st5;
		_ctr93:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 7224 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 7230 "gen/ragel/18__alt4_8.c"
		
		goto _st5;
		_ctr110:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7238 "gen/ragel/18__alt4_8.c"
		
		{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c7 = p; }
		
#line 7244 "gen/ragel/18__alt4_8.c"
		
		goto _st5;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr31;
			}
			case 99: {
				goto _st5;
			}
		}
		goto _st0;
		_ctr23:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7266 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 7272 "gen/ragel/18__alt4_8.c"
		
		goto _st6;
		_ctr46:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7280 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 7286 "gen/ragel/18__alt4_8.c"
		
		goto _st6;
		_ctr67:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7294 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 7300 "gen/ragel/18__alt4_8.c"
		
		goto _st6;
		_ctr76:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7308 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 7314 "gen/ragel/18__alt4_8.c"
		
		goto _st6;
		_ctr85:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 7322 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 7328 "gen/ragel/18__alt4_8.c"
		
		goto _st6;
		_ctr94:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 7336 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 7342 "gen/ragel/18__alt4_8.c"
		
		goto _st6;
		_ctr111:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7350 "gen/ragel/18__alt4_8.c"
		
		{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d7 = p; }
		
#line 7356 "gen/ragel/18__alt4_8.c"
		
		goto _st6;
		_st6:
		p+= 1;
		st_case_6:
		if ( p == pe )
			goto _out6;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr33;
			}
			case 100: {
				goto _st6;
			}
		}
		goto _st0;
		_ctr24:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7378 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 7384 "gen/ragel/18__alt4_8.c"
		
		goto _st7;
		_ctr47:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7392 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 7398 "gen/ragel/18__alt4_8.c"
		
		goto _st7;
		_ctr58:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7406 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 7412 "gen/ragel/18__alt4_8.c"
		
		goto _st7;
		_ctr77:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7420 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 7426 "gen/ragel/18__alt4_8.c"
		
		goto _st7;
		_ctr86:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 7434 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 7440 "gen/ragel/18__alt4_8.c"
		
		goto _st7;
		_ctr95:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 7448 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 7454 "gen/ragel/18__alt4_8.c"
		
		goto _st7;
		_ctr112:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7462 "gen/ragel/18__alt4_8.c"
		
		{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e7 = p; }
		
#line 7468 "gen/ragel/18__alt4_8.c"
		
		goto _st7;
		_st7:
		p+= 1;
		st_case_7:
		if ( p == pe )
			goto _out7;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr35;
			}
			case 101: {
				goto _st7;
			}
		}
		goto _st0;
		_ctr25:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7490 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 7496 "gen/ragel/18__alt4_8.c"
		
		goto _st8;
		_ctr48:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7504 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 7510 "gen/ragel/18__alt4_8.c"
		
		goto _st8;
		_ctr59:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7518 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 7524 "gen/ragel/18__alt4_8.c"
		
		goto _st8;
		_ctr68:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7532 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 7538 "gen/ragel/18__alt4_8.c"
		
		goto _st8;
		_ctr87:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 7546 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 7552 "gen/ragel/18__alt4_8.c"
		
		goto _st8;
		_ctr96:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 7560 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 7566 "gen/ragel/18__alt4_8.c"
		
		goto _st8;
		_ctr113:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7574 "gen/ragel/18__alt4_8.c"
		
		{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f7 = p; }
		
#line 7580 "gen/ragel/18__alt4_8.c"
		
		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr37;
			}
			case 102: {
				goto _st8;
			}
		}
		goto _st0;
		_ctr26:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7602 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 7608 "gen/ragel/18__alt4_8.c"
		
		goto _st9;
		_ctr49:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7616 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 7622 "gen/ragel/18__alt4_8.c"
		
		goto _st9;
		_ctr60:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7630 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 7636 "gen/ragel/18__alt4_8.c"
		
		goto _st9;
		_ctr69:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7644 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 7650 "gen/ragel/18__alt4_8.c"
		
		goto _st9;
		_ctr78:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7658 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 7664 "gen/ragel/18__alt4_8.c"
		
		goto _st9;
		_ctr97:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 7672 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 7678 "gen/ragel/18__alt4_8.c"
		
		goto _st9;
		_ctr114:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7686 "gen/ragel/18__alt4_8.c"
		
		{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g7 = p; }
		
#line 7692 "gen/ragel/18__alt4_8.c"
		
		goto _st9;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
			}
			case 103: {
				goto _st9;
			}
		}
		goto _st0;
		_ctr27:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7714 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 7720 "gen/ragel/18__alt4_8.c"
		
		goto _st10;
		_ctr50:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7728 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 7734 "gen/ragel/18__alt4_8.c"
		
		goto _st10;
		_ctr61:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7742 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 7748 "gen/ragel/18__alt4_8.c"
		
		goto _st10;
		_ctr70:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7756 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 7762 "gen/ragel/18__alt4_8.c"
		
		goto _st10;
		_ctr79:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7770 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 7776 "gen/ragel/18__alt4_8.c"
		
		goto _st10;
		_ctr88:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 7784 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 7790 "gen/ragel/18__alt4_8.c"
		
		goto _st10;
		_ctr115:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7798 "gen/ragel/18__alt4_8.c"
		
		{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h7 = p; }
		
#line 7804 "gen/ragel/18__alt4_8.c"
		
		goto _st10;
		_st10:
		p+= 1;
		st_case_10:
		if ( p == pe )
			goto _out10;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr41;
			}
			case 104: {
				goto _st10;
			}
		}
		goto _st0;
		_ctr13:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 7826 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 7832 "gen/ragel/18__alt4_8.c"
		
		goto _st11;
		_ctr120:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 7840 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 7846 "gen/ragel/18__alt4_8.c"
		
		goto _st11;
		_ctr129:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 7854 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 7860 "gen/ragel/18__alt4_8.c"
		
		goto _st11;
		_ctr138:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 7868 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 7874 "gen/ragel/18__alt4_8.c"
		
		goto _st11;
		_ctr147:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 7882 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 7888 "gen/ragel/18__alt4_8.c"
		
		goto _st11;
		_ctr156:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 7896 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 7902 "gen/ragel/18__alt4_8.c"
		
		goto _st11;
		_ctr173:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 7910 "gen/ragel/18__alt4_8.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c5 = p; }
		
#line 7916 "gen/ragel/18__alt4_8.c"
		
		goto _st11;
		_st11:
		p+= 1;
		st_case_11:
		if ( p == pe )
			goto _out11;
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
		goto _st0;
		_ctr44:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7959 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 7965 "gen/ragel/18__alt4_8.c"
		
		goto _st12;
		_ctr55:
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7973 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 7979 "gen/ragel/18__alt4_8.c"
		
		goto _st12;
		_ctr64:
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 7987 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 7993 "gen/ragel/18__alt4_8.c"
		
		goto _st12;
		_ctr73:
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 8001 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 8007 "gen/ragel/18__alt4_8.c"
		
		goto _st12;
		_ctr82:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
		
#line 8015 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 8021 "gen/ragel/18__alt4_8.c"
		
		goto _st12;
		_ctr91:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
		
#line 8029 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 8035 "gen/ragel/18__alt4_8.c"
		
		goto _st12;
		_ctr109:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
		
#line 8043 "gen/ragel/18__alt4_8.c"
		
		{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a7 = p; }
		
#line 8049 "gen/ragel/18__alt4_8.c"
		
		goto _st12;
		_st12:
		p+= 1;
		st_case_12:
		if ( p == pe )
			goto _out12;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr52;
			}
			case 97: {
				goto _st12;
			}
		}
		goto _st0;
		_ctr14:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8071 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 8077 "gen/ragel/18__alt4_8.c"
		
		goto _st13;
		_ctr102:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8085 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 8091 "gen/ragel/18__alt4_8.c"
		
		goto _st13;
		_ctr130:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8099 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 8105 "gen/ragel/18__alt4_8.c"
		
		goto _st13;
		_ctr139:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8113 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 8119 "gen/ragel/18__alt4_8.c"
		
		goto _st13;
		_ctr148:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 8127 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 8133 "gen/ragel/18__alt4_8.c"
		
		goto _st13;
		_ctr157:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 8141 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 8147 "gen/ragel/18__alt4_8.c"
		
		goto _st13;
		_ctr174:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8155 "gen/ragel/18__alt4_8.c"
		
		{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d5 = p; }
		
#line 8161 "gen/ragel/18__alt4_8.c"
		
		goto _st13;
		_st13:
		p+= 1;
		st_case_13:
		if ( p == pe )
			goto _out13;
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
		goto _st0;
		_ctr15:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8204 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 8210 "gen/ragel/18__alt4_8.c"
		
		goto _st14;
		_ctr103:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8218 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 8224 "gen/ragel/18__alt4_8.c"
		
		goto _st14;
		_ctr121:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8232 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 8238 "gen/ragel/18__alt4_8.c"
		
		goto _st14;
		_ctr140:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8246 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 8252 "gen/ragel/18__alt4_8.c"
		
		goto _st14;
		_ctr149:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 8260 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 8266 "gen/ragel/18__alt4_8.c"
		
		goto _st14;
		_ctr158:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 8274 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 8280 "gen/ragel/18__alt4_8.c"
		
		goto _st14;
		_ctr175:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8288 "gen/ragel/18__alt4_8.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e5 = p; }
		
#line 8294 "gen/ragel/18__alt4_8.c"
		
		goto _st14;
		_st14:
		p+= 1;
		st_case_14:
		if ( p == pe )
			goto _out14;
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
		goto _st0;
		_ctr16:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8337 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 8343 "gen/ragel/18__alt4_8.c"
		
		goto _st15;
		_ctr104:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8351 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 8357 "gen/ragel/18__alt4_8.c"
		
		goto _st15;
		_ctr122:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8365 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 8371 "gen/ragel/18__alt4_8.c"
		
		goto _st15;
		_ctr131:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8379 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 8385 "gen/ragel/18__alt4_8.c"
		
		goto _st15;
		_ctr150:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 8393 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 8399 "gen/ragel/18__alt4_8.c"
		
		goto _st15;
		_ctr159:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 8407 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 8413 "gen/ragel/18__alt4_8.c"
		
		goto _st15;
		_ctr176:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8421 "gen/ragel/18__alt4_8.c"
		
		{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f5 = p; }
		
#line 8427 "gen/ragel/18__alt4_8.c"
		
		goto _st15;
		_st15:
		p+= 1;
		st_case_15:
		if ( p == pe )
			goto _out15;
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
		goto _st0;
		_ctr17:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8470 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 8476 "gen/ragel/18__alt4_8.c"
		
		goto _st16;
		_ctr105:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8484 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 8490 "gen/ragel/18__alt4_8.c"
		
		goto _st16;
		_ctr123:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8498 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 8504 "gen/ragel/18__alt4_8.c"
		
		goto _st16;
		_ctr132:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8512 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 8518 "gen/ragel/18__alt4_8.c"
		
		goto _st16;
		_ctr141:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8526 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 8532 "gen/ragel/18__alt4_8.c"
		
		goto _st16;
		_ctr160:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 8540 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 8546 "gen/ragel/18__alt4_8.c"
		
		goto _st16;
		_ctr177:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8554 "gen/ragel/18__alt4_8.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g5 = p; }
		
#line 8560 "gen/ragel/18__alt4_8.c"
		
		goto _st16;
		_st16:
		p+= 1;
		st_case_16:
		if ( p == pe )
			goto _out16;
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
		goto _st0;
		_ctr18:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8603 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 8609 "gen/ragel/18__alt4_8.c"
		
		goto _st17;
		_ctr106:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8617 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 8623 "gen/ragel/18__alt4_8.c"
		
		goto _st17;
		_ctr124:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8631 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 8637 "gen/ragel/18__alt4_8.c"
		
		goto _st17;
		_ctr133:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8645 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 8651 "gen/ragel/18__alt4_8.c"
		
		goto _st17;
		_ctr142:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8659 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 8665 "gen/ragel/18__alt4_8.c"
		
		goto _st17;
		_ctr151:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 8673 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 8679 "gen/ragel/18__alt4_8.c"
		
		goto _st17;
		_ctr178:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8687 "gen/ragel/18__alt4_8.c"
		
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h5 = p; }
		
#line 8693 "gen/ragel/18__alt4_8.c"
		
		goto _st17;
		_st17:
		p+= 1;
		st_case_17:
		if ( p == pe )
			goto _out17;
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
		goto _st0;
		_ctr4:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 8736 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 8742 "gen/ragel/18__alt4_8.c"
		
		goto _st18;
		_ctr164:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 8750 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 8756 "gen/ragel/18__alt4_8.c"
		
		goto _st18;
		_ctr192:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 8764 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 8770 "gen/ragel/18__alt4_8.c"
		
		goto _st18;
		_ctr201:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 8778 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 8784 "gen/ragel/18__alt4_8.c"
		
		goto _st18;
		_ctr210:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 8792 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 8798 "gen/ragel/18__alt4_8.c"
		
		goto _st18;
		_ctr219:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 8806 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 8812 "gen/ragel/18__alt4_8.c"
		
		goto _st18;
		_ctr228:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 8820 "gen/ragel/18__alt4_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c3 = p; }
		
#line 8826 "gen/ragel/18__alt4_8.c"
		
		goto _st18;
		_st18:
		p+= 1;
		st_case_18:
		if ( p == pe )
			goto _out18;
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
		goto _st0;
		_ctr101:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8869 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 8875 "gen/ragel/18__alt4_8.c"
		
		goto _st19;
		_ctr119:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8883 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 8889 "gen/ragel/18__alt4_8.c"
		
		goto _st19;
		_ctr128:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8897 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 8903 "gen/ragel/18__alt4_8.c"
		
		goto _st19;
		_ctr137:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8911 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 8917 "gen/ragel/18__alt4_8.c"
		
		goto _st19;
		_ctr146:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 8925 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 8931 "gen/ragel/18__alt4_8.c"
		
		goto _st19;
		_ctr155:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 8939 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 8945 "gen/ragel/18__alt4_8.c"
		
		goto _st19;
		_ctr172:
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 8953 "gen/ragel/18__alt4_8.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b5 = p; }
		
#line 8959 "gen/ragel/18__alt4_8.c"
		
		goto _st19;
		_st19:
		p+= 1;
		st_case_19:
		if ( p == pe )
			goto _out19;
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
		goto _st0;
		_ctr5:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9002 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 9008 "gen/ragel/18__alt4_8.c"
		
		goto _st20;
		_ctr165:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9016 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 9022 "gen/ragel/18__alt4_8.c"
		
		goto _st20;
		_ctr183:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9030 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 9036 "gen/ragel/18__alt4_8.c"
		
		goto _st20;
		_ctr202:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9044 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 9050 "gen/ragel/18__alt4_8.c"
		
		goto _st20;
		_ctr211:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9058 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 9064 "gen/ragel/18__alt4_8.c"
		
		goto _st20;
		_ctr220:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 9072 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 9078 "gen/ragel/18__alt4_8.c"
		
		goto _st20;
		_ctr229:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 9086 "gen/ragel/18__alt4_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d3 = p; }
		
#line 9092 "gen/ragel/18__alt4_8.c"
		
		goto _st20;
		_st20:
		p+= 1;
		st_case_20:
		if ( p == pe )
			goto _out20;
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
		goto _st0;
		_ctr6:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9135 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 9141 "gen/ragel/18__alt4_8.c"
		
		goto _st21;
		_ctr166:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9149 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 9155 "gen/ragel/18__alt4_8.c"
		
		goto _st21;
		_ctr184:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9163 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 9169 "gen/ragel/18__alt4_8.c"
		
		goto _st21;
		_ctr193:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9177 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 9183 "gen/ragel/18__alt4_8.c"
		
		goto _st21;
		_ctr212:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9191 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 9197 "gen/ragel/18__alt4_8.c"
		
		goto _st21;
		_ctr221:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 9205 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 9211 "gen/ragel/18__alt4_8.c"
		
		goto _st21;
		_ctr230:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 9219 "gen/ragel/18__alt4_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e3 = p; }
		
#line 9225 "gen/ragel/18__alt4_8.c"
		
		goto _st21;
		_st21:
		p+= 1;
		st_case_21:
		if ( p == pe )
			goto _out21;
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
		goto _st0;
		_ctr7:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9268 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 9274 "gen/ragel/18__alt4_8.c"
		
		goto _st22;
		_ctr167:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9282 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 9288 "gen/ragel/18__alt4_8.c"
		
		goto _st22;
		_ctr185:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9296 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 9302 "gen/ragel/18__alt4_8.c"
		
		goto _st22;
		_ctr194:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9310 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 9316 "gen/ragel/18__alt4_8.c"
		
		goto _st22;
		_ctr203:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9324 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 9330 "gen/ragel/18__alt4_8.c"
		
		goto _st22;
		_ctr222:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 9338 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 9344 "gen/ragel/18__alt4_8.c"
		
		goto _st22;
		_ctr231:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 9352 "gen/ragel/18__alt4_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f3 = p; }
		
#line 9358 "gen/ragel/18__alt4_8.c"
		
		goto _st22;
		_st22:
		p+= 1;
		st_case_22:
		if ( p == pe )
			goto _out22;
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
		goto _st0;
		_ctr8:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9401 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 9407 "gen/ragel/18__alt4_8.c"
		
		goto _st23;
		_ctr168:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9415 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 9421 "gen/ragel/18__alt4_8.c"
		
		goto _st23;
		_ctr186:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9429 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 9435 "gen/ragel/18__alt4_8.c"
		
		goto _st23;
		_ctr195:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9443 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 9449 "gen/ragel/18__alt4_8.c"
		
		goto _st23;
		_ctr204:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9457 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 9463 "gen/ragel/18__alt4_8.c"
		
		goto _st23;
		_ctr213:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9471 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 9477 "gen/ragel/18__alt4_8.c"
		
		goto _st23;
		_ctr232:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 9485 "gen/ragel/18__alt4_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g3 = p; }
		
#line 9491 "gen/ragel/18__alt4_8.c"
		
		goto _st23;
		_st23:
		p+= 1;
		st_case_23:
		if ( p == pe )
			goto _out23;
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
		goto _st0;
		_ctr9:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9534 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 9540 "gen/ragel/18__alt4_8.c"
		
		goto _st24;
		_ctr169:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9548 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 9554 "gen/ragel/18__alt4_8.c"
		
		goto _st24;
		_ctr187:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9562 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 9568 "gen/ragel/18__alt4_8.c"
		
		goto _st24;
		_ctr196:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9576 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 9582 "gen/ragel/18__alt4_8.c"
		
		goto _st24;
		_ctr205:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9590 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 9596 "gen/ragel/18__alt4_8.c"
		
		goto _st24;
		_ctr214:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9604 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 9610 "gen/ragel/18__alt4_8.c"
		
		goto _st24;
		_ctr223:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 9618 "gen/ragel/18__alt4_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h3 = p; }
		
#line 9624 "gen/ragel/18__alt4_8.c"
		
		goto _st24;
		_st24:
		p+= 1;
		st_case_24:
		if ( p == pe )
			goto _out24;
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
		goto _st0;
		_ctr236:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b1 = p; }
		
#line 9667 "gen/ragel/18__alt4_8.c"
		
		goto _st25;
		_st25:
		p+= 1;
		st_case_25:
		if ( p == pe )
			goto _out25;
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
		goto _st0;
		_ctr163:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9710 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 9716 "gen/ragel/18__alt4_8.c"
		
		goto _st26;
		_ctr181:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9724 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 9730 "gen/ragel/18__alt4_8.c"
		
		goto _st26;
		_ctr190:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9738 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 9744 "gen/ragel/18__alt4_8.c"
		
		goto _st26;
		_ctr199:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9752 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 9758 "gen/ragel/18__alt4_8.c"
		
		goto _st26;
		_ctr208:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 9766 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 9772 "gen/ragel/18__alt4_8.c"
		
		goto _st26;
		_ctr217:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 9780 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 9786 "gen/ragel/18__alt4_8.c"
		
		goto _st26;
		_ctr226:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 9794 "gen/ragel/18__alt4_8.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			a3 = p; }
		
#line 9800 "gen/ragel/18__alt4_8.c"
		
		goto _st26;
		_st26:
		p+= 1;
		st_case_26:
		if ( p == pe )
			goto _out26;
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
		goto _st0;
		_ctr237:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			c1 = p; }
		
#line 9843 "gen/ragel/18__alt4_8.c"
		
		goto _st27;
		_st27:
		p+= 1;
		st_case_27:
		if ( p == pe )
			goto _out27;
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
		goto _st0;
		_ctr238:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			d1 = p; }
		
#line 9886 "gen/ragel/18__alt4_8.c"
		
		goto _st28;
		_st28:
		p+= 1;
		st_case_28:
		if ( p == pe )
			goto _out28;
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
		goto _st0;
		_ctr239:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			e1 = p; }
		
#line 9929 "gen/ragel/18__alt4_8.c"
		
		goto _st29;
		_st29:
		p+= 1;
		st_case_29:
		if ( p == pe )
			goto _out29;
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
		goto _st0;
		_ctr240:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			f1 = p; }
		
#line 9972 "gen/ragel/18__alt4_8.c"
		
		goto _st30;
		_st30:
		p+= 1;
		st_case_30:
		if ( p == pe )
			goto _out30;
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
		goto _st0;
		_ctr241:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			g1 = p; }
		
#line 10015 "gen/ragel/18__alt4_8.c"
		
		goto _st31;
		_st31:
		p+= 1;
		st_case_31:
		if ( p == pe )
			goto _out31;
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
		goto _st0;
		_ctr242:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
			h1 = p; }
		
#line 10058 "gen/ragel/18__alt4_8.c"
		
		goto _st32;
		_st32:
		p+= 1;
		st_case_32:
		if ( p == pe )
			goto _out32;
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
		goto _st0;
		_out33: cs = 33; goto _out; 
		_out0: cs = 0; goto _out; 
		_out1: cs = 1; goto _out; 
		_out2: cs = 2; goto _out; 
		_out3: cs = 3; goto _out; 
		_out4: cs = 4; goto _out; 
		_out5: cs = 5; goto _out; 
		_out6: cs = 6; goto _out; 
		_out7: cs = 7; goto _out; 
		_out8: cs = 8; goto _out; 
		_out9: cs = 9; goto _out; 
		_out10: cs = 10; goto _out; 
		_out11: cs = 11; goto _out; 
		_out12: cs = 12; goto _out; 
		_out13: cs = 13; goto _out; 
		_out14: cs = 14; goto _out; 
		_out15: cs = 15; goto _out; 
		_out16: cs = 16; goto _out; 
		_out17: cs = 17; goto _out; 
		_out18: cs = 18; goto _out; 
		_out19: cs = 19; goto _out; 
		_out20: cs = 20; goto _out; 
		_out21: cs = 21; goto _out; 
		_out22: cs = 22; goto _out; 
		_out23: cs = 23; goto _out; 
		_out24: cs = 24; goto _out; 
		_out25: cs = 25; goto _out; 
		_out26: cs = 26; goto _out; 
		_out27: cs = 27; goto _out; 
		_out28: cs = 28; goto _out; 
		_out29: cs = 29; goto _out; 
		_out30: cs = 30; goto _out; 
		_out31: cs = 31; goto _out; 
		_out32: cs = 32; goto _out; 
		_out: {}
	}
	
#line 116 "../../../benchmarks/submatch_dfa_aot/src/ragel/18__alt4_8.rl"
	
	
	in->p = p;
	in->pe = pe;
}
