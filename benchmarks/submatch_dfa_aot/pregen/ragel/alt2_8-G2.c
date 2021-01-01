#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"



#line 13 "gen/ragel/alt2_8-G2.c"
static const int m_start = 17;
static const int m_first_final = 17;
static const int m_error = 0;

static const int m_en_main = 17;


#line 61 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1, *c1, *d1, *e1, *f1, *g1, *h1,
	*a2, *b2, *c2, *d2, *e2, *f2, *g2, *h2,
	*a3, *b3, *c3, *d3, *e3, *f3, *g3, *h3,
	*a4, *b4, *c4, *d4, *e4, *f4, *g4, *h4;
	int cs;
	
	
#line 36 "gen/ragel/alt2_8-G2.c"
	{
		cs = (int)m_start;
	}
	
#line 74 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
	
	
#line 44 "gen/ragel/alt2_8-G2.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 17:
			goto st_case_17;
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
		}
		goto st_out;
		_ctr2:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 92 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 98 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 104 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 110 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 116 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 122 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 128 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 134 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 140 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 146 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 152 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 158 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 164 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 170 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 176 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 182 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 188 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 212 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr11:
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 220 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 244 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr13:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 252 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 276 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr15:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 284 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 308 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr17:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 316 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 340 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr19:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 348 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 372 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr21:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 380 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 404 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr23:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 412 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 436 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr25:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 444 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 450 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 456 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 462 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 468 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 474 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 480 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 486 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 492 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 498 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 504 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 510 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 516 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 522 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 528 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 534 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 540 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 564 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr34:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 572 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 596 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr36:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 604 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 610 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 616 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 622 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 628 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 634 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 640 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 646 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 652 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 658 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 664 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 670 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 676 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 682 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 688 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 694 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 700 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 724 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr45:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 732 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 738 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 744 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 750 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 756 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 762 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 768 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 774 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 780 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 786 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 792 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 798 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 804 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 810 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 816 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 822 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 828 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 852 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr54:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 860 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 866 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 872 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 878 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 884 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 890 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 896 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 902 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 908 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 914 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 920 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 926 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 932 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 938 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 944 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 950 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 956 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 980 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr63:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 988 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 994 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1000 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 1006 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1012 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 1018 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1024 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 1030 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1036 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 1042 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1048 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 1054 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 1060 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 1066 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 1072 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 1078 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1084 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 1108 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr72:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 1116 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 1122 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1128 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 1134 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1140 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 1146 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1152 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 1158 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1164 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 1170 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1176 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 1182 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 1188 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 1194 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 1200 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 1206 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1212 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 1236 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr81:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 1244 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 1250 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1256 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 1262 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1268 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 1274 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1280 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 1286 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1292 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 1298 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1304 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 1310 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 1316 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 1322 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 1328 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 1334 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1340 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 1364 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_ctr90:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b1 = p; }
		
#line 1372 "gen/ragel/alt2_8-G2.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1378 "gen/ragel/alt2_8-G2.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c1 = p; }
		
#line 1384 "gen/ragel/alt2_8-G2.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1390 "gen/ragel/alt2_8-G2.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d1 = p; }
		
#line 1396 "gen/ragel/alt2_8-G2.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1402 "gen/ragel/alt2_8-G2.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e1 = p; }
		
#line 1408 "gen/ragel/alt2_8-G2.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1414 "gen/ragel/alt2_8-G2.c"
		
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f1 = p; }
		
#line 1420 "gen/ragel/alt2_8-G2.c"
		
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1426 "gen/ragel/alt2_8-G2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g1 = p; }
		
#line 1432 "gen/ragel/alt2_8-G2.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 1438 "gen/ragel/alt2_8-G2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h1 = p; }
		
#line 1444 "gen/ragel/alt2_8-G2.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 1450 "gen/ragel/alt2_8-G2.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a1 = p; }
		
#line 1456 "gen/ragel/alt2_8-G2.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1462 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 1468 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1474 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 1480 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1486 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 1492 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1498 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 1504 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1510 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 1516 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1522 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 1528 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 1534 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 1540 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 1546 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 1552 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1558 "gen/ragel/alt2_8-G2.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
			else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
			else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
			else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
			else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
			else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
			else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
			outc(out, '\n');
		}
		
