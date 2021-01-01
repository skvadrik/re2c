#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 96 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"



#line 13 "gen/ragel/alt4_8-T1.c"
static const short _m_key_offsets[] = {
	0, 0, 9, 18, 27, 29, 31, 33,
	35, 37, 39, 41, 50, 52, 61, 70,
	79, 88, 97, 106, 115, 124, 133, 142,
	151, 160, 169, 178, 187, 196, 205, 214,
	223, 232, 0
};

static const char _m_trans_keys[] = {
	10, 97, 98, 99, 100, 101, 102, 103,
	104, 10, 97, 98, 99, 100, 101, 102,
	103, 104, 10, 97, 98, 99, 100, 101,
	102, 103, 104, 10, 98, 10, 99, 10,
	100, 10, 101, 10, 102, 10, 103, 10,
	104, 10, 97, 98, 99, 100, 101, 102,
	103, 104, 10, 97, 10, 97, 98, 99,
	100, 101, 102, 103, 104, 10, 97, 98,
	99, 100, 101, 102, 103, 104, 10, 97,
	98, 99, 100, 101, 102, 103, 104, 10,
	97, 98, 99, 100, 101, 102, 103, 104,
	10, 97, 98, 99, 100, 101, 102, 103,
	104, 10, 97, 98, 99, 100, 101, 102,
	103, 104, 10, 97, 98, 99, 100, 101,
	102, 103, 104, 10, 97, 98, 99, 100,
	101, 102, 103, 104, 10, 97, 98, 99,
	100, 101, 102, 103, 104, 10, 97, 98,
	99, 100, 101, 102, 103, 104, 10, 97,
	98, 99, 100, 101, 102, 103, 104, 10,
	97, 98, 99, 100, 101, 102, 103, 104,
	10, 97, 98, 99, 100, 101, 102, 103,
	104, 10, 97, 98, 99, 100, 101, 102,
	103, 104, 10, 97, 98, 99, 100, 101,
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
	0, 9, 9, 9, 2, 2, 2, 2,
	2, 2, 2, 9, 2, 9, 9, 9,
	9, 9, 9, 9, 9, 9, 9, 9,
	9, 9, 9, 9, 9, 9, 9, 9,
	9, 9, 0
};

static const signed char _m_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const short _m_index_offsets[] = {
	0, 0, 10, 20, 30, 33, 36, 39,
	42, 45, 48, 51, 61, 64, 74, 84,
	94, 104, 114, 124, 134, 144, 154, 164,
	174, 184, 194, 204, 214, 224, 234, 244,
	254, 264, 0
};

static const signed char _m_cond_targs[] = {
	33, 1, 2, 18, 20, 21, 22, 23,
	24, 0, 33, 3, 2, 11, 13, 14,
	15, 16, 17, 0, 33, 3, 4, 5,
	6, 7, 8, 9, 10, 0, 33, 4,
	0, 33, 5, 0, 33, 6, 0, 33,
	7, 0, 33, 8, 0, 33, 9, 0,
	33, 10, 0, 33, 12, 4, 11, 6,
	7, 8, 9, 10, 0, 33, 12, 0,
	33, 12, 4, 5, 13, 7, 8, 9,
	10, 0, 33, 12, 4, 5, 6, 14,
	8, 9, 10, 0, 33, 12, 4, 5,
	6, 7, 15, 9, 10, 0, 33, 12,
	4, 5, 6, 7, 8, 16, 10, 0,
	33, 12, 4, 5, 6, 7, 8, 9,
	17, 0, 33, 3, 19, 18, 13, 14,
	15, 16, 17, 0, 33, 12, 19, 5,
	6, 7, 8, 9, 10, 0, 33, 3,
	19, 11, 20, 14, 15, 16, 17, 0,
	33, 3, 19, 11, 13, 21, 15, 16,
	17, 0, 33, 3, 19, 11, 13, 14,
	22, 16, 17, 0, 33, 3, 19, 11,
	13, 14, 15, 23, 17, 0, 33, 3,
	19, 11, 13, 14, 15, 16, 24, 0,
	33, 26, 25, 18, 20, 21, 22, 23,
	24, 0, 33, 26, 19, 11, 13, 14,
	15, 16, 17, 0, 33, 26, 2, 27,
	20, 21, 22, 23, 24, 0, 33, 26,
	2, 18, 28, 21, 22, 23, 24, 0,
	33, 26, 2, 18, 20, 29, 22, 23,
	24, 0, 33, 26, 2, 18, 20, 21,
	30, 23, 24, 0, 33, 26, 2, 18,
	20, 21, 22, 31, 24, 0, 33, 26,
	2, 18, 20, 21, 22, 23, 32, 0,
	33, 1, 25, 27, 28, 29, 30, 31,
	32, 0, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 10, 11, 12, 13,
	14, 15, 16, 17, 18, 19, 20, 21,
	22, 23, 24, 25, 26, 27, 28, 29,
	30, 31, 32, 33, 0
};

