#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"



#line 13 "gen/ragel/alt2_4-T1.c"
static const signed char _m_key_offsets[] = {
	0, 0, 5, 7, 9, 11, 16, 18,
	23, 28, 0
};

static const char _m_trans_keys[] = {
	10, 97, 98, 99, 100, 10, 98, 10,
	99, 10, 100, 10, 97, 98, 99, 100,
	10, 97, 10, 97, 98, 99, 100, 10,
	97, 98, 99, 100, 10, 97, 98, 99,
	100, 0
};

static const signed char _m_single_lengths[] = {
	0, 5, 2, 2, 2, 5, 2, 5,
	5, 5, 0
};

static const signed char _m_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _m_index_offsets[] = {
	0, 0, 6, 9, 12, 15, 21, 24,
	30, 36, 0
};

static const signed char _m_cond_targs[] = {
	9, 1, 2, 3, 4, 0, 9, 2,
	0, 9, 3, 0, 9, 4, 0, 9,
	6, 5, 3, 4, 0, 9, 6, 0,
	9, 6, 2, 7, 4, 0, 9, 6,
	2, 3, 8, 0, 9, 1, 5, 7,
	8, 0, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 0
};

static const signed char _m_cond_actions[] = {
	1, 0, 2, 3, 4, 0, 5, 0,
	0, 6, 0, 0, 7, 0, 0, 8,
	9, 0, 10, 11, 0, 12, 0, 0,
	13, 14, 15, 0, 16, 0, 17, 18,
	19, 20, 0, 0, 21, 22, 23, 24,
	25, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
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
	
	
#line 84 "gen/ragel/alt2_4-T1.c"
	{
		cs = (int)m_start;
	}
	
#line 58 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
	
	
#line 92 "gen/ragel/alt2_4-T1.c"
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
				case 23:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b1 = p; }
					
#line 161 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c1 = p; }
					
#line 171 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d1 = p; }
					
#line 181 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a1 = p; }
					
#line 191 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 201 "gen/ragel/alt2_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 207 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 217 "gen/ragel/alt2_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 223 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 233 "gen/ragel/alt2_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 239 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 249 "gen/ragel/alt2_4-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 255 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 265 "gen/ragel/alt2_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 271 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 281 "gen/ragel/alt2_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 287 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 297 "gen/ragel/alt2_4-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 303 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 313 "gen/ragel/alt2_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 319 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 329 "gen/ragel/alt2_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 335 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 345 "gen/ragel/alt2_4-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 351 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 361 "gen/ragel/alt2_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 367 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 377 "gen/ragel/alt2_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 383 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 393 "gen/ragel/alt2_4-T1.c"
					
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
					
#line 409 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 419 "gen/ragel/alt2_4-T1.c"
					
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
					
#line 435 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 445 "gen/ragel/alt2_4-T1.c"
					
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
					
#line 461 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 471 "gen/ragel/alt2_4-T1.c"
					
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
					
#line 487 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 497 "gen/ragel/alt2_4-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 503 "gen/ragel/alt2_4-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 509 "gen/ragel/alt2_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 515 "gen/ragel/alt2_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 521 "gen/ragel/alt2_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 527 "gen/ragel/alt2_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 533 "gen/ragel/alt2_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 539 "gen/ragel/alt2_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 545 "gen/ragel/alt2_4-T1.c"
					
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
					
#line 561 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 571 "gen/ragel/alt2_4-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 577 "gen/ragel/alt2_4-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 583 "gen/ragel/alt2_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 589 "gen/ragel/alt2_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 595 "gen/ragel/alt2_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 601 "gen/ragel/alt2_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 607 "gen/ragel/alt2_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 613 "gen/ragel/alt2_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 619 "gen/ragel/alt2_4-T1.c"
					
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
					
#line 635 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 645 "gen/ragel/alt2_4-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 651 "gen/ragel/alt2_4-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 657 "gen/ragel/alt2_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 663 "gen/ragel/alt2_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 669 "gen/ragel/alt2_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 675 "gen/ragel/alt2_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 681 "gen/ragel/alt2_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 687 "gen/ragel/alt2_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 693 "gen/ragel/alt2_4-T1.c"
					
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
					
#line 709 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 719 "gen/ragel/alt2_4-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 725 "gen/ragel/alt2_4-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 731 "gen/ragel/alt2_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 737 "gen/ragel/alt2_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 743 "gen/ragel/alt2_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 749 "gen/ragel/alt2_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 755 "gen/ragel/alt2_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 761 "gen/ragel/alt2_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 767 "gen/ragel/alt2_4-T1.c"
					
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
					
#line 783 "gen/ragel/alt2_4-T1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b1 = p; }
					
#line 793 "gen/ragel/alt2_4-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 799 "gen/ragel/alt2_4-T1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c1 = p; }
					
#line 805 "gen/ragel/alt2_4-T1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 811 "gen/ragel/alt2_4-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d1 = p; }
					
#line 817 "gen/ragel/alt2_4-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 823 "gen/ragel/alt2_4-T1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a1 = p; }
					
#line 829 "gen/ragel/alt2_4-T1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 835 "gen/ragel/alt2_4-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b3 = p; }
					
#line 841 "gen/ragel/alt2_4-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 847 "gen/ragel/alt2_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c3 = p; }
					
#line 853 "gen/ragel/alt2_4-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; }
					
#line 859 "gen/ragel/alt2_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d3 = p; }
					
#line 865 "gen/ragel/alt2_4-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; }
					
#line 871 "gen/ragel/alt2_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a3 = p; }
					
#line 877 "gen/ragel/alt2_4-T1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_4.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; }
					
#line 883 "gen/ragel/alt2_4-T1.c"
					
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
					
#line 899 "gen/ragel/alt2_4-T1.c"
					
					
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
