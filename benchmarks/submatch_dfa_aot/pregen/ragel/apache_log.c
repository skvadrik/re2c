#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"



#line 12 "gen/ragel/apache_log.c"
static const int apache_log_start = 25;
static const int apache_log_first_final = 25;
static const int apache_log_error = 0;

static const int apache_log_en_main = 25;


#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*h1, *i1, *a1, *d1, *r1, *s1, *z1, *u1, *g1,
	*h2, *i2, *a2, *d2, *r2, *s2, *z2, *u2, *g2;
	int cs;
	
	
#line 33 "gen/ragel/apache_log.c"
	{
		cs = (int)apache_log_start;
	}
	
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
	
	
#line 41 "gen/ragel/apache_log.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 25:
			goto st_case_25;
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
		}
		goto st_out;
		_ctr41:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			g2 = p; }
		
#line 105 "gen/ragel/apache_log.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			
			OUT("host: ",     h1, h2);
			OUT("userid: ",   i1, i2);
			OUT("authuser: ", a1, a2);
			OUT("date: ",     d1, d2);
			OUT("request: ",  r1, r2);
			OUT("status: ",   s1, s2);
			OUT("size: ",     z1, z2);
			OUT("url: ",      u1, u2);
			OUT("agent: ",    g1, g2);
			outc(out, '\n');
		}
		
#line 122 "gen/ragel/apache_log.c"
		
		goto _st25;
		_st25:
		p+= 1;
		if ( p == pe )
			goto _test_eof25;
		st_case_25:
		if ( ( (*( p))) == 46 ) {
			goto _ctr44;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _ctr44;
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr44:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			h1 = p; }
		
#line 148 "gen/ragel/apache_log.c"
		
		goto _st1;
		_st1:
		p+= 1;
		if ( p == pe )
			goto _test_eof1;
		st_case_1:
		switch( ( (*( p))) ) {
			case 9: {
				goto _ctr2;
			}
			case 32: {
				goto _ctr2;
			}
			case 46: {
				goto _st1;
			}
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st1;
		}
		{
			goto _st0;
		}
		_ctr2:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			h2 = p; }
		
#line 178 "gen/ragel/apache_log.c"
		
		goto _st2;
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
		switch( ( (*( p))) ) {
			case 9: {
				goto _st2;
			}
			case 32: {
				goto _st2;
			}
			case 45: {
				goto _ctr4;
			}
		}
		{
			goto _st0;
		}
		_ctr4:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			i1 = p; }
		
#line 205 "gen/ragel/apache_log.c"
		
		goto _st3;
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		switch( ( (*( p))) ) {
			case 9: {
				goto _ctr6;
			}
			case 32: {
				goto _ctr6;
			}
		}
		{
			goto _st0;
		}
		_ctr6:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			i2 = p; }
		
#line 229 "gen/ragel/apache_log.c"
		
		goto _st4;
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		switch( ( (*( p))) ) {
			case 9: {
				goto _st4;
			}
			case 32: {
				goto _st4;
			}
			case 45: {
				goto _ctr8;
			}
		}
		{
			goto _st0;
		}
		_ctr8:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			a1 = p; }
		
#line 256 "gen/ragel/apache_log.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 9: {
				goto _ctr10;
			}
			case 32: {
				goto _ctr10;
			}
		}
		{
			goto _st0;
		}
		_ctr10:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			a2 = p; }
		
#line 280 "gen/ragel/apache_log.c"
		
		goto _st6;
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		switch( ( (*( p))) ) {
			case 9: {
				goto _st6;
			}
			case 32: {
				goto _st6;
			}
			case 91: {
				goto _ctr12;
			}
		}
		{
			goto _st0;
		}
		_ctr12:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			d1 = p; }
		
#line 307 "gen/ragel/apache_log.c"
		
		goto _st7;
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		switch( ( (*( p))) ) {
			case 10: {
				goto _st0;
			}
			case 93: {
				goto _st0;
			}
		}
		{
			goto _st8;
		}
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		switch( ( (*( p))) ) {
			case 10: {
				goto _st0;
			}
			case 93: {
				goto _st9;
			}
		}
		{
			goto _st8;
		}
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
		switch( ( (*( p))) ) {
			case 9: {
				goto _ctr16;
			}
			case 32: {
				goto _ctr16;
			}
		}
		{
			goto _st0;
		}
		_ctr16:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			d2 = p; }
		
#line 363 "gen/ragel/apache_log.c"
		
		goto _st10;
		_st10:
		p+= 1;
		if ( p == pe )
			goto _test_eof10;
		st_case_10:
		switch( ( (*( p))) ) {
			case 9: {
				goto _st10;
			}
			case 32: {
				goto _st10;
			}
			case 34: {
				goto _ctr18;
			}
		}
		{
			goto _st0;
		}
		_ctr18:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			r1 = p; }
		
