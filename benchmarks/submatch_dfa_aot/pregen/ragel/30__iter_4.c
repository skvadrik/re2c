#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__iter_4.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__iter_4.rl"



#line 12 "gen/ragel/30__iter_4.c"
static const int aaa_start = 5;
static const int aaa_first_final = 5;
static const int aaa_error = 0;

static const int aaa_en_main = 5;


#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__iter_4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *s;
	int cs;
	
	
#line 31 "gen/ragel/30__iter_4.c"
	{
		cs = (int)aaa_start;
	}
	
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__iter_4.rl"
	
	
#line 39 "gen/ragel/30__iter_4.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 5:
			goto st_case_5;
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
		}
		goto st_out;
		_ctr5:
		{
#line 8 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__iter_4.rl"
			
			outs(out, s, p);
			outc(out, '.');
			s = p;
		}
		
#line 67 "gen/ragel/30__iter_4.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__iter_4.rl"
			outc(out, '\n'); }
		
#line 73 "gen/ragel/30__iter_4.c"
		
		goto _st5;
		_ctr8:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__iter_4.rl"
			s = p; }
		
#line 81 "gen/ragel/30__iter_4.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__iter_4.rl"
			outc(out, '\n'); }
		
#line 87 "gen/ragel/30__iter_4.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr8;
			}
			case 97: {
				goto _ctr9;
			}
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr6:
		{
#line 8 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__iter_4.rl"
			
			outs(out, s, p);
			outc(out, '.');
			s = p;
		}
		
#line 119 "gen/ragel/30__iter_4.c"
		
		goto _st1;
		_ctr9:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__iter_4.rl"
			s = p; }
		
#line 127 "gen/ragel/30__iter_4.c"
		
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
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr5;
			}
			case 97: {
				goto _ctr6;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof5: cs = 5; goto _test_eof; 
		_test_eof1: cs = 1; goto _test_eof; 
		_test_eof2: cs = 2; goto _test_eof; 
		_test_eof3: cs = 3; goto _test_eof; 
		_test_eof4: cs = 4; goto _test_eof; 
		
		_test_eof: {}
		if ( cs >= 5 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/30__iter_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
