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
		_ctr2:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 93 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 99 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 105 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 111 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 117 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 123 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 129 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 135 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 141 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 147 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 153 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 159 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 165 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 171 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 177 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 183 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 189 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 195 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 201 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 207 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 213 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 219 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 225 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 231 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 237 "gen/ragel/17__alt4_4.c"
		
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
		
#line 261 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr7:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 269 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 275 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 281 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 287 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 293 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 299 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 305 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 311 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 317 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 323 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 329 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 335 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 341 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 347 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 353 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 359 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 365 "gen/ragel/17__alt4_4.c"
		
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
		
#line 389 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr12:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 397 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 403 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 409 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 415 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 421 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 427 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 433 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 439 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 445 "gen/ragel/17__alt4_4.c"
		
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
		
#line 469 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr17:
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 477 "gen/ragel/17__alt4_4.c"
		
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
		
#line 501 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr19:
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 509 "gen/ragel/17__alt4_4.c"
		
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
		
#line 533 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr21:
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 541 "gen/ragel/17__alt4_4.c"
		
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
		
#line 565 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr23:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 573 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 579 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 585 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 591 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 597 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 603 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 609 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 615 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 621 "gen/ragel/17__alt4_4.c"
		
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
		
#line 645 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr28:
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 653 "gen/ragel/17__alt4_4.c"
		
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
		
#line 677 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr30:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 685 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 691 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 697 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 703 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 709 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 715 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 721 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 727 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 733 "gen/ragel/17__alt4_4.c"
		
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
		
#line 757 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr35:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 765 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 771 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 777 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 783 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 789 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 795 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 801 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 807 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 813 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 819 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 825 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 831 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 837 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 843 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 849 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 855 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 861 "gen/ragel/17__alt4_4.c"
		
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
		
#line 885 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr40:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 893 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 899 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 905 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 911 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 917 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 923 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 929 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 935 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 941 "gen/ragel/17__alt4_4.c"
		
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
		
#line 965 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr45:
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 973 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 979 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 985 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 991 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 997 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 1003 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 1009 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 1015 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1021 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 1027 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1033 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 1039 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 1045 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 1051 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 1057 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 1063 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1069 "gen/ragel/17__alt4_4.c"
		
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
		
#line 1093 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr50:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 1101 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 1107 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1113 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 1119 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 1125 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 1131 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 1137 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 1143 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1149 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 1155 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1161 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 1167 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 1173 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 1179 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 1185 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 1191 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1197 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 1203 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1209 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 1215 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 1221 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 1227 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 1233 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 1239 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1245 "gen/ragel/17__alt4_4.c"
		
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
		
#line 1269 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr55:
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1277 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 1283 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1289 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 1295 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 1301 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 1307 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 1313 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 1319 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1325 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 1331 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1337 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 1343 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 1349 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 1355 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 1361 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 1367 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1373 "gen/ragel/17__alt4_4.c"
		
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
		
#line 1397 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr60:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 1405 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 1411 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1417 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 1423 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 1429 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 1435 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 1441 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 1447 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1453 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 1459 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1465 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 1471 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 1477 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 1483 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 1489 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 1495 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1501 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 1507 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1513 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 1519 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 1525 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 1531 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 1537 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 1543 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1549 "gen/ragel/17__alt4_4.c"
		
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
		
#line 1573 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr65:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 1581 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 1587 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1593 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 1599 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 1605 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 1611 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 1617 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 1623 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1629 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 1635 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1641 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 1647 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 1653 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 1659 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 1665 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 1671 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1677 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 1683 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1689 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 1695 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 1701 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 1707 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 1713 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 1719 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1725 "gen/ragel/17__alt4_4.c"
		
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
		
#line 1749 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_ctr70:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b1 = p; }
		
#line 1757 "gen/ragel/17__alt4_4.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 1763 "gen/ragel/17__alt4_4.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c1 = p; }
		
#line 1769 "gen/ragel/17__alt4_4.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 1775 "gen/ragel/17__alt4_4.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d1 = p; }
		
#line 1781 "gen/ragel/17__alt4_4.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 1787 "gen/ragel/17__alt4_4.c"
		
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a1 = p; }
		
