#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
#include "ragel/common.c"

const char *delim = "\n\n";


#line 74 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"



#line 12 "gen/ragel/http_simple-T1.c"
static const short _uri_key_offsets[] = {
	0, 0, 16, 34, 50, 51, 52, 53,
	54, 55, 57, 58, 60, 61, 77, 93,
	99, 105, 111, 117, 120, 136, 154, 167,
	181, 202, 218, 234, 245, 261, 273, 289,
	305, 320, 337, 354, 371, 386, 388, 389,
	391, 392, 394, 396, 398, 399, 405, 411,
	0
};

static const char _uri_trans_keys[] = {
	32, 33, 124, 126, 35, 39, 42, 43,
	45, 46, 48, 57, 65, 90, 94, 122,
	33, 43, 47, 61, 91, 93, 95, 126,
	36, 44, 45, 57, 58, 59, 65, 90,
	97, 122, 32, 33, 61, 64, 91, 93,
	95, 126, 36, 46, 48, 59, 65, 90,
	97, 122, 72, 84, 84, 80, 47, 48,
	57, 46, 48, 57, 10, 10, 33, 124,
	126, 35, 39, 42, 43, 45, 46, 48,
	57, 65, 90, 94, 122, 33, 58, 124,
	126, 35, 39, 42, 43, 45, 46, 48,
	57, 65, 90, 94, 122, 9, 10, 32,
	127, 0, 31, 9, 10, 32, 127, 0,
	31, 9, 10, 32, 127, 0, 31, 9,
	10, 32, 127, 0, 31, 9, 10, 32,
	10, 33, 124, 126, 35, 39, 42, 43,
	45, 46, 48, 57, 65, 90, 94, 122,
	9, 10, 32, 33, 124, 126, 35, 39,
	42, 43, 45, 46, 48, 57, 65, 90,
	94, 122, 33, 61, 93, 95, 126, 36,
	46, 48, 59, 65, 91, 97, 122, 32,
	33, 61, 93, 95, 126, 36, 46, 48,
	59, 65, 91, 97, 122, 32, 33, 43,
	58, 59, 61, 64, 91, 93, 95, 126,
	36, 44, 45, 46, 48, 57, 65, 90,
	97, 122, 32, 33, 47, 61, 63, 64,
	91, 93, 95, 126, 36, 59, 65, 90,
	97, 122, 32, 33, 47, 61, 63, 64,
	91, 93, 95, 126, 36, 59, 65, 90,
	97, 122, 32, 33, 61, 95, 126, 36,
	59, 63, 90, 97, 122, 32, 33, 47,
	61, 91, 93, 95, 126, 36, 59, 63,
	64, 65, 90, 97, 122, 32, 33, 47,
	61, 95, 126, 36, 59, 63, 90, 97,
	122, 32, 33, 47, 61, 91, 93, 95,
	126, 36, 59, 63, 64, 65, 90, 97,
	122, 32, 33, 47, 61, 63, 64, 91,
	93, 95, 126, 36, 59, 65, 90, 97,
	122, 32, 33, 47, 61, 93, 95, 126,
	36, 59, 63, 64, 65, 91, 97, 122,
	32, 33, 84, 124, 126, 35, 39, 42,
	43, 45, 46, 48, 57, 65, 90, 94,
	122, 32, 33, 84, 124, 126, 35, 39,
	42, 43, 45, 46, 48, 57, 65, 90,
	94, 122, 32, 33, 80, 124, 126, 35,
	39, 42, 43, 45, 46, 48, 57, 65,
	90, 94, 122, 32, 33, 47, 124, 126,
	35, 39, 42, 43, 45, 57, 65, 90,
	94, 122, 48, 57, 46, 48, 57, 32,
	48, 57, 48, 57, 48, 57, 32, 10,
	127, 0, 8, 11, 31, 10, 127, 0,
	8, 11, 31, 33, 72, 124, 126, 35,
	39, 42, 43, 45, 46, 48, 57, 65,
	90, 94, 122, 0
};

