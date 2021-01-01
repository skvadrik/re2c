#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"



#line 12 "gen/ragel/cat2_4-G2.c"
static const int abcd_start = 16;
static const int abcd_first_final = 16;
static const int abcd_error = 0;

static const int abcd_en_main = 16;


#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1,
	*b0, *b1;
	int cs;
	
	
#line 33 "gen/ragel/cat2_4-G2.c"
	{
		cs = (int)abcd_start;
	}
	
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
	
	
#line 41 "gen/ragel/cat2_4-G2.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 16:
			goto st_case_16;
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
		}
		goto st_out;
		_ctr17:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 90 "gen/ragel/cat2_4-G2.c"
		
		goto _st16;
		_st16:
		p+= 1;
		if ( p == pe )
			goto _test_eof16;
		st_case_16:
		if ( ( (*( p))) == 97 ) {
			goto _ctr29;
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr29:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			a0 = p; }
		
#line 113 "gen/ragel/cat2_4-G2.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b0 = p; }
		
#line 119 "gen/ragel/cat2_4-G2.c"
		
		goto _st1;
		_st1:
		p+= 1;
		if ( p == pe )
			goto _test_eof1;
		st_case_1:
		if ( ( (*( p))) == 97 ) {
			goto _ctr2;
		}
		{
			goto _st0;
		}
		_ctr2:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b0 = p; }
		
#line 138 "gen/ragel/cat2_4-G2.c"
		
		goto _st2;
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
		if ( ( (*( p))) == 97 ) {
			goto _ctr4;
		}
		{
			goto _st0;
		}
		_ctr4:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b0 = p; }
		
#line 157 "gen/ragel/cat2_4-G2.c"
		
		goto _st3;
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		if ( ( (*( p))) == 97 ) {
			goto _ctr6;
		}
		{
			goto _st0;
		}
		_ctr6:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b0 = p; }
		
#line 176 "gen/ragel/cat2_4-G2.c"
		
		goto _st4;
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr8;
			}
			case 98: {
				goto _st15;
			}
		}
		{
			goto _st0;
		}
		_ctr8:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b0 = p; }
		
#line 200 "gen/ragel/cat2_4-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			a1 = p; }
		
#line 206 "gen/ragel/cat2_4-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b1 = p; }
		
#line 212 "gen/ragel/cat2_4-G2.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr11;
			}
			case 98: {
				goto _st15;
			}
		}
		{
			goto _st0;
		}
		_ctr11:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b0 = p; }
		
#line 236 "gen/ragel/cat2_4-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			a1 = p; }
		
#line 242 "gen/ragel/cat2_4-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b1 = p; }
		
#line 248 "gen/ragel/cat2_4-G2.c"
		
		goto _st6;
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr13;
			}
			case 98: {
				goto _st15;
			}
		}
		{
			goto _st0;
		}
		_ctr13:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b0 = p; }
		
#line 272 "gen/ragel/cat2_4-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			a1 = p; }
		
#line 278 "gen/ragel/cat2_4-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b1 = p; }
		
#line 284 "gen/ragel/cat2_4-G2.c"
		
		goto _st7;
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr15;
			}
			case 98: {
				goto _st15;
			}
		}
		{
			goto _st0;
		}
		_ctr15:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b0 = p; }
		
#line 308 "gen/ragel/cat2_4-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			a1 = p; }
		
#line 314 "gen/ragel/cat2_4-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b1 = p; }
		
#line 320 "gen/ragel/cat2_4-G2.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr17;
			}
			case 97: {
				goto _ctr15;
			}
			case 98: {
				goto _st9;
			}
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
				goto _ctr17;
			}
			case 97: {
				goto _ctr19;
			}
			case 98: {
				goto _st9;
			}
		}
		{
			goto _st0;
		}
		_ctr19:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			a1 = p; }
		
#line 366 "gen/ragel/cat2_4-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b1 = p; }
		
#line 372 "gen/ragel/cat2_4-G2.c"
		
		goto _st10;
		_st10:
		p+= 1;
		if ( p == pe )
			goto _test_eof10;
		st_case_10:
		if ( ( (*( p))) == 97 ) {
			goto _ctr21;
		}
		{
			goto _st0;
		}
		_ctr21:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b1 = p; }
		
#line 391 "gen/ragel/cat2_4-G2.c"
		
		goto _st11;
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
		if ( ( (*( p))) == 97 ) {
			goto _ctr23;
		}
		{
			goto _st0;
		}
		_ctr23:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b1 = p; }
		
#line 410 "gen/ragel/cat2_4-G2.c"
		
		goto _st12;
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
		if ( ( (*( p))) == 97 ) {
			goto _ctr25;
		}
		{
			goto _st0;
		}
		_ctr25:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
			b1 = p; }
		
#line 429 "gen/ragel/cat2_4-G2.c"
		
		goto _st13;
		_st13:
		p+= 1;
		if ( p == pe )
			goto _test_eof13;
		st_case_13:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr17;
			}
			case 97: {
				goto _ctr25;
			}
			case 98: {
				goto _st14;
			}
		}
		{
			goto _st0;
		}
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr17;
			}
			case 98: {
				goto _st14;
			}
		}
		{
			goto _st0;
		}
		_st15:
		p+= 1;
		if ( p == pe )
			goto _test_eof15;
		st_case_15:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr19;
			}
			case 98: {
				goto _st15;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof16: cs = 16; goto _test_eof; 
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
		
		_test_eof: {}
		if ( cs >= 16 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
