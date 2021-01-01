#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"



#line 13 "gen/ragel/alt2_8-T1.c"
static const signed char _m_key_offsets[] = {
	0, 0, 9, 11, 13, 15, 17, 19,
	21, 23, 32, 34, 43, 52, 61, 70,
	79, 88, 0
};

static const char _m_trans_keys[] = {
	10, 97, 98, 99, 100, 101, 102, 103,
	104, 10, 98, 10, 99, 10, 100, 10,
	101, 10, 102, 10, 103, 10, 104, 10,
	97, 98, 99, 100, 101, 102, 103, 104,
	10, 97, 10, 97, 98, 99, 100, 101,
	102, 103, 104, 10, 97, 98, 99, 100,
	101, 102, 103, 104, 10, 97, 98, 99,
	100, 101, 102, 103, 104, 10, 97, 98,
	99, 100, 101, 102, 103, 104, 10, 97,
	98, 99, 100, 101, 102, 103, 104, 10,
	97, 98, 99, 100, 101, 102, 103, 104,
	10, 97, 98, 99, 100, 101, 102, 103,
	104, 0
};

static const signed char _m_single_lengths[] = {
	0, 9, 2, 2, 2, 2, 2, 2,
	2, 9, 2, 9, 9, 9, 9, 9,
	9, 9, 0
};

static const signed char _m_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _m_index_offsets[] = {
	0, 0, 10, 13, 16, 19, 22, 25,
	28, 31, 41, 44, 54, 64, 74, 84,
	94, 104, 0
};

static const signed char _m_cond_targs[] = {
	17, 1, 2, 3, 4, 5, 6, 7,
	8, 0, 17, 2, 0, 17, 3, 0,
	17, 4, 0, 17, 5, 0, 17, 6,
	0, 17, 7, 0, 17, 8, 0, 17,
	10, 9, 3, 4, 5, 6, 7, 8,
	0, 17, 10, 0, 17, 10, 2, 11,
	4, 5, 6, 7, 8, 0, 17, 10,
	2, 3, 12, 5, 6, 7, 8, 0,
	17, 10, 2, 3, 4, 13, 6, 7,
	8, 0, 17, 10, 2, 3, 4, 5,
	14, 7, 8, 0, 17, 10, 2, 3,
	4, 5, 6, 15, 8, 0, 17, 10,
	2, 3, 4, 5, 6, 7, 16, 0,
	17, 1, 9, 11, 12, 13, 14, 15,
	16, 0, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 10, 11, 12, 13,
	14, 15, 16, 17, 0
};

static const signed char _m_cond_actions[] = {
	1, 0, 2, 3, 4, 5, 6, 7,
	8, 0, 9, 0, 0, 10, 0, 0,
	11, 0, 0, 12, 0, 0, 13, 0,
	0, 14, 0, 0, 15, 0, 0, 16,
	17, 0, 18, 19, 20, 21, 22, 23,
	0, 24, 0, 0, 25, 26, 27, 0,
	28, 29, 30, 31, 32, 0, 33, 34,
	35, 36, 0, 37, 38, 39, 40, 0,
	41, 42, 43, 44, 45, 0, 46, 47,
	48, 0, 49, 50, 51, 52, 53, 54,
	0, 55, 56, 0, 57, 58, 59, 60,
	61, 62, 63, 0, 64, 0, 65, 66,
	67, 68, 69, 70, 71, 72, 0, 0,
	73, 74, 75, 76, 77, 78, 79, 80,
	81, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
};

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
	
	
#line 116 "gen/ragel/alt2_8-T1.c"
	{
		cs = (int)m_start;
	}
	
#line 74 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
	
	
#line 124 "gen/ragel/alt2_8-T1.c"
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
				case 75:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b1 = p; }
					
#line 193 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 76:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c1 = p; }
					
#line 203 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 77:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d1 = p; }
					
#line 213 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 78:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e1 = p; }
					
#line 223 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 79:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f1 = p; }
					
#line 233 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 80:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g1 = p; }
					
#line 243 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 81:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h1 = p; }
					
#line 253 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 74:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a1 = p; }
					
