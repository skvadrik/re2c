#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"



#line 13 "gen/ragel/alt2_4-F1.c"
static const char _m_trans_keys[] = {
	1, 0, 0, 5, 0, 3, 0, 4,
	0, 5, 0, 5, 0, 2, 0, 5,
	0, 5, 0, 5, 0
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
	3, 4, 5, 0
};

static const signed char _m_index_offsets[] = {
	0, 0, 6, 10, 15, 21, 27, 30,
	36, 42, 0
};

static const signed char _m_indicies[] = {
	2, 0, 1, 3, 4, 5, 7, 0,
	0, 6, 9, 0, 0, 0, 8, 11,
	0, 0, 0, 0, 10, 13, 0, 14,
	12, 15, 16, 18, 0, 17, 20, 0,
	21, 22, 19, 23, 25, 0, 26, 27,
	28, 24, 30, 0, 31, 32, 33, 34,
	0
};

static const signed char _m_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _m_cond_targs[] = {
	0, 1, 9, 2, 3, 4, 2, 9,
	3, 9, 4, 9, 5, 9, 6, 3,
	4, 6, 9, 7, 9, 6, 2, 4,
	8, 9, 6, 2, 3, 9, 9, 1,
	5, 7, 8, 0
};

static const signed char _m_cond_actions[] = {
	0, 0, 1, 2, 3, 4, 0, 5,
	0, 6, 0, 7, 0, 8, 9, 10,
	11, 0, 12, 0, 13, 14, 15, 16,
	0, 17, 18, 19, 20, 0, 21, 22,
	23, 24, 25, 0
};

static const int m_start = 9;
static const int m_first_final = 9;
static const int m_error = 0;

static const int m_en_main = 9;


#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"


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
	
	
#line 93 "gen/ragel/alt2_4-F1.c"
	{
		cs = (int)m_start;
	}
	
#line 58 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
	
	
#line 101 "gen/ragel/alt2_4-F1.c"
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
		
		if ( ( (*( p))) <= 100 && ( (*( p))) >= 10 ) {
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
				case 23:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b1 = p; }
					
#line 134 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c1 = p; }
					
#line 144 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d1 = p; }
					
#line 154 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a1 = p; }
					
#line 164 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 174 "gen/ragel/alt2_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 180 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 190 "gen/ragel/alt2_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 196 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 206 "gen/ragel/alt2_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 212 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 222 "gen/ragel/alt2_4-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 228 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 238 "gen/ragel/alt2_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 244 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 254 "gen/ragel/alt2_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 260 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 270 "gen/ragel/alt2_4-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 276 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 286 "gen/ragel/alt2_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 292 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 302 "gen/ragel/alt2_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 308 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 318 "gen/ragel/alt2_4-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 324 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 334 "gen/ragel/alt2_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 340 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 350 "gen/ragel/alt2_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 356 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 366 "gen/ragel/alt2_4-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						
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
					
#line 382 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 392 "gen/ragel/alt2_4-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						
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
					
#line 408 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 418 "gen/ragel/alt2_4-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						
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
					
#line 434 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 444 "gen/ragel/alt2_4-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						
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
					
#line 460 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 470 "gen/ragel/alt2_4-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 476 "gen/ragel/alt2_4-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 482 "gen/ragel/alt2_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 488 "gen/ragel/alt2_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 494 "gen/ragel/alt2_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 500 "gen/ragel/alt2_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 506 "gen/ragel/alt2_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 512 "gen/ragel/alt2_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 518 "gen/ragel/alt2_4-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						
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
					
#line 534 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 544 "gen/ragel/alt2_4-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 550 "gen/ragel/alt2_4-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 556 "gen/ragel/alt2_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 562 "gen/ragel/alt2_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 568 "gen/ragel/alt2_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 574 "gen/ragel/alt2_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 580 "gen/ragel/alt2_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 586 "gen/ragel/alt2_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 592 "gen/ragel/alt2_4-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						
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
					
#line 608 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 618 "gen/ragel/alt2_4-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 624 "gen/ragel/alt2_4-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 630 "gen/ragel/alt2_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 636 "gen/ragel/alt2_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 642 "gen/ragel/alt2_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 648 "gen/ragel/alt2_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 654 "gen/ragel/alt2_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 660 "gen/ragel/alt2_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 666 "gen/ragel/alt2_4-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						
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
					
#line 682 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 692 "gen/ragel/alt2_4-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 698 "gen/ragel/alt2_4-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 704 "gen/ragel/alt2_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 710 "gen/ragel/alt2_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 716 "gen/ragel/alt2_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 722 "gen/ragel/alt2_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 728 "gen/ragel/alt2_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 734 "gen/ragel/alt2_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 740 "gen/ragel/alt2_4-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						
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
					
#line 756 "gen/ragel/alt2_4-F1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b1 = p; }
					
#line 766 "gen/ragel/alt2_4-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 772 "gen/ragel/alt2_4-F1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c1 = p; }
					
#line 778 "gen/ragel/alt2_4-F1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 784 "gen/ragel/alt2_4-F1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d1 = p; }
					
#line 790 "gen/ragel/alt2_4-F1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 796 "gen/ragel/alt2_4-F1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a1 = p; }
					
#line 802 "gen/ragel/alt2_4-F1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 808 "gen/ragel/alt2_4-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 814 "gen/ragel/alt2_4-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 820 "gen/ragel/alt2_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 826 "gen/ragel/alt2_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 832 "gen/ragel/alt2_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 838 "gen/ragel/alt2_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 844 "gen/ragel/alt2_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 850 "gen/ragel/alt2_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 856 "gen/ragel/alt2_4-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						
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
					
#line 872 "gen/ragel/alt2_4-F1.c"
					
					
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
	
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
