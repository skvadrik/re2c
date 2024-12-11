#line 1 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 17 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"



#line 9 "gen/ragel/submatch_21__cat2_4.c"
static const int abcd_start = 16;
static const int abcd_first_final = 16;
static const int abcd_error = 0;

static const int abcd_en_main = 16;


#line 19 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1,
	*b0, *b1;
	int cs;
	

#line 27 "gen/ragel/submatch_21__cat2_4.c"
	{
		cs = (int)abcd_start;
	}
	
#line 30 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"


#line 32 "gen/ragel/submatch_21__cat2_4.c"
{
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
		_ctr17:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 77 "gen/ragel/submatch_21__cat2_4.c"

		goto _st16;
		_st16:
		p+= 1;
		st_case_16:
		if ( p == pe )
			goto _out16;
		if ( ( (*( p))) == 97 ) {
			goto _ctr29;
		}
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr29:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			a0 = p; }
		
#line 96 "gen/ragel/submatch_21__cat2_4.c"

			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b0 = p; }
		
#line 101 "gen/ragel/submatch_21__cat2_4.c"

		goto _st1;
		_st1:
		p+= 1;
		st_case_1:
		if ( p == pe )
			goto _out1;
		if ( ( (*( p))) == 97 ) {
			goto _ctr2;
		}
		goto _st0;
		_ctr2:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b0 = p; }
		
#line 117 "gen/ragel/submatch_21__cat2_4.c"

		goto _st2;
		_st2:
		p+= 1;
		st_case_2:
		if ( p == pe )
			goto _out2;
		if ( ( (*( p))) == 97 ) {
			goto _ctr4;
		}
		goto _st0;
		_ctr4:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b0 = p; }
		
#line 133 "gen/ragel/submatch_21__cat2_4.c"

		goto _st3;
		_st3:
		p+= 1;
		st_case_3:
		if ( p == pe )
			goto _out3;
		if ( ( (*( p))) == 97 ) {
			goto _ctr6;
		}
		goto _st0;
		_ctr6:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b0 = p; }
		
#line 149 "gen/ragel/submatch_21__cat2_4.c"

		goto _st4;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr8;
			}
			case 98: {
				goto _st15;
			}
		}
		goto _st0;
		_ctr8:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b0 = p; }
		
#line 170 "gen/ragel/submatch_21__cat2_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			a1 = p; }
		
#line 175 "gen/ragel/submatch_21__cat2_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b1 = p; }
		
#line 180 "gen/ragel/submatch_21__cat2_4.c"

		goto _st5;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr11;
			}
			case 98: {
				goto _st15;
			}
		}
		goto _st0;
		_ctr11:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b0 = p; }
		
#line 201 "gen/ragel/submatch_21__cat2_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			a1 = p; }
		
#line 206 "gen/ragel/submatch_21__cat2_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b1 = p; }
		
#line 211 "gen/ragel/submatch_21__cat2_4.c"

		goto _st6;
		_st6:
		p+= 1;
		st_case_6:
		if ( p == pe )
			goto _out6;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr13;
			}
			case 98: {
				goto _st15;
			}
		}
		goto _st0;
		_ctr13:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b0 = p; }
		
#line 232 "gen/ragel/submatch_21__cat2_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			a1 = p; }
		
#line 237 "gen/ragel/submatch_21__cat2_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b1 = p; }
		
#line 242 "gen/ragel/submatch_21__cat2_4.c"

		goto _st7;
		_st7:
		p+= 1;
		st_case_7:
		if ( p == pe )
			goto _out7;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr15;
			}
			case 98: {
				goto _st15;
			}
		}
		goto _st0;
		_ctr15:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b0 = p; }
		
#line 263 "gen/ragel/submatch_21__cat2_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			a1 = p; }
		
#line 268 "gen/ragel/submatch_21__cat2_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b1 = p; }
		
#line 273 "gen/ragel/submatch_21__cat2_4.c"

		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
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
		goto _st0;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
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
		goto _st0;
		_ctr19:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			a1 = p; }
		
#line 314 "gen/ragel/submatch_21__cat2_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b1 = p; }
		
#line 319 "gen/ragel/submatch_21__cat2_4.c"

		goto _st10;
		_st10:
		p+= 1;
		st_case_10:
		if ( p == pe )
			goto _out10;
		if ( ( (*( p))) == 97 ) {
			goto _ctr21;
		}
		goto _st0;
		_ctr21:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b1 = p; }
		
#line 335 "gen/ragel/submatch_21__cat2_4.c"

		goto _st11;
		_st11:
		p+= 1;
		st_case_11:
		if ( p == pe )
			goto _out11;
		if ( ( (*( p))) == 97 ) {
			goto _ctr23;
		}
		goto _st0;
		_ctr23:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b1 = p; }
		
#line 351 "gen/ragel/submatch_21__cat2_4.c"

		goto _st12;
		_st12:
		p+= 1;
		st_case_12:
		if ( p == pe )
			goto _out12;
		if ( ( (*( p))) == 97 ) {
			goto _ctr25;
		}
		goto _st0;
		_ctr25:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"
			b1 = p; }
		
#line 367 "gen/ragel/submatch_21__cat2_4.c"

		goto _st13;
		_st13:
		p+= 1;
		st_case_13:
		if ( p == pe )
			goto _out13;
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
		goto _st0;
		_st14:
		p+= 1;
		st_case_14:
		if ( p == pe )
			goto _out14;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr17;
			}
			case 98: {
				goto _st14;
			}
		}
		goto _st0;
		_st15:
		p+= 1;
		st_case_15:
		if ( p == pe )
			goto _out15;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr19;
			}
			case 98: {
				goto _st15;
			}
		}
		goto _st0;
		_out16: cs = 16; goto _out; 
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
		_out: {}
	}
	
#line 31 "../../../benchmarks/c/src/ragel/submatch_21__cat2_4.rl"

	
	in->p = p;
	in->pe = pe;
}
