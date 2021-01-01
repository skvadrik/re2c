#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"



#line 12 "gen/ragel/uri_simple-T1.c"
static const short _uri_key_offsets[] = {
	0, 0, 10, 24, 37, 48, 59, 71,
	83, 97, 114, 131, 150, 165, 182, 199,
	216, 233, 246, 265, 0
};

static const char _uri_trans_keys[] = {
	43, 58, 45, 46, 48, 57, 65, 90,
	97, 122, 10, 33, 35, 47, 61, 63,
	95, 126, 36, 59, 64, 90, 97, 122,
	10, 33, 35, 61, 63, 95, 126, 36,
	59, 64, 90, 97, 122, 10, 33, 61,
	95, 126, 36, 59, 63, 90, 97, 122,
	10, 33, 61, 95, 126, 36, 59, 63,
	90, 97, 122, 10, 33, 35, 61, 95,
	126, 36, 59, 63, 90, 97, 122, 10,
	33, 35, 61, 95, 126, 36, 59, 63,
	90, 97, 122, 10, 33, 35, 47, 61,
	63, 95, 126, 36, 59, 64, 90, 97,
	122, 10, 33, 35, 47, 58, 61, 63,
	64, 91, 95, 126, 36, 59, 65, 90,
	97, 122, 10, 33, 35, 47, 58, 61,
	63, 64, 91, 95, 126, 36, 59, 65,
	90, 97, 122, 10, 33, 35, 47, 61,
	63, 64, 95, 126, 36, 46, 48, 57,
	58, 59, 65, 90, 97, 122, 10, 33,
	35, 47, 61, 63, 64, 95, 126, 36,
	59, 65, 90, 97, 122, 10, 33, 35,
	47, 58, 61, 63, 64, 91, 95, 126,
	36, 59, 65, 90, 97, 122, 10, 33,
	35, 47, 58, 61, 63, 64, 91, 95,
	126, 36, 59, 65, 90, 97, 122, 10,
	33, 35, 61, 63, 95, 126, 36, 47,
	48, 57, 58, 59, 64, 90, 97, 122,
	10, 33, 35, 61, 63, 95, 126, 36,
	47, 48, 57, 58, 59, 64, 90, 97,
	122, 33, 61, 93, 95, 126, 36, 46,
	48, 59, 65, 90, 97, 122, 10, 33,
	35, 47, 61, 63, 64, 95, 126, 36,
	46, 48, 57, 58, 59, 65, 90, 97,
	122, 43, 45, 46, 48, 57, 65, 90,
	97, 122, 0
};

static const signed char _uri_single_lengths[] = {
	0, 2, 8, 7, 5, 5, 6, 6,
	8, 11, 11, 9, 9, 11, 11, 7,
	7, 5, 9, 1, 0
};

static const signed char _uri_range_lengths[] = {
	0, 4, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 5, 3, 3, 3, 5,
	5, 4, 5, 4, 0
};

static const short _uri_index_offsets[] = {
	0, 0, 7, 19, 30, 39, 48, 58,
	68, 80, 95, 110, 125, 138, 153, 168,
	181, 194, 204, 219, 0
};

static const signed char _uri_cond_targs[] = {
	1, 2, 1, 1, 1, 1, 0, 19,
	3, 4, 8, 3, 6, 3, 3, 3,
	3, 3, 0, 19, 3, 4, 3, 6,
	3, 3, 3, 3, 3, 0, 19, 5,
	5, 5, 5, 5, 5, 5, 0, 19,
	5, 5, 5, 5, 5, 5, 5, 0,
	19, 7, 4, 7, 7, 7, 7, 7,
	7, 0, 19, 7, 4, 7, 7, 7,
	7, 7, 7, 0, 19, 3, 4, 9,
	3, 6, 3, 3, 3, 3, 3, 0,
	19, 10, 4, 3, 12, 10, 6, 3,
	17, 10, 10, 10, 10, 10, 0, 19,
	10, 4, 3, 11, 10, 6, 13, 17,
	10, 10, 10, 10, 10, 0, 19, 12,
	4, 3, 12, 6, 13, 12, 12, 12,
	18, 12, 12, 12, 0, 19, 12, 4,
	3, 12, 6, 13, 12, 12, 12, 12,
	12, 0, 19, 14, 4, 3, 3, 14,
	6, 3, 17, 14, 14, 14, 14, 14,
	0, 19, 14, 4, 3, 15, 14, 6,
	3, 17, 14, 14, 14, 14, 14, 0,
	19, 3, 4, 3, 6, 3, 3, 3,
	16, 3, 3, 3, 0, 19, 3, 4,
	3, 6, 3, 3, 3, 16, 3, 3,
	3, 0, 17, 17, 14, 17, 17, 17,
	17, 17, 17, 0, 19, 12, 4, 3,
	12, 6, 13, 12, 12, 12, 18, 12,
	12, 12, 0, 1, 1, 1, 1, 1,
	0, 0, 1, 2, 3, 4, 5, 6,
	7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 0
};