static const signed char _uri_single_lengths[] = {
	0, 4, 8, 8, 1, 1, 1, 1,
	1, 0, 1, 0, 1, 4, 4, 4,
	4, 4, 4, 3, 4, 6, 5, 6,
	11, 10, 10, 5, 8, 6, 8, 10,
	7, 5, 5, 5, 5, 0, 1, 0,
	1, 0, 0, 0, 1, 2, 2, 4,
	0
};

static const signed char _uri_range_lengths[] = {
	0, 6, 5, 4, 0, 0, 0, 0,
	0, 1, 0, 1, 0, 6, 6, 1,
	1, 1, 1, 0, 6, 6, 4, 4,
	5, 3, 3, 3, 4, 3, 4, 3,
	4, 6, 6, 6, 5, 1, 0, 1,
	0, 1, 1, 1, 0, 2, 2, 6,
	0
};

static const short _uri_index_offsets[] = {
	0, 0, 11, 25, 38, 40, 42, 44,
	46, 48, 50, 52, 54, 56, 67, 78,
	84, 90, 96, 102, 106, 117, 130, 140,
	151, 168, 182, 196, 205, 218, 228, 241,
	255, 267, 279, 291, 303, 314, 316, 318,
	320, 322, 324, 326, 328, 330, 335, 340,
	0
};

static const signed char _uri_cond_targs[] = {
	2, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 0, 3, 24, 27, 3, 23,
	23, 3, 3, 3, 24, 3, 24, 24,
	0, 4, 3, 3, 22, 23, 23, 3,
	3, 3, 3, 3, 3, 0, 5, 0,
	6, 0, 7, 0, 8, 0, 9, 0,
	10, 0, 11, 0, 12, 0, 13, 0,
	47, 14, 14, 14, 14, 14, 14, 14,
	14, 14, 0, 14, 15, 14, 14, 14,
	14, 14, 14, 14, 14, 0, 15, 21,
	15, 0, 0, 16, 17, 21, 16, 0,
	0, 16, 17, 20, 16, 0, 0, 18,
	19, 21, 16, 0, 0, 16, 19, 20,
	19, 0, 47, 14, 14, 14, 14, 14,
	14, 14, 14, 14, 0, 15, 47, 15,
	14, 14, 14, 14, 14, 14, 14, 14,
	14, 0, 23, 23, 23, 23, 23, 23,
	23, 23, 23, 0, 4, 23, 23, 23,
	23, 23, 23, 23, 23, 23, 0, 4,
	3, 24, 25, 3, 3, 22, 23, 23,
	3, 3, 3, 24, 24, 24, 24, 0,
	4, 26, 29, 26, 27, 28, 23, 23,
	26, 26, 26, 26, 26, 0, 4, 26,
	27, 26, 27, 28, 23, 23, 26, 26,
	26, 26, 26, 0, 4, 27, 27, 27,
	27, 27, 27, 27, 0, 4, 28, 27,
	28, 23, 23, 28, 28, 28, 27, 28,
	28, 0, 4, 27, 30, 27, 27, 27,
	27, 27, 27, 0, 4, 31, 27, 31,
	32, 32, 31, 31, 31, 27, 31, 31,
	0, 4, 31, 27, 31, 27, 32, 32,
	32, 31, 31, 31, 31, 31, 0, 4,
	32, 27, 32, 32, 32, 32, 32, 27,
	32, 32, 0, 2, 1, 34, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 2,
	1, 35, 1, 1, 1, 1, 1, 1,
	1, 1, 0, 2, 1, 36, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 2,
	1, 37, 1, 1, 1, 1, 1, 1,
	1, 0, 38, 0, 39, 0, 40, 0,
	41, 0, 42, 0, 43, 0, 44, 0,
	45, 0, 13, 0, 0, 0, 46, 13,
	0, 0, 0, 46, 1, 33, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 0,
	1, 2, 3, 4, 5, 6, 7, 8,
	9, 10, 11, 12, 13, 14, 15, 16,
	17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30, 31, 32,
	33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 0
};

