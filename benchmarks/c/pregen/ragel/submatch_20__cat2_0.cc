#line 1 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
#include "ragel/base.h"

namespace ragel_submatch_20__cat2_0 {
	
	const char *delim = "\n";
	
	
#line 19 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"

	

#line 11 "gen/ragel/submatch_20__cat2_0.cc"
static const int abcd_start = 5;
	static const int abcd_first_final = 5;
	static const int abcd_error = 0;
	
	static const int abcd_en_main = 5;
	
	
#line 21 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *pe = in->pe;
		const char
		*a0, *a1,
		*b0, *b1;
		int cs;
		

#line 28 "gen/ragel/submatch_20__cat2_0.cc"
	{
			cs = (int)abcd_start;
		}
		
#line 31 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"


#line 33 "gen/ragel/submatch_20__cat2_0.cc"
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
#line 11 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				b0 = p; }
			
#line 53 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				a1 = p; }
			
#line 58 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				b1 = p; }
			
#line 63 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, p + 1);
			}
			
#line 71 "gen/ragel/submatch_20__cat2_0.cc"

			goto _st5;
			_ctr6:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				a1 = p; }
			
#line 78 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				b1 = p; }
			
#line 83 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, p + 1);
			}
			
#line 91 "gen/ragel/submatch_20__cat2_0.cc"

			goto _st5;
			_ctr10:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				b1 = p; }
			
#line 98 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, p + 1);
			}
			
#line 106 "gen/ragel/submatch_20__cat2_0.cc"

			goto _st5;
			_ctr13:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, p + 1);
			}
			
#line 116 "gen/ragel/submatch_20__cat2_0.cc"

			goto _st5;
			_ctr15:
				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				a0 = p; }
			
#line 123 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				b0 = p; }
			
#line 128 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				a1 = p; }
			
#line 133 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				b1 = p; }
			
#line 138 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, p + 1);
			}
			
#line 146 "gen/ragel/submatch_20__cat2_0.cc"

			goto _st5;
			_st5:
			p+= 1;
			st_case_5:
			if ( p == pe )
				goto _out5;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr15;
				}
				case 97: {
					goto _ctr16;
				}
				case 98: {
					goto _ctr17;
				}
			}
			goto _st0;
			_st0:
			st_case_0:
			goto _out0;
			_ctr3:
				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				b0 = p; }
			
#line 173 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				a1 = p; }
			
#line 178 "gen/ragel/submatch_20__cat2_0.cc"

			goto _st1;
			_ctr16:
				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				a0 = p; }
			
#line 185 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				b0 = p; }
			
#line 190 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				a1 = p; }
			
#line 195 "gen/ragel/submatch_20__cat2_0.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				b0 = p; }
			
#line 219 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				a1 = p; }
			
#line 224 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				b1 = p; }
			
#line 229 "gen/ragel/submatch_20__cat2_0.cc"

			goto _st2;
			_ctr8:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				a1 = p; }
			
#line 236 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				b1 = p; }
			
#line 241 "gen/ragel/submatch_20__cat2_0.cc"

			goto _st2;
			_ctr17:
				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				a0 = p; }
			
#line 248 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				b0 = p; }
			
#line 253 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				a1 = p; }
			
#line 258 "gen/ragel/submatch_20__cat2_0.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				b1 = p; }
			
#line 263 "gen/ragel/submatch_20__cat2_0.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				a1 = p; }
			
#line 287 "gen/ragel/submatch_20__cat2_0.cc"

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
					goto _st3;
				}
				case 98: {
					goto _ctr11;
				}
			}
			goto _st0;
			_ctr11:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
				b1 = p; }
			
#line 311 "gen/ragel/submatch_20__cat2_0.cc"

			goto _st4;
			_st4:
			p+= 1;
			st_case_4:
			if ( p == pe )
				goto _out4;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr13;
				}
				case 98: {
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
		
#line 32 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH()
	RAGEL_TEST()
	
} // namespace ragel_submatch_20__cat2_0
