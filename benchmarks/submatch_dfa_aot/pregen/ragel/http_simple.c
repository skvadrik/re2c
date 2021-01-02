#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
#include "ragel/common.c"

const char *delim = "\n\n";


#line 74 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"



#line 12 "gen/ragel/http_simple.c"
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
	
	
#line 33 "gen/ragel/http_simple.c"
	{
		cs = (int)uri_start;
	}
	
#line 87 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
	
	
#line 41 "gen/ragel/http_simple.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 47:
			goto st_case_47;
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
			case 19:
			goto st_case_19;
			case 20:
			goto st_case_20;
			case 21:
			goto st_case_21;
			case 22:
			goto st_case_22;
			case 23:
			goto st_case_23;
			case 24:
			goto st_case_24;
			case 25:
			goto st_case_25;
			case 26:
			goto st_case_26;
			case 27:
			goto st_case_27;
			case 28:
			goto st_case_28;
			case 29:
			goto st_case_29;
			case 30:
			goto st_case_30;
			case 31:
			goto st_case_31;
			case 32:
			goto st_case_32;
			case 33:
			goto st_case_33;
			case 34:
			goto st_case_34;
			case 35:
			goto st_case_35;
			case 36:
			goto st_case_36;
			case 37:
			goto st_case_37;
			case 38:
			goto st_case_38;
			case 39:
			goto st_case_39;
			case 40:
			goto st_case_40;
			case 41:
			goto st_case_41;
			case 42:
			goto st_case_42;
			case 43:
			goto st_case_43;
			case 44:
			goto st_case_44;
			case 45:
			goto st_case_45;
			case 46:
			goto st_case_46;
		}
		goto st_out;
		_ctr24:
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
		
#line 160 "gen/ragel/http_simple.c"
		
		{
#line 71 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			outc(out, '\n'); }
		
#line 166 "gen/ragel/http_simple.c"
		
		goto _st47;
		_ctr39:
		{
#line 71 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			outc(out, '\n'); }
		
#line 174 "gen/ragel/http_simple.c"
		
		goto _st47;
		_st47:
		p+= 1;
		if ( p == pe )
			goto _test_eof47;
		st_case_47:
		switch( ( (*( p))) ) {
			case 33: {
				goto _ctr72;
			}
			case 72: {
				goto _ctr73;
			}
			case 124: {
				goto _ctr72;
			}
			case 126: {
				goto _ctr72;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto _ctr72;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto _ctr72;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto _ctr72;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _ctr72;
				}
			} else {
				goto _ctr72;
			}
		} else {
			goto _ctr72;
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr72:
		{
#line 49 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			
			h1 = h2 =
			s1 = v1 = v3 = m1 = rp1 = rt1 =
			s2 = v2 = v4 = m2 = rp2 = rt2 = NULL;
		}
		
#line 235 "gen/ragel/http_simple.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			m1 = p; }
		
#line 241 "gen/ragel/http_simple.c"
		
		goto _st1;
		_st1:
		p+= 1;
		if ( p == pe )
			goto _test_eof1;
		st_case_1:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr2;
			}
			case 33: {
				goto _st1;
			}
			case 124: {
				goto _st1;
			}
			case 126: {
				goto _st1;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto _st1;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto _st1;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto _st1;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st1;
				}
			} else {
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
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			m2 = p; }
		
#line 294 "gen/ragel/http_simple.c"
		
		goto _st2;
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
		switch( ( (*( p))) ) {
			case 33: {
				goto _ctr4;
			}
			case 43: {
				goto _ctr5;
			}
			case 47: {
				goto _ctr6;
			}
			case 61: {
				goto _ctr4;
			}
			case 91: {
				goto _ctr7;
			}
			case 93: {
				goto _ctr7;
			}
			case 95: {
				goto _ctr4;
			}
			case 126: {
				goto _ctr4;
			}
		}
		if ( ( (*( p))) < 58 ) {
			if ( ( (*( p))) > 44 ) {
				{
					goto _ctr5;
				}
			} else if ( ( (*( p))) >= 36 ) {
				goto _ctr4;
			}
		} else if ( ( (*( p))) > 59 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _ctr5;
				}
			} else if ( ( (*( p))) >= 65 ) {
				goto _ctr5;
			}
		} else {
			goto _ctr4;
		}
		{
			goto _st0;
		}
		_ctr4:
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			rt1 = p; }
		
