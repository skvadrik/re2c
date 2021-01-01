#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"



#line 12 "gen/ragel/uri_simple-F1.c"
static const char _uri_trans_keys[] = {
	1, 0, 4, 7, 0, 9, 0, 9,
	0, 9, 0, 9, 0, 9, 0, 9,
	0, 9, 0, 10, 0, 10, 0, 9,
	0, 9, 0, 10, 0, 10, 0, 9,
	0, 9, 2, 11, 0, 9, 4, 6,
	0
};

static const signed char _uri_char_class[] = {
	0, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 2,
	1, 3, 2, 2, 2, 2, 2, 2,
	2, 4, 2, 4, 4, 5, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6,
	7, 2, 1, 2, 1, 8, 9, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 10, 1, 11, 1, 2, 1, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4,
	4, 1, 1, 1, 2, 0
};

static const short _uri_index_offsets[] = {
	0, 0, 4, 14, 24, 34, 44, 54,
	64, 74, 85, 96, 106, 116, 127, 138,
	148, 158, 168, 178, 0
};

static const signed char _uri_indicies[] = {
	1, 0, 1, 2, 4, 0, 5, 6,
	5, 7, 5, 5, 8, 5, 10, 0,
	9, 11, 9, 9, 9, 9, 12, 9,
	14, 0, 15, 0, 15, 15, 15, 15,
	15, 15, 17, 0, 16, 0, 16, 16,
	16, 16, 16, 16, 19, 0, 20, 21,
	20, 20, 20, 20, 20, 20, 23, 0,
	22, 24, 22, 22, 22, 22, 22, 22,
	10, 0, 9, 11, 9, 26, 9, 9,
	12, 9, 10, 0, 27, 11, 27, 9,
	27, 28, 12, 9, 29, 31, 0, 32,
	33, 32, 34, 32, 35, 36, 37, 38,
	40, 0, 41, 42, 41, 43, 44, 41,
	45, 46, 10, 0, 47, 11, 47, 9,
	47, 47, 12, 48, 10, 0, 50, 11,
	50, 9, 50, 9, 12, 9, 29, 31,
	0, 52, 33, 52, 34, 52, 53, 36,
	34, 38, 40, 0, 43, 42, 43, 43,
	55, 43, 45, 43, 57, 0, 58, 59,
	58, 58, 60, 58, 61, 58, 38, 0,
	38, 0, 38, 38, 0, 0, 0, 51,
	57, 0, 63, 59, 63, 58, 64, 63,
	61, 65, 67, 0, 67, 0
};

static const signed char _uri_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
};

static const signed char _uri_cond_targs[] = {
	0, 1, 2, 2, 19, 3, 4, 8,
	6, 3, 19, 4, 6, 4, 19, 5,
	5, 19, 6, 19, 7, 4, 7, 19,
	4, 8, 9, 10, 12, 17, 10, 19,
	10, 4, 3, 11, 6, 13, 17, 11,
	19, 12, 4, 3, 18, 6, 13, 12,
	13, 13, 14, 14, 14, 15, 15, 16,
	16, 19, 3, 4, 16, 6, 18, 12,
	18, 13, 19, 1, 0
};

static const signed char _uri_cond_actions[] = {
	0, 0, 1, 0, 2, 3, 4, 3,
	4, 0, 5, 6, 6, 0, 7, 8,
	0, 9, 0, 10, 11, 12, 0, 13,
	14, 0, 0, 15, 16, 17, 0, 18,
	19, 20, 19, 19, 20, 21, 0, 0,
	22, 23, 24, 23, 23, 24, 25, 0,
	26, 0, 17, 0, 19, 19, 0, 23,
	0, 27, 28, 29, 28, 29, 0, 28,
	28, 30, 0, 31, 0
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
	
	
#line 122 "gen/ragel/uri_simple-F1.c"
	{
		cs = (int)uri_start;
	}
	
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
	
	
#line 130 "gen/ragel/uri_simple-F1.c"
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
		
		if ( ( (*( p))) <= 126 && ( (*( p))) >= 10 ) {
			_ic = (int)_uri_char_class[(int)( (*( p))) - 10];
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
				case 31:  {
					{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						
						s1 = p;
						s2 = u1 = h1 = r1 = p1 = q1 = f1 =
						u2 = h2 = r2 = p2 = q2 = f2 = NULL;
					}
					
#line 167 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						s2 = p; }
					
#line 177 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 16:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						u1 = p; }
					
#line 187 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 26:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						u2 = p; }
					
#line 197 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 17:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						h1 = p; }
					
#line 207 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 217 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 227 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						q1 = p; }
					
#line 237 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 14:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						q2 = p; }
					
#line 247 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						f1 = p; }
					
#line 257 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 15:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						u1 = p; }
					
#line 267 "gen/ragel/uri_simple-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						h1 = p; }
					
#line 273 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 19:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						h2 = p; }
					
#line 283 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 289 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 28:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 299 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 305 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 315 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 321 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 331 "gen/ragel/uri_simple-F1.c"
					
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
					
#line 346 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						q1 = p; }
					
#line 356 "gen/ragel/uri_simple-F1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						q2 = p; }
					
#line 362 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 13:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						q2 = p; }
					
#line 372 "gen/ragel/uri_simple-F1.c"
					
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
					
#line 387 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						f2 = p; }
					
#line 397 "gen/ragel/uri_simple-F1.c"
					
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
					
#line 412 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 21:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						u2 = p; }
					
#line 422 "gen/ragel/uri_simple-F1.c"
					
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						h2 = p; }
					
#line 428 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 434 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 30:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						u2 = p; }
					
#line 444 "gen/ragel/uri_simple-F1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 450 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 456 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 20:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						h2 = p; }
					
#line 466 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 472 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 478 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 23:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r1 = p; }
					
#line 488 "gen/ragel/uri_simple-F1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 494 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 500 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 29:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 510 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 516 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 522 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 532 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 538 "gen/ragel/uri_simple-F1.c"
					
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
					
#line 553 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						q1 = p; }
					
#line 563 "gen/ragel/uri_simple-F1.c"
					
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						q2 = p; }
					
#line 569 "gen/ragel/uri_simple-F1.c"
					
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
					
#line 584 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						f1 = p; }
					
#line 594 "gen/ragel/uri_simple-F1.c"
					
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						f2 = p; }
					
#line 600 "gen/ragel/uri_simple-F1.c"
					
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
					
#line 615 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 25:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						u2 = p; }
					
#line 625 "gen/ragel/uri_simple-F1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r1 = p; }
					
#line 631 "gen/ragel/uri_simple-F1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 637 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 643 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 18:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						h2 = p; }
					
#line 653 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 659 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 665 "gen/ragel/uri_simple-F1.c"
					
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
					
#line 680 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 24:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r1 = p; }
					
#line 690 "gen/ragel/uri_simple-F1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 696 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 702 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 708 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 27:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 718 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 724 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 730 "gen/ragel/uri_simple-F1.c"
					
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
					
#line 745 "gen/ragel/uri_simple-F1.c"
					
					
					break; 
				}
				case 22:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r1 = p; }
					
#line 755 "gen/ragel/uri_simple-F1.c"
					
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						r2 = p; }
					
#line 761 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p1 = p; }
					
#line 767 "gen/ragel/uri_simple-F1.c"
					
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/uri_simple.rl"
						p2 = p; }
					
#line 773 "gen/ragel/uri_simple-F1.c"
					
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
					
#line 788 "gen/ragel/uri_simple-F1.c"
					
					
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
