#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"



#line 12 "gen/ragel/cat4_0-F1.c"
static const char _abcd_trans_keys[] = {
	1, 0, 0, 3, 0, 3, 0, 3,
	0, 3, 0, 3, 0, 3, 0, 3,
	0, 3, 0, 3, 0
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
	0, 0, 4, 8, 12, 16, 20, 24,
	28, 32, 0
};

static const signed char _abcd_indicies[] = {
	2, 0, 3, 4, 6, 0, 7, 8,
	10, 0, 11, 12, 14, 0, 15, 16,
	18, 0, 19, 20, 22, 0, 23, 24,
	26, 0, 25, 27, 29, 0, 0, 28,
	31, 0, 32, 33, 0
};

static const signed char _abcd_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _abcd_cond_targs[] = {
	0, 1, 9, 1, 2, 2, 9, 3,
	2, 3, 9, 3, 4, 4, 9, 5,
	4, 5, 9, 5, 6, 6, 9, 7,
	6, 7, 9, 8, 8, 9, 9, 9,
	1, 2, 0
};

static const signed char _abcd_cond_actions[] = {
	0, 0, 1, 2, 3, 0, 4, 5,
	6, 0, 7, 8, 9, 0, 10, 11,
	12, 0, 13, 14, 15, 0, 16, 17,
	18, 0, 19, 20, 0, 21, 0, 22,
	23, 24, 0
};

static const int abcd_start = 9;
static const int abcd_first_final = 9;
static const int abcd_error = 0;

static const int abcd_en_main = 9;


#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3,
	*b0, *b1, *b2, *b3;
	int cs;
	
	
#line 88 "gen/ragel/cat4_0-F1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
	
	
#line 96 "gen/ragel/cat4_0-F1.c"
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
				case 17:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 129 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 139 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 154 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 164 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 170 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 180 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 186 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 196 "gen/ragel/cat4_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 207 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 217 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 223 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 229 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 239 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 245 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 251 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 261 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 267 "gen/ragel/cat4_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 278 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 288 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 294 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 300 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 306 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 316 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 322 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 328 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 334 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 344 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 350 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 356 "gen/ragel/cat4_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 367 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 377 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 383 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 389 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 395 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 401 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 411 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 417 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 423 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 429 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 435 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 445 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 451 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 457 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 463 "gen/ragel/cat4_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 474 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b0 = p; }
					
#line 484 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 490 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 496 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 502 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 508 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 514 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 524 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 530 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 536 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 542 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 548 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 554 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 564 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 570 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 576 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 582 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 588 "gen/ragel/cat4_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 599 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a0 = p; }
					
#line 609 "gen/ragel/cat4_0-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b0 = p; }
					
#line 615 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 621 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 627 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 633 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 639 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 645 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b0 = p; }
					
#line 655 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 661 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 667 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 673 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 679 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 685 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 691 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 701 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 707 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 713 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 719 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 725 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 731 "gen/ragel/cat4_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 742 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a0 = p; }
					
#line 752 "gen/ragel/cat4_0-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b0 = p; }
					
#line 758 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 764 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 770 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 776 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 782 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 788 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 794 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b0 = p; }
					
#line 804 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 810 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 816 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 822 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 828 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 834 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 840 "gen/ragel/cat4_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 851 "gen/ragel/cat4_0-F1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a0 = p; }
					
#line 861 "gen/ragel/cat4_0-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b0 = p; }
					
#line 867 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 873 "gen/ragel/cat4_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 879 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 885 "gen/ragel/cat4_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 891 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 897 "gen/ragel/cat4_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 903 "gen/ragel/cat4_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 914 "gen/ragel/cat4_0-F1.c"
					
					
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
	
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
	
	
	in->p = p;
	in->pe = pe;
}
