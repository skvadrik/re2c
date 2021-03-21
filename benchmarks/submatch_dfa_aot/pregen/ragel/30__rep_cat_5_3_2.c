#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__rep_cat_5_3_2.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__rep_cat_5_3_2.rl"



#line 12 "gen/ragel/30__rep_cat_5_3_2.c"
static const int aaa_start = 11;
static const int aaa_first_final = 11;
static const int aaa_error = 0;

static const int aaa_en_main = 11;


#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__rep_cat_5_3_2.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *s = p;
	int cs;
	
	
#line 31 "gen/ragel/30__rep_cat_5_3_2.c"
	{
		cs = (int)aaa_start;
	}
	
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__rep_cat_5_3_2.rl"
	
	
#line 39 "gen/ragel/30__rep_cat_5_3_2.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 11:
			goto st_case_11;
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
		}
		goto st_out;
		_ctr13:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__rep_cat_5_3_2.rl"
			
			outs(out, s, p);
			outc(out, ';');
			s = p;
		}
		
#line 79 "gen/ragel/30__rep_cat_5_3_2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__rep_cat_5_3_2.rl"
			outc(out, '\n'); }
		
#line 85 "gen/ragel/30__rep_cat_5_3_2.c"
		
		goto _st11;
		_ctr16:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__rep_cat_5_3_2.rl"
			outc(out, '\n'); }
		
#line 93 "gen/ragel/30__rep_cat_5_3_2.c"
		
		goto _st11;
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr16;
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
		_ctr14:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__rep_cat_5_3_2.rl"
			
			outs(out, s, p);
			outc(out, ';');
			s = p;
		}
		
#line 125 "gen/ragel/30__rep_cat_5_3_2.c"
		
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
			goto _ctr6;
		}
		{
			goto _st0;
		}
		_ctr6:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__rep_cat_5_3_2.rl"
			
			outs(out, s, p);
			outc(out, '.');
			s = p;
		}
		
#line 192 "gen/ragel/30__rep_cat_5_3_2.c"
		
		goto _st6;
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
			goto _ctr10;
		}
		{
			goto _st0;
		}
		_ctr10:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__rep_cat_5_3_2.rl"
			
			outs(out, s, p);
			outc(out, '.');
			s = p;
		}
		
#line 237 "gen/ragel/30__rep_cat_5_3_2.c"
		
		goto _st9;
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
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr13;
			}
			case 97: {
				goto _ctr14;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof11: cs = 11; goto _test_eof; 
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
		
		_test_eof: {}
		if ( cs >= 11 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__rep_cat_5_3_2.rl"
	
	
	in->p = p;
	in->pe = pe;
}
