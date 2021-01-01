#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"



#line 13 "gen/ragel/alt1_4-F1.c"
static const char _m_trans_keys[] = {
	1, 0, 0, 2, 0, 3, 0, 4,
	0, 5, 0, 5, 0
};

static const signed char _m_char_class[] = {
	0, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 2,
	3, 4, 5, 0
};

static const signed char _m_index_offsets[] = {
	0, 0, 3, 7, 12, 18, 0
};

static const signed char _m_indicies[] = {
	2, 0, 1, 4, 0, 0, 3, 6,
	0, 0, 0, 5, 8, 0, 0, 0,
	0, 7, 10, 0, 11, 12, 13, 14,
	0
};

static const signed char _m_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0
};

static const signed char _m_cond_targs[] = {
	0, 1, 5, 2, 5, 3, 5, 4,
	5, 5, 5, 1, 2, 3, 4, 0
};

static const signed char _m_cond_actions[] = {
	0, 0, 1, 0, 2, 0, 3, 0,
	4, 0, 5, 6, 7, 8, 9, 0
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
	
	
#line 79 "gen/ragel/alt1_4-F1.c"
	{
		cs = (int)m_start;
	}
	
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
	
	
#line 87 "gen/ragel/alt1_4-F1.c"
	{
		unsigned int _trans = 0;
		const char * _keys;
		const signed char * _inds;
		int _ic;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _m_trans_keys + ((cs<<1)));
		_inds = ( _m_indicies + (_m_index_offsets[cs]));
		
		if ( ( (*( p))) <= 100 && ( (*( p))) >= 10 ) {
			_ic = (int)_m_char_class[(int)( (*( p))) - 10];
			if ( _ic <= (int)(*( _keys+1)) && _ic >= (int)(*( _keys)) )
				_trans = (unsigned int)(*( _inds + (int)( _ic - (int)(*( _keys)) ) )); 
			else
				_trans = (unsigned int)_m_index_defaults[cs];
		}
		else {
			_trans = (unsigned int)_m_index_defaults[cs];
		}
		
		cs = (int)_m_cond_targs[_trans];
		
		if ( _m_cond_actions[_trans] != 0 ) {
			
			switch ( _m_cond_actions[_trans] ) {
				case 7:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						b1 = p; }
					
#line 120 "gen/ragel/alt1_4-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						c1 = p; }
					
#line 130 "gen/ragel/alt1_4-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						d1 = p; }
					
#line 140 "gen/ragel/alt1_4-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						a1 = p; }
					
#line 150 "gen/ragel/alt1_4-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 160 "gen/ragel/alt1_4-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						outc(out, '\n');
					}
					
#line 172 "gen/ragel/alt1_4-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 182 "gen/ragel/alt1_4-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						outc(out, '\n');
					}
					
#line 194 "gen/ragel/alt1_4-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 204 "gen/ragel/alt1_4-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						outc(out, '\n');
					}
					
#line 216 "gen/ragel/alt1_4-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 226 "gen/ragel/alt1_4-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						outc(out, '\n');
					}
					
#line 238 "gen/ragel/alt1_4-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						b1 = p; }
					
#line 248 "gen/ragel/alt1_4-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 254 "gen/ragel/alt1_4-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						c1 = p; }
					
#line 260 "gen/ragel/alt1_4-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; }
					
#line 266 "gen/ragel/alt1_4-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						d1 = p; }
					
#line 272 "gen/ragel/alt1_4-F1.c"
					
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; }
					
#line 278 "gen/ragel/alt1_4-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						a1 = p; }
					
#line 284 "gen/ragel/alt1_4-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; }
					
#line 290 "gen/ragel/alt1_4-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_4.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
						else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
						outc(out, '\n');
					}
					
#line 302 "gen/ragel/alt1_4-F1.c"
					
					
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
