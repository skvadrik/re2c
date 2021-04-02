#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"



#line 12 "gen/ragel/20__cat2_0.c"
static const int abcd_start = 5;
static const int abcd_first_final = 5;
static const int abcd_error = 0;

static const int abcd_en_main = 5;


#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1,
	*b0, *b1;
	int cs;
	
	
#line 33 "gen/ragel/20__cat2_0.c"
	{
		cs = (int)abcd_start;
	}
	
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
	
	
#line 41 "gen/ragel/20__cat2_0.c"
	{
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
		_ctr2:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			b0 = p; }
		
#line 62 "gen/ragel/20__cat2_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			a1 = p; }
		
#line 68 "gen/ragel/20__cat2_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			b1 = p; }
		
#line 74 "gen/ragel/20__cat2_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 83 "gen/ragel/20__cat2_0.c"
		
		goto _st5;
		_ctr6:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			a1 = p; }
		
#line 91 "gen/ragel/20__cat2_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			b1 = p; }
		
#line 97 "gen/ragel/20__cat2_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 106 "gen/ragel/20__cat2_0.c"
		
		goto _st5;
		_ctr10:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			b1 = p; }
		
#line 114 "gen/ragel/20__cat2_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 123 "gen/ragel/20__cat2_0.c"
		
		goto _st5;
		_ctr13:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 134 "gen/ragel/20__cat2_0.c"
		
		goto _st5;
		_ctr15:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			a0 = p; }
		
#line 142 "gen/ragel/20__cat2_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			b0 = p; }
		
#line 148 "gen/ragel/20__cat2_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			a1 = p; }
		
#line 154 "gen/ragel/20__cat2_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			b1 = p; }
		
#line 160 "gen/ragel/20__cat2_0.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 169 "gen/ragel/20__cat2_0.c"
		
		goto _st5;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
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
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr3:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			b0 = p; }
		
#line 197 "gen/ragel/20__cat2_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			a1 = p; }
		
#line 203 "gen/ragel/20__cat2_0.c"
		
		goto _st1;
		_ctr16:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			a0 = p; }
		
#line 211 "gen/ragel/20__cat2_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			b0 = p; }
		
#line 217 "gen/ragel/20__cat2_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			a1 = p; }
		
#line 223 "gen/ragel/20__cat2_0.c"
		
		goto _st1;
		_st1:
		p+= 1;
		st_case_1:
		if ( p == pe )
			goto _out1;
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
		goto _st0;
		_ctr4:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			b0 = p; }
		
#line 248 "gen/ragel/20__cat2_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			a1 = p; }
		
#line 254 "gen/ragel/20__cat2_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			b1 = p; }
		
#line 260 "gen/ragel/20__cat2_0.c"
		
		goto _st2;
		_ctr8:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			a1 = p; }
		
#line 268 "gen/ragel/20__cat2_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			b1 = p; }
		
#line 274 "gen/ragel/20__cat2_0.c"
		
		goto _st2;
		_ctr17:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			a0 = p; }
		
#line 282 "gen/ragel/20__cat2_0.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			b0 = p; }
		
#line 288 "gen/ragel/20__cat2_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			a1 = p; }
		
#line 294 "gen/ragel/20__cat2_0.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			b1 = p; }
		
#line 300 "gen/ragel/20__cat2_0.c"
		
		goto _st2;
		_st2:
		p+= 1;
		st_case_2:
		if ( p == pe )
			goto _out2;
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
		goto _st0;
		_ctr7:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			a1 = p; }
		
#line 325 "gen/ragel/20__cat2_0.c"
		
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
			case 97: {
				goto _st3;
			}
			case 98: {
				goto _ctr11;
			}
		}
		goto _st0;
		_ctr11:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
			b1 = p; }
		
#line 350 "gen/ragel/20__cat2_0.c"
		
		goto _st4;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr13;
			}
			case 98: {
				goto _st4;
			}
		}
		goto _st0;
		_out5: cs = 5; goto _out; 
		_out0: cs = 0; goto _out; 
		_out1: cs = 1; goto _out; 
		_out2: cs = 2; goto _out; 
		_out3: cs = 3; goto _out; 
		_out4: cs = 4; goto _out; 
		_out: {}
	}
	
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/20__cat2_0.rl"
	
	
	in->p = p;
	in->pe = pe;
}
