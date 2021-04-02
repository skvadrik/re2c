#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"



#line 12 "gen/ragel/26__cat8_0.c"
static const int abcd_start = 17;
static const int abcd_first_final = 17;
static const int abcd_error = 0;

static const int abcd_en_main = 17;


#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
	*b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
	int cs;
	
	
#line 33 "gen/ragel/26__cat8_0.c"
	{
		cs = (int)abcd_start;
	}
	
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
	
	
#line 41 "gen/ragel/26__cat8_0.c"
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b0 = p; }
		
#line 86 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a1 = p; }
		
#line 92 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b1 = p; }
		
#line 98 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 104 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 110 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 116 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 122 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 128 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 134 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 140 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 146 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 152 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 158 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 164 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 170 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 185 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr6:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a1 = p; }
		
#line 193 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b1 = p; }
		
#line 199 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 205 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 211 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 217 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 223 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 229 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 235 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 241 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 247 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 253 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 259 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 265 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 271 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 286 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr10:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b1 = p; }
		
#line 294 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 300 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 306 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 312 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 318 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 324 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 330 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 336 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 342 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 348 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 354 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 360 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 366 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 381 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr14:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 389 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 395 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 401 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 407 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 413 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 419 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 425 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 431 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 437 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 443 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 449 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 455 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 470 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr18:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 478 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 484 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 490 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 496 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 502 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 508 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 514 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 520 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 526 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 532 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 538 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 553 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr22:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 561 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 567 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 573 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 579 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 585 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 591 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 597 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 603 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 609 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 615 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 630 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr26:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 638 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 644 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 650 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 656 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 662 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 668 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 674 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 680 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 686 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 701 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr30:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 709 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 715 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 721 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 727 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 733 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 739 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 745 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 751 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 766 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr34:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 774 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 780 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 786 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 792 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 798 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 804 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 810 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 825 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr38:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 833 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 839 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 845 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 851 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 857 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 863 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 878 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr42:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 886 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 892 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 898 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 904 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 910 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 925 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr46:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 933 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 939 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 945 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 951 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 966 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr50:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 974 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 980 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 986 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 1001 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr54:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 1009 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 1015 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 1030 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr58:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 1038 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 1053 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr61:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 1070 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_ctr63:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a0 = p; }
		
#line 1078 "gen/ragel/26__cat8_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b0 = p; }
		
#line 1084 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a1 = p; }
		
#line 1090 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b1 = p; }
		
#line 1096 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 1102 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 1108 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 1114 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 1120 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 1126 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 1132 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 1138 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 1144 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 1150 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 1156 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 1162 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 1168 "gen/ragel/26__cat8_0.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 1183 "gen/ragel/26__cat8_0.c"
		
		goto _st17;
		_st17:
		p+= 1;
		st_case_17:
		if ( p == pe )
			goto _out17;
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
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr3:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b0 = p; }
		
#line 1211 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a1 = p; }
		
#line 1217 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b1 = p; }
		
#line 1223 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 1229 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 1235 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 1241 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 1247 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 1253 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 1259 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 1265 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 1271 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 1277 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 1283 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 1289 "gen/ragel/26__cat8_0.c"
		
		goto _st1;
		_ctr64:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a0 = p; }
		
#line 1297 "gen/ragel/26__cat8_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b0 = p; }
		
#line 1303 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a1 = p; }
		
#line 1309 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b1 = p; }
		
#line 1315 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 1321 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 1327 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 1333 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 1339 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 1345 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 1351 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 1357 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 1363 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 1369 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 1375 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 1381 "gen/ragel/26__cat8_0.c"
		
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b0 = p; }
		
#line 1406 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a1 = p; }
		
#line 1412 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b1 = p; }
		
#line 1418 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 1424 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 1430 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 1436 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 1442 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 1448 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 1454 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 1460 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 1466 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 1472 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 1478 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 1484 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 1490 "gen/ragel/26__cat8_0.c"
		
		goto _st2;
		_ctr8:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a1 = p; }
		
#line 1498 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b1 = p; }
		
#line 1504 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 1510 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 1516 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 1522 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 1528 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 1534 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 1540 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 1546 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 1552 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 1558 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 1564 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 1570 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 1576 "gen/ragel/26__cat8_0.c"
		
		goto _st2;
		_ctr65:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a0 = p; }
		
#line 1584 "gen/ragel/26__cat8_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b0 = p; }
		
#line 1590 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a1 = p; }
		
#line 1596 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b1 = p; }
		
#line 1602 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 1608 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 1614 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 1620 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 1626 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 1632 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 1638 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 1644 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 1650 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 1656 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 1662 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 1668 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 1674 "gen/ragel/26__cat8_0.c"
		
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
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a1 = p; }
		
#line 1699 "gen/ragel/26__cat8_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b1 = p; }
		
#line 1705 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 1711 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 1717 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 1723 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 1729 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 1735 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 1741 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 1747 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 1753 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 1759 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 1765 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 1771 "gen/ragel/26__cat8_0.c"
		
		goto _st3;
		_ctr11:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b1 = p; }
		
#line 1779 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 1785 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 1791 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 1797 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 1803 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 1809 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 1815 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 1821 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 1827 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 1833 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 1839 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 1845 "gen/ragel/26__cat8_0.c"
		
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
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b1 = p; }
		
