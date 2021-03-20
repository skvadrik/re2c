#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 64 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"



#line 13 "gen/ragel/17__alt4_4.c"
static const int m_start = 17;
static const int m_first_final = 17;
static const int m_error = 0;

static const int m_en_main = 17;


#line 66 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1, *c1, *d1,
	*a2, *b2, *c2, *d2,
	*a3, *b3, *c3, *d3,
	*a4, *b4, *c4, *d4,
	*a5, *b5, *c5, *d5,
	*a6, *b6, *c6, *d6,
	*a7, *b7, *c7, *d7,
	*a8, *b8, *c8, *d8;
	int cs;
	
	
#line 40 "gen/ragel/17__alt4_4.c"
	{
		cs = (int)m_start;
	}
	
#line 83 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
	
	
#line 48 "gen/ragel/17__alt4_4.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 17:
			goto st_case_17;
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
		}
		goto st_out;
		_ctr2:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 96 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 102 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 108 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 114 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 120 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 126 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 132 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 138 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 144 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 150 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 156 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 162 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 168 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 174 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 180 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 186 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 192 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 198 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 204 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 210 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 216 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 222 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 228 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 234 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 240 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 264 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr7:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 272 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 278 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 284 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 290 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 296 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 302 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 308 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 314 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 320 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 326 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 332 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 338 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 344 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 350 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 356 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 362 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 368 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 392 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr12:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 400 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 406 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 412 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 418 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 424 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 430 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 436 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 442 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 448 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 472 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr17:
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 480 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 504 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr19:
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 512 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 536 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr21:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 544 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 568 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr23:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 576 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 582 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 588 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 594 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 600 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 606 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 612 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 618 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 624 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 648 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr28:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 656 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 680 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr30:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 688 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 694 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 700 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 706 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 712 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 718 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 724 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 730 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 736 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 760 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr35:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 768 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 774 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 780 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 786 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 792 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 798 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 804 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 810 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 816 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 822 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 828 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 834 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 840 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 846 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 852 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 858 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 864 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 888 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr40:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 896 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 902 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 908 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 914 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 920 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 926 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 932 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 938 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 944 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 968 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr45:
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 976 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 982 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 988 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 994 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 1000 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 1006 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 1012 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 1018 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1024 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 1030 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1036 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 1042 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 1048 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 1054 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 1060 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 1066 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1072 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 1096 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr50:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 1104 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 1110 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1116 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 1122 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 1128 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 1134 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 1140 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 1146 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1152 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 1158 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1164 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 1170 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 1176 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 1182 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 1188 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 1194 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1200 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 1206 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1212 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 1218 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 1224 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 1230 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 1236 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 1242 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1248 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 1272 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr55:
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1280 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 1286 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1292 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 1298 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 1304 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 1310 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 1316 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 1322 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1328 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 1334 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1340 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 1346 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 1352 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 1358 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 1364 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 1370 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1376 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 1400 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr60:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 1408 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 1414 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1420 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 1426 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 1432 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 1438 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 1444 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 1450 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1456 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 1462 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1468 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 1474 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 1480 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 1486 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 1492 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 1498 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1504 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 1510 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1516 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 1522 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 1528 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 1534 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 1540 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 1546 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1552 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 1576 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr65:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 1584 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 1590 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1596 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 1602 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 1608 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 1614 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 1620 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 1626 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1632 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 1638 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1644 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 1650 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 1656 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 1662 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 1668 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 1674 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1680 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 1686 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1692 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 1698 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 1704 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 1710 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 1716 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 1722 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1728 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 1752 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr70:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b1 = p; }
		
#line 1760 "gen/ragel/17__alt4_4.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 1766 "gen/ragel/17__alt4_4.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c1 = p; }
		
#line 1772 "gen/ragel/17__alt4_4.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 1778 "gen/ragel/17__alt4_4.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d1 = p; }
		
#line 1784 "gen/ragel/17__alt4_4.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 1790 "gen/ragel/17__alt4_4.c"
		
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a1 = p; }
		
#line 1796 "gen/ragel/17__alt4_4.c"
		
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 1802 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 1808 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1814 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 1820 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 1826 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 1832 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 1838 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 1844 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1850 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 1856 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1862 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 1868 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 1874 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 1880 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 1886 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 1892 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1898 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 1904 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1910 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 1916 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 1922 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 1928 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 1934 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 1940 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1946 "gen/ragel/17__alt4_4.c"
		
		{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
			else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
			else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
			outc(out, '\n');
		}
		
