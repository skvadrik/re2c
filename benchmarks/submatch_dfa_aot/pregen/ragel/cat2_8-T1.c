#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"



#line 12 "gen/ragel/cat2_8-T1.c"
static const signed char _abcd_key_offsets[] = {
	0, 0, 1, 2, 3, 4, 5, 6,
	7, 9, 11, 13, 15, 17, 19, 21,
	23, 26, 29, 30, 31, 32, 33, 34,
	35, 36, 39, 41, 43, 0
};

static const char _abcd_trans_keys[] = {
	97, 97, 97, 97, 97, 97, 97, 97,
	98, 97, 98, 97, 98, 97, 98, 97,
	98, 97, 98, 97, 98, 97, 98, 10,
	97, 98, 10, 97, 98, 97, 97, 97,
	97, 97, 97, 97, 10, 97, 98, 10,
	98, 97, 98, 97, 0
};

static const signed char _abcd_single_lengths[] = {
	0, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 1, 1, 1, 1, 1, 1,
	1, 3, 2, 2, 1, 0
};

static const signed char _abcd_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};

static const signed char _abcd_index_offsets[] = {
	0, 0, 2, 4, 6, 8, 10, 12,
	14, 17, 20, 23, 26, 29, 32, 35,
	38, 42, 46, 48, 50, 52, 54, 56,
	58, 60, 64, 67, 70, 0
};

static const signed char _abcd_cond_targs[] = {
	2, 0, 3, 0, 4, 0, 5, 0,
	6, 0, 7, 0, 8, 0, 9, 27,
	0, 10, 27, 0, 11, 27, 0, 12,
	27, 0, 13, 27, 0, 14, 27, 0,
	15, 27, 0, 16, 27, 0, 28, 16,
	17, 0, 28, 18, 17, 0, 19, 0,
	20, 0, 21, 0, 22, 0, 23, 0,
	24, 0, 25, 0, 28, 25, 26, 0,
	28, 26, 0, 18, 27, 0, 1, 0,
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23,
	24, 25, 26, 27, 28, 0
};

static const signed char _abcd_cond_actions[] = {
	1, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 2, 0,
	0, 2, 0, 0, 2, 0, 0, 2,
	0, 0, 2, 0, 0, 2, 0, 0,
	2, 0, 0, 2, 0, 0, 3, 2,
	0, 0, 3, 4, 0, 0, 5, 0,
	5, 0, 5, 0, 5, 0, 5, 0,
	5, 0, 5, 0, 3, 5, 0, 0,
	3, 0, 0, 4, 0, 0, 6, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};

static const int abcd_start = 28;
static const int abcd_first_final = 28;
static const int abcd_error = 0;

static const int abcd_en_main = 28;


#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1,
	*b0, *b1;
	int cs;
	
	
#line 102 "gen/ragel/cat2_8-T1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
	
	
#line 110 "gen/ragel/cat2_8-T1.c"
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						b0 = p; }
					
#line 179 "gen/ragel/cat2_8-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						b1 = p; }
					
#line 189 "gen/ragel/cat2_8-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
					}
					
#line 202 "gen/ragel/cat2_8-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						a0 = p; }
					
#line 212 "gen/ragel/cat2_8-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						b0 = p; }
					
#line 218 "gen/ragel/cat2_8-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						a1 = p; }
					
#line 228 "gen/ragel/cat2_8-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						b1 = p; }
					
#line 234 "gen/ragel/cat2_8-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						b0 = p; }
					
#line 244 "gen/ragel/cat2_8-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						a1 = p; }
					
#line 250 "gen/ragel/cat2_8-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						b1 = p; }
					
#line 256 "gen/ragel/cat2_8-T1.c"
					
					
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
	
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
	
	
	in->p = p;
	in->pe = pe;
}
