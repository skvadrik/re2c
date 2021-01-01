#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"



#line 12 "gen/ragel/cat8_1-F1.c"
static const char _abcd_trans_keys[] = {
	1, 0, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	0, 3, 0, 3, 0, 3, 0, 3,
	0, 3, 0, 3, 0, 3, 0, 3,
	0, 3, 0, 3, 0, 3, 0, 3,
	0, 3, 0, 3, 0, 3, 0, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 2, 0
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

static const short _abcd_index_offsets[] = {
	0, 0, 2, 4, 6, 8, 10, 12,
	14, 18, 22, 26, 30, 34, 38, 42,
	46, 50, 54, 58, 62, 66, 70, 74,
	78, 80, 82, 84, 86, 88, 90, 92,
	94, 96, 98, 100, 102, 104, 106, 108,
	110, 112, 114, 116, 118, 120, 122, 124,
	126, 128, 130, 132, 134, 136, 138, 140,
	142, 144, 146, 148, 150, 152, 154, 156,
	158, 160, 162, 164, 166, 168, 170, 172,
	174, 176, 0
};

static const short _abcd_indicies[] = {
	2, 3, 5, 6, 8, 9, 11, 12,
	14, 15, 17, 18, 20, 21, 23, 0,
	20, 24, 23, 0, 25, 24, 23, 0,
	27, 28, 23, 0, 29, 28, 23, 0,
	31, 32, 23, 0, 33, 32, 23, 0,
	35, 36, 23, 0, 37, 36, 23, 0,
	39, 40, 23, 0, 41, 40, 23, 0,
	43, 44, 23, 0, 45, 44, 23, 0,
	47, 48, 23, 0, 49, 48, 23, 0,
	51, 52, 23, 0, 0, 52, 25, 21,
	53, 18, 27, 55, 29, 55, 56, 15,
	58, 59, 60, 59, 31, 62, 33, 62,
	63, 12, 65, 66, 67, 66, 69, 70,
	71, 70, 35, 73, 37, 73, 74, 9,
	76, 77, 78, 77, 80, 81, 82, 81,
	84, 85, 86, 85, 39, 88, 41, 88,
	89, 6, 91, 92, 93, 92, 95, 96,
	97, 96, 99, 100, 101, 100, 103, 104,
	105, 104, 43, 107, 45, 107, 108, 3,
	110, 111, 112, 111, 114, 115, 116, 115,
	118, 119, 120, 119, 122, 123, 124, 123,
	126, 127, 128, 127, 47, 130, 49, 130,
	132, 0
};

static const signed char _abcd_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _abcd_cond_targs[] = {
	0, 1, 2, 60, 2, 3, 49, 3,
	4, 40, 4, 5, 33, 5, 6, 28,
	6, 7, 25, 7, 8, 24, 8, 73,
	9, 10, 10, 10, 11, 12, 12, 12,
	13, 14, 14, 14, 15, 16, 16, 16,
	17, 18, 18, 18, 19, 20, 20, 20,
	21, 22, 22, 22, 23, 26, 26, 27,
	29, 29, 26, 30, 31, 31, 32, 34,
	34, 29, 35, 36, 36, 31, 37, 38,
	38, 39, 41, 41, 34, 42, 43, 43,
	36, 44, 45, 45, 38, 46, 47, 47,
	48, 50, 50, 41, 51, 52, 52, 43,
	53, 54, 54, 45, 55, 56, 56, 47,
	57, 58, 58, 59, 61, 61, 50, 62,
	63, 63, 52, 64, 65, 65, 54, 66,
	67, 67, 56, 68, 69, 69, 58, 70,
	71, 71, 72, 73, 1, 0
};

static const signed char _abcd_cond_actions[] = {
	0, 0, 1, 0, 0, 2, 0, 0,
	3, 0, 0, 4, 0, 0, 5, 0,
	0, 6, 0, 0, 7, 0, 0, 8,
	0, 9, 0, 10, 0, 11, 0, 12,
	0, 13, 0, 14, 0, 15, 0, 16,
	0, 17, 0, 18, 0, 19, 0, 20,
	0, 21, 0, 22, 0, 23, 0, 0,
	24, 0, 25, 0, 26, 0, 0, 27,
	0, 28, 0, 29, 0, 30, 0, 31,
	0, 0, 32, 0, 33, 0, 34, 0,
	35, 0, 36, 0, 37, 0, 38, 0,
	0, 39, 0, 40, 0, 41, 0, 42,
	0, 43, 0, 44, 0, 45, 0, 46,
	0, 47, 0, 0, 48, 0, 49, 0,
	50, 0, 51, 0, 52, 0, 53, 0,
	54, 0, 55, 0, 56, 0, 57, 0,
	58, 0, 0, 0, 59, 0
};

static const int abcd_start = 73;
static const int abcd_first_final = 73;
static const int abcd_error = 0;

static const int abcd_en_main = 73;


#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
	*b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
	int cs;
	
	
#line 162 "gen/ragel/cat8_1-F1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
	
	
#line 170 "gen/ragel/cat8_1-F1.c"
	{
		unsigned int _trans = 0;
		const char * _keys;
		const short * _inds;
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
				case 22:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 203 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 222 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 59:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a0 = p; }
					
#line 232 "gen/ragel/cat8_1-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 238 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 48:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 248 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 254 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 50:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 264 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 270 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 52:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 280 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 286 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 54:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 296 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 302 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 56:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 312 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 318 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 58:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 328 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 334 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 344 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 350 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 360 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 366 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 372 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 49:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 382 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 388 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 394 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 51:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 404 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 410 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 416 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 53:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 426 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 432 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 438 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 55:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 448 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 454 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 460 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 57:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 470 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 476 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 482 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 492 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 498 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 504 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 39:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 514 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 520 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 526 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 532 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 41:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 542 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 548 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 554 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 560 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 43:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 570 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 576 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 582 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 588 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 45:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 598 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 604 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 610 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 616 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 47:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 626 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 632 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 638 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 644 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 654 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 660 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 666 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 672 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 682 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 688 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 694 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 700 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 706 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 40:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 716 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 722 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 728 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 734 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 740 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 42:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 750 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 756 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 762 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 768 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 774 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 44:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 784 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 790 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 796 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 802 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 808 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 46:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 818 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 824 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 830 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 836 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 842 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 852 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 858 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 864 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 870 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 876 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 32:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 886 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 892 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 898 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 904 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 910 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 916 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 34:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 926 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 932 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 938 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 944 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 950 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 956 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 36:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 966 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 972 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 978 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 984 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 990 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 996 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 38:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1006 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1012 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1018 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1024 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1030 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1036 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1046 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1052 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1058 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1064 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 1070 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 1076 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 1086 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 1092 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 1098 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1104 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1110 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1116 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1122 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 33:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 1132 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1138 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1144 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1150 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1156 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1162 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1168 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 35:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1178 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1184 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1190 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1196 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1202 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1208 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1214 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 37:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1224 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1230 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1236 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1242 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1248 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1254 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1260 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1270 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1276 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1282 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1288 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1294 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 1300 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 1306 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 27:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 1316 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 1322 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1328 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1334 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1340 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1346 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1352 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1358 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 29:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1368 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1374 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1380 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1386 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1392 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1398 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1404 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1410 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 31:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1420 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1426 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1432 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1438 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1444 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1450 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1456 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1462 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1472 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1478 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1484 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1490 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1496 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1502 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 1508 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 1514 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 1524 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 1530 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 1536 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1542 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1548 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1554 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1560 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1566 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1572 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 28:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 1582 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1588 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1594 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1600 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1606 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1612 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1618 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1624 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1630 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 30:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1640 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1646 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1652 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1658 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1664 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1670 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1676 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1682 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1688 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1698 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1704 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1710 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1716 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1722 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1728 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1734 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 1740 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 1746 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 1756 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 1762 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1768 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1774 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1780 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1786 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1792 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1798 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1804 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1810 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 26:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1820 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1826 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1832 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1838 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1844 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1850 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1856 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1862 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1868 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1874 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1884 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1890 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1896 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1902 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1908 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1914 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1920 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1926 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 1932 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 1938 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 1948 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 1954 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 1960 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1966 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1972 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1978 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1984 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1990 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1996 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2002 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2008 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 2018 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2024 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2030 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2036 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2042 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2048 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2054 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2060 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2066 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2072 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2078 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2088 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2094 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2100 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2106 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2112 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2118 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2124 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2130 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2136 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 2142 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 2148 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 2158 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 2164 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2170 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2176 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2182 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2188 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2194 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2200 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2206 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2212 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2218 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2224 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2234 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2240 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2246 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2252 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2258 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2264 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2270 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2276 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2282 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2288 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 2294 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 2300 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 2310 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 2316 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 2322 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2328 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2334 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2340 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2346 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2352 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2358 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2364 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2370 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2376 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2382 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 2392 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2398 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2404 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2410 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2416 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2422 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2428 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2434 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2440 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2446 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2452 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 2458 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 2464 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 2474 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 2480 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2486 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2492 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2498 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2504 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2510 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2516 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2522 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2528 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2534 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2540 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 2546 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 2552 "gen/ragel/cat8_1-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 2562 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 2568 "gen/ragel/cat8_1-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 2574 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2580 "gen/ragel/cat8_1-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2586 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2592 "gen/ragel/cat8_1-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2598 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2604 "gen/ragel/cat8_1-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2610 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2616 "gen/ragel/cat8_1-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2622 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2628 "gen/ragel/cat8_1-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2634 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 2640 "gen/ragel/cat8_1-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 2646 "gen/ragel/cat8_1-F1.c"
					
					
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
	
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
	
	
	in->p = p;
	in->pe = pe;
}
