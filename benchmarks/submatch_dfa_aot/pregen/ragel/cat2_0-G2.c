#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"



#line 12 "gen/ragel/cat2_0-G2.c"
static const int abcd_start = 5;
static const int abcd_first_final = 5;
static const int abcd_error = 0;

static const int abcd_en_main = 5;


#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1,
	*b0, *b1;
	int cs;
	
	
#line 33 "gen/ragel/cat2_0-G2.c"
	{
		cs = (int)abcd_start;
	}
	
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
	
	
#line 41 "gen/ragel/cat2_0-G2.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 5:
			goto st_case_5;
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
		}
		goto st_out;
		_ctr2:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			b0 = p; }
		
#line 65 "gen/ragel/cat2_0-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			a1 = p; }
		
#line 71 "gen/ragel/cat2_0-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			b1 = p; }
		
#line 77 "gen/ragel/cat2_0-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 86 "gen/ragel/cat2_0-G2.c"
		
		goto _st5;
		_ctr6:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			a1 = p; }
		
#line 94 "gen/ragel/cat2_0-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			b1 = p; }
		
#line 100 "gen/ragel/cat2_0-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 109 "gen/ragel/cat2_0-G2.c"
		
		goto _st5;
		_ctr10:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			b1 = p; }
		
#line 117 "gen/ragel/cat2_0-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 126 "gen/ragel/cat2_0-G2.c"
		
		goto _st5;
		_ctr13:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 137 "gen/ragel/cat2_0-G2.c"
		
		goto _st5;
		_ctr15:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			a0 = p; }
		
#line 145 "gen/ragel/cat2_0-G2.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			b0 = p; }
		
#line 151 "gen/ragel/cat2_0-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			a1 = p; }
		
#line 157 "gen/ragel/cat2_0-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			b1 = p; }
		
#line 163 "gen/ragel/cat2_0-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 172 "gen/ragel/cat2_0-G2.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr15;
			}
			case 97: {
				goto _ctr16;
			}
			case 98: {
				goto _ctr17;
			}
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr3:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			b0 = p; }
		
#line 203 "gen/ragel/cat2_0-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			a1 = p; }
		
#line 209 "gen/ragel/cat2_0-G2.c"
		
		goto _st1;
		_ctr16:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			a0 = p; }
		
#line 217 "gen/ragel/cat2_0-G2.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			b0 = p; }
		
#line 223 "gen/ragel/cat2_0-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			a1 = p; }
		
#line 229 "gen/ragel/cat2_0-G2.c"
		
		goto _st1;
		_st1:
		p+= 1;
		if ( p == pe )
			goto _test_eof1;
		st_case_1:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr2;
			}
			case 97: {
				goto _ctr3;
			}
			case 98: {
				goto _ctr4;
			}
		}
		{
			goto _st0;
		}
		_ctr4:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			b0 = p; }
		
#line 256 "gen/ragel/cat2_0-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			a1 = p; }
		
#line 262 "gen/ragel/cat2_0-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			b1 = p; }
		
#line 268 "gen/ragel/cat2_0-G2.c"
		
		goto _st2;
		_ctr8:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			a1 = p; }
		
#line 276 "gen/ragel/cat2_0-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			b1 = p; }
		
#line 282 "gen/ragel/cat2_0-G2.c"
		
		goto _st2;
		_ctr17:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			a0 = p; }
		
#line 290 "gen/ragel/cat2_0-G2.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			b0 = p; }
		
#line 296 "gen/ragel/cat2_0-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			a1 = p; }
		
#line 302 "gen/ragel/cat2_0-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			b1 = p; }
		
#line 308 "gen/ragel/cat2_0-G2.c"
		
		goto _st2;
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr6;
			}
			case 97: {
				goto _ctr7;
			}
			case 98: {
				goto _ctr8;
			}
		}
		{
			goto _st0;
		}
		_ctr7:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			a1 = p; }
		
#line 335 "gen/ragel/cat2_0-G2.c"
		
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
			case 97: {
				goto _st3;
			}
			case 98: {
				goto _ctr11;
			}
		}
		{
			goto _st0;
		}
		_ctr11:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
			b1 = p; }
		
#line 362 "gen/ragel/cat2_0-G2.c"
		
		goto _st4;
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr13;
			}
			case 98: {
				goto _st4;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof5: cs = 5; goto _test_eof; 
		_test_eof1: cs = 1; goto _test_eof; 
		_test_eof2: cs = 2; goto _test_eof; 
		_test_eof3: cs = 3; goto _test_eof; 
		_test_eof4: cs = 4; goto _test_eof; 
		
		_test_eof: {}
		if ( cs >= 5 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat2_0.rl"
	
	
	in->p = p;
	in->pe = pe;
}
