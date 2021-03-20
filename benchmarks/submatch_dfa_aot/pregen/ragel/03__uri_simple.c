#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"



#line 12 "gen/ragel/03__uri_simple.c"
static const int uri_start = 19;
static const int uri_first_final = 19;
static const int uri_error = 0;

static const int uri_en_main = 19;


#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*s1, *u1, *h1, *r1, *p1, *q1, *f1,
	*s2, *u2, *h2, *r2, *p2, *q2, *f2;
	int cs;
	
	
#line 33 "gen/ragel/03__uri_simple.c"
	{
		cs = (int)uri_start;
	}
	
#line 50 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
	
	
#line 41 "gen/ragel/03__uri_simple.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 19:
			goto st_case_19;
			case 0:
			goto st_case_0;
			case 1:
			goto st_case_1;
			case 2:
			goto st_case_2;
			case 3:
			goto st_case_3;
			case 4:
			goto st_case_4;
			case 5:
			goto st_case_5;
			case 6:
			goto st_case_6;
			case 7:
			goto st_case_7;
			case 8:
			goto st_case_8;
			case 9:
			goto st_case_9;
			case 10:
			goto st_case_10;
			case 11:
			goto st_case_11;
			case 12:
			goto st_case_12;
			case 13:
			goto st_case_13;
			case 14:
			goto st_case_14;
			case 15:
			goto st_case_15;
			case 16:
			goto st_case_16;
			case 17:
			goto st_case_17;
			case 18:
			goto st_case_18;
		}
		goto st_out;
		_ctr4:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 93 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 99 "gen/ragel/03__uri_simple.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 114 "gen/ragel/03__uri_simple.c"
		
		goto _st19;
		_ctr10:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 122 "gen/ragel/03__uri_simple.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 137 "gen/ragel/03__uri_simple.c"
		
		goto _st19;
		_ctr14:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			f1 = p; }
		
#line 145 "gen/ragel/03__uri_simple.c"
		
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			f2 = p; }
		
#line 151 "gen/ragel/03__uri_simple.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 166 "gen/ragel/03__uri_simple.c"
		
		goto _st19;
		_ctr17:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			f2 = p; }
		
#line 174 "gen/ragel/03__uri_simple.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 189 "gen/ragel/03__uri_simple.c"
		
		goto _st19;
		_ctr19:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			q1 = p; }
		
#line 197 "gen/ragel/03__uri_simple.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			q2 = p; }
		
#line 203 "gen/ragel/03__uri_simple.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 218 "gen/ragel/03__uri_simple.c"
		
		goto _st19;
		_ctr23:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			q2 = p; }
		
#line 226 "gen/ragel/03__uri_simple.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 241 "gen/ragel/03__uri_simple.c"
		
		goto _st19;
		_ctr31:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			h2 = p; }
		
#line 249 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 255 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 261 "gen/ragel/03__uri_simple.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 276 "gen/ragel/03__uri_simple.c"
		
		goto _st19;
		_ctr40:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r1 = p; }
		
#line 284 "gen/ragel/03__uri_simple.c"
		
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 290 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 296 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 302 "gen/ragel/03__uri_simple.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 317 "gen/ragel/03__uri_simple.c"
		
		goto _st19;
		_ctr57:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 325 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 331 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 337 "gen/ragel/03__uri_simple.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 352 "gen/ragel/03__uri_simple.c"
		
		goto _st19;
		_st19:
		p+= 1;
		if ( p == pe )
			goto _test_eof19;
		st_case_19:
		if ( ( (*( p))) == 43 ) {
			goto _ctr67;
		}
		if ( ( (*( p))) < 48 ) {
			if ( 45 <= ( (*( p))) && ( (*( p))) <= 46 ) {
				goto _ctr67;
			}
		} else if ( ( (*( p))) > 57 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _ctr67;
				}
			} else if ( ( (*( p))) >= 65 ) {
				goto _ctr67;
			}
		} else {
			goto _ctr67;
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr67:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			
			s1 = p;
			s2 = u1 = h1 = r1 = p1 = q1 = f1 =
			u2 = h2 = r2 = p2 = q2 = f2 = NULL;
		}
		
