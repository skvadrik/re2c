#line 1 "../../../benchmarks/c/src/ragel/submatch_31__rep_cat_13_11_7.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 28 "../../../benchmarks/c/src/ragel/submatch_31__rep_cat_13_11_7.rl"



#line 9 "gen/ragel/submatch_31__rep_cat_13_11_7.c"
static const int aaa_start = 32;
static const int aaa_first_final = 32;
static const int aaa_error = 0;

static const int aaa_en_main = 32;


#line 30 "../../../benchmarks/c/src/ragel/submatch_31__rep_cat_13_11_7.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *s = p;
	int cs;
	

#line 25 "gen/ragel/submatch_31__rep_cat_13_11_7.c"
	{
		cs = (int)aaa_start;
	}
	
#line 39 "../../../benchmarks/c/src/ragel/submatch_31__rep_cat_13_11_7.rl"


#line 30 "gen/ragel/submatch_31__rep_cat_13_11_7.c"
{
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
		_ctr34:
			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_31__rep_cat_13_11_7.rl"
			
			outs(out, s, p);
			outc(out, ';');
			s = p;
		}
		
#line 108 "gen/ragel/submatch_31__rep_cat_13_11_7.c"

			{
#line 25 "../../../benchmarks/c/src/ragel/submatch_31__rep_cat_13_11_7.rl"
			outc(out, '\n'); }
		
#line 113 "gen/ragel/submatch_31__rep_cat_13_11_7.c"

		goto _st32;
		_ctr37:
			{
#line 25 "../../../benchmarks/c/src/ragel/submatch_31__rep_cat_13_11_7.rl"
			outc(out, '\n'); }
		
#line 120 "gen/ragel/submatch_31__rep_cat_13_11_7.c"

		goto _st32;
		_st32:
		p+= 1;
		st_case_32:
		if ( p == pe )
			goto _out32;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr37;
			}
			case 97: {
				goto _st1;
			}
		}
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr35:
			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_31__rep_cat_13_11_7.rl"
			
			outs(out, s, p);
			outc(out, ';');
			s = p;
		}
		
#line 148 "gen/ragel/submatch_31__rep_cat_13_11_7.c"

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
			goto _ctr14;
		}
		goto _st0;
		_ctr14:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_31__rep_cat_13_11_7.rl"
			
			outs(out, s, p);
			outc(out, '.');
			s = p;
		}
		
#line 276 "gen/ragel/submatch_31__rep_cat_13_11_7.c"

		goto _st14;
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
			goto _st24;
		}
		goto _st0;
		_st24:
		p+= 1;
		st_case_24:
		if ( p == pe )
			goto _out24;
		if ( ( (*( p))) == 97 ) {
			goto _ctr26;
		}
		goto _st0;
		_ctr26:
			{
#line 14 "../../../benchmarks/c/src/ragel/submatch_31__rep_cat_13_11_7.rl"
			
			outs(out, s, p);
			outc(out, '.');
			s = p;
		}
		
#line 386 "gen/ragel/submatch_31__rep_cat_13_11_7.c"

		goto _st25;
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
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr34;
			}
			case 97: {
				goto _ctr35;
			}
		}
		goto _st0;
		_out32: cs = 32; goto _out; 
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
		_out: {}
	}
	
#line 40 "../../../benchmarks/c/src/ragel/submatch_31__rep_cat_13_11_7.rl"

	
	in->p = p;
	in->pe = pe;
}
