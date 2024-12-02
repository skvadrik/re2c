#line 1 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 29 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"



#line 9 "gen/ragel/submatch_26__cat8_0.c"
static const int abcd_start = 17;
static const int abcd_first_final = 17;
static const int abcd_error = 0;

static const int abcd_en_main = 17;


#line 31 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
	*b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
	int cs;
	

#line 27 "gen/ragel/submatch_26__cat8_0.c"
	{
		cs = (int)abcd_start;
	}
	
#line 42 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"


#line 32 "gen/ragel/submatch_26__cat8_0.c"
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
#line 9 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b0 = p; }
		
#line 76 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a1 = p; }
		
#line 81 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b1 = p; }
		
#line 86 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 91 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 96 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 101 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 106 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 111 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 116 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 121 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 126 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 131 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 136 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 141 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 146 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 160 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr6:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a1 = p; }
		
#line 167 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b1 = p; }
		
#line 172 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 177 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 182 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 187 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 192 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 197 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 202 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 207 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 212 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 217 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 222 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 227 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 232 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 246 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr10:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b1 = p; }
		
#line 253 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 258 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 263 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 268 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 273 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 278 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 283 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 288 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 293 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 298 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 303 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 308 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 313 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 327 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr14:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 334 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 339 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 344 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 349 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 354 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 359 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 364 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 369 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 374 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 379 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 384 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 389 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 403 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr18:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 410 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 415 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 420 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 425 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 430 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 435 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 440 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 445 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 450 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 455 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 460 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 474 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr22:
			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 481 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 486 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 491 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 496 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 501 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 506 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 511 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 516 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 521 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 526 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 540 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr26:
			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 547 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 552 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 557 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 562 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 567 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 572 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 577 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 582 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 587 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 601 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr30:
			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 608 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 613 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 618 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 623 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 628 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 633 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 638 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 643 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 657 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr34:
			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 664 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 669 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 674 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 679 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 684 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 689 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 694 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 708 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr38:
			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 715 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 720 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 725 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 730 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 735 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 740 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 754 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr42:
			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 761 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 766 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 771 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 776 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 781 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 795 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr46:
			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 802 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 807 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 812 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 817 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 831 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr50:
			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 838 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 843 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 848 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 862 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr54:
			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 869 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 874 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 888 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr58:
			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 895 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 909 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr61:
			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 925 "gen/ragel/submatch_26__cat8_0.c"

		goto _st17;
		_ctr63:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a0 = p; }
		
#line 932 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b0 = p; }
		
#line 937 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a1 = p; }
		
#line 942 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b1 = p; }
		
#line 947 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 952 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 957 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 962 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 967 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 972 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 977 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 982 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 987 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 992 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 997 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 1002 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 1007 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 1021 "gen/ragel/submatch_26__cat8_0.c"

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
#line 9 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b0 = p; }
		
#line 1048 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a1 = p; }
		
#line 1053 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b1 = p; }
		
#line 1058 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 1063 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 1068 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 1073 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 1078 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 1083 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 1088 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 1093 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 1098 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 1103 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 1108 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 1113 "gen/ragel/submatch_26__cat8_0.c"

		goto _st1;
		_ctr64:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a0 = p; }
		
#line 1120 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b0 = p; }
		
#line 1125 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a1 = p; }
		
#line 1130 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b1 = p; }
		
#line 1135 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 1140 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 1145 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 1150 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 1155 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 1160 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 1165 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 1170 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 1175 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 1180 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 1185 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 1190 "gen/ragel/submatch_26__cat8_0.c"

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
#line 9 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b0 = p; }
		
#line 1214 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a1 = p; }
		
#line 1219 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b1 = p; }
		
#line 1224 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 1229 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 1234 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 1239 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 1244 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 1249 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 1254 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 1259 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 1264 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 1269 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 1274 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 1279 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 1284 "gen/ragel/submatch_26__cat8_0.c"

		goto _st2;
		_ctr8:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a1 = p; }
		
#line 1291 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b1 = p; }
		
#line 1296 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 1301 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 1306 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 1311 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 1316 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 1321 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 1326 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 1331 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 1336 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 1341 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 1346 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 1351 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 1356 "gen/ragel/submatch_26__cat8_0.c"

		goto _st2;
		_ctr65:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a0 = p; }
		
#line 1363 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b0 = p; }
		
#line 1368 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a1 = p; }
		
#line 1373 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b1 = p; }
		
#line 1378 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 1383 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 1388 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 1393 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 1398 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 1403 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 1408 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 1413 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 1418 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 1423 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 1428 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 1433 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 1438 "gen/ragel/submatch_26__cat8_0.c"

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
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a1 = p; }
		
#line 1462 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b1 = p; }
		
