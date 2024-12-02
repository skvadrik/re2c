#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/38__rep_23_rep_19_rep_17.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/38__rep_23_rep_19_rep_17.rl"



#line 12 "gen/ragel/38__rep_23_rep_19_rep_17.c"
static const int aaa_start = 24;
static const int aaa_first_final = 24;
static const int aaa_error = 0;

static const int aaa_en_main = 24;


#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/38__rep_23_rep_19_rep_17.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *s;
	int cs;
	
	
#line 31 "gen/ragel/38__rep_23_rep_19_rep_17.c"
	{
		cs = (int)aaa_start;
	}
	
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/38__rep_23_rep_19_rep_17.rl"
	
	
#line 39 "gen/ragel/38__rep_23_rep_19_rep_17.c"
	{
		switch ( cs ) {
			case 24:
			goto st_case_24;
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
		}
		_ctr24:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/38__rep_23_rep_19_rep_17.rl"
			
			outs(out, s, p);
			outc(out, '.');
			s = p;
		}
		
#line 102 "gen/ragel/38__rep_23_rep_19_rep_17.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/38__rep_23_rep_19_rep_17.rl"
			outc(out, '\n'); }
		
#line 108 "gen/ragel/38__rep_23_rep_19_rep_17.c"
		
		goto _st24;
		_ctr27:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/38__rep_23_rep_19_rep_17.rl"
			s = p; }
		
#line 116 "gen/ragel/38__rep_23_rep_19_rep_17.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/38__rep_23_rep_19_rep_17.rl"
			outc(out, '\n'); }
		
#line 122 "gen/ragel/38__rep_23_rep_19_rep_17.c"
		
		goto _st24;
		_st24:
		p+= 1;
		st_case_24:
		if ( p == pe )
			goto _out24;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr27;
			}
			case 97: {
				goto _ctr28;
			}
		}
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr25:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/38__rep_23_rep_19_rep_17.rl"
			
			outs(out, s, p);
			outc(out, '.');
			s = p;
		}
		
#line 151 "gen/ragel/38__rep_23_rep_19_rep_17.c"
		
		goto _st1;
		_ctr28:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/38__rep_23_rep_19_rep_17.rl"
			s = p; }
		
#line 159 "gen/ragel/38__rep_23_rep_19_rep_17.c"
		
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
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr24;
			}
			case 97: {
				goto _ctr25;
			}
		}
		goto _st0;
		_out24: cs = 24; goto _out; 
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
		_out: {}
	}
	
#line 48 "../../../benchmarks/submatch_dfa_aot/src/ragel/38__rep_23_rep_19_rep_17.rl"
	
	
	in->p = p;
	in->pe = pe;
}