#line 1870 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 1876 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 1882 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 1888 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 1894 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 1900 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 1906 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 1912 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 1918 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 1924 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 1930 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 1936 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 1942 "gen/ragel/26__cat8_0.c"
		
		goto _st4;
		_ctr16:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 1950 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 1956 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 1962 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 1968 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 1974 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 1980 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 1986 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 1992 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 1998 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2004 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2010 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 2016 "gen/ragel/26__cat8_0.c"
		
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
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a2 = p; }
		
#line 2041 "gen/ragel/26__cat8_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 2047 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 2053 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 2059 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 2065 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 2071 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 2077 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2083 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2089 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2095 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2101 "gen/ragel/26__cat8_0.c"
		
		goto _st5;
		_ctr19:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 2109 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 2115 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 2121 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 2127 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 2133 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 2139 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2145 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2151 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2157 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2163 "gen/ragel/26__cat8_0.c"
		
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
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b2 = p; }
		
#line 2188 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 2194 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 2200 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 2206 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 2212 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 2218 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2224 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2230 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2236 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2242 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 2248 "gen/ragel/26__cat8_0.c"
		
		goto _st6;
		_ctr24:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 2256 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 2262 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 2268 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 2274 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 2280 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2286 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2292 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2298 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2304 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 2310 "gen/ragel/26__cat8_0.c"
		
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
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a3 = p; }
		
#line 2335 "gen/ragel/26__cat8_0.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 2341 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 2347 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 2353 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 2359 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2365 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2371 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2377 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2383 "gen/ragel/26__cat8_0.c"
		
		goto _st7;
		_ctr27:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 2391 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 2397 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 2403 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 2409 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2415 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2421 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2427 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2433 "gen/ragel/26__cat8_0.c"
		
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
				goto _ctr27;
			}
			case 98: {
				goto _ctr28;
			}
		}
		goto _st0;
		_ctr28:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b3 = p; }
		
#line 2458 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 2464 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 2470 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 2476 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2482 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2488 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2494 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2500 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 2506 "gen/ragel/26__cat8_0.c"
		
		goto _st8;
		_ctr32:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 2514 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 2520 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 2526 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2532 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2538 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2544 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2550 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 2556 "gen/ragel/26__cat8_0.c"
		
		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
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
		goto _st0;
		_ctr31:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a4 = p; }
		
#line 2581 "gen/ragel/26__cat8_0.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 2587 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 2593 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2599 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2605 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2611 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2617 "gen/ragel/26__cat8_0.c"
		
		goto _st9;
		_ctr35:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 2625 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 2631 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2637 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2643 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2649 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2655 "gen/ragel/26__cat8_0.c"
		
		goto _st9;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
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
		goto _st0;
		_ctr36:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b4 = p; }
		
#line 2680 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 2686 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2692 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2698 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2704 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2710 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 2716 "gen/ragel/26__cat8_0.c"
		
		goto _st10;
		_ctr40:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 2724 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2730 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2736 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2742 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2748 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 2754 "gen/ragel/26__cat8_0.c"
		
		goto _st10;
		_st10:
		p+= 1;
		st_case_10:
		if ( p == pe )
			goto _out10;
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
		goto _st0;
		_ctr39:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a5 = p; }
		
#line 2779 "gen/ragel/26__cat8_0.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2785 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2791 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2797 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2803 "gen/ragel/26__cat8_0.c"
		
		goto _st11;
		_ctr43:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2811 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2817 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2823 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2829 "gen/ragel/26__cat8_0.c"
		
		goto _st11;
		_st11:
		p+= 1;
		st_case_11:
		if ( p == pe )
			goto _out11;
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
		goto _st0;
		_ctr44:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b5 = p; }
		
#line 2854 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2860 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2866 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2872 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 2878 "gen/ragel/26__cat8_0.c"
		
		goto _st12;
		_ctr48:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2886 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2892 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2898 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 2904 "gen/ragel/26__cat8_0.c"
		
		goto _st12;
		_st12:
		p+= 1;
		st_case_12:
		if ( p == pe )
			goto _out12;
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
		goto _st0;
		_ctr47:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a6 = p; }
		
#line 2929 "gen/ragel/26__cat8_0.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2935 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2941 "gen/ragel/26__cat8_0.c"
		
		goto _st13;
		_ctr51:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2949 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2955 "gen/ragel/26__cat8_0.c"
		
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
				goto _ctr52;
			}
		}
		goto _st0;
		_ctr52:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b6 = p; }
		
#line 2980 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 2986 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 2992 "gen/ragel/26__cat8_0.c"
		
		goto _st14;
		_ctr56:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 3000 "gen/ragel/26__cat8_0.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 3006 "gen/ragel/26__cat8_0.c"
		
		goto _st14;
		_st14:
		p+= 1;
		st_case_14:
		if ( p == pe )
			goto _out14;
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
		goto _st0;
		_ctr55:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			a7 = p; }
		
#line 3031 "gen/ragel/26__cat8_0.c"
		
		goto _st15;
		_st15:
		p+= 1;
		st_case_15:
		if ( p == pe )
			goto _out15;
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
		goto _st0;
		_ctr59:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
			b7 = p; }
		
#line 3056 "gen/ragel/26__cat8_0.c"
		
		goto _st16;
		_st16:
		p+= 1;
		st_case_16:
		if ( p == pe )
			goto _out16;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr61;
			}
			case 98: {
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
	
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/26__cat8_0.rl"
	
	
	in->p = p;
	in->pe = pe;
}
