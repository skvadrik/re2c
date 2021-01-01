#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 48 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"



#line 13 "gen/ragel/alt4_2-F1.c"
static const char _m_trans_keys[] = {
	1, 0, 0, 3, 0, 3, 0, 3,
	0, 3, 0, 3, 0, 3, 0, 3,
	0, 2, 0, 3, 0
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
	3, 0
};

static const signed char _m_index_offsets[] = {
	0, 0, 4, 8, 12, 16, 20, 24,
	28, 31, 0
};

static const signed char _m_indicies[] = {
	2, 0, 1, 3, 5, 0, 6, 4,
	8, 0, 7, 9, 11, 0, 0, 10,
	13, 0, 14, 12, 16, 0, 15, 17,
	19, 0, 20, 18, 22, 0, 21, 24,
	0, 25, 26, 0
};

static const signed char _m_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _m_cond_targs[] = {
	0, 1, 9, 2, 2, 9, 3, 3,
	9, 4, 4, 9, 5, 9, 6, 6,
	9, 7, 7, 9, 8, 8, 9, 9,
	9, 1, 5, 0
};

static const signed char _m_cond_actions[] = {
	0, 0, 1, 2, 0, 3, 4, 0,
	5, 6, 0, 7, 0, 8, 9, 0,
	10, 11, 0, 12, 13, 0, 14, 0,
	15, 16, 17, 0
};

static const int m_start = 9;
static const int m_first_final = 9;
static const int m_error = 0;

static const int m_en_main = 9;


#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1,
	*a2, *b2,
	*a3, *b3,
	*a4, *b4,
	*a5, *b5,
	*a6, *b6,
	*a7, *b7,
	*a8, *b8;
	int cs;
	
	
#line 93 "gen/ragel/alt4_2-F1.c"
	{
		cs = (int)m_start;
	}
	
#line 67 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
	
	
#line 101 "gen/ragel/alt4_2-F1.c"
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
		
		if ( ( (*( p))) <= 98 && ( (*( p))) >= 10 ) {
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
				case 17:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b1 = p; }
					
#line 134 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a1 = p; }
					
#line 144 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 154 "gen/ragel/alt4_2-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a3 = p; }
					
#line 160 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 170 "gen/ragel/alt4_2-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b3 = p; }
					
#line 176 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 186 "gen/ragel/alt4_2-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a5 = p; }
					
#line 192 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 202 "gen/ragel/alt4_2-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b5 = p; }
					
#line 208 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b6 = p; a5 = a6 = NULL; }
					
#line 218 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 224 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a6 = p; b5 = b6 = NULL; }
					
#line 234 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 240 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 250 "gen/ragel/alt4_2-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						outc(out, '\n');
					}
					
#line 266 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 276 "gen/ragel/alt4_2-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						outc(out, '\n');
					}
					
#line 292 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b6 = p; a5 = a6 = NULL; }
					
#line 302 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 308 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 314 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 320 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 326 "gen/ragel/alt4_2-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						outc(out, '\n');
					}
					
#line 342 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a6 = p; b5 = b6 = NULL; }
					
#line 352 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 358 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 364 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 370 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 376 "gen/ragel/alt4_2-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						outc(out, '\n');
					}
					
#line 392 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 402 "gen/ragel/alt4_2-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b5 = p; }
					
#line 408 "gen/ragel/alt4_2-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b6 = p; a5 = a6 = NULL; }
					
#line 414 "gen/ragel/alt4_2-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a5 = p; }
					
#line 420 "gen/ragel/alt4_2-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a6 = p; b5 = b6 = NULL; }
					
#line 426 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 432 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 438 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 444 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 450 "gen/ragel/alt4_2-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						outc(out, '\n');
					}
					
#line 466 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 476 "gen/ragel/alt4_2-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b5 = p; }
					
#line 482 "gen/ragel/alt4_2-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b6 = p; a5 = a6 = NULL; }
					
#line 488 "gen/ragel/alt4_2-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a5 = p; }
					
#line 494 "gen/ragel/alt4_2-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a6 = p; b5 = b6 = NULL; }
					
#line 500 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 506 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 512 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 518 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 524 "gen/ragel/alt4_2-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						outc(out, '\n');
					}
					
#line 540 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 550 "gen/ragel/alt4_2-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b3 = p; }
					
#line 556 "gen/ragel/alt4_2-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 562 "gen/ragel/alt4_2-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a3 = p; }
					
#line 568 "gen/ragel/alt4_2-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 574 "gen/ragel/alt4_2-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b5 = p; }
					
#line 580 "gen/ragel/alt4_2-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b6 = p; a5 = a6 = NULL; }
					
#line 586 "gen/ragel/alt4_2-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a5 = p; }
					
#line 592 "gen/ragel/alt4_2-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a6 = p; b5 = b6 = NULL; }
					
#line 598 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 604 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 610 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 616 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 622 "gen/ragel/alt4_2-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						outc(out, '\n');
					}
					
#line 638 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 648 "gen/ragel/alt4_2-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b3 = p; }
					
#line 654 "gen/ragel/alt4_2-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 660 "gen/ragel/alt4_2-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a3 = p; }
					
#line 666 "gen/ragel/alt4_2-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 672 "gen/ragel/alt4_2-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b5 = p; }
					
#line 678 "gen/ragel/alt4_2-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b6 = p; a5 = a6 = NULL; }
					
#line 684 "gen/ragel/alt4_2-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a5 = p; }
					
#line 690 "gen/ragel/alt4_2-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a6 = p; b5 = b6 = NULL; }
					
#line 696 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 702 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 708 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 714 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 720 "gen/ragel/alt4_2-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						outc(out, '\n');
					}
					
#line 736 "gen/ragel/alt4_2-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b1 = p; }
					
#line 746 "gen/ragel/alt4_2-F1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 752 "gen/ragel/alt4_2-F1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a1 = p; }
					
#line 758 "gen/ragel/alt4_2-F1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 764 "gen/ragel/alt4_2-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b3 = p; }
					
#line 770 "gen/ragel/alt4_2-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 776 "gen/ragel/alt4_2-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a3 = p; }
					
#line 782 "gen/ragel/alt4_2-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 788 "gen/ragel/alt4_2-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b5 = p; }
					
#line 794 "gen/ragel/alt4_2-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b6 = p; a5 = a6 = NULL; }
					
#line 800 "gen/ragel/alt4_2-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a5 = p; }
					
#line 806 "gen/ragel/alt4_2-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a6 = p; b5 = b6 = NULL; }
					
#line 812 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 818 "gen/ragel/alt4_2-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 824 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 830 "gen/ragel/alt4_2-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 836 "gen/ragel/alt4_2-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						outc(out, '\n');
					}
					
#line 852 "gen/ragel/alt4_2-F1.c"
					
					
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
	
#line 68 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
	
	
	in->p = p;
	in->pe = pe;
}
