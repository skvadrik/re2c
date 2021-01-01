#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 48 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"



#line 13 "gen/ragel/alt4_2-G2.c"
static const int m_start = 9;
static const int m_first_final = 9;
static const int m_error = 0;

static const int m_en_main = 9;


#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1,
	*a2, *b2,
	*a3, *b3,
	*a4, *b4,
	*a5, *b5,
	*a6, *b6,
	*a7, *b7,
	*a8, *b8;
	int cs;
	
	
#line 40 "gen/ragel/alt4_2-G2.c"
	{
		cs = (int)m_start;
	}
	
#line 67 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
	
	
#line 48 "gen/ragel/alt4_2-G2.c"
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
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a2 = p; b1 = b2 = NULL; }
		
#line 80 "gen/ragel/alt4_2-G2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b3 = p; }
		
#line 86 "gen/ragel/alt4_2-G2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b4 = p; a3 = a4 = NULL; }
		
#line 92 "gen/ragel/alt4_2-G2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a3 = p; }
		
#line 98 "gen/ragel/alt4_2-G2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a4 = p; b3 = b4 = NULL; }
		
#line 104 "gen/ragel/alt4_2-G2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b5 = p; }
		
#line 110 "gen/ragel/alt4_2-G2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b6 = p; a5 = a6 = NULL; }
		
#line 116 "gen/ragel/alt4_2-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a5 = p; }
		
#line 122 "gen/ragel/alt4_2-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a6 = p; b5 = b6 = NULL; }
		
#line 128 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b7 = p; }
		
#line 134 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 140 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a7 = p; }
		
#line 146 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 152 "gen/ragel/alt4_2-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			outc(out, '\n');
		}
		
#line 168 "gen/ragel/alt4_2-G2.c"
		
		goto _st9;
		_ctr5:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b4 = p; a3 = a4 = NULL; }
		
#line 176 "gen/ragel/alt4_2-G2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b5 = p; }
		
#line 182 "gen/ragel/alt4_2-G2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b6 = p; a5 = a6 = NULL; }
		
#line 188 "gen/ragel/alt4_2-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a5 = p; }
		
#line 194 "gen/ragel/alt4_2-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a6 = p; b5 = b6 = NULL; }
		
#line 200 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b7 = p; }
		
#line 206 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 212 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a7 = p; }
		
#line 218 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 224 "gen/ragel/alt4_2-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			outc(out, '\n');
		}
		
#line 240 "gen/ragel/alt4_2-G2.c"
		
		goto _st9;
		_ctr8:
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a6 = p; b5 = b6 = NULL; }
		
#line 248 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b7 = p; }
		
#line 254 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 260 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a7 = p; }
		
#line 266 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 272 "gen/ragel/alt4_2-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			outc(out, '\n');
		}
		
#line 288 "gen/ragel/alt4_2-G2.c"
		
		goto _st9;
		_ctr11:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 296 "gen/ragel/alt4_2-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			outc(out, '\n');
		}
		
#line 312 "gen/ragel/alt4_2-G2.c"
		
		goto _st9;
		_ctr13:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b2 = p; a1 = a2 = NULL; }
		
#line 320 "gen/ragel/alt4_2-G2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b3 = p; }
		
#line 326 "gen/ragel/alt4_2-G2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b4 = p; a3 = a4 = NULL; }
		
#line 332 "gen/ragel/alt4_2-G2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a3 = p; }
		
#line 338 "gen/ragel/alt4_2-G2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a4 = p; b3 = b4 = NULL; }
		
#line 344 "gen/ragel/alt4_2-G2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b5 = p; }
		
#line 350 "gen/ragel/alt4_2-G2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b6 = p; a5 = a6 = NULL; }
		
#line 356 "gen/ragel/alt4_2-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a5 = p; }
		
#line 362 "gen/ragel/alt4_2-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a6 = p; b5 = b6 = NULL; }
		
#line 368 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b7 = p; }
		
#line 374 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 380 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a7 = p; }
		
#line 386 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 392 "gen/ragel/alt4_2-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			outc(out, '\n');
		}
		
#line 408 "gen/ragel/alt4_2-G2.c"
		
		goto _st9;
		_ctr16:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a4 = p; b3 = b4 = NULL; }
		
#line 416 "gen/ragel/alt4_2-G2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b5 = p; }
		
#line 422 "gen/ragel/alt4_2-G2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b6 = p; a5 = a6 = NULL; }
		
#line 428 "gen/ragel/alt4_2-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a5 = p; }
		
#line 434 "gen/ragel/alt4_2-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a6 = p; b5 = b6 = NULL; }
		
#line 440 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b7 = p; }
		
#line 446 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 452 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a7 = p; }
		
#line 458 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 464 "gen/ragel/alt4_2-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			outc(out, '\n');
		}
		
