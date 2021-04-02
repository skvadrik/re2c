#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"



#line 13 "gen/ragel/15__alt2_8.c"
static const int m_start = 17;
static const int m_first_final = 17;
static const int m_error = 0;

static const int m_en_main = 17;


#line 61 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"


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
	
	
#line 36 "gen/ragel/15__alt2_8.c"
	{
		cs = (int)m_start;
	}
	
#line 74 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
	
	
#line 44 "gen/ragel/15__alt2_8.c"
	{
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
		_ctr2:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 89 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 95 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 101 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 107 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 113 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 119 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 125 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 131 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 137 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 143 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 149 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 155 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 161 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 167 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 173 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 179 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 185 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 209 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr11:
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 217 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 241 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr13:
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 249 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 273 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr15:
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 281 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 305 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr17:
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 313 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 337 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr19:
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 345 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 369 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr21:
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 377 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 401 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr23:
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 409 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 433 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr25:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 441 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 447 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 453 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 459 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 465 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 471 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 477 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 483 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 489 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 495 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 501 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 507 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 513 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 519 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 525 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 531 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 537 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 561 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr34:
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 569 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 593 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr36:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 601 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 607 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 613 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 619 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 625 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 631 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 637 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 643 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 649 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 655 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 661 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 667 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 673 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 679 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 685 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 691 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 697 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 721 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr45:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 729 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 735 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 741 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 747 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 753 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 759 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 765 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 771 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 777 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 783 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 789 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 795 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 801 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 807 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 813 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 819 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 825 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 849 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr54:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 857 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 863 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 869 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 875 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 881 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 887 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 893 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 899 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 905 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 911 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 917 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 923 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 929 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 935 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 941 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 947 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 953 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 977 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr63:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 985 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 991 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 997 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 1003 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1009 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 1015 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1021 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 1027 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1033 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 1039 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1045 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 1051 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 1057 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 1063 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 1069 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 1075 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1081 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 1105 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr72:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 1113 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 1119 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1125 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 1131 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1137 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 1143 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1149 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 1155 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1161 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 1167 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1173 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 1179 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 1185 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 1191 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 1197 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 1203 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1209 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 1233 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr81:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 1241 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 1247 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1253 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 1259 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1265 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 1271 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1277 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 1283 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1289 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 1295 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1301 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 1307 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 1313 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 1319 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 1325 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 1331 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1337 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 1361 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_ctr90:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b1 = p; }
		
#line 1369 "gen/ragel/15__alt2_8.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1375 "gen/ragel/15__alt2_8.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c1 = p; }
		
#line 1381 "gen/ragel/15__alt2_8.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1387 "gen/ragel/15__alt2_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d1 = p; }
		
#line 1393 "gen/ragel/15__alt2_8.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1399 "gen/ragel/15__alt2_8.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e1 = p; }
		
#line 1405 "gen/ragel/15__alt2_8.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1411 "gen/ragel/15__alt2_8.c"
		
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f1 = p; }
		
#line 1417 "gen/ragel/15__alt2_8.c"
		
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1423 "gen/ragel/15__alt2_8.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g1 = p; }
		
#line 1429 "gen/ragel/15__alt2_8.c"
		
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 1435 "gen/ragel/15__alt2_8.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h1 = p; }
		
#line 1441 "gen/ragel/15__alt2_8.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 1447 "gen/ragel/15__alt2_8.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a1 = p; }
		
#line 1453 "gen/ragel/15__alt2_8.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1459 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 1465 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1471 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 1477 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1483 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 1489 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1495 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 1501 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1507 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 1513 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1519 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 1525 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
		
#line 1531 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 1537 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
		
#line 1543 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 1549 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
		
#line 1555 "gen/ragel/15__alt2_8.c"
		
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			
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
		
#line 1579 "gen/ragel/15__alt2_8.c"
		
		goto _st17;
		_st17:
		p+= 1;
		st_case_17:
		if ( p == pe )
			goto _out17;
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
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr91:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a1 = p; }
		
#line 1625 "gen/ragel/15__alt2_8.c"
		
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
		goto _st0;
		_ctr3:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1668 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 1674 "gen/ragel/15__alt2_8.c"
		
		goto _st2;
		_ctr38:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1682 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 1688 "gen/ragel/15__alt2_8.c"
		
		goto _st2;
		_ctr47:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1696 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 1702 "gen/ragel/15__alt2_8.c"
		
		goto _st2;
		_ctr56:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1710 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 1716 "gen/ragel/15__alt2_8.c"
		
		goto _st2;
		_ctr65:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1724 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 1730 "gen/ragel/15__alt2_8.c"
		
		goto _st2;
		_ctr74:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 1738 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 1744 "gen/ragel/15__alt2_8.c"
		
		goto _st2;
		_ctr83:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 1752 "gen/ragel/15__alt2_8.c"
		
		{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b3 = p; }
		
