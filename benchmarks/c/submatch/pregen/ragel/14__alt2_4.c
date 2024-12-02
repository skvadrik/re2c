#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"



#line 13 "gen/ragel/14__alt2_4.c"
static const int m_start = 9;
static const int m_first_final = 9;
static const int m_error = 0;

static const int m_en_main = 9;


#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1, *c1, *d1,
	*a2, *b2, *c2, *d2,
	*a3, *b3, *c3, *d3,
	*a4, *b4, *c4, *d4;
	int cs;
	
	
#line 36 "gen/ragel/14__alt2_4.c"
	{
		cs = (int)m_start;
	}
	
#line 58 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
	
	
#line 44 "gen/ragel/14__alt2_4.c"
	{
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
		_ctr2:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 73 "gen/ragel/14__alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b3 = p; }
		
#line 79 "gen/ragel/14__alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 85 "gen/ragel/14__alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c3 = p; }
		
#line 91 "gen/ragel/14__alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 97 "gen/ragel/14__alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d3 = p; }
		
#line 103 "gen/ragel/14__alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 109 "gen/ragel/14__alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a3 = p; }
		
#line 115 "gen/ragel/14__alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 121 "gen/ragel/14__alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 137 "gen/ragel/14__alt2_4.c"
		
		goto _st9;
		_ctr7:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 145 "gen/ragel/14__alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 161 "gen/ragel/14__alt2_4.c"
		
		goto _st9;
		_ctr9:
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 169 "gen/ragel/14__alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 185 "gen/ragel/14__alt2_4.c"
		
		goto _st9;
		_ctr11:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 193 "gen/ragel/14__alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 209 "gen/ragel/14__alt2_4.c"
		
		goto _st9;
		_ctr13:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 217 "gen/ragel/14__alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b3 = p; }
		
#line 223 "gen/ragel/14__alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 229 "gen/ragel/14__alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c3 = p; }
		
#line 235 "gen/ragel/14__alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 241 "gen/ragel/14__alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d3 = p; }
		
#line 247 "gen/ragel/14__alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 253 "gen/ragel/14__alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a3 = p; }
		
#line 259 "gen/ragel/14__alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 265 "gen/ragel/14__alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 281 "gen/ragel/14__alt2_4.c"
		
		goto _st9;
		_ctr18:
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 289 "gen/ragel/14__alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 305 "gen/ragel/14__alt2_4.c"
		
		goto _st9;
		_ctr20:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 313 "gen/ragel/14__alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b3 = p; }
		
#line 319 "gen/ragel/14__alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 325 "gen/ragel/14__alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c3 = p; }
		
#line 331 "gen/ragel/14__alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 337 "gen/ragel/14__alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d3 = p; }
		
#line 343 "gen/ragel/14__alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 349 "gen/ragel/14__alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a3 = p; }
		
#line 355 "gen/ragel/14__alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 361 "gen/ragel/14__alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 377 "gen/ragel/14__alt2_4.c"
		
		goto _st9;
		_ctr25:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 385 "gen/ragel/14__alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b3 = p; }
		
#line 391 "gen/ragel/14__alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 397 "gen/ragel/14__alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c3 = p; }
		
#line 403 "gen/ragel/14__alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 409 "gen/ragel/14__alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d3 = p; }
		
#line 415 "gen/ragel/14__alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 421 "gen/ragel/14__alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a3 = p; }
		
#line 427 "gen/ragel/14__alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 433 "gen/ragel/14__alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 449 "gen/ragel/14__alt2_4.c"
		
		goto _st9;
		_ctr30:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b1 = p; }
		
#line 457 "gen/ragel/14__alt2_4.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 463 "gen/ragel/14__alt2_4.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c1 = p; }
		
#line 469 "gen/ragel/14__alt2_4.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 475 "gen/ragel/14__alt2_4.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d1 = p; }
		
#line 481 "gen/ragel/14__alt2_4.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 487 "gen/ragel/14__alt2_4.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a1 = p; }
		
#line 493 "gen/ragel/14__alt2_4.c"
		
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 499 "gen/ragel/14__alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b3 = p; }
		
#line 505 "gen/ragel/14__alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 511 "gen/ragel/14__alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c3 = p; }
		
#line 517 "gen/ragel/14__alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
		
#line 523 "gen/ragel/14__alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d3 = p; }
		
#line 529 "gen/ragel/14__alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
		
#line 535 "gen/ragel/14__alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a3 = p; }
		
#line 541 "gen/ragel/14__alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
		
#line 547 "gen/ragel/14__alt2_4.c"
		
		{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			
			if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
			else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
			else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
			else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
			if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
			else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
			else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
			else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
			outc(out, '\n');
		}
		