#line 355 "gen/ragel/http_simple.c"
		
		goto _st3;
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr9;
			}
			case 33: {
				goto _st3;
			}
			case 61: {
				goto _st3;
			}
			case 64: {
				goto _st22;
			}
			case 91: {
				goto _st23;
			}
			case 93: {
				goto _st23;
			}
			case 95: {
				goto _st3;
			}
			case 126: {
				goto _st3;
			}
		}
		if ( ( (*( p))) < 48 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 46 ) {
				goto _st3;
			}
		} else if ( ( (*( p))) > 59 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st3;
				}
			} else if ( ( (*( p))) >= 65 ) {
				goto _st3;
			}
		} else {
			goto _st3;
		}
		{
			goto _st0;
		}
		_ctr9:
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			rt2 = p; }
		
#line 412 "gen/ragel/http_simple.c"
		
		goto _st4;
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		if ( ( (*( p))) == 72 ) {
			goto _ctr13;
		}
		{
			goto _st0;
		}
		_ctr13:
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			v3 = p; }
		
#line 431 "gen/ragel/http_simple.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		if ( ( (*( p))) == 84 ) {
			goto _st6;
		}
		{
			goto _st0;
		}
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		if ( ( (*( p))) == 84 ) {
			goto _st7;
		}
		{
			goto _st0;
		}
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		if ( ( (*( p))) == 80 ) {
			goto _st8;
		}
		{
			goto _st0;
		}
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		if ( ( (*( p))) == 47 ) {
			goto _st9;
		}
		{
			goto _st0;
		}
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st10;
		}
		{
			goto _st0;
		}
		_st10:
		p+= 1;
		if ( p == pe )
			goto _test_eof10;
		st_case_10:
		if ( ( (*( p))) == 46 ) {
			goto _st11;
		}
		{
			goto _st0;
		}
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st12;
		}
		{
			goto _st0;
		}
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
		if ( ( (*( p))) == 10 ) {
			goto _ctr22;
		}
		{
			goto _st0;
		}
		_ctr22:
		{
#line 39 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			v4 = p; }
		
#line 527 "gen/ragel/http_simple.c"
		
		goto _st13;
		_ctr68:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			rp1 = p; }
		
#line 535 "gen/ragel/http_simple.c"
		
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			rp2 = p; }
		
#line 541 "gen/ragel/http_simple.c"
		
		goto _st13;
		_ctr70:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			rp2 = p; }
		
#line 549 "gen/ragel/http_simple.c"
		
		goto _st13;
		_st13:
		p+= 1;
		if ( p == pe )
			goto _test_eof13;
		st_case_13:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr24;
			}
			case 33: {
				goto _ctr25;
			}
			case 124: {
				goto _ctr25;
			}
			case 126: {
				goto _ctr25;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto _ctr25;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto _ctr25;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto _ctr25;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _ctr25;
				}
			} else {
				goto _ctr25;
			}
		} else {
			goto _ctr25;
		}
		{
			goto _st0;
		}
		_ctr25:
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
		
#line 613 "gen/ragel/http_simple.c"
		
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			h1 = p; }
		
#line 619 "gen/ragel/http_simple.c"
		
		goto _st14;
		_ctr40:
		{
#line 25 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			h1 = p; }
		
#line 627 "gen/ragel/http_simple.c"
		
		goto _st14;
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
		switch( ( (*( p))) ) {
			case 33: {
				goto _st14;
			}
			case 58: {
				goto _st15;
			}
			case 124: {
				goto _st14;
			}
			case 126: {
				goto _st14;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto _st14;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto _st14;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto _st14;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st14;
				}
			} else {
				goto _st14;
			}
		} else {
			goto _st14;
		}
		{
			goto _st0;
		}
		_ctr29:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			h2 = p; }
		