#line 1758 "gen/ragel/15__alt2_8.c"
		
		goto _st2;
		_st2:
		p+= 1;
		st_case_2:
		if ( p == pe )
			goto _out2;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr11;
			}
			case 98: {
				goto _st2;
			}
		}
		goto _st0;
		_ctr4:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1780 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 1786 "gen/ragel/15__alt2_8.c"
		
		goto _st3;
		_ctr27:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1794 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 1800 "gen/ragel/15__alt2_8.c"
		
		goto _st3;
		_ctr48:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1808 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 1814 "gen/ragel/15__alt2_8.c"
		
		goto _st3;
		_ctr57:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1822 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 1828 "gen/ragel/15__alt2_8.c"
		
		goto _st3;
		_ctr66:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1836 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 1842 "gen/ragel/15__alt2_8.c"
		
		goto _st3;
		_ctr75:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 1850 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 1856 "gen/ragel/15__alt2_8.c"
		
		goto _st3;
		_ctr84:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 1864 "gen/ragel/15__alt2_8.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c3 = p; }
		
#line 1870 "gen/ragel/15__alt2_8.c"
		
		goto _st3;
		_st3:
		p+= 1;
		st_case_3:
		if ( p == pe )
			goto _out3;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr13;
			}
			case 99: {
				goto _st3;
			}
		}
		goto _st0;
		_ctr5:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1892 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 1898 "gen/ragel/15__alt2_8.c"
		
		goto _st4;
		_ctr28:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1906 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 1912 "gen/ragel/15__alt2_8.c"
		
		goto _st4;
		_ctr39:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1920 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 1926 "gen/ragel/15__alt2_8.c"
		
		goto _st4;
		_ctr58:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1934 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 1940 "gen/ragel/15__alt2_8.c"
		
		goto _st4;
		_ctr67:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 1948 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 1954 "gen/ragel/15__alt2_8.c"
		
		goto _st4;
		_ctr76:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 1962 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 1968 "gen/ragel/15__alt2_8.c"
		
		goto _st4;
		_ctr85:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 1976 "gen/ragel/15__alt2_8.c"
		
		{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d3 = p; }
		
#line 1982 "gen/ragel/15__alt2_8.c"
		
		goto _st4;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr15;
			}
			case 100: {
				goto _st4;
			}
		}
		goto _st0;
		_ctr6:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2004 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 2010 "gen/ragel/15__alt2_8.c"
		
		goto _st5;
		_ctr29:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2018 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 2024 "gen/ragel/15__alt2_8.c"
		
		goto _st5;
		_ctr40:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2032 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 2038 "gen/ragel/15__alt2_8.c"
		
		goto _st5;
		_ctr49:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2046 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 2052 "gen/ragel/15__alt2_8.c"
		
		goto _st5;
		_ctr68:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2060 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 2066 "gen/ragel/15__alt2_8.c"
		
		goto _st5;
		_ctr77:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 2074 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 2080 "gen/ragel/15__alt2_8.c"
		
		goto _st5;
		_ctr86:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 2088 "gen/ragel/15__alt2_8.c"
		
		{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e3 = p; }
		
#line 2094 "gen/ragel/15__alt2_8.c"
		
		goto _st5;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr17;
			}
			case 101: {
				goto _st5;
			}
		}
		goto _st0;
		_ctr7:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2116 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 2122 "gen/ragel/15__alt2_8.c"
		
		goto _st6;
		_ctr30:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2130 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 2136 "gen/ragel/15__alt2_8.c"
		
		goto _st6;
		_ctr41:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2144 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 2150 "gen/ragel/15__alt2_8.c"
		
		goto _st6;
		_ctr50:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2158 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 2164 "gen/ragel/15__alt2_8.c"
		
		goto _st6;
		_ctr59:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2172 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 2178 "gen/ragel/15__alt2_8.c"
		
		goto _st6;
		_ctr78:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 2186 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 2192 "gen/ragel/15__alt2_8.c"
		
		goto _st6;
		_ctr87:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 2200 "gen/ragel/15__alt2_8.c"
		
		{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f3 = p; }
		
#line 2206 "gen/ragel/15__alt2_8.c"
		
		goto _st6;
		_st6:
		p+= 1;
		st_case_6:
		if ( p == pe )
			goto _out6;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr19;
			}
			case 102: {
				goto _st6;
			}
		}
		goto _st0;
		_ctr8:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2228 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 2234 "gen/ragel/15__alt2_8.c"
		
		goto _st7;
		_ctr31:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2242 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 2248 "gen/ragel/15__alt2_8.c"
		
		goto _st7;
		_ctr42:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2256 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 2262 "gen/ragel/15__alt2_8.c"
		
		goto _st7;
		_ctr51:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2270 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 2276 "gen/ragel/15__alt2_8.c"
		
		goto _st7;
		_ctr60:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2284 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 2290 "gen/ragel/15__alt2_8.c"
		
		goto _st7;
		_ctr69:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2298 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 2304 "gen/ragel/15__alt2_8.c"
		
		goto _st7;
		_ctr88:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 2312 "gen/ragel/15__alt2_8.c"
		
		{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g3 = p; }
		
