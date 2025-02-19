#line 1 "../../../benchmarks/c/src/ragel/lex_02__words1.rl"
#include "ragel/base.h"

namespace ragel_lex_02__words1 {
	
	const char *delim = "\n";
	
	
#line 20 "../../../benchmarks/c/src/ragel/lex_02__words1.rl"

	

#line 11 "gen/ragel/lex_02__words1.cc"
static const int lex_words_start = 21;
	static const int lex_words_first_final = 21;
	static const int lex_words_error = 0;
	
	static const int lex_words_en_main = 21;
	
	
#line 22 "../../../benchmarks/c/src/ragel/lex_02__words1.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *ts = in->ts;
		char *te = in->te;
		char *pe = in->pe;
		int act = in->act;
		int cs;
		

#line 28 "gen/ragel/lex_02__words1.cc"
	{
			cs = (int)lex_words_start;
			ts = 0;
			te = 0;
		}
		
#line 32 "../../../benchmarks/c/src/ragel/lex_02__words1.rl"


#line 35 "gen/ragel/lex_02__words1.cc"
{
			switch ( cs ) {
				case 21:
				goto st_case_21;
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
				case 14:
				goto st_case_14;
				case 15:
				goto st_case_15;
				case 16:
				goto st_case_16;
				case 17:
				goto st_case_17;
				case 18:
				goto st_case_18;
				case 19:
				goto st_case_19;
				case 20:
				goto st_case_20;
			}
			_ctr7:
				{
#line 19 "../../../benchmarks/c/src/ragel/lex_02__words1.rl"
				{te = p+1;{
#line 19 "../../../benchmarks/c/src/ragel/lex_02__words1.rl"
						OUTS(ts, te); }
				}}
			
#line 90 "gen/ragel/lex_02__words1.cc"

			goto _st21;
			_st21:
				{
#line 1 "NONE"
				{ts = 0;}}
			
#line 97 "gen/ragel/lex_02__words1.cc"

			p+= 1;
			st_case_21:
			if ( p == pe )
				goto _out21;
				{
#line 1 "NONE"
				{ts = p;}}
			
#line 106 "gen/ragel/lex_02__words1.cc"

			switch( ( (*( p))) ) {
				case 70: {
					goto _st1;
				}
				case 77: {
					goto _st7;
				}
				case 83: {
					goto _st9;
				}
				case 84: {
					goto _st13;
				}
				case 87: {
					goto _st18;
				}
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
			if ( ( (*( p))) == 114 ) {
				goto _st2;
			}
			goto _st0;
			_st2:
			p+= 1;
			st_case_2:
			if ( p == pe )
				goto _out2;
			if ( ( (*( p))) == 105 ) {
				goto _st3;
			}
			goto _st0;
			_st3:
			p+= 1;
			st_case_3:
			if ( p == pe )
				goto _out3;
			if ( ( (*( p))) == 100 ) {
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
			if ( ( (*( p))) == 121 ) {
				goto _st6;
			}
			goto _st0;
			_st6:
			p+= 1;
			st_case_6:
			if ( p == pe )
				goto _out6;
			if ( ( (*( p))) == 10 ) {
				goto _ctr7;
			}
			goto _st0;
			_st7:
			p+= 1;
			st_case_7:
			if ( p == pe )
				goto _out7;
			if ( ( (*( p))) == 111 ) {
				goto _st8;
			}
			goto _st0;
			_st8:
			p+= 1;
			st_case_8:
			if ( p == pe )
				goto _out8;
			if ( ( (*( p))) == 110 ) {
				goto _st3;
			}
			goto _st0;
			_st9:
			p+= 1;
			st_case_9:
			if ( p == pe )
				goto _out9;
			switch( ( (*( p))) ) {
				case 97: {
					goto _st10;
				}
				case 117: {
					goto _st8;
				}
			}
			goto _st0;
			_st10:
			p+= 1;
			st_case_10:
			if ( p == pe )
				goto _out10;
			if ( ( (*( p))) == 116 ) {
				goto _st11;
			}
			goto _st0;
			_st11:
			p+= 1;
			st_case_11:
			if ( p == pe )
				goto _out11;
			if ( ( (*( p))) == 117 ) {
				goto _st12;
			}
			goto _st0;
			_st12:
			p+= 1;
			st_case_12:
			if ( p == pe )
				goto _out12;
			if ( ( (*( p))) == 114 ) {
				goto _st3;
			}
			goto _st0;
			_st13:
			p+= 1;
			st_case_13:
			if ( p == pe )
				goto _out13;
			switch( ( (*( p))) ) {
				case 104: {
					goto _st14;
				}
				case 117: {
					goto _st17;
				}
			}
			goto _st0;
			_st14:
			p+= 1;
			st_case_14:
			if ( p == pe )
				goto _out14;
			if ( ( (*( p))) == 117 ) {
				goto _st15;
			}
			goto _st0;
			_st15:
			p+= 1;
			st_case_15:
			if ( p == pe )
				goto _out15;
			if ( ( (*( p))) == 114 ) {
				goto _st16;
			}
			goto _st0;
			_st16:
			p+= 1;
			st_case_16:
			if ( p == pe )
				goto _out16;
			if ( ( (*( p))) == 115 ) {
				goto _st3;
			}
			goto _st0;
			_st17:
			p+= 1;
			st_case_17:
			if ( p == pe )
				goto _out17;
			if ( ( (*( p))) == 101 ) {
				goto _st16;
			}
			goto _st0;
			_st18:
			p+= 1;
			st_case_18:
			if ( p == pe )
				goto _out18;
			if ( ( (*( p))) == 101 ) {
				goto _st19;
			}
			goto _st0;
			_st19:
			p+= 1;
			st_case_19:
			if ( p == pe )
				goto _out19;
			if ( ( (*( p))) == 100 ) {
				goto _st20;
			}
			goto _st0;
			_st20:
			p+= 1;
			st_case_20:
			if ( p == pe )
				goto _out20;
			if ( ( (*( p))) == 110 ) {
				goto _st17;
			}
			goto _st0;
			_out21: cs = 21; goto _out; 
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
			_out14: cs = 14; goto _out; 
			_out15: cs = 15; goto _out; 
			_out16: cs = 16; goto _out; 
			_out17: cs = 17; goto _out; 
			_out18: cs = 18; goto _out; 
			_out19: cs = 19; goto _out; 
			_out20: cs = 20; goto _out; 
			_out: {}
		}
		
#line 33 "../../../benchmarks/c/src/ragel/lex_02__words1.rl"

		
		in->p = p;
		in->ts = ts;
		in->te = te;
		in->pe = pe;
		in->act = act;
		
		return count;
	}
	
	RAGEL_BENCH_AND_TEST()
	
} // namespace ragel_lex_02__words1
