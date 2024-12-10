#line 1 "../../../benchmarks/c/src/ragel/submatch_07__ipv4.rl"
#include "ragel/base.h"

namespace ragel_submatch_07__ipv4 {
	
	const char *delim = "\n";
	
	
#line 29 "../../../benchmarks/c/src/ragel/submatch_07__ipv4.rl"

	

#line 11 "gen/ragel/submatch_07__ipv4.cc"
static const int ipv4_start = 16;
	static const int ipv4_first_final = 16;
	static const int ipv4_error = 0;
	
	static const int ipv4_en_main = 16;
	
	
#line 31 "../../../benchmarks/c/src/ragel/submatch_07__ipv4.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *pe = in->pe;
		const char *p1, *p2, *p3, *p4;
		int cs;
		

#line 26 "gen/ragel/submatch_07__ipv4.cc"
	{
			cs = (int)ipv4_start;
		}
		
#line 39 "../../../benchmarks/c/src/ragel/submatch_07__ipv4.rl"


#line 31 "gen/ragel/submatch_07__ipv4.cc"
{
			switch ( cs ) {
				case 16:
				goto st_case_16;
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
			}
			_ctr14:
				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_07__ipv4.rl"
				
				OUTS(p1, p2 - 1);
				OUTC(',');
				OUTS(p2, p3 - 1);
				OUTC(',');
				OUTS(p3, p4 - 1);
				OUTC(',');
				OUTS(p4, p);
				OUTC('\n');
			}
			
#line 82 "gen/ragel/submatch_07__ipv4.cc"

			goto _st16;
			_st16:
			p+= 1;
			st_case_16:
			if ( p == pe )
				goto _out16;
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _ctr21;
			}
			goto _st0;
			_st0:
			st_case_0:
			goto _out0;
			_ctr21:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_07__ipv4.rl"
				p1 = p; }
			
#line 101 "gen/ragel/submatch_07__ipv4.cc"

			goto _st1;
			_st1:
			p+= 1;
			st_case_1:
			if ( p == pe )
				goto _out1;
			if ( ( (*( p))) == 46 ) {
				goto _st2;
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st14;
			}
			goto _st0;
			_st2:
			p+= 1;
			st_case_2:
			if ( p == pe )
				goto _out2;
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _ctr4;
			}
			goto _st0;
			_ctr4:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_07__ipv4.rl"
				p2 = p; }
			
#line 129 "gen/ragel/submatch_07__ipv4.cc"

			goto _st3;
			_st3:
			p+= 1;
			st_case_3:
			if ( p == pe )
				goto _out3;
			if ( ( (*( p))) == 46 ) {
				goto _st4;
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st12;
			}
			goto _st0;
			_st4:
			p+= 1;
			st_case_4:
			if ( p == pe )
				goto _out4;
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _ctr8;
			}
			goto _st0;
			_ctr8:
				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_07__ipv4.rl"
				p3 = p; }
			
#line 157 "gen/ragel/submatch_07__ipv4.cc"

			goto _st5;
			_st5:
			p+= 1;
			st_case_5:
			if ( p == pe )
				goto _out5;
			if ( ( (*( p))) == 46 ) {
				goto _st6;
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st10;
			}
			goto _st0;
			_st6:
			p+= 1;
			st_case_6:
			if ( p == pe )
				goto _out6;
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _ctr12;
			}
			goto _st0;
			_ctr12:
				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_07__ipv4.rl"
				p4 = p; }
			
#line 185 "gen/ragel/submatch_07__ipv4.cc"

			goto _st7;
			_st7:
			p+= 1;
			st_case_7:
			if ( p == pe )
				goto _out7;
			if ( ( (*( p))) == 10 ) {
				goto _ctr14;
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st8;
			}
			goto _st0;
			_st8:
			p+= 1;
			st_case_8:
			if ( p == pe )
				goto _out8;
			if ( ( (*( p))) == 10 ) {
				goto _ctr14;
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st9;
			}
			goto _st0;
			_st9:
			p+= 1;
			st_case_9:
			if ( p == pe )
				goto _out9;
			if ( ( (*( p))) == 10 ) {
				goto _ctr14;
			}
			goto _st0;
			_st10:
			p+= 1;
			st_case_10:
			if ( p == pe )
				goto _out10;
			if ( ( (*( p))) == 46 ) {
				goto _st6;
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st11;
			}
			goto _st0;
			_st11:
			p+= 1;
			st_case_11:
			if ( p == pe )
				goto _out11;
			if ( ( (*( p))) == 46 ) {
				goto _st6;
			}
			goto _st0;
			_st12:
			p+= 1;
			st_case_12:
			if ( p == pe )
				goto _out12;
			if ( ( (*( p))) == 46 ) {
				goto _st4;
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st13;
			}
			goto _st0;
			_st13:
			p+= 1;
			st_case_13:
			if ( p == pe )
				goto _out13;
			if ( ( (*( p))) == 46 ) {
				goto _st4;
			}
			goto _st0;
			_st14:
			p+= 1;
			st_case_14:
			if ( p == pe )
				goto _out14;
			if ( ( (*( p))) == 46 ) {
				goto _st2;
			}
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st15;
			}
			goto _st0;
			_st15:
			p+= 1;
			st_case_15:
			if ( p == pe )
				goto _out15;
			if ( ( (*( p))) == 46 ) {
				goto _st2;
			}
			goto _st0;
			_out16: cs = 16; goto _out; 
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
			_out: {}
		}
		
#line 40 "../../../benchmarks/c/src/ragel/submatch_07__ipv4.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH()
	RAGEL_TEST()
	
} // namespace ragel_submatch_07__ipv4
