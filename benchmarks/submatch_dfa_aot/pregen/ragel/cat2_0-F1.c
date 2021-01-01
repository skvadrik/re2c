#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"



#line 12 "gen/ragel/cat2_0-F1.c"
static const char _abcd_trans_keys[] = {
	1, 0, 0, 3, 0, 3, 0, 3,
	0, 3, 0, 3, 0
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
	0, 0, 4, 8, 12, 16, 0
};

static const signed char _abcd_indicies[] = {
	2, 0, 3, 4, 6, 0, 7, 8,
	10, 0, 9, 11, 13, 0, 0, 12,
	15, 0, 16, 17, 0
};

static const signed char _abcd_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0
};

static const signed char _abcd_cond_targs[] = {
	0, 1, 5, 1, 2, 2, 5, 3,
	2, 3, 5, 4, 4, 5, 5, 5,
	1, 2, 0
};

static const signed char _abcd_cond_actions[] = {
	0, 0, 1, 2, 3, 0, 4, 5,
	6, 0, 7, 8, 0, 9, 0, 10,
	11, 12, 0
};

static const int abcd_start = 5;
static const int abcd_first_final = 5;
static const int abcd_error = 0;

static const int abcd_en_main = 5;


#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1,
	*b0, *b1;
	int cs;
	
	
#line 79 "gen/ragel/cat2_0-F1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
	
	
#line 87 "gen/ragel/cat2_0-F1.c"
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
				case 5:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 120 "gen/ragel/cat2_0-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 130 "gen/ragel/cat2_0-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
					}
					
#line 143 "gen/ragel/cat2_0-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b0 = p; }
					
#line 153 "gen/ragel/cat2_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 159 "gen/ragel/cat2_0-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 169 "gen/ragel/cat2_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 175 "gen/ragel/cat2_0-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 185 "gen/ragel/cat2_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
					}
					
#line 194 "gen/ragel/cat2_0-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a0 = p; }
					
#line 204 "gen/ragel/cat2_0-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b0 = p; }
					
#line 210 "gen/ragel/cat2_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 216 "gen/ragel/cat2_0-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b0 = p; }
					
#line 226 "gen/ragel/cat2_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 232 "gen/ragel/cat2_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 238 "gen/ragel/cat2_0-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 248 "gen/ragel/cat2_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 254 "gen/ragel/cat2_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
					}
					
#line 263 "gen/ragel/cat2_0-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a0 = p; }
					
#line 273 "gen/ragel/cat2_0-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b0 = p; }
					
#line 279 "gen/ragel/cat2_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 285 "gen/ragel/cat2_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 291 "gen/ragel/cat2_0-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b0 = p; }
					
#line 301 "gen/ragel/cat2_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 307 "gen/ragel/cat2_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 313 "gen/ragel/cat2_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
					}
					
#line 322 "gen/ragel/cat2_0-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a0 = p; }
					
#line 332 "gen/ragel/cat2_0-F1.c"
					
					{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b0 = p; }
					
#line 338 "gen/ragel/cat2_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						a1 = p; }
					
#line 344 "gen/ragel/cat2_0-F1.c"
					
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						b1 = p; }
					
#line 350 "gen/ragel/cat2_0-F1.c"
					
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
						
						outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
						outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
					}
					
#line 359 "gen/ragel/cat2_0-F1.c"
					
					
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
	
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
	
	
	in->p = p;
	in->pe = pe;
}
