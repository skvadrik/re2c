#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 48 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"



#line 13 "gen/ragel/16__alt4_2.c"
static const int m_start = 9;
static const int m_first_final = 9;
static const int m_error = 0;

static const int m_en_main = 9;


#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"


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
	
	
#line 40 "gen/ragel/16__alt4_2.c"
	{
		cs = (int)m_start;
	}
	
#line 67 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
	
	
#line 48 "gen/ragel/16__alt4_2.c"
	{
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
		_ctr2:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a2 = p; b1 = b2 = NULL; }
		
#line 77 "gen/ragel/16__alt4_2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b3 = p; }
		
#line 83 "gen/ragel/16__alt4_2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b4 = p; a3 = a4 = NULL; }
		
#line 89 "gen/ragel/16__alt4_2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a3 = p; }
		
#line 95 "gen/ragel/16__alt4_2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a4 = p; b3 = b4 = NULL; }
		
#line 101 "gen/ragel/16__alt4_2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b5 = p; }
		
#line 107 "gen/ragel/16__alt4_2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b6 = p; a5 = a6 = NULL; }
		
#line 113 "gen/ragel/16__alt4_2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a5 = p; }
		
#line 119 "gen/ragel/16__alt4_2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a6 = p; b5 = b6 = NULL; }
		
#line 125 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b7 = p; }
		
#line 131 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 137 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a7 = p; }
		
#line 143 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 149 "gen/ragel/16__alt4_2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			
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
		
#line 165 "gen/ragel/16__alt4_2.c"
		
		goto _st9;
		_ctr5:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b4 = p; a3 = a4 = NULL; }
		
#line 173 "gen/ragel/16__alt4_2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b5 = p; }
		
#line 179 "gen/ragel/16__alt4_2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b6 = p; a5 = a6 = NULL; }
		
#line 185 "gen/ragel/16__alt4_2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a5 = p; }
		
#line 191 "gen/ragel/16__alt4_2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a6 = p; b5 = b6 = NULL; }
		
#line 197 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b7 = p; }
		
#line 203 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 209 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a7 = p; }
		
#line 215 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 221 "gen/ragel/16__alt4_2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			
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
		
#line 237 "gen/ragel/16__alt4_2.c"
		
		goto _st9;
		_ctr8:
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a6 = p; b5 = b6 = NULL; }
		
#line 245 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b7 = p; }
		
#line 251 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 257 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a7 = p; }
		
#line 263 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 269 "gen/ragel/16__alt4_2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			
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
		
#line 285 "gen/ragel/16__alt4_2.c"
		
		goto _st9;
		_ctr11:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 293 "gen/ragel/16__alt4_2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			
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
		
#line 309 "gen/ragel/16__alt4_2.c"
		
		goto _st9;
		_ctr13:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b2 = p; a1 = a2 = NULL; }
		
#line 317 "gen/ragel/16__alt4_2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b3 = p; }
		
#line 323 "gen/ragel/16__alt4_2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b4 = p; a3 = a4 = NULL; }
		
#line 329 "gen/ragel/16__alt4_2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a3 = p; }
		
#line 335 "gen/ragel/16__alt4_2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a4 = p; b3 = b4 = NULL; }
		
#line 341 "gen/ragel/16__alt4_2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b5 = p; }
		
#line 347 "gen/ragel/16__alt4_2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b6 = p; a5 = a6 = NULL; }
		
#line 353 "gen/ragel/16__alt4_2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a5 = p; }
		
#line 359 "gen/ragel/16__alt4_2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a6 = p; b5 = b6 = NULL; }
		
#line 365 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b7 = p; }
		
#line 371 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 377 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a7 = p; }
		
#line 383 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 389 "gen/ragel/16__alt4_2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			
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
		
#line 405 "gen/ragel/16__alt4_2.c"
		
		goto _st9;
		_ctr16:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a4 = p; b3 = b4 = NULL; }
		
#line 413 "gen/ragel/16__alt4_2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b5 = p; }
		
#line 419 "gen/ragel/16__alt4_2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b6 = p; a5 = a6 = NULL; }
		
#line 425 "gen/ragel/16__alt4_2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a5 = p; }
		
#line 431 "gen/ragel/16__alt4_2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a6 = p; b5 = b6 = NULL; }
		
#line 437 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b7 = p; }
		
#line 443 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 449 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a7 = p; }
		
#line 455 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 461 "gen/ragel/16__alt4_2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			
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
		
#line 477 "gen/ragel/16__alt4_2.c"
		
		goto _st9;
		_ctr19:
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b6 = p; a5 = a6 = NULL; }
		
#line 485 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b7 = p; }
		
#line 491 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 497 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a7 = p; }
		
#line 503 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 509 "gen/ragel/16__alt4_2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			
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
		
