#line 1 "../../../benchmarks/c/src/ragel/submatch_30__rep_cat_5_3_2.rl"
#include "ragel/base.h"

namespace ragel_submatch_30__rep_cat_5_3_2 {
	
	const char *delim = "\n";
	
	
#line 30 "../../../benchmarks/c/src/ragel/submatch_30__rep_cat_5_3_2.rl"

	

#line 11 "gen/ragel/submatch_30__rep_cat_5_3_2.cc"
static const int aaa_start = 11;
	static const int aaa_first_final = 11;
	static const int aaa_error = 0;
	
	static const int aaa_en_main = 11;
	
	
#line 32 "../../../benchmarks/c/src/ragel/submatch_30__rep_cat_5_3_2.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *pe = in->pe;
		const char *s = p;
		int cs;
		

#line 26 "gen/ragel/submatch_30__rep_cat_5_3_2.cc"
	{
			cs = (int)aaa_start;
		}
		
#line 40 "../../../benchmarks/c/src/ragel/submatch_30__rep_cat_5_3_2.rl"


#line 31 "gen/ragel/submatch_30__rep_cat_5_3_2.cc"
{
			switch ( cs ) {
				case 11:
				goto st_case_11;
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
			}
			_ctr13:
				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_30__rep_cat_5_3_2.rl"
				
				OUTS(s, p);
				OUTC(';');
				s = p;
			}
			
#line 67 "gen/ragel/submatch_30__rep_cat_5_3_2.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_30__rep_cat_5_3_2.rl"
				OUTC('\n'); }
			
#line 72 "gen/ragel/submatch_30__rep_cat_5_3_2.cc"

			goto _st11;
			_ctr16:
				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_30__rep_cat_5_3_2.rl"
				OUTC('\n'); }
			
#line 79 "gen/ragel/submatch_30__rep_cat_5_3_2.cc"

			goto _st11;
			_st11:
			p+= 1;
			st_case_11:
			if ( p == pe )
				goto _out11;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr16;
				}
				case 97: {
					goto _st1;
				}
			}
			goto _st0;
			_st0:
			st_case_0:
			goto _out0;
			_ctr14:
				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_30__rep_cat_5_3_2.rl"
				
				OUTS(s, p);
				OUTC(';');
				s = p;
			}
			
#line 107 "gen/ragel/submatch_30__rep_cat_5_3_2.cc"

			goto _st1;
			_st1:
			p+= 1;
			st_case_1:
			if ( p == pe )
				goto _out1;
			if ( ( (*( p))) == 97 ) {
				goto _st2;
			}
			goto _st0;
			_st2:
			p+= 1;
			st_case_2:
			if ( p == pe )
				goto _out2;
			if ( ( (*( p))) == 97 ) {
				goto _st3;
			}
			goto _st0;
			_st3:
			p+= 1;
			st_case_3:
			if ( p == pe )
				goto _out3;
			if ( ( (*( p))) == 97 ) {
				goto _st4;
			}
			goto _st0;
			_st4:
			p+= 1;
			st_case_4:
			if ( p == pe )
				goto _out4;
			if ( ( (*( p))) == 97 ) {
				goto _st5;
			}
			goto _st0;
			_st5:
			p+= 1;
			st_case_5:
			if ( p == pe )
				goto _out5;
			if ( ( (*( p))) == 97 ) {
				goto _ctr6;
			}
			goto _st0;
			_ctr6:
				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_30__rep_cat_5_3_2.rl"
				
				OUTS(s, p);
				OUTC('.');
				s = p;
			}
			
#line 163 "gen/ragel/submatch_30__rep_cat_5_3_2.cc"

			goto _st6;
			_st6:
			p+= 1;
			st_case_6:
			if ( p == pe )
				goto _out6;
			if ( ( (*( p))) == 97 ) {
				goto _st7;
			}
			goto _st0;
			_st7:
			p+= 1;
			st_case_7:
			if ( p == pe )
				goto _out7;
			if ( ( (*( p))) == 97 ) {
				goto _st8;
			}
			goto _st0;
			_st8:
			p+= 1;
			st_case_8:
			if ( p == pe )
				goto _out8;
			if ( ( (*( p))) == 97 ) {
				goto _ctr10;
			}
			goto _st0;
			_ctr10:
				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_30__rep_cat_5_3_2.rl"
				
				OUTS(s, p);
				OUTC('.');
				s = p;
			}
			
#line 201 "gen/ragel/submatch_30__rep_cat_5_3_2.cc"

			goto _st9;
			_st9:
			p+= 1;
			st_case_9:
			if ( p == pe )
				goto _out9;
			if ( ( (*( p))) == 97 ) {
				goto _st10;
			}
			goto _st0;
			_st10:
			p+= 1;
			st_case_10:
			if ( p == pe )
				goto _out10;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr13;
				}
				case 97: {
					goto _ctr14;
				}
			}
			goto _st0;
			_out11: cs = 11; goto _out; 
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
			_out: {}
		}
		
#line 41 "../../../benchmarks/c/src/ragel/submatch_30__rep_cat_5_3_2.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH()
	RAGEL_TEST()
	
} // namespace ragel_submatch_30__rep_cat_5_3_2
