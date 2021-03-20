#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/32__iter_64.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/32__iter_64.rl"



#line 12 "gen/ragel/32__iter_64.c"
static const int aaa_start = 65;
static const int aaa_first_final = 65;
static const int aaa_error = 0;

static const int aaa_en_main = 65;


#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/32__iter_64.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *s;
	int cs;
	
	
#line 31 "gen/ragel/32__iter_64.c"
	{
		cs = (int)aaa_start;
	}
	
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/32__iter_64.rl"
	
	
#line 39 "gen/ragel/32__iter_64.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 65:
			goto st_case_65;
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
			case 60:
			goto st_case_60;
			case 61:
			goto st_case_61;
			case 62:
			goto st_case_62;
			case 63:
			goto st_case_63;
			case 64:
			goto st_case_64;
		}
		goto st_out;
		_ctr65:
		{
#line 8 "../../../benchmarks/submatch_dfa_aot/src/ragel/32__iter_64.rl"
			
			outs(out, s, p);
			outc(out, '.');
			s = p;
		}
		
#line 187 "gen/ragel/32__iter_64.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/32__iter_64.rl"
			outc(out, '\n'); }
		
#line 193 "gen/ragel/32__iter_64.c"
		
		goto _st65;
		_ctr68:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/32__iter_64.rl"
			s = p; }
		
#line 201 "gen/ragel/32__iter_64.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/32__iter_64.rl"
			outc(out, '\n'); }
		
#line 207 "gen/ragel/32__iter_64.c"
		
		goto _st65;
		_st65:
		p+= 1;
		if ( p == pe )
			goto _test_eof65;
		st_case_65:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr68;
			}
			case 97: {
				goto _ctr69;
			}
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr66:
		{
#line 8 "../../../benchmarks/submatch_dfa_aot/src/ragel/32__iter_64.rl"
			
			outs(out, s, p);
			outc(out, '.');
			s = p;
		}
		
#line 239 "gen/ragel/32__iter_64.c"
		
		goto _st1;
		_ctr69:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/32__iter_64.rl"
			s = p; }
		