#line 680 "gen/ragel/http_simple.c"
		
		goto _st15;
		_st15:
		p+= 1;
		if ( p == pe )
			goto _test_eof15;
		st_case_15:
		switch( ( (*( p))) ) {
			case 9: {
				goto _ctr29;
			}
			case 10: {
				goto _ctr30;
			}
			case 32: {
				goto _ctr29;
			}
			case 127: {
				goto _st0;
			}
		}
		if ( 0 <= ( (*( p))) && ( (*( p))) <= 31 ) {
			goto _st0;
		}
		{
			goto _st16;
		}
		_ctr32:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			h2 = p; }
		
#line 713 "gen/ragel/http_simple.c"
		
		goto _st16;
		_st16:
		p+= 1;
		if ( p == pe )
			goto _test_eof16;
		st_case_16:
		switch( ( (*( p))) ) {
			case 9: {
				goto _ctr31;
			}
			case 10: {
				goto _ctr30;
			}
			case 32: {
				goto _ctr32;
			}
			case 127: {
				goto _st0;
			}
		}
		if ( 0 <= ( (*( p))) && ( (*( p))) <= 31 ) {
			goto _st0;
		}
		{
			goto _st16;
		}
		_ctr31:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			h2 = p; }
		
#line 746 "gen/ragel/http_simple.c"
		
		goto _st17;
		_st17:
		p+= 1;
		if ( p == pe )
			goto _test_eof17;
		st_case_17:
		switch( ( (*( p))) ) {
			case 9: {
				goto _st17;
			}
			case 10: {
				goto _ctr35;
			}
			case 32: {
				goto _st16;
			}
			case 127: {
				goto _st0;
			}
		}
		if ( 0 <= ( (*( p))) && ( (*( p))) <= 31 ) {
			goto _st0;
		}
		{
			goto _st18;
		}
		_st18:
		p+= 1;
		if ( p == pe )
			goto _test_eof18;
		st_case_18:
		switch( ( (*( p))) ) {
			case 9: {
				goto _ctr36;
			}
			case 10: {
				goto _ctr30;
			}
			case 32: {
				goto _ctr32;
			}
			case 127: {
				goto _st0;
			}
		}
		if ( 0 <= ( (*( p))) && ( (*( p))) <= 31 ) {
			goto _st0;
		}
		{
			goto _st16;
		}
		_ctr36:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			h2 = p; }
		
#line 804 "gen/ragel/http_simple.c"
		
		goto _st19;
		_st19:
		p+= 1;
		if ( p == pe )
			goto _test_eof19;
		st_case_19:
		switch( ( (*( p))) ) {
			case 9: {
				goto _st19;
			}
			case 10: {
				goto _ctr35;
			}
			case 32: {
				goto _st19;
			}
		}
		{
			goto _st0;
		}
		_ctr35:
		{
#line 66 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			
			if (h2) OUT("header: ", h1, h2);
			h1 = h2 = NULL;
		}
		
#line 834 "gen/ragel/http_simple.c"
		
		goto _st20;
		_st20:
		p+= 1;
		if ( p == pe )
			goto _test_eof20;
		st_case_20:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
			}
			case 33: {
				goto _ctr40;
			}
			case 124: {
				goto _ctr40;
			}
			case 126: {
				goto _ctr40;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto _ctr40;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto _ctr40;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto _ctr40;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _ctr40;
				}
			} else {
				goto _ctr40;
			}
		} else {
			goto _ctr40;
		}
		{
			goto _st0;
		}
		_ctr30:
		{
#line 27 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			h2 = p; }
		
#line 887 "gen/ragel/http_simple.c"
		
		{
#line 66 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			
			if (h2) OUT("header: ", h1, h2);
			h1 = h2 = NULL;
		}
		
#line 896 "gen/ragel/http_simple.c"
		
		goto _st21;
		_st21:
		p+= 1;
		if ( p == pe )
			goto _test_eof21;
		st_case_21:
		switch( ( (*( p))) ) {
			case 9: {
				goto _st15;
			}
			case 10: {
				goto _ctr39;
			}
			case 32: {
				goto _st15;
			}
			case 33: {
				goto _ctr40;
			}
			case 124: {
				goto _ctr40;
			}
			case 126: {
				goto _ctr40;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto _ctr40;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto _ctr40;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto _ctr40;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _ctr40;
				}
			} else {
				goto _ctr40;
			}
		} else {
			goto _ctr40;
		}
		{
			goto _st0;
		}
		_st22:
		p+= 1;
		if ( p == pe )
			goto _test_eof22;
		st_case_22:
		switch( ( (*( p))) ) {
			case 33: {
				goto _st23;
			}
			case 61: {
				goto _st23;
			}
			case 93: {
				goto _st23;
			}
			case 95: {
				goto _st23;
			}
			case 126: {
				goto _st23;
			}
		}
		if ( ( (*( p))) < 48 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 46 ) {
				goto _st23;
			}
		} else if ( ( (*( p))) > 59 ) {
			if ( ( (*( p))) > 91 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st23;
				}
			} else if ( ( (*( p))) >= 65 ) {
				goto _st23;
			}
		} else {
			goto _st23;
		}
		{
			goto _st0;
		}
		_ctr7:
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			rt1 = p; }
		
