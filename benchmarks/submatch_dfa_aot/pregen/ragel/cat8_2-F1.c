#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"



#line 12 "gen/ragel/cat8_2-F1.c"
static const char _abcd_trans_keys[] = {
	1, 0, 2, 2, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	0, 3, 0, 3, 2, 2, 0, 3,
	0, 3, 2, 2, 0, 3, 0, 3,
	2, 2, 0, 3, 0, 3, 2, 2,
	0, 3, 0, 3, 2, 2, 0, 3,
	0, 3, 2, 2, 0, 3, 0, 3,
	2, 2, 0, 3, 0, 3, 2, 3,
	2, 3, 2, 2, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 2, 2, 3,
	2, 3, 2, 3, 2, 2, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 2,
	2, 3, 2, 3, 2, 3, 2, 2,
	2, 3, 2, 3, 2, 3, 2, 2,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 2, 2, 3, 2, 3, 2, 3,
	2, 2, 2, 3, 2, 3, 2, 3,
	2, 2, 2, 3, 2, 3, 2, 3,
	2, 2, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 2, 2, 3, 2, 3,
	2, 3, 2, 2, 2, 3, 2, 3,
	2, 3, 2, 2, 2, 3, 2, 3,
	2, 3, 2, 2, 2, 3, 2, 3,
	2, 3, 2, 2, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 2, 2, 3,
	2, 3, 2, 3, 2, 2, 2, 3,
	2, 3, 2, 3, 2, 2, 2, 3,
	2, 3, 2, 3, 2, 2, 2, 3,
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

static const short _abcd_index_offsets[] = {
	0, 0, 1, 3, 5, 7, 9, 11,
	13, 15, 17, 19, 21, 23, 25, 27,
	29, 33, 37, 38, 42, 46, 47, 51,
	55, 56, 60, 64, 65, 69, 73, 74,
	78, 82, 83, 87, 91, 92, 96, 100,
	102, 104, 105, 107, 109, 111, 113, 114,
	116, 118, 120, 121, 123, 125, 127, 129,
	130, 132, 134, 136, 137, 139, 141, 143,
	144, 146, 148, 150, 152, 153, 155, 157,
	159, 160, 162, 164, 166, 167, 169, 171,
	173, 174, 176, 178, 180, 182, 183, 185,
	187, 189, 190, 192, 194, 196, 197, 199,
	201, 203, 204, 206, 208, 210, 211, 213,
	215, 217, 219, 220, 222, 224, 226, 227,
	229, 231, 233, 234, 236, 238, 240, 241,
	243, 245, 247, 248, 250, 252, 254, 255,
	257, 259, 261, 0
};

static const short _abcd_indicies[] = {
	2, 4, 5, 7, 5, 9, 10, 12,
	10, 14, 15, 17, 15, 19, 20, 22,
	20, 24, 25, 27, 25, 29, 30, 32,
	30, 34, 35, 37, 35, 39, 0, 37,
	40, 39, 0, 41, 40, 43, 39, 0,
	45, 46, 39, 0, 47, 46, 49, 39,
	0, 51, 52, 39, 0, 53, 52, 55,
	39, 0, 57, 58, 39, 0, 59, 58,
	61, 39, 0, 63, 64, 39, 0, 65,
	64, 67, 39, 0, 69, 70, 39, 0,
	71, 70, 73, 39, 0, 75, 76, 39,
	0, 77, 76, 79, 39, 0, 79, 81,
	39, 0, 0, 81, 41, 35, 82, 30,
	84, 86, 87, 45, 87, 47, 87, 89,
	25, 91, 93, 94, 96, 94, 97, 94,
	99, 101, 102, 51, 102, 53, 102, 104,
	20, 106, 108, 109, 111, 109, 112, 109,
	114, 116, 117, 119, 117, 120, 117, 122,
	124, 125, 57, 125, 59, 125, 127, 15,
	129, 131, 132, 134, 132, 135, 132, 137,
	139, 140, 142, 140, 143, 140, 145, 147,
	148, 150, 148, 151, 148, 153, 155, 156,
	63, 156, 65, 156, 158, 10, 160, 162,
	163, 165, 163, 166, 163, 168, 170, 171,
	173, 171, 174, 171, 176, 178, 179, 181,
	179, 182, 179, 184, 186, 187, 189, 187,
	190, 187, 192, 194, 195, 69, 195, 71,
	195, 197, 5, 199, 201, 202, 204, 202,
	205, 202, 207, 209, 210, 212, 210, 213,
	210, 215, 217, 218, 220, 218, 221, 218,
	223, 225, 226, 228, 226, 229, 226, 231,
	233, 234, 236, 234, 237, 234, 239, 241,
	242, 75, 242, 77, 242, 245, 0
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
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0
};

static const short _abcd_cond_targs[] = {
	0, 1, 2, 2, 3, 105, 3, 4,
	4, 5, 84, 5, 6, 6, 7, 67,
	7, 8, 8, 9, 54, 9, 10, 10,
	11, 45, 11, 12, 12, 13, 40, 13,
	14, 14, 15, 39, 15, 16, 16, 130,
	17, 18, 18, 19, 19, 19, 20, 21,
	21, 22, 22, 22, 23, 24, 24, 25,
	25, 25, 26, 27, 27, 28, 28, 28,
	29, 30, 30, 31, 31, 31, 32, 33,
	33, 34, 34, 34, 35, 36, 36, 37,
	37, 38, 41, 41, 42, 42, 43, 44,
	43, 46, 46, 47, 47, 48, 49, 48,
	42, 50, 50, 51, 51, 52, 53, 52,
	55, 55, 56, 56, 57, 58, 57, 47,
	59, 59, 60, 60, 61, 62, 61, 51,
	63, 63, 64, 64, 65, 66, 65, 68,
	68, 69, 69, 70, 71, 70, 56, 72,
	72, 73, 73, 74, 75, 74, 60, 76,
	76, 77, 77, 78, 79, 78, 64, 80,
	80, 81, 81, 82, 83, 82, 85, 85,
	86, 86, 87, 88, 87, 69, 89, 89,
	90, 90, 91, 92, 91, 73, 93, 93,
	94, 94, 95, 96, 95, 77, 97, 97,
	98, 98, 99, 100, 99, 81, 101, 101,
	102, 102, 103, 104, 103, 106, 106, 107,
	107, 108, 109, 108, 86, 110, 110, 111,
	111, 112, 113, 112, 90, 114, 114, 115,
	115, 116, 117, 116, 94, 118, 118, 119,
	119, 120, 121, 120, 98, 122, 122, 123,
	123, 124, 125, 124, 102, 126, 126, 127,
	127, 128, 129, 128, 130, 1, 0
};

static const signed char _abcd_cond_actions[] = {
	0, 0, 1, 0, 2, 0, 0, 2,
	0, 3, 0, 0, 3, 0, 4, 0,
	0, 4, 0, 5, 0, 0, 5, 0,
	6, 0, 0, 6, 0, 7, 0, 0,
	7, 0, 8, 0, 0, 8, 0, 9,
	0, 10, 0, 11, 0, 12, 0, 13,
	0, 14, 0, 15, 0, 16, 0, 17,
	0, 18, 0, 19, 0, 20, 0, 21,
	0, 22, 0, 23, 0, 24, 0, 25,
	0, 26, 0, 27, 0, 28, 0, 29,
	0, 0, 30, 0, 31, 0, 12, 0,
	0, 32, 0, 33, 0, 34, 0, 0,
	34, 35, 0, 36, 0, 15, 0, 0,
	37, 0, 38, 0, 39, 0, 0, 39,
	40, 0, 41, 0, 42, 0, 0, 42,
	43, 0, 44, 0, 18, 0, 0, 45,
	0, 46, 0, 47, 0, 0, 47, 48,
	0, 49, 0, 50, 0, 0, 50, 51,
	0, 52, 0, 53, 0, 0, 53, 54,
	0, 55, 0, 21, 0, 0, 56, 0,
	57, 0, 58, 0, 0, 58, 59, 0,
	60, 0, 61, 0, 0, 61, 62, 0,
	63, 0, 64, 0, 0, 64, 65, 0,
	66, 0, 67, 0, 0, 67, 68, 0,
	69, 0, 24, 0, 0, 70, 0, 71,
	0, 72, 0, 0, 72, 73, 0, 74,
	0, 75, 0, 0, 75, 76, 0, 77,
	0, 78, 0, 0, 78, 79, 0, 80,
	0, 81, 0, 0, 81, 82, 0, 83,
	0, 84, 0, 0, 84, 85, 0, 86,
	0, 27, 0, 0, 0, 87, 0
};

static const int abcd_start = 130;
static const int abcd_first_final = 130;
static const int abcd_error = 0;

static const int abcd_en_main = 130;


#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
	*b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
	int cs;
	
	
#line 228 "gen/ragel/cat8_2-F1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
	
	
#line 236 "gen/ragel/cat8_2-F1.c"
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
				case 1:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 269 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 71:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 279 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 74:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 289 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 77:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 299 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 80:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 309 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 83:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 319 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 86:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 329 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 29:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 339 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
						outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
						outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
						outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
						outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
					}
					
