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
		_ctr2:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 63 "gen/ragel/11__alt1_4.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			outc(out, '\n');
		}
		
#line 75 "gen/ragel/11__alt1_4.c"
		
		goto _st5;
		_ctr4:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 83 "gen/ragel/11__alt1_4.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			outc(out, '\n');
		}
		
#line 95 "gen/ragel/11__alt1_4.c"
		
		goto _st5;
		_ctr6:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 103 "gen/ragel/11__alt1_4.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			outc(out, '\n');
		}
		
#line 115 "gen/ragel/11__alt1_4.c"
		
		goto _st5;
		_ctr8:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 123 "gen/ragel/11__alt1_4.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			outc(out, '\n');
		}
		
#line 135 "gen/ragel/11__alt1_4.c"
		
		goto _st5;
		_ctr10:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			b1 = p; }
		
#line 143 "gen/ragel/11__alt1_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 149 "gen/ragel/11__alt1_4.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			c1 = p; }
		
#line 155 "gen/ragel/11__alt1_4.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 161 "gen/ragel/11__alt1_4.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			d1 = p; }
		
#line 167 "gen/ragel/11__alt1_4.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 173 "gen/ragel/11__alt1_4.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			a1 = p; }
		
#line 179 "gen/ragel/11__alt1_4.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 185 "gen/ragel/11__alt1_4.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			outc(out, '\n');
		}
		
#line 197 "gen/ragel/11__alt1_4.c"
		
		goto _st5;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
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
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr11:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			a1 = p; }
		
#line 231 "gen/ragel/11__alt1_4.c"
		
		goto _st1;
		_st1:
		p+= 1;
		st_case_1:
		if ( p == pe )
			goto _out1;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr2;
			}
			case 97: {
				goto _st1;
			}
		}
		goto _st0;
		_ctr12:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			b1 = p; }
		
#line 253 "gen/ragel/11__alt1_4.c"
		
		goto _st2;
		_st2:
		p+= 1;
		st_case_2:
		if ( p == pe )
			goto _out2;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr4;
			}
			case 98: {
				goto _st2;
			}
		}
		goto _st0;
		_ctr13:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			c1 = p; }
		
#line 275 "gen/ragel/11__alt1_4.c"
		
		goto _st3;
		_st3:
		p+= 1;
		st_case_3:
		if ( p == pe )
			goto _out3;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr6;
			}
			case 99: {
				goto _st3;
			}
		}
		goto _st0;
		_ctr14:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
			d1 = p; }
		
#line 297 "gen/ragel/11__alt1_4.c"
		
		goto _st4;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr8;
			}
			case 100: {
				goto _st4;
			}
		}
		goto _st0;
		_out5: cs = 5; goto _out; 
		_out0: cs = 0; goto _out; 
		_out1: cs = 1; goto _out; 
		_out2: cs = 2; goto _out; 
		_out3: cs = 3; goto _out; 
		_out4: cs = 4; goto _out; 
		_out: {}
	}
	
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/11__alt1_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
