#line 1 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 21 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"



#line 9 "gen/ragel/submatch_23__cat4_0.c"
static const int abcd_start = 9;
static const int abcd_first_final = 9;
static const int abcd_error = 0;

static const int abcd_en_main = 9;


#line 23 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3,
	*b0, *b1, *b2, *b3;
	int cs;
	

#line 27 "gen/ragel/submatch_23__cat4_0.c"
	{
		cs = (int)abcd_start;
	}
	
#line 34 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"


#line 32 "gen/ragel/submatch_23__cat4_0.c"
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
#line 9 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b0 = p; }
		
#line 60 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a1 = p; }
		
#line 65 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b1 = p; }
		
#line 70 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 75 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 80 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 85 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 90 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 100 "gen/ragel/submatch_23__cat4_0.c"

		goto _st9;
		_ctr6:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a1 = p; }
		
#line 107 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b1 = p; }
		
#line 112 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 117 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 122 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 127 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 132 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 142 "gen/ragel/submatch_23__cat4_0.c"

		goto _st9;
		_ctr10:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b1 = p; }
		
#line 149 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 154 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 159 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 164 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 169 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 179 "gen/ragel/submatch_23__cat4_0.c"

		goto _st9;
		_ctr14:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 186 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 191 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 196 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 201 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 211 "gen/ragel/submatch_23__cat4_0.c"

		goto _st9;
		_ctr18:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 218 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 223 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 228 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 238 "gen/ragel/submatch_23__cat4_0.c"

		goto _st9;
		_ctr22:
			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 245 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 250 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 260 "gen/ragel/submatch_23__cat4_0.c"

		goto _st9;
		_ctr26:
			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 267 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 277 "gen/ragel/submatch_23__cat4_0.c"

		goto _st9;
		_ctr29:
			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 289 "gen/ragel/submatch_23__cat4_0.c"

		goto _st9;
		_ctr31:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a0 = p; }
		
#line 296 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b0 = p; }
		
#line 301 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a1 = p; }
		
#line 306 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b1 = p; }
		
#line 311 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 316 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 321 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 326 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 331 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 341 "gen/ragel/submatch_23__cat4_0.c"

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
#line 9 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b0 = p; }
		
#line 368 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a1 = p; }
		
#line 373 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b1 = p; }
		
#line 378 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 383 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 388 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 393 "gen/ragel/submatch_23__cat4_0.c"

		goto _st1;
		_ctr32:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a0 = p; }
		
#line 400 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b0 = p; }
		
#line 405 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a1 = p; }
		
#line 410 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b1 = p; }
		
#line 415 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 420 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 425 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 430 "gen/ragel/submatch_23__cat4_0.c"

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
#line 9 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b0 = p; }
		
#line 454 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a1 = p; }
		
#line 459 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b1 = p; }
		
#line 464 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 469 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 474 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 479 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 484 "gen/ragel/submatch_23__cat4_0.c"

		goto _st2;
		_ctr8:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a1 = p; }
		
#line 491 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b1 = p; }
		
#line 496 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 501 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 506 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 511 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 516 "gen/ragel/submatch_23__cat4_0.c"

		goto _st2;
		_ctr33:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a0 = p; }
		
#line 523 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b0 = p; }
		
#line 528 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a1 = p; }
		
#line 533 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b1 = p; }
		
#line 538 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 543 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 548 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 553 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 558 "gen/ragel/submatch_23__cat4_0.c"

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
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a1 = p; }
		
#line 582 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b1 = p; }
		
#line 587 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 592 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 597 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 602 "gen/ragel/submatch_23__cat4_0.c"

		goto _st3;
		_ctr11:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b1 = p; }
		
#line 609 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 614 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 619 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 624 "gen/ragel/submatch_23__cat4_0.c"

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
#line 10 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b1 = p; }
		
#line 648 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 653 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 658 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 663 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 668 "gen/ragel/submatch_23__cat4_0.c"

		goto _st4;
		_ctr16:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 675 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 680 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 685 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 690 "gen/ragel/submatch_23__cat4_0.c"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a2 = p; }
		
#line 714 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 719 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 724 "gen/ragel/submatch_23__cat4_0.c"

		goto _st5;
		_ctr19:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 731 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 736 "gen/ragel/submatch_23__cat4_0.c"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b2 = p; }
		
#line 760 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 765 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 770 "gen/ragel/submatch_23__cat4_0.c"

		goto _st6;
		_ctr24:
			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 777 "gen/ragel/submatch_23__cat4_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 782 "gen/ragel/submatch_23__cat4_0.c"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			a3 = p; }
		
#line 806 "gen/ragel/submatch_23__cat4_0.c"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
			b3 = p; }
		
#line 830 "gen/ragel/submatch_23__cat4_0.c"

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
	
#line 35 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"

	
	in->p = p;
	in->pe = pe;
}
