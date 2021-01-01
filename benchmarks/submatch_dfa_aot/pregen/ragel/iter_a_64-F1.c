#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"



#line 12 "gen/ragel/iter_a_64-F1.c"
static const char _aaa_trans_keys[] = {
	1, 0, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	0, 2, 0, 2, 0
};

static const signed char _aaa_char_class[] = {
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
	0
};

static const signed char _aaa_index_offsets[] = {
	0, 0, 1, 2, 3, 4, 5, 6,
	7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 28, 29, 30,
	31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46,
	47, 48, 49, 50, 51, 52, 53, 54,
	55, 56, 57, 58, 59, 60, 61, 62,
	63, 66, 0
};

static const signed char _aaa_indicies[] = {
	2, 3, 4, 5, 6, 7, 8, 9,
	10, 11, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 24, 25,
	26, 27, 28, 29, 30, 31, 32, 33,
	34, 35, 36, 37, 38, 39, 40, 41,
	42, 43, 44, 45, 46, 47, 48, 49,
	50, 51, 52, 53, 54, 55, 56, 57,
	58, 59, 60, 61, 62, 63, 64, 65,
	0, 66, 68, 0, 69, 0
};

static const signed char _aaa_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _aaa_cond_targs[] = {
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23,
	24, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 35, 36, 37, 38, 39,
	40, 41, 42, 43, 44, 45, 46, 47,
	48, 49, 50, 51, 52, 53, 54, 55,
	56, 57, 58, 59, 60, 61, 62, 63,
	64, 65, 1, 65, 65, 1, 0
};

static const signed char _aaa_cond_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 2, 0, 3, 4, 0
};

static const int aaa_start = 65;
static const int aaa_first_final = 65;
static const int aaa_error = 0;

static const int aaa_en_main = 65;


#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *s;
	int cs;
	
	
#line 126 "gen/ragel/iter_a_64-F1.c"
	{
		cs = (int)aaa_start;
	}
	
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
	
	
#line 134 "gen/ragel/iter_a_64-F1.c"
	{
		unsigned int _trans = 0;
		const char * _keys;
		const signed char * _inds;
		int _ic;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _aaa_trans_keys + ((cs<<1)));
		_inds = ( _aaa_indicies + (_aaa_index_offsets[cs]));
		
		if ( ( (*( p))) <= 97 && ( (*( p))) >= 10 ) {
			_ic = (int)_aaa_char_class[(int)( (*( p))) - 10];
			if ( _ic <= (int)(*( _keys+1)) && _ic >= (int)(*( _keys)) )
				_trans = (unsigned int)(*( _inds + (int)( _ic - (int)(*( _keys)) ) )); 
			else
				_trans = (unsigned int)_aaa_index_defaults[cs];
		}
		else {
			_trans = (unsigned int)_aaa_index_defaults[cs];
		}
		
		cs = (int)_aaa_cond_targs[_trans];
		
		if ( _aaa_cond_actions[_trans] != 0 ) {
			
			switch ( _aaa_cond_actions[_trans] ) {
				case 2:  {
					{
#line 8 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
						
						outs(out, s, p);
						outc(out, '.');
						s = p;
					}
					
#line 171 "gen/ragel/iter_a_64-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
						s = p; }
					
#line 181 "gen/ragel/iter_a_64-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 8 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
						
						outs(out, s, p);
						outc(out, '.');
						s = p;
					}
					
#line 195 "gen/ragel/iter_a_64-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
						outc(out, '\n'); }
					
#line 201 "gen/ragel/iter_a_64-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
						s = p; }
					
#line 211 "gen/ragel/iter_a_64-F1.c"
					
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
						outc(out, '\n'); }
					
#line 217 "gen/ragel/iter_a_64-F1.c"
					
					
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
	
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/iter_a_64.rl"
	
	
	in->p = p;
	in->pe = pe;
}
