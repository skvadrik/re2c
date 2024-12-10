#line 1 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"
#include "ragel/base.h"

namespace ragel_submatch_10__alt1_2 {
	
	const char *delim = "\n";
	
	
#line 23 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"

	

#line 11 "gen/ragel/submatch_10__alt1_2.cc"
static const int m_start = 3;
	static const int m_first_final = 3;
	static const int m_error = 0;
	
	static const int m_en_main = 3;
	
	
#line 25 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *pe = in->pe;
		const char
		*a1, *b1,
		*a2, *b2;
		int cs;
		

#line 28 "gen/ragel/submatch_10__alt1_2.cc"
	{
			cs = (int)m_start;
		}
		
#line 35 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"


#line 33 "gen/ragel/submatch_10__alt1_2.cc"
{
			switch ( cs ) {
				case 3:
				goto st_case_3;
				case 0:
				goto st_case_0;
				case 1:
				goto st_case_1;
				case 2:
				goto st_case_2;
			}
			_ctr2:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"
				a2 = p; b1 = b2 = NULL; }
			
#line 49 "gen/ragel/submatch_10__alt1_2.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				OUTC('\n');
			}
			
#line 58 "gen/ragel/submatch_10__alt1_2.cc"

			goto _st3;
			_ctr4:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"
				b2 = p; a1 = a2 = NULL; }
			
#line 65 "gen/ragel/submatch_10__alt1_2.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				OUTC('\n');
			}
			
#line 74 "gen/ragel/submatch_10__alt1_2.cc"

			goto _st3;
			_ctr6:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"
				b1 = p; }
			
#line 81 "gen/ragel/submatch_10__alt1_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"
				b2 = p; a1 = a2 = NULL; }
			
#line 86 "gen/ragel/submatch_10__alt1_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"
				a1 = p; }
			
#line 91 "gen/ragel/submatch_10__alt1_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"
				a2 = p; b1 = b2 = NULL; }
			
#line 96 "gen/ragel/submatch_10__alt1_2.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"
				
				if (a1)      { OUTC('A'); OUTS(a1, a2); }
				else if (b1) { OUTC('B'); OUTS(b1, b2); }
				OUTC('\n');
			}
			
#line 105 "gen/ragel/submatch_10__alt1_2.cc"

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
				case 97: {
					goto _ctr7;
				}
				case 98: {
					goto _ctr8;
				}
			}
			goto _st0;
			_st0:
			st_case_0:
			goto _out0;
			_ctr7:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"
				a1 = p; }
			
#line 132 "gen/ragel/submatch_10__alt1_2.cc"

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
			_ctr8:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"
				b1 = p; }
			
#line 153 "gen/ragel/submatch_10__alt1_2.cc"

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
			_out3: cs = 3; goto _out; 
			_out0: cs = 0; goto _out; 
			_out1: cs = 1; goto _out; 
			_out2: cs = 2; goto _out; 
			_out: {}
		}
		
#line 36 "../../../benchmarks/c/src/ragel/submatch_10__alt1_2.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH()
	RAGEL_TEST()
	
} // namespace ragel_submatch_10__alt1_2
