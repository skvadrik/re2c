#line 1 "../../../benchmarks/c/src/ragel/submatch_32__rep_cat_23_19_17.rl"
#include "ragel/base.h"

namespace ragel_submatch_32__rep_cat_23_19_17 {
	
	const char *delim = "\n";
	
	
#line 30 "../../../benchmarks/c/src/ragel/submatch_32__rep_cat_23_19_17.rl"

	

#line 11 "gen/ragel/submatch_32__rep_cat_23_19_17.cc"
static const int aaa_start = 60;
	static const int aaa_first_final = 60;
	static const int aaa_error = 0;
	
	static const int aaa_en_main = 60;
	
	
#line 32 "../../../benchmarks/c/src/ragel/submatch_32__rep_cat_23_19_17.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *pe = in->pe;
		const char *s = p;
		int cs;
		

#line 26 "gen/ragel/submatch_32__rep_cat_23_19_17.cc"
	{
			cs = (int)aaa_start;
		}
		
#line 40 "../../../benchmarks/c/src/ragel/submatch_32__rep_cat_23_19_17.rl"


#line 31 "gen/ragel/submatch_32__rep_cat_23_19_17.cc"
{
			switch ( cs ) {
				case 60:
				goto st_case_60;
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
				case 21:
				goto st_case_21;
				case 22:
				goto st_case_22;
				case 23:
				goto st_case_23;
				case 24:
				goto st_case_24;
				case 25:
				goto st_case_25;
				case 26:
				goto st_case_26;
				case 27:
				goto st_case_27;
				case 28:
				goto st_case_28;
				case 29:
				goto st_case_29;
				case 30:
				goto st_case_30;
				case 31:
				goto st_case_31;
				case 32:
				goto st_case_32;
				case 33:
				goto st_case_33;
				case 34:
				goto st_case_34;
				case 35:
				goto st_case_35;
				case 36:
				goto st_case_36;
				case 37:
				goto st_case_37;
				case 38:
				goto st_case_38;
				case 39:
				goto st_case_39;
				case 40:
				goto st_case_40;
				case 41:
				goto st_case_41;
				case 42:
				goto st_case_42;
				case 43:
				goto st_case_43;
				case 44:
				goto st_case_44;
				case 45:
				goto st_case_45;
				case 46:
				goto st_case_46;
				case 47:
				goto st_case_47;
				case 48:
				goto st_case_48;
				case 49:
				goto st_case_49;
				case 50:
				goto st_case_50;
				case 51:
				goto st_case_51;
				case 52:
				goto st_case_52;
				case 53:
				goto st_case_53;
				case 54:
				goto st_case_54;
				case 55:
				goto st_case_55;
				case 56:
				goto st_case_56;
				case 57:
				goto st_case_57;
				case 58:
				goto st_case_58;
				case 59:
				goto st_case_59;
			}
			_ctr62:
				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_32__rep_cat_23_19_17.rl"
				
				OUTS(s, p);
				OUTC(';');
				s = p;
			}
			
#line 165 "gen/ragel/submatch_32__rep_cat_23_19_17.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_32__rep_cat_23_19_17.rl"
				OUTC('\n'); }
			
#line 170 "gen/ragel/submatch_32__rep_cat_23_19_17.cc"

			goto _st60;
			_ctr65:
				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_32__rep_cat_23_19_17.rl"
				OUTC('\n'); }
			
#line 177 "gen/ragel/submatch_32__rep_cat_23_19_17.cc"

			goto _st60;
			_st60:
			p+= 1;
			st_case_60:
			if ( p == pe )
				goto _out60;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr65;
				}
				case 97: {
					goto _st1;
				}
			}
			goto _st0;
			_st0:
			st_case_0:
			goto _out0;
			_ctr63:
				{
#line 21 "../../../benchmarks/c/src/ragel/submatch_32__rep_cat_23_19_17.rl"
				
				OUTS(s, p);
				OUTC(';');
				s = p;
			}
			
