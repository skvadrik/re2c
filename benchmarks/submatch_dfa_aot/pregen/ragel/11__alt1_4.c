#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"



#line 13 "gen/ragel/11__alt1_4.c"
static const int m_start = 5;
static const int m_first_final = 5;
static const int m_error = 0;

static const int m_en_main = 5;


#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1, *c1, *d1,
	*a2, *b2, *c2, *d2;
	int cs;
	
	
#line 34 "gen/ragel/11__alt1_4.c"
	{
		cs = (int)m_start;
	}
	
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
	
	
#line 42 "gen/ragel/11__alt1_4.c"
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
		_ctr2:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 66 "gen/ragel/11__alt1_4.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			outc(out, '\n');
		}
		
#line 78 "gen/ragel/11__alt1_4.c"
		
		goto _st5;
		_ctr4:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 86 "gen/ragel/11__alt1_4.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			outc(out, '\n');
		}
		
#line 98 "gen/ragel/11__alt1_4.c"
		
		goto _st5;
		_ctr6:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 106 "gen/ragel/11__alt1_4.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			outc(out, '\n');
		}
		
#line 118 "gen/ragel/11__alt1_4.c"
		
		goto _st5;
		_ctr8:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 126 "gen/ragel/11__alt1_4.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			outc(out, '\n');
		}
		
#line 138 "gen/ragel/11__alt1_4.c"
		
		goto _st5;
		_ctr10:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			b1 = p; }
		
#line 146 "gen/ragel/11__alt1_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 152 "gen/ragel/11__alt1_4.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			c1 = p; }
		
#line 158 "gen/ragel/11__alt1_4.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 164 "gen/ragel/11__alt1_4.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			d1 = p; }
		
#line 170 "gen/ragel/11__alt1_4.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 176 "gen/ragel/11__alt1_4.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			a1 = p; }
		
#line 182 "gen/ragel/11__alt1_4.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 188 "gen/ragel/11__alt1_4.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			outc(out, '\n');
		}
		
#line 200 "gen/ragel/11__alt1_4.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr10;
			}
			case 97: {
				goto _ctr11;
			}
			case 98: {
				goto _ctr12;
			}
			case 99: {
				goto _ctr13;
			}
			case 100: {
				goto _ctr14;
			}
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr11:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			a1 = p; }
		
#line 237 "gen/ragel/11__alt1_4.c"
		
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
		_ctr12:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			b1 = p; }
		
#line 261 "gen/ragel/11__alt1_4.c"
		
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
		_ctr13:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			c1 = p; }
		
#line 285 "gen/ragel/11__alt1_4.c"
		
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
			case 99: {
				goto _st3;
			}
		}
		{
			goto _st0;
		}
		_ctr14:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			d1 = p; }
		
#line 309 "gen/ragel/11__alt1_4.c"
		
		goto _st4;
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr8;
			}
			case 100: {
				goto _st4;
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
	
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