#line 263 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 273 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 279 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 289 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 295 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 305 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 311 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 321 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 327 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 337 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 343 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 353 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 359 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 369 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 375 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 27:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 385 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 391 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 28:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 401 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 407 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 29:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 417 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 423 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 30:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 433 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 439 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 31:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 449 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 455 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 32:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 465 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 471 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 26:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 481 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 487 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 35:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 497 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 503 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 36:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 513 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 519 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 37:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 529 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 535 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 38:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 545 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 551 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 39:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 561 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 567 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 40:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 577 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 583 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 34:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 593 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 599 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 43:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 609 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 615 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 44:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 625 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 631 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 45:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 641 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 647 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 46:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 657 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 663 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 47:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 673 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 679 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 48:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 689 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 695 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 42:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 705 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 711 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 51:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 721 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 727 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 52:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 737 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 743 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 53:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 753 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 759 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 54:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 769 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 775 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 55:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 785 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 791 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 56:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 801 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 807 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 50:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 817 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 823 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 59:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 833 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 839 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 60:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 849 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 855 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 61:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 865 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 871 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 62:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 881 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 887 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 63:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 897 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 903 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 64:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 913 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 919 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 58:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 929 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 935 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 67:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 945 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 951 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 68:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 961 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 967 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 69:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 977 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 983 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 70:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 993 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 999 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 71:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1009 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 1015 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 72:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1025 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 1031 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 66:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1041 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 1047 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1057 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 1063 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1073 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 1079 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1089 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 1095 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1105 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 1111 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1121 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 1127 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1137 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 1143 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1153 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 1159 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1169 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 1193 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1203 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 1227 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1237 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 1261 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1271 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 1295 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1305 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 1329 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1339 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 1363 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1373 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 1397 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1407 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 1431 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1441 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 1447 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1453 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 1459 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1465 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 1471 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1477 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 1483 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1489 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 1495 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1501 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 1507 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1513 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 1519 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1525 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 1531 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1537 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 1561 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1571 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 1577 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1583 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 1589 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1595 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 1601 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1607 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 1613 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1619 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 1625 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1631 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 1637 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1643 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 1649 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1655 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 1661 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1667 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 1691 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 33:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1701 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 1707 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1713 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 1719 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1725 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 1731 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1737 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 1743 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1749 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 1755 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1761 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 1767 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1773 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 1779 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1785 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 1791 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1797 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 1821 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 41:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1831 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 1837 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1843 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 1849 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1855 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 1861 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1867 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 1873 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1879 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 1885 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1891 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 1897 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1903 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 1909 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1915 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 1921 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1927 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 1951 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 49:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1961 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 1967 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1973 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 1979 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1985 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 1991 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1997 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 2003 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2009 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 2015 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2021 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 2027 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 2033 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 2039 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 2045 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 2051 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2057 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 2081 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 57:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 2091 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 2097 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2103 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 2109 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2115 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 2121 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2127 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 2133 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2139 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 2145 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2151 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 2157 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 2163 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 2169 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 2175 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 2181 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2187 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 2211 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 65:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 2221 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 2227 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2233 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 2239 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2245 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 2251 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2257 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 2263 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2269 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 2275 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2281 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 2287 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 2293 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 2299 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 2305 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 2311 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2317 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 2341 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 2351 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 2357 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2363 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 2369 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2375 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 2381 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2387 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 2393 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2399 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 2405 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2411 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 2417 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 2423 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 2429 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 2435 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 2441 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2447 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 2471 "gen/ragel/alt2_8-T1.c"
					
					
					break; 
				}
				case 73:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b1 = p; }
					
#line 2481 "gen/ragel/alt2_8-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 2487 "gen/ragel/alt2_8-T1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c1 = p; }
					
#line 2493 "gen/ragel/alt2_8-T1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 2499 "gen/ragel/alt2_8-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d1 = p; }
					
#line 2505 "gen/ragel/alt2_8-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 2511 "gen/ragel/alt2_8-T1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e1 = p; }
					
#line 2517 "gen/ragel/alt2_8-T1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 2523 "gen/ragel/alt2_8-T1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f1 = p; }
					
#line 2529 "gen/ragel/alt2_8-T1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 2535 "gen/ragel/alt2_8-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g1 = p; }
					
#line 2541 "gen/ragel/alt2_8-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 2547 "gen/ragel/alt2_8-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h1 = p; }
					
#line 2553 "gen/ragel/alt2_8-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 2559 "gen/ragel/alt2_8-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a1 = p; }
					
#line 2565 "gen/ragel/alt2_8-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 2571 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 2577 "gen/ragel/alt2_8-T1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2583 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 2589 "gen/ragel/alt2_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2595 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 2601 "gen/ragel/alt2_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2607 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 2613 "gen/ragel/alt2_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2619 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 2625 "gen/ragel/alt2_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2631 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 2637 "gen/ragel/alt2_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 2643 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 2649 "gen/ragel/alt2_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 2655 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 2661 "gen/ragel/alt2_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2667 "gen/ragel/alt2_8-T1.c"
					
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
					
#line 2691 "gen/ragel/alt2_8-T1.c"
					
					
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
	
#line 75 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
	
	
	in->p = p;
	in->pe = pe;
}