#line 205 "gen/ragel/submatch_32__rep_cat_23_19_17.cc"

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
				goto _st6;
			}
			goto _st0;
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
				goto _st9;
			}
			goto _st0;
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
			if ( ( (*( p))) == 97 ) {
				goto _st11;
			}
			goto _st0;
			_st11:
			p+= 1;
			st_case_11:
			if ( p == pe )
				goto _out11;
			if ( ( (*( p))) == 97 ) {
				goto _st12;
			}
			goto _st0;
			_st12:
			p+= 1;
			st_case_12:
			if ( p == pe )
				goto _out12;
			if ( ( (*( p))) == 97 ) {
				goto _st13;
			}
			goto _st0;
			_st13:
			p+= 1;
			st_case_13:
			if ( p == pe )
				goto _out13;
			if ( ( (*( p))) == 97 ) {
				goto _st14;
			}
			goto _st0;
			_st14:
			p+= 1;
			st_case_14:
			if ( p == pe )
				goto _out14;
			if ( ( (*( p))) == 97 ) {
				goto _st15;
			}
			goto _st0;
			_st15:
			p+= 1;
			st_case_15:
			if ( p == pe )
				goto _out15;
			if ( ( (*( p))) == 97 ) {
				goto _st16;
			}
			goto _st0;
			_st16:
			p+= 1;
			st_case_16:
			if ( p == pe )
				goto _out16;
			if ( ( (*( p))) == 97 ) {
				goto _st17;
			}
			goto _st0;
			_st17:
			p+= 1;
			st_case_17:
			if ( p == pe )
				goto _out17;
			if ( ( (*( p))) == 97 ) {
				goto _st18;
			}
			goto _st0;
			_st18:
			p+= 1;
			st_case_18:
			if ( p == pe )
				goto _out18;
			if ( ( (*( p))) == 97 ) {
				goto _st19;
			}
			goto _st0;
			_st19:
			p+= 1;
			st_case_19:
			if ( p == pe )
				goto _out19;
			if ( ( (*( p))) == 97 ) {
				goto _st20;
			}
			goto _st0;
			_st20:
			p+= 1;
			st_case_20:
			if ( p == pe )
				goto _out20;
			if ( ( (*( p))) == 97 ) {
				goto _st21;
			}
			goto _st0;
			_st21:
			p+= 1;
			st_case_21:
			if ( p == pe )
				goto _out21;
			if ( ( (*( p))) == 97 ) {
				goto _st22;
			}
			goto _st0;
			_st22:
			p+= 1;
			st_case_22:
			if ( p == pe )
				goto _out22;
			if ( ( (*( p))) == 97 ) {
				goto _st23;
			}
			goto _st0;
			_st23:
			p+= 1;
			st_case_23:
			if ( p == pe )
				goto _out23;
			if ( ( (*( p))) == 97 ) {
				goto _ctr24;
			}
			goto _st0;
			_ctr24:
				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_32__rep_cat_23_19_17.rl"
				
				OUTS(s, p);
				OUTC('.');
				s = p;
			}
			
