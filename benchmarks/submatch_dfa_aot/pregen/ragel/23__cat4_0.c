#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"



#line 12 "gen/ragel/23__cat4_0.c"
static const int abcd_start = 9;
static const int abcd_first_final = 9;
static const int abcd_error = 0;

static const int abcd_en_main = 9;


#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3,
	*b0, *b1, *b2, *b3;
	int cs;
	
	
#line 33 "gen/ragel/23__cat4_0.c"
	{
		cs = (int)abcd_start;
	}
	
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
	
	
#line 41 "gen/ragel/23__cat4_0.c"
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b0 = p; }
		
#line 73 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 79 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 85 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 91 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 97 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 103 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 109 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 120 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr6:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 128 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 134 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 140 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 146 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 152 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 158 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 169 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr10:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 177 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 183 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 189 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 195 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 201 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 212 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr14:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 220 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 226 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 232 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 238 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 249 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr18:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 257 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 263 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 269 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 280 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr22:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 288 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 294 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 305 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr26:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 313 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 324 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr29:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 337 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr31:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a0 = p; }
		
#line 345 "gen/ragel/23__cat4_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b0 = p; }
		
#line 351 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 357 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 363 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 369 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 375 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 381 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 387 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 398 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr31;
			}
			case 97: {
				goto _ctr32;
			}
			case 98: {
				goto _ctr33;
			}
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr3:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b0 = p; }
		
#line 429 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 435 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 441 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 447 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 453 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 459 "gen/ragel/23__cat4_0.c"
		
		goto _st1;
		_ctr32:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a0 = p; }
		
#line 467 "gen/ragel/23__cat4_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b0 = p; }
		
#line 473 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 479 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 485 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 491 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 497 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 503 "gen/ragel/23__cat4_0.c"
		
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
				goto _ctr3;
			}
			case 98: {
				goto _ctr4;
			}
		}
		{
			goto _st0;
		}
		_ctr4:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b0 = p; }
		
#line 530 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 536 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 542 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 548 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 554 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 560 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 566 "gen/ragel/23__cat4_0.c"
		
		goto _st2;
		_ctr8:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 574 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 580 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 586 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 592 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 598 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 604 "gen/ragel/23__cat4_0.c"
		
		goto _st2;
		_ctr33:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a0 = p; }
		
#line 612 "gen/ragel/23__cat4_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b0 = p; }
		
#line 618 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 624 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 630 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 636 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 642 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 648 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 654 "gen/ragel/23__cat4_0.c"
		
		goto _st2;
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr6;
			}
			case 97: {
				goto _ctr7;
			}
			case 98: {
				goto _ctr8;
			}
		}
		{
			goto _st0;
		}
		_ctr7:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 681 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 687 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 693 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 699 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 705 "gen/ragel/23__cat4_0.c"
		
		goto _st3;
		_ctr11:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 713 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 719 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 725 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 731 "gen/ragel/23__cat4_0.c"
		
		goto _st3;
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr10;
			}
			case 97: {
				goto _ctr11;
			}
			case 98: {
				goto _ctr12;
			}
		}
		{
			goto _st0;
		}
		_ctr12:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 758 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 764 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 770 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 776 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 782 "gen/ragel/23__cat4_0.c"
		
		goto _st4;
		_ctr16:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 790 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 796 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 802 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 808 "gen/ragel/23__cat4_0.c"
		
		goto _st4;
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr14;
			}
			case 97: {
				goto _ctr15;
			}
			case 98: {
				goto _ctr16;
			}
		}
		{
			goto _st0;
		}
		_ctr15:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 835 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 841 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 847 "gen/ragel/23__cat4_0.c"
		
		goto _st5;
		_ctr19:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 855 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 861 "gen/ragel/23__cat4_0.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr18;
			}
			case 97: {
				goto _ctr19;
			}
			case 98: {
				goto _ctr20;
			}
		}
		{
			goto _st0;
		}
		_ctr20:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 888 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 894 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 900 "gen/ragel/23__cat4_0.c"
		
		goto _st6;
		_ctr24:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 908 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 914 "gen/ragel/23__cat4_0.c"
		
		goto _st6;
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr22;
			}
			case 97: {
				goto _ctr23;
			}
			case 98: {
				goto _ctr24;
			}
		}
		{
			goto _st0;
		}
		_ctr23:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 941 "gen/ragel/23__cat4_0.c"
		
		goto _st7;
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr26;
			}
			case 97: {
				goto _st7;
			}
			case 98: {
				goto _ctr27;
			}
		}
		{
			goto _st0;
		}
		_ctr27:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 968 "gen/ragel/23__cat4_0.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr29;
			}
			case 98: {
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
	
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
	
	
	in->p = p;
	in->pe = pe;
}