#line 1793 "gen/ragel/17__alt4_4.c"
		
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 1799 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 1805 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1811 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 1817 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 1823 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 1829 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 1835 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 1841 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 1847 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 1853 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1859 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 1865 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 1871 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 1877 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 1883 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 1889 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 1895 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 1901 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1907 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 1913 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
		
#line 1919 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 1925 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
		
#line 1931 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 1937 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
		
#line 1943 "gen/ragel/17__alt4_4.c"
		
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
		
#line 1967 "gen/ragel/17__alt4_4.c"
		
		goto _st17;
		_st17:
		p+= 1;
		st_case_17:
		if ( p == pe )
			goto _out17;
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
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr71:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a1 = p; }
		
#line 2001 "gen/ragel/17__alt4_4.c"
		
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
		}
		goto _st0;
		_ctr3:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 2032 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 2038 "gen/ragel/17__alt4_4.c"
		
		goto _st2;
		_ctr62:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 2046 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 2052 "gen/ragel/17__alt4_4.c"
		
		goto _st2;
		_ctr67:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 2060 "gen/ragel/17__alt4_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b3 = p; }
		
#line 2066 "gen/ragel/17__alt4_4.c"
		
		goto _st2;
		_st2:
		p+= 1;
		st_case_2:
		if ( p == pe )
			goto _out2;
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
		goto _st0;
		_ctr8:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 2097 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 2103 "gen/ragel/17__alt4_4.c"
		
		goto _st3;
		_ctr36:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 2111 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 2117 "gen/ragel/17__alt4_4.c"
		
		goto _st3;
		_ctr46:
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 2125 "gen/ragel/17__alt4_4.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a5 = p; }
		
#line 2131 "gen/ragel/17__alt4_4.c"
		
		goto _st3;
		_st3:
		p+= 1;
		st_case_3:
		if ( p == pe )
			goto _out3;
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
		goto _st0;
		_ctr13:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 2162 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 2168 "gen/ragel/17__alt4_4.c"
		
		goto _st4;
		_ctr25:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 2176 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 2182 "gen/ragel/17__alt4_4.c"
		
		goto _st4;
		_ctr32:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 2190 "gen/ragel/17__alt4_4.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b7 = p; }
		
#line 2196 "gen/ragel/17__alt4_4.c"
		
		goto _st4;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr17;
			}
			case 98: {
				goto _st4;
			}
		}
		goto _st0;
		_ctr14:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 2218 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 2224 "gen/ragel/17__alt4_4.c"
		
		goto _st5;
		_ctr33:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 2232 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 2238 "gen/ragel/17__alt4_4.c"
		
		goto _st5;
		_ctr42:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 2246 "gen/ragel/17__alt4_4.c"
		
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c7 = p; }
		
#line 2252 "gen/ragel/17__alt4_4.c"
		
		goto _st5;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr19;
			}
			case 99: {
				goto _st5;
			}
		}
		goto _st0;
		_ctr15:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 2274 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 2280 "gen/ragel/17__alt4_4.c"
		
		goto _st6;
		_ctr26:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 2288 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 2294 "gen/ragel/17__alt4_4.c"
		
		goto _st6;
		_ctr43:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 2302 "gen/ragel/17__alt4_4.c"
		
		{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d7 = p; }
		
#line 2308 "gen/ragel/17__alt4_4.c"
		
		goto _st6;
		_st6:
		p+= 1;
		st_case_6:
		if ( p == pe )
			goto _out6;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr21;
			}
			case 100: {
				goto _st6;
			}
		}
		goto _st0;
		_ctr9:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 2330 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 2336 "gen/ragel/17__alt4_4.c"
		
		goto _st7;
		_ctr48:
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 2344 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 2350 "gen/ragel/17__alt4_4.c"
		
		goto _st7;
		_ctr57:
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 2358 "gen/ragel/17__alt4_4.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c5 = p; }
		
#line 2364 "gen/ragel/17__alt4_4.c"
		
		goto _st7;
		_st7:
		p+= 1;
		st_case_7:
		if ( p == pe )
			goto _out7;
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
		goto _st0;
		_ctr24:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
		
