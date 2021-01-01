#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"



#line 13 "gen/ragel/alt2_2-F1.c"
static const char _m_trans_keys[] = {
	1, 0, 0, 3, 0, 3, 0, 3,
	0, 2, 0, 3, 0
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
	3, 0
};

static const signed char _m_index_offsets[] = {
	0, 0, 4, 8, 12, 15, 0
};

static const signed char _m_indicies[] = {
	2, 0, 1, 3, 5, 0, 0, 4,
	7, 0, 8, 6, 10, 0, 9, 12,
	0, 13, 14, 0
};

static const signed char _m_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0
};

static const signed char _m_cond_targs[] = {
	0, 1, 5, 2, 2, 5, 3, 5,
	4, 4, 5, 5, 5, 1, 3, 0
};

static const signed char _m_cond_actions[] = {
	0, 0, 1, 2, 0, 3, 0, 4,
	5, 0, 6, 0, 7, 8, 9, 0
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
	
	
#line 80 "gen/ragel/alt2_2-F1.c"
	{
		cs = (int)m_start;
	}
	
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
	
	
#line 88 "gen/ragel/alt2_2-F1.c"
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
		
		if ( ( (*( p))) <= 98 && ( (*( p))) >= 10 ) {
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
				case 9:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b1 = p; }
					
#line 121 "gen/ragel/alt2_2-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a1 = p; }
					
#line 131 "gen/ragel/alt2_2-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 141 "gen/ragel/alt2_2-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a3 = p; }
					
#line 147 "gen/ragel/alt2_2-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 157 "gen/ragel/alt2_2-F1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b3 = p; }
					
#line 163 "gen/ragel/alt2_2-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 173 "gen/ragel/alt2_2-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						outc(out, '\n');
					}
					
#line 185 "gen/ragel/alt2_2-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 195 "gen/ragel/alt2_2-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						outc(out, '\n');
					}
					
#line 207 "gen/ragel/alt2_2-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 217 "gen/ragel/alt2_2-F1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b3 = p; }
					
#line 223 "gen/ragel/alt2_2-F1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 229 "gen/ragel/alt2_2-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a3 = p; }
					
#line 235 "gen/ragel/alt2_2-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 241 "gen/ragel/alt2_2-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						outc(out, '\n');
					}
					
#line 253 "gen/ragel/alt2_2-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 263 "gen/ragel/alt2_2-F1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b3 = p; }
					
#line 269 "gen/ragel/alt2_2-F1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 275 "gen/ragel/alt2_2-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a3 = p; }
					
#line 281 "gen/ragel/alt2_2-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 287 "gen/ragel/alt2_2-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						outc(out, '\n');
					}
					
#line 299 "gen/ragel/alt2_2-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b1 = p; }
					
#line 309 "gen/ragel/alt2_2-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 315 "gen/ragel/alt2_2-F1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a1 = p; }
					
#line 321 "gen/ragel/alt2_2-F1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 327 "gen/ragel/alt2_2-F1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b3 = p; }
					
#line 333 "gen/ragel/alt2_2-F1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						b4 = p; a3 = a4 = NULL; }
					
#line 339 "gen/ragel/alt2_2-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a3 = p; }
					
#line 345 "gen/ragel/alt2_2-F1.c"
					
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						a4 = p; b3 = b4 = NULL; }
					
#line 351 "gen/ragel/alt2_2-F1.c"
					
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt2_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
						else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
						outc(out, '\n');
					}
					
#line 363 "gen/ragel/alt2_2-F1.c"
					
					
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
