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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b0 = p; }
		
#line 70 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 76 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 82 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 88 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 94 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 100 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 106 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 117 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr6:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 125 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 131 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 137 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 143 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 149 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 155 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 166 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr10:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 174 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 180 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 186 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 192 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 198 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 209 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr14:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 217 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 223 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 229 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 235 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 246 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr18:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 254 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 260 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 266 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 277 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr22:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 285 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 291 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 302 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr26:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 310 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 321 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr29:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 334 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_ctr31:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a0 = p; }
		
#line 342 "gen/ragel/23__cat4_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b0 = p; }
		
#line 348 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 354 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 360 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 366 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 372 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 378 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 384 "gen/ragel/23__cat4_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 395 "gen/ragel/23__cat4_0.c"
		
		goto _st9;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
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
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr3:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b0 = p; }
		
#line 423 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 429 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 435 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 441 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 447 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 453 "gen/ragel/23__cat4_0.c"
		
		goto _st1;
		_ctr32:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a0 = p; }
		
#line 461 "gen/ragel/23__cat4_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b0 = p; }
		
#line 467 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 473 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 479 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 485 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 491 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 497 "gen/ragel/23__cat4_0.c"
		
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
				goto _ctr3;
			}
			case 98: {
				goto _ctr4;
			}
		}
		goto _st0;
		_ctr4:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b0 = p; }
		
#line 522 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 528 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 534 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 540 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 546 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 552 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 558 "gen/ragel/23__cat4_0.c"
		
		goto _st2;
		_ctr8:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 566 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 572 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 578 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 584 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 590 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 596 "gen/ragel/23__cat4_0.c"
		
		goto _st2;
		_ctr33:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a0 = p; }
		
#line 604 "gen/ragel/23__cat4_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b0 = p; }
		
#line 610 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 616 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 622 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 628 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 634 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 640 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 646 "gen/ragel/23__cat4_0.c"
		
		goto _st2;
		_st2:
		p+= 1;
		st_case_2:
		if ( p == pe )
			goto _out2;
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
		goto _st0;
		_ctr7:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a1 = p; }
		
#line 671 "gen/ragel/23__cat4_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 677 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 683 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 689 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 695 "gen/ragel/23__cat4_0.c"
		
		goto _st3;
		_ctr11:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 703 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 709 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 715 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 721 "gen/ragel/23__cat4_0.c"
		
		goto _st3;
		_st3:
		p+= 1;
		st_case_3:
		if ( p == pe )
			goto _out3;
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
		goto _st0;
		_ctr12:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b1 = p; }
		
#line 746 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 752 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 758 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 764 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 770 "gen/ragel/23__cat4_0.c"
		
		goto _st4;
		_ctr16:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 778 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 784 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 790 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 796 "gen/ragel/23__cat4_0.c"
		
		goto _st4;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
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
		goto _st0;
		_ctr15:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a2 = p; }
		
#line 821 "gen/ragel/23__cat4_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 827 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 833 "gen/ragel/23__cat4_0.c"
		
		goto _st5;
		_ctr19:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 841 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 847 "gen/ragel/23__cat4_0.c"
		
		goto _st5;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
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
		goto _st0;
		_ctr20:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b2 = p; }
		
#line 872 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 878 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 884 "gen/ragel/23__cat4_0.c"
		
		goto _st6;
		_ctr24:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 892 "gen/ragel/23__cat4_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 898 "gen/ragel/23__cat4_0.c"
		
		goto _st6;
		_st6:
		p+= 1;
		st_case_6:
		if ( p == pe )
			goto _out6;
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
		goto _st0;
		_ctr23:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			a3 = p; }
		
#line 923 "gen/ragel/23__cat4_0.c"
		
		goto _st7;
		_st7:
		p+= 1;
		st_case_7:
		if ( p == pe )
			goto _out7;
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
		goto _st0;
		_ctr27:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
			b3 = p; }
		
#line 948 "gen/ragel/23__cat4_0.c"
		
		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr29;
			}
			case 98: {
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
	
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/23__cat4_0.rl"
	
	
	in->p = p;
	in->pe = pe;
}