#line 2318 "gen/ragel/15__alt2_8.c"
		
		goto _st7;
		_st7:
		p+= 1;
		st_case_7:
		if ( p == pe )
			goto _out7;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr21;
			}
			case 103: {
				goto _st7;
			}
		}
		goto _st0;
		_ctr9:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2340 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 2346 "gen/ragel/15__alt2_8.c"
		
		goto _st8;
		_ctr32:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2354 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 2360 "gen/ragel/15__alt2_8.c"
		
		goto _st8;
		_ctr43:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2368 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 2374 "gen/ragel/15__alt2_8.c"
		
		goto _st8;
		_ctr52:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2382 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 2388 "gen/ragel/15__alt2_8.c"
		
		goto _st8;
		_ctr61:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2396 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 2402 "gen/ragel/15__alt2_8.c"
		
		goto _st8;
		_ctr70:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2410 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 2416 "gen/ragel/15__alt2_8.c"
		
		goto _st8;
		_ctr79:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 2424 "gen/ragel/15__alt2_8.c"
		
		{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h3 = p; }
		
#line 2430 "gen/ragel/15__alt2_8.c"
		
		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 104: {
				goto _st8;
			}
		}
		goto _st0;
		_ctr92:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b1 = p; }
		
#line 2452 "gen/ragel/15__alt2_8.c"
		
		goto _st9;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
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
		goto _st0;
		_ctr26:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2495 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 2501 "gen/ragel/15__alt2_8.c"
		
		goto _st10;
		_ctr37:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2509 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 2515 "gen/ragel/15__alt2_8.c"
		
		goto _st10;
		_ctr46:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2523 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 2529 "gen/ragel/15__alt2_8.c"
		
		goto _st10;
		_ctr55:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2537 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 2543 "gen/ragel/15__alt2_8.c"
		
		goto _st10;
		_ctr64:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
		
#line 2551 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 2557 "gen/ragel/15__alt2_8.c"
		
		goto _st10;
		_ctr73:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
		
#line 2565 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 2571 "gen/ragel/15__alt2_8.c"
		
		goto _st10;
		_ctr82:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
		
#line 2579 "gen/ragel/15__alt2_8.c"
		
		{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			a3 = p; }
		
#line 2585 "gen/ragel/15__alt2_8.c"
		
		goto _st10;
		_st10:
		p+= 1;
		st_case_10:
		if ( p == pe )
			goto _out10;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr34;
			}
			case 97: {
				goto _st10;
			}
		}
		goto _st0;
		_ctr93:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			c1 = p; }
		
#line 2607 "gen/ragel/15__alt2_8.c"
		
		goto _st11;
		_st11:
		p+= 1;
		st_case_11:
		if ( p == pe )
			goto _out11;
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
		goto _st0;
		_ctr94:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			d1 = p; }
		
#line 2650 "gen/ragel/15__alt2_8.c"
		
		goto _st12;
		_st12:
		p+= 1;
		st_case_12:
		if ( p == pe )
			goto _out12;
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
		goto _st0;
		_ctr95:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			e1 = p; }
		
#line 2693 "gen/ragel/15__alt2_8.c"
		
		goto _st13;
		_st13:
		p+= 1;
		st_case_13:
		if ( p == pe )
			goto _out13;
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
		goto _st0;
		_ctr96:
		{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			f1 = p; }
		
#line 2736 "gen/ragel/15__alt2_8.c"
		
		goto _st14;
		_st14:
		p+= 1;
		st_case_14:
		if ( p == pe )
			goto _out14;
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
		goto _st0;
		_ctr97:
		{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			g1 = p; }
		
#line 2779 "gen/ragel/15__alt2_8.c"
		
		goto _st15;
		_st15:
		p+= 1;
		st_case_15:
		if ( p == pe )
			goto _out15;
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
		goto _st0;
		_ctr98:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
			h1 = p; }
		
#line 2822 "gen/ragel/15__alt2_8.c"
		
		goto _st16;
		_st16:
		p+= 1;
		st_case_16:
		if ( p == pe )
			goto _out16;
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
		goto _st0;
		_out17: cs = 17; goto _out; 
		_out0: cs = 0; goto _out; 
		_out1: cs = 1; goto _out; 
		_out2: cs = 2; goto _out; 
		_out3: cs = 3; goto _out; 
		_out4: cs = 4; goto _out; 
		_out5: cs = 5; goto _out; 
		_out6: cs = 6; goto _out; 
		_out7: cs = 7; goto _out; 
		_out8: cs = 8; goto _out; 
		_out9: cs = 9; goto _out; 
		_out10: cs = 10; goto _out; 
		_out11: cs = 11; goto _out; 
		_out12: cs = 12; goto _out; 
		_out13: cs = 13; goto _out; 
		_out14: cs = 14; goto _out; 
		_out15: cs = 15; goto _out; 
		_out16: cs = 16; goto _out; 
		_out: {}
	}
	
#line 75 "../../../benchmarks/submatch_dfa_aot/src/ragel/15__alt2_8.rl"
	
	
	in->p = p;
	in->pe = pe;
}
