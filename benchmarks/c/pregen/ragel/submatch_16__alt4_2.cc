#line 1 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
#include "ragel/base.h"

namespace ragel_submatch_16__alt4_2 {
	
	const char *delim = "\n";
	
	
#line 49 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"

	

#line 11 "gen/ragel/submatch_16__alt4_2.cc"
static const int m_start = 9;
	static const int m_first_final = 9;
	static const int m_error = 0;
	
	static const int m_en_main = 9;
	
	
#line 51 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"

	
	static int lex(Input *in, int count) {
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
		

#line 34 "gen/ragel/submatch_16__alt4_2.cc"
	{
			cs = (int)m_start;
		}
		
#line 67 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"


#line 39 "gen/ragel/submatch_16__alt4_2.cc"
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
#line 22 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a2 = p; b1 = b2 = NULL; }
			
#line 67 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b3 = p; }
			
#line 72 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b4 = p; a3 = a4 = NULL; }
			
#line 77 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a3 = p; }
			
#line 82 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a4 = p; b3 = b4 = NULL; }
			
#line 87 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b5 = p; }
			
#line 92 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b6 = p; a5 = a6 = NULL; }
			
#line 97 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 30 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a5 = p; }
			
#line 102 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 30 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a6 = p; b5 = b6 = NULL; }
			
#line 107 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b7 = p; }
			
#line 112 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b8 = p; a7 = a8 = NULL; }
			
#line 117 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a7 = p; }
			
#line 122 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a8 = p; b7 = b8 = NULL; }
			
#line 127 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 36 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				if (a5)      { OUTC('A'); OUTS(a5, a6); }
				else if (b5) { OUTC('B'); OUTS(b5, b6); }
				if (a7)      { OUTC('A'); OUTS(a7, a8); }
				else if (b7) { OUTC('B'); OUTS(b7, b8); }
				OUTC('\n');
			}
			
#line 142 "gen/ragel/submatch_16__alt4_2.cc"

			goto _st9;
			_ctr5:
				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b4 = p; a3 = a4 = NULL; }
			
#line 149 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b5 = p; }
			
#line 154 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b6 = p; a5 = a6 = NULL; }
			
#line 159 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 30 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a5 = p; }
			
#line 164 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 30 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a6 = p; b5 = b6 = NULL; }
			
#line 169 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b7 = p; }
			
#line 174 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b8 = p; a7 = a8 = NULL; }
			
#line 179 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a7 = p; }
			
#line 184 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a8 = p; b7 = b8 = NULL; }
			
#line 189 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 36 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				if (a5)      { OUTC('A'); OUTS(a5, a6); }
				else if (b5) { OUTC('B'); OUTS(b5, b6); }
				if (a7)      { OUTC('A'); OUTS(a7, a8); }
				else if (b7) { OUTC('B'); OUTS(b7, b8); }
				OUTC('\n');
			}
			
#line 204 "gen/ragel/submatch_16__alt4_2.cc"

			goto _st9;
			_ctr8:
				{
#line 30 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a6 = p; b5 = b6 = NULL; }
			
#line 211 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b7 = p; }
			
#line 216 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b8 = p; a7 = a8 = NULL; }
			
#line 221 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a7 = p; }
			
#line 226 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a8 = p; b7 = b8 = NULL; }
			
#line 231 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 36 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				if (a5)      { OUTC('A'); OUTS(a5, a6); }
				else if (b5) { OUTC('B'); OUTS(b5, b6); }
				if (a7)      { OUTC('A'); OUTS(a7, a8); }
				else if (b7) { OUTC('B'); OUTS(b7, b8); }
				OUTC('\n');
			}
			
#line 246 "gen/ragel/submatch_16__alt4_2.cc"

			goto _st9;
			_ctr11:
				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b8 = p; a7 = a8 = NULL; }
			
#line 253 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 36 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				if (a5)      { OUTC('A'); OUTS(a5, a6); }
				else if (b5) { OUTC('B'); OUTS(b5, b6); }
				if (a7)      { OUTC('A'); OUTS(a7, a8); }
				else if (b7) { OUTC('B'); OUTS(b7, b8); }
				OUTC('\n');
			}
			
#line 268 "gen/ragel/submatch_16__alt4_2.cc"

			goto _st9;
			_ctr13:
				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b2 = p; a1 = a2 = NULL; }
			
#line 275 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b3 = p; }
			
#line 280 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b4 = p; a3 = a4 = NULL; }
			
#line 285 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a3 = p; }
			
#line 290 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a4 = p; b3 = b4 = NULL; }
			
#line 295 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b5 = p; }
			
#line 300 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b6 = p; a5 = a6 = NULL; }
			
#line 305 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 30 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a5 = p; }
			
#line 310 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 30 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a6 = p; b5 = b6 = NULL; }
			
#line 315 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b7 = p; }
			
#line 320 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b8 = p; a7 = a8 = NULL; }
			
#line 325 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a7 = p; }
			
#line 330 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a8 = p; b7 = b8 = NULL; }
			
#line 335 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 36 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				if (a5)      { OUTC('A'); OUTS(a5, a6); }
				else if (b5) { OUTC('B'); OUTS(b5, b6); }
				if (a7)      { OUTC('A'); OUTS(a7, a8); }
				else if (b7) { OUTC('B'); OUTS(b7, b8); }
				OUTC('\n');
			}
			
