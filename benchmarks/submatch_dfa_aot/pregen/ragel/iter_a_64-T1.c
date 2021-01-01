#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"



#line 12 "gen/ragel/iter_a_64-T1.c"
static const signed char _aaa_key_offsets[] = {
	0, 0, 1, 2, 3, 4, 5, 6,
	7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 28, 29, 30,
	31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46,
	47, 48, 49, 50, 51, 52, 53, 54,
	55, 56, 57, 58, 59, 60, 61, 62,
	63, 65, 0
};

static const char _aaa_trans_keys[] = {
	97, 97, 97, 97, 97, 97, 97, 97,
	97, 97, 97, 97, 97, 97, 97, 97,
	97, 97, 97, 97, 97, 97, 97, 97,
	97, 97, 97, 97, 97, 97, 97, 97,
	97, 97, 97, 97, 97, 97, 97, 97,
	97, 97, 97, 97, 97, 97, 97, 97,
	97, 97, 97, 97, 97, 97, 97, 97,
	97, 97, 97, 97, 97, 97, 97, 10,
	97, 10, 97, 0
};

static const signed char _aaa_single_lengths[] = {
	0, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 0
};

static const signed char _aaa_range_lengths[] = {
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

static const short _aaa_index_offsets[] = {
	0, 0, 2, 4, 6, 8, 10, 12,
	14, 16, 18, 20, 22, 24, 26, 28,
	30, 32, 34, 36, 38, 40, 42, 44,
	46, 48, 50, 52, 54, 56, 58, 60,
	62, 64, 66, 68, 70, 72, 74, 76,
	78, 80, 82, 84, 86, 88, 90, 92,
	94, 96, 98, 100, 102, 104, 106, 108,
	110, 112, 114, 116, 118, 120, 122, 124,
	126, 129, 0
};

static const signed char _aaa_cond_targs[] = {
	2, 0, 3, 0, 4, 0, 5, 0,
	6, 0, 7, 0, 8, 0, 9, 0,
	10, 0, 11, 0, 12, 0, 13, 0,
	14, 0, 15, 0, 16, 0, 17, 0,
	18, 0, 19, 0, 20, 0, 21, 0,
	22, 0, 23, 0, 24, 0, 25, 0,
	26, 0, 27, 0, 28, 0, 29, 0,
	30, 0, 31, 0, 32, 0, 33, 0,
	34, 0, 35, 0, 36, 0, 37, 0,
	38, 0, 39, 0, 40, 0, 41, 0,
	42, 0, 43, 0, 44, 0, 45, 0,
	46, 0, 47, 0, 48, 0, 49, 0,
	50, 0, 51, 0, 52, 0, 53, 0,
	54, 0, 55, 0, 56, 0, 57, 0,
	58, 0, 59, 0, 60, 0, 61, 0,
	62, 0, 63, 0, 64, 0, 65, 1,
	0, 65, 1, 0, 0, 1, 2, 3,
	4, 5, 6, 7, 8, 9, 10, 11,
	12, 13, 14, 15, 16, 17, 18, 19,
	20, 21, 22, 23, 24, 25, 26, 27,
	28, 29, 30, 31, 32, 33, 34, 35,
	36, 37, 38, 39, 40, 41, 42, 43,
	44, 45, 46, 47, 48, 49, 50, 51,
	52, 53, 54, 55, 56, 57, 58, 59,
	60, 61, 62, 63, 64, 65, 0
};

static const signed char _aaa_cond_actions[] = {
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
	0, 0, 0, 0, 0, 0, 1, 2,
	0, 3, 4, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0
};

static const int aaa_start = 65;
static const int aaa_first_final = 65;
static const int aaa_error = 0;

static const int aaa_en_main = 65;


#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *s;
	int cs;
	
	
#line 147 "gen/ragel/iter_a_64-T1.c"
	{
		cs = (int)aaa_start;
	}
	
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
	
	
#line 155 "gen/ragel/iter_a_64-T1.c"
	{
		int _klen;
		unsigned int _trans = 0;
		const char * _keys;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _aaa_trans_keys + (_aaa_key_offsets[cs]));
		_trans = (unsigned int)_aaa_index_offsets[cs];
		
		_klen = (int)_aaa_single_lengths[cs];
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
		
		_klen = (int)_aaa_range_lengths[cs];
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
		cs = (int)_aaa_cond_targs[_trans];
		
		if ( _aaa_cond_actions[_trans] != 0 ) {
			
			switch ( _aaa_cond_actions[_trans] ) {
				case 2:  {
					{
#line 8 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
						
						outs(out, s, p);
						outc(out, '.');
						s = p;
					}
					
#line 228 "gen/ragel/iter_a_64-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
						s = p; }
					
#line 238 "gen/ragel/iter_a_64-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 8 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
						
						outs(out, s, p);
						outc(out, '.');
						s = p;
					}
					
#line 252 "gen/ragel/iter_a_64-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
						outc(out, '\n'); }
					
#line 258 "gen/ragel/iter_a_64-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
						s = p; }
					
#line 268 "gen/ragel/iter_a_64-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
						outc(out, '\n'); }
					
#line 274 "gen/ragel/iter_a_64-T1.c"
					
					
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
	
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
	
	
	in->p = p;
	in->pe = pe;
}
