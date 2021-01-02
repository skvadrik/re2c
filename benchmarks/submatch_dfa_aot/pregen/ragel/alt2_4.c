#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"



#line 13 "gen/ragel/alt2_4.c"
static const int m_start = 9;
static const int m_first_final = 9;
static const int m_error = 0;

static const int m_en_main = 9;


#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1, *c1, *d1,
	*a2, *b2, *c2, *d2,
	*a3, *b3, *c3, *d3,
	*a4, *b4, *c4, *d4;
	int cs;
	
	
#line 36 "gen/ragel/alt2_4.c"
	{
		cs = (int)m_start;
	}
	
#line 58 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
	
	
#line 44 "gen/ragel/alt2_4.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 9:
			goto st_case_9;
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
		}
		goto st_out;
		_ctr2:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 76 "gen/ragel/alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b3 = p; }
		
#line 82 "gen/ragel/alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 88 "gen/ragel/alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c3 = p; }
		
#line 94 "gen/ragel/alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 100 "gen/ragel/alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d3 = p; }
		
#line 106 "gen/ragel/alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 112 "gen/ragel/alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a3 = p; }
		
#line 118 "gen/ragel/alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 124 "gen/ragel/alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 140 "gen/ragel/alt2_4.c"
		
		goto _st9;
		_ctr7:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 148 "gen/ragel/alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 164 "gen/ragel/alt2_4.c"
		
		goto _st9;
		_ctr9:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 172 "gen/ragel/alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 188 "gen/ragel/alt2_4.c"
		
		goto _st9;
		_ctr11:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 196 "gen/ragel/alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 212 "gen/ragel/alt2_4.c"
		
		goto _st9;
		_ctr13:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 220 "gen/ragel/alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b3 = p; }
		
#line 226 "gen/ragel/alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 232 "gen/ragel/alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c3 = p; }
		
#line 238 "gen/ragel/alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 244 "gen/ragel/alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d3 = p; }
		
#line 250 "gen/ragel/alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 256 "gen/ragel/alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a3 = p; }
		
#line 262 "gen/ragel/alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 268 "gen/ragel/alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 284 "gen/ragel/alt2_4.c"
		
		goto _st9;
		_ctr18:
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 292 "gen/ragel/alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 308 "gen/ragel/alt2_4.c"
		
		goto _st9;
		_ctr20:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 316 "gen/ragel/alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b3 = p; }
		
#line 322 "gen/ragel/alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 328 "gen/ragel/alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c3 = p; }
		
#line 334 "gen/ragel/alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 340 "gen/ragel/alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d3 = p; }
		
#line 346 "gen/ragel/alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 352 "gen/ragel/alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a3 = p; }
		
#line 358 "gen/ragel/alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 364 "gen/ragel/alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 380 "gen/ragel/alt2_4.c"
		
		goto _st9;
		_ctr25:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 388 "gen/ragel/alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b3 = p; }
		
#line 394 "gen/ragel/alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 400 "gen/ragel/alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c3 = p; }
		
#line 406 "gen/ragel/alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 412 "gen/ragel/alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d3 = p; }
		
#line 418 "gen/ragel/alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 424 "gen/ragel/alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a3 = p; }
		
#line 430 "gen/ragel/alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 436 "gen/ragel/alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 452 "gen/ragel/alt2_4.c"
		
		goto _st9;
		_ctr30:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b1 = p; }
		
#line 460 "gen/ragel/alt2_4.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 466 "gen/ragel/alt2_4.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c1 = p; }
		
#line 472 "gen/ragel/alt2_4.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 478 "gen/ragel/alt2_4.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d1 = p; }
		
#line 484 "gen/ragel/alt2_4.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 490 "gen/ragel/alt2_4.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a1 = p; }
		
#line 496 "gen/ragel/alt2_4.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 502 "gen/ragel/alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b3 = p; }
		
#line 508 "gen/ragel/alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 514 "gen/ragel/alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c3 = p; }
		
#line 520 "gen/ragel/alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 526 "gen/ragel/alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d3 = p; }
		
#line 532 "gen/ragel/alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 538 "gen/ragel/alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a3 = p; }
		
