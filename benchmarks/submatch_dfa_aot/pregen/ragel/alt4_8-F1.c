#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 96 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"



#line 13 "gen/ragel/alt4_8-F1.c"
static const char _m_trans_keys[] = {
	1, 0, 0, 9, 0, 9, 0, 9,
	0, 3, 0, 4, 0, 5, 0, 6,
	0, 7, 0, 8, 0, 9, 0, 9,
	0, 2, 0, 9, 0, 9, 0, 9,
	0, 9, 0, 9, 0, 9, 0, 9,
	0, 9, 0, 9, 0, 9, 0, 9,
	0, 9, 0, 9, 0, 9, 0, 9,
	0, 9, 0, 9, 0, 9, 0, 9,
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

static const short _m_index_offsets[] = {
	0, 0, 10, 20, 30, 34, 39, 45,
	52, 60, 69, 79, 89, 92, 102, 112,
	122, 132, 142, 152, 162, 172, 182, 192,
	202, 212, 222, 232, 242, 252, 262, 272,
	282, 292, 0
};

static const short _m_indicies[] = {
	2, 0, 1, 3, 4, 5, 6, 7,
	8, 9, 11, 0, 12, 10, 13, 14,
	15, 16, 17, 18, 20, 0, 19, 21,
	22, 23, 24, 25, 26, 27, 29, 0,
	0, 28, 31, 0, 0, 0, 30, 33,
	0, 0, 0, 0, 32, 35, 0, 0,
	0, 0, 0, 34, 37, 0, 0, 0,
	0, 0, 0, 36, 39, 0, 0, 0,
	0, 0, 0, 0, 38, 41, 0, 0,
	0, 0, 0, 0, 0, 0, 40, 43,
	0, 44, 45, 42, 46, 47, 48, 49,
	50, 52, 0, 51, 54, 0, 55, 56,
	57, 53, 58, 59, 60, 61, 63, 0,
	64, 65, 66, 67, 62, 68, 69, 70,
	72, 0, 73, 74, 75, 76, 77, 71,
	78, 79, 81, 0, 82, 83, 84, 85,
	86, 87, 80, 88, 90, 0, 91, 92,
	93, 94, 95, 96, 97, 89, 99, 0,
	100, 101, 98, 102, 103, 104, 105, 106,
	108, 0, 109, 107, 110, 111, 112, 113,
	114, 115, 117, 0, 118, 119, 120, 116,
	121, 122, 123, 124, 126, 0, 127, 128,
	129, 130, 125, 131, 132, 133, 135, 0,
	136, 137, 138, 139, 140, 134, 141, 142,
	144, 0, 145, 146, 147, 148, 149, 150,
	143, 151, 153, 0, 154, 155, 156, 157,
	158, 159, 160, 152, 162, 0, 163, 161,
	164, 165, 166, 167, 168, 169, 171, 0,
	170, 172, 173, 174, 175, 176, 177, 178,
	180, 0, 181, 182, 179, 183, 184, 185,
	186, 187, 189, 0, 190, 191, 192, 188,
	193, 194, 195, 196, 198, 0, 199, 200,
	201, 202, 197, 203, 204, 205, 207, 0,
	208, 209, 210, 211, 212, 206, 213, 214,
	216, 0, 217, 218, 219, 220, 221, 222,
	215, 223, 225, 0, 226, 227, 228, 229,
	230, 231, 232, 224, 234, 0, 235, 236,
	237, 238, 239, 240, 241, 242, 0
};

static const signed char _m_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _m_cond_targs[] = {
	0, 1, 33, 2, 18, 20, 21, 22,
	23, 24, 2, 33, 3, 11, 13, 14,
	15, 16, 17, 3, 33, 4, 5, 6,
	7, 8, 9, 10, 4, 33, 5, 33,
	6, 33, 7, 33, 8, 33, 9, 33,
	10, 33, 11, 33, 12, 4, 6, 7,
	8, 9, 10, 12, 33, 13, 33, 12,
	4, 5, 7, 8, 9, 10, 14, 33,
	12, 4, 5, 6, 8, 9, 10, 15,
	33, 12, 4, 5, 6, 7, 9, 10,
	16, 33, 12, 4, 5, 6, 7, 8,
	10, 17, 33, 12, 4, 5, 6, 7,
	8, 9, 18, 33, 3, 19, 13, 14,
	15, 16, 17, 19, 33, 12, 5, 6,
	7, 8, 9, 10, 20, 33, 3, 19,
	11, 14, 15, 16, 17, 21, 33, 3,
	19, 11, 13, 15, 16, 17, 22, 33,
	3, 19, 11, 13, 14, 16, 17, 23,
	33, 3, 19, 11, 13, 14, 15, 17,
	24, 33, 3, 19, 11, 13, 14, 15,
	16, 25, 33, 26, 18, 20, 21, 22,
	23, 24, 26, 33, 19, 11, 13, 14,
	15, 16, 17, 27, 33, 26, 2, 20,
	21, 22, 23, 24, 28, 33, 26, 2,
	18, 21, 22, 23, 24, 29, 33, 26,
	2, 18, 20, 22, 23, 24, 30, 33,
	26, 2, 18, 20, 21, 23, 24, 31,
	33, 26, 2, 18, 20, 21, 22, 24,
	32, 33, 26, 2, 18, 20, 21, 22,
	23, 33, 33, 1, 25, 27, 28, 29,
	30, 31, 32, 0
};

static const short _m_cond_actions[] = {
	0, 0, 1, 2, 3, 4, 5, 6,
	7, 8, 0, 9, 10, 11, 12, 13,
	14, 15, 16, 0, 17, 18, 19, 20,
	21, 22, 23, 24, 0, 25, 0, 26,
	0, 27, 0, 28, 0, 29, 0, 30,
	0, 31, 0, 32, 33, 34, 35, 36,
	37, 38, 39, 0, 40, 0, 41, 42,
	43, 44, 45, 46, 47, 48, 0, 49,
	50, 51, 52, 53, 54, 55, 56, 0,
	57, 58, 59, 60, 61, 62, 63, 64,
	0, 65, 66, 67, 68, 69, 70, 71,
	72, 0, 73, 74, 75, 76, 77, 78,
	79, 80, 0, 81, 82, 83, 84, 85,
	86, 87, 88, 0, 89, 90, 91, 92,
	93, 94, 95, 96, 0, 97, 98, 99,
	100, 101, 102, 103, 104, 0, 105, 106,
	107, 108, 109, 110, 111, 112, 0, 113,
	114, 115, 116, 117, 118, 119, 120, 0,
	121, 122, 123, 124, 125, 126, 127, 128,
	0, 129, 130, 131, 132, 133, 134, 135,
	136, 0, 137, 138, 139, 140, 141, 142,
	143, 144, 0, 145, 146, 147, 148, 149,
	150, 151, 152, 0, 153, 154, 155, 156,
	157, 158, 159, 160, 0, 161, 162, 163,
	164, 165, 166, 167, 168, 0, 169, 170,
	171, 172, 173, 174, 175, 176, 0, 177,
	178, 179, 180, 181, 182, 183, 184, 0,
	185, 186, 187, 188, 189, 190, 191, 192,
	0, 193, 194, 195, 196, 197, 198, 199,
	200, 0, 201, 202, 203, 204, 205, 206,
	207, 208, 209, 0
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
	
	
#line 192 "gen/ragel/alt4_8-F1.c"
	{
		cs = (int)m_start;
	}
	
#line 115 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
	
	
#line 200 "gen/ragel/alt4_8-F1.c"
	{
		unsigned int _trans = 0;
		const char * _keys;
		const short * _inds;
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
				case 203:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b1 = p; }
					
#line 233 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 204:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c1 = p; }
					
#line 243 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 205:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d1 = p; }
					
#line 253 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 206:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e1 = p; }
					
#line 263 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 207:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f1 = p; }
					
#line 273 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 208:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g1 = p; }
					
#line 283 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 209:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h1 = p; }
					
#line 293 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 202:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a1 = p; }
					
#line 303 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 139:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 313 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 319 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 140:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 329 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 335 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 141:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 345 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 351 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 142:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 361 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 367 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 143:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 377 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 383 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 144:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 393 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 399 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 138:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 409 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 415 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 155:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 425 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 431 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 156:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 441 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 447 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 157:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 457 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 463 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 158:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 473 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 479 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 159:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 489 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 495 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 160:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 505 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 511 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 154:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 521 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 527 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 163:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 537 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 543 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 164:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 553 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 559 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 165:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 569 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 575 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 166:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 585 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 591 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 167:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 601 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 607 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 168:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 617 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 623 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 162:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 633 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 639 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 171:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 649 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 655 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 172:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 665 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 671 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 173:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 681 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 687 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 174:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 697 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 703 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 175:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 713 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 719 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 176:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 729 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 735 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 170:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 745 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 751 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 179:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 761 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 767 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 180:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 777 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 783 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 181:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 793 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 799 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 182:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 809 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 815 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 183:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 825 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 831 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 184:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 841 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 847 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 178:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 857 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 863 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 187:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 873 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 879 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 188:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 889 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 895 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 189:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 905 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 911 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 190:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 921 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 927 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 191:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 937 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 943 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 192:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 953 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 959 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 186:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 969 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 975 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 195:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 985 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 991 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 196:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1001 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 1007 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 197:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1017 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 1023 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 198:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1033 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 1039 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 199:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1049 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 1055 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 200:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1065 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 1071 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 194:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1081 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 1087 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1097 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 1103 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1113 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 1119 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1129 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 1135 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1145 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 1151 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1161 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 1167 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1177 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 1183 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1193 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 1199 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1209 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 1215 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1225 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 1231 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1241 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 1247 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1257 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 1263 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1273 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 1279 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1289 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 1295 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1305 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 1311 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 83:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1321 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 1327 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 84:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1337 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 1343 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 85:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1353 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 1359 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 86:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1369 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 1375 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 87:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1385 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 1391 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 88:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1401 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 1407 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 82:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1417 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 1423 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 99:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1433 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 1439 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 100:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1449 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 1455 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 101:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1465 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 1471 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 102:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1481 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 1487 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 103:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1497 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 1503 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 104:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1513 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 1519 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 98:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1529 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 1535 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 107:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1545 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 1551 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 108:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1561 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 1567 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 109:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1577 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 1583 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 110:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1593 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 1599 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 111:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1609 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 1615 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 112:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1625 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 1631 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 106:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1641 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 1647 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 115:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1657 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 1663 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 116:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1673 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 1679 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 117:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1689 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 1695 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 118:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1705 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 1711 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 119:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1721 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 1727 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 120:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1737 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 1743 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 114:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1753 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 1759 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 123:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1769 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 1775 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 124:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1785 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 1791 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 125:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1801 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 1807 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 126:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1817 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 1823 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 127:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1833 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 1839 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 128:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1849 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 1855 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 122:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1865 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 1871 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 131:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1881 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 1887 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 132:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1897 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 1903 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 133:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1913 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 1919 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 134:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1929 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 1935 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 135:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1945 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 1951 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 136:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1961 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 1967 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 130:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1977 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 1983 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 146:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1993 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 1999 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 147:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2009 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 2015 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 148:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2025 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 2031 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 149:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2041 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 2047 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 150:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2057 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 2063 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 151:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2073 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 2079 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 152:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2089 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 2095 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 91:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2105 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 2111 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 92:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2121 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 2127 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 93:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2137 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 2143 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 94:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2153 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 2159 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 95:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2169 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 2175 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 96:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2185 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 2191 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 90:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2201 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 2207 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 34:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2217 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 2223 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 35:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2233 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 2239 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 36:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2249 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 2255 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 37:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2265 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 2271 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 38:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2281 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 2287 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 39:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2297 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 2303 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 33:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2313 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 2319 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 43:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2329 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 2335 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 44:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2345 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 2351 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 45:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2361 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 2367 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 46:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2377 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 2383 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 47:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2393 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 2399 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 48:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2409 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 2415 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 42:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2425 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 2431 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 51:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2441 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 2447 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 52:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2457 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 2463 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 53:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2473 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 2479 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 54:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2489 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 2495 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 55:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2505 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 2511 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 56:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2521 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 2527 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 50:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2537 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 2543 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 59:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2553 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 2559 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 60:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2569 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 2575 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 61:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2585 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 2591 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 62:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2601 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 2607 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 63:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2617 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 2623 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 64:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2633 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 2639 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 58:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2649 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 2655 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 67:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 2665 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 2671 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 68:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 2681 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 2687 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 69:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 2697 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 2703 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 70:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 2713 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 2719 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 71:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 2729 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 2735 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 72:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 2745 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 2751 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 66:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 2761 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 2767 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 75:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 2777 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 2783 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 76:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 2793 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 2799 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 77:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 2809 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 2815 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 78:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 2825 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 2831 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 79:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 2841 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 2847 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 80:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 2857 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 2863 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 74:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 2873 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 2879 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2889 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 2895 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2905 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 2911 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2921 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 2927 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2937 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 2943 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2953 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 2959 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2969 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 2975 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 2985 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 2991 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3001 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 3041 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 26:  {
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3051 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 3091 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 27:  {
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3101 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 3141 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 28:  {
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3151 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 3191 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 29:  {
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3201 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 3241 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 30:  {
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 3251 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 3291 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 31:  {
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 3301 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 3341 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 40:  {
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3351 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 3391 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 89:  {
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 3401 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 3407 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3413 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 3419 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3425 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 3431 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3437 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 3443 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3449 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 3455 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3461 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 3467 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 3473 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 3479 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 3485 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 3491 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3497 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 3537 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 32:  {
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 3547 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 3553 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3559 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 3565 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3571 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 3577 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3583 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 3589 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3595 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 3601 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3607 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 3613 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 3619 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 3625 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 3631 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 3637 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3643 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 3683 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 41:  {
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 3693 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 3699 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3705 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 3711 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3717 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 3723 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3729 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 3735 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3741 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 3747 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3753 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 3759 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 3765 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 3771 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 3777 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 3783 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3789 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 3829 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 49:  {
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 3839 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 3845 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3851 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 3857 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3863 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 3869 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3875 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 3881 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3887 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 3893 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3899 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 3905 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 3911 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 3917 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 3923 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 3929 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3935 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 3975 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 57:  {
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 3985 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 3991 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 3997 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 4003 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4009 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 4015 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4021 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 4027 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4033 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 4039 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4045 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 4051 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 4057 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 4063 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 4069 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 4075 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4081 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 4121 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 65:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 4131 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 4137 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4143 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 4149 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4155 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 4161 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4167 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 4173 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4179 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 4185 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4191 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 4197 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 4203 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 4209 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 4215 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 4221 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4227 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 4267 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 73:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 4277 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 4283 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4289 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 4295 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4301 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 4307 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4313 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 4319 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4325 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 4331 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4337 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 4343 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 4349 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 4355 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 4361 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 4367 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4373 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 4413 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4423 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 4429 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4435 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 4441 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4447 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 4453 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4459 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 4465 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4471 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 4477 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4483 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 4489 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 4495 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 4501 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 4507 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 4513 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4519 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 4559 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 4569 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 4575 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4581 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 4587 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4593 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 4599 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4605 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 4611 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4617 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 4623 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4629 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 4635 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 4641 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 4647 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 4653 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 4659 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4665 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 4671 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4677 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 4683 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4689 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 4695 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4701 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 4707 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4713 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 4719 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4725 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 4731 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 4737 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 4743 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 4749 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 4755 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4761 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 4801 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 81:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 4811 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 4817 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4823 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 4829 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4835 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 4841 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4847 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 4853 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4859 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 4865 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4871 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 4877 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 4883 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 4889 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 4895 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 4901 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 4907 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 4913 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4919 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 4925 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4931 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 4937 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4943 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 4949 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4955 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 4961 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 4967 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 4973 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 4979 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 4985 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 4991 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 4997 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5003 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 5043 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 97:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 5053 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 5059 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5065 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 5071 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5077 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 5083 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5089 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 5095 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5101 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 5107 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5113 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 5119 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 5125 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 5131 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 5137 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 5143 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5149 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 5155 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5161 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 5167 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5173 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 5179 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5185 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 5191 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5197 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 5203 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5209 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 5215 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 5221 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 5227 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 5233 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 5239 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5245 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 5285 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 105:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 5295 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 5301 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5307 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 5313 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5319 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 5325 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5331 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 5337 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5343 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 5349 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5355 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 5361 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 5367 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 5373 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 5379 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 5385 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5391 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 5397 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5403 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 5409 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5415 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 5421 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5427 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 5433 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5439 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 5445 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5451 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 5457 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 5463 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 5469 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 5475 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 5481 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5487 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 5527 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 113:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 5537 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 5543 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5549 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 5555 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5561 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 5567 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5573 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 5579 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5585 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 5591 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5597 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 5603 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 5609 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 5615 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 5621 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 5627 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5633 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 5639 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5645 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 5651 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5657 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 5663 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5669 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 5675 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5681 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 5687 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5693 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 5699 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 5705 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 5711 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 5717 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 5723 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5729 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 5769 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 121:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 5779 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 5785 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5791 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 5797 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5803 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 5809 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5815 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 5821 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5827 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 5833 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5839 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 5845 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 5851 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 5857 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 5863 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 5869 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 5875 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 5881 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5887 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 5893 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5899 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 5905 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5911 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 5917 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5923 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 5929 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5935 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 5941 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 5947 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 5953 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 5959 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 5965 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 5971 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 6011 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 129:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 6021 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 6027 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6033 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 6039 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6045 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 6051 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6057 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 6063 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6069 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 6075 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6081 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 6087 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 6093 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 6099 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 6105 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 6111 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6117 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 6123 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6129 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 6135 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6141 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 6147 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6153 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 6159 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6165 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 6171 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6177 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 6183 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 6189 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 6195 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 6201 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 6207 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6213 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 6253 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 145:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6263 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 6269 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6275 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 6281 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6287 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 6293 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6299 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 6305 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6311 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 6317 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6323 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 6329 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 6335 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 6341 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 6347 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 6353 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6359 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 6365 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6371 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 6377 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6383 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 6389 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6395 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 6401 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6407 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 6413 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6419 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 6425 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 6431 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 6437 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 6443 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 6449 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6455 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 6495 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 137:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 6505 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 6511 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6517 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 6523 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6529 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 6535 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6541 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 6547 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6553 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 6559 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6565 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 6571 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 6577 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 6583 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 6589 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 6595 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6601 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 6607 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6613 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 6619 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6625 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 6631 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6637 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 6643 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6649 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 6655 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6661 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 6667 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 6673 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 6679 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 6685 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 6691 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6697 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 6703 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6709 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 6715 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6721 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 6727 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6733 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 6739 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6745 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 6751 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6757 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 6763 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 6769 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 6775 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 6781 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 6787 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 6793 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 6833 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 153:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 6843 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 6849 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6855 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 6861 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6867 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 6873 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6879 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 6885 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6891 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 6897 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6903 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 6909 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 6915 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 6921 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 6927 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 6933 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 6939 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 6945 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6951 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 6957 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6963 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 6969 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6975 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 6981 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6987 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 6993 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 6999 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 7005 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 7011 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 7017 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 7023 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 7029 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7035 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 7041 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7047 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 7053 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7059 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 7065 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7071 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 7077 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7083 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 7089 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7095 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 7101 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 7107 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 7113 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 7119 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 7125 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7131 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 7171 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 161:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 7181 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 7187 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7193 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 7199 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7205 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 7211 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7217 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 7223 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7229 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 7235 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7241 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 7247 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 7253 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 7259 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 7265 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 7271 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7277 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 7283 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7289 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 7295 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7301 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 7307 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7313 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 7319 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7325 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 7331 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7337 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 7343 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 7349 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 7355 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 7361 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 7367 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7373 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 7379 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7385 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 7391 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7397 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 7403 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7409 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 7415 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7421 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 7427 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7433 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 7439 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 7445 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 7451 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 7457 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 7463 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7469 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 7509 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 169:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 7519 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 7525 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7531 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 7537 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7543 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 7549 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7555 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 7561 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7567 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 7573 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7579 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 7585 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 7591 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 7597 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 7603 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 7609 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7615 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 7621 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7627 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 7633 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7639 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 7645 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7651 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 7657 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7663 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 7669 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7675 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 7681 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 7687 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 7693 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 7699 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 7705 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7711 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 7717 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7723 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 7729 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7735 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 7741 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7747 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 7753 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7759 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 7765 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7771 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 7777 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 7783 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 7789 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 7795 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 7801 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 7807 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 7847 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 177:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 7857 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 7863 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7869 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 7875 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7881 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 7887 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7893 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 7899 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7905 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 7911 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7917 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 7923 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 7929 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 7935 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 7941 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 7947 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 7953 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 7959 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7965 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 7971 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7977 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 7983 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 7989 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 7995 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8001 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 8007 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8013 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 8019 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 8025 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 8031 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 8037 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 8043 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8049 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 8055 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8061 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 8067 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8073 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 8079 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8085 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 8091 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8097 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 8103 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8109 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 8115 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 8121 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 8127 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 8133 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 8139 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8145 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 8185 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 185:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 8195 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 8201 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8207 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 8213 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8219 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 8225 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8231 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 8237 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8243 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 8249 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8255 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 8261 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 8267 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 8273 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 8279 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 8285 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8291 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 8297 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8303 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 8309 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8315 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 8321 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8327 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 8333 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8339 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 8345 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8351 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 8357 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 8363 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 8369 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 8375 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 8381 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8387 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 8393 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8399 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 8405 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8411 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 8417 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8423 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 8429 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8435 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 8441 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8447 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 8453 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 8459 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 8465 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 8471 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 8477 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8483 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 8523 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 193:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 8533 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 8539 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8545 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 8551 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8557 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 8563 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8569 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 8575 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8581 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 8587 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8593 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 8599 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 8605 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 8611 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 8617 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 8623 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8629 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 8635 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8641 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 8647 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8653 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 8659 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8665 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 8671 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8677 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 8683 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8689 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 8695 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 8701 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 8707 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 8713 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 8719 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8725 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 8731 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8737 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 8743 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8749 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 8755 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8761 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 8767 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8773 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 8779 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8785 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 8791 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 8797 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 8803 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 8809 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 8815 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 8821 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 8861 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 8871 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 8877 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8883 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 8889 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8895 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 8901 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8907 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 8913 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8919 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 8925 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8931 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 8937 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 8943 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 8949 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 8955 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 8961 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 8967 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 8973 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8979 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 8985 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 8991 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 8997 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9003 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 9009 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9015 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 9021 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9027 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 9033 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 9039 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 9045 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 9051 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 9057 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9063 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 9069 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9075 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 9081 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9087 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 9093 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9099 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 9105 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9111 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 9117 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9123 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 9129 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 9135 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 9141 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 9147 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 9153 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9159 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 9199 "gen/ragel/alt4_8-F1.c"
					
					
					break; 
				}
				case 201:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b1 = p; }
					
#line 9209 "gen/ragel/alt4_8-F1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 9215 "gen/ragel/alt4_8-F1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c1 = p; }
					
#line 9221 "gen/ragel/alt4_8-F1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 9227 "gen/ragel/alt4_8-F1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d1 = p; }
					
#line 9233 "gen/ragel/alt4_8-F1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 9239 "gen/ragel/alt4_8-F1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e1 = p; }
					
#line 9245 "gen/ragel/alt4_8-F1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 9251 "gen/ragel/alt4_8-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f1 = p; }
					
#line 9257 "gen/ragel/alt4_8-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 9263 "gen/ragel/alt4_8-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g1 = p; }
					
#line 9269 "gen/ragel/alt4_8-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 9275 "gen/ragel/alt4_8-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h1 = p; }
					
#line 9281 "gen/ragel/alt4_8-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 9287 "gen/ragel/alt4_8-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a1 = p; }
					
#line 9293 "gen/ragel/alt4_8-F1.c"
					
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 9299 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b3 = p; }
					
#line 9305 "gen/ragel/alt4_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 9311 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c3 = p; }
					
#line 9317 "gen/ragel/alt4_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 9323 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d3 = p; }
					
#line 9329 "gen/ragel/alt4_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 9335 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e3 = p; }
					
#line 9341 "gen/ragel/alt4_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 9347 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f3 = p; }
					
#line 9353 "gen/ragel/alt4_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 9359 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g3 = p; }
					
#line 9365 "gen/ragel/alt4_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 9371 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h3 = p; }
					
#line 9377 "gen/ragel/alt4_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 9383 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a3 = p; }
					
#line 9389 "gen/ragel/alt4_8-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 9395 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b5 = p; }
					
#line 9401 "gen/ragel/alt4_8-F1.c"
					
					{
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9407 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c5 = p; }
					
#line 9413 "gen/ragel/alt4_8-F1.c"
					
					{
#line 41 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9419 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d5 = p; }
					
#line 9425 "gen/ragel/alt4_8-F1.c"
					
					{
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9431 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e5 = p; }
					
#line 9437 "gen/ragel/alt4_8-F1.c"
					
					{
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9443 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f5 = p; }
					
#line 9449 "gen/ragel/alt4_8-F1.c"
					
					{
#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9455 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g5 = p; }
					
#line 9461 "gen/ragel/alt4_8-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; }
					
#line 9467 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h5 = p; }
					
#line 9473 "gen/ragel/alt4_8-F1.c"
					
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; }
					
#line 9479 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a5 = p; }
					
#line 9485 "gen/ragel/alt4_8-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; }
					
#line 9491 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b7 = p; }
					
#line 9497 "gen/ragel/alt4_8-F1.c"
					
					{
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9503 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c7 = p; }
					
#line 9509 "gen/ragel/alt4_8-F1.c"
					
					{
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9515 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d7 = p; }
					
#line 9521 "gen/ragel/alt4_8-F1.c"
					
					{
#line 52 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9527 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e7 = p; }
					
#line 9533 "gen/ragel/alt4_8-F1.c"
					
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9539 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f7 = p; }
					
#line 9545 "gen/ragel/alt4_8-F1.c"
					
					{
#line 54 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9551 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g7 = p; }
					
#line 9557 "gen/ragel/alt4_8-F1.c"
					
					{
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; }
					
#line 9563 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h7 = p; }
					
#line 9569 "gen/ragel/alt4_8-F1.c"
					
					{
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; }
					
#line 9575 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a7 = p; }
					
#line 9581 "gen/ragel/alt4_8-F1.c"
					
					{
#line 57 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt4_8.rl"
						a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; }
					
#line 9587 "gen/ragel/alt4_8-F1.c"
					
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
					
#line 9627 "gen/ragel/alt4_8-F1.c"
					
					
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
