#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 64 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"



#line 13 "gen/ragel/alt4_4-F1.c"
static const char _m_trans_keys[] = {
	1, 0, 0, 5, 0, 5, 0, 5,
	0, 3, 0, 4, 0, 5, 0, 5,
	0, 2, 0, 5, 0, 5, 0, 5,
	0, 5, 0, 5, 0, 5, 0, 5,
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
	0, 0, 6, 12, 18, 22, 27, 33,
	39, 42, 48, 54, 60, 66, 72, 78,
	84, 90, 0
};

static const signed char _m_indicies[] = {
	2, 0, 1, 3, 4, 5, 7, 0,
	8, 6, 9, 10, 12, 0, 11, 13,
	14, 15, 17, 0, 0, 16, 19, 0,
	0, 0, 18, 21, 0, 0, 0, 0,
	20, 23, 0, 24, 25, 22, 26, 28,
	0, 27, 30, 0, 31, 32, 33, 29,
	35, 0, 36, 37, 34, 38, 40, 0,
	41, 39, 42, 43, 45, 0, 46, 47,
	48, 44, 50, 0, 51, 49, 52, 53,
	55, 0, 54, 56, 57, 58, 60, 0,
	61, 62, 59, 63, 65, 0, 66, 67,
	68, 64, 70, 0, 71, 72, 73, 74,
	0
};

static const signed char _m_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _m_cond_targs[] = {
	0, 1, 17, 2, 10, 12, 2, 17,
	3, 7, 9, 3, 17, 4, 5, 6,
	4, 17, 5, 17, 6, 17, 7, 17,
	8, 4, 6, 8, 17, 9, 17, 8,
	4, 5, 10, 17, 3, 11, 9, 11,
	17, 8, 5, 6, 12, 17, 3, 11,
	7, 13, 17, 14, 10, 12, 14, 17,
	11, 7, 9, 15, 17, 14, 2, 12,
	16, 17, 14, 2, 10, 17, 17, 1,
	13, 15, 16, 0
};

static const signed char _m_cond_actions[] = {
	0, 0, 1, 2, 3, 4, 0, 5,
	6, 7, 8, 0, 9, 10, 11, 12,
	0, 13, 0, 14, 0, 15, 0, 16,
	17, 18, 19, 0, 20, 0, 21, 22,
	23, 24, 0, 25, 26, 27, 28, 0,
	29, 30, 31, 32, 0, 33, 34, 35,
	36, 0, 37, 38, 39, 40, 0, 41,
	42, 43, 44, 0, 45, 46, 47, 48,
	0, 49, 50, 51, 52, 0, 53, 54,
	55, 56, 57, 0
};

static const int m_start = 17;
static const int m_first_final = 17;
static const int m_error = 0;

static const int m_en_main = 17;


#line 66 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1, *c1, *d1,
	*a2, *b2, *c2, *d2,
	*a3, *b3, *c3, *d3,
	*a4, *b4, *c4, *d4,
	*a5, *b5, *c5, *d5,
	*a6, *b6, *c6, *d6,
	*a7, *b7, *c7, *d7,
	*a8, *b8, *c8, *d8;
	int cs;
	
	
#line 117 "gen/ragel/alt4_4-F1.c"
	{
		cs = (int)m_start;
	}
	
#line 83 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
	
	
#line 125 "gen/ragel/alt4_4-F1.c"
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
				case 55:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b1 = p; }
					
#line 158 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 56:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c1 = p; }
					
#line 168 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 57:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d1 = p; }
					
#line 178 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 54:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a1 = p; }
					
