#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/31__rep_cat_13_11_7.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/31__rep_cat_13_11_7.rl"



#line 12 "gen/ragel/31__rep_cat_13_11_7.c"
static const int aaa_start = 32;
static const int aaa_first_final = 32;
static const int aaa_error = 0;

static const int aaa_en_main = 32;


#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/31__rep_cat_13_11_7.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *s = p;
	int cs;
	
	
#line 31 "gen/ragel/31__rep_cat_13_11_7.c"
	{
		cs = (int)aaa_start;
	}
	
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/31__rep_cat_13_11_7.rl"
	
	
#line 39 "gen/ragel/31__rep_cat_13_11_7.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 32:
			goto st_case_32;
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
		}
		goto st_out;
		_ctr34:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/31__rep_cat_13_11_7.rl"
			
			outs(out, s, p);
			outc(out, ';');
			s = p;
		}
		
#line 121 "gen/ragel/31__rep_cat_13_11_7.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/31__rep_cat_13_11_7.rl"
			outc(out, '\n'); }
		
#line 127 "gen/ragel/31__rep_cat_13_11_7.c"
		
		goto _st32;
		_ctr37:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/31__rep_cat_13_11_7.rl"
			outc(out, '\n'); }
		
#line 135 "gen/ragel/31__rep_cat_13_11_7.c"
		
		goto _st32;
		_st32:
		p+= 1;
		if ( p == pe )
			goto _test_eof32;
		st_case_32:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr37;
			}
			case 97: {
				goto _st1;
			}
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr35:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/31__rep_cat_13_11_7.rl"
			
			outs(out, s, p);
			outc(out, ';');
			s = p;
		}
		
#line 167 "gen/ragel/31__rep_cat_13_11_7.c"
		
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
			goto _ctr14;
		}
		{
			goto _st0;
		}
		_ctr14:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/31__rep_cat_13_11_7.rl"
			
			outs(out, s, p);
			outc(out, '.');
			s = p;
		}
		
#line 322 "gen/ragel/31__rep_cat_13_11_7.c"
		
		goto _st14;
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
			goto _ctr26;
		}
		{
			goto _st0;
		}
		_ctr26:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/31__rep_cat_13_11_7.rl"
			
			outs(out, s, p);
			outc(out, '.');
			s = p;
		}
		
#line 455 "gen/ragel/31__rep_cat_13_11_7.c"
		
		goto _st25;
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
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr34;
			}
			case 97: {
				goto _ctr35;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof32: cs = 32; goto _test_eof; 
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
		
		_test_eof: {}
		if ( cs >= 32 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/31__rep_cat_13_11_7.rl"
	
	
	in->p = p;
	in->pe = pe;
}
