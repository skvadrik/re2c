#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"



#line 12 "gen/ragel/email-F1.c"
static const char _email_trans_keys[] = {
	0, 0, 0, 6, 0, 5, 0, 5,
	0, 5, 0, 5, 0, 5, 0, 5,
	0, 5, 0, 5, 0
};

static const signed char _email_char_class[] = {
	0, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 2,
	1, 2, 2, 2, 2, 2, 1, 1,
	2, 2, 1, 3, 4, 2, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	1, 1, 1, 2, 1, 2, 6, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 2, 2, 2, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 2, 2, 2, 2, 0
};

static const signed char _email_index_offsets[] = {
	0, 1, 8, 14, 20, 26, 32, 38,
	44, 50, 0
};

static const signed char _email_indicies[] = {
	1, 1, 0, 2, 2, 3, 2, 4,
	1, 0, 2, 2, 0, 2, 1, 0,
	0, 0, 0, 5, 1, 0, 0, 7,
	8, 6, 1, 0, 0, 7, 0, 6,
	1, 0, 0, 0, 0, 9, 10, 0,
	0, 11, 8, 9, 1, 0, 0, 11,
	0, 9, 1, 0, 12, 12, 0, 12,
	0
};

static const signed char _email_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

static const signed char _email_cond_targs[] = {
	0, 9, 1, 2, 3, 4, 4, 5,
	6, 7, 9, 8, 1, 0
};

static const signed char _email_cond_actions[] = {
	0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 2, 0, 3, 0
};

static const int email_start = 9;
static const int email_first_final = 9;
static const int email_error = -1;

static const int email_en_main = 9;


#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	char *p1, *p2;
	int cs;
	
	
#line 86 "gen/ragel/email-F1.c"
	{
		cs = (int)email_start;
	}
	
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
	
	
#line 94 "gen/ragel/email-F1.c"
	{
		unsigned int _trans = 0;
		const char * _keys;
		const signed char * _inds;
		int _ic;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _email_trans_keys + ((cs<<1)));
		_inds = ( _email_indicies + (_email_index_offsets[cs]));
		
		if ( ( (*( p))) <= 126 && ( (*( p))) >= 10 ) {
			_ic = (int)_email_char_class[(int)( (*( p))) - 10];
			if ( _ic <= (int)(*( _keys+1)) && _ic >= (int)(*( _keys)) )
				_trans = (unsigned int)(*( _inds + (int)( _ic - (int)(*( _keys)) ) )); 
			else
				_trans = (unsigned int)_email_index_defaults[cs];
		}
		else {
			_trans = (unsigned int)_email_index_defaults[cs];
		}
		
		cs = (int)_email_cond_targs[_trans];
		
		if ( _email_cond_actions[_trans] != 0 ) {
			
			switch ( _email_cond_actions[_trans] ) {
				case 3:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
						p1 = p; }
					
#line 127 "gen/ragel/email-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
						p2 = p; }
					
#line 137 "gen/ragel/email-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
						
						outc(out, ' ');
						outs(out, p1, p2 - 1);
						outc(out, ' ');
						outs(out, p2, p);
						outc(out, '\n');
					}
					
#line 153 "gen/ragel/email-F1.c"
					
					
					break; 
				}
			}
			
		}
		
		p += 1;
		goto _resume;
		_out: {}
	}
	
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
	
	
	in->p = p;
	in->pe = pe;
}
