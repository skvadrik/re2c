#line 1 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 37 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"



#line 9 "gen/ragel/submatch_03__uri_simple.c"
static const int uri_start = 19;
static const int uri_first_final = 19;
static const int uri_error = 0;

static const int uri_en_main = 19;


#line 39 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*s1, *u1, *h1, *r1, *p1, *q1, *f1,
	*s2, *u2, *h2, *r2, *p2, *q2, *f2;
	int cs;
	

#line 27 "gen/ragel/submatch_03__uri_simple.c"
	{
		cs = (int)uri_start;
	}
	
#line 50 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"


#line 32 "gen/ragel/submatch_03__uri_simple.c"
{
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
		_ctr4:
			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 80 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 85 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 25 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 99 "gen/ragel/submatch_03__uri_simple.c"

		goto _st19;
		_ctr10:
			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 106 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 25 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 120 "gen/ragel/submatch_03__uri_simple.c"

		goto _st19;
		_ctr14:
			{
#line 21 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			f1 = p; }
		
#line 127 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 21 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			f2 = p; }
		
#line 132 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 25 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 146 "gen/ragel/submatch_03__uri_simple.c"

		goto _st19;
		_ctr17:
			{
#line 21 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			f2 = p; }
		
#line 153 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 25 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 167 "gen/ragel/submatch_03__uri_simple.c"

		goto _st19;
		_ctr19:
			{
#line 20 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			q1 = p; }
		
#line 174 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 20 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			q2 = p; }
		
#line 179 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 25 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 193 "gen/ragel/submatch_03__uri_simple.c"

		goto _st19;
		_ctr23:
			{
#line 20 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			q2 = p; }
		
#line 200 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 25 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 214 "gen/ragel/submatch_03__uri_simple.c"

		goto _st19;
		_ctr31:
			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			h2 = p; }
		
#line 221 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 226 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 231 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 25 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 245 "gen/ragel/submatch_03__uri_simple.c"

		goto _st19;
		_ctr40:
			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r1 = p; }
		
#line 252 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 257 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 262 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 267 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 25 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 281 "gen/ragel/submatch_03__uri_simple.c"

		goto _st19;
		_ctr57:
			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 288 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 293 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 298 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 25 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			
			OUT("scheme: ", s1, s2);
			if (u2) OUT("user: ", u1, u2);
			if (h1) OUT("host: ", h1, h2);
			if (r2 - r1 > 1) OUT("port: ", r1, r2);
			OUT("path: ", p1, p2);
			if (q1) OUT("query: ", q1, q2);
			if (f1) OUT("fragment: ", f1, f2);
			outc(out, '\n');
		}
		
#line 312 "gen/ragel/submatch_03__uri_simple.c"

		goto _st19;
		_st19:
		p+= 1;
		st_case_19:
		if ( p == pe )
			goto _out19;
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
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr67:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			
			s1 = p;
			s2 = u1 = h1 = r1 = p1 = q1 = f1 =
			u2 = h2 = r2 = p2 = q2 = f2 = NULL;
		}
		
#line 350 "gen/ragel/submatch_03__uri_simple.c"

		goto _st1;
		_st1:
		p+= 1;
		st_case_1:
		if ( p == pe )
			goto _out1;
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
		goto _st0;
		_ctr2:
			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			s2 = p; }
		
#line 386 "gen/ragel/submatch_03__uri_simple.c"

		goto _st2;
		_st2:
		p+= 1;
		st_case_2:
		if ( p == pe )
			goto _out2;
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
		goto _st0;
		_ctr5:
			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 436 "gen/ragel/submatch_03__uri_simple.c"

		goto _st3;
		_ctr34:
			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			h2 = p; }
		
#line 443 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 448 "gen/ragel/submatch_03__uri_simple.c"

		goto _st3;
		_ctr43:
			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r1 = p; }
		
