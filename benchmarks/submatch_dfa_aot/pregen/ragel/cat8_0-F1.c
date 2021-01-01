#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"



#line 12 "gen/ragel/cat8_0-F1.c"
static const char _abcd_trans_keys[] = {
	1, 0, 0, 3, 0, 3, 0, 3,
	0, 3, 0, 3, 0, 3, 0, 3,
	0, 3, 0, 3, 0, 3, 0, 3,
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
	28, 32, 36, 40, 44, 48, 52, 56,
	60, 64, 0
};

static const signed char _abcd_indicies[] = {
	2, 0, 3, 4, 6, 0, 7, 8,
	10, 0, 11, 12, 14, 0, 15, 16,
	18, 0, 19, 20, 22, 0, 23, 24,
	26, 0, 27, 28, 30, 0, 31, 32,
	34, 0, 35, 36, 38, 0, 39, 40,
	42, 0, 43, 44, 46, 0, 47, 48,
	50, 0, 51, 52, 54, 0, 55, 56,
	58, 0, 57, 59, 61, 0, 0, 60,
	63, 0, 64, 65, 0
};

static const signed char _abcd_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _abcd_cond_targs[] = {
	0, 1, 17, 1, 2, 2, 17, 3,
	2, 3, 17, 3, 4, 4, 17, 5,
	4, 5, 17, 5, 6, 6, 17, 7,
	6, 7, 17, 7, 8, 8, 17, 9,
	8, 9, 17, 9, 10, 10, 17, 11,
	10, 11, 17, 11, 12, 12, 17, 13,
	12, 13, 17, 13, 14, 14, 17, 15,
	14, 15, 17, 16, 16, 17, 17, 17,
	1, 2, 0
};

static const signed char _abcd_cond_actions[] = {
	0, 0, 1, 2, 3, 0, 4, 5,
	6, 0, 7, 8, 9, 0, 10, 11,
	12, 0, 13, 14, 15, 0, 16, 17,
	18, 0, 19, 20, 21, 0, 22, 23,
	24, 0, 25, 26, 27, 0, 28, 29,
	30, 0, 31, 32, 33, 0, 34, 35,
	36, 0, 37, 38, 39, 0, 40, 41,
	42, 0, 43, 44, 0, 45, 0, 46,
	47, 48, 0
};

static const int abcd_start = 17;
static const int abcd_first_final = 17;
static const int abcd_error = 0;

static const int abcd_en_main = 17;


#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
	*b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
	int cs;
	
	
