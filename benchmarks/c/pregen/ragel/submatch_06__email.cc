#line 1 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"
#include "ragel/base.h"

namespace ragel_submatch_06__email {
	
	const char *delim = "\n";
	
	
#line 28 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"

	

#line 11 "gen/ragel/submatch_06__email.cc"
static const int email_start = 10;
	static const int email_first_final = 10;
	static const int email_error = 0;
	
	static const int email_en_main = 10;
	
	
#line 30 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *pe = in->pe;
		char *p1, *p2;
		int cs;
		

#line 26 "gen/ragel/submatch_06__email.cc"
	{
			cs = (int)email_start;
		}
		
#line 38 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"


#line 31 "gen/ragel/submatch_06__email.cc"
{
			switch ( cs ) {
				case 10:
				goto st_case_10;
				case 1:
				goto st_case_1;
				case 0:
				goto st_case_0;
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
			}
			_ctr11:
				{
#line 19 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"
				
				OUTC(' ');
				OUTS(p1, p2 - 1);
				OUTC(' ');
				OUTS(p2, p);
				OUTC('\n');
			}
			
#line 67 "gen/ragel/submatch_06__email.cc"

			goto _st10;
			_st10:
			p+= 1;
			st_case_10:
			if ( p == pe )
				goto _out10;
			switch( ( (*( p))) ) {
				case 0: {
					goto _st0;
				}
				case 10: {
					goto _st10;
				}
				case 33: {
					goto _ctr13;
				}
				case 45: {
					goto _ctr13;
				}
				case 61: {
					goto _ctr13;
				}
				case 63: {
					goto _ctr13;
				}
			}
			if ( ( (*( p))) < 42 ) {
				if ( 35 <= ( (*( p))) && ( (*( p))) <= 39 ) {
					goto _ctr13;
				}
			} else if ( ( (*( p))) > 43 ) {
				if ( ( (*( p))) > 57 ) {
					if ( 94 <= ( (*( p))) && ( (*( p))) <= 126 ) {
						goto _ctr13;
					}
				} else if ( ( (*( p))) >= 47 ) {
					goto _ctr13;
				}
			} else {
				goto _ctr13;
			}
			goto _st1;
			_st1:
			p+= 1;
			st_case_1:
			if ( p == pe )
				goto _out1;
			switch( ( (*( p))) ) {
				case 0: {
					goto _st0;
				}
				case 10: {
					goto _st10;
				}
			}
			goto _st1;
			_st0:
			st_case_0:
			goto _out0;
			_ctr13:
				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"
				p1 = p; }
			
#line 132 "gen/ragel/submatch_06__email.cc"

			goto _st2;
			_st2:
			p+= 1;
			st_case_2:
			if ( p == pe )
				goto _out2;
			switch( ( (*( p))) ) {
				case 0: {
					goto _st0;
				}
				case 10: {
					goto _st10;
				}
				case 33: {
					goto _st2;
				}
				case 46: {
					goto _st3;
				}
				case 61: {
					goto _st2;
				}
				case 63: {
					goto _st2;
				}
				case 64: {
					goto _st4;
				}
			}
			if ( ( (*( p))) < 42 ) {
				if ( 35 <= ( (*( p))) && ( (*( p))) <= 39 ) {
					goto _st2;
				}
			} else if ( ( (*( p))) > 43 ) {
				if ( ( (*( p))) > 57 ) {
					if ( 94 <= ( (*( p))) && ( (*( p))) <= 126 ) {
						goto _st2;
					}
				} else if ( ( (*( p))) >= 45 ) {
					goto _st2;
				}
			} else {
				goto _st2;
			}
			goto _st1;
			_st3:
			p+= 1;
			st_case_3:
			if ( p == pe )
				goto _out3;
			switch( ( (*( p))) ) {
				case 0: {
					goto _st0;
				}
				case 10: {
					goto _st10;
				}
				case 33: {
					goto _st2;
				}
				case 45: {
					goto _st2;
				}
				case 61: {
					goto _st2;
				}
				case 63: {
					goto _st2;
				}
			}
			if ( ( (*( p))) < 42 ) {
				if ( 35 <= ( (*( p))) && ( (*( p))) <= 39 ) {
					goto _st2;
				}
			} else if ( ( (*( p))) > 43 ) {
				if ( ( (*( p))) > 57 ) {
					if ( 94 <= ( (*( p))) && ( (*( p))) <= 126 ) {
						goto _st2;
					}
				} else if ( ( (*( p))) >= 47 ) {
					goto _st2;
				}
			} else {
				goto _st2;
			}
			goto _st1;
			_st4:
			p+= 1;
			st_case_4:
			if ( p == pe )
				goto _out4;
			switch( ( (*( p))) ) {
				case 0: {
					goto _st0;
				}
				case 10: {
					goto _st10;
				}
			}
			if ( ( (*( p))) > 57 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _ctr6;
				}
			} else if ( ( (*( p))) >= 48 ) {
				goto _ctr6;
			}
			goto _st1;
			_ctr6:
				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"
				p2 = p; }
			
