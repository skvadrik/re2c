#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"



#line 13 "gen/ragel/alt1_8-T1.c"
static const signed char _m_key_offsets[] = {
	0, 0, 2, 4, 6, 8, 10, 12,
	14, 16, 0
};

static const char _m_trans_keys[] = {
	10, 97, 10, 98, 10, 99, 10, 100,
	10, 101, 10, 102, 10, 103, 10, 104,
	10, 97, 98, 99, 100, 101, 102, 103,
	104, 0
};

static const signed char _m_single_lengths[] = {
	0, 2, 2, 2, 2, 2, 2, 2,
	2, 9, 0
};

static const signed char _m_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _m_index_offsets[] = {
	0, 0, 3, 6, 9, 12, 15, 18,
	21, 24, 0
};

static const signed char _m_cond_targs[] = {
	9, 1, 0, 9, 2, 0, 9, 3,
	0, 9, 4, 0, 9, 5, 0, 9,
	6, 0, 9, 7, 0, 9, 8, 0,
	9, 1, 2, 3, 4, 5, 6, 7,
	8, 0, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 0
};

static const signed char _m_cond_actions[] = {
	1, 0, 0, 2, 0, 0, 3, 0,
	0, 4, 0, 0, 5, 0, 0, 6,
	0, 0, 7, 0, 0, 8, 0, 0,
	9, 10, 11, 12, 13, 14, 15, 16,
	17, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
};

static const int m_start = 9;
static const int m_first_final = 9;
static const int m_error = 0;

static const int m_en_main = 9;


#line 36 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a1, *b1, *c1, *d1, *e1, *f1, *g1, *h1,
	*a2, *b2, *c2, *d2, *e2, *f2, *g2, *h2;
	int cs;
	
	
#line 79 "gen/ragel/alt1_8-T1.c"
	{
		cs = (int)m_start;
	}
	
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
	
	
#line 87 "gen/ragel/alt1_8-T1.c"
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
				case 11:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						b1 = p; }
					
#line 156 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						c1 = p; }
					
#line 166 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						d1 = p; }
					
#line 176 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						e1 = p; }
					
#line 186 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						f1 = p; }
					
#line 196 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						g1 = p; }
					
#line 206 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						h1 = p; }
					
#line 216 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						a1 = p; }
					
#line 226 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 236 "gen/ragel/alt1_8-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
						else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
						else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
						else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
						outc(out, '\n');
					}
					
#line 252 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 262 "gen/ragel/alt1_8-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
						else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
						else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
						else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
						outc(out, '\n');
					}
					
#line 278 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 288 "gen/ragel/alt1_8-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
						else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
						else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
						else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
						outc(out, '\n');
					}
					
#line 304 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 314 "gen/ragel/alt1_8-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
						else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
						else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
						else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
						outc(out, '\n');
					}
					
#line 330 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 340 "gen/ragel/alt1_8-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
						else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
						else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
						else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
						outc(out, '\n');
					}
					
#line 356 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 366 "gen/ragel/alt1_8-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
						else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
						else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
						else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
						outc(out, '\n');
					}
					
#line 382 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 392 "gen/ragel/alt1_8-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
						else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
						else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
						else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
						outc(out, '\n');
					}
					
#line 408 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 418 "gen/ragel/alt1_8-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
						else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
						else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
						else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
						outc(out, '\n');
					}
					
#line 434 "gen/ragel/alt1_8-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						b1 = p; }
					
#line 444 "gen/ragel/alt1_8-T1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 450 "gen/ragel/alt1_8-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						c1 = p; }
					
#line 456 "gen/ragel/alt1_8-T1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 462 "gen/ragel/alt1_8-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						d1 = p; }
					
#line 468 "gen/ragel/alt1_8-T1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 474 "gen/ragel/alt1_8-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						e1 = p; }
					
#line 480 "gen/ragel/alt1_8-T1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 486 "gen/ragel/alt1_8-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						f1 = p; }
					
#line 492 "gen/ragel/alt1_8-T1.c"
					
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 498 "gen/ragel/alt1_8-T1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						g1 = p; }
					
#line 504 "gen/ragel/alt1_8-T1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; }
					
#line 510 "gen/ragel/alt1_8-T1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						h1 = p; }
					
#line 516 "gen/ragel/alt1_8-T1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; }
					
#line 522 "gen/ragel/alt1_8-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						a1 = p; }
					
#line 528 "gen/ragel/alt1_8-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; }
					
#line 534 "gen/ragel/alt1_8-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
						else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
						else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
						else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
						outc(out, '\n');
					}
					
#line 550 "gen/ragel/alt1_8-T1.c"
					
					
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
	
#line 48 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_8.rl"
	
	
	in->p = p;
	in->pe = pe;
}
