#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 59 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"



#line 13 "gen/ragel/alt2_8-F1.c"
static const char _m_trans_keys[] = {
	1, 0, 0, 9, 0, 3, 0, 4,
	0, 5, 0, 6, 0, 7, 0, 8,
	0, 9, 0, 9, 0, 2, 0, 9,
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
	0, 0, 10, 14, 19, 25, 32, 40,
	49, 59, 69, 72, 82, 92, 102, 112,
	122, 132, 0
};

static const signed char _m_indicies[] = {
	2, 0, 1, 3, 4, 5, 6, 7,
	8, 9, 11, 0, 0, 10, 13, 0,
	0, 0, 12, 15, 0, 0, 0, 0,
	14, 17, 0, 0, 0, 0, 0, 16,
	19, 0, 0, 0, 0, 0, 0, 18,
	21, 0, 0, 0, 0, 0, 0, 0,
	20, 23, 0, 0, 0, 0, 0, 0,
	0, 0, 22, 25, 0, 26, 24, 27,
	28, 29, 30, 31, 32, 34, 0, 33,
	36, 0, 37, 38, 35, 39, 40, 41,
	42, 43, 45, 0, 46, 47, 48, 44,
	49, 50, 51, 52, 54, 0, 55, 56,
	57, 58, 53, 59, 60, 61, 63, 0,
	64, 65, 66, 67, 68, 62, 69, 70,
	72, 0, 73, 74, 75, 76, 77, 78,
	71, 79, 81, 0, 82, 83, 84, 85,
	86, 87, 88, 80, 90, 0, 91, 92,
	93, 94, 95, 96, 97, 98, 0
};

static const signed char _m_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _m_cond_targs[] = {
	0, 1, 17, 2, 3, 4, 5, 6,
	7, 8, 2, 17, 3, 17, 4, 17,
	5, 17, 6, 17, 7, 17, 8, 17,
	9, 17, 10, 3, 4, 5, 6, 7,
	8, 10, 17, 11, 17, 10, 2, 4,
	5, 6, 7, 8, 12, 17, 10, 2,
	3, 5, 6, 7, 8, 13, 17, 10,
	2, 3, 4, 6, 7, 8, 14, 17,
	10, 2, 3, 4, 5, 7, 8, 15,
	17, 10, 2, 3, 4, 5, 6, 8,
	16, 17, 10, 2, 3, 4, 5, 6,
	7, 17, 17, 1, 9, 11, 12, 13,
	14, 15, 16, 0
};

static const signed char _m_cond_actions[] = {
	0, 0, 1, 2, 3, 4, 5, 6,
	7, 8, 0, 9, 0, 10, 0, 11,
	0, 12, 0, 13, 0, 14, 0, 15,
	0, 16, 17, 18, 19, 20, 21, 22,
	23, 0, 24, 0, 25, 26, 27, 28,
	29, 30, 31, 32, 0, 33, 34, 35,
	36, 37, 38, 39, 40, 0, 41, 42,
	43, 44, 45, 46, 47, 48, 0, 49,
	50, 51, 52, 53, 54, 55, 56, 0,
	57, 58, 59, 60, 61, 62, 63, 64,
	0, 65, 66, 67, 68, 69, 70, 71,
	72, 0, 73, 74, 75, 76, 77, 78,
	79, 80, 81, 0
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
	
	
#line 124 "gen/ragel/alt2_8-F1.c"
	{
		cs = (int)m_start;
	}
	
#line 74 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
	
	
#line 132 "gen/ragel/alt2_8-F1.c"
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
				case 75:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b1 = p; }
					
#line 165 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 76:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c1 = p; }
					
#line 175 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 77:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d1 = p; }
					
#line 185 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 78:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e1 = p; }
					
#line 195 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 79:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f1 = p; }
					
#line 205 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 80:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g1 = p; }
					
#line 215 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 81:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h1 = p; }
					
#line 225 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 74:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a1 = p; }
					