#line 104 "gen/ragel/cat8_0-F1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
	
	
#line 112 "gen/ragel/cat8_0-F1.c"
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
				case 41:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 145 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 44:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 155 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 45:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 174 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 38:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 184 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 190 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 42:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 200 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 206 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 43:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 216 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 231 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 35:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 241 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 247 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 253 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 39:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 263 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 269 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 275 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 40:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 285 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 291 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 306 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 32:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 316 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 322 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 328 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 334 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 36:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 344 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 350 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 356 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 362 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 37:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 372 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 378 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 384 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 399 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 29:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 409 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 415 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 421 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 427 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 433 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 33:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 443 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 449 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 455 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 461 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 467 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 34:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 477 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 483 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 489 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 495 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 510 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 26:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 520 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 526 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 532 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 538 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 544 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 550 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 30:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 560 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 566 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 572 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 578 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 584 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 590 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 31:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 600 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 606 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 612 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 618 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 624 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 639 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 649 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 655 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 661 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 667 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 673 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 679 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 685 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 27:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 695 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 701 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 707 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 713 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 719 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 725 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 731 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 28:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 741 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 747 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 753 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 759 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 765 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 771 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 786 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 796 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 802 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 808 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 814 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 820 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 826 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 832 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 838 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 848 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 854 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 860 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 866 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 872 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 878 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 884 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 890 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 900 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 906 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 912 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 918 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 924 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 930 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 936 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 951 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 961 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 967 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 973 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 979 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 985 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 991 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 997 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1003 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1009 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1019 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1025 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1031 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1037 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1043 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1049 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1055 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1061 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1067 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1077 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1083 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1089 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1095 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1101 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1107 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1113 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1119 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 1134 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1144 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1150 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1156 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1162 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1168 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1174 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1180 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1186 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1192 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1198 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1208 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1214 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1220 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1226 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1232 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1238 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1244 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1250 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1256 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1262 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1272 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1278 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1284 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1290 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1296 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1302 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1308 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1314 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1320 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 1335 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 1345 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1351 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1357 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1363 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1369 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1375 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1381 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1387 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1393 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1399 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1405 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1415 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1421 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1427 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1433 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1439 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1445 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1451 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1457 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1463 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1469 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1475 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1485 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1491 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1497 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1503 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1509 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1515 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1521 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1527 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1533 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1539 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 1554 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 1564 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 1570 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1576 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1582 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1588 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1594 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1600 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1606 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1612 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1618 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1624 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1630 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 1640 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1646 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1652 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1658 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1664 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1670 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1676 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1682 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1688 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1694 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1700 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1706 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1716 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1722 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1728 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1734 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1740 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1746 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1752 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1758 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1764 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1770 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1776 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 1791 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 1801 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 1807 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 1813 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1819 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1825 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1831 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1837 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1843 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1849 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1855 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1861 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1867 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1873 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 1883 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 1889 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1895 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1901 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1907 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1913 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1919 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1925 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1931 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1937 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1943 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1949 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1955 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 1965 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1971 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1977 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1983 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1989 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1995 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2001 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2007 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2013 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2019 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2025 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2031 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 2046 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b0 = p; }
					
#line 2056 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2062 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2068 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2074 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2080 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2086 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2092 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2098 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2104 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2110 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2116 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2122 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2128 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2134 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2144 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2150 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2156 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2162 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2168 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2174 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2180 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2186 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2192 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2198 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2204 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2210 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2216 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2222 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2232 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2238 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2244 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2250 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2256 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2262 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2268 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2274 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2280 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2286 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2292 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2298 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2304 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 2319 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 47:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a0 = p; }
					
#line 2329 "gen/ragel/cat8_0-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b0 = p; }
					
#line 2335 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2341 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2347 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2353 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2359 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2365 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2371 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2377 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2383 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2389 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2395 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2401 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2407 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2413 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b0 = p; }
					
#line 2423 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2429 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2435 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2441 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2447 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2453 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2459 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2465 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2471 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2477 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2483 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2489 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2495 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2501 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2507 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2517 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2523 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2529 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2535 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2541 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2547 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2553 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2559 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2565 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2571 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2577 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2583 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2589 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2595 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 2610 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 48:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a0 = p; }
					
#line 2620 "gen/ragel/cat8_0-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b0 = p; }
					
#line 2626 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2632 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2638 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2644 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2650 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2656 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2662 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2668 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2674 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2680 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2686 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2692 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2698 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2704 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2710 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b0 = p; }
					
#line 2720 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2726 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2732 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2738 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2744 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2750 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2756 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2762 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2768 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2774 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2780 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2786 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2792 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2798 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2804 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 2819 "gen/ragel/cat8_0-F1.c"
					
					
					break; 
				}
				case 46:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a0 = p; }
					
#line 2829 "gen/ragel/cat8_0-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b0 = p; }
					
#line 2835 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2841 "gen/ragel/cat8_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2847 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2853 "gen/ragel/cat8_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2859 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2865 "gen/ragel/cat8_0-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2871 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2877 "gen/ragel/cat8_0-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2883 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2889 "gen/ragel/cat8_0-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2895 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2901 "gen/ragel/cat8_0-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2907 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2913 "gen/ragel/cat8_0-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2919 "gen/ragel/cat8_0-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 2934 "gen/ragel/cat8_0-F1.c"
					
					
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
	
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
	
	
	in->p = p;
	in->pe = pe;
}
