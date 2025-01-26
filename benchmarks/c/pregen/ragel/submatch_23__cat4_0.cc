#line 1 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
#include "ragel/base.h"

namespace ragel_submatch_23__cat4_0 {
	
	const char *delim = "\n";
	
	
#line 23 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"

	

#line 11 "gen/ragel/submatch_23__cat4_0.cc"
static const int abcd_start = 9;
	static const int abcd_first_final = 9;
	static const int abcd_error = 0;
	
	static const int abcd_en_main = 9;
	
	
#line 25 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *pe = in->pe;
		const char
		*a0, *a1, *a2, *a3,
		*b0, *b1, *b2, *b3;
		int cs;
		

#line 28 "gen/ragel/submatch_23__cat4_0.cc"
	{
			cs = (int)abcd_start;
		}
		
#line 35 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"


#line 33 "gen/ragel/submatch_23__cat4_0.cc"
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
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b0 = p; }
			
#line 61 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a1 = p; }
			
#line 66 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b1 = p; }
			
#line 71 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 76 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 81 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 86 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 91 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, p + 1);
			}
			
#line 101 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st9;
			_ctr6:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a1 = p; }
			
#line 108 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b1 = p; }
			
#line 113 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 118 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 123 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 128 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 133 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, p + 1);
			}
			
#line 143 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st9;
			_ctr10:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b1 = p; }
			
#line 150 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 155 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 160 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 165 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 170 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, p + 1);
			}
			
#line 180 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st9;
			_ctr14:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 187 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 192 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 197 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 202 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, p + 1);
			}
			
#line 212 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st9;
			_ctr18:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 219 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 224 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 229 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, p + 1);
			}
			
#line 239 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st9;
			_ctr22:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 246 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 251 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, p + 1);
			}
			
#line 261 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st9;
			_ctr26:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 268 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, p + 1);
			}
			
#line 278 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st9;
			_ctr29:
				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, p + 1);
			}
			
#line 290 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st9;
			_ctr31:
				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a0 = p; }
			
#line 297 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b0 = p; }
			
#line 302 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a1 = p; }
			
#line 307 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b1 = p; }
			
#line 312 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 317 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 322 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 327 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 332 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, p + 1);
			}
			
#line 342 "gen/ragel/submatch_23__cat4_0.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b0 = p; }
			
#line 369 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a1 = p; }
			
#line 374 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b1 = p; }
			
#line 379 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 384 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 389 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 394 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st1;
			_ctr32:
				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a0 = p; }
			
#line 401 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b0 = p; }
			
#line 406 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a1 = p; }
			
#line 411 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b1 = p; }
			
#line 416 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 421 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 426 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 431 "gen/ragel/submatch_23__cat4_0.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b0 = p; }
			
#line 455 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a1 = p; }
			
#line 460 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b1 = p; }
			
#line 465 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 470 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 475 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 480 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 485 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st2;
			_ctr8:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a1 = p; }
			
#line 492 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b1 = p; }
			
#line 497 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 502 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 507 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 512 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 517 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st2;
			_ctr33:
				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a0 = p; }
			
#line 524 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b0 = p; }
			
#line 529 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a1 = p; }
			
#line 534 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b1 = p; }
			
#line 539 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 544 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 549 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 554 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 559 "gen/ragel/submatch_23__cat4_0.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a1 = p; }
			
#line 583 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b1 = p; }
			
#line 588 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 593 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 598 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 603 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st3;
			_ctr11:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b1 = p; }
			
#line 610 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 615 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 620 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 625 "gen/ragel/submatch_23__cat4_0.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b1 = p; }
			
#line 649 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 654 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 659 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 664 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 669 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st4;
			_ctr16:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 676 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 681 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 686 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 691 "gen/ragel/submatch_23__cat4_0.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a2 = p; }
			
#line 715 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 720 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 725 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st5;
			_ctr19:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 732 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 737 "gen/ragel/submatch_23__cat4_0.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b2 = p; }
			
#line 761 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 766 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 771 "gen/ragel/submatch_23__cat4_0.cc"

			goto _st6;
			_ctr24:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 778 "gen/ragel/submatch_23__cat4_0.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 783 "gen/ragel/submatch_23__cat4_0.cc"

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
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				a3 = p; }
			
#line 807 "gen/ragel/submatch_23__cat4_0.cc"

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
#line 14 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"
				b3 = p; }
			
#line 831 "gen/ragel/submatch_23__cat4_0.cc"

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
		
#line 36 "../../../benchmarks/c/src/ragel/submatch_23__cat4_0.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH_AND_TEST()
	
} // namespace ragel_submatch_23__cat4_0
