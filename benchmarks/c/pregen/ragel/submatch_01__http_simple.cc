#line 1 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
#include "ragel/base.h"

namespace ragel_submatch_01__http_simple {
	
	const char *delim = "\n\n";
	
	
#line 76 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"

	

#line 11 "gen/ragel/submatch_01__http_simple.cc"
static const int uri_start = 47;
	static const int uri_first_final = 47;
	static const int uri_error = 0;
	
	static const int uri_en_main = 47;
	
	
#line 78 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *pe = in->pe;
		const char *h1, *h2,
		*s1, *v1, *v3, *m1, *rp1, *rt1,
		*s2, *v2, *v4, *m2, *rp2, *rt2;
		int cs;
		

#line 28 "gen/ragel/submatch_01__http_simple.cc"
	{
			cs = (int)uri_start;
		}
		
#line 88 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"


#line 33 "gen/ragel/submatch_01__http_simple.cc"
{
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
			_ctr24:
				{
#line 55 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				
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
			
#line 148 "gen/ragel/submatch_01__http_simple.cc"

				{
#line 73 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				OUTC('\n'); }
			
#line 153 "gen/ragel/submatch_01__http_simple.cc"

			goto _st47;
			_ctr39:
				{
#line 73 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				OUTC('\n'); }
			
#line 160 "gen/ragel/submatch_01__http_simple.cc"

			goto _st47;
			_st47:
			p+= 1;
			st_case_47:
			if ( p == pe )
				goto _out47;
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
			goto _st0;
			_st0:
			st_case_0:
			goto _out0;
			_ctr72:
				{
#line 51 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				
				h1 = h2 =
				s1 = v1 = v3 = m1 = rp1 = rt1 =
				s2 = v2 = v4 = m2 = rp2 = rt2 = NULL;
			}
			
#line 217 "gen/ragel/submatch_01__http_simple.cc"

				{
#line 39 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				m1 = p; }
			
#line 222 "gen/ragel/submatch_01__http_simple.cc"

			goto _st1;
			_st1:
			p+= 1;
			st_case_1:
			if ( p == pe )
				goto _out1;
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
			goto _st0;
			_ctr2:
				{
#line 39 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				m2 = p; }
			
#line 272 "gen/ragel/submatch_01__http_simple.cc"

			goto _st2;
			_st2:
			p+= 1;
			st_case_2:
			if ( p == pe )
				goto _out2;
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
			goto _st0;
			_ctr4:
				{
#line 40 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				rt1 = p; }
			
#line 330 "gen/ragel/submatch_01__http_simple.cc"

			goto _st3;
			_st3:
			p+= 1;
			st_case_3:
			if ( p == pe )
				goto _out3;
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
			goto _st0;
			_ctr9:
				{
#line 40 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				rt2 = p; }
			
#line 384 "gen/ragel/submatch_01__http_simple.cc"

			goto _st4;
			_st4:
			p+= 1;
			st_case_4:
			if ( p == pe )
				goto _out4;
			if ( ( (*( p))) == 72 ) {
				goto _ctr13;
			}
			goto _st0;
			_ctr13:
				{
#line 41 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				v3 = p; }
			
#line 400 "gen/ragel/submatch_01__http_simple.cc"

			goto _st5;
			_st5:
			p+= 1;
			st_case_5:
			if ( p == pe )
				goto _out5;
			if ( ( (*( p))) == 84 ) {
				goto _st6;
			}
			goto _st0;
			_st6:
			p+= 1;
			st_case_6:
			if ( p == pe )
				goto _out6;
			if ( ( (*( p))) == 84 ) {
				goto _st7;
			}
			goto _st0;
			_st7:
			p+= 1;
			st_case_7:
			if ( p == pe )
				goto _out7;
			if ( ( (*( p))) == 80 ) {
				goto _st8;
			}
			goto _st0;
			_st8:
			p+= 1;
			st_case_8:
			if ( p == pe )
				goto _out8;
			if ( ( (*( p))) == 47 ) {
				goto _st9;
			}
			goto _st0;
			_st9:
			p+= 1;
			st_case_9:
			if ( p == pe )
				goto _out9;
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st10;
			}
			goto _st0;
			_st10:
			p+= 1;
			st_case_10:
			if ( p == pe )
				goto _out10;
			if ( ( (*( p))) == 46 ) {
				goto _st11;
			}
			goto _st0;
			_st11:
			p+= 1;
			st_case_11:
			if ( p == pe )
				goto _out11;
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st12;
			}
			goto _st0;
			_st12:
			p+= 1;
			st_case_12:
			if ( p == pe )
				goto _out12;
			if ( ( (*( p))) == 10 ) {
				goto _ctr22;
			}
			goto _st0;
			_ctr22:
				{
#line 41 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				v4 = p; }
			
#line 479 "gen/ragel/submatch_01__http_simple.cc"

			goto _st13;
			_ctr68:
				{
#line 49 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				rp1 = p; }
			
#line 486 "gen/ragel/submatch_01__http_simple.cc"

				{
#line 49 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				rp2 = p; }
			
#line 491 "gen/ragel/submatch_01__http_simple.cc"

			goto _st13;
			_ctr70:
				{
#line 49 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				rp2 = p; }
			
#line 498 "gen/ragel/submatch_01__http_simple.cc"

			goto _st13;
			_st13:
			p+= 1;
			st_case_13:
			if ( p == pe )
				goto _out13;
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
			goto _st0;
			_ctr25:
				{
#line 55 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				
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
			
#line 559 "gen/ragel/submatch_01__http_simple.cc"

				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				h1 = p; }
			
#line 564 "gen/ragel/submatch_01__http_simple.cc"

			goto _st14;
			_ctr40:
				{
#line 27 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				h1 = p; }
			
#line 571 "gen/ragel/submatch_01__http_simple.cc"

			goto _st14;
			_st14:
			p+= 1;
			st_case_14:
			if ( p == pe )
				goto _out14;
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
			goto _st0;
			_ctr29:
				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				h2 = p; }
			
#line 621 "gen/ragel/submatch_01__http_simple.cc"

			goto _st15;
			_st15:
			p+= 1;
			st_case_15:
			if ( p == pe )
				goto _out15;
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
			goto _st16;
			_ctr32:
				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				h2 = p; }
			
#line 651 "gen/ragel/submatch_01__http_simple.cc"

			goto _st16;
			_st16:
			p+= 1;
			st_case_16:
			if ( p == pe )
				goto _out16;
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
			goto _st16;
			_ctr31:
				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				h2 = p; }
			
#line 681 "gen/ragel/submatch_01__http_simple.cc"

			goto _st17;
			_st17:
			p+= 1;
			st_case_17:
			if ( p == pe )
				goto _out17;
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
			goto _st18;
			_st18:
			p+= 1;
			st_case_18:
			if ( p == pe )
				goto _out18;
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
			goto _st16;
			_ctr36:
				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				h2 = p; }
			
#line 734 "gen/ragel/submatch_01__http_simple.cc"

			goto _st19;
			_st19:
			p+= 1;
			st_case_19:
			if ( p == pe )
				goto _out19;
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
			goto _st0;
			_ctr35:
				{
#line 68 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				
				if (h2) OUT("header: ", h1, h2);
				h1 = h2 = NULL;
			}
			
#line 761 "gen/ragel/submatch_01__http_simple.cc"

			goto _st20;
			_st20:
			p+= 1;
			st_case_20:
			if ( p == pe )
				goto _out20;
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
			goto _st0;
			_ctr30:
				{
#line 29 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				h2 = p; }
			
#line 811 "gen/ragel/submatch_01__http_simple.cc"

				{
#line 68 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				
				if (h2) OUT("header: ", h1, h2);
				h1 = h2 = NULL;
			}
			
#line 819 "gen/ragel/submatch_01__http_simple.cc"

			goto _st21;
			_st21:
			p+= 1;
			st_case_21:
			if ( p == pe )
				goto _out21;
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
			goto _st0;
			_st22:
			p+= 1;
			st_case_22:
			if ( p == pe )
				goto _out22;
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
			goto _st0;
			_ctr7:
				{
#line 40 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				rt1 = p; }
			
#line 913 "gen/ragel/submatch_01__http_simple.cc"

			goto _st23;
			_st23:
			p+= 1;
			st_case_23:
			if ( p == pe )
				goto _out23;
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
			goto _st0;
			_ctr5:
				{
#line 40 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				rt1 = p; }
			
#line 961 "gen/ragel/submatch_01__http_simple.cc"

			goto _st24;
			_st24:
			p+= 1;
			st_case_24:
			if ( p == pe )
				goto _out24;
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
			goto _st0;
			_st25:
			p+= 1;
			st_case_25:
			if ( p == pe )
				goto _out25;
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
			goto _st0;
			_st26:
			p+= 1;
			st_case_26:
			if ( p == pe )
				goto _out26;
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
			goto _st0;
			_ctr6:
				{
#line 40 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				rt1 = p; }
			
#line 1126 "gen/ragel/submatch_01__http_simple.cc"

			goto _st27;
			_st27:
			p+= 1;
			st_case_27:
			if ( p == pe )
				goto _out27;
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
			goto _st0;
			_st28:
			p+= 1;
			st_case_28:
			if ( p == pe )
				goto _out28;
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
			goto _st0;
			_st29:
			p+= 1;
			st_case_29:
			if ( p == pe )
				goto _out29;
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
			goto _st0;
			_st30:
			p+= 1;
			st_case_30:
			if ( p == pe )
				goto _out30;
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
			goto _st0;
			_st31:
			p+= 1;
			st_case_31:
			if ( p == pe )
				goto _out31;
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
			goto _st0;
			_st32:
			p+= 1;
			st_case_32:
			if ( p == pe )
				goto _out32;
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
			goto _st0;
			_ctr73:
				{
#line 51 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				
				h1 = h2 =
				s1 = v1 = v3 = m1 = rp1 = rt1 =
				s2 = v2 = v4 = m2 = rp2 = rt2 = NULL;
			}
			
#line 1395 "gen/ragel/submatch_01__http_simple.cc"

				{
#line 39 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				m1 = p; }
			
#line 1400 "gen/ragel/submatch_01__http_simple.cc"

				{
#line 47 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				v1 = p; }
			
#line 1405 "gen/ragel/submatch_01__http_simple.cc"

			goto _st33;
			_st33:
			p+= 1;
			st_case_33:
			if ( p == pe )
				goto _out33;
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
			goto _st0;
			_st34:
			p+= 1;
			st_case_34:
			if ( p == pe )
				goto _out34;
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
			goto _st0;
			_st35:
			p+= 1;
			st_case_35:
			if ( p == pe )
				goto _out35;
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
			goto _st0;
			_st36:
			p+= 1;
			st_case_36:
			if ( p == pe )
				goto _out36;
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
			goto _st0;
			_st37:
			p+= 1;
			st_case_37:
			if ( p == pe )
				goto _out37;
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st38;
			}
			goto _st0;
			_st38:
			p+= 1;
			st_case_38:
			if ( p == pe )
				goto _out38;
			if ( ( (*( p))) == 46 ) {
				goto _st39;
			}
			goto _st0;
			_st39:
			p+= 1;
			st_case_39:
			if ( p == pe )
				goto _out39;
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st40;
			}
			goto _st0;
			_st40:
			p+= 1;
			st_case_40:
			if ( p == pe )
				goto _out40;
			if ( ( (*( p))) == 32 ) {
				goto _ctr59;
			}
			goto _st0;
			_ctr59:
				{
#line 47 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				v2 = p; }
			
#line 1628 "gen/ragel/submatch_01__http_simple.cc"

			goto _st41;
			_st41:
			p+= 1;
			st_case_41:
			if ( p == pe )
				goto _out41;
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _ctr61;
			}
			goto _st0;
			_ctr61:
				{
#line 48 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				s1 = p; }
			
#line 1644 "gen/ragel/submatch_01__http_simple.cc"

			goto _st42;
			_st42:
			p+= 1;
			st_case_42:
			if ( p == pe )
				goto _out42;
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st43;
			}
			goto _st0;
			_st43:
			p+= 1;
			st_case_43:
			if ( p == pe )
				goto _out43;
			if ( 48 <= ( (*( p))) && ( (*( p))) <= 57 ) {
				goto _st44;
			}
			goto _st0;
			_st44:
			p+= 1;
			st_case_44:
			if ( p == pe )
				goto _out44;
			if ( ( (*( p))) == 32 ) {
				goto _ctr65;
			}
			goto _st0;
			_ctr65:
				{
#line 48 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				s2 = p; }
			
#line 1678 "gen/ragel/submatch_01__http_simple.cc"

			goto _st45;
			_st45:
			p+= 1;
			st_case_45:
			if ( p == pe )
				goto _out45;
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
			goto _ctr67;
			_ctr67:
				{
#line 49 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"
				rp1 = p; }
			
#line 1706 "gen/ragel/submatch_01__http_simple.cc"

			goto _st46;
			_st46:
			p+= 1;
			st_case_46:
			if ( p == pe )
				goto _out46;
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
			goto _st46;
			_out47: cs = 47; goto _out; 
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
			_out19: cs = 19; goto _out; 
			_out20: cs = 20; goto _out; 
			_out21: cs = 21; goto _out; 
			_out22: cs = 22; goto _out; 
			_out23: cs = 23; goto _out; 
			_out24: cs = 24; goto _out; 
			_out25: cs = 25; goto _out; 
			_out26: cs = 26; goto _out; 
			_out27: cs = 27; goto _out; 
			_out28: cs = 28; goto _out; 
			_out29: cs = 29; goto _out; 
			_out30: cs = 30; goto _out; 
			_out31: cs = 31; goto _out; 
			_out32: cs = 32; goto _out; 
			_out33: cs = 33; goto _out; 
			_out34: cs = 34; goto _out; 
			_out35: cs = 35; goto _out; 
			_out36: cs = 36; goto _out; 
			_out37: cs = 37; goto _out; 
			_out38: cs = 38; goto _out; 
			_out39: cs = 39; goto _out; 
			_out40: cs = 40; goto _out; 
			_out41: cs = 41; goto _out; 
			_out42: cs = 42; goto _out; 
			_out43: cs = 43; goto _out; 
			_out44: cs = 44; goto _out; 
			_out45: cs = 45; goto _out; 
			_out46: cs = 46; goto _out; 
			_out: {}
		}
		
#line 89 "../../../benchmarks/c/src/ragel/submatch_01__http_simple.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH_AND_TEST()
	
} // namespace ragel_submatch_01__http_simple
