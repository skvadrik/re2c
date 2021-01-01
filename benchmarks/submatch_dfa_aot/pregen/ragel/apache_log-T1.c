#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"



#line 12 "gen/ragel/apache_log-T1.c"
static const signed char _apache_log_key_offsets[] = {
	0, 0, 5, 8, 10, 13, 15, 18,
	20, 22, 24, 27, 29, 31, 33, 37,
	41, 46, 48, 51, 53, 55, 58, 60,
	61, 65, 0
};

static const char _apache_log_trans_keys[] = {
	9, 32, 46, 48, 57, 9, 32, 45,
	9, 32, 9, 32, 45, 9, 32, 9,
	32, 91, 10, 93, 10, 93, 9, 32,
	9, 32, 34, 10, 34, 10, 34, 9,
	32, 9, 32, 48, 57, 9, 32, 48,
	57, 9, 32, 45, 48, 57, 9, 32,
	9, 32, 34, 10, 34, 9, 32, 9,
	32, 34, 10, 34, 10, 9, 32, 48,
	57, 46, 48, 57, 0
};

static const signed char _apache_log_single_lengths[] = {
	0, 3, 3, 2, 3, 2, 3, 2,
	2, 2, 3, 2, 2, 2, 2, 2,
	3, 2, 3, 2, 2, 3, 2, 1,
	2, 1, 0
};

static const signed char _apache_log_range_lengths[] = {
	0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 0
};

static const signed char _apache_log_index_offsets[] = {
	0, 0, 5, 9, 12, 16, 19, 23,
	26, 29, 32, 36, 39, 42, 45, 49,
	53, 58, 61, 65, 68, 71, 75, 78,
	80, 84, 0
};

static const signed char _apache_log_cond_targs[] = {
	2, 2, 1, 1, 0, 2, 2, 3,
	0, 4, 4, 0, 4, 4, 5, 0,
	6, 6, 0, 6, 6, 7, 0, 0,
	0, 8, 0, 9, 8, 10, 10, 0,
	10, 10, 11, 0, 0, 0, 12, 0,
	13, 12, 14, 14, 0, 14, 14, 15,
	0, 16, 16, 15, 0, 16, 16, 17,
	24, 0, 18, 18, 0, 18, 18, 19,
	0, 0, 20, 19, 21, 21, 0, 21,
	21, 22, 0, 0, 23, 22, 25, 0,
	18, 18, 24, 0, 1, 1, 0, 0,
	1, 2, 3, 4, 5, 6, 7, 8,
	9, 10, 11, 12, 13, 14, 15, 16,
	17, 18, 19, 20, 21, 22, 23, 24,
	25, 0
};

static const signed char _apache_log_cond_actions[] = {
	1, 1, 0, 0, 0, 0, 0, 2,
	0, 3, 3, 0, 0, 0, 4, 0,
	5, 5, 0, 0, 0, 6, 0, 0,
	0, 0, 0, 0, 0, 7, 7, 0,
	0, 0, 8, 0, 0, 0, 0, 0,
	0, 0, 9, 9, 0, 0, 0, 10,
	0, 11, 11, 0, 0, 0, 0, 12,
	12, 0, 13, 13, 0, 0, 0, 14,
	0, 0, 0, 0, 15, 15, 0, 0,
	0, 16, 0, 0, 0, 0, 17, 0,
	13, 13, 0, 0, 18, 18, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0
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
	
	
#line 109 "gen/ragel/apache_log-T1.c"
	{
		cs = (int)apache_log_start;
	}
	
#line 55 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
	
	
#line 117 "gen/ragel/apache_log-T1.c"
	{
		int _klen;
		unsigned int _trans = 0;
		const char * _keys;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _apache_log_trans_keys + (_apache_log_key_offsets[cs]));
		_trans = (unsigned int)_apache_log_index_offsets[cs];
		
		_klen = (int)_apache_log_single_lengths[cs];
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
		
		_klen = (int)_apache_log_range_lengths[cs];
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
		cs = (int)_apache_log_cond_targs[_trans];
		
		if ( _apache_log_cond_actions[_trans] != 0 ) {
			
			switch ( _apache_log_cond_actions[_trans] ) {
				case 18:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						h1 = p; }
					
#line 186 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						h2 = p; }
					
#line 196 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						i1 = p; }
					
#line 206 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						i2 = p; }
					
#line 216 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						a1 = p; }
					
#line 226 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						a2 = p; }
					
#line 236 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						d1 = p; }
					
#line 246 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						d2 = p; }
					
#line 256 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						r1 = p; }
					
#line 266 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						r2 = p; }
					
#line 276 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						s1 = p; }
					
#line 286 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 24 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						s2 = p; }
					
#line 296 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						z1 = p; }
					
#line 306 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						z2 = p; }
					
#line 316 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						u1 = p; }
					
#line 326 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						u2 = p; }
					
#line 336 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						g1 = p; }
					
#line 346 "gen/ragel/apache_log-T1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/apache_log.rl"
						g2 = p; }
					
#line 356 "gen/ragel/apache_log-T1.c"
					
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
					
#line 373 "gen/ragel/apache_log-T1.c"
					
					
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