#line 350 "gen/ragel/submatch_16__alt4_2.cc"

			goto _st9;
			_ctr16:
				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a4 = p; b3 = b4 = NULL; }
			
#line 357 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b5 = p; }
			
#line 362 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b6 = p; a5 = a6 = NULL; }
			
#line 367 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 30 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a5 = p; }
			
#line 372 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 30 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a6 = p; b5 = b6 = NULL; }
			
#line 377 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b7 = p; }
			
#line 382 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b8 = p; a7 = a8 = NULL; }
			
#line 387 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a7 = p; }
			
#line 392 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a8 = p; b7 = b8 = NULL; }
			
#line 397 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 36 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				if (a5)      { OUTC('A'); OUTS(a5, a6); }
				else if (b5) { OUTC('B'); OUTS(b5, b6); }
				if (a7)      { OUTC('A'); OUTS(a7, a8); }
				else if (b7) { OUTC('B'); OUTS(b7, b8); }
				OUTC('\n');
			}
			
#line 412 "gen/ragel/submatch_16__alt4_2.cc"

			goto _st9;
			_ctr19:
				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b6 = p; a5 = a6 = NULL; }
			
#line 419 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b7 = p; }
			
#line 424 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b8 = p; a7 = a8 = NULL; }
			
#line 429 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a7 = p; }
			
#line 434 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a8 = p; b7 = b8 = NULL; }
			
#line 439 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 36 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				if (a5)      { OUTC('A'); OUTS(a5, a6); }
				else if (b5) { OUTC('B'); OUTS(b5, b6); }
				if (a7)      { OUTC('A'); OUTS(a7, a8); }
				else if (b7) { OUTC('B'); OUTS(b7, b8); }
				OUTC('\n');
			}
			
#line 454 "gen/ragel/submatch_16__alt4_2.cc"

			goto _st9;
			_ctr22:
				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a8 = p; b7 = b8 = NULL; }
			
#line 461 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 36 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				if (a5)      { OUTC('A'); OUTS(a5, a6); }
				else if (b5) { OUTC('B'); OUTS(b5, b6); }
				if (a7)      { OUTC('A'); OUTS(a7, a8); }
				else if (b7) { OUTC('B'); OUTS(b7, b8); }
				OUTC('\n');
			}
			
#line 476 "gen/ragel/submatch_16__alt4_2.cc"

			goto _st9;
			_ctr24:
				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b1 = p; }
			
#line 483 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b2 = p; a1 = a2 = NULL; }
			
#line 488 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 22 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a1 = p; }
			
#line 493 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 22 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a2 = p; b1 = b2 = NULL; }
			
#line 498 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b3 = p; }
			
#line 503 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b4 = p; a3 = a4 = NULL; }
			
#line 508 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a3 = p; }
			
#line 513 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a4 = p; b3 = b4 = NULL; }
			
#line 518 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b5 = p; }
			
#line 523 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b6 = p; a5 = a6 = NULL; }
			
#line 528 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 30 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a5 = p; }
			
#line 533 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 30 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a6 = p; b5 = b6 = NULL; }
			
#line 538 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b7 = p; }
			
#line 543 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b8 = p; a7 = a8 = NULL; }
			
#line 548 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a7 = p; }
			
#line 553 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a8 = p; b7 = b8 = NULL; }
			
#line 558 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 36 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				if (a5)      { OUTC('A'); OUTS(a5, a6); }
				else if (b5) { OUTC('B'); OUTS(b5, b6); }
				if (a7)      { OUTC('A'); OUTS(a7, a8); }
				else if (b7) { OUTC('B'); OUTS(b7, b8); }
				OUTC('\n');
			}
			
#line 573 "gen/ragel/submatch_16__alt4_2.cc"

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
#line 22 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a1 = p; }
			
#line 600 "gen/ragel/submatch_16__alt4_2.cc"

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
#line 22 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a2 = p; b1 = b2 = NULL; }
			
#line 624 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b3 = p; }
			
#line 629 "gen/ragel/submatch_16__alt4_2.cc"

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
#line 25 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b4 = p; a3 = a4 = NULL; }
			
#line 653 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 30 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a5 = p; }
			
#line 658 "gen/ragel/submatch_16__alt4_2.cc"

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
#line 30 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a6 = p; b5 = b6 = NULL; }
			
#line 682 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 33 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b7 = p; }
			
#line 687 "gen/ragel/submatch_16__alt4_2.cc"

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
#line 21 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b1 = p; }
			
#line 708 "gen/ragel/submatch_16__alt4_2.cc"

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
#line 21 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b2 = p; a1 = a2 = NULL; }
			
#line 732 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a3 = p; }
			
#line 737 "gen/ragel/submatch_16__alt4_2.cc"

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
#line 26 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a4 = p; b3 = b4 = NULL; }
			
#line 761 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b5 = p; }
			
#line 766 "gen/ragel/submatch_16__alt4_2.cc"

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
#line 29 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				b6 = p; a5 = a6 = NULL; }
			
#line 790 "gen/ragel/submatch_16__alt4_2.cc"

				{
#line 34 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"
				a7 = p; }
			
#line 795 "gen/ragel/submatch_16__alt4_2.cc"

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
		
#line 68 "../../../benchmarks/c/src/ragel/submatch_16__alt4_2.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH_AND_TEST()
	
} // namespace ragel_submatch_16__alt4_2