#line 423 "gen/ragel/submatch_32__rep_cat_23_19_17.cc"

			goto _st24;
			_st24:
			p+= 1;
			st_case_24:
			if ( p == pe )
				goto _out24;
			if ( ( (*( p))) == 97 ) {
				goto _st25;
			}
			goto _st0;
			_st25:
			p+= 1;
			st_case_25:
			if ( p == pe )
				goto _out25;
			if ( ( (*( p))) == 97 ) {
				goto _st26;
			}
			goto _st0;
			_st26:
			p+= 1;
			st_case_26:
			if ( p == pe )
				goto _out26;
			if ( ( (*( p))) == 97 ) {
				goto _st27;
			}
			goto _st0;
			_st27:
			p+= 1;
			st_case_27:
			if ( p == pe )
				goto _out27;
			if ( ( (*( p))) == 97 ) {
				goto _st28;
			}
			goto _st0;
			_st28:
			p+= 1;
			st_case_28:
			if ( p == pe )
				goto _out28;
			if ( ( (*( p))) == 97 ) {
				goto _st29;
			}
			goto _st0;
			_st29:
			p+= 1;
			st_case_29:
			if ( p == pe )
				goto _out29;
			if ( ( (*( p))) == 97 ) {
				goto _st30;
			}
			goto _st0;
			_st30:
			p+= 1;
			st_case_30:
			if ( p == pe )
				goto _out30;
			if ( ( (*( p))) == 97 ) {
				goto _st31;
			}
			goto _st0;
			_st31:
			p+= 1;
			st_case_31:
			if ( p == pe )
				goto _out31;
			if ( ( (*( p))) == 97 ) {
				goto _st32;
			}
			goto _st0;
			_st32:
			p+= 1;
			st_case_32:
			if ( p == pe )
				goto _out32;
			if ( ( (*( p))) == 97 ) {
				goto _st33;
			}
			goto _st0;
			_st33:
			p+= 1;
			st_case_33:
			if ( p == pe )
				goto _out33;
			if ( ( (*( p))) == 97 ) {
				goto _st34;
			}
			goto _st0;
			_st34:
			p+= 1;
			st_case_34:
			if ( p == pe )
				goto _out34;
			if ( ( (*( p))) == 97 ) {
				goto _st35;
			}
			goto _st0;
			_st35:
			p+= 1;
			st_case_35:
			if ( p == pe )
				goto _out35;
			if ( ( (*( p))) == 97 ) {
				goto _st36;
			}
			goto _st0;
			_st36:
			p+= 1;
			st_case_36:
			if ( p == pe )
				goto _out36;
			if ( ( (*( p))) == 97 ) {
				goto _st37;
			}
			goto _st0;
			_st37:
			p+= 1;
			st_case_37:
			if ( p == pe )
				goto _out37;
			if ( ( (*( p))) == 97 ) {
				goto _st38;
			}
			goto _st0;
			_st38:
			p+= 1;
			st_case_38:
			if ( p == pe )
				goto _out38;
			if ( ( (*( p))) == 97 ) {
				goto _st39;
			}
			goto _st0;
			_st39:
			p+= 1;
			st_case_39:
			if ( p == pe )
				goto _out39;
			if ( ( (*( p))) == 97 ) {
				goto _st40;
			}
			goto _st0;
			_st40:
			p+= 1;
			st_case_40:
			if ( p == pe )
				goto _out40;
			if ( ( (*( p))) == 97 ) {
				goto _st41;
			}
			goto _st0;
			_st41:
			p+= 1;
			st_case_41:
			if ( p == pe )
				goto _out41;
			if ( ( (*( p))) == 97 ) {
				goto _st42;
			}
			goto _st0;
			_st42:
			p+= 1;
			st_case_42:
			if ( p == pe )
				goto _out42;
			if ( ( (*( p))) == 97 ) {
				goto _ctr44;
			}
			goto _st0;
			_ctr44:
				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_32__rep_cat_23_19_17.rl"
				
				OUTS(s, p);
				OUTC('.');
				s = p;
			}
			
