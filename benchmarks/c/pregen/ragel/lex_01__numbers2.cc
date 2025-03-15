#line 1 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"
#include "ragel/base.h"

namespace ragel_lex_01__numbers2 {
	
	const char *delim = "\n";
	
	
#line 24 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"

	

#line 11 "gen/ragel/lex_01__numbers2.cc"
static const int lex_numbers_start = 14;
	static const int lex_numbers_first_final = 14;
	static const int lex_numbers_error = 0;
	
	static const int lex_numbers_en_main = 14;
	
	
#line 26 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *ts = in->ts;
		char *te = in->te;
		char *pe = in->pe;
		int act = in->act;
		int cs;
		

#line 28 "gen/ragel/lex_01__numbers2.cc"
	{
			cs = (int)lex_numbers_start;
			ts = 0;
			te = 0;
		}
		
#line 36 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"


#line 35 "gen/ragel/lex_01__numbers2.cc"
{
			switch ( cs ) {
				case 14:
				goto st_case_14;
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
				case 11:
				goto st_case_11;
				case 12:
				goto st_case_12;
				case 13:
				goto st_case_13;
			}
			_ctr3:
				{
#line 22 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"
				{te = p+1;{
#line 22 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"
						OUTX(ts, te, 1); }
				}}
			
#line 76 "gen/ragel/lex_01__numbers2.cc"

			goto _st14;
			_ctr8:
				{
#line 19 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"
				{te = p+1;{
#line 19 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"
						OUTX(ts, te, 8); }
				}}
			
#line 86 "gen/ragel/lex_01__numbers2.cc"

			goto _st14;
			_ctr14:
				{
#line 18 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"
				{te = p+1;{
#line 18 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"
						OUTX(ts, te, 2); }
				}}
			
#line 96 "gen/ragel/lex_01__numbers2.cc"

			goto _st14;
			_ctr16:
				{
#line 21 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"
				{te = p+1;{
#line 21 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"
						OUTX(ts, te, 16); }
				}}
			
#line 106 "gen/ragel/lex_01__numbers2.cc"

			goto _st14;
			_ctr18:
				{
#line 20 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"
				{te = p+1;{
#line 20 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"
						OUTX(ts, te, 10); }
				}}
			
#line 116 "gen/ragel/lex_01__numbers2.cc"

			goto _st14;
			_st14:
				{
#line 1 "NONE"
				{ts = 0;}}
			
#line 123 "gen/ragel/lex_01__numbers2.cc"

			p+= 1;
			st_case_14:
			if ( p == pe )
				goto _out14;
				{
#line 1 "NONE"
				{ts = p;}}
			
#line 132 "gen/ragel/lex_01__numbers2.cc"

			switch( ( (*( p))) ) {
				case 46: {
					goto _st1;
				}
				case 48: {
					goto _st6;
				}
			}
			if ( 49 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st13;
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
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st2;
			}
			goto _st0;
			_st2:
			p+= 1;
			st_case_2:
			if ( p == pe )
				goto _out2;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr3;
				}
				case 69: {
					goto _st3;
				}
				case 101: {
					goto _st3;
				}
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st2;
			}
			goto _st0;
			_st3:
			p+= 1;
			st_case_3:
			if ( p == pe )
				goto _out3;
			switch( ( (*( p))) ) {
				case 43: {
					goto _st4;
				}
				case 45: {
					goto _st4;
				}
			}
			if ( 49 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st5;
			}
			goto _st0;
			_st4:
			p+= 1;
			st_case_4:
			if ( p == pe )
				goto _out4;
			if ( 49 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st5;
			}
			goto _st0;
			_st5:
			p+= 1;
			st_case_5:
			if ( p == pe )
				goto _out5;
			if ( ( (*( p))) == 10 ) {
				goto _ctr3;
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st5;
			}
			goto _st0;
			_st6:
			p+= 1;
			st_case_6:
			if ( p == pe )
				goto _out6;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr8;
				}
				case 46: {
					goto _st1;
				}
				case 66: {
					goto _st9;
				}
				case 88: {
					goto _st11;
				}
				case 98: {
					goto _st9;
				}
				case 120: {
					goto _st11;
				}
			}
			if ( ( (*( p))) > 55 ) {
				if ( ( (*( p))) <= 57 ) {
					goto _st8;
				}
			} else if ( ( (*( p))) >= 48 ) {
				goto _st7;
			}
			goto _st0;
			_st7:
			p+= 1;
			st_case_7:
			if ( p == pe )
				goto _out7;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr8;
				}
				case 46: {
					goto _st1;
				}
			}
			if ( ( (*( p))) > 55 ) {
				if ( ( (*( p))) <= 57 ) {
					goto _st8;
				}
			} else if ( ( (*( p))) >= 48 ) {
				goto _st7;
			}
			goto _st0;
			_st8:
			p+= 1;
			st_case_8:
			if ( p == pe )
				goto _out8;
			if ( ( (*( p))) == 46 ) {
				goto _st1;
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st8;
			}
			goto _st0;
			_st9:
			p+= 1;
			st_case_9:
			if ( p == pe )
				goto _out9;
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 49 ) {
				goto _st10;
			}
			goto _st0;
			_st10:
			p+= 1;
			st_case_10:
			if ( p == pe )
				goto _out10;
			if ( ( (*( p))) == 10 ) {
				goto _ctr14;
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 49 ) {
				goto _st10;
			}
			goto _st0;
			_st11:
			p+= 1;
			st_case_11:
			if ( p == pe )
				goto _out11;
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto _st12;
				}
			} else if ( ( (*( p))) > 70 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 102 ) {
					goto _st12;
				}
			} else {
				goto _st12;
			}
			goto _st0;
			_st12:
			p+= 1;
			st_case_12:
			if ( p == pe )
				goto _out12;
			if ( ( (*( p))) == 10 ) {
				goto _ctr16;
			}
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto _st12;
				}
			} else if ( ( (*( p))) > 70 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 102 ) {
					goto _st12;
				}
			} else {
				goto _st12;
			}
			goto _st0;
			_st13:
			p+= 1;
			st_case_13:
			if ( p == pe )
				goto _out13;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr18;
				}
				case 46: {
					goto _st1;
				}
				case 69: {
					goto _st3;
				}
				case 101: {
					goto _st3;
				}
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st13;
			}
			goto _st0;
			_out14: cs = 14; goto _out; 
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
			_out11: cs = 11; goto _out; 
			_out12: cs = 12; goto _out; 
			_out13: cs = 13; goto _out; 
			_out: {}
		}
		
#line 37 "../../../benchmarks/c/src/ragel/lex_01__numbers2.rl"

		
		in->p = p;
		in->ts = ts;
		in->te = te;
		in->pe = pe;
		in->act = act;
		
		return count;
	}
	
	RAGEL_BENCH_AND_TEST()
	
} // namespace ragel_lex_01__numbers2