#line 1582 "gen/ragel/alt2_8-G2.c"
		
		goto _st17;
		_st17:
		p+= 1;
		if ( p == pe )
			goto _test_eof17;
		st_case_17:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr90;
			}
			case 97: {
				goto _ctr91;
			}
			case 98: {
				goto _ctr92;
			}
			case 99: {
				goto _ctr93;
			}
			case 100: {
				goto _ctr94;
			}
			case 101: {
				goto _ctr95;
			}
			case 102: {
				goto _ctr96;
			}
			case 103: {
				goto _ctr97;
			}
			case 104: {
				goto _ctr98;
			}
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr91:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a1 = p; }
		
#line 1631 "gen/ragel/alt2_8-G2.c"
		
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
			case 98: {
				goto _ctr3;
			}
			case 99: {
				goto _ctr4;
			}
			case 100: {
				goto _ctr5;
			}
			case 101: {
				goto _ctr6;
			}
			case 102: {
				goto _ctr7;
			}
			case 103: {
				goto _ctr8;
			}
			case 104: {
				goto _ctr9;
			}
		}
		{
			goto _st0;
		}
		_ctr3:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1676 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 1682 "gen/ragel/alt2_8-G2.c"
		
		goto _st2;
		_ctr38:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1690 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 1696 "gen/ragel/alt2_8-G2.c"
		
		goto _st2;
		_ctr47:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1704 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 1710 "gen/ragel/alt2_8-G2.c"
		
		goto _st2;
		_ctr56:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1718 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 1724 "gen/ragel/alt2_8-G2.c"
		
		goto _st2;
		_ctr65:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1732 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 1738 "gen/ragel/alt2_8-G2.c"
		
		goto _st2;
		_ctr74:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 1746 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 1752 "gen/ragel/alt2_8-G2.c"
		
		goto _st2;
		_ctr83:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 1760 "gen/ragel/alt2_8-G2.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b3 = p; }
		
#line 1766 "gen/ragel/alt2_8-G2.c"
		
		goto _st2;
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr11;
			}
			case 98: {
				goto _st2;
			}
		}
		{
			goto _st0;
		}
		_ctr4:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1790 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 1796 "gen/ragel/alt2_8-G2.c"
		
		goto _st3;
		_ctr27:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1804 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 1810 "gen/ragel/alt2_8-G2.c"
		
		goto _st3;
		_ctr48:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1818 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 1824 "gen/ragel/alt2_8-G2.c"
		
		goto _st3;
		_ctr57:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1832 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 1838 "gen/ragel/alt2_8-G2.c"
		
		goto _st3;
		_ctr66:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1846 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 1852 "gen/ragel/alt2_8-G2.c"
		
		goto _st3;
		_ctr75:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 1860 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 1866 "gen/ragel/alt2_8-G2.c"
		
		goto _st3;
		_ctr84:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 1874 "gen/ragel/alt2_8-G2.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c3 = p; }
		
#line 1880 "gen/ragel/alt2_8-G2.c"
		
		goto _st3;
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr13;
			}
			case 99: {
				goto _st3;
			}
		}
		{
			goto _st0;
		}
		_ctr5:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1904 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 1910 "gen/ragel/alt2_8-G2.c"
		
		goto _st4;
		_ctr28:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1918 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 1924 "gen/ragel/alt2_8-G2.c"
		
		goto _st4;
		_ctr39:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1932 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 1938 "gen/ragel/alt2_8-G2.c"
		
		goto _st4;
		_ctr58:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1946 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 1952 "gen/ragel/alt2_8-G2.c"
		
		goto _st4;
		_ctr67:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1960 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 1966 "gen/ragel/alt2_8-G2.c"
		
		goto _st4;
		_ctr76:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 1974 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 1980 "gen/ragel/alt2_8-G2.c"
		
		goto _st4;
		_ctr85:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 1988 "gen/ragel/alt2_8-G2.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d3 = p; }
		
#line 1994 "gen/ragel/alt2_8-G2.c"
		
		goto _st4;
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr15;
			}
			case 100: {
				goto _st4;
			}
		}
		{
			goto _st0;
		}
		_ctr6:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2018 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 2024 "gen/ragel/alt2_8-G2.c"
		
		goto _st5;
		_ctr29:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2032 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 2038 "gen/ragel/alt2_8-G2.c"
		
		goto _st5;
		_ctr40:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2046 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 2052 "gen/ragel/alt2_8-G2.c"
		
		goto _st5;
		_ctr49:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2060 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 2066 "gen/ragel/alt2_8-G2.c"
		
		goto _st5;
		_ctr68:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2074 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 2080 "gen/ragel/alt2_8-G2.c"
		
		goto _st5;
		_ctr77:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 2088 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 2094 "gen/ragel/alt2_8-G2.c"
		
		goto _st5;
		_ctr86:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 2102 "gen/ragel/alt2_8-G2.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e3 = p; }
		
