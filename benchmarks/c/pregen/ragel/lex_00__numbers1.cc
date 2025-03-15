#line 1 "../../../benchmarks/c/src/ragel/lex_00__numbers1.rl"
#include "ragel/base.h"

namespace ragel_lex_00__numbers1 {
	
	const char *delim = "\n";
	
	
#line 13 "../../../benchmarks/c/src/ragel/lex_00__numbers1.rl"

	

#line 11 "gen/ragel/lex_00__numbers1.cc"
static const int lex_numbers_start = 2;
	static const int lex_numbers_first_final = 2;
	static const int lex_numbers_error = 0;
	
	static const int lex_numbers_en_main = 2;
	
	
#line 15 "../../../benchmarks/c/src/ragel/lex_00__numbers1.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *ts = in->ts;
		char *te = in->te;
		char *pe = in->pe;
		int act = in->act;
		int cs;
		

#line 28 "gen/ragel/lex_00__numbers1.cc"
	{
			cs = (int)lex_numbers_start;
			ts = 0;
			te = 0;
		}
		
#line 25 "../../../benchmarks/c/src/ragel/lex_00__numbers1.rl"


#line 35 "gen/ragel/lex_00__numbers1.cc"
{
			switch ( cs ) {
				case 2:
				goto st_case_2;
				case 0:
				goto st_case_0;
				case 1:
				goto st_case_1;
			}
			_ctr2:
				{
#line 12 "../../../benchmarks/c/src/ragel/lex_00__numbers1.rl"
				{te = p+1;{
#line 12 "../../../benchmarks/c/src/ragel/lex_00__numbers1.rl"
						OUTS(ts, te); }
				}}
			
#line 52 "gen/ragel/lex_00__numbers1.cc"

			goto _st2;
			_st2:
				{
#line 1 "NONE"
				{ts = 0;}}
			
#line 59 "gen/ragel/lex_00__numbers1.cc"

			p+= 1;
			st_case_2:
			if ( p == pe )
				goto _out2;
				{
#line 1 "NONE"
				{ts = p;}}
			
#line 68 "gen/ragel/lex_00__numbers1.cc"

			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st1;
			}
			goto _st0;
			_st0:
			st_case_0:
			goto _out0;
			_st1:
			p+= 1;
			st_case_1:
			if ( p == pe )
				goto _out1;
			if ( ( (*( p))) == 10 ) {
				goto _ctr2;
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st1;
			}
			goto _st0;
			_out2: cs = 2; goto _out; 
			_out0: cs = 0; goto _out; 
			_out1: cs = 1; goto _out; 
			_out: {}
		}
		
#line 26 "../../../benchmarks/c/src/ragel/lex_00__numbers1.rl"

		
		in->p = p;
		in->ts = ts;
		in->te = te;
		in->pe = pe;
		in->act = act;
		
		return count;
	}
	
	RAGEL_BENCH_AND_TEST()
	
} // namespace ragel_lex_00__numbers1