#line 995 "gen/ragel/http_simple.c"
		
		goto _st23;
		_st23:
		p+= 1;
		if ( p == pe )
			goto _test_eof23;
		st_case_23:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr9;
			}
			case 33: {
				goto _st23;
			}
			case 61: {
				goto _st23;
			}
			case 93: {
				goto _st23;
			}
			case 95: {
				goto _st23;
			}
			case 126: {
				goto _st23;
			}
		}
		if ( ( (*( p))) < 48 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 46 ) {
				goto _st23;
			}
		} else if ( ( (*( p))) > 59 ) {
			if ( ( (*( p))) > 91 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st23;
				}
			} else if ( ( (*( p))) >= 65 ) {
				goto _st23;
			}
		} else {
			goto _st23;
		}
		{
			goto _st0;
		}
		_ctr5:
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			rt1 = p; }
		
#line 1046 "gen/ragel/http_simple.c"
		
		goto _st24;
		_st24:
		p+= 1;
		if ( p == pe )
			goto _test_eof24;
		st_case_24:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr9;
			}
			case 33: {
				goto _st3;
			}
			case 43: {
				goto _st24;
			}
			case 58: {
				goto _st25;
			}
			case 59: {
				goto _st3;
			}
			case 61: {
				goto _st3;
			}
			case 64: {
				goto _st22;
			}
			case 91: {
				goto _st23;
			}
			case 93: {
				goto _st23;
			}
			case 95: {
				goto _st3;
			}
			case 126: {
				goto _st3;
			}
		}
		if ( ( (*( p))) < 48 ) {
			if ( ( (*( p))) > 44 ) {
				if ( ( (*( p))) <= 46 ) {
					goto _st24;
				}
			} else if ( ( (*( p))) >= 36 ) {
				goto _st3;
			}
		} else if ( ( (*( p))) > 57 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st24;
				}
			} else if ( ( (*( p))) >= 65 ) {
				goto _st24;
			}
		} else {
			goto _st24;
		}
		{
			goto _st0;
		}
		_st25:
		p+= 1;
		if ( p == pe )
			goto _test_eof25;
		st_case_25:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr9;
			}
			case 33: {
				goto _st26;
			}
			case 47: {
				goto _st29;
			}
			case 61: {
				goto _st26;
			}
			case 63: {
				goto _st27;
			}
			case 64: {
				goto _st28;
			}
			case 91: {
				goto _st23;
			}
			case 93: {
				goto _st23;
			}
			case 95: {
				goto _st26;
			}
			case 126: {
				goto _st26;
			}
		}
		if ( ( (*( p))) < 65 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _st26;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st26;
			}
		} else {
			goto _st26;
		}
		{
			goto _st0;
		}
		_st26:
		p+= 1;
		if ( p == pe )
			goto _test_eof26;
		st_case_26:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr9;
			}
			case 33: {
				goto _st26;
			}
			case 47: {
				goto _st27;
			}
			case 61: {
				goto _st26;
			}
			case 63: {
				goto _st27;
			}
			case 64: {
				goto _st28;
			}
			case 91: {
				goto _st23;
			}
			case 93: {
				goto _st23;
			}
			case 95: {
				goto _st26;
			}
			case 126: {
				goto _st26;
			}
		}
		if ( ( (*( p))) < 65 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _st26;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st26;
			}
		} else {
			goto _st26;
		}
		{
			goto _st0;
		}
		_ctr6:
		{
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			rt1 = p; }
		
