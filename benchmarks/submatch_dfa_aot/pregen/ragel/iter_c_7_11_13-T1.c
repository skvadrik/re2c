#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_c_7_11_13.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_c_7_11_13.rl"



#line 12 "gen/ragel/iter_c_7_11_13-T1.c"
static const signed char _aaa_key_offsets[] = {
	0, 0, 1, 2, 3, 4, 5, 6,
	7, 8, 9, 10, 11, 12, 14, 0
};

static const char _aaa_trans_keys[] = {
	97, 97, 97, 97, 97, 97, 97, 97,
	97, 97, 97, 97, 10, 97, 10, 97,
	0
};

static const signed char _aaa_single_lengths[] = {
	0, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 2, 2, 0
};

static const signed char _aaa_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

static const signed char _aaa_index_offsets[] = {
	0, 0, 2, 4, 6, 8, 10, 12,
	14, 16, 18, 20, 22, 24, 27, 0
};

static const signed char _aaa_cond_targs[] = {
	2, 0, 3, 0, 4, 0, 5, 0,
	6, 0, 7, 0, 8, 0, 9, 0,
	10, 0, 11, 0, 12, 0, 13, 0,
	14, 1, 0, 14, 1, 0, 0, 1,
	2, 3, 4, 5, 6, 7, 8, 9,
	10, 11, 12, 13, 14, 0
};

static const signed char _aaa_cond_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 2, 0, 3, 4, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};

static const int aaa_start = 14;
static const int aaa_first_final = 14;
static const int aaa_error = 0;

static const int aaa_en_main = 14;


#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_c_7_11_13.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *s;
	int cs;
	
	
#line 75 "gen/ragel/iter_c_7_11_13-T1.c"
	{
		cs = (int)aaa_start;
	}
	
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_c_7_11_13.rl"
	
	
#line 83 "gen/ragel/iter_c_7_11_13-T1.c"
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
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_c_7_11_13.rl"
						
						outs(out, s, p);
						outc(out, '.');
						s = p;
					}
					
#line 156 "gen/ragel/iter_c_7_11_13-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_c_7_11_13.rl"
						s = p; }
					
#line 166 "gen/ragel/iter_c_7_11_13-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_c_7_11_13.rl"
						
						outs(out, s, p);
						outc(out, '.');
						s = p;
					}
					
#line 180 "gen/ragel/iter_c_7_11_13-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_c_7_11_13.rl"
						outc(out, '\n'); }
					
#line 186 "gen/ragel/iter_c_7_11_13-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_c_7_11_13.rl"
						s = p; }
					
#line 196 "gen/ragel/iter_c_7_11_13-T1.c"
					
					{
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_c_7_11_13.rl"
						outc(out, '\n'); }
					
#line 202 "gen/ragel/iter_c_7_11_13-T1.c"
					
					
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
	
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_c_7_11_13.rl"
	
	
	in->p = p;
	in->pe = pe;
}
