#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"



#line 12 "gen/ragel/cat8_1-T1.c"
static const short _abcd_key_offsets[] = {
	0, 0, 2, 4, 6, 8, 10, 12,
	14, 17, 20, 23, 26, 29, 32, 35,
	38, 41, 44, 47, 50, 53, 56, 59,
	61, 63, 65, 67, 69, 71, 73, 75,
	77, 79, 81, 83, 85, 87, 89, 91,
	93, 95, 97, 99, 101, 103, 105, 107,
	109, 111, 113, 115, 117, 119, 121, 123,
	125, 127, 129, 131, 133, 135, 137, 139,
	141, 143, 145, 147, 149, 151, 153, 155,
	157, 159, 0
};

static const char _abcd_trans_keys[] = {
	97, 98, 97, 98, 97, 98, 97, 98,
	97, 98, 97, 98, 97, 98, 10, 97,
	98, 10, 97, 98, 10, 97, 98, 10,
	97, 98, 10, 97, 98, 10, 97, 98,
	10, 97, 98, 10, 97, 98, 10, 97,
	98, 10, 97, 98, 10, 97, 98, 10,
	97, 98, 10, 97, 98, 10, 97, 98,
	10, 97, 98, 10, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	0
};

static const signed char _abcd_single_lengths[] = {
	0, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 1, 0
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
	0, 0, 0
};

static const short _abcd_index_offsets[] = {
	0, 0, 3, 6, 9, 12, 15, 18,
	21, 25, 29, 33, 37, 41, 45, 49,
	53, 57, 61, 65, 69, 73, 77, 81,
	84, 87, 90, 93, 96, 99, 102, 105,
	108, 111, 114, 117, 120, 123, 126, 129,
	132, 135, 138, 141, 144, 147, 150, 153,
	156, 159, 162, 165, 168, 171, 174, 177,
	180, 183, 186, 189, 192, 195, 198, 201,
	204, 207, 210, 213, 216, 219, 222, 225,
	228, 231, 0
};

static const signed char _abcd_cond_targs[] = {
	2, 60, 0, 3, 49, 0, 4, 40,
	0, 5, 33, 0, 6, 28, 0, 7,
	25, 0, 8, 24, 0, 73, 8, 9,
	0, 73, 10, 9, 0, 73, 10, 11,
	0, 73, 12, 11, 0, 73, 12, 13,
	0, 73, 14, 13, 0, 73, 14, 15,
	0, 73, 16, 15, 0, 73, 16, 17,
	0, 73, 18, 17, 0, 73, 18, 19,
	0, 73, 20, 19, 0, 73, 20, 21,
	0, 73, 22, 21, 0, 73, 22, 23,
	0, 73, 23, 0, 10, 24, 0, 26,
	25, 0, 10, 27, 0, 12, 27, 0,
	29, 28, 0, 26, 30, 0, 31, 30,
	0, 12, 32, 0, 14, 32, 0, 34,
	33, 0, 29, 35, 0, 36, 35, 0,
	31, 37, 0, 38, 37, 0, 14, 39,
	0, 16, 39, 0, 41, 40, 0, 34,
	42, 0, 43, 42, 0, 36, 44, 0,
	45, 44, 0, 38, 46, 0, 47, 46,
	0, 16, 48, 0, 18, 48, 0, 50,
	49, 0, 41, 51, 0, 52, 51, 0,
	43, 53, 0, 54, 53, 0, 45, 55,
	0, 56, 55, 0, 47, 57, 0, 58,
	57, 0, 18, 59, 0, 20, 59, 0,
	61, 60, 0, 50, 62, 0, 63, 62,
	0, 52, 64, 0, 65, 64, 0, 54,
	66, 0, 67, 66, 0, 56, 68, 0,
	69, 68, 0, 58, 70, 0, 71, 70,
	0, 20, 72, 0, 22, 72, 0, 1,
	0, 0, 1, 2, 3, 4, 5, 6,
	7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 28, 29, 30,
	31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46,
	47, 48, 49, 50, 51, 52, 53, 54,
	55, 56, 57, 58, 59, 60, 61, 62,
	63, 64, 65, 66, 67, 68, 69, 70,
	71, 72, 73, 0
};

