#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"



#line 12 "gen/ragel/cat2_4-T1.c"
static const signed char _abcd_key_offsets[] = {
	0, 0, 1, 2, 3, 5, 7, 9,
	11, 14, 17, 18, 19, 20, 23, 25,
	27, 0
};

static const char _abcd_trans_keys[] = {
	97, 97, 97, 97, 98, 97, 98, 97,
	98, 97, 98, 10, 97, 98, 10, 97,
	98, 97, 97, 97, 10, 97, 98, 10,
	98, 97, 98, 97, 0
};

static const signed char _abcd_single_lengths[] = {
	0, 1, 1, 1, 2, 2, 2, 2,
	3, 3, 1, 1, 1, 3, 2, 2,
	1, 0
};

static const signed char _abcd_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0
};

static const signed char _abcd_index_offsets[] = {
	0, 0, 2, 4, 6, 9, 12, 15,
	18, 22, 26, 28, 30, 32, 36, 39,
	42, 0
};

static const signed char _abcd_cond_targs[] = {
	2, 0, 3, 0, 4, 0, 5, 15,
	0, 6, 15, 0, 7, 15, 0, 8,
	15, 0, 16, 8, 9, 0, 16, 10,
	9, 0, 11, 0, 12, 0, 13, 0,
	16, 13, 14, 0, 16, 14, 0, 10,
	15, 0, 1, 0, 0, 1, 2, 3,
	4, 5, 6, 7, 8, 9, 10, 11,
	12, 13, 14, 15, 16, 0
};

static const signed char _abcd_cond_actions[] = {
	1, 0, 1, 0, 1, 0, 2, 0,
	0, 2, 0, 0, 2, 0, 0, 2,
	0, 0, 3, 2, 0, 0, 3, 4,
	0, 0, 5, 0, 5, 0, 5, 0,
	3, 5, 0, 0, 3, 0, 0, 4,
	0, 0, 6, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};

static const int abcd_start = 16;
static const int abcd_first_final = 16;
static const int abcd_error = 0;

static const int abcd_en_main = 16;


#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1,
	*b0, *b1;
	int cs;
	
	
#line 86 "gen/ragel/cat2_4-T1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
	
	
#line 94 "gen/ragel/cat2_4-T1.c"
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						b0 = p; }
					
#line 163 "gen/ragel/cat2_4-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						b1 = p; }
					
#line 173 "gen/ragel/cat2_4-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
					}
					
#line 186 "gen/ragel/cat2_4-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						a0 = p; }
					
#line 196 "gen/ragel/cat2_4-T1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						b0 = p; }
					
#line 202 "gen/ragel/cat2_4-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						a1 = p; }
					
#line 212 "gen/ragel/cat2_4-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						b1 = p; }
					
#line 218 "gen/ragel/cat2_4-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						b0 = p; }
					
#line 228 "gen/ragel/cat2_4-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						a1 = p; }
					
#line 234 "gen/ragel/cat2_4-T1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						b1 = p; }
					
#line 240 "gen/ragel/cat2_4-T1.c"
					
					
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
	
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
