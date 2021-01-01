#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"



#line 12 "gen/ragel/cat8_0-T1.c"
static const signed char _abcd_key_offsets[] = {
	0, 0, 3, 6, 9, 12, 15, 18,
	21, 24, 27, 30, 33, 36, 39, 42,
	45, 47, 0
};

static const char _abcd_trans_keys[] = {
	10, 97, 98, 10, 97, 98, 10, 97,
	98, 10, 97, 98, 10, 97, 98, 10,
	97, 98, 10, 97, 98, 10, 97, 98,
	10, 97, 98, 10, 97, 98, 10, 97,
	98, 10, 97, 98, 10, 97, 98, 10,
	97, 98, 10, 97, 98, 10, 98, 10,
	97, 98, 0
};

static const signed char _abcd_single_lengths[] = {
	0, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	2, 3, 0
};

static const signed char _abcd_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _abcd_index_offsets[] = {
	0, 0, 4, 8, 12, 16, 20, 24,
	28, 32, 36, 40, 44, 48, 52, 56,
	60, 63, 0
};

static const signed char _abcd_cond_targs[] = {
	17, 1, 2, 0, 17, 3, 2, 0,
	17, 3, 4, 0, 17, 5, 4, 0,
	17, 5, 6, 0, 17, 7, 6, 0,
	17, 7, 8, 0, 17, 9, 8, 0,
	17, 9, 10, 0, 17, 11, 10, 0,
	17, 11, 12, 0, 17, 13, 12, 0,
	17, 13, 14, 0, 17, 15, 14, 0,
	17, 15, 16, 0, 17, 16, 0, 17,
	1, 2, 0, 0, 1, 2, 3, 4,
	5, 6, 7, 8, 9, 10, 11, 12,
	13, 14, 15, 16, 17, 0
};

