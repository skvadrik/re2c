#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
#include "ragel/common.c"

const char *delim = "\n\n";


#line 74 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"



#line 12 "gen/ragel/http_simple-F1.c"
static const char _uri_trans_keys[] = {
	1, 0, 3, 17, 4, 18, 3, 18,
	15, 15, 17, 17, 17, 17, 16, 16,
	10, 10, 11, 11, 9, 9, 11, 11,
	2, 2, 2, 17, 4, 17, 0, 3,
	0, 3, 0, 3, 0, 3, 1, 3,
	2, 17, 1, 17, 4, 18, 3, 18,
	3, 18, 3, 18, 3, 18, 3, 17,
	3, 18, 3, 17, 3, 18, 3, 18,
	3, 18, 3, 17, 3, 17, 3, 17,
	3, 17, 11, 11, 9, 9, 11, 11,
	3, 3, 11, 11, 11, 11, 11, 11,
	3, 3, 0, 2, 0, 2, 4, 17,
	0
};

static const signed char _uri_char_class[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 2, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	3, 4, 5, 6, 4, 4, 4, 4,
	7, 7, 4, 8, 7, 8, 9, 10,
	11, 11, 11, 11, 11, 11, 11, 11,
	11, 11, 12, 7, 5, 7, 5, 13,
	14, 8, 8, 8, 8, 8, 8, 8,
	15, 8, 8, 8, 8, 8, 8, 8,
	16, 8, 8, 8, 17, 8, 8, 8,
	8, 8, 8, 18, 5, 18, 6, 4,
	6, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 5, 6, 5, 4, 0,
	0
};

static const short _uri_index_offsets[] = {
	0, 0, 15, 30, 46, 47, 48, 49,
	50, 51, 52, 53, 54, 55, 71, 85,
	89, 93, 97, 101, 104, 120, 137, 152,
	168, 184, 200, 216, 231, 247, 262, 278,
	294, 310, 325, 340, 355, 370, 371, 372,
	373, 374, 375, 376, 377, 378, 381, 384,
	0
};

static const signed char _uri_indicies[] = {
	2, 1, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 0, 1, 1, 1, 4,
	0, 0, 4, 5, 5, 6, 5, 4,
	0, 0, 5, 5, 5, 7, 9, 8,
	0, 0, 8, 8, 8, 0, 8, 8,
	0, 10, 8, 8, 8, 11, 13, 15,
	16, 17, 18, 19, 20, 21, 22, 24,
	0, 25, 0, 25, 0, 25, 25, 0,
	25, 0, 0, 0, 25, 25, 25, 26,
	0, 26, 0, 26, 26, 0, 26, 27,
	0, 0, 26, 26, 26, 0, 29, 30,
	29, 0, 31, 30, 32, 0, 33, 35,
	28, 0, 36, 30, 32, 37, 35, 37,
	39, 0, 40, 0, 40, 0, 40, 40,
	0, 40, 0, 0, 0, 40, 40, 40,
	27, 39, 27, 40, 0, 40, 0, 40,
	40, 0, 40, 0, 0, 0, 40, 40,
	40, 11, 0, 0, 11, 11, 11, 0,
	11, 11, 0, 0, 11, 11, 11, 11,
	9, 11, 0, 0, 11, 11, 11, 0,
	11, 11, 0, 0, 11, 11, 11, 11,
	9, 8, 0, 0, 8, 42, 42, 0,
	42, 43, 0, 10, 42, 42, 42, 11,
	9, 44, 0, 0, 44, 44, 44, 45,
	44, 44, 46, 47, 44, 44, 44, 11,
	9, 44, 0, 0, 44, 44, 44, 46,
	44, 44, 46, 47, 44, 44, 44, 11,
	9, 46, 0, 0, 46, 46, 46, 46,
	46, 46, 46, 46, 46, 46, 46, 9,
	47, 0, 0, 47, 47, 47, 46, 47,
	47, 46, 46, 47, 47, 47, 11, 9,
	46, 0, 0, 46, 46, 46, 48, 46,
	46, 46, 46, 46, 46, 46, 9, 49,
	0, 0, 49, 49, 49, 46, 49, 49,
	46, 46, 49, 49, 49, 50, 9, 49,
	0, 0, 49, 49, 49, 46, 49, 49,
	46, 50, 49, 49, 49, 50, 9, 50,
	0, 0, 50, 50, 50, 46, 50, 50,
	46, 46, 50, 50, 50, 50, 2, 1,
	0, 1, 0, 1, 1, 0, 1, 0,
	0, 0, 1, 1, 52, 2, 1, 0,
	1, 0, 1, 1, 0, 1, 0, 0,
	0, 1, 1, 53, 2, 1, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 0,
	1, 54, 1, 2, 1, 0, 1, 0,
	1, 1, 55, 1, 0, 0, 0, 1,
	1, 1, 56, 57, 58, 59, 61, 63,
	64, 65, 0, 67, 68, 0, 69, 70,
	72, 0, 72, 0, 72, 72, 0, 72,
	0, 0, 0, 73, 72, 72, 0
};

static const signed char _uri_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 28,
	28, 34, 28, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 67, 69, 0,
	0
};

