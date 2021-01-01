#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"



#line 12 "gen/ragel/cat4_4-T1.c"
static const signed char _abcd_key_offsets[] = {
	0, 0, 1, 2, 3, 5, 7, 9,
	11, 13, 15, 17, 19, 21, 23, 25,
	27, 30, 33, 34, 35, 36, 39, 42,
	43, 44, 45, 48, 51, 52, 53, 54,
	57, 59, 61, 63, 64, 65, 66, 68,
	70, 72, 74, 76, 78, 79, 80, 81,
	83, 85, 87, 89, 91, 92, 93, 94,
	96, 98, 100, 102, 104, 0
};

static const char _abcd_trans_keys[] = {
	97, 97, 97, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 10, 97, 98, 10, 97,
	98, 97, 97, 97, 10, 97, 98, 10,
	97, 98, 97, 97, 97, 10, 97, 98,
	10, 97, 98, 97, 97, 97, 10, 97,
	98, 10, 98, 97, 98, 97, 98, 97,
	97, 97, 97, 98, 97, 98, 97, 98,
	97, 98, 97, 98, 97, 98, 97, 97,
	97, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 97, 97, 97, 98,
	97, 98, 97, 98, 97, 98, 97, 98,
	97, 0
};

static const signed char _abcd_single_lengths[] = {
	0, 1, 1, 1, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 1, 1, 1, 3, 3, 1,
	1, 1, 3, 3, 1, 1, 1, 3,
	2, 2, 2, 1, 1, 1, 2, 2,
	2, 2, 2, 2, 1, 1, 1, 2,
	2, 2, 2, 2, 1, 1, 1, 2,
	2, 2, 2, 2, 1, 0
};

static const signed char _abcd_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};

static const short _abcd_index_offsets[] = {
	0, 0, 2, 4, 6, 9, 12, 15,
	18, 21, 24, 27, 30, 33, 36, 39,
	42, 46, 50, 52, 54, 56, 60, 64,
	66, 68, 70, 74, 78, 80, 82, 84,
	88, 91, 94, 97, 99, 101, 103, 106,
	109, 112, 115, 118, 121, 123, 125, 127,
	130, 133, 136, 139, 142, 144, 146, 148,
	151, 154, 157, 160, 163, 0
};

static const signed char _abcd_cond_targs[] = {
	2, 0, 3, 0, 4, 0, 5, 43,
	0, 6, 43, 0, 7, 43, 0, 8,
	43, 0, 9, 34, 0, 10, 34, 0,
	11, 34, 0, 12, 34, 0, 13, 33,
	0, 14, 33, 0, 15, 33, 0, 16,
	33, 0, 60, 16, 17, 0, 60, 18,
	17, 0, 19, 0, 20, 0, 21, 0,
	60, 21, 22, 0, 60, 23, 22, 0,
	24, 0, 25, 0, 26, 0, 60, 26,
	27, 0, 60, 28, 27, 0, 29, 0,
	30, 0, 31, 0, 60, 31, 32, 0,
	60, 32, 0, 18, 33, 0, 35, 34,
	0, 36, 0, 37, 0, 38, 0, 39,
	42, 0, 40, 42, 0, 41, 42, 0,
	21, 42, 0, 23, 42, 0, 44, 43,
	0, 45, 0, 46, 0, 47, 0, 48,
	51, 0, 49, 51, 0, 50, 51, 0,
	38, 51, 0, 52, 51, 0, 53, 0,
	54, 0, 55, 0, 56, 59, 0, 57,
	59, 0, 58, 59, 0, 26, 59, 0,
	28, 59, 0, 1, 0, 0, 1, 2,
	3, 4, 5, 6, 7, 8, 9, 10,
	11, 12, 13, 14, 15, 16, 17, 18,
	19, 20, 21, 22, 23, 24, 25, 26,
	27, 28, 29, 30, 31, 32, 33, 34,
	35, 36, 37, 38, 39, 40, 41, 42,
	43, 44, 45, 46, 47, 48, 49, 50,
	51, 52, 53, 54, 55, 56, 57, 58,
	59, 60, 0
};