#line 358 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 87:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a0 = p; }
					
#line 368 "gen/ragel/cat8_2-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 374 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 70:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 384 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 390 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 57:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 400 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 406 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 73:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 416 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 422 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 60:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 432 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 438 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 76:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 448 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 454 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 63:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 464 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 470 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 79:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 480 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 486 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 66:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 496 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 502 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 82:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 512 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 518 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 69:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 528 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 534 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 85:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 544 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 550 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 26:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 560 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 566 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 28:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 576 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 582 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 592 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 598 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 604 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 72:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 614 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 620 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 626 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 46:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 636 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 642 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 648 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 75:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 658 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 664 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 670 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 49:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 680 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 686 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 692 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 78:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 702 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 708 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 714 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 52:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 724 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 730 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 736 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 81:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 746 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 752 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 758 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 55:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 768 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 774 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 780 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 84:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 790 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 796 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 802 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 812 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 818 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 824 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 27:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 834 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 840 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 846 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 56:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 856 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 862 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 868 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 874 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 38:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 884 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 890 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 896 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 902 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 59:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 912 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 918 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 924 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 930 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 41:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 940 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 946 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 952 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 958 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 62:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 968 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 974 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 980 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 986 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 44:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 996 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1002 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1008 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1014 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 65:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1024 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1030 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1036 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1042 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1052 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1058 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1064 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1070 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 68:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1080 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1086 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 1092 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1098 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 1108 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1114 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 1120 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1126 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 1136 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 1142 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1148 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 1154 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1160 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 58:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1170 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 1176 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1182 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1188 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1194 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 33:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1204 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1210 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1216 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1222 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1228 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 61:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1238 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1244 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1250 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1256 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1262 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 36:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1272 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1278 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1284 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1290 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1296 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 64:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1306 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1312 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1318 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1324 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1330 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1340 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1346 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1352 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1358 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1364 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 67:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1374 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1380 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1386 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 1392 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1398 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1408 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 1414 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1420 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 1426 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1432 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 45:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 1442 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1448 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 1454 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1460 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1466 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1472 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 31:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1482 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1488 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1494 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1500 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1506 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1512 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 48:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 1522 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1528 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1534 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1540 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1546 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1552 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1562 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1568 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1574 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1580 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1586 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1592 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 51:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1602 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1608 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1614 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1620 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1626 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1632 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 54:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1642 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1648 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1654 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1660 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 1666 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1672 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1682 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1688 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 1694 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1700 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 1706 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1712 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 1722 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 1728 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1734 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 1740 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1746 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1752 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1758 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 47:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1768 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 1774 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1780 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1786 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1792 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1798 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1804 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1814 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1820 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1826 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1832 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1838 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1844 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1850 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 50:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1860 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1866 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1872 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1878 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1884 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1890 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1896 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 53:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1906 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1912 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1918 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1924 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1930 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 1936 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1942 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1952 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1958 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1964 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 1970 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1976 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 1982 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1988 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 37:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 1998 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 2004 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2010 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2016 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2022 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2028 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2034 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2040 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 40:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2050 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2056 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2062 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2068 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2074 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2080 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2086 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2092 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 43:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2102 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2108 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2114 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2120 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2126 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2132 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2138 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2144 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2154 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2160 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2166 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2172 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2178 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2184 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 2190 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 2196 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 2206 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 2212 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 2218 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2224 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2230 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2236 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2242 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2248 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2254 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 39:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 2264 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2270 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2276 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2282 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2288 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2294 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2300 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2306 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2312 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 42:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2322 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2328 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2334 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2340 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2346 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2352 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2358 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2364 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2370 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2380 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2386 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2392 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2398 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2404 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2410 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2416 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 2422 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 2428 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 32:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 2438 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 2444 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2450 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2456 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2462 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2468 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2474 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2480 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2486 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2492 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 35:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2502 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2508 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2514 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2520 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2526 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2532 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2538 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2544 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2550 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2556 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2566 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2572 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2578 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2584 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2590 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2596 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2602 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2608 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 2614 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 2620 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 2630 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 2636 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 2642 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2648 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2654 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2660 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2666 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2672 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2678 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2684 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2690 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 34:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 2700 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2706 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2712 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2718 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2724 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2730 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2736 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2742 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2748 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2754 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2760 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2770 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2776 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2782 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2788 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2794 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2800 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2806 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2812 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2818 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 2824 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 2830 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 30:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 2840 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 2846 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2852 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2858 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2864 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2870 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2876 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2882 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2888 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2894 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2900 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2906 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2916 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2922 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2928 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2934 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2940 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2946 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2952 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2958 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2964 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2970 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 2976 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 2982 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 2992 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 2998 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 3004 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 3010 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 3016 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 3022 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 3028 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 3034 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 3040 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 3046 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 3052 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 3058 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 3064 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 3074 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 3080 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 3086 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 3092 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 3098 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 3104 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 3110 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 3116 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 3122 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 3128 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 3134 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 3140 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 3146 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 3156 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 3162 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 3168 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 3174 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 3180 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 3186 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 3192 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 3198 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 3204 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 3210 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 3216 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 3222 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 3228 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 3234 "gen/ragel/cat8_2-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 3244 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 3250 "gen/ragel/cat8_2-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 3256 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 3262 "gen/ragel/cat8_2-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 3268 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 3274 "gen/ragel/cat8_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 3280 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 3286 "gen/ragel/cat8_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 3292 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 3298 "gen/ragel/cat8_2-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 3304 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 3310 "gen/ragel/cat8_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 3316 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 3322 "gen/ragel/cat8_2-F1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 3328 "gen/ragel/cat8_2-F1.c"
					
					
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
	
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
	
	
	in->p = p;
	in->pe = pe;
}
