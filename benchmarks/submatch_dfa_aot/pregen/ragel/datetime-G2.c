#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"



#line 12 "gen/ragel/datetime-G2.c"
static const int datetime_start = 35;
static const int datetime_first_final = 35;
static const int datetime_error = 0;

static const int datetime_en_main = 35;


#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*s1, *y1, *h1, *m1, *d1, *M1, *z1,
	*s2, *y2, *h2, *m2, *d2, *M2, *z2;
	int cs;
	
	
#line 33 "gen/ragel/datetime-G2.c"
	{
		cs = (int)datetime_start;
	}
	
#line 48 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
	
	
#line 41 "gen/ragel/datetime-G2.c"
	{
		if ( p == pe )
			goto _test_eof;
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
		goto st_out;
		_ctr43:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			z2 = p; }
		
#line 125 "gen/ragel/datetime-G2.c"
		
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			
			OUT("year: ",    y1, y2);
			OUT("month: ",   m1, m2);
			OUT("day: ",     d1, d2);
			OUT("hours: ",   h1, h2);
			OUT("minutes: ", M1, M2);
			OUT("seconds: ", s1, s2);
			OUT("tz: ",      z1, z2);
			outc(out, '\n');
		}
		
#line 140 "gen/ragel/datetime-G2.c"
		
		goto _st35;
		_st35:
		p+= 1;
		if ( p == pe )
			goto _test_eof35;
		st_case_35:
		if ( ( (*( p))) == 48 ) {
			goto _ctr53;
		}
		if ( 49 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _ctr54;
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr53:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			y1 = p; }
		
#line 166 "gen/ragel/datetime-G2.c"
		
		goto _st1;
		_st1:
		p+= 1;
		if ( p == pe )
			goto _test_eof1;
		st_case_1:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( ( (*( p))) == 45 ) {
			goto _ctr5;
		}
		{
			goto _st0;
		}
		_ctr5:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			y2 = p; }
		
#line 218 "gen/ragel/datetime-G2.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 48: {
				goto _ctr7;
			}
			case 49: {
				goto _ctr8;
			}
		}
		{
			goto _st0;
		}
		_ctr7:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			m1 = p; }
		
#line 242 "gen/ragel/datetime-G2.c"
		
		goto _st6;
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		if ( 49 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( ( (*( p))) == 45 ) {
			goto _ctr11;
		}
		{
			goto _st0;
		}
		_ctr11:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			m2 = p; }
		
#line 272 "gen/ragel/datetime-G2.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
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
		{
			goto _st0;
		}
		_ctr13:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			d1 = p; }
		
#line 299 "gen/ragel/datetime-G2.c"
		
		goto _st9;
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
		if ( 49 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( ( (*( p))) == 84 ) {
			goto _ctr18;
		}
		{
			goto _st0;
		}
		_ctr18:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			d2 = p; }
		
#line 329 "gen/ragel/datetime-G2.c"
		
		goto _st11;
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
		if ( ( (*( p))) == 50 ) {
			goto _ctr21;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 49 ) {
			goto _ctr20;
		}
		{
			goto _st0;
		}
		_ctr20:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			h1 = p; }
		
#line 351 "gen/ragel/datetime-G2.c"
		
		goto _st12;
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( ( (*( p))) == 58 ) {
			goto _ctr24;
		}
		{
			goto _st0;
		}
		_ctr24:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			h2 = p; }
		
#line 381 "gen/ragel/datetime-G2.c"
		
		goto _st14;
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 53 ) {
			goto _ctr26;
		}
		{
			goto _st0;
		}
		_ctr26:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			M1 = p; }
		
#line 400 "gen/ragel/datetime-G2.c"
		
		goto _st15;
		_st15:
		p+= 1;
		if ( p == pe )
			goto _test_eof15;
		st_case_15:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( ( (*( p))) == 58 ) {
			goto _ctr29;
		}
		{
			goto _st0;
		}
		_ctr29:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			M2 = p; }
		
#line 430 "gen/ragel/datetime-G2.c"
		
		goto _st17;
		_st17:
		p+= 1;
		if ( p == pe )
			goto _test_eof17;
		st_case_17:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 53 ) {
			goto _ctr31;
		}
		{
			goto _st0;
		}
		_ctr31:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			s1 = p; }
		
#line 449 "gen/ragel/datetime-G2.c"
		
		goto _st18;
		_st18:
		p+= 1;
		if ( p == pe )
			goto _test_eof18;
		st_case_18:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		{
			goto _st0;
		}
		_ctr34:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			s2 = p; }
		
#line 487 "gen/ragel/datetime-G2.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			z1 = p; }
		
#line 493 "gen/ragel/datetime-G2.c"
		
		goto _st20;
		_st20:
		p+= 1;
		if ( p == pe )
			goto _test_eof20;
		st_case_20:
		if ( ( (*( p))) == 50 ) {
			goto _st26;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 49 ) {
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
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( ( (*( p))) == 58 ) {
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
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 53 ) {
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
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st25;
		}
		{
			goto _st0;
		}
		_ctr35:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			s2 = p; }
		
#line 559 "gen/ragel/datetime-G2.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			z1 = p; }
		
#line 565 "gen/ragel/datetime-G2.c"
		
		goto _st25;
		_st25:
		p+= 1;
		if ( p == pe )
			goto _test_eof25;
		st_case_25:
		if ( ( (*( p))) == 10 ) {
			goto _ctr43;
		}
		{
			goto _st0;
		}
		_st26:
		p+= 1;
		if ( p == pe )
			goto _test_eof26;
		st_case_26:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 51 ) {
			goto _st22;
		}
		{
			goto _st0;
		}
		_ctr21:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			h1 = p; }
		
#line 595 "gen/ragel/datetime-G2.c"
		
		goto _st27;
		_st27:
		p+= 1;
		if ( p == pe )
			goto _test_eof27;
		st_case_27:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 51 ) {
			goto _st13;
		}
		{
			goto _st0;
		}
		_ctr14:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			d1 = p; }
		
#line 614 "gen/ragel/datetime-G2.c"
		
		goto _st28;
		_st28:
		p+= 1;
		if ( p == pe )
			goto _test_eof28;
		st_case_28:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st10;
		}
		{
			goto _st0;
		}
		_ctr15:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			d1 = p; }
		
#line 633 "gen/ragel/datetime-G2.c"
		
		goto _st29;
		_st29:
		p+= 1;
		if ( p == pe )
			goto _test_eof29;
		st_case_29:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 49 ) {
			goto _st10;
		}
		{
			goto _st0;
		}
		_ctr8:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			m1 = p; }
		
#line 652 "gen/ragel/datetime-G2.c"
		
		goto _st30;
		_st30:
		p+= 1;
		if ( p == pe )
			goto _test_eof30;
		st_case_30:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 50 ) {
			goto _st7;
		}
		{
			goto _st0;
		}
		_ctr54:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
			y1 = p; }
		
#line 671 "gen/ragel/datetime-G2.c"
		
		goto _st31;
		_st31:
		p+= 1;
		if ( p == pe )
			goto _test_eof31;
		st_case_31:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( ( (*( p))) == 45 ) {
			goto _ctr5;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st34;
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof35: cs = 35; goto _test_eof; 
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
		
		_test_eof: {}
		if ( cs >= 35 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 49 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
	
	
	in->p = p;
	in->pe = pe;
}