#line 563 "gen/ragel/14__alt2_4.c"
		
		goto _st9;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr30;
			}
			case 97: {
				goto _ctr31;
			}
			case 98: {
				goto _ctr32;
			}
			case 99: {
				goto _ctr33;
			}
			case 100: {
				goto _ctr34;
			}
		}
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr31:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a1 = p; }
		
#line 597 "gen/ragel/14__alt2_4.c"
		
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
		}
		goto _st0;
		_ctr3:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 628 "gen/ragel/14__alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b3 = p; }
		
#line 634 "gen/ragel/14__alt2_4.c"
		
		goto _st2;
		_ctr22:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 642 "gen/ragel/14__alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b3 = p; }
		
#line 648 "gen/ragel/14__alt2_4.c"
		
		goto _st2;
		_ctr27:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 656 "gen/ragel/14__alt2_4.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b3 = p; }
		
#line 662 "gen/ragel/14__alt2_4.c"
		
		goto _st2;
		_st2:
		p+= 1;
		st_case_2:
		if ( p == pe )
			goto _out2;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr7;
			}
			case 98: {
				goto _st2;
			}
		}
		goto _st0;
		_ctr4:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 684 "gen/ragel/14__alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c3 = p; }
		
#line 690 "gen/ragel/14__alt2_4.c"
		
		goto _st3;
		_ctr15:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 698 "gen/ragel/14__alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c3 = p; }
		
#line 704 "gen/ragel/14__alt2_4.c"
		
		goto _st3;
		_ctr28:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 712 "gen/ragel/14__alt2_4.c"
		
		{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c3 = p; }
		
#line 718 "gen/ragel/14__alt2_4.c"
		
		goto _st3;
		_st3:
		p+= 1;
		st_case_3:
		if ( p == pe )
			goto _out3;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr9;
			}
			case 99: {
				goto _st3;
			}
		}
		goto _st0;
		_ctr5:
		{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 740 "gen/ragel/14__alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d3 = p; }
		
#line 746 "gen/ragel/14__alt2_4.c"
		
		goto _st4;
		_ctr16:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 754 "gen/ragel/14__alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d3 = p; }
		
#line 760 "gen/ragel/14__alt2_4.c"
		
		goto _st4;
		_ctr23:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 768 "gen/ragel/14__alt2_4.c"
		
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d3 = p; }
		
#line 774 "gen/ragel/14__alt2_4.c"
		
		goto _st4;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr11;
			}
			case 100: {
				goto _st4;
			}
		}
		goto _st0;
		_ctr32:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b1 = p; }
		
#line 796 "gen/ragel/14__alt2_4.c"
		
		goto _st5;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr13;
			}
			case 97: {
				goto _ctr14;
			}
			case 98: {
				goto _st5;
			}
			case 99: {
				goto _ctr15;
			}
			case 100: {
				goto _ctr16;
			}
		}
		goto _st0;
		_ctr14:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
		
#line 827 "gen/ragel/14__alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a3 = p; }
		
#line 833 "gen/ragel/14__alt2_4.c"
		
		goto _st6;
		_ctr21:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
		
#line 841 "gen/ragel/14__alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a3 = p; }
		
#line 847 "gen/ragel/14__alt2_4.c"
		
		goto _st6;
		_ctr26:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
		
#line 855 "gen/ragel/14__alt2_4.c"
		
		{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			a3 = p; }
		
#line 861 "gen/ragel/14__alt2_4.c"
		
		goto _st6;
		_st6:
		p+= 1;
		st_case_6:
		if ( p == pe )
			goto _out6;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr18;
			}
			case 97: {
				goto _st6;
			}
		}
		goto _st0;
		_ctr33:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			c1 = p; }
		
#line 883 "gen/ragel/14__alt2_4.c"
		
		goto _st7;
		_st7:
		p+= 1;
		st_case_7:
		if ( p == pe )
			goto _out7;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr20;
			}
			case 97: {
				goto _ctr21;
			}
			case 98: {
				goto _ctr22;
			}
			case 99: {
				goto _st7;
			}
			case 100: {
				goto _ctr23;
			}
		}
		goto _st0;
		_ctr34:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
			d1 = p; }
		
#line 914 "gen/ragel/14__alt2_4.c"
		
		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr25;
			}
			case 97: {
				goto _ctr26;
			}
			case 98: {
				goto _ctr27;
			}
			case 99: {
				goto _ctr28;
			}
			case 100: {
				goto _st8;
			}
		}
		goto _st0;
		_out9: cs = 9; goto _out; 
		_out0: cs = 0; goto _out; 
		_out1: cs = 1; goto _out; 
		_out2: cs = 2; goto _out; 
		_out3: cs = 3; goto _out; 
		_out4: cs = 4; goto _out; 
		_out5: cs = 5; goto _out; 
		_out6: cs = 6; goto _out; 
		_out7: cs = 7; goto _out; 
		_out8: cs = 8; goto _out; 
		_out: {}
	}
	
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/14__alt2_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