static const signed char _uri_cond_actions[] = {
	0, 1, 0, 0, 0, 0, 0, 2,
	3, 4, 3, 3, 4, 3, 3, 3,
	3, 3, 0, 5, 0, 6, 0, 6,
	0, 0, 0, 0, 0, 0, 7, 8,
	8, 8, 8, 8, 8, 8, 0, 9,
	0, 0, 0, 0, 0, 0, 0, 0,
	10, 11, 12, 11, 11, 11, 11, 11,
	11, 0, 13, 0, 14, 0, 0, 0,
	0, 0, 0, 0, 5, 0, 6, 0,
	0, 6, 0, 0, 0, 0, 0, 0,
	5, 15, 6, 0, 16, 15, 6, 0,
	17, 15, 15, 15, 15, 15, 0, 18,
	19, 20, 19, 19, 19, 20, 21, 0,
	19, 19, 19, 19, 19, 0, 22, 23,
	24, 23, 23, 24, 25, 23, 23, 23,
	23, 23, 23, 23, 0, 5, 0, 6,
	0, 0, 6, 26, 0, 0, 0, 0,
	0, 0, 5, 17, 6, 0, 0, 17,
	6, 0, 17, 17, 17, 17, 17, 17,
	0, 18, 19, 20, 19, 19, 19, 20,
	19, 0, 19, 19, 19, 19, 19, 0,
	22, 23, 24, 23, 24, 23, 23, 23,
	23, 23, 23, 23, 0, 27, 28, 29,
	28, 29, 28, 28, 28, 28, 28, 28,
	28, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 27, 28, 29, 28,
	28, 29, 30, 28, 28, 28, 28, 28,
	28, 28, 0, 31, 31, 31, 31, 31,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};

static const int uri_start = 19;
static const int uri_first_final = 19;
static const int uri_error = 0;

static const int uri_en_main = 19;


#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*s1, *u1, *h1, *r1, *p1, *q1, *f1,
	*s2, *u2, *h2, *r2, *p2, *q2, *f2;
	int cs;
	
	
#line 163 "gen/ragel/uri_simple-T1.c"
	{
		cs = (int)uri_start;
	}
	
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
	
	
#line 171 "gen/ragel/uri_simple-T1.c"
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
				case 31:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						
						s1 = p;
						s2 = u1 = h1 = r1 = p1 = q1 = f1 =
						u2 = h2 = r2 = p2 = q2 = f2 = NULL;
					}
					
#line 244 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						s2 = p; }
					
#line 254 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						u1 = p; }
					
#line 264 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 26:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						u2 = p; }
					
#line 274 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						h1 = p; }
					
#line 284 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 294 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 304 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						q1 = p; }
					
#line 314 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						q2 = p; }
					
#line 324 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						f1 = p; }
					
#line 334 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						u1 = p; }
					
#line 344 "gen/ragel/uri_simple-T1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						h1 = p; }
					
#line 350 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						h2 = p; }
					
#line 360 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 366 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 28:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 376 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 382 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 392 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 398 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 408 "gen/ragel/uri_simple-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						
						OUT("scheme: ", s1, s2);
						if (u2) OUT("user: ", u1, u2);
						if (h1) OUT("host: ", h1, h2);
						if (r2 - r1 > 1) OUT("port: ", r1, r2);
						OUT("path: ", p1, p2);
						if (q1) OUT("query: ", q1, q2);
						if (f1) OUT("fragment: ", f1, f2);
						outc(out, '\n');
					}
					
#line 423 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						q1 = p; }
					
#line 433 "gen/ragel/uri_simple-T1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						q2 = p; }
					
#line 439 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						q2 = p; }
					
#line 449 "gen/ragel/uri_simple-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						
						OUT("scheme: ", s1, s2);
						if (u2) OUT("user: ", u1, u2);
						if (h1) OUT("host: ", h1, h2);
						if (r2 - r1 > 1) OUT("port: ", r1, r2);
						OUT("path: ", p1, p2);
						if (q1) OUT("query: ", q1, q2);
						if (f1) OUT("fragment: ", f1, f2);
						outc(out, '\n');
					}
					
#line 464 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						f2 = p; }
					