#line 455 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 460 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 465 "gen/ragel/submatch_03__uri_simple.c"

		goto _st3;
		_ctr58:
			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 472 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 477 "gen/ragel/submatch_03__uri_simple.c"

		goto _st3;
		_st3:
		p+= 1;
		st_case_3:
		if ( p == pe )
			goto _out3;
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
		goto _st0;
		_ctr6:
			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 524 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 529 "gen/ragel/submatch_03__uri_simple.c"

		goto _st4;
		_ctr11:
			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 536 "gen/ragel/submatch_03__uri_simple.c"

		goto _st4;
		_ctr21:
			{
#line 20 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			q1 = p; }
		
#line 543 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 20 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			q2 = p; }
		
#line 548 "gen/ragel/submatch_03__uri_simple.c"

		goto _st4;
		_ctr24:
			{
#line 20 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			q2 = p; }
		
#line 555 "gen/ragel/submatch_03__uri_simple.c"

		goto _st4;
		_ctr33:
			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			h2 = p; }
		
#line 562 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 567 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 572 "gen/ragel/submatch_03__uri_simple.c"

		goto _st4;
		_ctr42:
			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r1 = p; }
		
#line 579 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 584 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 589 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 594 "gen/ragel/submatch_03__uri_simple.c"

		goto _st4;
		_ctr59:
			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 601 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 606 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 611 "gen/ragel/submatch_03__uri_simple.c"

		goto _st4;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
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
		goto _st0;
		_ctr15:
			{
#line 21 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			f1 = p; }
		
#line 652 "gen/ragel/submatch_03__uri_simple.c"

		goto _st5;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
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
		goto _st0;
		_ctr8:
			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 693 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 698 "gen/ragel/submatch_03__uri_simple.c"

		goto _st6;
		_ctr12:
			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 705 "gen/ragel/submatch_03__uri_simple.c"

		goto _st6;
		_ctr36:
			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			h2 = p; }
		
#line 712 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 717 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 722 "gen/ragel/submatch_03__uri_simple.c"

		goto _st6;
		_ctr45:
			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r1 = p; }
		
#line 729 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 734 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 739 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 744 "gen/ragel/submatch_03__uri_simple.c"

		goto _st6;
		_ctr61:
			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 751 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 756 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p2 = p; }
		
#line 761 "gen/ragel/submatch_03__uri_simple.c"

		goto _st6;
		_st6:
		p+= 1;
		st_case_6:
		if ( p == pe )
			goto _out6;
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
		goto _st0;
		_ctr20:
			{
#line 20 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			q1 = p; }
		
#line 805 "gen/ragel/submatch_03__uri_simple.c"

		goto _st7;
		_st7:
		p+= 1;
		st_case_7:
		if ( p == pe )
			goto _out7;
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
		goto _st0;
		_ctr7:
			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 849 "gen/ragel/submatch_03__uri_simple.c"

		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
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
		goto _st0;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
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
		goto _st0;
		_ctr27:
			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			u1 = p; }
		
#line 951 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			h1 = p; }
		
#line 956 "gen/ragel/submatch_03__uri_simple.c"

		goto _st10;
		_ctr32:
			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			h2 = p; }
		
#line 963 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 968 "gen/ragel/submatch_03__uri_simple.c"

		goto _st10;
		_st10:
		p+= 1;
		st_case_10:
		if ( p == pe )
			goto _out10;
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
		goto _st0;
		_ctr35:
			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			h2 = p; }
		
#line 1027 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 1032 "gen/ragel/submatch_03__uri_simple.c"

		goto _st11;
		_st11:
		p+= 1;
		st_case_11:
		if ( p == pe )
			goto _out11;
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
		goto _st0;
		_ctr28:
			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			u1 = p; }
		
#line 1093 "gen/ragel/submatch_03__uri_simple.c"

		goto _st12;
		_ctr41:
			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r1 = p; }
		
#line 1100 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 1105 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 1110 "gen/ragel/submatch_03__uri_simple.c"

		goto _st12;
		_ctr63:
			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 1117 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 1122 "gen/ragel/submatch_03__uri_simple.c"

		goto _st12;
		_st12:
		p+= 1;
		st_case_12:
		if ( p == pe )
			goto _out12;
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
		goto _st0;
		_ctr37:
			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			u2 = p; }
		
