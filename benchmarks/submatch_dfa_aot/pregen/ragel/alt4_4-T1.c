#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 64 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"



#line 13 "gen/ragel/alt4_4-T1.c"
static const signed char _m_key_offsets[] = {
	0, 0, 5, 10, 15, 17, 19, 21,
	26, 28, 33, 38, 43, 48, 53, 58,
	63, 68, 0
};

static const char _m_trans_keys[] = {
	10, 97, 98, 99, 100, 10, 97, 98,
	99, 100, 10, 97, 98, 99, 100, 10,
	98, 10, 99, 10, 100, 10, 97, 98,
	99, 100, 10, 97, 10, 97, 98, 99,
	100, 10, 97, 98, 99, 100, 10, 97,
	98, 99, 100, 10, 97, 98, 99, 100,
	10, 97, 98, 99, 100, 10, 97, 98,
	99, 100, 10, 97, 98, 99, 100, 10,
	97, 98, 99, 100, 10, 97, 98, 99,
	100, 0
};

static const signed char _m_single_lengths[] = {
	0, 5, 5, 5, 2, 2, 2, 5,
	2, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 0
};

static const signed char _m_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _m_index_offsets[] = {
	0, 0, 6, 12, 18, 21, 24, 27,
	33, 36, 42, 48, 54, 60, 66, 72,
	78, 84, 0
};

static const signed char _m_cond_targs[] = {
	17, 1, 2, 10, 12, 0, 17, 3,
	2, 7, 9, 0, 17, 3, 4, 5,
	6, 0, 17, 4, 0, 17, 5, 0,
	17, 6, 0, 17, 8, 4, 7, 6,
	0, 17, 8, 0, 17, 8, 4, 5,
	9, 0, 17, 3, 11, 10, 9, 0,
	17, 8, 11, 5, 6, 0, 17, 3,
	11, 7, 12, 0, 17, 14, 13, 10,
	12, 0, 17, 14, 11, 7, 9, 0,
	17, 14, 2, 15, 12, 0, 17, 14,
	2, 10, 16, 0, 17, 1, 13, 15,
	16, 0, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 10, 11, 12, 13,
	14, 15, 16, 17, 0
};

