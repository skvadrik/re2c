#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"



#line 12 "gen/ragel/cat8_0.c"
static const int abcd_start = 17;
static const int abcd_first_final = 17;
static const int abcd_error = 0;

static const int abcd_en_main = 17;


#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
	*b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
	int cs;
	
	
#line 33 "gen/ragel/cat8_0.c"
	{
		cs = (int)abcd_start;
	}
	
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
	
	
#line 41 "gen/ragel/cat8_0.c"
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b0 = p; }
		
#line 89 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a1 = p; }
		
#line 95 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b1 = p; }
		
#line 101 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 107 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 113 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 119 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 125 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 131 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 137 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 143 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 149 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 155 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 161 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 167 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 173 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 188 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr6:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a1 = p; }
		
#line 196 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b1 = p; }
		
#line 202 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 208 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 214 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 220 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 226 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 232 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 238 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 244 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 250 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 256 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 262 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 268 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 274 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 289 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr10:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b1 = p; }
		
#line 297 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 303 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 309 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 315 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 321 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 327 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 333 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 339 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 345 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 351 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 357 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 363 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 369 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 384 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr14:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 392 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 398 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 404 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 410 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 416 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 422 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 428 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 434 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 440 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 446 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 452 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 458 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 473 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr18:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 481 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 487 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 493 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 499 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 505 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 511 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 517 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 523 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 529 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 535 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 541 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 556 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr22:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 564 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 570 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 576 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 582 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 588 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 594 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 600 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 606 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 612 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 618 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 633 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr26:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 641 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 647 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 653 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 659 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 665 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 671 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 677 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 683 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 689 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 704 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr30:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 712 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 718 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 724 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 730 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 736 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 742 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 748 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 754 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 769 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr34:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 777 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 783 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 789 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 795 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 801 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 807 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 813 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 828 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr38:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 836 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 842 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 848 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 854 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 860 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 866 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 881 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr42:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 889 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 895 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 901 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 907 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 913 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 928 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr46:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 936 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 942 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 948 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 954 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 969 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr50:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 977 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 983 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 989 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 1004 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr54:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 1012 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 1018 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 1033 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr58:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 1041 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 1056 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr61:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 1073 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_ctr63:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a0 = p; }
		
#line 1081 "gen/ragel/cat8_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b0 = p; }
		
#line 1087 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a1 = p; }
		
#line 1093 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b1 = p; }
		
#line 1099 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 1105 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 1111 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 1117 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 1123 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 1129 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 1135 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 1141 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 1147 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 1153 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 1159 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 1165 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 1171 "gen/ragel/cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 1186 "gen/ragel/cat8_0.c"
		
		goto _st17;
		_st17:
		p+= 1;
		if ( p == pe )
			goto _test_eof17;
		st_case_17:
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b0 = p; }
		
#line 1217 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a1 = p; }
		
#line 1223 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b1 = p; }
		
#line 1229 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 1235 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 1241 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 1247 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 1253 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 1259 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 1265 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 1271 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 1277 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 1283 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 1289 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 1295 "gen/ragel/cat8_0.c"
		
		goto _st1;
		_ctr64:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a0 = p; }
		
#line 1303 "gen/ragel/cat8_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b0 = p; }
		
#line 1309 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a1 = p; }
		
#line 1315 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b1 = p; }
		
#line 1321 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 1327 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 1333 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 1339 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 1345 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 1351 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 1357 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 1363 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 1369 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 1375 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 1381 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 1387 "gen/ragel/cat8_0.c"
		
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b0 = p; }
		
#line 1414 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a1 = p; }
		
#line 1420 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b1 = p; }
		
#line 1426 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 1432 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 1438 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 1444 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 1450 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 1456 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 1462 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 1468 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 1474 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 1480 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 1486 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 1492 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 1498 "gen/ragel/cat8_0.c"
		
		goto _st2;
		_ctr8:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a1 = p; }
		
#line 1506 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b1 = p; }
		
#line 1512 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 1518 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 1524 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 1530 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 1536 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 1542 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 1548 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 1554 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 1560 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 1566 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 1572 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 1578 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 1584 "gen/ragel/cat8_0.c"
		
		goto _st2;
		_ctr65:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a0 = p; }
		
#line 1592 "gen/ragel/cat8_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b0 = p; }
		
#line 1598 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a1 = p; }
		
#line 1604 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b1 = p; }
		
#line 1610 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 1616 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 1622 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 1628 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 1634 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 1640 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 1646 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 1652 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 1658 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 1664 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 1670 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 1676 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 1682 "gen/ragel/cat8_0.c"
		
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
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a1 = p; }
		
#line 1709 "gen/ragel/cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b1 = p; }
		
#line 1715 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 1721 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 1727 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 1733 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 1739 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 1745 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 1751 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 1757 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 1763 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 1769 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 1775 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 1781 "gen/ragel/cat8_0.c"
		
		goto _st3;
		_ctr11:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b1 = p; }
		
#line 1789 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 1795 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 1801 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 1807 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 1813 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 1819 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 1825 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 1831 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 1837 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 1843 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 1849 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 1855 "gen/ragel/cat8_0.c"
		
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
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b1 = p; }
		
#line 1882 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 1888 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 1894 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 1900 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 1906 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 1912 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 1918 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 1924 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 1930 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 1936 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 1942 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 1948 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 1954 "gen/ragel/cat8_0.c"
		
		goto _st4;
		_ctr16:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 1962 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 1968 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 1974 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 1980 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 1986 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 1992 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 1998 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2004 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2010 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2016 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2022 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 2028 "gen/ragel/cat8_0.c"
		
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
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a2 = p; }
		