#line 605 "gen/ragel/submatch_32__rep_cat_23_19_17.cc"

			goto _st43;
			_st43:
			p+= 1;
			st_case_43:
			if ( p == pe )
				goto _out43;
			if ( ( (*( p))) == 97 ) {
				goto _st44;
			}
			goto _st0;
			_st44:
			p+= 1;
			st_case_44:
			if ( p == pe )
				goto _out44;
			if ( ( (*( p))) == 97 ) {
				goto _st45;
			}
			goto _st0;
			_st45:
			p+= 1;
			st_case_45:
			if ( p == pe )
				goto _out45;
			if ( ( (*( p))) == 97 ) {
				goto _st46;
			}
			goto _st0;
			_st46:
			p+= 1;
			st_case_46:
			if ( p == pe )
				goto _out46;
			if ( ( (*( p))) == 97 ) {
				goto _st47;
			}
			goto _st0;
			_st47:
			p+= 1;
			st_case_47:
			if ( p == pe )
				goto _out47;
			if ( ( (*( p))) == 97 ) {
				goto _st48;
			}
			goto _st0;
			_st48:
			p+= 1;
			st_case_48:
			if ( p == pe )
				goto _out48;
			if ( ( (*( p))) == 97 ) {
				goto _st49;
			}
			goto _st0;
			_st49:
			p+= 1;
			st_case_49:
			if ( p == pe )
				goto _out49;
			if ( ( (*( p))) == 97 ) {
				goto _st50;
			}
			goto _st0;
			_st50:
			p+= 1;
			st_case_50:
			if ( p == pe )
				goto _out50;
			if ( ( (*( p))) == 97 ) {
				goto _st51;
			}
			goto _st0;
			_st51:
			p+= 1;
			st_case_51:
			if ( p == pe )
				goto _out51;
			if ( ( (*( p))) == 97 ) {
				goto _st52;
			}
			goto _st0;
			_st52:
			p+= 1;
			st_case_52:
			if ( p == pe )
				goto _out52;
			if ( ( (*( p))) == 97 ) {
				goto _st53;
			}
			goto _st0;
			_st53:
			p+= 1;
			st_case_53:
			if ( p == pe )
				goto _out53;
			if ( ( (*( p))) == 97 ) {
				goto _st54;
			}
			goto _st0;
			_st54:
			p+= 1;
			st_case_54:
			if ( p == pe )
				goto _out54;
			if ( ( (*( p))) == 97 ) {
				goto _st55;
			}
			goto _st0;
			_st55:
			p+= 1;
			st_case_55:
			if ( p == pe )
				goto _out55;
			if ( ( (*( p))) == 97 ) {
				goto _st56;
			}
			goto _st0;
			_st56:
			p+= 1;
			st_case_56:
			if ( p == pe )
				goto _out56;
			if ( ( (*( p))) == 97 ) {
				goto _st57;
			}
			goto _st0;
			_st57:
			p+= 1;
			st_case_57:
			if ( p == pe )
				goto _out57;
			if ( ( (*( p))) == 97 ) {
				goto _st58;
			}
			goto _st0;
			_st58:
			p+= 1;
			st_case_58:
			if ( p == pe )
				goto _out58;
			if ( ( (*( p))) == 97 ) {
				goto _st59;
			}
			goto _st0;
			_st59:
			p+= 1;
			st_case_59:
			if ( p == pe )
				goto _out59;
			switch( ( (*( p))) ) {
				case 10: {
					goto _ctr62;
				}
				case 97: {
					goto _ctr63;
				}
			}
			goto _st0;
			_out60: cs = 60; goto _out; 
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
			_out21: cs = 21; goto _out; 
			_out22: cs = 22; goto _out; 
			_out23: cs = 23; goto _out; 
			_out24: cs = 24; goto _out; 
			_out25: cs = 25; goto _out; 
			_out26: cs = 26; goto _out; 
			_out27: cs = 27; goto _out; 
			_out28: cs = 28; goto _out; 
			_out29: cs = 29; goto _out; 
			_out30: cs = 30; goto _out; 
			_out31: cs = 31; goto _out; 
			_out32: cs = 32; goto _out; 
			_out33: cs = 33; goto _out; 
			_out34: cs = 34; goto _out; 
			_out35: cs = 35; goto _out; 
			_out36: cs = 36; goto _out; 
			_out37: cs = 37; goto _out; 
			_out38: cs = 38; goto _out; 
			_out39: cs = 39; goto _out; 
			_out40: cs = 40; goto _out; 
			_out41: cs = 41; goto _out; 
			_out42: cs = 42; goto _out; 
			_out43: cs = 43; goto _out; 
			_out44: cs = 44; goto _out; 
			_out45: cs = 45; goto _out; 
			_out46: cs = 46; goto _out; 
			_out47: cs = 47; goto _out; 
			_out48: cs = 48; goto _out; 
			_out49: cs = 49; goto _out; 
			_out50: cs = 50; goto _out; 
			_out51: cs = 51; goto _out; 
			_out52: cs = 52; goto _out; 
			_out53: cs = 53; goto _out; 
			_out54: cs = 54; goto _out; 
			_out55: cs = 55; goto _out; 
			_out56: cs = 56; goto _out; 
			_out57: cs = 57; goto _out; 
			_out58: cs = 58; goto _out; 
			_out59: cs = 59; goto _out; 
			_out: {}
		}
		
#line 41 "../../../benchmarks/c/src/ragel/submatch_32__rep_cat_23_19_17.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH_AND_TEST()
	
} // namespace ragel_submatch_32__rep_cat_23_19_17