static const signed char _uri_cond_targs[] = {
	0, 1, 2, 2, 3, 24, 27, 23,
	3, 4, 22, 23, 4, 5, 5, 6,
	7, 8, 9, 10, 11, 12, 13, 13,
	47, 14, 14, 15, 16, 15, 21, 17,
	16, 17, 18, 20, 19, 19, 20, 47,
	14, 21, 24, 25, 26, 29, 27, 28,
	30, 31, 32, 33, 34, 35, 36, 37,
	38, 39, 40, 41, 41, 42, 42, 43,
	44, 45, 45, 46, 13, 46, 13, 47,
	1, 33, 0
};

static const signed char _uri_cond_actions[] = {
	0, 0, 1, 0, 2, 2, 2, 2,
	0, 3, 0, 0, 0, 4, 0, 0,
	0, 0, 0, 0, 0, 0, 5, 0,
	6, 7, 0, 0, 0, 8, 9, 8,
	8, 0, 0, 10, 8, 0, 0, 11,
	12, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 13, 0, 14, 0, 0,
	0, 15, 0, 16, 17, 0, 18, 0,
	19, 20, 0
};

static const int uri_start = 47;
static const int uri_first_final = 47;
static const int uri_error = 0;

static const int uri_en_main = 47;


#line 76 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char *h1, *h2,
	*s1, *v1, *v3, *m1, *rp1, *rt1,
	*s2, *v2, *v4, *m2, *rp2, *rt2;
	int cs;
	
	
#line 168 "gen/ragel/http_simple-F1.c"
	{
		cs = (int)uri_start;
	}
	
#line 87 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
	
	
#line 176 "gen/ragel/http_simple-F1.c"
	{
		unsigned int _trans = 0;
		const char * _keys;
		const signed char * _inds;
		int _ic;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _uri_trans_keys + ((cs<<1)));
		_inds = ( _uri_indicies + (_uri_index_offsets[cs]));
		
		if ( ( (*( p))) >= 0 ) {
			_ic = (int)_uri_char_class[(int)( (*( p))) - 0];
			if ( _ic <= (int)(*( _keys+1)) && _ic >= (int)(*( _keys)) )
				_trans = (unsigned int)(*( _inds + (int)( _ic - (int)(*( _keys)) ) )); 
			else
				_trans = (unsigned int)_uri_index_defaults[cs];
		}
		else {
			_trans = (unsigned int)_uri_index_defaults[cs];
		}
		
		cs = (int)_uri_cond_targs[_trans];
		
		if ( _uri_cond_actions[_trans] != 0 ) {
			
			switch ( _uri_cond_actions[_trans] ) {
				case 12:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						h1 = p; }
					
#line 209 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						h2 = p; }
					
#line 219 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						m2 = p; }
					
#line 229 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						rt1 = p; }
					
#line 239 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						rt2 = p; }
					
#line 249 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						v3 = p; }
					
#line 259 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						v4 = p; }
					
#line 269 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						v2 = p; }
					
#line 279 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						s1 = p; }
					
#line 289 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						s2 = p; }
					
#line 299 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						rp1 = p; }
					
#line 309 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						rp2 = p; }
					
#line 319 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 66 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						
						if (h2) OUT("header: ", h1, h2);
						h1 = h2 = NULL;
					}
					
#line 332 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 71 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						outc(out, '\n'); }
					
#line 342 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						h2 = p; }
					
#line 352 "gen/ragel/http_simple-F1.c"
					
					{
#line 66 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						
						if (h2) OUT("header: ", h1, h2);
						h1 = h2 = NULL;
					}
					
#line 361 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						rp1 = p; }
					
#line 371 "gen/ragel/http_simple-F1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						rp2 = p; }
					
#line 377 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 49 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						
						h1 = h2 =
						s1 = v1 = v3 = m1 = rp1 = rt1 =
						s2 = v2 = v4 = m2 = rp2 = rt2 = NULL;
					}
					
#line 391 "gen/ragel/http_simple-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						m1 = p; }
					
#line 397 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						
						if (s2) {
							OUT("version: ", v1, v2);
							OUT("status: ", s1, s2);
							OUT("reason: ", rp1, rp2);
						}
						if (m2) {
							OUT("method: ", m1, m2);
							OUT("request: ", rt1, rt2);
							OUT("version: ", v3, v4);
						}
					}
					
#line 418 "gen/ragel/http_simple-F1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						h1 = p; }
					
#line 424 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 53 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						
						if (s2) {
							OUT("version: ", v1, v2);
							OUT("status: ", s1, s2);
							OUT("reason: ", rp1, rp2);
						}
						if (m2) {
							OUT("method: ", m1, m2);
							OUT("request: ", rt1, rt2);
							OUT("version: ", v3, v4);
						}
					}
					
#line 445 "gen/ragel/http_simple-F1.c"
					
					{
#line 71 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						outc(out, '\n'); }
					
#line 451 "gen/ragel/http_simple-F1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 49 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						
						h1 = h2 =
						s1 = v1 = v3 = m1 = rp1 = rt1 =
						s2 = v2 = v4 = m2 = rp2 = rt2 = NULL;
					}
					
#line 465 "gen/ragel/http_simple-F1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						m1 = p; }
					
#line 471 "gen/ragel/http_simple-F1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						v1 = p; }
					
#line 477 "gen/ragel/http_simple-F1.c"
					
					
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
	
#line 88 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
	
	
	in->p = p;
	in->pe = pe;
}
