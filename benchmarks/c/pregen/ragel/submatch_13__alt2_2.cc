#line 1 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
#include "ragel/base.h"

namespace ragel_submatch_13__alt2_2 {
	
	const char *delim = "\n";
	
	
#line 36 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"

	

#line 11 "gen/ragel/submatch_13__alt2_2.cc"
static const int m_start = 5;
	static const int m_first_final = 5;
	static const int m_error = 0;
	
	static const int m_en_main = 5;
	
	
#line 38 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *pe = in->pe;
		const char
		*a1, *b1,
		*a2, *b2,
		*a3, *b3,
		*a4, *b4;
		int cs;
		

#line 30 "gen/ragel/submatch_13__alt2_2.cc"
	{
			cs = (int)m_start;
		}
		
#line 50 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"


#line 35 "gen/ragel/submatch_13__alt2_2.cc"
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
#line 21 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				a2 = p; b1 = b2 = NULL; }
			
#line 55 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 24 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				b3 = p; }
			
#line 60 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 24 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				b4 = p; a3 = a4 = NULL; }
			
#line 65 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				a3 = p; }
			
#line 70 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				a4 = p; b3 = b4 = NULL; }
			
#line 75 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				OUTC('\n');
			}
			
#line 86 "gen/ragel/submatch_13__alt2_2.cc"

			goto _st5;
			_ctr5:
				{
#line 24 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				b4 = p; a3 = a4 = NULL; }
			
#line 93 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				OUTC('\n');
			}
			
#line 104 "gen/ragel/submatch_13__alt2_2.cc"

			goto _st5;
			_ctr7:
				{
#line 20 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				b2 = p; a1 = a2 = NULL; }
			
#line 111 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 24 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				b3 = p; }
			
#line 116 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 24 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				b4 = p; a3 = a4 = NULL; }
			
#line 121 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				a3 = p; }
			
#line 126 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				a4 = p; b3 = b4 = NULL; }
			
#line 131 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				OUTC('\n');
			}
			
#line 142 "gen/ragel/submatch_13__alt2_2.cc"

			goto _st5;
			_ctr10:
				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				a4 = p; b3 = b4 = NULL; }
			
#line 149 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				OUTC('\n');
			}
			
#line 160 "gen/ragel/submatch_13__alt2_2.cc"

			goto _st5;
			_ctr12:
				{
#line 20 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				b1 = p; }
			
#line 167 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 20 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				b2 = p; a1 = a2 = NULL; }
			
#line 172 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				a1 = p; }
			
#line 177 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				a2 = p; b1 = b2 = NULL; }
			
#line 182 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 24 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				b3 = p; }
			
#line 187 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 24 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				b4 = p; a3 = a4 = NULL; }
			
#line 192 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				a3 = p; }
			
#line 197 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				a4 = p; b3 = b4 = NULL; }
			
#line 202 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				if (a3)      { OUTC('A'); OUTS(a3, a4); }
				else if (b3) { OUTC('B'); OUTS(b3, b4); }
				OUTC('\n');
			}
			
#line 213 "gen/ragel/submatch_13__alt2_2.cc"

			goto _st5;
			_st5:
			p+= 1;
			st_case_5:
			if ( p == pe )
				goto _out5;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr12;
				}
				case 97: {
					goto _ctr13;
				}
				case 98: {
					goto _ctr14;
				}
			}
			goto _st0;
			_st0:
			st_case_0:
			goto _out0;
			_ctr13:
				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				a1 = p; }
			
#line 240 "gen/ragel/submatch_13__alt2_2.cc"

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
#line 21 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				a2 = p; b1 = b2 = NULL; }
			
#line 264 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 24 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				b3 = p; }
			
#line 269 "gen/ragel/submatch_13__alt2_2.cc"

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
				case 98: {
					goto _st2;
				}
			}
			goto _st0;
			_ctr14:
				{
#line 20 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				b1 = p; }
			
#line 290 "gen/ragel/submatch_13__alt2_2.cc"

			goto _st3;
			_st3:
			p+= 1;
			st_case_3:
			if ( p == pe )
				goto _out3;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr7;
				}
				case 97: {
					goto _ctr8;
				}
				case 98: {
					goto _st3;
				}
			}
			goto _st0;
			_ctr8:
				{
#line 20 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				b2 = p; a1 = a2 = NULL; }
			
#line 314 "gen/ragel/submatch_13__alt2_2.cc"

				{
#line 25 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"
				a3 = p; }
			
#line 319 "gen/ragel/submatch_13__alt2_2.cc"

			goto _st4;
			_st4:
			p+= 1;
			st_case_4:
			if ( p == pe )
				goto _out4;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr10;
				}
				case 97: {
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
		
#line 51 "../../../benchmarks/c/src/ragel/submatch_13__alt2_2.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH_AND_TEST()
	
} // namespace ragel_submatch_13__alt2_2
