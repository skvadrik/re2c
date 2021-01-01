#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"



#line 12 "gen/ragel/cat8_2-T1.c"
static const short _abcd_key_offsets[] = {
	0, 0, 1, 3, 5, 7, 9, 11,
	13, 15, 17, 19, 21, 23, 25, 27,
	29, 32, 35, 36, 39, 42, 43, 46,
	49, 50, 53, 56, 57, 60, 63, 64,
	67, 70, 71, 74, 77, 78, 81, 83,
	85, 87, 88, 90, 92, 94, 96, 97,
	99, 101, 103, 104, 106, 108, 110, 112,
	113, 115, 117, 119, 120, 122, 124, 126,
	127, 129, 131, 133, 135, 136, 138, 140,
	142, 143, 145, 147, 149, 150, 152, 154,
	156, 157, 159, 161, 163, 165, 166, 168,
	170, 172, 173, 175, 177, 179, 180, 182,
	184, 186, 187, 189, 191, 193, 194, 196,
	198, 200, 202, 203, 205, 207, 209, 210,
	212, 214, 216, 217, 219, 221, 223, 224,
	226, 228, 230, 231, 233, 235, 237, 238,
	240, 242, 244, 0
};

static const char _abcd_trans_keys[] = {
	97, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 10, 97, 98,
	10, 97, 98, 97, 10, 97, 98, 10,
	97, 98, 97, 10, 97, 98, 10, 97,
	98, 97, 10, 97, 98, 10, 97, 98,
	97, 10, 97, 98, 10, 97, 98, 97,
	10, 97, 98, 10, 97, 98, 97, 10,
	97, 98, 10, 97, 98, 97, 10, 97,
	98, 10, 98, 97, 98, 97, 98, 97,
	97, 98, 97, 98, 97, 98, 97, 98,
	97, 97, 98, 97, 98, 97, 98, 97,
	97, 98, 97, 98, 97, 98, 97, 98,
	97, 97, 98, 97, 98, 97, 98, 97,
	97, 98, 97, 98, 97, 98, 97, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	97, 98, 97, 98, 97, 98, 97, 97,
	98, 97, 98, 97, 98, 97, 97, 98,
	97, 98, 97, 98, 97, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 97, 98,
	97, 98, 97, 98, 97, 97, 98, 97,
	98, 97, 98, 97, 97, 98, 97, 98,
	97, 98, 97, 97, 98, 97, 98, 97,
	98, 97, 97, 98, 97, 98, 97, 98,
	97, 98, 97, 97, 98, 97, 98, 97,
	98, 97, 97, 98, 97, 98, 97, 98,
	97, 97, 98, 97, 98, 97, 98, 97,
	97, 98, 97, 98, 97, 98, 97, 97,
	98, 97, 98, 97, 98, 97, 97, 98,
	97, 98, 97, 98, 97, 0
};

static const signed char _abcd_single_lengths[] = {
	0, 1, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 1, 3, 3, 1, 3, 3,
	1, 3, 3, 1, 3, 3, 1, 3,
	3, 1, 3, 3, 1, 3, 2, 2,
	2, 1, 2, 2, 2, 2, 1, 2,
	2, 2, 1, 2, 2, 2, 2, 1,
	2, 2, 2, 1, 2, 2, 2, 1,
	2, 2, 2, 2, 1, 2, 2, 2,
	1, 2, 2, 2, 1, 2, 2, 2,
	1, 2, 2, 2, 2, 1, 2, 2,
	2, 1, 2, 2, 2, 1, 2, 2,
	2, 1, 2, 2, 2, 1, 2, 2,
	2, 2, 1, 2, 2, 2, 1, 2,
	2, 2, 1, 2, 2, 2, 1, 2,
	2, 2, 1, 2, 2, 2, 1, 2,
	2, 2, 1, 0
};