static const signed char _abcd_cond_actions[] = {
	1, 0, 1, 0, 1, 0, 2, 0,
	0, 2, 0, 0, 2, 0, 0, 2,
	0, 0, 3, 0, 0, 3, 0, 0,
	3, 0, 0, 3, 0, 0, 4, 0,
	0, 4, 0, 0, 4, 0, 0, 4,
	0, 0, 5, 4, 0, 0, 5, 6,
	0, 0, 7, 0, 7, 0, 7, 0,
	5, 8, 0, 0, 5, 9, 0, 0,
	10, 0, 10, 0, 10, 0, 5, 11,
	0, 0, 5, 12, 0, 0, 13, 0,
	13, 0, 13, 0, 5, 13, 0, 0,
	5, 0, 0, 6, 0, 0, 14, 0,
	0, 15, 0, 15, 0, 15, 0, 8,
	0, 0, 8, 0, 0, 8, 0, 0,
	8, 0, 0, 9, 0, 0, 16, 0,
	0, 17, 0, 17, 0, 17, 0, 18,
	0, 0, 18, 0, 0, 18, 0, 0,
	18, 0, 0, 19, 0, 0, 20, 0,
	20, 0, 20, 0, 11, 0, 0, 11,
	0, 0, 11, 0, 0, 11, 0, 0,
	12, 0, 0, 21, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
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
	
	
#line 158 "gen/ragel/cat4_4-T1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
	
	
#line 166 "gen/ragel/cat4_4-T1.c"
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b0 = p; }
					
#line 235 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 245 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 255 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 265 "gen/ragel/cat4_4-T1.c"
					
					
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
					
#line 280 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a0 = p; }
					
#line 290 "gen/ragel/cat4_4-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b0 = p; }
					
#line 296 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a1 = p; }
					
#line 306 "gen/ragel/cat4_4-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 312 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 322 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 328 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 338 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 344 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 354 "gen/ragel/cat4_4-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 360 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a3 = p; }
					
#line 370 "gen/ragel/cat4_4-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 376 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b0 = p; }
					
#line 386 "gen/ragel/cat4_4-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a1 = p; }
					
#line 392 "gen/ragel/cat4_4-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 398 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 408 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 414 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 420 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 430 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 436 "gen/ragel/cat4_4-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 442 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 452 "gen/ragel/cat4_4-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a3 = p; }
					
#line 458 "gen/ragel/cat4_4-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 464 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a1 = p; }
					
#line 474 "gen/ragel/cat4_4-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 480 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 486 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 492 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 502 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 508 "gen/ragel/cat4_4-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a3 = p; }
					
#line 514 "gen/ragel/cat4_4-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 520 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b0 = p; }
					
#line 530 "gen/ragel/cat4_4-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a1 = p; }
					
#line 536 "gen/ragel/cat4_4-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 542 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 548 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 554 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 564 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 570 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 576 "gen/ragel/cat4_4-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a3 = p; }
					
#line 582 "gen/ragel/cat4_4-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 588 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a1 = p; }
					
#line 598 "gen/ragel/cat4_4-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 604 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 610 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 616 "gen/ragel/cat4_4-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a3 = p; }
					
#line 622 "gen/ragel/cat4_4-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 628 "gen/ragel/cat4_4-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b0 = p; }
					
#line 638 "gen/ragel/cat4_4-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a1 = p; }
					
#line 644 "gen/ragel/cat4_4-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b1 = p; }
					
#line 650 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a2 = p; }
					
#line 656 "gen/ragel/cat4_4-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b2 = p; }
					
#line 662 "gen/ragel/cat4_4-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						a3 = p; }
					
#line 668 "gen/ragel/cat4_4-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_4.rl"
						b3 = p; }
					
#line 674 "gen/ragel/cat4_4-T1.c"
					
					
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