#line 544 "gen/ragel/alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 550 "gen/ragel/alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 566 "gen/ragel/alt2_4.c"
		
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
				goto _ctr34;
			}
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr31:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a1 = p; }
		
#line 603 "gen/ragel/alt2_4.c"
		
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
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 636 "gen/ragel/alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b3 = p; }
		
#line 642 "gen/ragel/alt2_4.c"
		
		goto _st2;
		_ctr22:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 650 "gen/ragel/alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b3 = p; }
		
#line 656 "gen/ragel/alt2_4.c"
		
		goto _st2;
		_ctr27:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 664 "gen/ragel/alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b3 = p; }
		
#line 670 "gen/ragel/alt2_4.c"
		
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
			case 98: {
				goto _st2;
			}
		}
		{
			goto _st0;
		}
		_ctr4:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 694 "gen/ragel/alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c3 = p; }
		
#line 700 "gen/ragel/alt2_4.c"
		
		goto _st3;
		_ctr15:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 708 "gen/ragel/alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c3 = p; }
		
#line 714 "gen/ragel/alt2_4.c"
		
		goto _st3;
		_ctr28:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 722 "gen/ragel/alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c3 = p; }
		
#line 728 "gen/ragel/alt2_4.c"
		
		goto _st3;
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr9;
			}
			case 99: {
				goto _st3;
			}
		}
		{
			goto _st0;
		}
		_ctr5:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 752 "gen/ragel/alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d3 = p; }
		
#line 758 "gen/ragel/alt2_4.c"
		
		goto _st4;
		_ctr16:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 766 "gen/ragel/alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d3 = p; }
		
#line 772 "gen/ragel/alt2_4.c"
		
		goto _st4;
		_ctr23:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 780 "gen/ragel/alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d3 = p; }
		
#line 786 "gen/ragel/alt2_4.c"
		
		goto _st4;
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr11;
			}
			case 100: {
				goto _st4;
			}
		}
		{
			goto _st0;
		}
		_ctr32:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b1 = p; }
		
#line 810 "gen/ragel/alt2_4.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr13;
			}
			case 97: {
				goto _ctr14;
			}
			case 98: {
				goto _st5;
			}
			case 99: {
				goto _ctr15;
			}
			case 100: {
				goto _ctr16;
			}
		}
		{
			goto _st0;
		}
		_ctr14:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 843 "gen/ragel/alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a3 = p; }
		
#line 849 "gen/ragel/alt2_4.c"
		
		goto _st6;
		_ctr21:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 857 "gen/ragel/alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a3 = p; }
		
#line 863 "gen/ragel/alt2_4.c"
		
		goto _st6;
		_ctr26:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 871 "gen/ragel/alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			a3 = p; }
		
#line 877 "gen/ragel/alt2_4.c"
		
		goto _st6;
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr18;
			}
			case 97: {
				goto _st6;
			}
		}
		{
			goto _st0;
		}
		_ctr33:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			c1 = p; }
		
#line 901 "gen/ragel/alt2_4.c"
		
		goto _st7;
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr20;
			}
			case 97: {
				goto _ctr21;
			}
			case 98: {
				goto _ctr22;
			}
			case 99: {
				goto _st7;
			}
			case 100: {
				goto _ctr23;
			}
		}
		{
			goto _st0;
		}
		_ctr34:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
			d1 = p; }
		
#line 934 "gen/ragel/alt2_4.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr25;
			}
			case 97: {
				goto _ctr26;
			}
			case 98: {
				goto _ctr27;
			}
			case 99: {
				goto _ctr28;
			}
			case 100: {
				goto _st8;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof9: cs = 9; goto _test_eof; 
		_test_eof1: cs = 1; goto _test_eof; 
		_test_eof2: cs = 2; goto _test_eof; 
		_test_eof3: cs = 3; goto _test_eof; 
		_test_eof4: cs = 4; goto _test_eof; 
		_test_eof5: cs = 5; goto _test_eof; 
		_test_eof6: cs = 6; goto _test_eof; 
		_test_eof7: cs = 7; goto _test_eof; 
		_test_eof8: cs = 8; goto _test_eof; 
		
		_test_eof: {}
		if ( cs >= 9 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