#line 2055 "gen/ragel/cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 2061 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 2067 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 2073 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 2079 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 2085 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 2091 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2097 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2103 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2109 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2115 "gen/ragel/cat8_0.c"
		
		goto _st5;
		_ctr19:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 2123 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 2129 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 2135 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 2141 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 2147 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 2153 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2159 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2165 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2171 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2177 "gen/ragel/cat8_0.c"
		
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
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b2 = p; }
		
#line 2204 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 2210 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 2216 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 2222 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 2228 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 2234 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2240 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2246 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2252 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2258 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 2264 "gen/ragel/cat8_0.c"
		
		goto _st6;
		_ctr24:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 2272 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 2278 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 2284 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 2290 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 2296 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2302 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2308 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2314 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2320 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 2326 "gen/ragel/cat8_0.c"
		
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
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a3 = p; }
		
#line 2353 "gen/ragel/cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 2359 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 2365 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 2371 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 2377 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2383 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2389 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2395 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2401 "gen/ragel/cat8_0.c"
		
		goto _st7;
		_ctr27:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 2409 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 2415 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 2421 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 2427 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2433 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2439 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2445 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2451 "gen/ragel/cat8_0.c"
		
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
				goto _ctr27;
			}
			case 98: {
				goto _ctr28;
			}
		}
		{
			goto _st0;
		}
		_ctr28:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b3 = p; }
		
#line 2478 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 2484 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 2490 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 2496 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2502 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2508 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2514 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2520 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 2526 "gen/ragel/cat8_0.c"
		
		goto _st8;
		_ctr32:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 2534 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 2540 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 2546 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2552 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2558 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2564 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2570 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 2576 "gen/ragel/cat8_0.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
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
		}
		{
			goto _st0;
		}
		_ctr31:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a4 = p; }
		
#line 2603 "gen/ragel/cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 2609 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 2615 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2621 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2627 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2633 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2639 "gen/ragel/cat8_0.c"
		
		goto _st9;
		_ctr35:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 2647 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 2653 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2659 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2665 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2671 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2677 "gen/ragel/cat8_0.c"
		
		goto _st9;
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr34;
			}
			case 97: {
				goto _ctr35;
			}
			case 98: {
				goto _ctr36;
			}
		}
		{
			goto _st0;
		}
		_ctr36:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b4 = p; }
		
#line 2704 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 2710 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2716 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2722 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2728 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2734 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 2740 "gen/ragel/cat8_0.c"
		
		goto _st10;
		_ctr40:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 2748 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2754 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2760 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2766 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2772 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 2778 "gen/ragel/cat8_0.c"
		
		goto _st10;
		_st10:
		p+= 1;
		if ( p == pe )
			goto _test_eof10;
		st_case_10:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr38;
			}
			case 97: {
				goto _ctr39;
			}
			case 98: {
				goto _ctr40;
			}
		}
		{
			goto _st0;
		}
		_ctr39:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a5 = p; }
		
#line 2805 "gen/ragel/cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2811 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2817 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2823 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2829 "gen/ragel/cat8_0.c"
		
		goto _st11;
		_ctr43:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2837 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2843 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2849 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2855 "gen/ragel/cat8_0.c"
		
		goto _st11;
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr42;
			}
			case 97: {
				goto _ctr43;
			}
			case 98: {
				goto _ctr44;
			}
		}
		{
			goto _st0;
		}
		_ctr44:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b5 = p; }
		
#line 2882 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2888 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2894 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2900 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 2906 "gen/ragel/cat8_0.c"
		
		goto _st12;
		_ctr48:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2914 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2920 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2926 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 2932 "gen/ragel/cat8_0.c"
		
		goto _st12;
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr46;
			}
			case 97: {
				goto _ctr47;
			}
			case 98: {
				goto _ctr48;
			}
		}
		{
			goto _st0;
		}
		_ctr47:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a6 = p; }
		
#line 2959 "gen/ragel/cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2965 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2971 "gen/ragel/cat8_0.c"
		
		goto _st13;
		_ctr51:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 2979 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 2985 "gen/ragel/cat8_0.c"
		
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
				goto _ctr52;
			}
		}
		{
			goto _st0;
		}
		_ctr52:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b6 = p; }
		
#line 3012 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 3018 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 3024 "gen/ragel/cat8_0.c"
		
		goto _st14;
		_ctr56:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 3032 "gen/ragel/cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 3038 "gen/ragel/cat8_0.c"
		
		goto _st14;
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
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
		}
		{
			goto _st0;
		}
		_ctr55:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			a7 = p; }
		
#line 3065 "gen/ragel/cat8_0.c"
		
		goto _st15;
		_st15:
		p+= 1;
		if ( p == pe )
			goto _test_eof15;
		st_case_15:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr58;
			}
			case 97: {
				goto _st15;
			}
			case 98: {
				goto _ctr59;
			}
		}
		{
			goto _st0;
		}
		_ctr59:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
			b7 = p; }
		
#line 3092 "gen/ragel/cat8_0.c"
		
		goto _st16;
		_st16:
		p+= 1;
		if ( p == pe )
			goto _test_eof16;
		st_case_16:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr61;
			}
			case 98: {
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
	
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
	
	
	in->p = p;
	in->pe = pe;
}
