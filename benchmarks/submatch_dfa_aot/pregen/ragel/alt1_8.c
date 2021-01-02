#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"



#line 13 "gen/ragel/alt1_8.c"
static const int m_start = 9;
static const int m_first_final = 9;
static const int m_error = 0;

static const int m_en_main = 9;


#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1, *c1, *d1, *e1, *f1, *g1, *h1,
	*a2, *b2, *c2, *d2, *e2, *f2, *g2, *h2;
	int cs;
	
	
#line 34 "gen/ragel/alt1_8.c"
	{
		cs = (int)m_start;
	}
	
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
	
	
#line 42 "gen/ragel/alt1_8.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 9:
			goto st_case_9;
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
		}
		goto st_out;
		_ctr2:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 74 "gen/ragel/alt1_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			outc(out, '\n');
		}
		
#line 90 "gen/ragel/alt1_8.c"
		
		goto _st9;
		_ctr4:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 98 "gen/ragel/alt1_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			outc(out, '\n');
		}
		
#line 114 "gen/ragel/alt1_8.c"
		
		goto _st9;
		_ctr6:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 122 "gen/ragel/alt1_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			outc(out, '\n');
		}
		
#line 138 "gen/ragel/alt1_8.c"
		
		goto _st9;
		_ctr8:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 146 "gen/ragel/alt1_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			outc(out, '\n');
		}
		
#line 162 "gen/ragel/alt1_8.c"
		
		goto _st9;
		_ctr10:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 170 "gen/ragel/alt1_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			outc(out, '\n');
		}
		
#line 186 "gen/ragel/alt1_8.c"
		
		goto _st9;
		_ctr12:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 194 "gen/ragel/alt1_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			outc(out, '\n');
		}
		
#line 210 "gen/ragel/alt1_8.c"
		
		goto _st9;
		_ctr14:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 218 "gen/ragel/alt1_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			outc(out, '\n');
		}
		
#line 234 "gen/ragel/alt1_8.c"
		
		goto _st9;
		_ctr16:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 242 "gen/ragel/alt1_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			outc(out, '\n');
		}
		
#line 258 "gen/ragel/alt1_8.c"
		
		goto _st9;
		_ctr18:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			b1 = p; }
		
#line 266 "gen/ragel/alt1_8.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 272 "gen/ragel/alt1_8.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			c1 = p; }
		
#line 278 "gen/ragel/alt1_8.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 284 "gen/ragel/alt1_8.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			d1 = p; }
		
#line 290 "gen/ragel/alt1_8.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 296 "gen/ragel/alt1_8.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			e1 = p; }
		
#line 302 "gen/ragel/alt1_8.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 308 "gen/ragel/alt1_8.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			f1 = p; }
		
#line 314 "gen/ragel/alt1_8.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 320 "gen/ragel/alt1_8.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			g1 = p; }
		
#line 326 "gen/ragel/alt1_8.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 332 "gen/ragel/alt1_8.c"
		
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			h1 = p; }
		
#line 338 "gen/ragel/alt1_8.c"
		
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 344 "gen/ragel/alt1_8.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			a1 = p; }
		
#line 350 "gen/ragel/alt1_8.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 356 "gen/ragel/alt1_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			outc(out, '\n');
		}
		
#line 372 "gen/ragel/alt1_8.c"
		
		goto _st9;
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr18;
			}
			case 97: {
				goto _ctr19;
			}
			case 98: {
				goto _ctr20;
			}
			case 99: {
				goto _ctr21;
			}
			case 100: {
				goto _ctr22;
			}
			case 101: {
				goto _ctr23;
			}
			case 102: {
				goto _ctr24;
			}
			case 103: {
				goto _ctr25;
			}
			case 104: {
				goto _ctr26;
			}
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr19:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			a1 = p; }
		
#line 421 "gen/ragel/alt1_8.c"
		
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
		_ctr20:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			b1 = p; }
		
#line 445 "gen/ragel/alt1_8.c"
		
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
		_ctr21:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			c1 = p; }
		
#line 469 "gen/ragel/alt1_8.c"
		
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
		_ctr22:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			d1 = p; }
		
#line 493 "gen/ragel/alt1_8.c"
		
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
		_ctr23:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			e1 = p; }
		
#line 517 "gen/ragel/alt1_8.c"
		
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
			case 101: {
				goto _st5;
			}
		}
		{
			goto _st0;
		}
		_ctr24:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			f1 = p; }
		
#line 541 "gen/ragel/alt1_8.c"
		
		goto _st6;
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr12;
			}
			case 102: {
				goto _st6;
			}
		}
		{
			goto _st0;
		}
		_ctr25:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			g1 = p; }
		
#line 565 "gen/ragel/alt1_8.c"
		
		goto _st7;
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr14;
			}
			case 103: {
				goto _st7;
			}
		}
		{
			goto _st0;
		}
		_ctr26:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
			h1 = p; }
		
#line 589 "gen/ragel/alt1_8.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr16;
			}
			case 104: {
				goto _st8;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof9: cs = 9; goto _test_eof; 
		_test_eof1: cs = 1; goto _test_eof; 
		_test_eof2: cs = 2; goto _test_eof; 
		_test_eof3: cs = 3; goto _test_eof; 
		_test_eof4: cs = 4; goto _test_eof; 
		_test_eof5: cs = 5; goto _test_eof; 
		_test_eof6: cs = 6; goto _test_eof; 
		_test_eof7: cs = 7; goto _test_eof; 
		_test_eof8: cs = 8; goto _test_eof; 
		
		_test_eof: {}
		if ( cs >= 9 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 48 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
	
	
	in->p = p;
	in->pe = pe;
}