#line 394 "gen/ragel/03__uri_simple.c"
		
		goto _st1;
		_st1:
		p+= 1;
		if ( p == pe )
			goto _test_eof1;
		st_case_1:
		switch( ( (*( p))) ) {
			case 43: {
				goto _st1;
			}
			case 58: {
				goto _ctr2;
			}
		}
		if ( ( (*( p))) < 48 ) {
			if ( 45 <= ( (*( p))) && ( (*( p))) <= 46 ) {
				goto _st1;
			}
		} else if ( ( (*( p))) > 57 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st1;
				}
			} else if ( ( (*( p))) >= 65 ) {
				goto _st1;
			}
		} else {
			goto _st1;
		}
		{
			goto _st0;
		}
		_ctr2:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			s2 = p; }
		
#line 433 "gen/ragel/03__uri_simple.c"
		
		goto _st2;
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr4;
			}
			case 33: {
				goto _ctr5;
			}
			case 35: {
				goto _ctr6;
			}
			case 47: {
				goto _ctr7;
			}
			case 61: {
				goto _ctr5;
			}
			case 63: {
				goto _ctr8;
			}
			case 95: {
				goto _ctr5;
			}
			case 126: {
				goto _ctr5;
			}
		}
		if ( ( (*( p))) < 64 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _ctr5;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _ctr5;
			}
		} else {
			goto _ctr5;
		}
		{
			goto _st0;
		}
		_ctr5:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 486 "gen/ragel/03__uri_simple.c"
		
		goto _st3;
		_ctr34:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			h2 = p; }
		
#line 494 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 500 "gen/ragel/03__uri_simple.c"
		
		goto _st3;
		_ctr43:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r1 = p; }
		
#line 508 "gen/ragel/03__uri_simple.c"
		
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 514 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 520 "gen/ragel/03__uri_simple.c"
		
		goto _st3;
		_ctr58:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 528 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 534 "gen/ragel/03__uri_simple.c"
		
		goto _st3;
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr10;
			}
			case 33: {
				goto _st3;
			}
			case 35: {
				goto _ctr11;
			}
			case 61: {
				goto _st3;
			}
			case 63: {
				goto _ctr12;
			}
			case 95: {
				goto _st3;
			}
			case 126: {
				goto _st3;
			}
		}
		if ( ( (*( p))) < 64 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _st3;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st3;
			}
		} else {
			goto _st3;
		}
		{
			goto _st0;
		}
		_ctr6:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 584 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 590 "gen/ragel/03__uri_simple.c"
		
		goto _st4;
		_ctr11:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 598 "gen/ragel/03__uri_simple.c"
		
		goto _st4;
		_ctr21:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			q1 = p; }
		
#line 606 "gen/ragel/03__uri_simple.c"
		
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			q2 = p; }
		
#line 612 "gen/ragel/03__uri_simple.c"
		
		goto _st4;
		_ctr24:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			q2 = p; }
		
#line 620 "gen/ragel/03__uri_simple.c"
		
		goto _st4;
		_ctr33:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			h2 = p; }
		
#line 628 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 634 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 640 "gen/ragel/03__uri_simple.c"
		
		goto _st4;
		_ctr42:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r1 = p; }
		
#line 648 "gen/ragel/03__uri_simple.c"
		
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 654 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 660 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 666 "gen/ragel/03__uri_simple.c"
		
		goto _st4;
		_ctr59:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 674 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 680 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 686 "gen/ragel/03__uri_simple.c"
		
		goto _st4;
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr14;
			}
			case 33: {
				goto _ctr15;
			}
			case 61: {
				goto _ctr15;
			}
			case 95: {
				goto _ctr15;
			}
			case 126: {
				goto _ctr15;
			}
		}
		if ( ( (*( p))) < 63 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _ctr15;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _ctr15;
			}
		} else {
			goto _ctr15;
		}
		{
			goto _st0;
		}
		_ctr15:
		{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			f1 = p; }
		