#line 474 "gen/ragel/uri_simple-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						
						OUT("scheme: ", s1, s2);
						if (u2) OUT("user: ", u1, u2);
						if (h1) OUT("host: ", h1, h2);
						if (r2 - r1 > 1) OUT("port: ", r1, r2);
						OUT("path: ", p1, p2);
						if (q1) OUT("query: ", q1, q2);
						if (f1) OUT("fragment: ", f1, f2);
						outc(out, '\n');
					}
					
#line 489 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						u2 = p; }
					
#line 499 "gen/ragel/uri_simple-T1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						h2 = p; }
					
#line 505 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 511 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 30:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						u2 = p; }
					
#line 521 "gen/ragel/uri_simple-T1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 527 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 533 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						h2 = p; }
					
#line 543 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 549 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 555 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r1 = p; }
					
#line 565 "gen/ragel/uri_simple-T1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 571 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 577 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 29:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 587 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 593 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 599 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 609 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 615 "gen/ragel/uri_simple-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						
						OUT("scheme: ", s1, s2);
						if (u2) OUT("user: ", u1, u2);
						if (h1) OUT("host: ", h1, h2);
						if (r2 - r1 > 1) OUT("port: ", r1, r2);
						OUT("path: ", p1, p2);
						if (q1) OUT("query: ", q1, q2);
						if (f1) OUT("fragment: ", f1, f2);
						outc(out, '\n');
					}
					
#line 630 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						q1 = p; }
					
#line 640 "gen/ragel/uri_simple-T1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						q2 = p; }
					
#line 646 "gen/ragel/uri_simple-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						
						OUT("scheme: ", s1, s2);
						if (u2) OUT("user: ", u1, u2);
						if (h1) OUT("host: ", h1, h2);
						if (r2 - r1 > 1) OUT("port: ", r1, r2);
						OUT("path: ", p1, p2);
						if (q1) OUT("query: ", q1, q2);
						if (f1) OUT("fragment: ", f1, f2);
						outc(out, '\n');
					}
					
#line 661 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						f1 = p; }
					
#line 671 "gen/ragel/uri_simple-T1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						f2 = p; }
					
#line 677 "gen/ragel/uri_simple-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						
						OUT("scheme: ", s1, s2);
						if (u2) OUT("user: ", u1, u2);
						if (h1) OUT("host: ", h1, h2);
						if (r2 - r1 > 1) OUT("port: ", r1, r2);
						OUT("path: ", p1, p2);
						if (q1) OUT("query: ", q1, q2);
						if (f1) OUT("fragment: ", f1, f2);
						outc(out, '\n');
					}
					
#line 692 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						u2 = p; }
					
#line 702 "gen/ragel/uri_simple-T1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r1 = p; }
					
#line 708 "gen/ragel/uri_simple-T1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 714 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 720 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						h2 = p; }
					
#line 730 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 736 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 742 "gen/ragel/uri_simple-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						
						OUT("scheme: ", s1, s2);
						if (u2) OUT("user: ", u1, u2);
						if (h1) OUT("host: ", h1, h2);
						if (r2 - r1 > 1) OUT("port: ", r1, r2);
						OUT("path: ", p1, p2);
						if (q1) OUT("query: ", q1, q2);
						if (f1) OUT("fragment: ", f1, f2);
						outc(out, '\n');
					}
					
#line 757 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r1 = p; }
					
#line 767 "gen/ragel/uri_simple-T1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 773 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 779 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 785 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 27:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 795 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 801 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 807 "gen/ragel/uri_simple-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						
						OUT("scheme: ", s1, s2);
						if (u2) OUT("user: ", u1, u2);
						if (h1) OUT("host: ", h1, h2);
						if (r2 - r1 > 1) OUT("port: ", r1, r2);
						OUT("path: ", p1, p2);
						if (q1) OUT("query: ", q1, q2);
						if (f1) OUT("fragment: ", f1, f2);
						outc(out, '\n');
					}
					
#line 822 "gen/ragel/uri_simple-T1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r1 = p; }
					
#line 832 "gen/ragel/uri_simple-T1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 838 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 844 "gen/ragel/uri_simple-T1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 850 "gen/ragel/uri_simple-T1.c"
					
					{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						
						OUT("scheme: ", s1, s2);
						if (u2) OUT("user: ", u1, u2);
						if (h1) OUT("host: ", h1, h2);
						if (r2 - r1 > 1) OUT("port: ", r1, r2);
						OUT("path: ", p1, p2);
						if (q1) OUT("query: ", q1, q2);
						if (f1) OUT("fragment: ", f1, f2);
						outc(out, '\n');
					}
					
#line 865 "gen/ragel/uri_simple-T1.c"
					
					
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
	
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
	
	
	in->p = p;
	in->pe = pe;
}
