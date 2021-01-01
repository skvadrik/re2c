#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"



#line 12 "gen/ragel/cat2_0-T1.c"
static const signed char _abcd_key_offsets[] = {
	0, 0, 3, 6, 9, 11, 0
};

static const char _abcd_trans_keys[] = {
	10, 97, 98, 10, 97, 98, 10, 97,
	98, 10, 98, 10, 97, 98, 0
};

static const signed char _abcd_single_lengths[] = {
	0, 3, 3, 3, 2, 3, 0
};

static const signed char _abcd_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0
};

static const signed char _abcd_index_offsets[] = {
	0, 0, 4, 8, 12, 15, 0
};

static const signed char _abcd_cond_targs[] = {
	5, 1, 2, 0, 5, 3, 2, 0,
	5, 3, 4, 0, 5, 4, 0, 5,
	1, 2, 0, 0, 1, 2, 3, 4,
	5, 0
};

static const signed char _abcd_cond_actions[] = {
	1, 2, 3, 0, 4, 5, 6, 0,
	7, 0, 8, 0, 9, 0, 0, 10,
	11, 12, 0, 0, 0, 0, 0, 0,
	0, 0
};

static const int abcd_start = 5;
static const int abcd_first_final = 5;
static const int abcd_error = 0;

static const int abcd_en_main = 5;


#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1,
	*b0, *b1;
	int cs;
	
	
#line 68 "gen/ragel/cat2_0-T1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
	
	
#line 76 "gen/ragel/cat2_0-T1.c"
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
				case 5:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 145 "gen/ragel/cat2_0-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 155 "gen/ragel/cat2_0-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
					}
					
#line 168 "gen/ragel/cat2_0-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b0 = p; }
					
#line 178 "gen/ragel/cat2_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 184 "gen/ragel/cat2_0-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 194 "gen/ragel/cat2_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 200 "gen/ragel/cat2_0-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 210 "gen/ragel/cat2_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
					}
					
#line 219 "gen/ragel/cat2_0-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a0 = p; }
					
#line 229 "gen/ragel/cat2_0-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b0 = p; }
					
#line 235 "gen/ragel/cat2_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 241 "gen/ragel/cat2_0-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b0 = p; }
					
#line 251 "gen/ragel/cat2_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 257 "gen/ragel/cat2_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 263 "gen/ragel/cat2_0-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 273 "gen/ragel/cat2_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 279 "gen/ragel/cat2_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
					}
					
#line 288 "gen/ragel/cat2_0-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a0 = p; }
					
#line 298 "gen/ragel/cat2_0-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b0 = p; }
					
#line 304 "gen/ragel/cat2_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 310 "gen/ragel/cat2_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 316 "gen/ragel/cat2_0-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b0 = p; }
					
#line 326 "gen/ragel/cat2_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 332 "gen/ragel/cat2_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 338 "gen/ragel/cat2_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
					}
					
#line 347 "gen/ragel/cat2_0-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a0 = p; }
					
#line 357 "gen/ragel/cat2_0-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b0 = p; }
					
#line 363 "gen/ragel/cat2_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 369 "gen/ragel/cat2_0-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 375 "gen/ragel/cat2_0-T1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
					}
					
#line 384 "gen/ragel/cat2_0-T1.c"
					
					
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
	
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
	
	
	in->p = p;
	in->pe = pe;
}