#line 1970 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_st17:
		p+= 1;
		if ( p == pe )
			goto _test_eof17;
		st_case_17:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr70;
			}
			case 97: {
				goto _ctr71;
			}
			case 98: {
				goto _ctr72;
			}
			case 99: {
				goto _ctr73;
			}
			case 100: {
				goto _ctr74;
			}
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr71:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a1 = p; }
		
#line 2007 "gen/ragel/17__alt4_4.c"
		
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
		}
		{
			goto _st0;
		}
		_ctr3:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 2040 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 2046 "gen/ragel/17__alt4_4.c"
		
		goto _st2;
		_ctr62:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 2054 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 2060 "gen/ragel/17__alt4_4.c"
		
		goto _st2;
		_ctr67:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 2068 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 2074 "gen/ragel/17__alt4_4.c"
		
		goto _st2;
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr7;
			}
			case 97: {
				goto _ctr8;
			}
			case 98: {
				goto _st2;
			}
			case 99: {
				goto _ctr9;
			}
			case 100: {
				goto _ctr10;
			}
		}
		{
			goto _st0;
		}
		_ctr8:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 2107 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 2113 "gen/ragel/17__alt4_4.c"
		
		goto _st3;
		_ctr36:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 2121 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 2127 "gen/ragel/17__alt4_4.c"
		
		goto _st3;
		_ctr46:
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 2135 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 2141 "gen/ragel/17__alt4_4.c"
		
		goto _st3;
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr12;
			}
			case 97: {
				goto _st3;
			}
			case 98: {
				goto _ctr13;
			}
			case 99: {
				goto _ctr14;
			}
			case 100: {
				goto _ctr15;
			}
		}
		{
			goto _st0;
		}
		_ctr13:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 2174 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 2180 "gen/ragel/17__alt4_4.c"
		
		goto _st4;
		_ctr25:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 2188 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 2194 "gen/ragel/17__alt4_4.c"
		
		goto _st4;
		_ctr32:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 2202 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 2208 "gen/ragel/17__alt4_4.c"
		
		goto _st4;
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr17;
			}
			case 98: {
				goto _st4;
			}
		}
		{
			goto _st0;
		}
		_ctr14:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 2232 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 2238 "gen/ragel/17__alt4_4.c"
		
		goto _st5;
		_ctr33:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 2246 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 2252 "gen/ragel/17__alt4_4.c"
		
		goto _st5;
		_ctr42:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 2260 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 2266 "gen/ragel/17__alt4_4.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr19;
			}
			case 99: {
				goto _st5;
			}
		}
		{
			goto _st0;
		}
		_ctr15:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 2290 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 2296 "gen/ragel/17__alt4_4.c"
		
		goto _st6;
		_ctr26:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 2304 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 2310 "gen/ragel/17__alt4_4.c"
		
		goto _st6;
		_ctr43:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 2318 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 2324 "gen/ragel/17__alt4_4.c"
		
		goto _st6;
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr21;
			}
			case 100: {
				goto _st6;
			}
		}
		{
			goto _st0;
		}
		_ctr9:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 2348 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 2354 "gen/ragel/17__alt4_4.c"
		
		goto _st7;
		_ctr48:
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 2362 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 2368 "gen/ragel/17__alt4_4.c"
		
		goto _st7;
		_ctr57:
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 2376 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 2382 "gen/ragel/17__alt4_4.c"
		
		goto _st7;
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 97: {
				goto _ctr24;
			}
			case 98: {
				goto _ctr25;
			}
			case 99: {
				goto _st7;
			}
			case 100: {
				goto _ctr26;
			}
		}
		{
			goto _st0;
		}
		_ctr24:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 2415 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 2421 "gen/ragel/17__alt4_4.c"
		
		goto _st8;
		_ctr31:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 2429 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 2435 "gen/ragel/17__alt4_4.c"
		
		goto _st8;
		_ctr41:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 2443 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 2449 "gen/ragel/17__alt4_4.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr28;
			}
			case 97: {
				goto _st8;
			}
		}
		{
			goto _st0;
		}
		_ctr10:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 2473 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 2479 "gen/ragel/17__alt4_4.c"
		
		goto _st9;
		_ctr38:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 2487 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 2493 "gen/ragel/17__alt4_4.c"
		
		goto _st9;
		_ctr58:
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 2501 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 2507 "gen/ragel/17__alt4_4.c"
		
		goto _st9;
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr30;
			}
			case 97: {
				goto _ctr31;
			}
			case 98: {
				goto _ctr32;
			}
			case 99: {
				goto _ctr33;
			}
			case 100: {
				goto _st9;
			}
		}
		{
			goto _st0;
		}
		_ctr4:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 2540 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 2546 "gen/ragel/17__alt4_4.c"
		
		goto _st10;
		_ctr52:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 2554 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 2560 "gen/ragel/17__alt4_4.c"
		
		goto _st10;
		_ctr68:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 2568 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 2574 "gen/ragel/17__alt4_4.c"
		
		goto _st10;
		_st10:
		p+= 1;
		if ( p == pe )
			goto _test_eof10;
		st_case_10:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr35;
			}
			case 97: {
				goto _ctr36;
			}
			case 98: {
				goto _ctr37;
			}
			case 99: {
				goto _st10;
			}
			case 100: {
				goto _ctr38;
			}
		}
		{
			goto _st0;
		}
		_ctr37:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 2607 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 2613 "gen/ragel/17__alt4_4.c"
		
		goto _st11;
		_ctr47:
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 2621 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 2627 "gen/ragel/17__alt4_4.c"
		
		goto _st11;
		_ctr56:
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 2635 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 2641 "gen/ragel/17__alt4_4.c"
		
		goto _st11;
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr40;
			}
			case 97: {
				goto _ctr41;
			}
			case 98: {
				goto _st11;
			}
			case 99: {
				goto _ctr42;
			}
			case 100: {
				goto _ctr43;
			}
		}
		{
			goto _st0;
		}
		_ctr5:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 2674 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 2680 "gen/ragel/17__alt4_4.c"
		
		goto _st12;
		_ctr53:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 2688 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 2694 "gen/ragel/17__alt4_4.c"
		
		goto _st12;
		_ctr63:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 2702 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 2708 "gen/ragel/17__alt4_4.c"
		
		goto _st12;
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr45;
			}
			case 97: {
				goto _ctr46;
			}
			case 98: {
				goto _ctr47;
			}
			case 99: {
				goto _ctr48;
			}
			case 100: {
				goto _st12;
			}
		}
		{
			goto _st0;
		}
		_ctr72:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b1 = p; }
		