static const signed char _abcd_range_lengths[] = {
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

static const short _abcd_index_offsets[] = {
	0, 0, 2, 5, 8, 11, 14, 17,
	20, 23, 26, 29, 32, 35, 38, 41,
	44, 48, 52, 54, 58, 62, 64, 68,
	72, 74, 78, 82, 84, 88, 92, 94,
	98, 102, 104, 108, 112, 114, 118, 121,
	124, 127, 129, 132, 135, 138, 141, 143,
	146, 149, 152, 154, 157, 160, 163, 166,
	168, 171, 174, 177, 179, 182, 185, 188,
	190, 193, 196, 199, 202, 204, 207, 210,
	213, 215, 218, 221, 224, 226, 229, 232,
	235, 237, 240, 243, 246, 249, 251, 254,
	257, 260, 262, 265, 268, 271, 273, 276,
	279, 282, 284, 287, 290, 293, 295, 298,
	301, 304, 307, 309, 312, 315, 318, 320,
	323, 326, 329, 331, 334, 337, 340, 342,
	345, 348, 351, 353, 356, 359, 362, 364,
	367, 370, 373, 0
};

static const short _abcd_cond_targs[] = {
	2, 0, 3, 105, 0, 4, 105, 0,
	5, 84, 0, 6, 84, 0, 7, 67,
	0, 8, 67, 0, 9, 54, 0, 10,
	54, 0, 11, 45, 0, 12, 45, 0,
	13, 40, 0, 14, 40, 0, 15, 39,
	0, 16, 39, 0, 130, 16, 17, 0,
	130, 18, 17, 0, 19, 0, 130, 19,
	20, 0, 130, 21, 20, 0, 22, 0,
	130, 22, 23, 0, 130, 24, 23, 0,
	25, 0, 130, 25, 26, 0, 130, 27,
	26, 0, 28, 0, 130, 28, 29, 0,
	130, 30, 29, 0, 31, 0, 130, 31,
	32, 0, 130, 33, 32, 0, 34, 0,
	130, 34, 35, 0, 130, 36, 35, 0,
	37, 0, 130, 37, 38, 0, 130, 38,
	0, 18, 39, 0, 41, 40, 0, 42,
	0, 43, 44, 0, 19, 44, 0, 21,
	44, 0, 46, 45, 0, 47, 0, 48,
	49, 0, 42, 49, 0, 50, 49, 0,
	51, 0, 52, 53, 0, 22, 53, 0,
	24, 53, 0, 55, 54, 0, 56, 0,
	57, 58, 0, 47, 58, 0, 59, 58,
	0, 60, 0, 61, 62, 0, 51, 62,
	0, 63, 62, 0, 64, 0, 65, 66,
	0, 25, 66, 0, 27, 66, 0, 68,
	67, 0, 69, 0, 70, 71, 0, 56,
	71, 0, 72, 71, 0, 73, 0, 74,
	75, 0, 60, 75, 0, 76, 75, 0,
	77, 0, 78, 79, 0, 64, 79, 0,
	80, 79, 0, 81, 0, 82, 83, 0,
	28, 83, 0, 30, 83, 0, 85, 84,
	0, 86, 0, 87, 88, 0, 69, 88,
	0, 89, 88, 0, 90, 0, 91, 92,
	0, 73, 92, 0, 93, 92, 0, 94,
	0, 95, 96, 0, 77, 96, 0, 97,
	96, 0, 98, 0, 99, 100, 0, 81,
	100, 0, 101, 100, 0, 102, 0, 103,
	104, 0, 31, 104, 0, 33, 104, 0,
	106, 105, 0, 107, 0, 108, 109, 0,
	86, 109, 0, 110, 109, 0, 111, 0,
	112, 113, 0, 90, 113, 0, 114, 113,
	0, 115, 0, 116, 117, 0, 94, 117,
	0, 118, 117, 0, 119, 0, 120, 121,
	0, 98, 121, 0, 122, 121, 0, 123,
	0, 124, 125, 0, 102, 125, 0, 126,
	125, 0, 127, 0, 128, 129, 0, 34,
	129, 0, 36, 129, 0, 1, 0, 0,
	1, 2, 3, 4, 5, 6, 7, 8,
	9, 10, 11, 12, 13, 14, 15, 16,
	17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30, 31, 32,
	33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48,
	49, 50, 51, 52, 53, 54, 55, 56,
	57, 58, 59, 60, 61, 62, 63, 64,
	65, 66, 67, 68, 69, 70, 71, 72,
	73, 74, 75, 76, 77, 78, 79, 80,
	81, 82, 83, 84, 85, 86, 87, 88,
	89, 90, 91, 92, 93, 94, 95, 96,
	97, 98, 99, 100, 101, 102, 103, 104,
	105, 106, 107, 108, 109, 110, 111, 112,
	113, 114, 115, 116, 117, 118, 119, 120,
	121, 122, 123, 124, 125, 126, 127, 128,
	129, 130, 0
};

static const signed char _abcd_cond_actions[] = {
	1, 0, 2, 0, 0, 2, 0, 0,
	3, 0, 0, 3, 0, 0, 4, 0,
	0, 4, 0, 0, 5, 0, 0, 5,
	0, 0, 6, 0, 0, 6, 0, 0,
	7, 0, 0, 7, 0, 0, 8, 0,
	0, 8, 0, 0, 9, 8, 0, 0,
	9, 10, 0, 0, 11, 0, 9, 12,
	0, 0, 9, 13, 0, 0, 14, 0,
	9, 15, 0, 0, 9, 16, 0, 0,
	17, 0, 9, 18, 0, 0, 9, 19,
	0, 0, 20, 0, 9, 21, 0, 0,
	9, 22, 0, 0, 23, 0, 9, 24,
	0, 0, 9, 25, 0, 0, 26, 0,
	9, 27, 0, 0, 9, 28, 0, 0,
	29, 0, 9, 29, 0, 0, 9, 0,
	0, 10, 0, 0, 30, 0, 0, 31,
	0, 12, 0, 0, 12, 0, 0, 13,
	0, 0, 32, 0, 0, 33, 0, 34,
	0, 0, 34, 0, 0, 35, 0, 0,
	36, 0, 15, 0, 0, 15, 0, 0,
	16, 0, 0, 37, 0, 0, 38, 0,
	39, 0, 0, 39, 0, 0, 40, 0,
	0, 41, 0, 42, 0, 0, 42, 0,
	0, 43, 0, 0, 44, 0, 18, 0,
	0, 18, 0, 0, 19, 0, 0, 45,
	0, 0, 46, 0, 47, 0, 0, 47,
	0, 0, 48, 0, 0, 49, 0, 50,
	0, 0, 50, 0, 0, 51, 0, 0,
	52, 0, 53, 0, 0, 53, 0, 0,
	54, 0, 0, 55, 0, 21, 0, 0,
	21, 0, 0, 22, 0, 0, 56, 0,
	0, 57, 0, 58, 0, 0, 58, 0,
	0, 59, 0, 0, 60, 0, 61, 0,
	0, 61, 0, 0, 62, 0, 0, 63,
	0, 64, 0, 0, 64, 0, 0, 65,
	0, 0, 66, 0, 67, 0, 0, 67,
	0, 0, 68, 0, 0, 69, 0, 24,
	0, 0, 24, 0, 0, 25, 0, 0,
	70, 0, 0, 71, 0, 72, 0, 0,
	72, 0, 0, 73, 0, 0, 74, 0,
	75, 0, 0, 75, 0, 0, 76, 0,
	0, 77, 0, 78, 0, 0, 78, 0,
	0, 79, 0, 0, 80, 0, 81, 0,
	0, 81, 0, 0, 82, 0, 0, 83,
	0, 84, 0, 0, 84, 0, 0, 85,
	0, 0, 86, 0, 27, 0, 0, 27,
	0, 0, 28, 0, 0, 87, 0, 0,
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
	0, 0, 0
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
	
	
#line 281 "gen/ragel/cat8_2-T1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
	
	
#line 289 "gen/ragel/cat8_2-T1.c"
	{
		int _klen;
		unsigned int _trans = 0;
		const char * _keys;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _abcd_trans_keys + (_abcd_key_offsets[cs]));
		_trans = (unsigned int)_abcd_index_offsets[cs];
		
		_klen = (int)_abcd_single_lengths[cs];
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
		
		_klen = (int)_abcd_range_lengths[cs];
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
		cs = (int)_abcd_cond_targs[_trans];
		
		if ( _abcd_cond_actions[_trans] != 0 ) {
			
			switch ( _abcd_cond_actions[_trans] ) {
				case 1:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 358 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 71:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 368 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 74:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 378 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 77:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 388 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 80:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 398 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 83:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 408 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 86:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 418 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 29:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 428 "gen/ragel/cat8_2-T1.c"
					
					
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
					
#line 447 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 87:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a0 = p; }
					
#line 457 "gen/ragel/cat8_2-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 463 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 70:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 473 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 479 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 57:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 489 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 495 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 73:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 505 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 511 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 60:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 521 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 527 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 76:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 537 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 543 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 63:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 553 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 559 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 79:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 569 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 575 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 66:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 585 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 591 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 82:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 601 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 607 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 69:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 617 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 623 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 85:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 633 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 639 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 26:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 649 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 655 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 28:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 665 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 671 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 681 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 687 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 693 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 72:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 703 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 709 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 715 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 46:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 725 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 731 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 737 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 75:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 747 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 753 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 759 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 49:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 769 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 775 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 781 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 78:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 791 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 797 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 803 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 52:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 813 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 819 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 825 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 81:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 835 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 841 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 847 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 55:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 857 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 863 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 869 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 84:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 879 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 885 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 891 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 901 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 907 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 913 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 27:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 923 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 929 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 935 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 56:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 945 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 951 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 957 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 963 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 38:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 973 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 979 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 985 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 991 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 59:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 1001 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1007 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1013 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1019 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 41:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1029 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1035 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1041 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1047 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 62:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1057 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1063 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1069 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1075 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 44:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1085 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1091 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1097 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1103 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 65:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1113 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1119 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1125 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1131 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1141 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1147 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1153 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1159 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 68:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1169 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1175 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 1181 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1187 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 1197 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1203 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 1209 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1215 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 1225 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 1231 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1237 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 1243 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1249 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 58:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1259 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 1265 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1271 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1277 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1283 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 33:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1293 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1299 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1305 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1311 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1317 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 61:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1327 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1333 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1339 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1345 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1351 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 36:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1361 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1367 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1373 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1379 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1385 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 64:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1395 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1401 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1407 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1413 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1419 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1429 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1435 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1441 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1447 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1453 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 67:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1463 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1469 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1475 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 1481 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1487 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1497 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 1503 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1509 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 1515 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1521 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 45:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 1531 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1537 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 1543 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1549 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1555 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1561 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 31:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1571 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1577 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1583 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1589 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1595 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1601 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 48:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 1611 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1617 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1623 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1629 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1635 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1641 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1651 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1657 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1663 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1669 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1675 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1681 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 51:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1691 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1697 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1703 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1709 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1715 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1721 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 54:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1731 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1737 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1743 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1749 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 1755 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1761 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1771 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1777 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 1783 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1789 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 1795 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1801 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 1811 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 1817 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1823 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 1829 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1835 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1841 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1847 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 47:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1857 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 1863 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1869 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1875 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1881 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1887 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1893 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 1903 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1909 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1915 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1921 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1927 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 1933 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 1939 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 50:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 1949 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 1955 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1961 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 1967 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 1973 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 1979 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 1985 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 53:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 1995 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2001 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2007 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2013 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2019 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2025 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2031 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2041 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2047 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2053 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2059 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2065 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 2071 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 2077 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 37:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 2087 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 2093 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2099 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2105 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2111 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2117 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2123 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2129 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 40:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2139 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2145 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2151 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2157 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2163 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2169 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2175 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2181 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 43:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2191 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2197 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2203 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2209 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2215 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2221 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2227 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2233 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2243 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2249 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2255 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2261 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2267 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2273 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 2279 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 2285 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 2295 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 2301 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 2307 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2313 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2319 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2325 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2331 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2337 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2343 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 39:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 2353 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2359 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2365 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2371 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2377 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2383 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2389 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2395 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2401 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 42:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2411 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2417 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2423 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2429 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2435 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2441 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2447 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2453 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2459 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2469 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2475 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2481 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2487 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2493 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2499 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2505 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 2511 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 2517 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 32:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 2527 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 2533 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2539 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2545 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2551 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2557 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2563 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2569 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2575 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2581 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 35:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2591 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2597 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2603 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2609 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2615 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2621 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2627 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2633 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2639 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2645 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2655 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2661 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2667 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2673 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2679 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2685 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2691 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2697 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 2703 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 2709 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 2719 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 2725 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 2731 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2737 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2743 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2749 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2755 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2761 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2767 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2773 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2779 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 34:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 2789 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2795 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2801 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2807 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2813 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2819 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2825 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2831 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2837 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2843 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2849 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2859 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2865 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2871 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2877 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2883 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2889 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2895 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2901 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2907 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 2913 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 2919 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 30:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 2929 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 2935 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 2941 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 2947 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 2953 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 2959 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 2965 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 2971 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 2977 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 2983 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 2989 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 2995 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 3005 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 3011 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 3017 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 3023 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 3029 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 3035 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 3041 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 3047 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 3053 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 3059 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 3065 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 3071 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 3081 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 3087 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 3093 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 3099 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 3105 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 3111 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 3117 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 3123 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 3129 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 3135 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 3141 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 3147 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 3153 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 3163 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 3169 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 3175 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 3181 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 3187 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 3193 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 3199 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 3205 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 3211 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 3217 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 3223 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 3229 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 3235 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 3245 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 3251 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 3257 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 3263 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 3269 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 3275 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 3281 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 3287 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 3293 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 3299 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 3305 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 3311 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 3317 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 3323 "gen/ragel/cat8_2-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b0 = p; }
					
#line 3333 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a1 = p; }
					
#line 3339 "gen/ragel/cat8_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b1 = p; }
					
#line 3345 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a2 = p; }
					
#line 3351 "gen/ragel/cat8_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b2 = p; }
					
#line 3357 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a3 = p; }
					
#line 3363 "gen/ragel/cat8_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b3 = p; }
					
#line 3369 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a4 = p; }
					
#line 3375 "gen/ragel/cat8_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b4 = p; }
					
#line 3381 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a5 = p; }
					
#line 3387 "gen/ragel/cat8_2-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b5 = p; }
					
#line 3393 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a6 = p; }
					
#line 3399 "gen/ragel/cat8_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b6 = p; }
					
#line 3405 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						a7 = p; }
					
#line 3411 "gen/ragel/cat8_2-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
						b7 = p; }
					
#line 3417 "gen/ragel/cat8_2-T1.c"
					
					
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
