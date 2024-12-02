#line 1 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 17 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"



#line 9 "gen/ragel/submatch_20__cat2_0.c"
static const int abcd_start = 5;
static const int abcd_first_final = 5;
static const int abcd_error = 0;

static const int abcd_en_main = 5;


#line 19 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1,
	*b0, *b1;
	int cs;
	

#line 27 "gen/ragel/submatch_20__cat2_0.c"
	{
		cs = (int)abcd_start;
	}
	
#line 30 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"


#line 32 "gen/ragel/submatch_20__cat2_0.c"
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
#line 9 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			b0 = p; }
		
#line 52 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			a1 = p; }
		
#line 57 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			b1 = p; }
		
#line 62 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 70 "gen/ragel/submatch_20__cat2_0.c"

		goto _st5;
		_ctr6:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			a1 = p; }
		
#line 77 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			b1 = p; }
		
#line 82 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 90 "gen/ragel/submatch_20__cat2_0.c"

		goto _st5;
		_ctr10:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			b1 = p; }
		
#line 97 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 105 "gen/ragel/submatch_20__cat2_0.c"

		goto _st5;
		_ctr13:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 115 "gen/ragel/submatch_20__cat2_0.c"

		goto _st5;
		_ctr15:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			a0 = p; }
		
#line 122 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			b0 = p; }
		
#line 127 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			a1 = p; }
		
#line 132 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			b1 = p; }
		
#line 137 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 145 "gen/ragel/submatch_20__cat2_0.c"

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
#line 9 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			b0 = p; }
		
#line 172 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			a1 = p; }
		
#line 177 "gen/ragel/submatch_20__cat2_0.c"

		goto _st1;
		_ctr16:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			a0 = p; }
		
#line 184 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			b0 = p; }
		
#line 189 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			a1 = p; }
		
#line 194 "gen/ragel/submatch_20__cat2_0.c"

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
#line 9 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			b0 = p; }
		
#line 218 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			a1 = p; }
		
#line 223 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			b1 = p; }
		
#line 228 "gen/ragel/submatch_20__cat2_0.c"

		goto _st2;
		_ctr8:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			a1 = p; }
		
#line 235 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			b1 = p; }
		
#line 240 "gen/ragel/submatch_20__cat2_0.c"

		goto _st2;
		_ctr17:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			a0 = p; }
		
#line 247 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			b0 = p; }
		
#line 252 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			a1 = p; }
		
#line 257 "gen/ragel/submatch_20__cat2_0.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			b1 = p; }
		
#line 262 "gen/ragel/submatch_20__cat2_0.c"

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
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			a1 = p; }
		
#line 286 "gen/ragel/submatch_20__cat2_0.c"

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
#line 10 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"
			b1 = p; }
		
#line 310 "gen/ragel/submatch_20__cat2_0.c"

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
	
#line 31 "../../../benchmarks/c/src/ragel/submatch_20__cat2_0.rl"

	
	in->p = p;
	in->pe = pe;
}
