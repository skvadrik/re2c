#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"



#line 12 "gen/ragel/05__datetime.c"
static const int datetime_start = 35;
static const int datetime_first_final = 35;
static const int datetime_error = 0;

static const int datetime_en_main = 35;


#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*s1, *y1, *h1, *m1, *d1, *M1, *z1,
	*s2, *y2, *h2, *m2, *d2, *M2, *z2;
	int cs;
	
	
#line 33 "gen/ragel/05__datetime.c"
	{
		cs = (int)datetime_start;
	}
	
#line 48 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
	
	
#line 41 "gen/ragel/05__datetime.c"
	{
		switch ( cs ) {
			case 35:
			goto st_case_35;
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
		}
		_ctr43:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			z2 = p; }
		
#line 122 "gen/ragel/05__datetime.c"
		
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			
			OUT("year: ",    y1, y2);
			OUT("month: ",   m1, m2);
			OUT("day: ",     d1, d2);
			OUT("hours: ",   h1, h2);
			OUT("minutes: ", M1, M2);
			OUT("seconds: ", s1, s2);
			OUT("tz: ",      z1, z2);
			outc(out, '\n');
		}
		
#line 137 "gen/ragel/05__datetime.c"
		
		goto _st35;
		_st35:
		p+= 1;
		st_case_35:
		if ( p == pe )
			goto _out35;
		if ( ( (*( p))) == 48 ) {
			goto _ctr53;
		}
		if ( 49 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _ctr54;
		}
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr53:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			y1 = p; }
		
#line 160 "gen/ragel/05__datetime.c"
		
		goto _st1;
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
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st3;
		}
		goto _st0;
		_st3:
		p+= 1;
		st_case_3:
		if ( p == pe )
			goto _out3;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st4;
		}
		goto _st0;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
		if ( ( (*( p))) == 45 ) {
			goto _ctr5;
		}
		goto _st0;
		_ctr5:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			y2 = p; }
		
#line 204 "gen/ragel/05__datetime.c"
		
		goto _st5;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
		switch( ( (*( p))) ) {
			case 48: {
				goto _ctr7;
			}
			case 49: {
				goto _ctr8;
			}
		}
		goto _st0;
		_ctr7:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			m1 = p; }
		
#line 226 "gen/ragel/05__datetime.c"
		
		goto _st6;
		_st6:
		p+= 1;
		st_case_6:
		if ( p == pe )
			goto _out6;
		if ( 49 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st7;
		}
		goto _st0;
		_st7:
		p+= 1;
		st_case_7:
		if ( p == pe )
			goto _out7;
		if ( ( (*( p))) == 45 ) {
			goto _ctr11;
		}
		goto _st0;
		_ctr11:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			m2 = p; }
		
#line 252 "gen/ragel/05__datetime.c"
		
		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
		switch( ( (*( p))) ) {
			case 48: {
				goto _ctr13;
			}
			case 51: {
				goto _ctr15;
			}
		}
		if ( 49 <= ( (*( p))) && ( (*( p))) <= 50 ) {
			goto _ctr14;
		}
		goto _st0;
		_ctr13:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			d1 = p; }
		
#line 277 "gen/ragel/05__datetime.c"
		
		goto _st9;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
		if ( 49 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st10;
		}
		goto _st0;
		_st10:
		p+= 1;
		st_case_10:
		if ( p == pe )
			goto _out10;
		if ( ( (*( p))) == 84 ) {
			goto _ctr18;
		}
		goto _st0;
		_ctr18:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			d2 = p; }
		
#line 303 "gen/ragel/05__datetime.c"
		
		goto _st11;
		_st11:
		p+= 1;
		st_case_11:
		if ( p == pe )
			goto _out11;
		if ( ( (*( p))) == 50 ) {
			goto _ctr21;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 49 ) {
			goto _ctr20;
		}
		goto _st0;
		_ctr20:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			h1 = p; }
		
#line 323 "gen/ragel/05__datetime.c"
		
		goto _st12;
		_st12:
		p+= 1;
		st_case_12:
		if ( p == pe )
			goto _out12;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st13;
		}
		goto _st0;
		_st13:
		p+= 1;
		st_case_13:
		if ( p == pe )
			goto _out13;
		if ( ( (*( p))) == 58 ) {
			goto _ctr24;
		}
		goto _st0;
		_ctr24:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			h2 = p; }
		
#line 349 "gen/ragel/05__datetime.c"
		
		goto _st14;
		_st14:
		p+= 1;
		st_case_14:
		if ( p == pe )
			goto _out14;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 53 ) {
			goto _ctr26;
		}
		goto _st0;
		_ctr26:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			M1 = p; }
		