#line 730 "gen/ragel/03__uri_simple.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr17;
			}
			case 33: {
				goto _st5;
			}
			case 61: {
				goto _st5;
			}
			case 95: {
				goto _st5;
			}
			case 126: {
				goto _st5;
			}
		}
		if ( ( (*( p))) < 63 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _st5;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st5;
			}
		} else {
			goto _st5;
		}
		{
			goto _st0;
		}
		_ctr8:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 774 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 780 "gen/ragel/03__uri_simple.c"
		
		goto _st6;
		_ctr12:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 788 "gen/ragel/03__uri_simple.c"
		
		goto _st6;
		_ctr36:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			h2 = p; }
		
#line 796 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 802 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 808 "gen/ragel/03__uri_simple.c"
		
		goto _st6;
		_ctr45:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r1 = p; }
		
#line 816 "gen/ragel/03__uri_simple.c"
		
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 822 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 828 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 834 "gen/ragel/03__uri_simple.c"
		
		goto _st6;
		_ctr61:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 842 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 848 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p2 = p; }
		
#line 854 "gen/ragel/03__uri_simple.c"
		
		goto _st6;
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr19;
			}
			case 33: {
				goto _ctr20;
			}
			case 35: {
				goto _ctr21;
			}
			case 61: {
				goto _ctr20;
			}
			case 95: {
				goto _ctr20;
			}
			case 126: {
				goto _ctr20;
			}
		}
		if ( ( (*( p))) < 63 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _ctr20;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _ctr20;
			}
		} else {
			goto _ctr20;
		}
		{
			goto _st0;
		}
		_ctr20:
		{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			q1 = p; }
		
#line 901 "gen/ragel/03__uri_simple.c"
		
		goto _st7;
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 33: {
				goto _st7;
			}
			case 35: {
				goto _ctr24;
			}
			case 61: {
				goto _st7;
			}
			case 95: {
				goto _st7;
			}
			case 126: {
				goto _st7;
			}
		}
		if ( ( (*( p))) < 63 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _st7;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st7;
			}
		} else {
			goto _st7;
		}
		{
			goto _st0;
		}
		_ctr7:
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 948 "gen/ragel/03__uri_simple.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr10;
			}
			case 33: {
				goto _st3;
			}
			case 35: {
				goto _ctr11;
			}
			case 47: {
				goto _st9;
			}
			case 61: {
				goto _st3;
			}
			case 63: {
				goto _ctr12;
			}
			case 95: {
				goto _st3;
			}
			case 126: {
				goto _st3;
			}
		}
		if ( ( (*( p))) < 64 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _st3;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st3;
			}
		} else {
			goto _st3;
		}
		{
			goto _st0;
		}
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr10;
			}
			case 33: {
				goto _ctr27;
			}
			case 35: {
				goto _ctr11;
			}
			case 47: {
				goto _st3;
			}
			case 58: {
				goto _ctr28;
			}
			case 61: {
				goto _ctr27;
			}
			case 63: {
				goto _ctr12;
			}
			case 64: {
				goto _st3;
			}
			case 91: {
				goto _ctr29;
			}
			case 95: {
				goto _ctr27;
			}
			case 126: {
				goto _ctr27;
			}
		}
		if ( ( (*( p))) < 65 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _ctr27;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _ctr27;
			}
		} else {
			goto _ctr27;
		}
		{
			goto _st0;
		}
		_ctr27:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			u1 = p; }
		
#line 1055 "gen/ragel/03__uri_simple.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			h1 = p; }
		
#line 1061 "gen/ragel/03__uri_simple.c"
		
		goto _st10;
		_ctr32:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			h2 = p; }
		
