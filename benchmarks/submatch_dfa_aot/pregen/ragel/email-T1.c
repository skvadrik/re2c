#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"



#line 12 "gen/ragel/email-T1.c"
static const signed char _email_key_offsets[] = {
	0, 1, 15, 28, 33, 40, 46, 51,
	58, 64, 0
};

static const char _email_trans_keys[] = {
	10, 10, 33, 46, 61, 63, 64, 35,
	39, 42, 43, 45, 57, 94, 126, 10,
	33, 45, 61, 63, 35, 39, 42, 43,
	47, 57, 94, 126, 10, 48, 57, 97,
	122, 10, 45, 46, 48, 57, 97, 122,
	10, 45, 48, 57, 97, 122, 10, 48,
	57, 97, 122, 10, 45, 46, 48, 57,
	97, 122, 10, 45, 48, 57, 97, 122,
	10, 33, 45, 61, 63, 35, 39, 42,
	43, 47, 57, 94, 126, 0
};

static const signed char _email_single_lengths[] = {
	1, 6, 5, 1, 3, 2, 1, 3,
	2, 5, 0
};

static const signed char _email_range_lengths[] = {
	0, 4, 4, 2, 2, 2, 2, 2,
	2, 4, 0
};

static const signed char _email_index_offsets[] = {
	0, 2, 13, 23, 27, 33, 38, 42,
	48, 53, 0
};

static const signed char _email_cond_targs[] = {
	9, 0, 9, 1, 2, 1, 1, 3,
	1, 1, 1, 1, 0, 9, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 9,
	4, 4, 0, 9, 5, 6, 4, 4,
	0, 9, 5, 4, 4, 0, 9, 7,
	7, 0, 9, 8, 6, 7, 7, 0,
	9, 8, 7, 7, 0, 9, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 2, 3, 4, 5, 6, 7, 8,
	9, 0
};

static const signed char _email_cond_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 2, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 3, 3,
	3, 3, 3, 3, 3, 3, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0
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
	
	
#line 90 "gen/ragel/email-T1.c"
	{
		cs = (int)email_start;
	}
	
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
	
	
#line 98 "gen/ragel/email-T1.c"
	{
		int _klen;
		unsigned int _trans = 0;
		const char * _keys;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _email_trans_keys + (_email_key_offsets[cs]));
		_trans = (unsigned int)_email_index_offsets[cs];
		
		_klen = (int)_email_single_lengths[cs];
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
		
		_klen = (int)_email_range_lengths[cs];
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
		cs = (int)_email_cond_targs[_trans];
		
		if ( _email_cond_actions[_trans] != 0 ) {
			
			switch ( _email_cond_actions[_trans] ) {
				case 3:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
						p1 = p; }
					
#line 167 "gen/ragel/email-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
						p2 = p; }
					
#line 177 "gen/ragel/email-T1.c"
					
					
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
					
#line 193 "gen/ragel/email-T1.c"
					
					
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