#line 188 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 39:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 198 "gen/ragel/alt4_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 204 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 40:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 214 "gen/ragel/alt4_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 220 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 38:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 230 "gen/ragel/alt4_4-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 236 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 47:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 246 "gen/ragel/alt4_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 252 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 48:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 262 "gen/ragel/alt4_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 268 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 46:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 278 "gen/ragel/alt4_4-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 284 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 51:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 294 "gen/ragel/alt4_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 300 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 52:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 310 "gen/ragel/alt4_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 316 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 50:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 326 "gen/ragel/alt4_4-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 332 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 342 "gen/ragel/alt4_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 348 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 358 "gen/ragel/alt4_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 364 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 374 "gen/ragel/alt4_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 380 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 390 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 396 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 406 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 412 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 422 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 428 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 27:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 438 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 444 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 28:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 454 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 460 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 26:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 470 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 476 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 35:  {
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 486 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 492 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 36:  {
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 502 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 508 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 34:  {
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 518 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 524 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 42:  {
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 534 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 540 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 43:  {
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 550 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 556 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 44:  {
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 566 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 572 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 31:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 582 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 588 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 32:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 598 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 604 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 30:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 614 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 620 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 630 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 636 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 646 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 652 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 662 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 668 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 678 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 684 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 694 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 700 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 710 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 716 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 726 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 732 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 742 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 748 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 758 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 764 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 774 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 798 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 808 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 832 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 842 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 866 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 876 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 900 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 29:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 910 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 916 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 922 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 928 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 934 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 940 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 946 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 952 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 958 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 982 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 992 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 998 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1004 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1010 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1016 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1022 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1028 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1034 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1040 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 1064 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 1074 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1080 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1086 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1092 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1098 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1104 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1110 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1116 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1122 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 1146 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1156 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1162 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1168 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1174 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1180 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1186 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1192 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1198 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1204 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 1228 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 1238 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 1244 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1250 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 1256 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 1262 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 1268 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 1274 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 1280 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1286 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1292 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1298 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1304 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1310 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1316 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1322 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1328 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1334 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 1358 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 1368 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 1374 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1380 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 1386 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 1392 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 1398 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 1404 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 1410 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1416 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1422 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1428 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1434 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1440 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1446 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1452 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1458 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1464 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 1488 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 33:  {
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 1498 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 1504 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1510 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 1516 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 1522 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 1528 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 1534 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 1540 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1546 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1552 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1558 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1564 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1570 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1576 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1582 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1588 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1594 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 1618 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 41:  {
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 1628 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 1634 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1640 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 1646 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 1652 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 1658 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 1664 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 1670 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1676 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1682 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1688 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1694 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1700 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1706 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1712 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1718 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1724 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 1748 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 37:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 1758 "gen/ragel/alt4_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 1764 "gen/ragel/alt4_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 1770 "gen/ragel/alt4_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 1776 "gen/ragel/alt4_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 1782 "gen/ragel/alt4_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 1788 "gen/ragel/alt4_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 1794 "gen/ragel/alt4_4-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 1800 "gen/ragel/alt4_4-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 1806 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 1812 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1818 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 1824 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 1830 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 1836 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 1842 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 1848 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1854 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1860 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1866 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1872 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1878 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1884 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1890 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1896 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1902 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 1926 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 45:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 1936 "gen/ragel/alt4_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 1942 "gen/ragel/alt4_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 1948 "gen/ragel/alt4_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 1954 "gen/ragel/alt4_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 1960 "gen/ragel/alt4_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 1966 "gen/ragel/alt4_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 1972 "gen/ragel/alt4_4-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 1978 "gen/ragel/alt4_4-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 1984 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 1990 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1996 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 2002 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 2008 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 2014 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 2020 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 2026 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2032 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 2038 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2044 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 2050 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 2056 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 2062 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 2068 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 2074 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2080 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 2104 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 49:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 2114 "gen/ragel/alt4_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 2120 "gen/ragel/alt4_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 2126 "gen/ragel/alt4_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 2132 "gen/ragel/alt4_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 2138 "gen/ragel/alt4_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 2144 "gen/ragel/alt4_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 2150 "gen/ragel/alt4_4-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 2156 "gen/ragel/alt4_4-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 2162 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 2168 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2174 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 2180 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 2186 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 2192 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 2198 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 2204 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2210 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 2216 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2222 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 2228 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 2234 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 2240 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 2246 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 2252 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2258 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 2282 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 2292 "gen/ragel/alt4_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 2298 "gen/ragel/alt4_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 2304 "gen/ragel/alt4_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 2310 "gen/ragel/alt4_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 2316 "gen/ragel/alt4_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 2322 "gen/ragel/alt4_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 2328 "gen/ragel/alt4_4-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 2334 "gen/ragel/alt4_4-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 2340 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 2346 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2352 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 2358 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 2364 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 2370 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 2376 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 2382 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2388 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 2394 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2400 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 2406 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 2412 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 2418 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 2424 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 2430 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2436 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 2460 "gen/ragel/alt4_4-F1.c"
					
					
					break; 
				}
				case 53:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b1 = p; }
					
#line 2470 "gen/ragel/alt4_4-F1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 2476 "gen/ragel/alt4_4-F1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c1 = p; }
					
#line 2482 "gen/ragel/alt4_4-F1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 2488 "gen/ragel/alt4_4-F1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d1 = p; }
					
#line 2494 "gen/ragel/alt4_4-F1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 2500 "gen/ragel/alt4_4-F1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a1 = p; }
					
#line 2506 "gen/ragel/alt4_4-F1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 2512 "gen/ragel/alt4_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 2518 "gen/ragel/alt4_4-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 2524 "gen/ragel/alt4_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 2530 "gen/ragel/alt4_4-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 2536 "gen/ragel/alt4_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 2542 "gen/ragel/alt4_4-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 2548 "gen/ragel/alt4_4-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 2554 "gen/ragel/alt4_4-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 2560 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 2566 "gen/ragel/alt4_4-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2572 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 2578 "gen/ragel/alt4_4-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 2584 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 2590 "gen/ragel/alt4_4-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 2596 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 2602 "gen/ragel/alt4_4-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2608 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 2614 "gen/ragel/alt4_4-F1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2620 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 2626 "gen/ragel/alt4_4-F1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 2632 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 2638 "gen/ragel/alt4_4-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 2644 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 2650 "gen/ragel/alt4_4-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2656 "gen/ragel/alt4_4-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
						else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
						if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c5) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d5) { outc(out, 'D'); outs(out, d5, d6); }
						if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c7) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d7) { outc(out, 'D'); outs(out, d7, d8); }
						outc(out, '\n');
					}
					
#line 2680 "gen/ragel/alt4_4-F1.c"
					
					
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
	
#line 84 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