#line 247 "gen/ragel/32__iter_64.c"
		
		goto _st1;
		_st1:
		p+= 1;
		if ( p == pe )
			goto _test_eof1;
		st_case_1:
		if ( ( (*( p))) == 97 ) {
			goto _st2;
		}
		{
			goto _st0;
		}
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
		if ( ( (*( p))) == 97 ) {
			goto _st3;
		}
		{
			goto _st0;
		}
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		if ( ( (*( p))) == 97 ) {
			goto _st4;
		}
		{
			goto _st0;
		}
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		if ( ( (*( p))) == 97 ) {
			goto _st5;
		}
		{
			goto _st0;
		}
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		if ( ( (*( p))) == 97 ) {
			goto _st6;
		}
		{
			goto _st0;
		}
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		if ( ( (*( p))) == 97 ) {
			goto _st7;
		}
		{
			goto _st0;
		}
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		if ( ( (*( p))) == 97 ) {
			goto _st8;
		}
		{
			goto _st0;
		}
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		if ( ( (*( p))) == 97 ) {
			goto _st9;
		}
		{
			goto _st0;
		}
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
		if ( ( (*( p))) == 97 ) {
			goto _st10;
		}
		{
			goto _st0;
		}
		_st10:
		p+= 1;
		if ( p == pe )
			goto _test_eof10;
		st_case_10:
		if ( ( (*( p))) == 97 ) {
			goto _st11;
		}
		{
			goto _st0;
		}
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
		if ( ( (*( p))) == 97 ) {
			goto _st12;
		}
		{
			goto _st0;
		}
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
		if ( ( (*( p))) == 97 ) {
			goto _st13;
		}
		{
			goto _st0;
		}
		_st13:
		p+= 1;
		if ( p == pe )
			goto _test_eof13;
		st_case_13:
		if ( ( (*( p))) == 97 ) {
			goto _st14;
		}
		{
			goto _st0;
		}
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
		if ( ( (*( p))) == 97 ) {
			goto _st15;
		}
		{
			goto _st0;
		}
		_st15:
		p+= 1;
		if ( p == pe )
			goto _test_eof15;
		st_case_15:
		if ( ( (*( p))) == 97 ) {
			goto _st16;
		}
		{
			goto _st0;
		}
		_st16:
		p+= 1;
		if ( p == pe )
			goto _test_eof16;
		st_case_16:
		if ( ( (*( p))) == 97 ) {
			goto _st17;
		}
		{
			goto _st0;
		}
		_st17:
		p+= 1;
		if ( p == pe )
			goto _test_eof17;
		st_case_17:
		if ( ( (*( p))) == 97 ) {
			goto _st18;
		}
		{
			goto _st0;
		}
		_st18:
		p+= 1;
		if ( p == pe )
			goto _test_eof18;
		st_case_18:
		if ( ( (*( p))) == 97 ) {
			goto _st19;
		}
		{
			goto _st0;
		}
		_st19:
		p+= 1;
		if ( p == pe )
			goto _test_eof19;
		st_case_19:
		if ( ( (*( p))) == 97 ) {
			goto _st20;
		}
		{
			goto _st0;
		}
		_st20:
		p+= 1;
		if ( p == pe )
			goto _test_eof20;
		st_case_20:
		if ( ( (*( p))) == 97 ) {
			goto _st21;
		}
		{
			goto _st0;
		}
		_st21:
		p+= 1;
		if ( p == pe )
			goto _test_eof21;
		st_case_21:
		if ( ( (*( p))) == 97 ) {
			goto _st22;
		}
		{
			goto _st0;
		}
		_st22:
		p+= 1;
		if ( p == pe )
			goto _test_eof22;
		st_case_22:
		if ( ( (*( p))) == 97 ) {
			goto _st23;
		}
		{
			goto _st0;
		}
		_st23:
		p+= 1;
		if ( p == pe )
			goto _test_eof23;
		st_case_23:
		if ( ( (*( p))) == 97 ) {
			goto _st24;
		}
		{
			goto _st0;
		}
		_st24:
		p+= 1;
		if ( p == pe )
			goto _test_eof24;
		st_case_24:
		if ( ( (*( p))) == 97 ) {
			goto _st25;
		}
		{
			goto _st0;
		}
		_st25:
		p+= 1;
		if ( p == pe )
			goto _test_eof25;
		st_case_25:
		if ( ( (*( p))) == 97 ) {
			goto _st26;
		}
		{
			goto _st0;
		}
		_st26:
		p+= 1;
		if ( p == pe )
			goto _test_eof26;
		st_case_26:
		if ( ( (*( p))) == 97 ) {
			goto _st27;
		}
		{
			goto _st0;
		}
		_st27:
		p+= 1;
		if ( p == pe )
			goto _test_eof27;
		st_case_27:
		if ( ( (*( p))) == 97 ) {
			goto _st28;
		}
		{
			goto _st0;
		}
		_st28:
		p+= 1;
		if ( p == pe )
			goto _test_eof28;
		st_case_28:
		if ( ( (*( p))) == 97 ) {
			goto _st29;
		}
		{
			goto _st0;
		}
		_st29:
		p+= 1;
		if ( p == pe )
			goto _test_eof29;
		st_case_29:
		if ( ( (*( p))) == 97 ) {
			goto _st30;
		}
		{
			goto _st0;
		}
		_st30:
		p+= 1;
		if ( p == pe )
			goto _test_eof30;
		st_case_30:
		if ( ( (*( p))) == 97 ) {
			goto _st31;
		}
		{
			goto _st0;
		}
		_st31:
		p+= 1;
		if ( p == pe )
			goto _test_eof31;
		st_case_31:
		if ( ( (*( p))) == 97 ) {
			goto _st32;
		}
		{
			goto _st0;
		}
		_st32:
		p+= 1;
		if ( p == pe )
			goto _test_eof32;
		st_case_32:
		if ( ( (*( p))) == 97 ) {
			goto _st33;
		}
		{
			goto _st0;
		}
		_st33:
		p+= 1;
		if ( p == pe )
			goto _test_eof33;
		st_case_33:
		if ( ( (*( p))) == 97 ) {
			goto _st34;
		}
		{
			goto _st0;
		}
		_st34:
		p+= 1;
		if ( p == pe )
			goto _test_eof34;
		st_case_34:
		if ( ( (*( p))) == 97 ) {
			goto _st35;
		}
		{
			goto _st0;
		}
		_st35:
		p+= 1;
		if ( p == pe )
			goto _test_eof35;
		st_case_35:
		if ( ( (*( p))) == 97 ) {
			goto _st36;
		}
		{
			goto _st0;
		}
		_st36:
		p+= 1;
		if ( p == pe )
			goto _test_eof36;
		st_case_36:
		if ( ( (*( p))) == 97 ) {
			goto _st37;
		}
		{
			goto _st0;
		}
		_st37:
		p+= 1;
		if ( p == pe )
			goto _test_eof37;
		st_case_37:
		if ( ( (*( p))) == 97 ) {
			goto _st38;
		}
		{
			goto _st0;
		}
		_st38:
		p+= 1;
		if ( p == pe )
			goto _test_eof38;
		st_case_38:
		if ( ( (*( p))) == 97 ) {
			goto _st39;
		}
		{
			goto _st0;
		}
		_st39:
		p+= 1;
		if ( p == pe )
			goto _test_eof39;
		st_case_39:
		if ( ( (*( p))) == 97 ) {
			goto _st40;
		}
		{
			goto _st0;
		}
		_st40:
		p+= 1;
		if ( p == pe )
			goto _test_eof40;
		st_case_40:
		if ( ( (*( p))) == 97 ) {
			goto _st41;
		}
		{
			goto _st0;
		}
		_st41:
		p+= 1;
		if ( p == pe )
			goto _test_eof41;
		st_case_41:
		if ( ( (*( p))) == 97 ) {
			goto _st42;
		}
		{
			goto _st0;
		}
		_st42:
		p+= 1;
		if ( p == pe )
			goto _test_eof42;
		st_case_42:
		if ( ( (*( p))) == 97 ) {
			goto _st43;
		}
		{
			goto _st0;
		}
		_st43:
		p+= 1;
		if ( p == pe )
			goto _test_eof43;
		st_case_43:
		if ( ( (*( p))) == 97 ) {
			goto _st44;
		}
		{
			goto _st0;
		}
		_st44:
		p+= 1;
		if ( p == pe )
			goto _test_eof44;
		st_case_44:
		if ( ( (*( p))) == 97 ) {
			goto _st45;
		}
		{
			goto _st0;
		}
		_st45:
		p+= 1;
		if ( p == pe )
			goto _test_eof45;
		st_case_45:
		if ( ( (*( p))) == 97 ) {
			goto _st46;
		}
		{
			goto _st0;
		}
		_st46:
		p+= 1;
		if ( p == pe )
			goto _test_eof46;
		st_case_46:
		if ( ( (*( p))) == 97 ) {
			goto _st47;
		}
		{
			goto _st0;
		}
		_st47:
		p+= 1;
		if ( p == pe )
			goto _test_eof47;
		st_case_47:
		if ( ( (*( p))) == 97 ) {
			goto _st48;
		}
		{
			goto _st0;
		}
		_st48:
		p+= 1;
		if ( p == pe )
			goto _test_eof48;
		st_case_48:
		if ( ( (*( p))) == 97 ) {
			goto _st49;
		}
		{
			goto _st0;
		}
		_st49:
		p+= 1;
		if ( p == pe )
			goto _test_eof49;
		st_case_49:
		if ( ( (*( p))) == 97 ) {
			goto _st50;
		}
		{
			goto _st0;
		}
		_st50:
		p+= 1;
		if ( p == pe )
			goto _test_eof50;
		st_case_50:
		if ( ( (*( p))) == 97 ) {
			goto _st51;
		}
		{
			goto _st0;
		}
		_st51:
		p+= 1;
		if ( p == pe )
			goto _test_eof51;
		st_case_51:
		if ( ( (*( p))) == 97 ) {
			goto _st52;
		}
		{
			goto _st0;
		}
		_st52:
		p+= 1;
		if ( p == pe )
			goto _test_eof52;
		st_case_52:
		if ( ( (*( p))) == 97 ) {
			goto _st53;
		}
		{
			goto _st0;
		}
		_st53:
		p+= 1;
		if ( p == pe )
			goto _test_eof53;
		st_case_53:
		if ( ( (*( p))) == 97 ) {
			goto _st54;
		}
		{
			goto _st0;
		}
		_st54:
		p+= 1;
		if ( p == pe )
			goto _test_eof54;
		st_case_54:
		if ( ( (*( p))) == 97 ) {
			goto _st55;
		}
		{
			goto _st0;
		}
		_st55:
		p+= 1;
		if ( p == pe )
			goto _test_eof55;
		st_case_55:
		if ( ( (*( p))) == 97 ) {
			goto _st56;
		}
		{
			goto _st0;
		}
		_st56:
		p+= 1;
		if ( p == pe )
			goto _test_eof56;
		st_case_56:
		if ( ( (*( p))) == 97 ) {
			goto _st57;
		}
		{
			goto _st0;
		}
		_st57:
		p+= 1;
		if ( p == pe )
			goto _test_eof57;
		st_case_57:
		if ( ( (*( p))) == 97 ) {
			goto _st58;
		}
		{
			goto _st0;
		}
		_st58:
		p+= 1;
		if ( p == pe )
			goto _test_eof58;
		st_case_58:
		if ( ( (*( p))) == 97 ) {
			goto _st59;
		}
		{
			goto _st0;
		}
		_st59:
		p+= 1;
		if ( p == pe )
			goto _test_eof59;
		st_case_59:
		if ( ( (*( p))) == 97 ) {
			goto _st60;
		}
		{
			goto _st0;
		}
		_st60:
		p+= 1;
		if ( p == pe )
			goto _test_eof60;
		st_case_60:
		if ( ( (*( p))) == 97 ) {
			goto _st61;
		}
		{
			goto _st0;
		}
		_st61:
		p+= 1;
		if ( p == pe )
			goto _test_eof61;
		st_case_61:
		if ( ( (*( p))) == 97 ) {
			goto _st62;
		}
		{
			goto _st0;
		}
		_st62:
		p+= 1;
		if ( p == pe )
			goto _test_eof62;
		st_case_62:
		if ( ( (*( p))) == 97 ) {
			goto _st63;
		}
		{
			goto _st0;
		}
		_st63:
		p+= 1;
		if ( p == pe )
			goto _test_eof63;
		st_case_63:
		if ( ( (*( p))) == 97 ) {
			goto _st64;
		}
		{
			goto _st0;
		}
		_st64:
		p+= 1;
		if ( p == pe )
			goto _test_eof64;
		st_case_64:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr65;
			}
			case 97: {
				goto _ctr66;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof65: cs = 65; goto _test_eof; 
		_test_eof1: cs = 1; goto _test_eof; 
		_test_eof2: cs = 2; goto _test_eof; 
		_test_eof3: cs = 3; goto _test_eof; 
		_test_eof4: cs = 4; goto _test_eof; 
		_test_eof5: cs = 5; goto _test_eof; 
		_test_eof6: cs = 6; goto _test_eof; 
		_test_eof7: cs = 7; goto _test_eof; 
		_test_eof8: cs = 8; goto _test_eof; 
		_test_eof9: cs = 9; goto _test_eof; 
		_test_eof10: cs = 10; goto _test_eof; 
		_test_eof11: cs = 11; goto _test_eof; 
		_test_eof12: cs = 12; goto _test_eof; 
		_test_eof13: cs = 13; goto _test_eof; 
		_test_eof14: cs = 14; goto _test_eof; 
		_test_eof15: cs = 15; goto _test_eof; 
		_test_eof16: cs = 16; goto _test_eof; 
		_test_eof17: cs = 17; goto _test_eof; 
		_test_eof18: cs = 18; goto _test_eof; 
		_test_eof19: cs = 19; goto _test_eof; 
		_test_eof20: cs = 20; goto _test_eof; 
		_test_eof21: cs = 21; goto _test_eof; 
		_test_eof22: cs = 22; goto _test_eof; 
		_test_eof23: cs = 23; goto _test_eof; 
		_test_eof24: cs = 24; goto _test_eof; 
		_test_eof25: cs = 25; goto _test_eof; 
		_test_eof26: cs = 26; goto _test_eof; 
		_test_eof27: cs = 27; goto _test_eof; 
		_test_eof28: cs = 28; goto _test_eof; 
		_test_eof29: cs = 29; goto _test_eof; 
		_test_eof30: cs = 30; goto _test_eof; 
		_test_eof31: cs = 31; goto _test_eof; 
		_test_eof32: cs = 32; goto _test_eof; 
		_test_eof33: cs = 33; goto _test_eof; 
		_test_eof34: cs = 34; goto _test_eof; 
		_test_eof35: cs = 35; goto _test_eof; 
		_test_eof36: cs = 36; goto _test_eof; 
		_test_eof37: cs = 37; goto _test_eof; 
		_test_eof38: cs = 38; goto _test_eof; 
		_test_eof39: cs = 39; goto _test_eof; 
		_test_eof40: cs = 40; goto _test_eof; 
		_test_eof41: cs = 41; goto _test_eof; 
		_test_eof42: cs = 42; goto _test_eof; 
		_test_eof43: cs = 43; goto _test_eof; 
		_test_eof44: cs = 44; goto _test_eof; 
		_test_eof45: cs = 45; goto _test_eof; 
		_test_eof46: cs = 46; goto _test_eof; 
		_test_eof47: cs = 47; goto _test_eof; 
		_test_eof48: cs = 48; goto _test_eof; 
		_test_eof49: cs = 49; goto _test_eof; 
		_test_eof50: cs = 50; goto _test_eof; 
		_test_eof51: cs = 51; goto _test_eof; 
		_test_eof52: cs = 52; goto _test_eof; 
		_test_eof53: cs = 53; goto _test_eof; 
		_test_eof54: cs = 54; goto _test_eof; 
		_test_eof55: cs = 55; goto _test_eof; 
		_test_eof56: cs = 56; goto _test_eof; 
		_test_eof57: cs = 57; goto _test_eof; 
		_test_eof58: cs = 58; goto _test_eof; 
		_test_eof59: cs = 59; goto _test_eof; 
		_test_eof60: cs = 60; goto _test_eof; 
		_test_eof61: cs = 61; goto _test_eof; 
		_test_eof62: cs = 62; goto _test_eof; 
		_test_eof63: cs = 63; goto _test_eof; 
		_test_eof64: cs = 64; goto _test_eof; 
		
		_test_eof: {}
		if ( cs >= 65 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/32__iter_64.rl"
	
	
	in->p = p;
	in->pe = pe;
}
