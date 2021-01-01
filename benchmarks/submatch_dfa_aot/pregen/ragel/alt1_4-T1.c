#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"



#line 13 "gen/ragel/alt1_4-T1.c"
static const signed char _m_key_offsets[] = {
	0, 0, 2, 4, 6, 8, 0
};

static const char _m_trans_keys[] = {
	10, 97, 10, 98, 10, 99, 10, 100,
	10, 97, 98, 99, 100, 0
};

static const signed char _m_single_lengths[] = {
	0, 2, 2, 2, 2, 5, 0
};

static const signed char _m_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0
};

static const signed char _m_index_offsets[] = {
	0, 0, 3, 6, 9, 12, 0
};

static const signed char _m_cond_targs[] = {
	5, 1, 0, 5, 2, 0, 5, 3,
	0, 5, 4, 0, 5, 1, 2, 3,
	4, 0, 0, 1, 2, 3, 4, 5,
	0
};

static const signed char _m_cond_actions[] = {
	1, 0, 0, 2, 0, 0, 3, 0,
	0, 4, 0, 0, 5, 6, 7, 8,
	9, 0, 0, 0, 0, 0, 0, 0,
	0
};

static const int m_start = 5;
static const int m_first_final = 5;
static const int m_error = 0;

static const int m_en_main = 5;


#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1, *c1, *d1,
	*a2, *b2, *c2, *d2;
	int cs;
	
	
#line 69 "gen/ragel/alt1_4-T1.c"
	{
		cs = (int)m_start;
	}
	
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
	
	
#line 77 "gen/ragel/alt1_4-T1.c"
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
				case 7:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						b1 = p; }
					
#line 146 "gen/ragel/alt1_4-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						c1 = p; }
					
#line 156 "gen/ragel/alt1_4-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						d1 = p; }
					
#line 166 "gen/ragel/alt1_4-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						a1 = p; }
					
#line 176 "gen/ragel/alt1_4-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 186 "gen/ragel/alt1_4-T1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						outc(out, '\n');
					}
					
#line 198 "gen/ragel/alt1_4-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 208 "gen/ragel/alt1_4-T1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						outc(out, '\n');
					}
					
#line 220 "gen/ragel/alt1_4-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 230 "gen/ragel/alt1_4-T1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						outc(out, '\n');
					}
					
#line 242 "gen/ragel/alt1_4-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 252 "gen/ragel/alt1_4-T1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						outc(out, '\n');
					}
					
#line 264 "gen/ragel/alt1_4-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						b1 = p; }
					
#line 274 "gen/ragel/alt1_4-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 280 "gen/ragel/alt1_4-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						c1 = p; }
					
#line 286 "gen/ragel/alt1_4-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 292 "gen/ragel/alt1_4-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						d1 = p; }
					
#line 298 "gen/ragel/alt1_4-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 304 "gen/ragel/alt1_4-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						a1 = p; }
					
#line 310 "gen/ragel/alt1_4-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 316 "gen/ragel/alt1_4-T1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						outc(out, '\n');
					}
					
#line 328 "gen/ragel/alt1_4-T1.c"
					
					
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
	
#line 40 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
