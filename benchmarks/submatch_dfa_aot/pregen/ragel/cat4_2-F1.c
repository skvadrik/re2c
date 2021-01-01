#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"



#line 12 "gen/ragel/cat4_2-F1.c"
static const char _abcd_trans_keys[] = {
	1, 0, 2, 2, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	0, 3, 0, 3, 2, 2, 0, 3,
	0, 3, 2, 2, 0, 3, 0, 3,
	2, 2, 0, 3, 0, 3, 2, 3,
	2, 3, 2, 2, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 2, 2, 3,
	2, 3, 2, 3, 2, 2, 2, 3,
	2, 3, 2, 3, 2, 2, 0
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
	0, 0, 1, 3, 5, 7, 9, 11,
	13, 17, 21, 22, 26, 30, 31, 35,
	39, 40, 44, 48, 50, 52, 53, 55,
	57, 59, 61, 62, 64, 66, 68, 69,
	71, 73, 75, 0
};

static const signed char _abcd_indicies[] = {
	2, 4, 5, 7, 5, 9, 10, 12,
	10, 14, 15, 17, 15, 19, 0, 17,
	20, 19, 0, 21, 20, 23, 19, 0,
	25, 26, 19, 0, 27, 26, 29, 19,
	0, 31, 32, 19, 0, 33, 32, 35,
	19, 0, 35, 37, 19, 0, 0, 37,
	21, 15, 38, 10, 40, 42, 43, 25,
	43, 27, 43, 45, 5, 47, 49, 50,
	52, 50, 53, 50, 55, 57, 58, 31,
	58, 33, 58, 61, 0
};

static const signed char _abcd_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0
};

static const signed char _abcd_cond_targs[] = {
	0, 1, 2, 2, 3, 25, 3, 4,
	4, 5, 20, 5, 6, 6, 7, 19,
	7, 8, 8, 34, 9, 10, 10, 11,
	11, 11, 12, 13, 13, 14, 14, 14,
	15, 16, 16, 17, 17, 18, 21, 21,
	22, 22, 23, 24, 23, 26, 26, 27,
	27, 28, 29, 28, 22, 30, 30, 31,
	31, 32, 33, 32, 34, 1, 0
};

static const signed char _abcd_cond_actions[] = {
	0, 0, 1, 0, 2, 0, 0, 2,
	0, 3, 0, 0, 3, 0, 4, 0,
	0, 4, 0, 5, 0, 6, 0, 7,
	0, 8, 0, 9, 0, 10, 0, 11,
	0, 12, 0, 13, 0, 0, 14, 0,
	15, 0, 8, 0, 0, 16, 0, 17,
	0, 18, 0, 0, 18, 19, 0, 20,
	0, 11, 0, 0, 0, 21, 0
};

static const int abcd_start = 34;
static const int abcd_first_final = 34;
static const int abcd_error = 0;

static const int abcd_en_main = 34;


#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3,
	*b0, *b1, *b2, *b3;
	int cs;
	
	
#line 111 "gen/ragel/cat4_2-F1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
	
	
#line 119 "gen/ragel/cat4_2-F1.c"
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b0 = p; }
					
#line 152 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 162 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 172 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 182 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 197 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a0 = p; }
					
#line 207 "gen/ragel/cat4_2-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b0 = p; }
					
#line 213 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a1 = p; }
					
#line 223 "gen/ragel/cat4_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 229 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 239 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 245 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 255 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 261 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 271 "gen/ragel/cat4_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 277 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a3 = p; }
					
#line 287 "gen/ragel/cat4_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 293 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b0 = p; }
					
#line 303 "gen/ragel/cat4_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a1 = p; }
					
#line 309 "gen/ragel/cat4_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 315 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 325 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 331 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 337 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 347 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 353 "gen/ragel/cat4_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 359 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 369 "gen/ragel/cat4_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a3 = p; }
					
#line 375 "gen/ragel/cat4_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 381 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a1 = p; }
					
#line 391 "gen/ragel/cat4_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 397 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 403 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 409 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 419 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 425 "gen/ragel/cat4_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a3 = p; }
					
#line 431 "gen/ragel/cat4_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 437 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b0 = p; }
					
#line 447 "gen/ragel/cat4_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a1 = p; }
					
#line 453 "gen/ragel/cat4_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 459 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 465 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 471 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 481 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 487 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 493 "gen/ragel/cat4_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a3 = p; }
					
#line 499 "gen/ragel/cat4_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 505 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a1 = p; }
					
#line 515 "gen/ragel/cat4_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 521 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 527 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 533 "gen/ragel/cat4_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a3 = p; }
					
#line 539 "gen/ragel/cat4_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 545 "gen/ragel/cat4_2-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b0 = p; }
					
#line 555 "gen/ragel/cat4_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a1 = p; }
					
#line 561 "gen/ragel/cat4_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 567 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 573 "gen/ragel/cat4_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 579 "gen/ragel/cat4_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a3 = p; }
					
#line 585 "gen/ragel/cat4_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 591 "gen/ragel/cat4_2-F1.c"
					
					
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
	
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
	
	
	in->p = p;
	in->pe = pe;
}