#line 235 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 245 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 251 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 261 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 267 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 277 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 283 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 293 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 299 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 309 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 315 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 325 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 331 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 341 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 347 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 27:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 357 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 363 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 28:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 373 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 379 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 29:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 389 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 395 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 30:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 405 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 411 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 31:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 421 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 427 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 32:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 437 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 443 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 26:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 453 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 459 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 35:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 469 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 475 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 36:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 485 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 491 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 37:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 501 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 507 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 38:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 517 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 523 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 39:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 533 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 539 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 40:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 549 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 555 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 34:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 565 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 571 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 43:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 581 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 587 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 44:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 597 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 603 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 45:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 613 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 619 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 46:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 629 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 635 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 47:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 645 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 651 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 48:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 661 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 667 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 42:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 677 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 683 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 51:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 693 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 699 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 52:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 709 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 715 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 53:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 725 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 731 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 54:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 741 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 747 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 55:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 757 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 763 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 56:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 773 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 779 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 50:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 789 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 795 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 59:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 805 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 811 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 60:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 821 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 827 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 61:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 837 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 843 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 62:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 853 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 859 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 63:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 869 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 875 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 64:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 885 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 891 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 58:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 901 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 907 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 67:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 917 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 923 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 68:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 933 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 939 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 69:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 949 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 955 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 70:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 965 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 971 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 71:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 981 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 987 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 72:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 997 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 1003 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 66:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 1013 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 1019 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1029 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 1035 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1045 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 1051 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1061 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 1067 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1077 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 1083 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1093 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 1099 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1109 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 1115 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1125 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 1131 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1141 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 1165 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1175 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 1199 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1209 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 1233 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1243 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 1267 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1277 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 1301 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1311 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 1335 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1345 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 1369 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1379 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 1403 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1413 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 1419 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1425 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 1431 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1437 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 1443 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1449 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 1455 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1461 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 1467 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1473 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 1479 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1485 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 1491 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1497 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 1503 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1509 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 1533 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1543 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 1549 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1555 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 1561 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1567 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 1573 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1579 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 1585 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1591 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 1597 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1603 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 1609 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1615 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 1621 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1627 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 1633 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1639 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 1663 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 33:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1673 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 1679 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1685 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 1691 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1697 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 1703 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1709 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 1715 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1721 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 1727 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1733 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 1739 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1745 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 1751 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1757 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 1763 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1769 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 1793 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 41:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1803 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 1809 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1815 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 1821 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1827 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 1833 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1839 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 1845 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1851 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 1857 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1863 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 1869 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 1875 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 1881 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 1887 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 1893 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1899 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 1923 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 49:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 1933 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 1939 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1945 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 1951 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1957 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 1963 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1969 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 1975 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1981 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 1987 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 1993 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 1999 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 2005 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 2011 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 2017 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 2023 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2029 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 2053 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 57:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 2063 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 2069 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2075 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 2081 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2087 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 2093 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2099 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 2105 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2111 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 2117 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2123 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 2129 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 2135 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 2141 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 2147 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 2153 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2159 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 2183 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 65:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 2193 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 2199 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2205 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 2211 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2217 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 2223 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2229 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 2235 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2241 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 2247 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2253 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 2259 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 2265 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 2271 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 2277 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 2283 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2289 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 2313 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 2323 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 2329 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2335 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 2341 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2347 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 2353 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2359 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 2365 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2371 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 2377 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2383 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 2389 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 2395 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 2401 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 2407 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 2413 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2419 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 2443 "gen/ragel/alt2_8-F1.c"
					
					
					break; 
				}
				case 73:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b1 = p; }
					
#line 2453 "gen/ragel/alt2_8-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 2459 "gen/ragel/alt2_8-F1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c1 = p; }
					
#line 2465 "gen/ragel/alt2_8-F1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 2471 "gen/ragel/alt2_8-F1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d1 = p; }
					
#line 2477 "gen/ragel/alt2_8-F1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 2483 "gen/ragel/alt2_8-F1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e1 = p; }
					
#line 2489 "gen/ragel/alt2_8-F1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 2495 "gen/ragel/alt2_8-F1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f1 = p; }
					
#line 2501 "gen/ragel/alt2_8-F1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 2507 "gen/ragel/alt2_8-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g1 = p; }
					
#line 2513 "gen/ragel/alt2_8-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 2519 "gen/ragel/alt2_8-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h1 = p; }
					
#line 2525 "gen/ragel/alt2_8-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 2531 "gen/ragel/alt2_8-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a1 = p; }
					
#line 2537 "gen/ragel/alt2_8-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 2543 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b3 = p; }
					
#line 2549 "gen/ragel/alt2_8-F1.c"
					
					{
#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2555 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c3 = p; }
					
#line 2561 "gen/ragel/alt2_8-F1.c"
					
					{
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2567 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d3 = p; }
					
#line 2573 "gen/ragel/alt2_8-F1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2579 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e3 = p; }
					
#line 2585 "gen/ragel/alt2_8-F1.c"
					
					{
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2591 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f3 = p; }
					
#line 2597 "gen/ragel/alt2_8-F1.c"
					
					{
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2603 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g3 = p; }
					
#line 2609 "gen/ragel/alt2_8-F1.c"
					
					{
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; }
					
#line 2615 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h3 = p; }
					
#line 2621 "gen/ragel/alt2_8-F1.c"
					
					{
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; }
					
#line 2627 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a3 = p; }
					
#line 2633 "gen/ragel/alt2_8-F1.c"
					
					{
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_8.rl"
						a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; }
					
#line 2639 "gen/ragel/alt2_8-F1.c"
					
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
					
#line 2663 "gen/ragel/alt2_8-F1.c"
					
					
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
