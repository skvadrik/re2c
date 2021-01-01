#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"



#line 13 "gen/ragel/alt2_2-T1.c"
static const signed char _m_key_offsets[] = {
	0, 0, 3, 5, 8, 10, 0
};

static const char _m_trans_keys[] = {
	10, 97, 98, 10, 98, 10, 97, 98,
	10, 97, 10, 97, 98, 0
};

static const signed char _m_single_lengths[] = {
	0, 3, 2, 3, 2, 3, 0
};

static const signed char _m_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0
};

static const signed char _m_index_offsets[] = {
	0, 0, 4, 7, 11, 14, 0
};

static const signed char _m_cond_targs[] = {
	5, 1, 2, 0, 5, 2, 0, 5,
	4, 3, 0, 5, 4, 0, 5, 1,
	3, 0, 0, 1, 2, 3, 4, 5,
	0
};

static const signed char _m_cond_actions[] = {
	1, 0, 2, 0, 3, 0, 0, 4,
	5, 0, 0, 6, 0, 0, 7, 8,
	9, 0, 0, 0, 0, 0, 0, 0,
	0
};

static const int m_start = 5;
static const int m_first_final = 5;
static const int m_error = 0;

static const int m_en_main = 5;


#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1,
	*a2, *b2,
	*a3, *b3,
	*a4, *b4;
	int cs;
	
	
#line 71 "gen/ragel/alt2_2-T1.c"
	{
		cs = (int)m_start;
	}
	
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
	
	
#line 79 "gen/ragel/alt2_2-T1.c"
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
				case 9:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b1 = p; }
					
#line 148 "gen/ragel/alt2_2-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a1 = p; }
					
#line 158 "gen/ragel/alt2_2-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 168 "gen/ragel/alt2_2-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a3 = p; }
					
#line 174 "gen/ragel/alt2_2-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 184 "gen/ragel/alt2_2-T1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b3 = p; }
					
#line 190 "gen/ragel/alt2_2-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 200 "gen/ragel/alt2_2-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						outc(out, '\n');
					}
					
#line 212 "gen/ragel/alt2_2-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 222 "gen/ragel/alt2_2-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						outc(out, '\n');
					}
					
#line 234 "gen/ragel/alt2_2-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 244 "gen/ragel/alt2_2-T1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b3 = p; }
					
#line 250 "gen/ragel/alt2_2-T1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 256 "gen/ragel/alt2_2-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a3 = p; }
					
#line 262 "gen/ragel/alt2_2-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 268 "gen/ragel/alt2_2-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						outc(out, '\n');
					}
					
#line 280 "gen/ragel/alt2_2-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 290 "gen/ragel/alt2_2-T1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b3 = p; }
					
#line 296 "gen/ragel/alt2_2-T1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 302 "gen/ragel/alt2_2-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a3 = p; }
					
#line 308 "gen/ragel/alt2_2-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 314 "gen/ragel/alt2_2-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						outc(out, '\n');
					}
					
#line 326 "gen/ragel/alt2_2-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b1 = p; }
					
#line 336 "gen/ragel/alt2_2-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 342 "gen/ragel/alt2_2-T1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a1 = p; }
					
#line 348 "gen/ragel/alt2_2-T1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 354 "gen/ragel/alt2_2-T1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b3 = p; }
					
#line 360 "gen/ragel/alt2_2-T1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 366 "gen/ragel/alt2_2-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a3 = p; }
					
#line 372 "gen/ragel/alt2_2-T1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 378 "gen/ragel/alt2_2-T1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						outc(out, '\n');
					}
					
#line 390 "gen/ragel/alt2_2-T1.c"
					
					
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
	
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
	
	
	in->p = p;
	in->pe = pe;
}