#line 1069 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 1075 "gen/ragel/03__uri_simple.c"
		
		goto _st10;
		_st10:
		p+= 1;
		if ( p == pe )
			goto _test_eof10;
		st_case_10:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr31;
			}
			case 33: {
				goto _ctr32;
			}
			case 35: {
				goto _ctr33;
			}
			case 47: {
				goto _ctr34;
			}
			case 58: {
				goto _ctr35;
			}
			case 61: {
				goto _ctr32;
			}
			case 63: {
				goto _ctr36;
			}
			case 64: {
				goto _ctr37;
			}
			case 91: {
				goto _st17;
			}
			case 95: {
				goto _ctr32;
			}
			case 126: {
				goto _ctr32;
			}
		}
		if ( ( (*( p))) < 65 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _ctr32;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _ctr32;
			}
		} else {
			goto _ctr32;
		}
		{
			goto _st0;
		}
		_ctr35:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			h2 = p; }
		
#line 1137 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 1143 "gen/ragel/03__uri_simple.c"
		
		goto _st11;
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr40;
			}
			case 33: {
				goto _ctr41;
			}
			case 35: {
				goto _ctr42;
			}
			case 47: {
				goto _ctr43;
			}
			case 61: {
				goto _ctr41;
			}
			case 63: {
				goto _ctr45;
			}
			case 64: {
				goto _ctr46;
			}
			case 95: {
				goto _ctr41;
			}
			case 126: {
				goto _ctr41;
			}
		}
		if ( ( (*( p))) < 58 ) {
			if ( ( (*( p))) > 46 ) {
				if ( 48 <= ( (*( p))) ) {
					goto _ctr44;
				}
			} else if ( ( (*( p))) >= 36 ) {
				goto _ctr41;
			}
		} else if ( ( (*( p))) > 59 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _ctr41;
				}
			} else if ( ( (*( p))) >= 65 ) {
				goto _ctr41;
			}
		} else {
			goto _ctr41;
		}
		{
			goto _st0;
		}
		_ctr28:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			u1 = p; }
		
#line 1207 "gen/ragel/03__uri_simple.c"
		
		goto _st12;
		_ctr41:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r1 = p; }
		
#line 1215 "gen/ragel/03__uri_simple.c"
		
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 1221 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 1227 "gen/ragel/03__uri_simple.c"
		
		goto _st12;
		_ctr63:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 1235 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 1241 "gen/ragel/03__uri_simple.c"
		
		goto _st12;
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr10;
			}
			case 33: {
				goto _st12;
			}
			case 35: {
				goto _ctr11;
			}
			case 47: {
				goto _st3;
			}
			case 61: {
				goto _st12;
			}
			case 63: {
				goto _ctr12;
			}
			case 64: {
				goto _ctr48;
			}
			case 95: {
				goto _st12;
			}
			case 126: {
				goto _st12;
			}
		}
		if ( ( (*( p))) < 65 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _st12;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st12;
			}
		} else {
			goto _st12;
		}
		{
			goto _st0;
		}
		_ctr37:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			u2 = p; }
		
#line 1297 "gen/ragel/03__uri_simple.c"
		
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			h2 = p; }
		
#line 1303 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 1309 "gen/ragel/03__uri_simple.c"
		
		goto _st13;
		_ctr46:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			u2 = p; }
		
#line 1317 "gen/ragel/03__uri_simple.c"
		
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r1 = p; }
		
#line 1323 "gen/ragel/03__uri_simple.c"
		
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 1329 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 1335 "gen/ragel/03__uri_simple.c"
		
		goto _st13;
		_ctr48:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			u2 = p; }
		
#line 1343 "gen/ragel/03__uri_simple.c"
		
		goto _st13;
		_ctr65:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			u2 = p; }
		