#line 390 "gen/ragel/apache_log.c"
		
		goto _st11;
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
		switch( ( (*( p))) ) {
			case 10: {
				goto _st0;
			}
			case 34: {
				goto _st0;
			}
		}
		{
			goto _st12;
		}
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
		switch( ( (*( p))) ) {
			case 10: {
				goto _st0;
			}
			case 34: {
				goto _st13;
			}
		}
		{
			goto _st12;
		}
		_st13:
		p+= 1;
		if ( p == pe )
			goto _test_eof13;
		st_case_13:
		switch( ( (*( p))) ) {
			case 9: {
				goto _ctr22;
			}
			case 32: {
				goto _ctr22;
			}
		}
		{
			goto _st0;
		}
		_ctr22:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			r2 = p; }
		
#line 446 "gen/ragel/apache_log.c"
		
		goto _st14;
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
		switch( ( (*( p))) ) {
			case 9: {
				goto _st14;
			}
			case 32: {
				goto _st14;
			}
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _ctr24;
		}
		{
			goto _st0;
		}
		_ctr24:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			s1 = p; }
		
#line 473 "gen/ragel/apache_log.c"
		
		goto _st15;
		_st15:
		p+= 1;
		if ( p == pe )
			goto _test_eof15;
		st_case_15:
		switch( ( (*( p))) ) {
			case 9: {
				goto _ctr26;
			}
			case 32: {
				goto _ctr26;
			}
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st15;
		}
		{
			goto _st0;
		}
		_ctr26:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			s2 = p; }
		
#line 500 "gen/ragel/apache_log.c"
		
		goto _st16;
		_st16:
		p+= 1;
		if ( p == pe )
			goto _test_eof16;
		st_case_16:
		switch( ( (*( p))) ) {
			case 9: {
				goto _st16;
			}
			case 32: {
				goto _st16;
			}
			case 45: {
				goto _ctr28;
			}
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _ctr29;
		}
		{
			goto _st0;
		}
		_ctr28:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			z1 = p; }
		
#line 530 "gen/ragel/apache_log.c"
		
		goto _st17;
		_st17:
		p+= 1;
		if ( p == pe )
			goto _test_eof17;
		st_case_17:
		switch( ( (*( p))) ) {
			case 9: {
				goto _ctr31;
			}
			case 32: {
				goto _ctr31;
			}
		}
		{
			goto _st0;
		}
		_ctr31:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			z2 = p; }
		
#line 554 "gen/ragel/apache_log.c"
		
		goto _st18;
		_st18:
		p+= 1;
		if ( p == pe )
			goto _test_eof18;
		st_case_18:
		switch( ( (*( p))) ) {
			case 9: {
				goto _st18;
			}
			case 32: {
				goto _st18;
			}
			case 34: {
				goto _ctr33;
			}
		}
		{
			goto _st0;
		}
		_ctr33:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			u1 = p; }
		
#line 581 "gen/ragel/apache_log.c"
		
		goto _st19;
		_st19:
		p+= 1;
		if ( p == pe )
			goto _test_eof19;
		st_case_19:
		switch( ( (*( p))) ) {
			case 10: {
				goto _st0;
			}
			case 34: {
				goto _st20;
			}
		}
		{
			goto _st19;
		}
		_st20:
		p+= 1;
		if ( p == pe )
			goto _test_eof20;
		st_case_20:
		switch( ( (*( p))) ) {
			case 9: {
				goto _ctr36;
			}
			case 32: {
				goto _ctr36;
			}
		}
		{
			goto _st0;
		}
		_ctr36:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			u2 = p; }
		
#line 621 "gen/ragel/apache_log.c"
		
		goto _st21;
		_st21:
		p+= 1;
		if ( p == pe )
			goto _test_eof21;
		st_case_21:
		switch( ( (*( p))) ) {
			case 9: {
				goto _st21;
			}
			case 32: {
				goto _st21;
			}
			case 34: {
				goto _ctr38;
			}
		}
		{
			goto _st0;
		}
		_ctr38:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			g1 = p; }
		
#line 648 "gen/ragel/apache_log.c"
		
		goto _st22;
		_st22:
		p+= 1;
		if ( p == pe )
			goto _test_eof22;
		st_case_22:
		switch( ( (*( p))) ) {
			case 10: {
				goto _st0;
			}
			case 34: {
				goto _st23;
			}
		}
		{
			goto _st22;
		}
		_st23:
		p+= 1;
		if ( p == pe )
			goto _test_eof23;
		st_case_23:
		if ( ( (*( p))) == 10 ) {
			goto _ctr41;
		}
		{
			goto _st0;
		}
		_ctr29:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
			z1 = p; }
		
#line 683 "gen/ragel/apache_log.c"
		
		goto _st24;
		_st24:
		p+= 1;
		if ( p == pe )
			goto _test_eof24;
		st_case_24:
		switch( ( (*( p))) ) {
			case 9: {
				goto _ctr31;
			}
			case 32: {
				goto _ctr31;
			}
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st24;
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof25: cs = 25; goto _test_eof; 
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
		
		_test_eof: {}
		if ( cs >= 25 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
	
	
	in->p = p;
	in->pe = pe;
}
