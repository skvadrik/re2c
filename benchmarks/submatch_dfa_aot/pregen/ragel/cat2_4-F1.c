#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"



#line 12 "gen/ragel/cat2_4-F1.c"
static const char _abcd_trans_keys[] = {
	1, 0, 2, 2, 2, 2, 2, 2,
	2, 3, 2, 3, 2, 3, 2, 3,
	0, 3, 0, 3, 2, 2, 2, 2,
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
	0, 0, 1, 2, 3, 5, 7, 9,
	11, 15, 19, 20, 21, 22, 26, 30,
	32, 0
};

static const signed char _abcd_indicies[] = {
	2, 4, 6, 8, 9, 11, 9, 13,
	9, 15, 9, 17, 0, 15, 18, 17,
	0, 19, 18, 21, 23, 25, 17, 0,
	25, 27, 17, 0, 0, 27, 19, 9,
	29, 0
};

static const signed char _abcd_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0
};

static const signed char _abcd_cond_targs[] = {
	0, 1, 2, 2, 3, 3, 4, 4,
	5, 15, 5, 6, 6, 7, 7, 8,
	8, 16, 9, 10, 10, 11, 11, 12,
	12, 13, 13, 14, 16, 1, 0
};

static const signed char _abcd_cond_actions[] = {
	0, 0, 1, 0, 1, 0, 1, 0,
	2, 0, 0, 2, 0, 2, 0, 2,
	0, 3, 0, 4, 0, 5, 0, 5,
	0, 5, 0, 0, 0, 6, 0
};

static const int abcd_start = 16;
static const int abcd_first_final = 16;
static const int abcd_error = 0;

static const int abcd_en_main = 16;


#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1,
	*b0, *b1;
	int cs;
	
	
#line 90 "gen/ragel/cat2_4-F1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
	
	
#line 98 "gen/ragel/cat2_4-F1.c"
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						b0 = p; }
					
#line 131 "gen/ragel/cat2_4-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						b1 = p; }
					
#line 141 "gen/ragel/cat2_4-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
					}
					
#line 154 "gen/ragel/cat2_4-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						a0 = p; }
					
#line 164 "gen/ragel/cat2_4-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						b0 = p; }
					
#line 170 "gen/ragel/cat2_4-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						a1 = p; }
					
#line 180 "gen/ragel/cat2_4-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						b1 = p; }
					
#line 186 "gen/ragel/cat2_4-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						b0 = p; }
					
#line 196 "gen/ragel/cat2_4-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						a1 = p; }
					
#line 202 "gen/ragel/cat2_4-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
						b1 = p; }
					
#line 208 "gen/ragel/cat2_4-F1.c"
					
					
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
	
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