static const short _m_cond_actions[] = {
	1, 0, 2, 3, 4, 5, 6, 7,
	8, 0, 9, 10, 0, 11, 12, 13,
	14, 15, 16, 0, 17, 0, 18, 19,
	20, 21, 22, 23, 24, 0, 25, 0,
	0, 26, 0, 0, 27, 0, 0, 28,
	0, 0, 29, 0, 0, 30, 0, 0,
	31, 0, 0, 32, 33, 34, 0, 35,
	36, 37, 38, 39, 0, 40, 0, 0,
	41, 42, 43, 44, 0, 45, 46, 47,
	48, 0, 49, 50, 51, 52, 53, 0,
	54, 55, 56, 0, 57, 58, 59, 60,
	61, 62, 0, 63, 64, 0, 65, 66,
	67, 68, 69, 70, 71, 0, 72, 0,
	73, 74, 75, 76, 77, 78, 79, 80,
	0, 0, 81, 82, 83, 0, 84, 85,
	86, 87, 88, 0, 89, 90, 0, 91,
	92, 93, 94, 95, 96, 0, 97, 98,
	99, 100, 0, 101, 102, 103, 104, 0,
	105, 106, 107, 108, 109, 0, 110, 111,
	112, 0, 113, 114, 115, 116, 117, 118,
	0, 119, 120, 0, 121, 122, 123, 124,
	125, 126, 127, 0, 128, 0, 129, 130,
	131, 132, 133, 134, 135, 136, 0, 0,
	137, 138, 0, 139, 140, 141, 142, 143,
	144, 0, 145, 0, 146, 147, 148, 149,
	150, 151, 152, 0, 153, 154, 155, 0,
	156, 157, 158, 159, 160, 0, 161, 162,
	163, 164, 0, 165, 166, 167, 168, 0,
	169, 170, 171, 172, 173, 0, 174, 175,
	176, 0, 177, 178, 179, 180, 181, 182,
	0, 183, 184, 0, 185, 186, 187, 188,
	189, 190, 191, 0, 192, 0, 193, 194,
	195, 196, 197, 198, 199, 200, 0, 0,
	201, 202, 203, 204, 205, 206, 207, 208,
	209, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
};

static const int m_start = 33;
static const int m_first_final = 33;
static const int m_error = 0;

static const int m_en_main = 33;


#line 98 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1, *c1, *d1, *e1, *f1, *g1, *h1,
	*a2, *b2, *c2, *d2, *e2, *f2, *g2, *h2,
	*a3, *b3, *c3, *d3, *e3, *f3, *g3, *h3,
	*a4, *b4, *c4, *d4, *e4, *f4, *g4, *h4,
	*a5, *b5, *c5, *d5, *e5, *f5, *g5, *h5,
	*a6, *b6, *c6, *d6, *e6, *f6, *g6, *h6,
	*a7, *b7, *c7, *d7, *e7, *f7, *g7, *h7,
	*a8, *b8, *c8, *d8, *e8, *f8, *g8, *h8;
	int cs;
	
	
