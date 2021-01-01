#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"



#line 12 "gen/ragel/cat4_2-T1.c"
static const signed char _abcd_key_offsets[] = {
	0, 0, 1, 3, 5, 7, 9, 11,
	13, 16, 19, 20, 23, 26, 27, 30,
	33, 34, 37, 39, 41, 43, 44, 46,
	48, 50, 52, 53, 55, 57, 59, 60,
	62, 64, 66, 0
};

static const char _abcd_trans_keys[] = {
	97, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 10, 97, 98,
	10, 97, 98, 97, 10, 97, 98, 10,
	97, 98, 97, 10, 97, 98, 10, 97,
	98, 97, 10, 97, 98, 10, 98, 97,
	98, 97, 98, 97, 97, 98, 97, 98,
	97, 98, 97, 98, 97, 97, 98, 97,
	98, 97, 98, 97, 97, 98, 97, 98,
	97, 98, 97, 0
};

static const signed char _abcd_single_lengths[] = {
	0, 1, 2, 2, 2, 2, 2, 2,
	3, 3, 1, 3, 3, 1, 3, 3,
	1, 3, 2, 2, 2, 1, 2, 2,
	2, 2, 1, 2, 2, 2, 1, 2,
	2, 2, 1, 0
};

static const signed char _abcd_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0
};

static const signed char _abcd_index_offsets[] = {
	0, 0, 2, 5, 8, 11, 14, 17,
	20, 24, 28, 30, 34, 38, 40, 44,
	48, 50, 54, 57, 60, 63, 65, 68,
	71, 74, 77, 79, 82, 85, 88, 90,
	93, 96, 99, 0
};

static const signed char _abcd_cond_targs[] = {
	2, 0, 3, 25, 0, 4, 25, 0,
	5, 20, 0, 6, 20, 0, 7, 19,
	0, 8, 19, 0, 34, 8, 9, 0,
	34, 10, 9, 0, 11, 0, 34, 11,
	12, 0, 34, 13, 12, 0, 14, 0,
	34, 14, 15, 0, 34, 16, 15, 0,
	17, 0, 34, 17, 18, 0, 34, 18,
	0, 10, 19, 0, 21, 20, 0, 22,
	0, 23, 24, 0, 11, 24, 0, 13,
	24, 0, 26, 25, 0, 27, 0, 28,
	29, 0, 22, 29, 0, 30, 29, 0,
	31, 0, 32, 33, 0, 14, 33, 0,
	16, 33, 0, 1, 0, 0, 1, 2,
	3, 4, 5, 6, 7, 8, 9, 10,
	11, 12, 13, 14, 15, 16, 17, 18,
	19, 20, 21, 22, 23, 24, 25, 26,
	27, 28, 29, 30, 31, 32, 33, 34,
	0
};

static const signed char _abcd_cond_actions[] = {
	1, 0, 2, 0, 0, 2, 0, 0,
	3, 0, 0, 3, 0, 0, 4, 0,
	0, 4, 0, 0, 5, 4, 0, 0,
	5, 6, 0, 0, 7, 0, 5, 8,
	0, 0, 5, 9, 0, 0, 10, 0,
	5, 11, 0, 0, 5, 12, 0, 0,
	13, 0, 5, 13, 0, 0, 5, 0,
	0, 6, 0, 0, 14, 0, 0, 15,
	0, 8, 0, 0, 8, 0, 0, 9,
	0, 0, 16, 0, 0, 17, 0, 18,
	0, 0, 18, 0, 0, 19, 0, 0,
	20, 0, 11, 0, 0, 11, 0, 0,
	12, 0, 0, 21, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0
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
	
	
#line 119 "gen/ragel/cat4_2-T1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
	
	
#line 127 "gen/ragel/cat4_2-T1.c"
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b0 = p; }
					
#line 196 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 206 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 216 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 226 "gen/ragel/cat4_2-T1.c"
					
					
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
					
#line 241 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a0 = p; }
					
#line 251 "gen/ragel/cat4_2-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b0 = p; }
					
#line 257 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a1 = p; }
					
#line 267 "gen/ragel/cat4_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 273 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 283 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 289 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 299 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 305 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 315 "gen/ragel/cat4_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 321 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a3 = p; }
					
#line 331 "gen/ragel/cat4_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 337 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b0 = p; }
					
#line 347 "gen/ragel/cat4_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a1 = p; }
					
#line 353 "gen/ragel/cat4_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 359 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 369 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 375 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 381 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 391 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 397 "gen/ragel/cat4_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 403 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 413 "gen/ragel/cat4_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a3 = p; }
					
#line 419 "gen/ragel/cat4_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 425 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a1 = p; }
					
#line 435 "gen/ragel/cat4_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 441 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 447 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 453 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 463 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 469 "gen/ragel/cat4_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a3 = p; }
					
#line 475 "gen/ragel/cat4_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 481 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b0 = p; }
					
#line 491 "gen/ragel/cat4_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a1 = p; }
					
#line 497 "gen/ragel/cat4_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 503 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 509 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 515 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 525 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 531 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 537 "gen/ragel/cat4_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a3 = p; }
					
#line 543 "gen/ragel/cat4_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 549 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a1 = p; }
					
#line 559 "gen/ragel/cat4_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 565 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 571 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 577 "gen/ragel/cat4_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a3 = p; }
					
#line 583 "gen/ragel/cat4_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 589 "gen/ragel/cat4_2-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b0 = p; }
					
#line 599 "gen/ragel/cat4_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a1 = p; }
					
#line 605 "gen/ragel/cat4_2-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b1 = p; }
					
#line 611 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a2 = p; }
					
#line 617 "gen/ragel/cat4_2-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b2 = p; }
					
#line 623 "gen/ragel/cat4_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						a3 = p; }
					
#line 629 "gen/ragel/cat4_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat4_2.rl"
						b3 = p; }
					
#line 635 "gen/ragel/cat4_2-T1.c"
					
					
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