#line 1467 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 1472 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 1477 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 1482 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 1487 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 1492 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 1497 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 1502 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 1507 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 1512 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 1517 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 1522 "gen/ragel/submatch_26__cat8_0.c"

		goto _st3;
		_ctr11:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b1 = p; }
		
#line 1529 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 1534 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 1539 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 1544 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 1549 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 1554 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 1559 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 1564 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 1569 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 1574 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 1579 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 1584 "gen/ragel/submatch_26__cat8_0.c"

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
#line 10 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b1 = p; }
		
#line 1608 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 1613 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 1618 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 1623 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 1628 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 1633 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 1638 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 1643 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 1648 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 1653 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 1658 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 1663 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 1668 "gen/ragel/submatch_26__cat8_0.c"

		goto _st4;
		_ctr16:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 1675 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 1680 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 1685 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 1690 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 1695 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 1700 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 1705 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 1710 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 1715 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 1720 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 1725 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 1730 "gen/ragel/submatch_26__cat8_0.c"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a2 = p; }
		
#line 1754 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 1759 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 1764 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 1769 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 1774 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 1779 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 1784 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 1789 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 1794 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 1799 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 1804 "gen/ragel/submatch_26__cat8_0.c"

		goto _st5;
		_ctr19:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 1811 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 1816 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 1821 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 1826 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 1831 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 1836 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 1841 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 1846 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 1851 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 1856 "gen/ragel/submatch_26__cat8_0.c"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b2 = p; }
		
#line 1880 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 1885 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 1890 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 1895 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 1900 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 1905 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 1910 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 1915 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 1920 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 1925 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 1930 "gen/ragel/submatch_26__cat8_0.c"

		goto _st6;
		_ctr24:
			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 1937 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 1942 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 1947 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 1952 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 1957 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 1962 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 1967 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 1972 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 1977 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 1982 "gen/ragel/submatch_26__cat8_0.c"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a3 = p; }
		
#line 2006 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 2011 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 2016 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 2021 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 2026 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 2031 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 2036 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2041 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2046 "gen/ragel/submatch_26__cat8_0.c"

		goto _st7;
		_ctr27:
			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 2053 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 2058 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 2063 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 2068 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 2073 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 2078 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2083 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2088 "gen/ragel/submatch_26__cat8_0.c"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b3 = p; }
		
#line 2112 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 2117 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 2122 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 2127 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 2132 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 2137 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2142 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2147 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 2152 "gen/ragel/submatch_26__cat8_0.c"

		goto _st8;
		_ctr32:
			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 2159 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 2164 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 2169 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 2174 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 2179 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2184 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2189 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 2194 "gen/ragel/submatch_26__cat8_0.c"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a4 = p; }
		
#line 2218 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 2223 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 2228 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 2233 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 2238 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2243 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2248 "gen/ragel/submatch_26__cat8_0.c"

		goto _st9;
		_ctr35:
			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 2255 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 2260 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 2265 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 2270 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2275 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2280 "gen/ragel/submatch_26__cat8_0.c"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b4 = p; }
		
#line 2304 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 2309 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 2314 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 2319 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2324 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2329 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 2334 "gen/ragel/submatch_26__cat8_0.c"

		goto _st10;
		_ctr40:
			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 2341 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 2346 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 2351 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2356 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2361 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 2366 "gen/ragel/submatch_26__cat8_0.c"

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
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a5 = p; }
		
#line 2390 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 2395 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 2400 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2405 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2410 "gen/ragel/submatch_26__cat8_0.c"

		goto _st11;
		_ctr43:
			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 2417 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 2422 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2427 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2432 "gen/ragel/submatch_26__cat8_0.c"

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
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b5 = p; }
		
#line 2456 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 2461 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2466 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2471 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 2476 "gen/ragel/submatch_26__cat8_0.c"

		goto _st12;
		_ctr48:
			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 2483 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2488 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2493 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 2498 "gen/ragel/submatch_26__cat8_0.c"

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
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a6 = p; }
		
#line 2522 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2527 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2532 "gen/ragel/submatch_26__cat8_0.c"

		goto _st13;
		_ctr51:
			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2539 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2544 "gen/ragel/submatch_26__cat8_0.c"

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
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b6 = p; }
		
#line 2568 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2573 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 2578 "gen/ragel/submatch_26__cat8_0.c"

		goto _st14;
		_ctr56:
			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2585 "gen/ragel/submatch_26__cat8_0.c"

			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 2590 "gen/ragel/submatch_26__cat8_0.c"

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
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			a7 = p; }
		
#line 2614 "gen/ragel/submatch_26__cat8_0.c"

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
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
			b7 = p; }
		
#line 2638 "gen/ragel/submatch_26__cat8_0.c"

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
	
#line 43 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"

	
	in->p = p;
	in->pe = pe;
}
