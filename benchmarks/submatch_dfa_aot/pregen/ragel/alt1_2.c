#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"



#line 13 "gen/ragel/alt1_2.c"
static const int m_start = 3;
static const int m_first_final = 3;
static const int m_error = 0;

static const int m_en_main = 3;


#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1,
	*a2, *b2;
	int cs;
	
	
#line 34 "gen/ragel/alt1_2.c"
	{
		cs = (int)m_start;
	}
	
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
	
	
#line 42 "gen/ragel/alt1_2.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 3:
			goto st_case_3;
			case 0:
			goto st_case_0;
			case 1:
			goto st_case_1;
			case 2:
			goto st_case_2;
		}
		goto st_out;
		_ctr2:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
			a2 = p; b1 = b2 = NULL; }
		
#line 62 "gen/ragel/alt1_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			outc(out, '\n');
		}
		
#line 72 "gen/ragel/alt1_2.c"
		
		goto _st3;
		_ctr4:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
			b2 = p; a1 = a2 = NULL; }
		
#line 80 "gen/ragel/alt1_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			outc(out, '\n');
		}
		
#line 90 "gen/ragel/alt1_2.c"
		
		goto _st3;
		_ctr6:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
			b1 = p; }
		
#line 98 "gen/ragel/alt1_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
			b2 = p; a1 = a2 = NULL; }
		
#line 104 "gen/ragel/alt1_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
			a1 = p; }
		
#line 110 "gen/ragel/alt1_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
			a2 = p; b1 = b2 = NULL; }
		
#line 116 "gen/ragel/alt1_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			outc(out, '\n');
		}
		
#line 126 "gen/ragel/alt1_2.c"
		
		goto _st3;
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr6;
			}
			case 97: {
				goto _ctr7;
			}
			case 98: {
				goto _ctr8;
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
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
			a1 = p; }
		
#line 157 "gen/ragel/alt1_2.c"
		
		goto _st1;
		_st1:
		p+= 1;
		if ( p == pe )
			goto _test_eof1;
		st_case_1:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr2;
			}
			case 97: {
				goto _st1;
			}
		}
		{
			goto _st0;
		}
		_ctr8:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
			b1 = p; }
		
#line 181 "gen/ragel/alt1_2.c"
		
		goto _st2;
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr4;
			}
			case 98: {
				goto _st2;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof3: cs = 3; goto _test_eof; 
		_test_eof1: cs = 1; goto _test_eof; 
		_test_eof2: cs = 2; goto _test_eof; 
		
		_test_eof: {}
		if ( cs >= 3 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
	
	
	in->p = p;
	in->pe = pe;
}