#line 2108 "gen/ragel/alt2_8-G2.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr17;
			}
			case 101: {
				goto _st5;
			}
		}
		{
			goto _st0;
		}
		_ctr7:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2132 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 2138 "gen/ragel/alt2_8-G2.c"
		
		goto _st6;
		_ctr30:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2146 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 2152 "gen/ragel/alt2_8-G2.c"
		
		goto _st6;
		_ctr41:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2160 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 2166 "gen/ragel/alt2_8-G2.c"
		
		goto _st6;
		_ctr50:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2174 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 2180 "gen/ragel/alt2_8-G2.c"
		
		goto _st6;
		_ctr59:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2188 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 2194 "gen/ragel/alt2_8-G2.c"
		
		goto _st6;
		_ctr78:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 2202 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 2208 "gen/ragel/alt2_8-G2.c"
		
		goto _st6;
		_ctr87:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 2216 "gen/ragel/alt2_8-G2.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f3 = p; }
		
#line 2222 "gen/ragel/alt2_8-G2.c"
		
		goto _st6;
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr19;
			}
			case 102: {
				goto _st6;
			}
		}
		{
			goto _st0;
		}
		_ctr8:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2246 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 2252 "gen/ragel/alt2_8-G2.c"
		
		goto _st7;
		_ctr31:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2260 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 2266 "gen/ragel/alt2_8-G2.c"
		
		goto _st7;
		_ctr42:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2274 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 2280 "gen/ragel/alt2_8-G2.c"
		
		goto _st7;
		_ctr51:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2288 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 2294 "gen/ragel/alt2_8-G2.c"
		
		goto _st7;
		_ctr60:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2302 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 2308 "gen/ragel/alt2_8-G2.c"
		
		goto _st7;
		_ctr69:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2316 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 2322 "gen/ragel/alt2_8-G2.c"
		
		goto _st7;
		_ctr88:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 2330 "gen/ragel/alt2_8-G2.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g3 = p; }
		
#line 2336 "gen/ragel/alt2_8-G2.c"
		
		goto _st7;
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr21;
			}
			case 103: {
				goto _st7;
			}
		}
		{
			goto _st0;
		}
		_ctr9:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2360 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 2366 "gen/ragel/alt2_8-G2.c"
		
		goto _st8;
		_ctr32:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2374 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 2380 "gen/ragel/alt2_8-G2.c"
		
		goto _st8;
		_ctr43:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2388 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 2394 "gen/ragel/alt2_8-G2.c"
		
		goto _st8;
		_ctr52:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2402 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 2408 "gen/ragel/alt2_8-G2.c"
		
		goto _st8;
		_ctr61:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2416 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 2422 "gen/ragel/alt2_8-G2.c"
		
		goto _st8;
		_ctr70:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2430 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 2436 "gen/ragel/alt2_8-G2.c"
		
		goto _st8;
		_ctr79:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 2444 "gen/ragel/alt2_8-G2.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h3 = p; }
		
#line 2450 "gen/ragel/alt2_8-G2.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 104: {
				goto _st8;
			}
		}
		{
			goto _st0;
		}
		_ctr92:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b1 = p; }
		
#line 2474 "gen/ragel/alt2_8-G2.c"
		
		goto _st9;
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr25;
			}
			case 97: {
				goto _ctr26;
			}
			case 98: {
				goto _st9;
			}
			case 99: {
				goto _ctr27;
			}
			case 100: {
				goto _ctr28;
			}
			case 101: {
				goto _ctr29;
			}
			case 102: {
				goto _ctr30;
			}
			case 103: {
				goto _ctr31;
			}
			case 104: {
				goto _ctr32;
			}
		}
		{
			goto _st0;
		}
		_ctr26:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2519 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 2525 "gen/ragel/alt2_8-G2.c"
		
		goto _st10;
		_ctr37:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2533 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 2539 "gen/ragel/alt2_8-G2.c"
		
		goto _st10;
		_ctr46:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2547 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 2553 "gen/ragel/alt2_8-G2.c"
		
		goto _st10;
		_ctr55:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2561 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 2567 "gen/ragel/alt2_8-G2.c"
		
		goto _st10;
		_ctr64:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2575 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 2581 "gen/ragel/alt2_8-G2.c"
		
		goto _st10;
		_ctr73:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 2589 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 2595 "gen/ragel/alt2_8-G2.c"
		
		goto _st10;
		_ctr82:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 2603 "gen/ragel/alt2_8-G2.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			a3 = p; }
		