#line 1218 "gen/ragel/http_simple.c"
		
		goto _st27;
		_st27:
		p+= 1;
		if ( p == pe )
			goto _test_eof27;
		st_case_27:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr9;
			}
			case 33: {
				goto _st27;
			}
			case 61: {
				goto _st27;
			}
			case 95: {
				goto _st27;
			}
			case 126: {
				goto _st27;
			}
		}
		if ( ( (*( p))) < 63 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _st27;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st27;
			}
		} else {
			goto _st27;
		}
		{
			goto _st0;
		}
		_st28:
		p+= 1;
		if ( p == pe )
			goto _test_eof28;
		st_case_28:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr9;
			}
			case 33: {
				goto _st28;
			}
			case 47: {
				goto _st27;
			}
			case 61: {
				goto _st28;
			}
			case 91: {
				goto _st23;
			}
			case 93: {
				goto _st23;
			}
			case 95: {
				goto _st28;
			}
			case 126: {
				goto _st28;
			}
		}
		if ( ( (*( p))) < 63 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _st28;
			}
		} else if ( ( (*( p))) > 64 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st28;
				}
			} else {
				goto _st28;
			}
		} else {
			goto _st27;
		}
		{
			goto _st0;
		}
		_st29:
		p+= 1;
		if ( p == pe )
			goto _test_eof29;
		st_case_29:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr9;
			}
			case 33: {
				goto _st27;
			}
			case 47: {
				goto _st30;
			}
			case 61: {
				goto _st27;
			}
			case 95: {
				goto _st27;
			}
			case 126: {
				goto _st27;
			}
		}
		if ( ( (*( p))) < 63 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _st27;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st27;
			}
		} else {
			goto _st27;
		}
		{
			goto _st0;
		}
		_st30:
		p+= 1;
		if ( p == pe )
			goto _test_eof30;
		st_case_30:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr9;
			}
			case 33: {
				goto _st31;
			}
			case 47: {
				goto _st27;
			}
			case 61: {
				goto _st31;
			}
			case 91: {
				goto _st32;
			}
			case 93: {
				goto _st32;
			}
			case 95: {
				goto _st31;
			}
			case 126: {
				goto _st31;
			}
		}
		if ( ( (*( p))) < 63 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _st31;
			}
		} else if ( ( (*( p))) > 64 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st31;
				}
			} else {
				goto _st31;
			}
		} else {
			goto _st27;
		}
		{
			goto _st0;
		}
		_st31:
		p+= 1;
		if ( p == pe )
			goto _test_eof31;
		st_case_31:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr9;
			}
			case 33: {
				goto _st31;
			}
			case 47: {
				goto _st27;
			}
			case 61: {
				goto _st31;
			}
			case 63: {
				goto _st27;
			}
			case 64: {
				goto _st32;
			}
			case 91: {
				goto _st32;
			}
			case 93: {
				goto _st32;
			}
			case 95: {
				goto _st31;
			}
			case 126: {
				goto _st31;
			}
		}
		if ( ( (*( p))) < 65 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _st31;
			}
		} else if ( ( (*( p))) > 90 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st31;
			}
		} else {
			goto _st31;
		}
		{
			goto _st0;
		}
		_st32:
		p+= 1;
		if ( p == pe )
			goto _test_eof32;
		st_case_32:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr9;
			}
			case 33: {
				goto _st32;
			}
			case 47: {
				goto _st27;
			}
			case 61: {
				goto _st32;
			}
			case 93: {
				goto _st32;
			}
			case 95: {
				goto _st32;
			}
			case 126: {
				goto _st32;
			}
		}
		if ( ( (*( p))) < 63 ) {
			if ( 36 <= ( (*( p))) && ( (*( p))) <= 59 ) {
				goto _st32;
			}
		} else if ( ( (*( p))) > 64 ) {
			if ( ( (*( p))) > 91 ) {
				if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st32;
				}
			} else {
				goto _st32;
			}
		} else {
			goto _st27;
		}
		{
			goto _st0;
		}
		_ctr73:
		{
#line 49 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			
			h1 = h2 =
			s1 = v1 = v3 = m1 = rp1 = rt1 =
			s2 = v2 = v4 = m2 = rp2 = rt2 = NULL;
		}
		