static const signed char _uri_cond_actions[] = {
	1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
	0, 3, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 4, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 5, 0,
	6, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 8, 9,
	8, 0, 0, 0, 8, 9, 8, 0,
	0, 0, 0, 10, 0, 0, 0, 0,
	8, 9, 8, 0, 0, 0, 0, 10,
	0, 0, 11, 12, 12, 12, 12, 12,
	12, 12, 12, 12, 0, 0, 11, 0,
	12, 12, 12, 12, 12, 12, 12, 12,
	12, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 3, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 3,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	3, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 3, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 3, 0, 0, 0,
	0, 0, 0, 0, 0, 3, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 3, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 3, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 3, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 3,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	13, 0, 14, 0, 0, 0, 0, 0,
	15, 0, 17, 0, 0, 0, 16, 18,
	0, 0, 0, 0, 19, 20, 19, 19,
	19, 19, 19, 19, 19, 19, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
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
	
	
#line 236 "gen/ragel/http_simple-T1.c"
	{
		cs = (int)uri_start;
	}
	
#line 87 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
	
	
#line 244 "gen/ragel/http_simple-T1.c"
	{
		int _klen;
		unsigned int _trans = 0;
		const char * _keys;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _uri_trans_keys + (_uri_key_offsets[cs]));
		_trans = (unsigned int)_uri_index_offsets[cs];
		
		_klen = (int)_uri_single_lengths[cs];
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
		
		_klen = (int)_uri_range_lengths[cs];
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
		cs = (int)_uri_cond_targs[_trans];
		
		if ( _uri_cond_actions[_trans] != 0 ) {
			
			switch ( _uri_cond_actions[_trans] ) {
				case 12:  {
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						h1 = p; }
					
#line 313 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						h2 = p; }
					
#line 323 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						m2 = p; }
					
#line 333 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						rt1 = p; }
					
#line 343 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						rt2 = p; }
					
#line 353 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						v3 = p; }
					
#line 363 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						v4 = p; }
					
#line 373 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						v2 = p; }
					
#line 383 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						s1 = p; }
					
#line 393 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						s2 = p; }
					
#line 403 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						rp1 = p; }
					
#line 413 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						rp2 = p; }
					
#line 423 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 66 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						
						if (h2) OUT("header: ", h1, h2);
						h1 = h2 = NULL;
					}
					
#line 436 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 71 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						outc(out, '\n'); }
					
#line 446 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						h2 = p; }
					
#line 456 "gen/ragel/http_simple-T1.c"
					
					{
#line 66 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						
						if (h2) OUT("header: ", h1, h2);
						h1 = h2 = NULL;
					}
					
#line 465 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						rp1 = p; }
					
#line 475 "gen/ragel/http_simple-T1.c"
					
					{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						rp2 = p; }
					
#line 481 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 49 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						
						h1 = h2 =
						s1 = v1 = v3 = m1 = rp1 = rt1 =
						s2 = v2 = v4 = m2 = rp2 = rt2 = NULL;
					}
					
#line 495 "gen/ragel/http_simple-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						m1 = p; }
					
#line 501 "gen/ragel/http_simple-T1.c"
					
					
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
					
#line 522 "gen/ragel/http_simple-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						h1 = p; }
					
#line 528 "gen/ragel/http_simple-T1.c"
					
					
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
					
#line 549 "gen/ragel/http_simple-T1.c"
					
					{
#line 71 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						outc(out, '\n'); }
					
#line 555 "gen/ragel/http_simple-T1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 49 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						
						h1 = h2 =
						s1 = v1 = v3 = m1 = rp1 = rt1 =
						s2 = v2 = v4 = m2 = rp2 = rt2 = NULL;
					}
					
#line 569 "gen/ragel/http_simple-T1.c"
					
					{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						m1 = p; }
					
#line 575 "gen/ragel/http_simple-T1.c"
					
					{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
						v1 = p; }
					
#line 581 "gen/ragel/http_simple-T1.c"
					
					
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
