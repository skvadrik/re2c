#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";


#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"



#line 13 "gen/ragel/alt1_2-F1.c"
static const char _m_trans_keys[] = {
	1, 0, 0, 2, 0, 3, 0, 3,
	0
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
	0, 0, 3, 7, 0
};

static const signed char _m_indicies[] = {
	2, 0, 1, 4, 0, 0, 3, 6,
	0, 7, 8, 0
};

static const signed char _m_index_defaults[] = {
	0, 0, 0, 0, 0
};

static const signed char _m_cond_targs[] = {
	0, 1, 3, 2, 3, 3, 3, 1,
	2, 0
};

static const signed char _m_cond_actions[] = {
	0, 0, 1, 0, 2, 0, 3, 4,
	5, 0
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
	
	
#line 77 "gen/ragel/alt1_2-F1.c"
	{
		cs = (int)m_start;
	}
	
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
	
	
#line 85 "gen/ragel/alt1_2-F1.c"
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
				case 5:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						b1 = p; }
					
#line 118 "gen/ragel/alt1_2-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						a1 = p; }
					
#line 128 "gen/ragel/alt1_2-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 138 "gen/ragel/alt1_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						outc(out, '\n');
					}
					
#line 148 "gen/ragel/alt1_2-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 158 "gen/ragel/alt1_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						outc(out, '\n');
					}
					
#line 168 "gen/ragel/alt1_2-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						b1 = p; }
					
#line 178 "gen/ragel/alt1_2-F1.c"
					
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						b2 = p; a1 = a2 = NULL; }
					
#line 184 "gen/ragel/alt1_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						a1 = p; }
					
#line 190 "gen/ragel/alt1_2-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						a2 = p; b1 = b2 = NULL; }
					
#line 196 "gen/ragel/alt1_2-F1.c"
					
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/alt1_2.rl"
						
						if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
						else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
						outc(out, '\n');
					}
					
#line 206 "gen/ragel/alt1_2-F1.c"
					
					
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