#line 366 "gen/ragel/05__datetime.c"
		
		goto _st15;
		_st15:
		p+= 1;
		st_case_15:
		if ( p == pe )
			goto _out15;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st16;
		}
		goto _st0;
		_st16:
		p+= 1;
		st_case_16:
		if ( p == pe )
			goto _out16;
		if ( ( (*( p))) == 58 ) {
			goto _ctr29;
		}
		goto _st0;
		_ctr29:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			M2 = p; }
		
#line 392 "gen/ragel/05__datetime.c"
		
		goto _st17;
		_st17:
		p+= 1;
		st_case_17:
		if ( p == pe )
			goto _out17;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 53 ) {
			goto _ctr31;
		}
		goto _st0;
		_ctr31:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			s1 = p; }
		
#line 409 "gen/ragel/05__datetime.c"
		
		goto _st18;
		_st18:
		p+= 1;
		st_case_18:
		if ( p == pe )
			goto _out18;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st19;
		}
		goto _st0;
		_st19:
		p+= 1;
		st_case_19:
		if ( p == pe )
			goto _out19;
		switch( ( (*( p))) ) {
			case 43: {
				goto _ctr34;
			}
			case 45: {
				goto _ctr34;
			}
			case 90: {
				goto _ctr35;
			}
		}
		goto _st0;
		_ctr34:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			s2 = p; }
		
#line 443 "gen/ragel/05__datetime.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			z1 = p; }
		
#line 449 "gen/ragel/05__datetime.c"
		
		goto _st20;
		_st20:
		p+= 1;
		st_case_20:
		if ( p == pe )
			goto _out20;
		if ( ( (*( p))) == 50 ) {
			goto _st26;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 49 ) {
			goto _st21;
		}
		goto _st0;
		_st21:
		p+= 1;
		st_case_21:
		if ( p == pe )
			goto _out21;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st22;
		}
		goto _st0;
		_st22:
		p+= 1;
		st_case_22:
		if ( p == pe )
			goto _out22;
		if ( ( (*( p))) == 58 ) {
			goto _st23;
		}
		goto _st0;
		_st23:
		p+= 1;
		st_case_23:
		if ( p == pe )
			goto _out23;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 53 ) {
			goto _st24;
		}
		goto _st0;
		_st24:
		p+= 1;
		st_case_24:
		if ( p == pe )
			goto _out24;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st25;
		}
		goto _st0;
		_ctr35:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			s2 = p; }
		
#line 505 "gen/ragel/05__datetime.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			z1 = p; }
		
#line 511 "gen/ragel/05__datetime.c"
		
		goto _st25;
		_st25:
		p+= 1;
		st_case_25:
		if ( p == pe )
			goto _out25;
		if ( ( (*( p))) == 10 ) {
			goto _ctr43;
		}
		goto _st0;
		_st26:
		p+= 1;
		st_case_26:
		if ( p == pe )
			goto _out26;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 51 ) {
			goto _st22;
		}
		goto _st0;
		_ctr21:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			h1 = p; }
		
#line 537 "gen/ragel/05__datetime.c"
		
		goto _st27;
		_st27:
		p+= 1;
		st_case_27:
		if ( p == pe )
			goto _out27;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 51 ) {
			goto _st13;
		}
		goto _st0;
		_ctr14:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			d1 = p; }
		
#line 554 "gen/ragel/05__datetime.c"
		
		goto _st28;
		_st28:
		p+= 1;
		st_case_28:
		if ( p == pe )
			goto _out28;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st10;
		}
		goto _st0;
		_ctr15:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			d1 = p; }
		
#line 571 "gen/ragel/05__datetime.c"
		
		goto _st29;
		_st29:
		p+= 1;
		st_case_29:
		if ( p == pe )
			goto _out29;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 49 ) {
			goto _st10;
		}
		goto _st0;
		_ctr8:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			m1 = p; }
		
#line 588 "gen/ragel/05__datetime.c"
		
		goto _st30;
		_st30:
		p+= 1;
		st_case_30:
		if ( p == pe )
			goto _out30;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 50 ) {
			goto _st7;
		}
		goto _st0;
		_ctr54:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
			y1 = p; }
		
#line 605 "gen/ragel/05__datetime.c"
		
		goto _st31;
		_st31:
		p+= 1;
		st_case_31:
		if ( p == pe )
			goto _out31;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st32;
		}
		goto _st0;
		_st32:
		p+= 1;
		st_case_32:
		if ( p == pe )
			goto _out32;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st33;
		}
		goto _st0;
		_st33:
		p+= 1;
		st_case_33:
		if ( p == pe )
			goto _out33;
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st34;
		}
		goto _st0;
		_st34:
		p+= 1;
		st_case_34:
		if ( p == pe )
			goto _out34;
		if ( ( (*( p))) == 45 ) {
			goto _ctr5;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st34;
		}
		goto _st0;
		_out35: cs = 35; goto _out; 
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
		_out: {}
	}
	
#line 49 "../../../benchmarks/submatch_dfa_aot/src/ragel/05__datetime.rl"
	
	
	in->p = p;
	in->pe = pe;
}