static const signed char _abcd_cond_actions[] = {
	1, 0, 0, 2, 0, 0, 3, 0,
	0, 4, 0, 0, 5, 0, 0, 6,
	0, 0, 7, 0, 0, 8, 7, 0,
	0, 8, 9, 0, 0, 8, 10, 0,
	0, 8, 11, 0, 0, 8, 12, 0,
	0, 8, 13, 0, 0, 8, 14, 0,
	0, 8, 15, 0, 0, 8, 16, 0,
	0, 8, 17, 0, 0, 8, 18, 0,
	0, 8, 19, 0, 0, 8, 20, 0,
	0, 8, 21, 0, 0, 8, 22, 0,
	0, 8, 0, 0, 9, 0, 0, 23,
	0, 0, 10, 0, 0, 11, 0, 0,
	24, 0, 0, 25, 0, 0, 26, 0,
	0, 12, 0, 0, 13, 0, 0, 27,
	0, 0, 28, 0, 0, 29, 0, 0,
	30, 0, 0, 31, 0, 0, 14, 0,
	0, 15, 0, 0, 32, 0, 0, 33,
	0, 0, 34, 0, 0, 35, 0, 0,
	36, 0, 0, 37, 0, 0, 38, 0,
	0, 16, 0, 0, 17, 0, 0, 39,
	0, 0, 40, 0, 0, 41, 0, 0,
	42, 0, 0, 43, 0, 0, 44, 0,
	0, 45, 0, 0, 46, 0, 0, 47,
	0, 0, 18, 0, 0, 19, 0, 0,
	48, 0, 0, 49, 0, 0, 50, 0,
	0, 51, 0, 0, 52, 0, 0, 53,
	0, 0, 54, 0, 0, 55, 0, 0,
	56, 0, 0, 57, 0, 0, 58, 0,
	0, 20, 0, 0, 21, 0, 0, 59,
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
	
	
#line 193 "gen/ragel/cat8_1-T1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
	
	
#line 201 "gen/ragel/cat8_1-T1.c"
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
				case 22:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 270 "gen/ragel/cat8_1-T1.c"
					
					
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
					
#line 289 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 59:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a0 = p; }
					
#line 299 "gen/ragel/cat8_1-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 305 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 48:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 315 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 321 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 50:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 331 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 337 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 52:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 347 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 353 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 54:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 363 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 369 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 56:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 379 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 385 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 58:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 395 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 401 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 411 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 417 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 427 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 433 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 439 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 49:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 449 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 455 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 461 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 51:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 471 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 477 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 483 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 53:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 493 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 499 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 505 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 55:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 515 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 521 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 527 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 57:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 537 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 543 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 549 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 559 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 565 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 571 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 39:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 581 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 587 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 593 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 599 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 41:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 609 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 615 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 621 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 627 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 43:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 637 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 643 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 649 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 655 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 45:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 665 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 671 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 677 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 683 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 47:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 693 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 699 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 705 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 711 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 721 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 727 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 733 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 739 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 749 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 755 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 761 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 767 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 773 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 40:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 783 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 789 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 795 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 801 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 807 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 42:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 817 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 823 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 829 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 835 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 841 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 44:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 851 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 857 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 863 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 869 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 875 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 46:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 885 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 891 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 897 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 903 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 909 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 919 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 925 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 931 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 937 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 943 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 32:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 953 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 959 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 965 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 971 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 977 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 983 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 34:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 993 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 999 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1005 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1011 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1017 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1023 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 36:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1033 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1039 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1045 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1051 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1057 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1063 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 38:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1073 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1079 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1085 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1091 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1097 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1103 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1113 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1119 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1125 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1131 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 1137 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 1143 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 1153 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 1159 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 1165 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1171 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1177 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1183 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1189 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 33:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 1199 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1205 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1211 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1217 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1223 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1229 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1235 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 35:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1245 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1251 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1257 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1263 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1269 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1275 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1281 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 37:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1291 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1297 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1303 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1309 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1315 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1321 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1327 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1337 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1343 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1349 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1355 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1361 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 1367 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 1373 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 27:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 1383 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 1389 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1395 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1401 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1407 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1413 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1419 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1425 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 29:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1435 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1441 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1447 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1453 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1459 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1465 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1471 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1477 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 31:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1487 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1493 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1499 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1505 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1511 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1517 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1523 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1529 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1539 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1545 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1551 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1557 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1563 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1569 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 1575 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 1581 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 1591 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 1597 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 1603 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1609 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1615 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1621 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1627 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1633 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1639 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 28:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 1649 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1655 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1661 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1667 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1673 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1679 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1685 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1691 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1697 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 30:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1707 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1713 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1719 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1725 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1731 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1737 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1743 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1749 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1755 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1765 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1771 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1777 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1783 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1789 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1795 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1801 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 1807 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 1813 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 1823 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 1829 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1835 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1841 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1847 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1853 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1859 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1865 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1871 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1877 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 26:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 1887 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 1893 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1899 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1905 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1911 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1917 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1923 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1929 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1935 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1941 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 1951 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 1957 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 1963 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 1969 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 1975 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 1981 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 1987 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 1993 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 1999 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 2005 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 2015 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 2021 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 2027 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2033 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2039 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2045 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2051 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2057 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2063 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2069 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2075 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 2085 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2091 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2097 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2103 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2109 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2115 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2121 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2127 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2133 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2139 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2145 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2155 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2161 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2167 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2173 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2179 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2185 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2191 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2197 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2203 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 2209 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 2215 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 2225 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 2231 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2237 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2243 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2249 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2255 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2261 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2267 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2273 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2279 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2285 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2291 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2301 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2307 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2313 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2319 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2325 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2331 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2337 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2343 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2349 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2355 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 2361 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 2367 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 2377 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 2383 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 2389 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2395 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2401 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2407 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2413 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2419 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2425 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2431 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2437 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2443 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2449 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 2459 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2465 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2471 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2477 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2483 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2489 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2495 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2501 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2507 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2513 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2519 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 2525 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 2531 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 2541 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 2547 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2553 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2559 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2565 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2571 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2577 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2583 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2589 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2595 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2601 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2607 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 2613 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 2619 "gen/ragel/cat8_1-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b0 = p; }
					
#line 2629 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a1 = p; }
					
#line 2635 "gen/ragel/cat8_1-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b1 = p; }
					
#line 2641 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a2 = p; }
					
#line 2647 "gen/ragel/cat8_1-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b2 = p; }
					
#line 2653 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a3 = p; }
					
#line 2659 "gen/ragel/cat8_1-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b3 = p; }
					
#line 2665 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a4 = p; }
					
#line 2671 "gen/ragel/cat8_1-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b4 = p; }
					
#line 2677 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a5 = p; }
					
#line 2683 "gen/ragel/cat8_1-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b5 = p; }
					
#line 2689 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a6 = p; }
					
#line 2695 "gen/ragel/cat8_1-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b6 = p; }
					
#line 2701 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						a7 = p; }
					
#line 2707 "gen/ragel/cat8_1-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
						b7 = p; }
					
#line 2713 "gen/ragel/cat8_1-T1.c"
					
					
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
