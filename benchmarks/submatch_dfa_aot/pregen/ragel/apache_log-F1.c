#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"



#line 12 "gen/ragel/apache_log-F1.c"
static const char _apache_log_trans_keys[] = {
	1, 0, 0, 6, 0, 4, 0, 0,
	0, 4, 0, 0, 0, 7, 1, 8,
	1, 8, 0, 0, 0, 3, 1, 3,
	1, 3, 0, 0, 0, 6, 0, 6,
	0, 6, 0, 0, 0, 3, 1, 3,
	0, 0, 0, 3, 1, 3, 1, 1,
	0, 6, 5, 6, 0
};

static const signed char _apache_log_char_class[] = {
	0, 1, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 0,
	2, 3, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 4, 5, 2, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 7, 2, 8, 0
};

static const signed char _apache_log_index_offsets[] = {
	0, 0, 7, 12, 13, 18, 19, 27,
	35, 43, 44, 48, 51, 54, 55, 62,
	69, 76, 77, 81, 84, 85, 89, 92,
	93, 100, 0
};

static const signed char _apache_log_indicies[] = {
	2, 0, 0, 0, 0, 1, 1, 3,
	0, 0, 0, 4, 6, 7, 0, 0,
	0, 8, 10, 11, 0, 0, 0, 0,
	0, 0, 12, 0, 14, 14, 14, 14,
	14, 14, 0, 0, 14, 14, 14, 14,
	14, 14, 15, 16, 17, 0, 0, 18,
	0, 20, 0, 0, 20, 21, 22, 23,
	0, 0, 0, 0, 0, 24, 26, 0,
	0, 0, 0, 0, 25, 27, 0, 0,
	0, 28, 0, 29, 31, 32, 0, 0,
	33, 0, 34, 35, 36, 37, 0, 0,
	38, 0, 39, 40, 41, 31, 0, 0,
	0, 0, 0, 42, 44, 44, 0
};

static const signed char _apache_log_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 14,
	14, 0, 0, 20, 20, 0, 0, 0,
	0, 0, 0, 34, 0, 0, 39, 0,
	0, 0, 0
};

static const signed char _apache_log_cond_targs[] = {
	0, 1, 2, 2, 3, 3, 4, 4,
	5, 5, 6, 6, 7, 7, 8, 9,
	10, 10, 11, 11, 12, 13, 14, 14,
	15, 15, 16, 16, 17, 24, 17, 18,
	18, 19, 19, 20, 21, 21, 22, 22,
	23, 25, 24, 25, 1, 0
};

static const signed char _apache_log_cond_actions[] = {
	0, 0, 1, 0, 2, 0, 3, 0,
	4, 0, 5, 0, 6, 0, 0, 0,
	7, 0, 8, 0, 0, 0, 9, 0,
	10, 0, 11, 0, 12, 12, 0, 13,
	0, 14, 0, 0, 15, 0, 16, 0,
	0, 17, 0, 0, 18, 0
};

static const int apache_log_start = 25;
static const int apache_log_first_final = 25;
static const int apache_log_error = 0;

static const int apache_log_en_main = 25;


#line 44 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*h1, *i1, *a1, *d1, *r1, *s1, *z1, *u1, *g1,
	*h2, *i2, *a2, *d2, *r2, *s2, *z2, *u2, *g2;
	int cs;
	
	
#line 105 "gen/ragel/apache_log-F1.c"
	{
		cs = (int)apache_log_start;
	}
	
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
	
	
#line 113 "gen/ragel/apache_log-F1.c"
	{
		unsigned int _trans = 0;
		const char * _keys;
		const signed char * _inds;
		int _ic;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _apache_log_trans_keys + ((cs<<1)));
		_inds = ( _apache_log_indicies + (_apache_log_index_offsets[cs]));
		
		if ( ( (*( p))) <= 93 && ( (*( p))) >= 9 ) {
			_ic = (int)_apache_log_char_class[(int)( (*( p))) - 9];
			if ( _ic <= (int)(*( _keys+1)) && _ic >= (int)(*( _keys)) )
				_trans = (unsigned int)(*( _inds + (int)( _ic - (int)(*( _keys)) ) )); 
			else
				_trans = (unsigned int)_apache_log_index_defaults[cs];
		}
		else {
			_trans = (unsigned int)_apache_log_index_defaults[cs];
		}
		
		cs = (int)_apache_log_cond_targs[_trans];
		
		if ( _apache_log_cond_actions[_trans] != 0 ) {
			
			switch ( _apache_log_cond_actions[_trans] ) {
				case 18:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						h1 = p; }
					
#line 146 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						h2 = p; }
					
#line 156 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						i1 = p; }
					
#line 166 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						i2 = p; }
					
#line 176 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						a1 = p; }
					
#line 186 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						a2 = p; }
					
#line 196 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						d1 = p; }
					
#line 206 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						d2 = p; }
					
#line 216 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						r1 = p; }
					
#line 226 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						r2 = p; }
					
#line 236 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						s1 = p; }
					
#line 246 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						s2 = p; }
					
#line 256 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						z1 = p; }
					
#line 266 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						z2 = p; }
					
#line 276 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						u1 = p; }
					
#line 286 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						u2 = p; }
					
#line 296 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						g1 = p; }
					
#line 306 "gen/ragel/apache_log-F1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						g2 = p; }
					
#line 316 "gen/ragel/apache_log-F1.c"
					
					{
#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						
						OUT("host: ",     h1, h2);
						OUT("userid: ",   i1, i2);
						OUT("authuser: ", a1, a2);
						OUT("date: ",     d1, d2);
						OUT("request: ",  r1, r2);
						OUT("status: ",   s1, s2);
						OUT("size: ",     z1, z2);
						OUT("url: ",      u1, u2);
						OUT("agent: ",    g1, g2);
						outc(out, '\n');
					}
					
#line 333 "gen/ragel/apache_log-F1.c"
					
					
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
	
#line 56 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
	
	
	in->p = p;
	in->pe = pe;
}
