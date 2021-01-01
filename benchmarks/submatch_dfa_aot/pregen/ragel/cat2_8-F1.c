#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"



#line 12 "gen/ragel/cat2_8-F1.c"
static const char _abcd_trans_keys[] = {
	1, 0, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 3, 2, 3, 2, 3, 2, 3,
	2, 3, 2, 3, 2, 3, 2, 3,
	0, 3, 0, 3, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 0, 3, 0, 3, 2, 3,
	2, 2, 0
};

static const signed char _abcd_char_class[] = {
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

static const signed char _abcd_index_offsets[] = {
	0, 0, 1, 2, 3, 4, 5, 6,
	7, 9, 11, 13, 15, 17, 19, 21,
	23, 27, 31, 32, 33, 34, 35, 36,
	37, 38, 42, 46, 48, 0
};

static const signed char _abcd_indicies[] = {
	2, 4, 6, 8, 10, 12, 14, 16,
	17, 19, 17, 21, 17, 23, 17, 25,
	17, 27, 17, 29, 17, 31, 17, 33,
	0, 31, 34, 33, 0, 35, 34, 37,
	39, 41, 43, 45, 47, 49, 33, 0,
	49, 51, 33, 0, 0, 51, 35, 17,
	53, 0
};

static const signed char _abcd_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};

static const signed char _abcd_cond_targs[] = {
	0, 1, 2, 2, 3, 3, 4, 4,
	5, 5, 6, 6, 7, 7, 8, 8,
	9, 27, 9, 10, 10, 11, 11, 12,
	12, 13, 13, 14, 14, 15, 15, 16,
	16, 28, 17, 18, 18, 19, 19, 20,
	20, 21, 21, 22, 22, 23, 23, 24,
	24, 25, 25, 26, 28, 1, 0
};

static const signed char _abcd_cond_actions[] = {
	0, 0, 1, 0, 1, 0, 1, 0,
	1, 0, 1, 0, 1, 0, 1, 0,
	2, 0, 0, 2, 0, 2, 0, 2,
	0, 2, 0, 2, 0, 2, 0, 2,
	0, 3, 0, 4, 0, 5, 0, 5,
	0, 5, 0, 5, 0, 5, 0, 5,
	0, 5, 0, 0, 0, 6, 0
};

static const int abcd_start = 28;
static const int abcd_first_final = 28;
static const int abcd_error = 0;

static const int abcd_en_main = 28;


#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1,
	*b0, *b1;
	int cs;
	
	
#line 103 "gen/ragel/cat2_8-F1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
	
	
#line 111 "gen/ragel/cat2_8-F1.c"
	{
		unsigned int _trans = 0;
		const char * _keys;
		const signed char * _inds;
		int _ic;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _abcd_trans_keys + ((cs<<1)));
		_inds = ( _abcd_indicies + (_abcd_index_offsets[cs]));
		
		if ( ( (*( p))) <= 98 && ( (*( p))) >= 10 ) {
			_ic = (int)_abcd_char_class[(int)( (*( p))) - 10];
			if ( _ic <= (int)(*( _keys+1)) && _ic >= (int)(*( _keys)) )
				_trans = (unsigned int)(*( _inds + (int)( _ic - (int)(*( _keys)) ) )); 
			else
				_trans = (unsigned int)_abcd_index_defaults[cs];
		}
		else {
			_trans = (unsigned int)_abcd_index_defaults[cs];
		}
		
		cs = (int)_abcd_cond_targs[_trans];
		
		if ( _abcd_cond_actions[_trans] != 0 ) {
			
			switch ( _abcd_cond_actions[_trans] ) {
				case 1:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						b0 = p; }
					
#line 144 "gen/ragel/cat2_8-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						b1 = p; }
					
#line 154 "gen/ragel/cat2_8-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
					}
					
#line 167 "gen/ragel/cat2_8-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						a0 = p; }
					
#line 177 "gen/ragel/cat2_8-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						b0 = p; }
					
#line 183 "gen/ragel/cat2_8-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						a1 = p; }
					
#line 193 "gen/ragel/cat2_8-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						b1 = p; }
					
#line 199 "gen/ragel/cat2_8-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						b0 = p; }
					
#line 209 "gen/ragel/cat2_8-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						a1 = p; }
					
#line 215 "gen/ragel/cat2_8-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
						b1 = p; }
					
#line 221 "gen/ragel/cat2_8-F1.c"
					
					
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
	
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_8.rl"
	
	
	in->p = p;
	in->pe = pe;
}