static const signed char _abcd_cond_actions[] = {
	1, 2, 3, 0, 4, 5, 6, 0,
	7, 8, 9, 0, 10, 11, 12, 0,
	13, 14, 15, 0, 16, 17, 18, 0,
	19, 20, 21, 0, 22, 23, 24, 0,
	25, 26, 27, 0, 28, 29, 30, 0,
	31, 32, 33, 0, 34, 35, 36, 0,
	37, 38, 39, 0, 40, 41, 42, 0,
	43, 0, 44, 0, 45, 0, 0, 46,
	47, 48, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
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
	
	
#line 95 "gen/ragel/cat8_0-T1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
	
	
#line 103 "gen/ragel/cat8_0-T1.c"
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
				case 41:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 172 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 44:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 182 "gen/ragel/cat8_0-T1.c"
					
					
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
					
#line 201 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 38:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 211 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 217 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 42:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 227 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 233 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 43:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 243 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 258 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 35:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 268 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 274 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 280 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 39:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 290 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 296 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 302 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 40:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 312 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 318 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 333 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 32:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 343 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 349 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 355 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 361 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 36:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 371 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 377 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 383 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 389 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 37:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 399 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 405 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 411 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 426 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 29:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 436 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 442 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 448 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 454 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 460 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 33:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 470 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 476 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 482 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 488 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 494 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 34:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 504 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 510 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 516 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 522 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 537 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 26:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 547 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 553 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 559 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 565 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 571 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 577 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 30:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 587 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 593 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 599 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 605 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 611 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 617 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 31:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 627 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 633 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 639 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 645 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 651 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 666 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 676 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 682 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 688 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 694 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 700 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 706 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 712 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 27:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 722 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 728 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 734 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 740 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 746 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 752 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 758 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 28:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 768 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 774 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 780 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 786 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 792 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 798 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 813 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 823 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 829 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 835 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 841 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 847 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 853 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 859 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 865 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 875 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 881 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 887 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 893 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 899 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 905 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 911 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 917 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 927 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 933 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 939 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 945 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 951 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 957 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 963 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 978 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 988 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 994 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1000 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1006 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1012 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1018 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1024 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1030 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1036 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1046 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1052 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1058 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1064 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1070 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1076 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1082 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1088 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1094 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1104 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1110 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1116 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1122 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1128 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1134 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1140 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1146 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 1161 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1171 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1177 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1183 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1189 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1195 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1201 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1207 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1213 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1219 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1225 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1235 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1241 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1247 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1253 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1259 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1265 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1271 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1277 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1283 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1289 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1299 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1305 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1311 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1317 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1323 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1329 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1335 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1341 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1347 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 1362 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 1372 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1378 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1384 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1390 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1396 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1402 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1408 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1414 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1420 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1426 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1432 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1442 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1448 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1454 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1460 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1466 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1472 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1478 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1484 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1490 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1496 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1502 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1512 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1518 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1524 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1530 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1536 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1542 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1548 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1554 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1560 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1566 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 1581 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 1591 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 1597 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1603 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1609 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1615 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1621 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1627 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1633 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1639 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1645 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1651 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1657 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 1667 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1673 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1679 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1685 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1691 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1697 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1703 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1709 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1715 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1721 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1727 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1733 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1743 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1749 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1755 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1761 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1767 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1773 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1779 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1785 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1791 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1797 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1803 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 1818 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 1828 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 1834 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 1840 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1846 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1852 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1858 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1864 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1870 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1876 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1882 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1888 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1894 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1900 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 1910 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 1916 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1922 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 1928 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 1934 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 1940 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 1946 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 1952 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 1958 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 1964 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 1970 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 1976 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 1982 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 1992 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 1998 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2004 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2010 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2016 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2022 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2028 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2034 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2040 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2046 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2052 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2058 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 2073 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b0 = p; }
					
#line 2083 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2089 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2095 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2101 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2107 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2113 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2119 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2125 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2131 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2137 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2143 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2149 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2155 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2161 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2171 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2177 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2183 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2189 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2195 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2201 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2207 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2213 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2219 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2225 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2231 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2237 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2243 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2249 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2259 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2265 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2271 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2277 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2283 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2289 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2295 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2301 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2307 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2313 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2319 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2325 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2331 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 2346 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 47:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a0 = p; }
					
#line 2356 "gen/ragel/cat8_0-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b0 = p; }
					
#line 2362 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2368 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2374 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2380 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2386 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2392 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2398 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2404 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2410 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2416 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2422 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2428 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2434 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2440 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b0 = p; }
					
#line 2450 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2456 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2462 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2468 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2474 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2480 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2486 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2492 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2498 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2504 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2510 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2516 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2522 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2528 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2534 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2544 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2550 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2556 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2562 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2568 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2574 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2580 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2586 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2592 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2598 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2604 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2610 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2616 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2622 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 2637 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 48:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a0 = p; }
					
#line 2647 "gen/ragel/cat8_0-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b0 = p; }
					
#line 2653 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2659 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2665 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2671 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2677 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2683 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2689 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2695 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2701 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2707 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2713 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2719 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2725 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2731 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2737 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b0 = p; }
					
#line 2747 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2753 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2759 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2765 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2771 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2777 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2783 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2789 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2795 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2801 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2807 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2813 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2819 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2825 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2831 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 2846 "gen/ragel/cat8_0-T1.c"
					
					
					break; 
				}
				case 46:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a0 = p; }
					
#line 2856 "gen/ragel/cat8_0-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b0 = p; }
					
#line 2862 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a1 = p; }
					
#line 2868 "gen/ragel/cat8_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b1 = p; }
					
#line 2874 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a2 = p; }
					
#line 2880 "gen/ragel/cat8_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b2 = p; }
					
#line 2886 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a3 = p; }
					
#line 2892 "gen/ragel/cat8_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b3 = p; }
					
#line 2898 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a4 = p; }
					
#line 2904 "gen/ragel/cat8_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b4 = p; }
					
#line 2910 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a5 = p; }
					
#line 2916 "gen/ragel/cat8_0-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b5 = p; }
					
#line 2922 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a6 = p; }
					
#line 2928 "gen/ragel/cat8_0-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b6 = p; }
					
#line 2934 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						a7 = p; }
					
#line 2940 "gen/ragel/cat8_0-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_0.rl"
						b7 = p; }
					
#line 2946 "gen/ragel/cat8_0-T1.c"
					
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
					
#line 2961 "gen/ragel/cat8_0-T1.c"
					
					
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
