#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_b_2_3_5.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_b_2_3_5.rl"



#line 12 "gen/ragel/iter_b_2_3_5-T1.c"
static const signed char _aaa_key_offsets[] = {
	0, 0, 1, 3, 5, 6, 8, 0
};

static const char _aaa_trans_keys[] = {
	97, 10, 97, 10, 97, 97, 10, 97,
	10, 97, 0
};

static const signed char _aaa_single_lengths[] = {
	0, 1, 2, 2, 1, 2, 2, 0
};

static const signed char _aaa_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0
};

static const signed char _aaa_index_offsets[] = {
	0, 0, 2, 5, 8, 10, 13, 0
};

static const signed char _aaa_cond_targs[] = {
	2, 0, 6, 3, 0, 6, 4, 0,
	5, 0, 6, 1, 0, 6, 1, 0,
	0, 1, 2, 3, 4, 5, 6, 0
};

static const signed char _aaa_cond_actions[] = {
	0, 0, 1, 0, 0, 1, 0, 0,
	0, 0, 1, 2, 0, 3, 4, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

static const int aaa_start = 6;
static const int aaa_first_final = 6;
static const int aaa_error = 0;

static const int aaa_en_main = 6;


#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_b_2_3_5.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *s;
	int cs;
	
	
#line 64 "gen/ragel/iter_b_2_3_5-T1.c"
	{
		cs = (int)aaa_start;
	}
	
#line 32 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_b_2_3_5.rl"
	
	
#line 72 "gen/ragel/iter_b_2_3_5-T1.c"
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
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_b_2_3_5.rl"
						
						outs(out, s, p);
						outc(out, '.');
						s = p;
					}
					
#line 145 "gen/ragel/iter_b_2_3_5-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_b_2_3_5.rl"
						s = p; }
					
#line 155 "gen/ragel/iter_b_2_3_5-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_b_2_3_5.rl"
						
						outs(out, s, p);
						outc(out, '.');
						s = p;
					}
					
#line 169 "gen/ragel/iter_b_2_3_5-T1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_b_2_3_5.rl"
						outc(out, '\n'); }
					
#line 175 "gen/ragel/iter_b_2_3_5-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_b_2_3_5.rl"
						s = p; }
					
#line 185 "gen/ragel/iter_b_2_3_5-T1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_b_2_3_5.rl"
						outc(out, '\n'); }
					
#line 191 "gen/ragel/iter_b_2_3_5-T1.c"
					
					
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
	
#line 33 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_b_2_3_5.rl"
	
	
	in->p = p;
	in->pe = pe;
}