#line 1500 "gen/ragel/http_simple.c"
		
		{
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			m1 = p; }
		
#line 1506 "gen/ragel/http_simple.c"
		
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			v1 = p; }
		
#line 1512 "gen/ragel/http_simple.c"
		
		goto _st33;
		_st33:
		p+= 1;
		if ( p == pe )
			goto _test_eof33;
		st_case_33:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr2;
			}
			case 33: {
				goto _st1;
			}
			case 84: {
				goto _st34;
			}
			case 124: {
				goto _st1;
			}
			case 126: {
				goto _st1;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto _st1;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto _st1;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto _st1;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st1;
				}
			} else {
				goto _st1;
			}
		} else {
			goto _st1;
		}
		{
			goto _st0;
		}
		_st34:
		p+= 1;
		if ( p == pe )
			goto _test_eof34;
		st_case_34:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr2;
			}
			case 33: {
				goto _st1;
			}
			case 84: {
				goto _st35;
			}
			case 124: {
				goto _st1;
			}
			case 126: {
				goto _st1;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto _st1;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto _st1;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto _st1;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st1;
				}
			} else {
				goto _st1;
			}
		} else {
			goto _st1;
		}
		{
			goto _st0;
		}
		_st35:
		p+= 1;
		if ( p == pe )
			goto _test_eof35;
		st_case_35:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr2;
			}
			case 33: {
				goto _st1;
			}
			case 80: {
				goto _st36;
			}
			case 124: {
				goto _st1;
			}
			case 126: {
				goto _st1;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto _st1;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto _st1;
			}
		} else if ( ( (*( p))) > 46 ) {
			if ( ( (*( p))) < 65 ) {
				if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
					goto _st1;
				}
			} else if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
					goto _st1;
				}
			} else {
				goto _st1;
			}
		} else {
			goto _st1;
		}
		{
			goto _st0;
		}
		_st36:
		p+= 1;
		if ( p == pe )
			goto _test_eof36;
		st_case_36:
		switch( ( (*( p))) ) {
			case 32: {
				goto _ctr2;
			}
			case 33: {
				goto _st1;
			}
			case 47: {
				goto _st37;
			}
			case 124: {
				goto _st1;
			}
			case 126: {
				goto _st1;
			}
		}
		if ( ( (*( p))) < 45 ) {
			if ( ( (*( p))) > 39 ) {
				if ( 42 <= ( (*( p))) && ( (*( p))) <= 43 ) {
					goto _st1;
				}
			} else if ( ( (*( p))) >= 35 ) {
				goto _st1;
			}
		} else if ( ( (*( p))) > 57 ) {
			if ( ( (*( p))) > 90 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 122 ) {
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
		_st37:
		p+= 1;
		if ( p == pe )
			goto _test_eof37;
		st_case_37:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st38;
		}
		{
			goto _st0;
		}
		_st38:
		p+= 1;
		if ( p == pe )
			goto _test_eof38;
		st_case_38:
		if ( ( (*( p))) == 46 ) {
			goto _st39;
		}
		{
			goto _st0;
		}
		_st39:
		p+= 1;
		if ( p == pe )
			goto _test_eof39;
		st_case_39:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st40;
		}
		{
			goto _st0;
		}
		_st40:
		p+= 1;
		if ( p == pe )
			goto _test_eof40;
		st_case_40:
		if ( ( (*( p))) == 32 ) {
			goto _ctr59;
		}
		{
			goto _st0;
		}
		_ctr59:
		{
#line 45 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			v2 = p; }
		
#line 1752 "gen/ragel/http_simple.c"
		
		goto _st41;
		_st41:
		p+= 1;
		if ( p == pe )
			goto _test_eof41;
		st_case_41:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _ctr61;
		}
		{
			goto _st0;
		}
		_ctr61:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			s1 = p; }
		
