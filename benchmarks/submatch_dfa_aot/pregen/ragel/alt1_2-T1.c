#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"



#line 13 "gen/ragel/alt1_2-T1.c"
static const signed char _m_key_offsets[] = {
	0, 0, 2, 4, 0
};

static const char _m_trans_keys[] = {
	10, 97, 10, 98, 10, 97, 98, 0
};

static const signed char _m_single_lengths[] = {
	0, 2, 2, 3, 0
};

static const signed char _m_range_lengths[] = {
	0, 0, 0, 0, 0
};

static const signed char _m_index_offsets[] = {
	0, 0, 3, 6, 0
};

static const signed char _m_cond_targs[] = {
	3, 1, 0, 3, 2, 0, 3, 1,
	2, 0, 0, 1, 2, 3, 0
};

static const signed char _m_cond_actions[] = {
	1, 0, 0, 2, 0, 0, 3, 4,
	5, 0, 0, 0, 0, 0, 0
};

static const int m_start = 3;
static const int m_first_final = 3;
static const int m_error = 0;

static const int m_en_main = 3;


#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1,
	*a2, *b2;
	int cs;
	
	
#line 64 "gen/ragel/alt1_2-T1.c"
	{
		cs = (int)m_start;
	}
	
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
	
	
#line 72 "gen/ragel/alt1_2-T1.c"
	{
		int _klen;
		unsigned int _trans = 0;
		const char * _keys;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _m_trans_keys + (_m_key_offsets[cs]));
		_trans = (unsigned int)_m_index_offsets[cs];
		
		_klen = (int)_m_single_lengths[cs];
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
		
		_klen = (int)_m_range_lengths[cs];
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
		cs = (int)_m_cond_targs[_trans];
		
		if ( _m_cond_actions[_trans] != 0 ) {
			
			switch ( _m_cond_actions[_trans] ) {
				case 5:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						b1 = p; }
					
#line 141 "gen/ragel/alt1_2-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						a1 = p; }
					
#line 151 "gen/ragel/alt1_2-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 161 "gen/ragel/alt1_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						outc(out, '\n');
					}
					
#line 171 "gen/ragel/alt1_2-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 181 "gen/ragel/alt1_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						outc(out, '\n');
					}
					
#line 191 "gen/ragel/alt1_2-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						b1 = p; }
					
#line 201 "gen/ragel/alt1_2-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 207 "gen/ragel/alt1_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						a1 = p; }
					
#line 213 "gen/ragel/alt1_2-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 219 "gen/ragel/alt1_2-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						outc(out, '\n');
					}
					
#line 229 "gen/ragel/alt1_2-T1.c"
					
					
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
	
#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
	
	
	in->p = p;
	in->pe = pe;
}