#line 245 "gen/ragel/submatch_06__email.cc"

			goto _st5;
			_st5:
			p+= 1;
			st_case_5:
			if ( p == pe )
				goto _out5;
			switch( ( (*( p))) ) {
				case 0: {
					goto _st0;
				}
				case 10: {
					goto _st10;
				}
				case 45: {
					goto _st6;
				}
				case 46: {
					goto _st7;
				}
			}
			if ( ( (*( p))) > 57 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st5;
				}
			} else if ( ( (*( p))) >= 48 ) {
				goto _st5;
			}
			goto _st1;
			_st6:
			p+= 1;
			st_case_6:
			if ( p == pe )
				goto _out6;
			switch( ( (*( p))) ) {
				case 0: {
					goto _st0;
				}
				case 10: {
					goto _st10;
				}
				case 45: {
					goto _st6;
				}
			}
			if ( ( (*( p))) > 57 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st5;
				}
			} else if ( ( (*( p))) >= 48 ) {
				goto _st5;
			}
			goto _st1;
			_st7:
			p+= 1;
			st_case_7:
			if ( p == pe )
				goto _out7;
			switch( ( (*( p))) ) {
				case 0: {
					goto _st0;
				}
				case 10: {
					goto _st10;
				}
			}
			if ( ( (*( p))) > 57 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st8;
				}
			} else if ( ( (*( p))) >= 48 ) {
				goto _st8;
			}
			goto _st1;
			_st8:
			p+= 1;
			st_case_8:
			if ( p == pe )
				goto _out8;
			switch( ( (*( p))) ) {
				case 0: {
					goto _st0;
				}
				case 10: {
					goto _ctr11;
				}
				case 45: {
					goto _st9;
				}
				case 46: {
					goto _st7;
				}
			}
			if ( ( (*( p))) > 57 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st8;
				}
			} else if ( ( (*( p))) >= 48 ) {
				goto _st8;
			}
			goto _st1;
			_st9:
			p+= 1;
			st_case_9:
			if ( p == pe )
				goto _out9;
			switch( ( (*( p))) ) {
				case 0: {
					goto _st0;
				}
				case 10: {
					goto _st10;
				}
				case 45: {
					goto _st9;
				}
			}
			if ( ( (*( p))) > 57 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st8;
				}
			} else if ( ( (*( p))) >= 48 ) {
				goto _st8;
			}
			goto _st1;
			_out10: cs = 10; goto _out; 
			_out1: cs = 1; goto _out; 
			_out0: cs = 0; goto _out; 
			_out2: cs = 2; goto _out; 
			_out3: cs = 3; goto _out; 
			_out4: cs = 4; goto _out; 
			_out5: cs = 5; goto _out; 
			_out6: cs = 6; goto _out; 
			_out7: cs = 7; goto _out; 
			_out8: cs = 8; goto _out; 
			_out9: cs = 9; goto _out; 
			_out: {}
		}
		
#line 39 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH()
	RAGEL_TEST()
	
} // namespace ragel_submatch_06__email
