#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"



#line 12 "gen/ragel/ipv4-T1.c"
static const signed char _ipv4_key_offsets[] = {
	0, 0, 3, 5, 8, 10, 13, 15,
	18, 21, 22, 25, 26, 29, 30, 33,
	34, 0
};

static const char _ipv4_trans_keys[] = {
	46, 48, 57, 48, 57, 46, 48, 57,
	48, 57, 46, 48, 57, 48, 57, 10,
	48, 57, 10, 48, 57, 10, 46, 48,
	57, 46, 46, 48, 57, 46, 46, 48,
	57, 46, 48, 57, 0
};

static const signed char _ipv4_single_lengths[] = {
	0, 1, 0, 1, 0, 1, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	0, 0
};

static const signed char _ipv4_range_lengths[] = {
	0, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 1, 0, 1, 0,
	1, 0
};

static const signed char _ipv4_index_offsets[] = {
	0, 0, 3, 5, 8, 10, 13, 15,
	18, 21, 23, 26, 28, 31, 33, 36,
	38, 0
};

static const signed char _ipv4_cond_targs[] = {
	2, 14, 0, 3, 0, 4, 12, 0,
	5, 0, 6, 10, 0, 7, 0, 16,
	8, 0, 16, 9, 0, 16, 0, 6,
	11, 0, 6, 0, 4, 13, 0, 4,
	0, 2, 15, 0, 2, 0, 1, 0,
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 9, 10, 11, 12, 13, 14, 15,
	16, 0
};

static const signed char _ipv4_cond_actions[] = {
	0, 0, 0, 1, 0, 0, 0, 0,
	2, 0, 0, 0, 0, 3, 0, 4,
	0, 0, 4, 0, 0, 4, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 5, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0
};

static const int ipv4_start = 16;
static const int ipv4_first_final = 16;
static const int ipv4_error = 0;

static const int ipv4_en_main = 16;


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *p1, *p2, *p3, *p4;
	int cs;
	
	
#line 85 "gen/ragel/ipv4-T1.c"
	{
		cs = (int)ipv4_start;
	}
	
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
	
	
#line 93 "gen/ragel/ipv4-T1.c"
	{
		int _klen;
		unsigned int _trans = 0;
		const char * _keys;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _ipv4_trans_keys + (_ipv4_key_offsets[cs]));
		_trans = (unsigned int)_ipv4_index_offsets[cs];
		
		_klen = (int)_ipv4_single_lengths[cs];
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
		
		_klen = (int)_ipv4_range_lengths[cs];
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
		cs = (int)_ipv4_cond_targs[_trans];
		
		if ( _ipv4_cond_actions[_trans] != 0 ) {
			
			switch ( _ipv4_cond_actions[_trans] ) {
				case 5:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
						p1 = p; }
					
#line 162 "gen/ragel/ipv4-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
						p2 = p; }
					
#line 172 "gen/ragel/ipv4-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
						p3 = p; }
					
#line 182 "gen/ragel/ipv4-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
						p4 = p; }
					
#line 192 "gen/ragel/ipv4-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
						
						outs(out, p1, p2 - 1);
						outc(out, ',');
						outs(out, p2, p3 - 1);
						outc(out, ',');
						outs(out, p3, p4 - 1);
						outc(out, ',');
						outs(out, p4, p);
						outc(out, '\n');
					}
					
#line 211 "gen/ragel/ipv4-T1.c"
					
					
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
	
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
