#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"



#line 12 "gen/ragel/ipv4-G2.c"
static const int ipv4_start = 16;
static const int ipv4_first_final = 16;
static const int ipv4_error = 0;

static const int ipv4_en_main = 16;


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *p1, *p2, *p3, *p4;
	int cs;
	
	
#line 31 "gen/ragel/ipv4-G2.c"
	{
		cs = (int)ipv4_start;
	}
	
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
	
	
#line 39 "gen/ragel/ipv4-G2.c"
	{
		if ( p == pe )
			goto _test_eof;
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
		goto st_out;
		_ctr14:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
			
			outs(out, p1, p2 - 1);
			outc(out, ',');
			outs(out, p2, p3 - 1);
			outc(out, ',');
			outs(out, p3, p4 - 1);
			outc(out, ',');
			outs(out, p4, p);
			outc(out, '\n');
		}
		
#line 94 "gen/ragel/ipv4-G2.c"
		
		goto _st16;
		_st16:
		p+= 1;
		if ( p == pe )
			goto _test_eof16;
		st_case_16:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _ctr21;
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr21:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
			p1 = p; }
		
#line 117 "gen/ragel/ipv4-G2.c"
		
		goto _st1;
		_st1:
		p+= 1;
		if ( p == pe )
			goto _test_eof1;
		st_case_1:
		if ( ( (*( p))) == 46 ) {
			goto _st2;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st14;
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
			goto _ctr4;
		}
		{
			goto _st0;
		}
		_ctr4:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
			p2 = p; }
		
#line 150 "gen/ragel/ipv4-G2.c"
		
		goto _st3;
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		if ( ( (*( p))) == 46 ) {
			goto _st4;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st12;
		}
		{
			goto _st0;
		}
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _ctr8;
		}
		{
			goto _st0;
		}
		_ctr8:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
			p3 = p; }
		
#line 183 "gen/ragel/ipv4-G2.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		if ( ( (*( p))) == 46 ) {
			goto _st6;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st10;
		}
		{
			goto _st0;
		}
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _ctr12;
		}
		{
			goto _st0;
		}
		_ctr12:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
			p4 = p; }
		
#line 216 "gen/ragel/ipv4-G2.c"
		
		goto _st7;
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		if ( ( (*( p))) == 10 ) {
			goto _ctr14;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( ( (*( p))) == 10 ) {
			goto _ctr14;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( ( (*( p))) == 10 ) {
			goto _ctr14;
		}
		{
			goto _st0;
		}
		_st10:
		p+= 1;
		if ( p == pe )
			goto _test_eof10;
		st_case_10:
		if ( ( (*( p))) == 46 ) {
			goto _st6;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( ( (*( p))) == 46 ) {
			goto _st6;
		}
		{
			goto _st0;
		}
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
		if ( ( (*( p))) == 46 ) {
			goto _st4;
		}
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
		if ( ( (*( p))) == 46 ) {
			goto _st4;
		}
		{
			goto _st0;
		}
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
		if ( ( (*( p))) == 46 ) {
			goto _st2;
		}
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
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
		if ( ( (*( p))) == 46 ) {
			goto _st2;
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof16: cs = 16; goto _test_eof; 
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
		
		_test_eof: {}
		if ( cs >= 16 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