#line 2741 "gen/ragel/17__alt4_4.c"
		
		goto _st13;
		_st13:
		p+= 1;
		if ( p == pe )
			goto _test_eof13;
		st_case_13:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr50;
			}
			case 97: {
				goto _ctr51;
			}
			case 98: {
				goto _st13;
			}
			case 99: {
				goto _ctr52;
			}
			case 100: {
				goto _ctr53;
			}
		}
		{
			goto _st0;
		}
		_ctr51:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 2774 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 2780 "gen/ragel/17__alt4_4.c"
		
		goto _st14;
		_ctr61:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 2788 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 2794 "gen/ragel/17__alt4_4.c"
		
		goto _st14;
		_ctr66:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 2802 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 2808 "gen/ragel/17__alt4_4.c"
		
		goto _st14;
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr55;
			}
			case 97: {
				goto _st14;
			}
			case 98: {
				goto _ctr56;
			}
			case 99: {
				goto _ctr57;
			}
			case 100: {
				goto _ctr58;
			}
		}
		{
			goto _st0;
		}
		_ctr73:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c1 = p; }
		
#line 2841 "gen/ragel/17__alt4_4.c"
		
		goto _st15;
		_st15:
		p+= 1;
		if ( p == pe )
			goto _test_eof15;
		st_case_15:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr60;
			}
			case 97: {
				goto _ctr61;
			}
			case 98: {
				goto _ctr62;
			}
			case 99: {
				goto _st15;
			}
			case 100: {
				goto _ctr63;
			}
		}
		{
			goto _st0;
		}
		_ctr74:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d1 = p; }
		
#line 2874 "gen/ragel/17__alt4_4.c"
		
		goto _st16;
		_st16:
		p+= 1;
		if ( p == pe )
			goto _test_eof16;
		st_case_16:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr65;
			}
			case 97: {
				goto _ctr66;
			}
			case 98: {
				goto _ctr67;
			}
			case 99: {
				goto _ctr68;
			}
			case 100: {
				goto _st16;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof17: cs = 17; goto _test_eof; 
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
		
		_test_eof: {}
		if ( cs >= 17 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 84 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
