#line 1 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
#include "ragel/base.h"

namespace ragel_submatch_11__alt1_4 {
	
	const char *delim = "\n";
	
	
#line 27 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"

	

#line 11 "gen/ragel/submatch_11__alt1_4.cc"
static const int m_start = 5;
	static const int m_first_final = 5;
	static const int m_error = 0;
	
	static const int m_en_main = 5;
	
	
#line 29 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *pe = in->pe;
		const char
		*a1, *b1, *c1, *d1,
		*a2, *b2, *c2, *d2;
		int cs;
		

#line 28 "gen/ragel/submatch_11__alt1_4.cc"
	{
			cs = (int)m_start;
		}
		
#line 39 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"


#line 33 "gen/ragel/submatch_11__alt1_4.cc"
{
			switch ( cs ) {
				case 5:
				goto st_case_5;
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
			}
			_ctr2:
				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
			
#line 53 "gen/ragel/submatch_11__alt1_4.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				else if (c1) { OUTC('C'); OUTS(c1, c2); }
				else if (d1) { OUTC('D'); OUTS(d1, d2); }
				OUTC('\n');
			}
			
#line 64 "gen/ragel/submatch_11__alt1_4.cc"

			goto _st5;
			_ctr4:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
			
#line 71 "gen/ragel/submatch_11__alt1_4.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				else if (c1) { OUTC('C'); OUTS(c1, c2); }
				else if (d1) { OUTC('D'); OUTS(d1, d2); }
				OUTC('\n');
			}
			
#line 82 "gen/ragel/submatch_11__alt1_4.cc"

			goto _st5;
			_ctr6:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
			
#line 89 "gen/ragel/submatch_11__alt1_4.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				else if (c1) { OUTC('C'); OUTS(c1, c2); }
				else if (d1) { OUTC('D'); OUTS(d1, d2); }
				OUTC('\n');
			}
			
#line 100 "gen/ragel/submatch_11__alt1_4.cc"

			goto _st5;
			_ctr8:
				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
			
#line 107 "gen/ragel/submatch_11__alt1_4.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				else if (c1) { OUTC('C'); OUTS(c1, c2); }
				else if (d1) { OUTC('D'); OUTS(d1, d2); }
				OUTC('\n');
			}
			
#line 118 "gen/ragel/submatch_11__alt1_4.cc"

			goto _st5;
			_ctr10:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				b1 = p; }
			
#line 125 "gen/ragel/submatch_11__alt1_4.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
			
#line 130 "gen/ragel/submatch_11__alt1_4.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				c1 = p; }
			
#line 135 "gen/ragel/submatch_11__alt1_4.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
			
#line 140 "gen/ragel/submatch_11__alt1_4.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				d1 = p; }
			
#line 145 "gen/ragel/submatch_11__alt1_4.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
			
#line 150 "gen/ragel/submatch_11__alt1_4.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				a1 = p; }
			
#line 155 "gen/ragel/submatch_11__alt1_4.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
			
#line 160 "gen/ragel/submatch_11__alt1_4.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				else if (c1) { OUTC('C'); OUTS(c1, c2); }
				else if (d1) { OUTC('D'); OUTS(d1, d2); }
				OUTC('\n');
			}
			
#line 171 "gen/ragel/submatch_11__alt1_4.cc"

			goto _st5;
			_st5:
			p+= 1;
			st_case_5:
			if ( p == pe )
				goto _out5;
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
				case 99: {
					goto _ctr13;
				}
				case 100: {
					goto _ctr14;
				}
			}
			goto _st0;
			_st0:
			st_case_0:
			goto _out0;
			_ctr11:
				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				a1 = p; }
			
#line 204 "gen/ragel/submatch_11__alt1_4.cc"

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
			}
			goto _st0;
			_ctr12:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				b1 = p; }
			
#line 225 "gen/ragel/submatch_11__alt1_4.cc"

			goto _st2;
			_st2:
			p+= 1;
			st_case_2:
			if ( p == pe )
				goto _out2;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr4;
				}
				case 98: {
					goto _st2;
				}
			}
			goto _st0;
			_ctr13:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				c1 = p; }
			
#line 246 "gen/ragel/submatch_11__alt1_4.cc"

			goto _st3;
			_st3:
			p+= 1;
			st_case_3:
			if ( p == pe )
				goto _out3;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr6;
				}
				case 99: {
					goto _st3;
				}
			}
			goto _st0;
			_ctr14:
				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"
				d1 = p; }
			
#line 267 "gen/ragel/submatch_11__alt1_4.cc"

			goto _st4;
			_st4:
			p+= 1;
			st_case_4:
			if ( p == pe )
				goto _out4;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr8;
				}
				case 100: {
					goto _st4;
				}
			}
			goto _st0;
			_out5: cs = 5; goto _out; 
			_out0: cs = 0; goto _out; 
			_out1: cs = 1; goto _out; 
			_out2: cs = 2; goto _out; 
			_out3: cs = 3; goto _out; 
			_out4: cs = 4; goto _out; 
			_out: {}
		}
		
#line 40 "../../../benchmarks/c/src/ragel/submatch_11__alt1_4.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH()
	RAGEL_TEST()
	
} // namespace ragel_submatch_11__alt1_4
