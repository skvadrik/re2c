#line 1 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
#include "ragel/base.h"

namespace ragel_submatch_14__alt2_4 {
	
	const char *delim = "\n";
	
	
#line 44 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"

	

#line 11 "gen/ragel/submatch_14__alt2_4.cc"
static const int m_start = 9;
	static const int m_first_final = 9;
	static const int m_error = 0;
	
	static const int m_en_main = 9;
	
	
#line 46 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *pe = in->pe;
		const char
		*a1, *b1, *c1, *d1,
		*a2, *b2, *c2, *d2,
		*a3, *b3, *c3, *d3,
		*a4, *b4, *c4, *d4;
		int cs;
		

#line 30 "gen/ragel/submatch_14__alt2_4.cc"
	{
			cs = (int)m_start;
		}
		
#line 58 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"


#line 35 "gen/ragel/submatch_14__alt2_4.cc"
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
#line 23 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
			
#line 63 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b3 = p; }
			
#line 68 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
			
#line 73 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c3 = p; }
			
#line 78 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
			
#line 83 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 28 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d3 = p; }
			
#line 88 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 28 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
			
#line 93 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a3 = p; }
			
#line 98 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
			
#line 103 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 31 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				else if (c1) { OUTC('C'); OUTS(c1, c2); }
				else if (d1) { OUTC('D'); OUTS(d1, d2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				else if (c3) { OUTC('C'); OUTS(c3, c4); }
				else if (d3) { OUTC('D'); OUTS(d3, d4); }
				OUTC('\n');
			}
			
#line 118 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st9;
			_ctr7:
				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
			
#line 125 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 31 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				else if (c1) { OUTC('C'); OUTS(c1, c2); }
				else if (d1) { OUTC('D'); OUTS(d1, d2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				else if (c3) { OUTC('C'); OUTS(c3, c4); }
				else if (d3) { OUTC('D'); OUTS(d3, d4); }
				OUTC('\n');
			}
			
#line 140 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st9;
			_ctr9:
				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
			
#line 147 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 31 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				else if (c1) { OUTC('C'); OUTS(c1, c2); }
				else if (d1) { OUTC('D'); OUTS(d1, d2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				else if (c3) { OUTC('C'); OUTS(c3, c4); }
				else if (d3) { OUTC('D'); OUTS(d3, d4); }
				OUTC('\n');
			}
			
#line 162 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st9;
			_ctr11:
				{
#line 28 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
			
#line 169 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 31 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				else if (c1) { OUTC('C'); OUTS(c1, c2); }
				else if (d1) { OUTC('D'); OUTS(d1, d2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				else if (c3) { OUTC('C'); OUTS(c3, c4); }
				else if (d3) { OUTC('D'); OUTS(d3, d4); }
				OUTC('\n');
			}
			
#line 184 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st9;
			_ctr13:
				{
#line 20 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
			
#line 191 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b3 = p; }
			
#line 196 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
			
#line 201 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c3 = p; }
			
#line 206 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
			
#line 211 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 28 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d3 = p; }
			
#line 216 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 28 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
			
#line 221 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a3 = p; }
			
#line 226 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
			
#line 231 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 31 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				else if (c1) { OUTC('C'); OUTS(c1, c2); }
				else if (d1) { OUTC('D'); OUTS(d1, d2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				else if (c3) { OUTC('C'); OUTS(c3, c4); }
				else if (d3) { OUTC('D'); OUTS(d3, d4); }
				OUTC('\n');
			}
			
#line 246 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st9;
			_ctr18:
				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
			
#line 253 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 31 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				else if (c1) { OUTC('C'); OUTS(c1, c2); }
				else if (d1) { OUTC('D'); OUTS(d1, d2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				else if (c3) { OUTC('C'); OUTS(c3, c4); }
				else if (d3) { OUTC('D'); OUTS(d3, d4); }
				OUTC('\n');
			}
			
#line 268 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st9;
			_ctr20:
				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
			
#line 275 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b3 = p; }
			
#line 280 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
			
#line 285 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c3 = p; }
			
#line 290 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
			
#line 295 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 28 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d3 = p; }
			
#line 300 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 28 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
			
#line 305 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a3 = p; }
			
#line 310 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
			
#line 315 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 31 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				else if (c1) { OUTC('C'); OUTS(c1, c2); }
				else if (d1) { OUTC('D'); OUTS(d1, d2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				else if (c3) { OUTC('C'); OUTS(c3, c4); }
				else if (d3) { OUTC('D'); OUTS(d3, d4); }
				OUTC('\n');
			}
			
#line 330 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st9;
			_ctr25:
				{
#line 22 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
			
#line 337 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b3 = p; }
			
#line 342 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
			
#line 347 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c3 = p; }
			
#line 352 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
			
#line 357 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 28 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d3 = p; }
			
#line 362 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 28 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
			
#line 367 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a3 = p; }
			
#line 372 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
			
#line 377 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 31 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				else if (c1) { OUTC('C'); OUTS(c1, c2); }
				else if (d1) { OUTC('D'); OUTS(d1, d2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				else if (c3) { OUTC('C'); OUTS(c3, c4); }
				else if (d3) { OUTC('D'); OUTS(d3, d4); }
				OUTC('\n');
			}
			
#line 392 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st9;
			_ctr30:
				{
#line 20 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b1 = p; }
			
#line 399 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 20 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
			
#line 404 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c1 = p; }
			
#line 409 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
			
#line 414 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 22 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d1 = p; }
			
#line 419 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 22 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
			
#line 424 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 23 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a1 = p; }
			
#line 429 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 23 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
			
#line 434 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b3 = p; }
			
#line 439 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
			
#line 444 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c3 = p; }
			
#line 449 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
			
#line 454 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 28 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d3 = p; }
			
#line 459 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 28 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
			
#line 464 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a3 = p; }
			
#line 469 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
			
#line 474 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 31 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				else if (c1) { OUTC('C'); OUTS(c1, c2); }
				else if (d1) { OUTC('D'); OUTS(d1, d2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				else if (c3) { OUTC('C'); OUTS(c3, c4); }
				else if (d3) { OUTC('D'); OUTS(d3, d4); }
				OUTC('\n');
			}
			
#line 489 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st9;
			_st9:
			p+= 1;
			st_case_9:
			if ( p == pe )
				goto _out9;
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
				case 99: {
					goto _ctr33;
				}
				case 100: {
					goto _ctr34;
				}
			}
			goto _st0;
			_st0:
			st_case_0:
			goto _out0;
			_ctr31:
				{
#line 23 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a1 = p; }
			
#line 522 "gen/ragel/submatch_14__alt2_4.cc"

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
				case 99: {
					goto _ctr4;
				}
				case 100: {
					goto _ctr5;
				}
			}
			goto _st0;
			_ctr3:
				{
#line 23 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
			
#line 552 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b3 = p; }
			
#line 557 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st2;
			_ctr22:
				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
			
#line 564 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b3 = p; }
			
#line 569 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st2;
			_ctr27:
				{
#line 22 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
			
#line 576 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 26 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b3 = p; }
			
#line 581 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st2;
			_st2:
			p+= 1;
			st_case_2:
			if ( p == pe )
				goto _out2;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr7;
				}
				case 98: {
					goto _st2;
				}
			}
			goto _st0;
			_ctr4:
				{
#line 23 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
			
#line 602 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c3 = p; }
			
#line 607 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st3;
			_ctr15:
				{
#line 20 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
			
#line 614 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c3 = p; }
			
#line 619 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st3;
			_ctr28:
				{
#line 22 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
			
#line 626 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c3 = p; }
			
#line 631 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st3;
			_st3:
			p+= 1;
			st_case_3:
			if ( p == pe )
				goto _out3;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr9;
				}
				case 99: {
					goto _st3;
				}
			}
			goto _st0;
			_ctr5:
				{
#line 23 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
			
#line 652 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 28 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d3 = p; }
			
#line 657 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st4;
			_ctr16:
				{
#line 20 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
			
#line 664 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 28 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d3 = p; }
			
#line 669 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st4;
			_ctr23:
				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
			
#line 676 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 28 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d3 = p; }
			
#line 681 "gen/ragel/submatch_14__alt2_4.cc"

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
				case 100: {
					goto _st4;
				}
			}
			goto _st0;
			_ctr32:
				{
#line 20 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b1 = p; }
			
#line 702 "gen/ragel/submatch_14__alt2_4.cc"

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
				case 99: {
					goto _ctr15;
				}
				case 100: {
					goto _ctr16;
				}
			}
			goto _st0;
			_ctr14:
				{
#line 20 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
			
#line 732 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a3 = p; }
			
#line 737 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st6;
			_ctr21:
				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
			
#line 744 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a3 = p; }
			
#line 749 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st6;
			_ctr26:
				{
#line 22 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
			
#line 756 "gen/ragel/submatch_14__alt2_4.cc"

				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				a3 = p; }
			
#line 761 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st6;
			_st6:
			p+= 1;
			st_case_6:
			if ( p == pe )
				goto _out6;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr18;
				}
				case 97: {
					goto _st6;
				}
			}
			goto _st0;
			_ctr33:
				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				c1 = p; }
			
#line 782 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st7;
			_st7:
			p+= 1;
			st_case_7:
			if ( p == pe )
				goto _out7;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr20;
				}
				case 97: {
					goto _ctr21;
				}
				case 98: {
					goto _ctr22;
				}
				case 99: {
					goto _st7;
				}
				case 100: {
					goto _ctr23;
				}
			}
			goto _st0;
			_ctr34:
				{
#line 22 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"
				d1 = p; }
			
#line 812 "gen/ragel/submatch_14__alt2_4.cc"

			goto _st8;
			_st8:
			p+= 1;
			st_case_8:
			if ( p == pe )
				goto _out8;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr25;
				}
				case 97: {
					goto _ctr26;
				}
				case 98: {
					goto _ctr27;
				}
				case 99: {
					goto _ctr28;
				}
				case 100: {
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
		
#line 59 "../../../benchmarks/c/src/ragel/submatch_14__alt2_4.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH_AND_TEST()
	
} // namespace ragel_submatch_14__alt2_4
