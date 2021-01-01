#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"



#line 12 "gen/ragel/cat4_4-F1.c"
static const char _abcd_trans_keys[] = {
	1, 0, 2, 2, 2, 2, 2, 2,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	0, 3, 0, 3, 2, 2, 2, 2,
	2, 2, 0, 3, 0, 3, 2, 2,
	2, 2, 2, 2, 0, 3, 0, 3,
	2, 2, 2, 2, 2, 2, 0, 3,
	0, 3, 2, 3, 2, 3, 2, 2,
	2, 2, 2, 2, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 2, 2, 2, 2, 2, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 2, 2, 2, 2, 2, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 2, 0
};

static const signed char _abcd_char_class[] = {
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

static const signed char _abcd_index_offsets[] = {
	0, 0, 1, 2, 3, 5, 7, 9,
	11, 13, 15, 17, 19, 21, 23, 25,
	27, 31, 35, 36, 37, 38, 42, 46,
	47, 48, 49, 53, 57, 58, 59, 60,
	64, 68, 70, 72, 73, 74, 75, 77,
	79, 81, 83, 85, 87, 88, 89, 90,
	92, 94, 96, 98, 100, 101, 102, 103,
	105, 107, 109, 111, 113, 0
};

static const signed char _abcd_indicies[] = {
	2, 4, 6, 8, 9, 11, 9, 13,
	9, 15, 9, 17, 18, 20, 18, 22,
	18, 24, 18, 26, 27, 29, 27, 31,
	27, 33, 27, 35, 0, 33, 36, 35,
	0, 37, 36, 39, 41, 43, 35, 0,
	45, 46, 35, 0, 47, 46, 49, 51,
	53, 35, 0, 55, 56, 35, 0, 57,
	56, 59, 61, 63, 35, 0, 63, 65,
	35, 0, 0, 65, 37, 27, 66, 18,
	68, 70, 72, 74, 75, 77, 75, 79,
	75, 45, 75, 47, 75, 81, 9, 83,
	85, 87, 89, 90, 92, 90, 94, 90,
	96, 90, 97, 90, 99, 101, 103, 105,
	106, 108, 106, 110, 106, 55, 106, 57,
	106, 113, 0
};

static const signed char _abcd_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};

static const signed char _abcd_cond_targs[] = {
	0, 1, 2, 2, 3, 3, 4, 4,
	5, 43, 5, 6, 6, 7, 7, 8,
	8, 9, 34, 9, 10, 10, 11, 11,
	12, 12, 13, 33, 13, 14, 14, 15,
	15, 16, 16, 60, 17, 18, 18, 19,
	19, 20, 20, 21, 21, 21, 22, 23,
	23, 24, 24, 25, 25, 26, 26, 26,
	27, 28, 28, 29, 29, 30, 30, 31,
	31, 32, 35, 35, 36, 36, 37, 37,
	38, 38, 39, 42, 39, 40, 40, 41,
	41, 44, 44, 45, 45, 46, 46, 47,
	47, 48, 51, 48, 49, 49, 50, 50,
	38, 52, 52, 53, 53, 54, 54, 55,
	55, 56, 59, 56, 57, 57, 58, 58,
	60, 1, 0
};

static const signed char _abcd_cond_actions[] = {
	0, 0, 1, 0, 1, 0, 1, 0,
	2, 0, 0, 2, 0, 2, 0, 2,
	0, 3, 0, 0, 3, 0, 3, 0,
	3, 0, 4, 0, 0, 4, 0, 4,
	0, 4, 0, 5, 0, 6, 0, 7,
	0, 7, 0, 7, 0, 8, 0, 9,
	0, 10, 0, 10, 0, 10, 0, 11,
	0, 12, 0, 13, 0, 13, 0, 13,
	0, 0, 14, 0, 15, 0, 15, 0,
	15, 0, 8, 0, 0, 8, 0, 8,
	0, 16, 0, 17, 0, 17, 0, 17,
	0, 18, 0, 0, 18, 0, 18, 0,
	18, 19, 0, 20, 0, 20, 0, 20,
	0, 11, 0, 0, 11, 0, 11, 0,
	0, 21, 0
};

static const int abcd_start = 60;
static const int abcd_first_final = 60;
static const int abcd_error = 0;

static const int abcd_en_main = 60;


#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3,
	*b0, *b1, *b2, *b3;
	int cs;
	
	
#line 143 "gen/ragel/cat4_4-F1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
	
	
#line 151 "gen/ragel/cat4_4-F1.c"
	{
		unsigned int _trans = 0;
		const char * _keys;
		const signed char * _inds;
		int _ic;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _abcd_trans_keys + ((cs<<1)));
		_inds = ( _abcd_indicies + (_abcd_index_offsets[cs]));
		
		if ( ( (*( p))) <= 98 && ( (*( p))) >= 10 ) {
			_ic = (int)_abcd_char_class[(int)( (*( p))) - 10];
			if ( _ic <= (int)(*( _keys+1)) && _ic >= (int)(*( _keys)) )
				_trans = (unsigned int)(*( _inds + (int)( _ic - (int)(*( _keys)) ) )); 
			else
				_trans = (unsigned int)_abcd_index_defaults[cs];
		}
		else {
			_trans = (unsigned int)_abcd_index_defaults[cs];
		}
		
		cs = (int)_abcd_cond_targs[_trans];
		
		if ( _abcd_cond_actions[_trans] != 0 ) {
			
			switch ( _abcd_cond_actions[_trans] ) {
				case 1:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b0 = p; }
					
#line 184 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 194 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 204 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 214 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 229 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a0 = p; }
					
#line 239 "gen/ragel/cat4_4-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b0 = p; }
					
#line 245 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a1 = p; }
					
#line 255 "gen/ragel/cat4_4-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 261 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 271 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 277 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 287 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 293 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 303 "gen/ragel/cat4_4-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 309 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a3 = p; }
					
#line 319 "gen/ragel/cat4_4-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 325 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b0 = p; }
					
#line 335 "gen/ragel/cat4_4-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a1 = p; }
					
#line 341 "gen/ragel/cat4_4-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 347 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 357 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 363 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 369 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 379 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 385 "gen/ragel/cat4_4-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 391 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 401 "gen/ragel/cat4_4-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a3 = p; }
					
#line 407 "gen/ragel/cat4_4-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 413 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a1 = p; }
					
#line 423 "gen/ragel/cat4_4-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 429 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 435 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 441 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 451 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 457 "gen/ragel/cat4_4-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a3 = p; }
					
#line 463 "gen/ragel/cat4_4-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 469 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b0 = p; }
					
#line 479 "gen/ragel/cat4_4-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a1 = p; }
					
#line 485 "gen/ragel/cat4_4-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 491 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 497 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 503 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 513 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 519 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 525 "gen/ragel/cat4_4-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a3 = p; }
					
#line 531 "gen/ragel/cat4_4-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 537 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a1 = p; }
					
#line 547 "gen/ragel/cat4_4-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 553 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 559 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 565 "gen/ragel/cat4_4-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a3 = p; }
					
#line 571 "gen/ragel/cat4_4-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 577 "gen/ragel/cat4_4-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b0 = p; }
					
#line 587 "gen/ragel/cat4_4-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a1 = p; }
					
#line 593 "gen/ragel/cat4_4-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 599 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 605 "gen/ragel/cat4_4-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 611 "gen/ragel/cat4_4-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a3 = p; }
					
#line 617 "gen/ragel/cat4_4-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 623 "gen/ragel/cat4_4-F1.c"
					
					
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
	
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
