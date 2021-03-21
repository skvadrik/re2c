#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/33__rep_alt_5_3_2.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/33__rep_alt_5_3_2.rl"



#line 12 "gen/ragel/33__rep_alt_5_3_2.c"
static const int aaa_start = 6;
static const int aaa_first_final = 6;
static const int aaa_error = 0;

static const int aaa_en_main = 6;


#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/33__rep_alt_5_3_2.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *s;
	int cs;
	
	
#line 31 "gen/ragel/33__rep_alt_5_3_2.c"
	{
		cs = (int)aaa_start;
	}
	
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/33__rep_alt_5_3_2.rl"
	
	
#line 39 "gen/ragel/33__rep_alt_5_3_2.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 6:
			goto st_case_6;
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
		}
		goto st_out;
		_ctr3:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/33__rep_alt_5_3_2.rl"
			
			outs(out, s, p);
			outc(out, '.');
			s = p;
		}
		
#line 69 "gen/ragel/33__rep_alt_5_3_2.c"
		
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/33__rep_alt_5_3_2.rl"
			outc(out, '\n'); }
		
#line 75 "gen/ragel/33__rep_alt_5_3_2.c"
		
		goto _st6;
		_ctr9:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/33__rep_alt_5_3_2.rl"
			s = p; }
		
#line 83 "gen/ragel/33__rep_alt_5_3_2.c"
		
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/33__rep_alt_5_3_2.rl"
			outc(out, '\n'); }
		
#line 89 "gen/ragel/33__rep_alt_5_3_2.c"
		
		goto _st6;
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr9;
			}
			case 97: {
				goto _ctr10;
			}
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr7:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/33__rep_alt_5_3_2.rl"
			
			outs(out, s, p);
			outc(out, '.');
			s = p;
		}
		
#line 121 "gen/ragel/33__rep_alt_5_3_2.c"
		
		goto _st1;
		_ctr10:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/33__rep_alt_5_3_2.rl"
			s = p; }
		
#line 129 "gen/ragel/33__rep_alt_5_3_2.c"
		
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
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr3;
			}
			case 97: {
				goto _st3;
			}
		}
		{
			goto _st0;
		}
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr3;
			}
			case 97: {
				goto _st4;
			}
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
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr3;
			}
			case 97: {
				goto _ctr7;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof6: cs = 6; goto _test_eof; 
		_test_eof1: cs = 1; goto _test_eof; 
		_test_eof2: cs = 2; goto _test_eof; 
		_test_eof3: cs = 3; goto _test_eof; 
		_test_eof4: cs = 4; goto _test_eof; 
		_test_eof5: cs = 5; goto _test_eof; 
		
		_test_eof: {}
		if ( cs >= 6 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/33__rep_alt_5_3_2.rl"
	
	
	in->p = p;
	in->pe = pe;
}
