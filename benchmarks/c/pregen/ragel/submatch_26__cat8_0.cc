#line 1 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
#include "ragel/base.h"

namespace ragel_submatch_26__cat8_0 {
	
	const char *delim = "\n";
	
	
#line 31 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"

	

#line 11 "gen/ragel/submatch_26__cat8_0.cc"
static const int abcd_start = 17;
	static const int abcd_first_final = 17;
	static const int abcd_error = 0;
	
	static const int abcd_en_main = 17;
	
	
#line 33 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *pe = in->pe;
		const char
		*a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
		*b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
		int cs;
		

#line 28 "gen/ragel/submatch_26__cat8_0.cc"
	{
			cs = (int)abcd_start;
		}
		
#line 43 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"


#line 33 "gen/ragel/submatch_26__cat8_0.cc"
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
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b0 = p; }
			
#line 77 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a1 = p; }
			
#line 82 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b1 = p; }
			
#line 87 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 92 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 97 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 102 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 107 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 112 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 117 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 122 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 127 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 132 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 137 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 142 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 147 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 161 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr6:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a1 = p; }
			
#line 168 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b1 = p; }
			
#line 173 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 178 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 183 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 188 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 193 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 198 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 203 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 208 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 213 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 218 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 223 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 228 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 233 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 247 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr10:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b1 = p; }
			
#line 254 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 259 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 264 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 269 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 274 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 279 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 284 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 289 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 294 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 299 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 304 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 309 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 314 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 328 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr14:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 335 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 340 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 345 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 350 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 355 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 360 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 365 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 370 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 375 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 380 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 385 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 390 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 404 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr18:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 411 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 416 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 421 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 426 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 431 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 436 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 441 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 446 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 451 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 456 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 461 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 475 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr22:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 482 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 487 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 492 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 497 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 502 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 507 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 512 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 517 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 522 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 527 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 541 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr26:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 548 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 553 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 558 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 563 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 568 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 573 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 578 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 583 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 588 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 602 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr30:
				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 609 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 614 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 619 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 624 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 629 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 634 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 639 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 644 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 658 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr34:
				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 665 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 670 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 675 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 680 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 685 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 690 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 695 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 709 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr38:
				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 716 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 721 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 726 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 731 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 736 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 741 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 755 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr42:
				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 762 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 767 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 772 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 777 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 782 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 796 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr46:
				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 803 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 808 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 813 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 818 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 832 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr50:
				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 839 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 844 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 849 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 863 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr54:
				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 870 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 875 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 889 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr58:
				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 896 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 910 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr61:
				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 926 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st17;
			_ctr63:
				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a0 = p; }
			
#line 933 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b0 = p; }
			
#line 938 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a1 = p; }
			
#line 943 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b1 = p; }
			
#line 948 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 953 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 958 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 963 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 968 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 973 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 978 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 983 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 988 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 993 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 998 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 1003 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 1008 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 1022 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b0 = p; }
			
#line 1049 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a1 = p; }
			
#line 1054 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b1 = p; }
			
#line 1059 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 1064 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 1069 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 1074 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 1079 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 1084 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 1089 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 1094 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 1099 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 1104 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 1109 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 1114 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st1;
			_ctr64:
				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a0 = p; }
			
#line 1121 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b0 = p; }
			
#line 1126 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a1 = p; }
			
#line 1131 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b1 = p; }
			
#line 1136 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 1141 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 1146 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 1151 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 1156 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 1161 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 1166 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 1171 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 1176 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 1181 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 1186 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 1191 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b0 = p; }
			
#line 1215 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a1 = p; }
			
#line 1220 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b1 = p; }
			
#line 1225 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 1230 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 1235 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 1240 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 1245 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 1250 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 1255 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 1260 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 1265 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 1270 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 1275 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 1280 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 1285 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st2;
			_ctr8:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a1 = p; }
			
#line 1292 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b1 = p; }
			
