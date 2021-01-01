#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"



#line 13 "gen/ragel/alt1_8-F1.c"
static const char _m_trans_keys[] = {
	1, 0, 0, 2, 0, 3, 0, 4,
	0, 5, 0, 6, 0, 7, 0, 8,
	0, 9, 0, 9, 0
};

static const signed char _m_char_class[] = {
	0, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 2,
	3, 4, 5, 6, 7, 8, 9, 0
};

static const signed char _m_index_offsets[] = {
	0, 0, 3, 7, 12, 18, 25, 33,
	42, 52, 0
};

static const signed char _m_indicies[] = {
	2, 0, 1, 4, 0, 0, 3, 6,
	0, 0, 0, 5, 8, 0, 0, 0,
	0, 7, 10, 0, 0, 0, 0, 0,
	9, 12, 0, 0, 0, 0, 0, 0,
	11, 14, 0, 0, 0, 0, 0, 0,
	0, 13, 16, 0, 0, 0, 0, 0,
	0, 0, 0, 15, 18, 0, 19, 20,
	21, 22, 23, 24, 25, 26, 0
};

static const signed char _m_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _m_cond_targs[] = {
	0, 1, 9, 2, 9, 3, 9, 4,
	9, 5, 9, 6, 9, 7, 9, 8,
	9, 9, 9, 1, 2, 3, 4, 5,
	6, 7, 8, 0
};

static const signed char _m_cond_actions[] = {
	0, 0, 1, 0, 2, 0, 3, 0,
	4, 0, 5, 0, 6, 0, 7, 0,
	8, 0, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 0
};

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
	
	
#line 90 "gen/ragel/alt1_8-F1.c"
	{
		cs = (int)m_start;
	}
	
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
	
	
#line 98 "gen/ragel/alt1_8-F1.c"
	{
		unsigned int _trans = 0;
		const char * _keys;
		const signed char * _inds;
		int _ic;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _m_trans_keys + ((cs<<1)));
		_inds = ( _m_indicies + (_m_index_offsets[cs]));
		
		if ( ( (*( p))) <= 104 && ( (*( p))) >= 10 ) {
			_ic = (int)_m_char_class[(int)( (*( p))) - 10];
			if ( _ic <= (int)(*( _keys+1)) && _ic >= (int)(*( _keys)) )
				_trans = (unsigned int)(*( _inds + (int)( _ic - (int)(*( _keys)) ) )); 
			else
				_trans = (unsigned int)_m_index_defaults[cs];
		}
		else {
			_trans = (unsigned int)_m_index_defaults[cs];
		}
		
		cs = (int)_m_cond_targs[_trans];
		
		if ( _m_cond_actions[_trans] != 0 ) {
			
			switch ( _m_cond_actions[_trans] ) {
				case 11:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						b1 = p; }
					
#line 131 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						c1 = p; }
					
#line 141 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						d1 = p; }
					
#line 151 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						e1 = p; }
					
#line 161 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						f1 = p; }
					
#line 171 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						g1 = p; }
					
#line 181 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						h1 = p; }
					
#line 191 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						a1 = p; }
					
#line 201 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 211 "gen/ragel/alt1_8-F1.c"
					
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
					
#line 227 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 237 "gen/ragel/alt1_8-F1.c"
					
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
					
#line 253 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 263 "gen/ragel/alt1_8-F1.c"
					
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
					
#line 279 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 289 "gen/ragel/alt1_8-F1.c"
					
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
					
#line 305 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 315 "gen/ragel/alt1_8-F1.c"
					
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
					
#line 331 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 341 "gen/ragel/alt1_8-F1.c"
					
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
					
#line 357 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 367 "gen/ragel/alt1_8-F1.c"
					
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
					
#line 383 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 393 "gen/ragel/alt1_8-F1.c"
					
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
					
#line 409 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						b1 = p; }
					
#line 419 "gen/ragel/alt1_8-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 425 "gen/ragel/alt1_8-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						c1 = p; }
					
#line 431 "gen/ragel/alt1_8-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 437 "gen/ragel/alt1_8-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						d1 = p; }
					
#line 443 "gen/ragel/alt1_8-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 449 "gen/ragel/alt1_8-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						e1 = p; }
					
#line 455 "gen/ragel/alt1_8-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 461 "gen/ragel/alt1_8-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						f1 = p; }
					
#line 467 "gen/ragel/alt1_8-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 473 "gen/ragel/alt1_8-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						g1 = p; }
					
#line 479 "gen/ragel/alt1_8-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 485 "gen/ragel/alt1_8-F1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						h1 = p; }
					
#line 491 "gen/ragel/alt1_8-F1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 497 "gen/ragel/alt1_8-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						a1 = p; }
					
#line 503 "gen/ragel/alt1_8-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 509 "gen/ragel/alt1_8-F1.c"
					
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
					
#line 525 "gen/ragel/alt1_8-F1.c"
					
					
					break; 
				}
			}
			
		}
		
		if ( cs != 0 ) {
			p += 1;
			goto _resume;
		}
		_out: {}
	}
	
#line 48 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
	
	
	in->p = p;
	in->pe = pe;
}