static const signed char _m_cond_actions[] = {
	1, 0, 2, 3, 4, 0, 5, 6,
	0, 7, 8, 0, 9, 0, 10, 11,
	12, 0, 13, 0, 0, 14, 0, 0,
	15, 0, 0, 16, 17, 18, 0, 19,
	0, 20, 0, 0, 21, 22, 23, 24,
	0, 0, 25, 26, 27, 0, 28, 0,
	29, 30, 0, 31, 32, 0, 33, 34,
	35, 36, 0, 0, 37, 38, 0, 39,
	40, 0, 41, 0, 42, 43, 44, 0,
	45, 46, 47, 0, 48, 0, 49, 50,
	51, 52, 0, 0, 53, 54, 55, 56,
	57, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
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
	
	
#line 111 "gen/ragel/alt4_4-T1.c"
	{
		cs = (int)m_start;
	}
	
#line 83 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
	
	
#line 119 "gen/ragel/alt4_4-T1.c"
	{
		int _klen;
		unsigned int _trans = 0;
		const char * _keys;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _m_trans_keys + (_m_key_offsets[cs]));
		_trans = (unsigned int)_m_index_offsets[cs];
		
		_klen = (int)_m_single_lengths[cs];
		if ( _klen > 0 ) {
			const char *_lower = _keys;
			const char *_upper = _keys + _klen - 1;
			const char *_mid;
			while ( 1 ) {
				if ( _upper < _lower ) {
					_keys += _klen;
					_trans += (unsigned int)_klen;
					break;
				}
				
				_mid = _lower + ((_upper-_lower) >> 1);
				if ( ( (*( p))) < (*( _mid)) )
					_upper = _mid - 1;
				else if ( ( (*( p))) > (*( _mid)) )
					_lower = _mid + 1;
				else {
					_trans += (unsigned int)(_mid - _keys);
					goto _match;
				}
			}
		}
		
		_klen = (int)_m_range_lengths[cs];
		if ( _klen > 0 ) {
			const char *_lower = _keys;
			const char *_upper = _keys + (_klen<<1) - 2;
			const char *_mid;
			while ( 1 ) {
				if ( _upper < _lower ) {
					_trans += (unsigned int)_klen;
					break;
				}
				
				_mid = _lower + (((_upper-_lower) >> 1) & ~1);
				if ( ( (*( p))) < (*( _mid)) )
					_upper = _mid - 2;
				else if ( ( (*( p))) > (*( _mid + 1)) )
					_lower = _mid + 2;
				else {
					_trans += (unsigned int)((_mid - _keys)>>1);
					break;
				}
			}
		}
		
		_match: {}
		cs = (int)_m_cond_targs[_trans];
		
		if ( _m_cond_actions[_trans] != 0 ) {
			
			switch ( _m_cond_actions[_trans] ) {
				case 55:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b1 = p; }
					
#line 188 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 56:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c1 = p; }
					
#line 198 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 57:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d1 = p; }
					
#line 208 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 54:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a1 = p; }
					
#line 218 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 39:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 228 "gen/ragel/alt4_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 234 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 40:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 244 "gen/ragel/alt4_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 250 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 38:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 260 "gen/ragel/alt4_4-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 266 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 47:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 276 "gen/ragel/alt4_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 282 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 48:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 292 "gen/ragel/alt4_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 298 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 46:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 308 "gen/ragel/alt4_4-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 314 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 51:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 324 "gen/ragel/alt4_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 330 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 52:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 340 "gen/ragel/alt4_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 346 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 50:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 356 "gen/ragel/alt4_4-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 362 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 372 "gen/ragel/alt4_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 378 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 388 "gen/ragel/alt4_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 394 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 404 "gen/ragel/alt4_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 410 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 420 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 426 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 436 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 442 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 452 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 458 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 27:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 468 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 474 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 28:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 484 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 490 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 26:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 500 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 506 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 35:  {
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 516 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 522 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 36:  {
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 532 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 538 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 34:  {
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 548 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 554 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 42:  {
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 564 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 570 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 43:  {
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 580 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 586 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 44:  {
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 596 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 602 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 31:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 612 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 618 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 32:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 628 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 634 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 30:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 644 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 650 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 660 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 666 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 676 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 682 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 692 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 698 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 708 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 714 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 724 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 730 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 740 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 746 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 756 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 762 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 772 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 778 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 788 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 794 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 804 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 828 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 838 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 862 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 872 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 896 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 906 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 930 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 29:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 940 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 946 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 952 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 958 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 964 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 970 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 976 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 982 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 988 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 1012 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 1022 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1028 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1034 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1040 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1046 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1052 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1058 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1064 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1070 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 1094 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 1104 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1110 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1116 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1122 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1128 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1134 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1140 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1146 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1152 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 1176 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1186 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1192 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1198 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1204 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1210 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1216 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1222 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1228 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1234 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 1258 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 1268 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 1274 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1280 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 1286 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 1292 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 1298 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 1304 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 1310 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1316 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1322 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1328 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1334 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1340 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1346 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1352 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1358 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1364 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 1388 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 1398 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 1404 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1410 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 1416 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 1422 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 1428 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 1434 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 1440 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1446 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1452 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1458 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1464 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1470 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1476 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1482 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1488 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1494 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 1518 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 33:  {
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 1528 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 1534 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1540 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 1546 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 1552 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 1558 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 1564 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 1570 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1576 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1582 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1588 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1594 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1600 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1606 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1612 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1618 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1624 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 1648 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 41:  {
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 1658 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 1664 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1670 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 1676 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 1682 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 1688 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 1694 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 1700 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1706 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1712 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1718 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1724 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1730 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1736 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1742 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1748 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1754 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 1778 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 37:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 1788 "gen/ragel/alt4_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 1794 "gen/ragel/alt4_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 1800 "gen/ragel/alt4_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 1806 "gen/ragel/alt4_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 1812 "gen/ragel/alt4_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 1818 "gen/ragel/alt4_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 1824 "gen/ragel/alt4_4-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 1830 "gen/ragel/alt4_4-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 1836 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 1842 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1848 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 1854 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 1860 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 1866 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 1872 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 1878 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 1884 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 1890 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1896 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 1902 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 1908 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 1914 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 1920 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 1926 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 1932 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 1956 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 45:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 1966 "gen/ragel/alt4_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 1972 "gen/ragel/alt4_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 1978 "gen/ragel/alt4_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 1984 "gen/ragel/alt4_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 1990 "gen/ragel/alt4_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 1996 "gen/ragel/alt4_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 2002 "gen/ragel/alt4_4-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 2008 "gen/ragel/alt4_4-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 2014 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 2020 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2026 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 2032 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 2038 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 2044 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 2050 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 2056 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2062 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 2068 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2074 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 2080 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 2086 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 2092 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 2098 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 2104 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2110 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 2134 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 49:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 2144 "gen/ragel/alt4_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 2150 "gen/ragel/alt4_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 2156 "gen/ragel/alt4_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 2162 "gen/ragel/alt4_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 2168 "gen/ragel/alt4_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 2174 "gen/ragel/alt4_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 2180 "gen/ragel/alt4_4-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 2186 "gen/ragel/alt4_4-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 2192 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 2198 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2204 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 2210 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 2216 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 2222 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 2228 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 2234 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2240 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 2246 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2252 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 2258 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 2264 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 2270 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 2276 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 2282 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2288 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 2312 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 2322 "gen/ragel/alt4_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 2328 "gen/ragel/alt4_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 2334 "gen/ragel/alt4_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 2340 "gen/ragel/alt4_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 2346 "gen/ragel/alt4_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 2352 "gen/ragel/alt4_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 2358 "gen/ragel/alt4_4-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 2364 "gen/ragel/alt4_4-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 2370 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 2376 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2382 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 2388 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 2394 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 2400 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 2406 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 2412 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2418 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 2424 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2430 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 2436 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 2442 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 2448 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 2454 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 2460 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2466 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 2490 "gen/ragel/alt4_4-T1.c"
					
					
					break; 
				}
				case 53:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b1 = p; }
					
#line 2500 "gen/ragel/alt4_4-T1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 2506 "gen/ragel/alt4_4-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c1 = p; }
					
#line 2512 "gen/ragel/alt4_4-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 2518 "gen/ragel/alt4_4-T1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d1 = p; }
					
#line 2524 "gen/ragel/alt4_4-T1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 2530 "gen/ragel/alt4_4-T1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a1 = p; }
					
#line 2536 "gen/ragel/alt4_4-T1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 2542 "gen/ragel/alt4_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b3 = p; }
					
#line 2548 "gen/ragel/alt4_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 2554 "gen/ragel/alt4_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c3 = p; }
					
#line 2560 "gen/ragel/alt4_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 2566 "gen/ragel/alt4_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d3 = p; }
					
#line 2572 "gen/ragel/alt4_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 2578 "gen/ragel/alt4_4-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a3 = p; }
					
#line 2584 "gen/ragel/alt4_4-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 2590 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b5 = p; }
					
#line 2596 "gen/ragel/alt4_4-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2602 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c5 = p; }
					
#line 2608 "gen/ragel/alt4_4-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; }
					
#line 2614 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d5 = p; }
					
#line 2620 "gen/ragel/alt4_4-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; }
					
#line 2626 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a5 = p; }
					
#line 2632 "gen/ragel/alt4_4-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; }
					
#line 2638 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b7 = p; }
					
#line 2644 "gen/ragel/alt4_4-T1.c"
					
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2650 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c7 = p; }
					
#line 2656 "gen/ragel/alt4_4-T1.c"
					
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; }
					
#line 2662 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d7 = p; }
					
#line 2668 "gen/ragel/alt4_4-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; }
					
#line 2674 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a7 = p; }
					
#line 2680 "gen/ragel/alt4_4-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_4.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; }
					
#line 2686 "gen/ragel/alt4_4-T1.c"
					
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
					
#line 2710 "gen/ragel/alt4_4-T1.c"
					
					
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