#line 1351 "gen/ragel/03__uri_simple.c"
		
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 1357 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 1363 "gen/ragel/03__uri_simple.c"
		
		goto _st13;
		_st13:
		p+= 1;
		if ( p == pe )
			goto _test_eof13;
		st_case_13:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr10;
			}
			case 33: {
				goto _ctr50;
			}
			case 35: {
				goto _ctr11;
			}
			case 47: {
				goto _st3;
			}
			case 58: {
				goto _st3;
			}
			case 61: {
				goto _ctr50;
			}
			case 63: {
				goto _ctr12;
			}
			case 64: {
				goto _st3;
			}
			case 91: {
				goto _ctr29;
			}
			case 95: {
				goto _ctr50;
			}
			case 126: {
				goto _ctr50;
			}
		}
		if ( ( (*( p))) < 65 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _ctr50;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _ctr50;
			}
		} else {
			goto _ctr50;
		}
		{
			goto _st0;
		}
		_ctr50:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			h1 = p; }
		
#line 1425 "gen/ragel/03__uri_simple.c"
		
		goto _st14;
		_ctr52:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			h2 = p; }
		
#line 1433 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 1439 "gen/ragel/03__uri_simple.c"
		
		goto _st14;
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr31;
			}
			case 33: {
				goto _ctr52;
			}
			case 35: {
				goto _ctr33;
			}
			case 47: {
				goto _ctr34;
			}
			case 58: {
				goto _ctr53;
			}
			case 61: {
				goto _ctr52;
			}
			case 63: {
				goto _ctr36;
			}
			case 64: {
				goto _ctr34;
			}
			case 91: {
				goto _st17;
			}
			case 95: {
				goto _ctr52;
			}
			case 126: {
				goto _ctr52;
			}
		}
		if ( ( (*( p))) < 65 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _ctr52;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _ctr52;
			}
		} else {
			goto _ctr52;
		}
		{
			goto _st0;
		}
		_ctr53:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			h2 = p; }
		
#line 1501 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 1507 "gen/ragel/03__uri_simple.c"
		
		goto _st15;
		_st15:
		p+= 1;
		if ( p == pe )
			goto _test_eof15;
		st_case_15:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr40;
			}
			case 33: {
				goto _ctr43;
			}
			case 35: {
				goto _ctr42;
			}
			case 61: {
				goto _ctr43;
			}
			case 63: {
				goto _ctr45;
			}
			case 95: {
				goto _ctr43;
			}
			case 126: {
				goto _ctr43;
			}
		}
		if ( ( (*( p))) < 58 ) {
			if ( ( (*( p))) > 47 ) {
				{
					goto _ctr55;
				}
			} else if ( ( (*( p))) >= 36 ) {
				goto _ctr43;
			}
		} else if ( ( (*( p))) > 59 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _ctr43;
				}
			} else if ( ( (*( p))) >= 64 ) {
				goto _ctr43;
			}
		} else {
			goto _ctr43;
		}
		{
			goto _st0;
		}
		_ctr55:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r1 = p; }
		
#line 1565 "gen/ragel/03__uri_simple.c"
		
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 1571 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 1577 "gen/ragel/03__uri_simple.c"
		
		goto _st16;
		_ctr60:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 1585 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 1591 "gen/ragel/03__uri_simple.c"
		
		goto _st16;
		_st16:
		p+= 1;
		if ( p == pe )
			goto _test_eof16;
		st_case_16:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr57;
			}
			case 33: {
				goto _ctr58;
			}
			case 35: {
				goto _ctr59;
			}
			case 61: {
				goto _ctr58;
			}
			case 63: {
				goto _ctr61;
			}
			case 95: {
				goto _ctr58;
			}
			case 126: {
				goto _ctr58;
			}
		}
		if ( ( (*( p))) < 58 ) {
			if ( ( (*( p))) > 47 ) {
				{
					goto _ctr60;
				}
			} else if ( ( (*( p))) >= 36 ) {
				goto _ctr58;
			}
		} else if ( ( (*( p))) > 59 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _ctr58;
				}
			} else if ( ( (*( p))) >= 64 ) {
				goto _ctr58;
			}
		} else {
			goto _ctr58;
		}
		{
			goto _st0;
		}
		_ctr29:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			h1 = p; }
		
