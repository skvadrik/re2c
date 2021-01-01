#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"



#line 12 "gen/ragel/ipv4-F1.c"
static const char _ipv4_trans_keys[] = {
	1, 0, 2, 3, 3, 3, 2, 3,
	3, 3, 2, 3, 3, 3, 0, 3,
	0, 3, 0, 0, 2, 3, 2, 2,
	2, 3, 2, 2, 2, 3, 2, 2,
	3, 3, 0
};

static const signed char _ipv4_char_class[] = {
	0, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 2, 1, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	0
};

static const signed char _ipv4_index_offsets[] = {
	0, 0, 2, 3, 5, 6, 8, 9,
	13, 17, 18, 20, 21, 23, 24, 26,
	27, 0
};

static const signed char _ipv4_indicies[] = {
	2, 3, 4, 6, 7, 8, 10, 11,
	12, 14, 0, 0, 15, 14, 0, 0,
	16, 14, 10, 17, 10, 6, 18, 6,
	2, 19, 2, 21, 0
};

static const signed char _ipv4_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0
};

static const signed char _ipv4_cond_targs[] = {
	0, 1, 2, 14, 3, 3, 4, 12,
	5, 5, 6, 10, 7, 7, 16, 8,
	9, 11, 13, 15, 16, 1, 0
};

static const signed char _ipv4_cond_actions[] = {
	0, 0, 0, 0, 1, 0, 0, 0,
	2, 0, 0, 0, 3, 0, 4, 0,
	0, 0, 0, 0, 0, 5, 0
};

static const int ipv4_start = 16;
static const int ipv4_first_final = 16;
static const int ipv4_error = 0;

static const int ipv4_en_main = 16;


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *p1, *p2, *p3, *p4;
	int cs;
	
	
#line 80 "gen/ragel/ipv4-F1.c"
	{
		cs = (int)ipv4_start;
	}
	
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
	
	
#line 88 "gen/ragel/ipv4-F1.c"
	{
		unsigned int _trans = 0;
		const char * _keys;
		const signed char * _inds;
		int _ic;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _ipv4_trans_keys + ((cs<<1)));
		_inds = ( _ipv4_indicies + (_ipv4_index_offsets[cs]));
		
		if ( ( (*( p))) <= 57 && ( (*( p))) >= 10 ) {
			_ic = (int)_ipv4_char_class[(int)( (*( p))) - 10];
			if ( _ic <= (int)(*( _keys+1)) && _ic >= (int)(*( _keys)) )
				_trans = (unsigned int)(*( _inds + (int)( _ic - (int)(*( _keys)) ) )); 
			else
				_trans = (unsigned int)_ipv4_index_defaults[cs];
		}
		else {
			_trans = (unsigned int)_ipv4_index_defaults[cs];
		}
		
		cs = (int)_ipv4_cond_targs[_trans];
		
		if ( _ipv4_cond_actions[_trans] != 0 ) {
			
			switch ( _ipv4_cond_actions[_trans] ) {
				case 5:  {
					{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
						p1 = p; }
					
#line 121 "gen/ragel/ipv4-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
						p2 = p; }
					
#line 131 "gen/ragel/ipv4-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
						p3 = p; }
					
#line 141 "gen/ragel/ipv4-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
						p4 = p; }
					
#line 151 "gen/ragel/ipv4-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
						
						outs(out, p1, p2 - 1);
						outc(out, ',');
						outs(out, p2, p3 - 1);
						outc(out, ',');
						outs(out, p3, p4 - 1);
						outc(out, ',');
						outs(out, p4, p);
						outc(out, '\n');
					}
					
#line 170 "gen/ragel/ipv4-F1.c"
					
					
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
	
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/ipv4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