#line 1771 "gen/ragel/http_simple.c"
		
		goto _st42;
		_st42:
		p+= 1;
		if ( p == pe )
			goto _test_eof42;
		st_case_42:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st43;
		}
		{
			goto _st0;
		}
		_st43:
		p+= 1;
		if ( p == pe )
			goto _test_eof43;
		st_case_43:
		if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
			goto _st44;
		}
		{
			goto _st0;
		}
		_st44:
		p+= 1;
		if ( p == pe )
			goto _test_eof44;
		st_case_44:
		if ( ( (*( p))) == 32 ) {
			goto _ctr65;
		}
		{
			goto _st0;
		}
		_ctr65:
		{
#line 46 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			s2 = p; }
		
#line 1812 "gen/ragel/http_simple.c"
		
		goto _st45;
		_st45:
		p+= 1;
		if ( p == pe )
			goto _test_eof45;
		st_case_45:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr68;
			}
			case 127: {
				goto _st0;
			}
		}
		if ( ( (*( p))) > 8 ) {
			if ( 11 <= ( (*( p))) && ( (*( p))) <= 31 ) {
				goto _st0;
			}
		} else if ( ( (*( p))) >= 0 ) {
			goto _st0;
		}
		{
			goto _ctr67;
		}
		_ctr67:
		{
#line 47 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
			rp1 = p; }
		
#line 1843 "gen/ragel/http_simple.c"
		
		goto _st46;
		_st46:
		p+= 1;
		if ( p == pe )
			goto _test_eof46;
		st_case_46:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr70;
			}
			case 127: {
				goto _st0;
			}
		}
		if ( ( (*( p))) > 8 ) {
			if ( 11 <= ( (*( p))) && ( (*( p))) <= 31 ) {
				goto _st0;
			}
		} else if ( ( (*( p))) >= 0 ) {
			goto _st0;
		}
		{
			goto _st46;
		}
		st_out:
		_test_eof47: cs = 47; goto _test_eof; 
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
		_test_eof19: cs = 19; goto _test_eof; 
		_test_eof20: cs = 20; goto _test_eof; 
		_test_eof21: cs = 21; goto _test_eof; 
		_test_eof22: cs = 22; goto _test_eof; 
		_test_eof23: cs = 23; goto _test_eof; 
		_test_eof24: cs = 24; goto _test_eof; 
		_test_eof25: cs = 25; goto _test_eof; 
		_test_eof26: cs = 26; goto _test_eof; 
		_test_eof27: cs = 27; goto _test_eof; 
		_test_eof28: cs = 28; goto _test_eof; 
		_test_eof29: cs = 29; goto _test_eof; 
		_test_eof30: cs = 30; goto _test_eof; 
		_test_eof31: cs = 31; goto _test_eof; 
		_test_eof32: cs = 32; goto _test_eof; 
		_test_eof33: cs = 33; goto _test_eof; 
		_test_eof34: cs = 34; goto _test_eof; 
		_test_eof35: cs = 35; goto _test_eof; 
		_test_eof36: cs = 36; goto _test_eof; 
		_test_eof37: cs = 37; goto _test_eof; 
		_test_eof38: cs = 38; goto _test_eof; 
		_test_eof39: cs = 39; goto _test_eof; 
		_test_eof40: cs = 40; goto _test_eof; 
		_test_eof41: cs = 41; goto _test_eof; 
		_test_eof42: cs = 42; goto _test_eof; 
		_test_eof43: cs = 43; goto _test_eof; 
		_test_eof44: cs = 44; goto _test_eof; 
		_test_eof45: cs = 45; goto _test_eof; 
		_test_eof46: cs = 46; goto _test_eof; 
		
		_test_eof: {}
		if ( cs >= 47 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 88 "../../../benchmarks/submatch_dfa_aot/src/ragel/http_simple.rl"
	
	
	in->p = p;
	in->pe = pe;
}