#line 480 "gen/ragel/alt4_2-G2.c"
		
		goto _st9;
		_ctr19:
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b6 = p; a5 = a6 = NULL; }
		
#line 488 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b7 = p; }
		
#line 494 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 500 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a7 = p; }
		
#line 506 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 512 "gen/ragel/alt4_2-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			outc(out, '\n');
		}
		
#line 528 "gen/ragel/alt4_2-G2.c"
		
		goto _st9;
		_ctr22:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 536 "gen/ragel/alt4_2-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			outc(out, '\n');
		}
		
#line 552 "gen/ragel/alt4_2-G2.c"
		
		goto _st9;
		_ctr24:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b1 = p; }
		
#line 560 "gen/ragel/alt4_2-G2.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b2 = p; a1 = a2 = NULL; }
		
#line 566 "gen/ragel/alt4_2-G2.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a1 = p; }
		
#line 572 "gen/ragel/alt4_2-G2.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a2 = p; b1 = b2 = NULL; }
		
#line 578 "gen/ragel/alt4_2-G2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b3 = p; }
		
#line 584 "gen/ragel/alt4_2-G2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b4 = p; a3 = a4 = NULL; }
		
#line 590 "gen/ragel/alt4_2-G2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a3 = p; }
		
#line 596 "gen/ragel/alt4_2-G2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a4 = p; b3 = b4 = NULL; }
		
#line 602 "gen/ragel/alt4_2-G2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b5 = p; }
		
#line 608 "gen/ragel/alt4_2-G2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b6 = p; a5 = a6 = NULL; }
		
#line 614 "gen/ragel/alt4_2-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a5 = p; }
		
#line 620 "gen/ragel/alt4_2-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a6 = p; b5 = b6 = NULL; }
		
#line 626 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b7 = p; }
		
#line 632 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 638 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a7 = p; }
		
#line 644 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 650 "gen/ragel/alt4_2-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
			else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
			if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
			else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
			outc(out, '\n');
		}
		
#line 666 "gen/ragel/alt4_2-G2.c"
		
		goto _st9;
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr24;
			}
			case 97: {
				goto _ctr25;
			}
			case 98: {
				goto _ctr26;
			}
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr25:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a1 = p; }
		
#line 697 "gen/ragel/alt4_2-G2.c"
		
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
		}
		{
			goto _st0;
		}
		_ctr3:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a2 = p; b1 = b2 = NULL; }
		
#line 724 "gen/ragel/alt4_2-G2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b3 = p; }
		
#line 730 "gen/ragel/alt4_2-G2.c"
		
		goto _st2;
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr5;
			}
			case 97: {
				goto _ctr6;
			}
			case 98: {
				goto _st2;
			}
		}
		{
			goto _st0;
		}
		_ctr6:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b4 = p; a3 = a4 = NULL; }
		
#line 757 "gen/ragel/alt4_2-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a5 = p; }
		
#line 763 "gen/ragel/alt4_2-G2.c"
		
		goto _st3;
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr8;
			}
			case 97: {
				goto _st3;
			}
			case 98: {
				goto _ctr9;
			}
		}
		{
			goto _st0;
		}
		_ctr9:
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a6 = p; b5 = b6 = NULL; }
		
#line 790 "gen/ragel/alt4_2-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b7 = p; }
		
#line 796 "gen/ragel/alt4_2-G2.c"
		
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
			case 98: {
				goto _st4;
			}
		}
		{
			goto _st0;
		}
		_ctr26:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b1 = p; }
		
#line 820 "gen/ragel/alt4_2-G2.c"
		
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
		}
		{
			goto _st0;
		}
		_ctr14:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b2 = p; a1 = a2 = NULL; }
		
#line 847 "gen/ragel/alt4_2-G2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a3 = p; }
		
#line 853 "gen/ragel/alt4_2-G2.c"
		
		goto _st6;
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr16;
			}
			case 97: {
				goto _st6;
			}
			case 98: {
				goto _ctr17;
			}
		}
		{
			goto _st0;
		}
		_ctr17:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a4 = p; b3 = b4 = NULL; }
		
#line 880 "gen/ragel/alt4_2-G2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b5 = p; }
		
#line 886 "gen/ragel/alt4_2-G2.c"
		
		goto _st7;
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr19;
			}
			case 97: {
				goto _ctr20;
			}
			case 98: {
				goto _st7;
			}
		}
		{
			goto _st0;
		}
		_ctr20:
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			b6 = p; a5 = a6 = NULL; }
		
#line 913 "gen/ragel/alt4_2-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
			a7 = p; }
		
#line 919 "gen/ragel/alt4_2-G2.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr22;
			}
			case 97: {
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
	
#line 68 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
	
	
	in->p = p;
	in->pe = pe;
}