#line 1175 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			h2 = p; }
		
#line 1180 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 1185 "gen/ragel/submatch_03__uri_simple.c"

		goto _st13;
		_ctr46:
			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			u2 = p; }
		
#line 1192 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r1 = p; }
		
#line 1197 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 1202 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 1207 "gen/ragel/submatch_03__uri_simple.c"

		goto _st13;
		_ctr48:
			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			u2 = p; }
		
#line 1214 "gen/ragel/submatch_03__uri_simple.c"

		goto _st13;
		_ctr65:
			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			u2 = p; }
		
#line 1221 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 1226 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 1231 "gen/ragel/submatch_03__uri_simple.c"

		goto _st13;
		_st13:
		p+= 1;
		st_case_13:
		if ( p == pe )
			goto _out13;
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
		goto _st0;
		_ctr50:
			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			h1 = p; }
		
#line 1290 "gen/ragel/submatch_03__uri_simple.c"

		goto _st14;
		_ctr52:
			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			h2 = p; }
		
#line 1297 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 1302 "gen/ragel/submatch_03__uri_simple.c"

		goto _st14;
		_st14:
		p+= 1;
		st_case_14:
		if ( p == pe )
			goto _out14;
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
		goto _st0;
		_ctr53:
			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			h2 = p; }
		
#line 1361 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 1366 "gen/ragel/submatch_03__uri_simple.c"

		goto _st15;
		_st15:
		p+= 1;
		st_case_15:
		if ( p == pe )
			goto _out15;
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
		goto _st0;
		_ctr55:
			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r1 = p; }
		
#line 1421 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 1426 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 1431 "gen/ragel/submatch_03__uri_simple.c"

		goto _st16;
		_ctr60:
			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 1438 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 1443 "gen/ragel/submatch_03__uri_simple.c"

		goto _st16;
		_st16:
		p+= 1;
		st_case_16:
		if ( p == pe )
			goto _out16;
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
		goto _st0;
		_ctr29:
			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			h1 = p; }
		
#line 1498 "gen/ragel/submatch_03__uri_simple.c"

		goto _st17;
		_st17:
		p+= 1;
		st_case_17:
		if ( p == pe )
			goto _out17;
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
		goto _st0;
		_ctr44:
			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r1 = p; }
		
#line 1543 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 1548 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 1553 "gen/ragel/submatch_03__uri_simple.c"

		goto _st18;
		_ctr64:
			{
#line 18 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			r2 = p; }
		
#line 1560 "gen/ragel/submatch_03__uri_simple.c"

			{
#line 19 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"
			p1 = p; }
		
#line 1565 "gen/ragel/submatch_03__uri_simple.c"

		goto _st18;
		_st18:
		p+= 1;
		st_case_18:
		if ( p == pe )
			goto _out18;
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
		goto _st0;
		_out19: cs = 19; goto _out; 
		_out0: cs = 0; goto _out; 
		_out1: cs = 1; goto _out; 
		_out2: cs = 2; goto _out; 
		_out3: cs = 3; goto _out; 
		_out4: cs = 4; goto _out; 
		_out5: cs = 5; goto _out; 
		_out6: cs = 6; goto _out; 
		_out7: cs = 7; goto _out; 
		_out8: cs = 8; goto _out; 
		_out9: cs = 9; goto _out; 
		_out10: cs = 10; goto _out; 
		_out11: cs = 11; goto _out; 
		_out12: cs = 12; goto _out; 
		_out13: cs = 13; goto _out; 
		_out14: cs = 14; goto _out; 
		_out15: cs = 15; goto _out; 
		_out16: cs = 16; goto _out; 
		_out17: cs = 17; goto _out; 
		_out18: cs = 18; goto _out; 
		_out: {}
	}
	
#line 51 "../../../benchmarks/c/src/ragel/submatch_03__uri_simple.rl"

	
	in->p = p;
	in->pe = pe;
}