#line 1649 "gen/ragel/03__uri_simple.c"
		
		goto _st17;
		_st17:
		p+= 1;
		if ( p == pe )
			goto _test_eof17;
		st_case_17:
		switch( ( (*( p))) ) {
			case 33: {
				goto _st17;
			}
			case 61: {
				goto _st17;
			}
			case 93: {
				goto _st14;
			}
			case 95: {
				goto _st17;
			}
			case 126: {
				goto _st17;
			}
		}
		if ( ( (*( p))) < 48 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 46 ) {
				goto _st17;
			}
		} else if ( ( (*( p))) > 59 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st17;
				}
			} else if ( ( (*( p))) >= 65 ) {
				goto _st17;
			}
		} else {
			goto _st17;
		}
		{
			goto _st0;
		}
		_ctr44:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r1 = p; }
		
#line 1697 "gen/ragel/03__uri_simple.c"
		
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 1703 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 1709 "gen/ragel/03__uri_simple.c"
		
		goto _st18;
		_ctr64:
		{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			r2 = p; }
		
#line 1717 "gen/ragel/03__uri_simple.c"
		
		{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
			p1 = p; }
		
#line 1723 "gen/ragel/03__uri_simple.c"
		
		goto _st18;
		_st18:
		p+= 1;
		if ( p == pe )
			goto _test_eof18;
		st_case_18:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr57;
			}
			case 33: {
				goto _ctr63;
			}
			case 35: {
				goto _ctr59;
			}
			case 47: {
				goto _ctr58;
			}
			case 61: {
				goto _ctr63;
			}
			case 63: {
				goto _ctr61;
			}
			case 64: {
				goto _ctr65;
			}
			case 95: {
				goto _ctr63;
			}
			case 126: {
				goto _ctr63;
			}
		}
		if ( ( (*( p))) < 58 ) {
			if ( ( (*( p))) > 46 ) {
				if ( 48 <= ( (*( p))) ) {
					goto _ctr64;
				}
			} else if ( ( (*( p))) >= 36 ) {
				goto _ctr63;
			}
		} else if ( ( (*( p))) > 59 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _ctr63;
				}
			} else if ( ( (*( p))) >= 65 ) {
				goto _ctr63;
			}
		} else {
			goto _ctr63;
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof19: cs = 19; goto _test_eof; 
		_test_eof1: cs = 1; goto _test_eof; 
		_test_eof2: cs = 2; goto _test_eof; 
		_test_eof3: cs = 3; goto _test_eof; 
		_test_eof4: cs = 4; goto _test_eof; 
		_test_eof5: cs = 5; goto _test_eof; 
		_test_eof6: cs = 6; goto _test_eof; 
		_test_eof7: cs = 7; goto _test_eof; 
		_test_eof8: cs = 8; goto _test_eof; 
		_test_eof9: cs = 9; goto _test_eof; 
		_test_eof10: cs = 10; goto _test_eof; 
		_test_eof11: cs = 11; goto _test_eof; 
		_test_eof12: cs = 12; goto _test_eof; 
		_test_eof13: cs = 13; goto _test_eof; 
		_test_eof14: cs = 14; goto _test_eof; 
		_test_eof15: cs = 15; goto _test_eof; 
		_test_eof16: cs = 16; goto _test_eof; 
		_test_eof17: cs = 17; goto _test_eof; 
		_test_eof18: cs = 18; goto _test_eof; 
		
		_test_eof: {}
		if ( cs >= 19 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 51 "../../../benchmarks/submatch_dfa_aot/src/ragel/03__uri_simple.rl"
	
	
	in->p = p;
	in->pe = pe;
}