#line 2609 "gen/ragel/alt2_8-G2.c"
		
		goto _st10;
		_st10:
		p+= 1;
		if ( p == pe )
			goto _test_eof10;
		st_case_10:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr34;
			}
			case 97: {
				goto _st10;
			}
		}
		{
			goto _st0;
		}
		_ctr93:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			c1 = p; }
		
#line 2633 "gen/ragel/alt2_8-G2.c"
		
		goto _st11;
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr36;
			}
			case 97: {
				goto _ctr37;
			}
			case 98: {
				goto _ctr38;
			}
			case 99: {
				goto _st11;
			}
			case 100: {
				goto _ctr39;
			}
			case 101: {
				goto _ctr40;
			}
			case 102: {
				goto _ctr41;
			}
			case 103: {
				goto _ctr42;
			}
			case 104: {
				goto _ctr43;
			}
		}
		{
			goto _st0;
		}
		_ctr94:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			d1 = p; }
		
#line 2678 "gen/ragel/alt2_8-G2.c"
		
		goto _st12;
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr45;
			}
			case 97: {
				goto _ctr46;
			}
			case 98: {
				goto _ctr47;
			}
			case 99: {
				goto _ctr48;
			}
			case 100: {
				goto _st12;
			}
			case 101: {
				goto _ctr49;
			}
			case 102: {
				goto _ctr50;
			}
			case 103: {
				goto _ctr51;
			}
			case 104: {
				goto _ctr52;
			}
		}
		{
			goto _st0;
		}
		_ctr95:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			e1 = p; }
		
#line 2723 "gen/ragel/alt2_8-G2.c"
		
		goto _st13;
		_st13:
		p+= 1;
		if ( p == pe )
			goto _test_eof13;
		st_case_13:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr54;
			}
			case 97: {
				goto _ctr55;
			}
			case 98: {
				goto _ctr56;
			}
			case 99: {
				goto _ctr57;
			}
			case 100: {
				goto _ctr58;
			}
			case 101: {
				goto _st13;
			}
			case 102: {
				goto _ctr59;
			}
			case 103: {
				goto _ctr60;
			}
			case 104: {
				goto _ctr61;
			}
		}
		{
			goto _st0;
		}
		_ctr96:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			f1 = p; }
		
#line 2768 "gen/ragel/alt2_8-G2.c"
		
		goto _st14;
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr63;
			}
			case 97: {
				goto _ctr64;
			}
			case 98: {
				goto _ctr65;
			}
			case 99: {
				goto _ctr66;
			}
			case 100: {
				goto _ctr67;
			}
			case 101: {
				goto _ctr68;
			}
			case 102: {
				goto _st14;
			}
			case 103: {
				goto _ctr69;
			}
			case 104: {
				goto _ctr70;
			}
		}
		{
			goto _st0;
		}
		_ctr97:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			g1 = p; }
		
#line 2813 "gen/ragel/alt2_8-G2.c"
		
		goto _st15;
		_st15:
		p+= 1;
		if ( p == pe )
			goto _test_eof15;
		st_case_15:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr72;
			}
			case 97: {
				goto _ctr73;
			}
			case 98: {
				goto _ctr74;
			}
			case 99: {
				goto _ctr75;
			}
			case 100: {
				goto _ctr76;
			}
			case 101: {
				goto _ctr77;
			}
			case 102: {
				goto _ctr78;
			}
			case 103: {
				goto _st15;
			}
			case 104: {
				goto _ctr79;
			}
		}
		{
			goto _st0;
		}
		_ctr98:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
			h1 = p; }
		
#line 2858 "gen/ragel/alt2_8-G2.c"
		
		goto _st16;
		_st16:
		p+= 1;
		if ( p == pe )
			goto _test_eof16;
		st_case_16:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr81;
			}
			case 97: {
				goto _ctr82;
			}
			case 98: {
				goto _ctr83;
			}
			case 99: {
				goto _ctr84;
			}
			case 100: {
				goto _ctr85;
			}
			case 101: {
				goto _ctr86;
			}
			case 102: {
				goto _ctr87;
			}
			case 103: {
				goto _ctr88;
			}
			case 104: {
				goto _st16;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof17: cs = 17; goto _test_eof; 
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
		
		_test_eof: {}
		if ( cs >= 17 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 75 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
	
	
	in->p = p;
	in->pe = pe;
}