#line 190 "gen/ragel/alt4_8-T1.c"
	{
		cs = (int)m_start;
	}
	
#line 115 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
	
	
#line 198 "gen/ragel/alt4_8-T1.c"
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
				case 203:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b1 = p; }
					
#line 267 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 204:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c1 = p; }
					
#line 277 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 205:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d1 = p; }
					
#line 287 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 206:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e1 = p; }
					
#line 297 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 207:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f1 = p; }
					
#line 307 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 208:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g1 = p; }
					
#line 317 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 209:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h1 = p; }
					
#line 327 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 202:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a1 = p; }
					
#line 337 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 139:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 347 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 353 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 140:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 363 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 369 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 141:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 379 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 385 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 142:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 395 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 401 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 143:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 411 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 417 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 144:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 427 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 433 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 138:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 443 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 449 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 155:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 459 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 465 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 156:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 475 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 481 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 157:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 491 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 497 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 158:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 507 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 513 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 159:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 523 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 529 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 160:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 539 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 545 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 154:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 555 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 561 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 163:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 571 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 577 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 164:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 587 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 593 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 165:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 603 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 609 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 166:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 619 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 625 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 167:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 635 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 641 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 168:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 651 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 657 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 162:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 667 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 673 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 171:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 683 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 689 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 172:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 699 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 705 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 173:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 715 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 721 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 174:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 731 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 737 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 175:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 747 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 753 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 176:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 763 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 769 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 170:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 779 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 785 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 179:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 795 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 801 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 180:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 811 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 817 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 181:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 827 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 833 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 182:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 843 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 849 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 183:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 859 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 865 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 184:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 875 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 881 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 178:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 891 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 897 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 187:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 907 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 913 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 188:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 923 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 929 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 189:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 939 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 945 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 190:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 955 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 961 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 191:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 971 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 977 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 192:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 987 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 993 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 186:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 1003 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 1009 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 195:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1019 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 1025 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 196:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1035 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 1041 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 197:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1051 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 1057 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 198:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1067 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 1073 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 199:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1083 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 1089 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 200:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1099 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 1105 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 194:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1115 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 1121 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1131 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 1137 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1147 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 1153 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1163 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 1169 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1179 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 1185 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1195 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 1201 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1211 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 1217 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1227 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 1233 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1243 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 1249 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1259 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 1265 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1275 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 1281 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1291 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 1297 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1307 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 1313 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1323 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 1329 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1339 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 1345 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 83:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1355 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 1361 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 84:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1371 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 1377 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 85:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1387 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 1393 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 86:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1403 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 1409 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 87:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1419 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 1425 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 88:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1435 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 1441 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 82:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1451 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 1457 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 99:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1467 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 1473 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 100:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1483 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 1489 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 101:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1499 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 1505 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 102:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1515 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 1521 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 103:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1531 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 1537 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 104:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1547 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 1553 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 98:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1563 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 1569 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 107:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1579 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 1585 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 108:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1595 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 1601 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 109:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1611 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 1617 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 110:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1627 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 1633 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 111:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1643 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 1649 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 112:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1659 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 1665 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 106:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1675 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 1681 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 115:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1691 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 1697 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 116:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1707 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 1713 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 117:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1723 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 1729 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 118:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1739 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 1745 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 119:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1755 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 1761 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 120:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1771 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 1777 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 114:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1787 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 1793 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 123:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1803 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 1809 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 124:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1819 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 1825 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 125:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1835 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 1841 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 126:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1851 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 1857 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 127:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1867 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 1873 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 128:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1883 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 1889 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 122:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1899 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 1905 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 131:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1915 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 1921 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 132:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1931 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 1937 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 133:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1947 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 1953 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 134:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1963 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 1969 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 135:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1979 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 1985 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 136:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1995 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 2001 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 130:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 2011 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 2017 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 146:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2027 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 2033 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 147:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2043 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 2049 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 148:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2059 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 2065 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 149:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2075 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 2081 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 150:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2091 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 2097 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 151:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2107 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 2113 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 152:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2123 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 2129 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 91:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2139 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 2145 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 92:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2155 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 2161 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 93:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2171 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 2177 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 94:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2187 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 2193 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 95:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2203 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 2209 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 96:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2219 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 2225 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 90:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2235 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 2241 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 34:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2251 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 2257 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 35:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2267 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 2273 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 36:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2283 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 2289 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 37:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2299 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 2305 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 38:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2315 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 2321 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 39:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2331 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 2337 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 33:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2347 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 2353 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 43:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2363 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 2369 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 44:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2379 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 2385 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 45:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2395 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 2401 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 46:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2411 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 2417 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 47:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2427 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 2433 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 48:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2443 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 2449 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 42:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2459 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 2465 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 51:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2475 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 2481 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 52:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2491 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 2497 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 53:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2507 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 2513 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 54:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2523 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 2529 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 55:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2539 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 2545 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 56:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2555 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 2561 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 50:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2571 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 2577 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 59:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2587 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 2593 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 60:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2603 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 2609 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 61:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2619 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 2625 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 62:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2635 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 2641 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 63:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2651 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 2657 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 64:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2667 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 2673 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 58:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2683 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 2689 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 67:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 2699 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 2705 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 68:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 2715 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 2721 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 69:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 2731 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 2737 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 70:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 2747 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 2753 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 71:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 2763 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 2769 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 72:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 2779 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 2785 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 66:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 2795 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 2801 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 75:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 2811 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 2817 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 76:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 2827 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 2833 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 77:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 2843 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 2849 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 78:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 2859 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 2865 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 79:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 2875 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 2881 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 80:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 2891 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 2897 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 74:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 2907 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 2913 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2923 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 2929 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2939 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 2945 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2955 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 2961 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2971 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 2977 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2987 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 2993 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 3003 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 3009 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 3019 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 3025 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3035 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 3075 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 26:  {
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3085 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 3125 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 27:  {
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3135 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 3175 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 28:  {
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3185 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 3225 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 29:  {
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3235 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 3275 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 30:  {
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 3285 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 3325 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 31:  {
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 3335 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 3375 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 40:  {
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3385 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 3425 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 89:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 3435 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 3441 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3447 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 3453 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3459 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 3465 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3471 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 3477 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3483 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 3489 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3495 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 3501 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 3507 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 3513 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 3519 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 3525 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3531 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 3571 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 32:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 3581 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 3587 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3593 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 3599 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3605 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 3611 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3617 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 3623 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3629 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 3635 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3641 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 3647 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 3653 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 3659 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 3665 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 3671 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3677 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 3717 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 41:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 3727 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 3733 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3739 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 3745 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3751 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 3757 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3763 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 3769 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3775 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 3781 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3787 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 3793 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 3799 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 3805 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 3811 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 3817 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3823 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 3863 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 49:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 3873 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 3879 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3885 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 3891 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3897 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 3903 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3909 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 3915 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3921 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 3927 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3933 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 3939 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 3945 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 3951 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 3957 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 3963 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3969 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 4009 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 57:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4019 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 4025 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4031 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 4037 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4043 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 4049 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4055 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 4061 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4067 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 4073 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4079 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 4085 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 4091 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 4097 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 4103 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 4109 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4115 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 4155 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 65:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 4165 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 4171 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4177 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 4183 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4189 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 4195 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4201 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 4207 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4213 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 4219 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4225 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 4231 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 4237 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 4243 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 4249 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 4255 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4261 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 4301 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 73:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 4311 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 4317 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4323 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 4329 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4335 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 4341 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4347 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 4353 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4359 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 4365 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4371 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 4377 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 4383 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 4389 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 4395 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 4401 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4407 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 4447 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4457 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 4463 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4469 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 4475 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4481 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 4487 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4493 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 4499 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4505 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 4511 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4517 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 4523 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 4529 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 4535 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 4541 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 4547 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4553 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 4593 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 4603 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 4609 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4615 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 4621 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4627 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 4633 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4639 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 4645 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4651 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 4657 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4663 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 4669 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 4675 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 4681 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 4687 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 4693 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4699 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 4705 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4711 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 4717 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4723 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 4729 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4735 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 4741 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4747 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 4753 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4759 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 4765 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 4771 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 4777 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 4783 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 4789 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4795 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 4835 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 81:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 4845 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 4851 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4857 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 4863 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4869 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 4875 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4881 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 4887 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4893 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 4899 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4905 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 4911 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 4917 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 4923 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 4929 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 4935 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4941 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 4947 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4953 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 4959 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4965 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 4971 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4977 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 4983 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4989 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 4995 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5001 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 5007 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 5013 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 5019 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 5025 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 5031 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5037 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 5077 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 97:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 5087 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 5093 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5099 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 5105 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5111 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 5117 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5123 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 5129 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5135 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 5141 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5147 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 5153 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 5159 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 5165 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 5171 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 5177 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5183 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 5189 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5195 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 5201 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5207 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 5213 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5219 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 5225 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5231 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 5237 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5243 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 5249 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 5255 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 5261 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 5267 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 5273 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5279 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 5319 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 105:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 5329 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 5335 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5341 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 5347 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5353 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 5359 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5365 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 5371 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5377 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 5383 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5389 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 5395 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 5401 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 5407 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 5413 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 5419 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5425 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 5431 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5437 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 5443 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5449 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 5455 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5461 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 5467 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5473 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 5479 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5485 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 5491 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 5497 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 5503 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 5509 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 5515 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5521 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 5561 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 113:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 5571 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 5577 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5583 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 5589 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5595 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 5601 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5607 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 5613 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5619 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 5625 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5631 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 5637 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 5643 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 5649 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 5655 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 5661 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5667 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 5673 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5679 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 5685 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5691 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 5697 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5703 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 5709 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5715 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 5721 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5727 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 5733 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 5739 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 5745 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 5751 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 5757 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5763 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 5803 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 121:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 5813 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 5819 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5825 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 5831 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5837 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 5843 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5849 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 5855 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5861 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 5867 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5873 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 5879 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 5885 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 5891 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 5897 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 5903 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5909 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 5915 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5921 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 5927 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5933 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 5939 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5945 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 5951 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5957 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 5963 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5969 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 5975 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 5981 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 5987 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 5993 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 5999 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6005 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 6045 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 129:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 6055 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 6061 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6067 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 6073 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6079 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 6085 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6091 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 6097 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6103 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 6109 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6115 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 6121 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 6127 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 6133 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 6139 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 6145 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6151 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 6157 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6163 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 6169 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6175 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 6181 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6187 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 6193 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6199 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 6205 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6211 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 6217 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 6223 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 6229 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 6235 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 6241 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6247 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 6287 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 145:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6297 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 6303 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6309 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 6315 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6321 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 6327 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6333 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 6339 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6345 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 6351 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6357 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 6363 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 6369 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 6375 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 6381 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 6387 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6393 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 6399 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6405 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 6411 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6417 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 6423 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6429 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 6435 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6441 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 6447 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6453 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 6459 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 6465 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 6471 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 6477 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 6483 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6489 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 6529 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 137:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 6539 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 6545 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6551 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 6557 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6563 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 6569 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6575 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 6581 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6587 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 6593 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6599 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 6605 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 6611 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 6617 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 6623 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 6629 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6635 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 6641 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6647 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 6653 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6659 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 6665 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6671 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 6677 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6683 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 6689 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6695 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 6701 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 6707 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 6713 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 6719 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 6725 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6731 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 6737 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6743 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 6749 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6755 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 6761 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6767 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 6773 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6779 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 6785 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6791 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 6797 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 6803 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 6809 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 6815 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 6821 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6827 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 6867 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 153:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 6877 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 6883 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6889 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 6895 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6901 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 6907 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6913 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 6919 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6925 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 6931 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6937 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 6943 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 6949 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 6955 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 6961 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 6967 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6973 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 6979 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6985 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 6991 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6997 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 7003 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7009 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 7015 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7021 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 7027 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7033 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 7039 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 7045 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 7051 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 7057 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 7063 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7069 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 7075 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7081 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 7087 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7093 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 7099 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7105 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 7111 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7117 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 7123 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7129 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 7135 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 7141 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 7147 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 7153 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 7159 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7165 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 7205 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 161:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 7215 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 7221 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7227 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 7233 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7239 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 7245 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7251 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 7257 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7263 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 7269 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7275 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 7281 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 7287 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 7293 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 7299 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 7305 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7311 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 7317 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7323 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 7329 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7335 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 7341 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7347 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 7353 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7359 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 7365 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7371 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 7377 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 7383 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 7389 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 7395 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 7401 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7407 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 7413 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7419 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 7425 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7431 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 7437 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7443 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 7449 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7455 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 7461 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7467 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 7473 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 7479 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 7485 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 7491 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 7497 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7503 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 7543 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 169:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 7553 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 7559 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7565 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 7571 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7577 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 7583 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7589 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 7595 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7601 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 7607 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7613 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 7619 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 7625 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 7631 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 7637 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 7643 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7649 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 7655 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7661 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 7667 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7673 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 7679 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7685 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 7691 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7697 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 7703 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7709 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 7715 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 7721 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 7727 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 7733 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 7739 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7745 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 7751 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7757 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 7763 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7769 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 7775 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7781 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 7787 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7793 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 7799 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7805 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 7811 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 7817 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 7823 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 7829 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 7835 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7841 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 7881 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 177:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 7891 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 7897 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7903 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 7909 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7915 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 7921 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7927 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 7933 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7939 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 7945 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7951 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 7957 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 7963 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 7969 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 7975 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 7981 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7987 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 7993 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7999 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 8005 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8011 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 8017 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8023 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 8029 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8035 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 8041 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8047 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 8053 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 8059 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 8065 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 8071 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 8077 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8083 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 8089 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8095 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 8101 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8107 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 8113 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8119 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 8125 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8131 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 8137 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8143 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 8149 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 8155 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 8161 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 8167 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 8173 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8179 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 8219 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 185:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 8229 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 8235 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8241 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 8247 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8253 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 8259 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8265 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 8271 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8277 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 8283 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8289 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 8295 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 8301 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 8307 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 8313 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 8319 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8325 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 8331 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8337 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 8343 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8349 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 8355 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8361 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 8367 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8373 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 8379 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8385 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 8391 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 8397 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 8403 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 8409 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 8415 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8421 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 8427 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8433 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 8439 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8445 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 8451 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8457 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 8463 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8469 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 8475 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8481 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 8487 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 8493 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 8499 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 8505 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 8511 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8517 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 8557 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 193:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 8567 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 8573 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8579 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 8585 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8591 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 8597 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8603 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 8609 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8615 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 8621 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8627 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 8633 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 8639 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 8645 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 8651 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 8657 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8663 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 8669 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8675 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 8681 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8687 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 8693 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8699 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 8705 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8711 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 8717 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8723 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 8729 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 8735 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 8741 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 8747 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 8753 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8759 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 8765 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8771 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 8777 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8783 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 8789 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8795 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 8801 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8807 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 8813 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8819 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 8825 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 8831 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 8837 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 8843 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 8849 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8855 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 8895 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 8905 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 8911 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8917 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 8923 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8929 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 8935 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8941 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 8947 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8953 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 8959 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8965 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 8971 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 8977 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 8983 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 8989 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 8995 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 9001 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 9007 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9013 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 9019 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9025 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 9031 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9037 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 9043 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9049 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 9055 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9061 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 9067 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 9073 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 9079 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 9085 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 9091 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9097 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 9103 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9109 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 9115 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9121 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 9127 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9133 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 9139 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9145 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 9151 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9157 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 9163 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 9169 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 9175 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 9181 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 9187 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9193 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 9233 "gen/ragel/alt4_8-T1.c"
					
					
					break; 
				}
				case 201:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b1 = p; }
					
#line 9243 "gen/ragel/alt4_8-T1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 9249 "gen/ragel/alt4_8-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c1 = p; }
					
#line 9255 "gen/ragel/alt4_8-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 9261 "gen/ragel/alt4_8-T1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d1 = p; }
					
#line 9267 "gen/ragel/alt4_8-T1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 9273 "gen/ragel/alt4_8-T1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e1 = p; }
					
#line 9279 "gen/ragel/alt4_8-T1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 9285 "gen/ragel/alt4_8-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f1 = p; }
					
#line 9291 "gen/ragel/alt4_8-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 9297 "gen/ragel/alt4_8-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g1 = p; }
					
#line 9303 "gen/ragel/alt4_8-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 9309 "gen/ragel/alt4_8-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h1 = p; }
					
#line 9315 "gen/ragel/alt4_8-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 9321 "gen/ragel/alt4_8-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a1 = p; }
					
#line 9327 "gen/ragel/alt4_8-T1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 9333 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 9339 "gen/ragel/alt4_8-T1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 9345 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 9351 "gen/ragel/alt4_8-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 9357 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 9363 "gen/ragel/alt4_8-T1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 9369 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 9375 "gen/ragel/alt4_8-T1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 9381 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 9387 "gen/ragel/alt4_8-T1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 9393 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 9399 "gen/ragel/alt4_8-T1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 9405 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 9411 "gen/ragel/alt4_8-T1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 9417 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 9423 "gen/ragel/alt4_8-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 9429 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 9435 "gen/ragel/alt4_8-T1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9441 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 9447 "gen/ragel/alt4_8-T1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9453 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 9459 "gen/ragel/alt4_8-T1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9465 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 9471 "gen/ragel/alt4_8-T1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9477 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 9483 "gen/ragel/alt4_8-T1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9489 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 9495 "gen/ragel/alt4_8-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 9501 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 9507 "gen/ragel/alt4_8-T1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 9513 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 9519 "gen/ragel/alt4_8-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9525 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 9531 "gen/ragel/alt4_8-T1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9537 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 9543 "gen/ragel/alt4_8-T1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9549 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 9555 "gen/ragel/alt4_8-T1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9561 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 9567 "gen/ragel/alt4_8-T1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9573 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 9579 "gen/ragel/alt4_8-T1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9585 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 9591 "gen/ragel/alt4_8-T1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 9597 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 9603 "gen/ragel/alt4_8-T1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 9609 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 9615 "gen/ragel/alt4_8-T1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9621 "gen/ragel/alt4_8-T1.c"
					
					{
#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						
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
						if (a6)      { outc(out, 'A'); outs(out, a5, a6); }
						else if (b6) { outc(out, 'B'); outs(out, b5, b6); }
						else if (c6) { outc(out, 'C'); outs(out, c5, c6); }
						else if (d6) { outc(out, 'D'); outs(out, d5, d6); }
						else if (e6) { outc(out, 'E'); outs(out, e5, e6); }
						else if (f6) { outc(out, 'F'); outs(out, f5, f6); }
						else if (g6) { outc(out, 'G'); outs(out, g5, g6); }
						else if (h6) { outc(out, 'H'); outs(out, h5, h6); }
						if (a8)      { outc(out, 'A'); outs(out, a7, a8); }
						else if (b8) { outc(out, 'B'); outs(out, b7, b8); }
						else if (c8) { outc(out, 'C'); outs(out, c7, c8); }
						else if (d8) { outc(out, 'D'); outs(out, d7, d8); }
						else if (e8) { outc(out, 'E'); outs(out, e7, e8); }
						else if (f8) { outc(out, 'F'); outs(out, f7, f8); }
						else if (g8) { outc(out, 'G'); outs(out, g7, g8); }
						else if (h8) { outc(out, 'H'); outs(out, h7, h8); }
						outc(out, '\n');
					}
					
#line 9661 "gen/ragel/alt4_8-T1.c"
					
					
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
	
#line 116 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
	
	
	in->p = p;
	in->pe = pe;
}
