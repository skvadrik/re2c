#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"



#line 12 "gen/ragel/cat4_0-T1.c"
static const signed char _abcd_key_offsets[] = {
	0, 0, 3, 6, 9, 12, 15, 18,
	21, 23, 0
};

static const char _abcd_trans_keys[] = {
	10, 97, 98, 10, 97, 98, 10, 97,
	98, 10, 97, 98, 10, 97, 98, 10,
	97, 98, 10, 97, 98, 10, 98, 10,
	97, 98, 0
};

static const signed char _abcd_single_lengths[] = {
	0, 3, 3, 3, 3, 3, 3, 3,
	2, 3, 0
};

static const signed char _abcd_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _abcd_index_offsets[] = {
	0, 0, 4, 8, 12, 16, 20, 24,
	28, 31, 0
};

static const signed char _abcd_cond_targs[] = {
	9, 1, 2, 0, 9, 3, 2, 0,
	9, 3, 4, 0, 9, 5, 4, 0,
	9, 5, 6, 0, 9, 7, 6, 0,
	9, 7, 8, 0, 9, 8, 0, 9,
	1, 2, 0, 0, 1, 2, 3, 4,
	5, 6, 7, 8, 9, 0
};

static const signed char _abcd_cond_actions[] = {
	1, 2, 3, 0, 4, 5, 6, 0,
	7, 8, 9, 0, 10, 11, 12, 0,
	13, 14, 15, 0, 16, 17, 18, 0,
	19, 0, 20, 0, 21, 0, 0, 22,
	23, 24, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
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
	
	
#line 78 "gen/ragel/cat4_0-T1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
	
	
#line 86 "gen/ragel/cat4_0-T1.c"
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
				case 17:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 155 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 165 "gen/ragel/cat4_0-T1.c"
					
					
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
					
#line 180 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 190 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 196 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 206 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 212 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 222 "gen/ragel/cat4_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 233 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 243 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 249 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 255 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 265 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 271 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 277 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 287 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 293 "gen/ragel/cat4_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 304 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 314 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 320 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 326 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 332 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 342 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 348 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 354 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 360 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 370 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 376 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 382 "gen/ragel/cat4_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 393 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 403 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 409 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 415 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 421 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 427 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 437 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 443 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 449 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 455 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 461 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 471 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 477 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 483 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 489 "gen/ragel/cat4_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 500 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b0 = p; }
					
#line 510 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 516 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 522 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 528 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 534 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 540 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 550 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 556 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 562 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 568 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 574 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 580 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 590 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 596 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 602 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 608 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 614 "gen/ragel/cat4_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 625 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a0 = p; }
					
#line 635 "gen/ragel/cat4_0-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b0 = p; }
					
#line 641 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 647 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 653 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 659 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 665 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 671 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b0 = p; }
					
#line 681 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 687 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 693 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 699 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 705 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 711 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 717 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 727 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 733 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 739 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 745 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 751 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 757 "gen/ragel/cat4_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 768 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a0 = p; }
					
#line 778 "gen/ragel/cat4_0-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b0 = p; }
					
#line 784 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 790 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 796 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 802 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 808 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 814 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 820 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b0 = p; }
					
#line 830 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 836 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 842 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 848 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 854 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 860 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 866 "gen/ragel/cat4_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 877 "gen/ragel/cat4_0-T1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a0 = p; }
					
#line 887 "gen/ragel/cat4_0-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b0 = p; }
					
#line 893 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a1 = p; }
					
#line 899 "gen/ragel/cat4_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b1 = p; }
					
#line 905 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a2 = p; }
					
#line 911 "gen/ragel/cat4_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b2 = p; }
					
#line 917 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						a3 = p; }
					
#line 923 "gen/ragel/cat4_0-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						b3 = p; }
					
#line 929 "gen/ragel/cat4_0-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
						outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
						outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
					}
					
#line 940 "gen/ragel/cat4_0-T1.c"
					
					
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