#line 2395 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 2401 "gen/ragel/17__alt4_4.c"
		
		goto _st8;
		_ctr31:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
		
#line 2409 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 2415 "gen/ragel/17__alt4_4.c"
		
		goto _st8;
		_ctr41:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
		
#line 2423 "gen/ragel/17__alt4_4.c"
		
		{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a7 = p; }
		
#line 2429 "gen/ragel/17__alt4_4.c"
		
		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr28;
			}
			case 97: {
				goto _st8;
			}
		}
		goto _st0;
		_ctr10:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 2451 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 2457 "gen/ragel/17__alt4_4.c"
		
		goto _st9;
		_ctr38:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 2465 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 2471 "gen/ragel/17__alt4_4.c"
		
		goto _st9;
		_ctr58:
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 2479 "gen/ragel/17__alt4_4.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d5 = p; }
		
#line 2485 "gen/ragel/17__alt4_4.c"
		
		goto _st9;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
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
		goto _st0;
		_ctr4:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 2516 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 2522 "gen/ragel/17__alt4_4.c"
		
		goto _st10;
		_ctr52:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 2530 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 2536 "gen/ragel/17__alt4_4.c"
		
		goto _st10;
		_ctr68:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 2544 "gen/ragel/17__alt4_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c3 = p; }
		
#line 2550 "gen/ragel/17__alt4_4.c"
		
		goto _st10;
		_st10:
		p+= 1;
		st_case_10:
		if ( p == pe )
			goto _out10;
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
		goto _st0;
		_ctr37:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 2581 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 2587 "gen/ragel/17__alt4_4.c"
		
		goto _st11;
		_ctr47:
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 2595 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 2601 "gen/ragel/17__alt4_4.c"
		
		goto _st11;
		_ctr56:
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 2609 "gen/ragel/17__alt4_4.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b5 = p; }
		
#line 2615 "gen/ragel/17__alt4_4.c"
		
		goto _st11;
		_st11:
		p+= 1;
		st_case_11:
		if ( p == pe )
			goto _out11;
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
		goto _st0;
		_ctr5:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 2646 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 2652 "gen/ragel/17__alt4_4.c"
		
		goto _st12;
		_ctr53:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 2660 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 2666 "gen/ragel/17__alt4_4.c"
		
		goto _st12;
		_ctr63:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 2674 "gen/ragel/17__alt4_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d3 = p; }
		
#line 2680 "gen/ragel/17__alt4_4.c"
		
		goto _st12;
		_st12:
		p+= 1;
		st_case_12:
		if ( p == pe )
			goto _out12;
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
		goto _st0;
		_ctr72:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b1 = p; }
		
#line 2711 "gen/ragel/17__alt4_4.c"
		
		goto _st13;
		_st13:
		p+= 1;
		st_case_13:
		if ( p == pe )
			goto _out13;
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
		goto _st0;
		_ctr51:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 2742 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 2748 "gen/ragel/17__alt4_4.c"
		
		goto _st14;
		_ctr61:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 2756 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 2762 "gen/ragel/17__alt4_4.c"
		
		goto _st14;
		_ctr66:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 2770 "gen/ragel/17__alt4_4.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			a3 = p; }
		
#line 2776 "gen/ragel/17__alt4_4.c"
		
		goto _st14;
		_st14:
		p+= 1;
		st_case_14:
		if ( p == pe )
			goto _out14;
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
		goto _st0;
		_ctr73:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			c1 = p; }
		
#line 2807 "gen/ragel/17__alt4_4.c"
		
		goto _st15;
		_st15:
		p+= 1;
		st_case_15:
		if ( p == pe )
			goto _out15;
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
		goto _st0;
		_ctr74:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
			d1 = p; }
		
#line 2838 "gen/ragel/17__alt4_4.c"
		
		goto _st16;
		_st16:
		p+= 1;
		st_case_16:
		if ( p == pe )
			goto _out16;
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
		goto _st0;
		_out17: cs = 17; goto _out; 
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
		_out: {}
	}
	
#line 84 "../../../benchmarks/submatch_dfa_aot/src/ragel/17__alt4_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