#line 525 "gen/ragel/16__alt4_2.c"
		
		goto _st9;
		_ctr22:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 533 "gen/ragel/16__alt4_2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			
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
		
#line 549 "gen/ragel/16__alt4_2.c"
		
		goto _st9;
		_ctr24:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b1 = p; }
		
#line 557 "gen/ragel/16__alt4_2.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b2 = p; a1 = a2 = NULL; }
		
#line 563 "gen/ragel/16__alt4_2.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a1 = p; }
		
#line 569 "gen/ragel/16__alt4_2.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a2 = p; b1 = b2 = NULL; }
		
#line 575 "gen/ragel/16__alt4_2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b3 = p; }
		
#line 581 "gen/ragel/16__alt4_2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b4 = p; a3 = a4 = NULL; }
		
#line 587 "gen/ragel/16__alt4_2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a3 = p; }
		
#line 593 "gen/ragel/16__alt4_2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a4 = p; b3 = b4 = NULL; }
		
#line 599 "gen/ragel/16__alt4_2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b5 = p; }
		
#line 605 "gen/ragel/16__alt4_2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b6 = p; a5 = a6 = NULL; }
		
#line 611 "gen/ragel/16__alt4_2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a5 = p; }
		
#line 617 "gen/ragel/16__alt4_2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a6 = p; b5 = b6 = NULL; }
		
#line 623 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b7 = p; }
		
#line 629 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b8 = p; a7 = a8 = NULL; }
		
#line 635 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a7 = p; }
		
#line 641 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a8 = p; b7 = b8 = NULL; }
		
#line 647 "gen/ragel/16__alt4_2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			
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
		
#line 663 "gen/ragel/16__alt4_2.c"
		
		goto _st9;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
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
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr25:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a1 = p; }
		
#line 691 "gen/ragel/16__alt4_2.c"
		
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
		}
		goto _st0;
		_ctr3:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a2 = p; b1 = b2 = NULL; }
		
#line 716 "gen/ragel/16__alt4_2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b3 = p; }
		
#line 722 "gen/ragel/16__alt4_2.c"
		
		goto _st2;
		_st2:
		p+= 1;
		st_case_2:
		if ( p == pe )
			goto _out2;
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
		goto _st0;
		_ctr6:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b4 = p; a3 = a4 = NULL; }
		
#line 747 "gen/ragel/16__alt4_2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a5 = p; }
		
#line 753 "gen/ragel/16__alt4_2.c"
		
		goto _st3;
		_st3:
		p+= 1;
		st_case_3:
		if ( p == pe )
			goto _out3;
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
		goto _st0;
		_ctr9:
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a6 = p; b5 = b6 = NULL; }
		
#line 778 "gen/ragel/16__alt4_2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b7 = p; }
		
#line 784 "gen/ragel/16__alt4_2.c"
		
		goto _st4;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr11;
			}
			case 98: {
				goto _st4;
			}
		}
		goto _st0;
		_ctr26:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b1 = p; }
		
#line 806 "gen/ragel/16__alt4_2.c"
		
		goto _st5;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
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
		goto _st0;
		_ctr14:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b2 = p; a1 = a2 = NULL; }
		
#line 831 "gen/ragel/16__alt4_2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a3 = p; }
		
#line 837 "gen/ragel/16__alt4_2.c"
		
		goto _st6;
		_st6:
		p+= 1;
		st_case_6:
		if ( p == pe )
			goto _out6;
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
		goto _st0;
		_ctr17:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a4 = p; b3 = b4 = NULL; }
		
#line 862 "gen/ragel/16__alt4_2.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b5 = p; }
		
#line 868 "gen/ragel/16__alt4_2.c"
		
		goto _st7;
		_st7:
		p+= 1;
		st_case_7:
		if ( p == pe )
			goto _out7;
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
		goto _st0;
		_ctr20:
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			b6 = p; a5 = a6 = NULL; }
		
#line 893 "gen/ragel/16__alt4_2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
			a7 = p; }
		
#line 899 "gen/ragel/16__alt4_2.c"
		
		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr22;
			}
			case 97: {
				goto _st8;
			}
		}
		goto _st0;
		_out9: cs = 9; goto _out; 
		_out0: cs = 0; goto _out; 
		_out1: cs = 1; goto _out; 
		_out2: cs = 2; goto _out; 
		_out3: cs = 3; goto _out; 
		_out4: cs = 4; goto _out; 
		_out5: cs = 5; goto _out; 
		_out6: cs = 6; goto _out; 
		_out7: cs = 7; goto _out; 
		_out8: cs = 8; goto _out; 
		_out: {}
	}
	
#line 68 "../../../benchmarks/submatch_dfa_aot/src/ragel/16__alt4_2.rl"
	
	
	in->p = p;
	in->pe = pe;
}
