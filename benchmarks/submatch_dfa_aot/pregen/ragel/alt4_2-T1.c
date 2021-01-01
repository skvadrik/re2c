#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 48 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"



#line 13 "gen/ragel/alt4_2-T1.c"
static const signed char _m_key_offsets[] = {
	0, 0, 3, 6, 9, 11, 14, 17,
	20, 22, 0
};

static const char _m_trans_keys[] = {
	10, 97, 98, 10, 97, 98, 10, 97,
	98, 10, 98, 10, 97, 98, 10, 97,
	98, 10, 97, 98, 10, 97, 10, 97,
	98, 0
};

static const signed char _m_single_lengths[] = {
	0, 3, 3, 3, 2, 3, 3, 3,
	2, 3, 0
};

static const signed char _m_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _m_index_offsets[] = {
	0, 0, 4, 8, 12, 15, 19, 23,
	27, 30, 0
};

static const signed char _m_cond_targs[] = {
	9, 1, 2, 0, 9, 3, 2, 0,
	9, 3, 4, 0, 9, 4, 0, 9,
	6, 5, 0, 9, 6, 7, 0, 9,
	8, 7, 0, 9, 8, 0, 9, 1,
	5, 0, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 0
};

static const signed char _m_cond_actions[] = {
	1, 0, 2, 0, 3, 4, 0, 0,
	5, 0, 6, 0, 7, 0, 0, 8,
	9, 0, 0, 10, 0, 11, 0, 12,
	13, 0, 0, 14, 0, 0, 15, 16,
	17, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
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
	
	
#line 85 "gen/ragel/alt4_2-T1.c"
	{
		cs = (int)m_start;
	}
	
#line 67 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
	
	
#line 93 "gen/ragel/alt4_2-T1.c"
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
				case 17:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b1 = p; }
					
#line 162 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a1 = p; }
					
#line 172 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 182 "gen/ragel/alt4_2-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a3 = p; }
					
#line 188 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 198 "gen/ragel/alt4_2-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b3 = p; }
					
#line 204 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 214 "gen/ragel/alt4_2-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a5 = p; }
					
#line 220 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 230 "gen/ragel/alt4_2-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b5 = p; }
					
#line 236 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b6 = p; a5 = a6 = NULL; }
					
#line 246 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 252 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a6 = p; b5 = b6 = NULL; }
					
#line 262 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 268 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 278 "gen/ragel/alt4_2-T1.c"
					
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
					
#line 294 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 304 "gen/ragel/alt4_2-T1.c"
					
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
					
#line 320 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b6 = p; a5 = a6 = NULL; }
					
#line 330 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 336 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 342 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 348 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 354 "gen/ragel/alt4_2-T1.c"
					
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
					
#line 370 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a6 = p; b5 = b6 = NULL; }
					
#line 380 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 386 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 392 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 398 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 404 "gen/ragel/alt4_2-T1.c"
					
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
					
#line 420 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 430 "gen/ragel/alt4_2-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b5 = p; }
					
#line 436 "gen/ragel/alt4_2-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b6 = p; a5 = a6 = NULL; }
					
#line 442 "gen/ragel/alt4_2-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a5 = p; }
					
#line 448 "gen/ragel/alt4_2-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a6 = p; b5 = b6 = NULL; }
					
#line 454 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 460 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 466 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 472 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 478 "gen/ragel/alt4_2-T1.c"
					
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
					
#line 494 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 504 "gen/ragel/alt4_2-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b5 = p; }
					
#line 510 "gen/ragel/alt4_2-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b6 = p; a5 = a6 = NULL; }
					
#line 516 "gen/ragel/alt4_2-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a5 = p; }
					
#line 522 "gen/ragel/alt4_2-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a6 = p; b5 = b6 = NULL; }
					
#line 528 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 534 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 540 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 546 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 552 "gen/ragel/alt4_2-T1.c"
					
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
					
#line 568 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 578 "gen/ragel/alt4_2-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b3 = p; }
					
#line 584 "gen/ragel/alt4_2-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 590 "gen/ragel/alt4_2-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a3 = p; }
					
#line 596 "gen/ragel/alt4_2-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 602 "gen/ragel/alt4_2-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b5 = p; }
					
#line 608 "gen/ragel/alt4_2-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b6 = p; a5 = a6 = NULL; }
					
#line 614 "gen/ragel/alt4_2-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a5 = p; }
					
#line 620 "gen/ragel/alt4_2-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a6 = p; b5 = b6 = NULL; }
					
#line 626 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 632 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 638 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 644 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 650 "gen/ragel/alt4_2-T1.c"
					
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
					
#line 666 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 676 "gen/ragel/alt4_2-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b3 = p; }
					
#line 682 "gen/ragel/alt4_2-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 688 "gen/ragel/alt4_2-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a3 = p; }
					
#line 694 "gen/ragel/alt4_2-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 700 "gen/ragel/alt4_2-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b5 = p; }
					
#line 706 "gen/ragel/alt4_2-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b6 = p; a5 = a6 = NULL; }
					
#line 712 "gen/ragel/alt4_2-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a5 = p; }
					
#line 718 "gen/ragel/alt4_2-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a6 = p; b5 = b6 = NULL; }
					
#line 724 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 730 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 736 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 742 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 748 "gen/ragel/alt4_2-T1.c"
					
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
					
#line 764 "gen/ragel/alt4_2-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b1 = p; }
					
#line 774 "gen/ragel/alt4_2-T1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 780 "gen/ragel/alt4_2-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a1 = p; }
					
#line 786 "gen/ragel/alt4_2-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 792 "gen/ragel/alt4_2-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b3 = p; }
					
#line 798 "gen/ragel/alt4_2-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 804 "gen/ragel/alt4_2-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a3 = p; }
					
#line 810 "gen/ragel/alt4_2-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 816 "gen/ragel/alt4_2-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b5 = p; }
					
#line 822 "gen/ragel/alt4_2-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b6 = p; a5 = a6 = NULL; }
					
#line 828 "gen/ragel/alt4_2-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a5 = p; }
					
#line 834 "gen/ragel/alt4_2-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a6 = p; b5 = b6 = NULL; }
					
#line 840 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b7 = p; }
					
#line 846 "gen/ragel/alt4_2-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						b8 = p; a7 = a8 = NULL; }
					
#line 852 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a7 = p; }
					
#line 858 "gen/ragel/alt4_2-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_2.rl"
						a8 = p; b7 = b8 = NULL; }
					
#line 864 "gen/ragel/alt4_2-T1.c"
					
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
					
#line 880 "gen/ragel/alt4_2-T1.c"
					
					
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