#line 1297 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 1302 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 1307 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 1312 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 1317 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 1322 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 1327 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 1332 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 1337 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 1342 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 1347 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 1352 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 1357 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st2;
			_ctr65:
				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a0 = p; }
			
#line 1364 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b0 = p; }
			
#line 1369 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a1 = p; }
			
#line 1374 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b1 = p; }
			
#line 1379 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 1384 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 1389 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 1394 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 1399 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 1404 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 1409 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 1414 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 1419 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 1424 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 1429 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 1434 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 1439 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a1 = p; }
			
#line 1463 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b1 = p; }
			
#line 1468 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 1473 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 1478 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 1483 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 1488 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 1493 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 1498 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 1503 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 1508 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 1513 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 1518 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 1523 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st3;
			_ctr11:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b1 = p; }
			
#line 1530 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 1535 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 1540 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 1545 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 1550 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 1555 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 1560 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 1565 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 1570 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 1575 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 1580 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 1585 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b1 = p; }
			
#line 1609 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 1614 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 1619 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 1624 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 1629 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 1634 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 1639 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 1644 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 1649 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 1654 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 1659 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 1664 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 1669 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st4;
			_ctr16:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 1676 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 1681 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 1686 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 1691 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 1696 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 1701 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 1706 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 1711 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 1716 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 1721 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 1726 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 1731 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a2 = p; }
			
#line 1755 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 1760 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 1765 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 1770 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 1775 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 1780 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 1785 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 1790 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 1795 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 1800 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 1805 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st5;
			_ctr19:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 1812 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 1817 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 1822 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 1827 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 1832 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 1837 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 1842 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 1847 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 1852 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 1857 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b2 = p; }
			
#line 1881 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 1886 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 1891 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 1896 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 1901 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 1906 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 1911 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 1916 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 1921 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 1926 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 1931 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st6;
			_ctr24:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 1938 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 1943 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 1948 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 1953 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 1958 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 1963 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 1968 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 1973 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 1978 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 1983 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a3 = p; }
			
#line 2007 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 2012 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 2017 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 2022 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 2027 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 2032 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 2037 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2042 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2047 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st7;
			_ctr27:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 2054 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 2059 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 2064 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 2069 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 2074 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 2079 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2084 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2089 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 14 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b3 = p; }
			
#line 2113 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 2118 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 2123 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 2128 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 2133 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 2138 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2143 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2148 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 2153 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st8;
			_ctr32:
				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 2160 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 2165 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 2170 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 2175 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 2180 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2185 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2190 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 2195 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a4 = p; }
			
#line 2219 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 2224 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 2229 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 2234 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 2239 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2244 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2249 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st9;
			_ctr35:
				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 2256 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 2261 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 2266 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 2271 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2276 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2281 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 15 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b4 = p; }
			
#line 2305 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 2310 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 2315 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 2320 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2325 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2330 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 2335 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st10;
			_ctr40:
				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 2342 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 2347 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 2352 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2357 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2362 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 2367 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a5 = p; }
			
#line 2391 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 2396 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 2401 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2406 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2411 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st11;
			_ctr43:
				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 2418 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 2423 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2428 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2433 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 16 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b5 = p; }
			
#line 2457 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 2462 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2467 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2472 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 2477 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st12;
			_ctr48:
				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 2484 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2489 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2494 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 2499 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a6 = p; }
			
#line 2523 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2528 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2533 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st13;
			_ctr51:
				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2540 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2545 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 17 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b6 = p; }
			
#line 2569 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2574 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 2579 "gen/ragel/submatch_26__cat8_0.cc"

			goto _st14;
			_ctr56:
				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2586 "gen/ragel/submatch_26__cat8_0.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 2591 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				a7 = p; }
			
#line 2615 "gen/ragel/submatch_26__cat8_0.cc"

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
#line 18 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"
				b7 = p; }
			
#line 2639 "gen/ragel/submatch_26__cat8_0.cc"

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
		
#line 44 "../../../benchmarks/c/src/ragel/submatch_26__cat8_0.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH_AND_TEST()
	
} // namespace ragel_submatch_26__cat8_0
