#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"



#line 12 "gen/ragel/24__cat4_2.c"
static const int abcd_start = 34;
static const int abcd_first_final = 34;
static const int abcd_error = 0;

static const int abcd_en_main = 34;


#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3,
	*b0, *b1, *b2, *b3;
	int cs;
	
	
#line 33 "gen/ragel/24__cat4_2.c"
	{
		cs = (int)abcd_start;
	}
	
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
	
	
#line 41 "gen/ragel/24__cat4_2.c"
	{
		switch ( cs ) {
			case 34:
			goto st_case_34;
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
		}
		_ctr19:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 125 "gen/ragel/24__cat4_2.c"
		
		goto _st34;
		_st34:
		p+= 1;
		st_case_34:
		if ( p == pe )
			goto _out34;
		if ( ( (*( p))) == 97 ) {
			goto _ctr61;
		}
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr61:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a0 = p; }
		
#line 145 "gen/ragel/24__cat4_2.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 151 "gen/ragel/24__cat4_2.c"
		
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 168 "gen/ragel/24__cat4_2.c"
		
		goto _st2;
		_st2:
		p+= 1;
		st_case_2:
		if ( p == pe )
			goto _out2;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr4;
			}
			case 98: {
				goto _st25;
			}
		}
		goto _st0;
		_ctr4:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 190 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 196 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 202 "gen/ragel/24__cat4_2.c"
		
		goto _st3;
		_st3:
		p+= 1;
		st_case_3:
		if ( p == pe )
			goto _out3;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr7;
			}
			case 98: {
				goto _st25;
			}
		}
		goto _st0;
		_ctr7:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 224 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 230 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 236 "gen/ragel/24__cat4_2.c"
		
		goto _st4;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr9;
			}
			case 98: {
				goto _st20;
			}
		}
		goto _st0;
		_ctr9:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 258 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 264 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 270 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 276 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 282 "gen/ragel/24__cat4_2.c"
		
		goto _st5;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr12;
			}
			case 98: {
				goto _st20;
			}
		}
		goto _st0;
		_ctr12:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 304 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 310 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 316 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 322 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 328 "gen/ragel/24__cat4_2.c"
		
		goto _st6;
		_st6:
		p+= 1;
		st_case_6:
		if ( p == pe )
			goto _out6;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr14;
			}
			case 98: {
				goto _st19;
			}
		}
		goto _st0;
		_ctr14:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 350 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 356 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 362 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 368 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 374 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 380 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 386 "gen/ragel/24__cat4_2.c"
		
		goto _st7;
		_st7:
		p+= 1;
		st_case_7:
		if ( p == pe )
			goto _out7;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr17;
			}
			case 98: {
				goto _st19;
			}
		}
		goto _st0;
		_ctr17:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 408 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 414 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 420 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 426 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 432 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 438 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 444 "gen/ragel/24__cat4_2.c"
		
		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr19;
			}
			case 97: {
				goto _ctr17;
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
				goto _ctr19;
			}
			case 97: {
				goto _ctr21;
			}
			case 98: {
				goto _st9;
			}
		}
		goto _st0;
		_ctr21:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 486 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 492 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 498 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 504 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 510 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 516 "gen/ragel/24__cat4_2.c"
		
		goto _st10;
		_st10:
		p+= 1;
		st_case_10:
		if ( p == pe )
			goto _out10;
		if ( ( (*( p))) == 97 ) {
			goto _ctr23;
		}
		goto _st0;
		_ctr23:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 533 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 539 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 545 "gen/ragel/24__cat4_2.c"
		
		goto _st11;
		_ctr25:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 553 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 559 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 565 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 571 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 577 "gen/ragel/24__cat4_2.c"
		
		goto _st11;
		_st11:
		p+= 1;
		st_case_11:
		if ( p == pe )
			goto _out11;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr19;
			}
			case 97: {
				goto _ctr25;
			}
			case 98: {
				goto _st12;
			}
		}
		goto _st0;
		_st12:
		p+= 1;
		st_case_12:
		if ( p == pe )
			goto _out12;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr19;
			}
			case 97: {
				goto _ctr27;
			}
			case 98: {
				goto _st12;
			}
		}
		goto _st0;
		_ctr27:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 619 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 625 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 631 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 637 "gen/ragel/24__cat4_2.c"
		
		goto _st13;
		_st13:
		p+= 1;
		st_case_13:
		if ( p == pe )
			goto _out13;
		if ( ( (*( p))) == 97 ) {
			goto _ctr29;
		}
		goto _st0;
		_ctr29:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 654 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 660 "gen/ragel/24__cat4_2.c"
		
		goto _st14;
		_ctr31:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 668 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 674 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 680 "gen/ragel/24__cat4_2.c"
		
		goto _st14;
		_st14:
		p+= 1;
		st_case_14:
		if ( p == pe )
			goto _out14;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr19;
			}
			case 97: {
				goto _ctr31;
			}
			case 98: {
				goto _st15;
			}
		}
		goto _st0;
		_st15:
		p+= 1;
		st_case_15:
		if ( p == pe )
			goto _out15;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr19;
			}
			case 97: {
				goto _ctr33;
			}
			case 98: {
				goto _st15;
			}
		}
		goto _st0;
		_ctr33:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 722 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 728 "gen/ragel/24__cat4_2.c"
		
		goto _st16;
		_st16:
		p+= 1;
		st_case_16:
		if ( p == pe )
			goto _out16;
		if ( ( (*( p))) == 97 ) {
			goto _ctr35;
		}
		goto _st0;
		_ctr35:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 745 "gen/ragel/24__cat4_2.c"
		
		goto _st17;
		_st17:
		p+= 1;
		st_case_17:
		if ( p == pe )
			goto _out17;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr19;
			}
			case 97: {
				goto _ctr35;
			}
			case 98: {
				goto _st18;
			}
		}
		goto _st0;
		_st18:
		p+= 1;
		st_case_18:
		if ( p == pe )
			goto _out18;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr19;
			}
			case 98: {
				goto _st18;
			}
		}
		goto _st0;
		_st19:
		p+= 1;
		st_case_19:
		if ( p == pe )
			goto _out19;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr21;
			}
			case 98: {
				goto _st19;
			}
		}
		goto _st0;
		_st20:
		p+= 1;
		st_case_20:
		if ( p == pe )
			goto _out20;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr38;
			}
			case 98: {
				goto _st20;
			}
		}
		goto _st0;
		_ctr38:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 812 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 818 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 824 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 830 "gen/ragel/24__cat4_2.c"
		
		goto _st21;
		_st21:
		p+= 1;
		st_case_21:
		if ( p == pe )
			goto _out21;
		if ( ( (*( p))) == 97 ) {
			goto _ctr40;
		}
		goto _st0;
		_ctr40:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 847 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 853 "gen/ragel/24__cat4_2.c"
		
		goto _st22;
		_ctr52:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 861 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 867 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 873 "gen/ragel/24__cat4_2.c"
		
		goto _st22;
		_st22:
		p+= 1;
		st_case_22:
		if ( p == pe )
			goto _out22;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr42;
			}
			case 98: {
				goto _st24;
			}
		}
		goto _st0;
		_ctr42:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 895 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 901 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 907 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 913 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 919 "gen/ragel/24__cat4_2.c"
		
		goto _st23;
		_st23:
		p+= 1;
		st_case_23:
		if ( p == pe )
			goto _out23;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr25;
			}
			case 98: {
				goto _st24;
			}
		}
		goto _st0;
		_st24:
		p+= 1;
		st_case_24:
		if ( p == pe )
			goto _out24;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr27;
			}
			case 98: {
				goto _st24;
			}
		}
		goto _st0;
		_st25:
		p+= 1;
		st_case_25:
		if ( p == pe )
			goto _out25;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr45;
			}
			case 98: {
				goto _st25;
			}
		}
		goto _st0;
		_ctr45:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 969 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 975 "gen/ragel/24__cat4_2.c"
		
		goto _st26;
		_st26:
		p+= 1;
		st_case_26:
		if ( p == pe )
			goto _out26;
		if ( ( (*( p))) == 97 ) {
			goto _ctr47;
		}
		goto _st0;
		_ctr47:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 992 "gen/ragel/24__cat4_2.c"
		
		goto _st27;
		_st27:
		p+= 1;
		st_case_27:
		if ( p == pe )
			goto _out27;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr49;
			}
			case 98: {
				goto _st29;
			}
		}
		goto _st0;
		_ctr49:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 1014 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 1020 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 1026 "gen/ragel/24__cat4_2.c"
		
		goto _st28;
		_st28:
		p+= 1;
		st_case_28:
		if ( p == pe )
			goto _out28;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr52;
			}
			case 98: {
				goto _st29;
			}
		}
		goto _st0;
		_st29:
		p+= 1;
		st_case_29:
		if ( p == pe )
			goto _out29;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr53;
			}
			case 98: {
				goto _st29;
			}
		}
		goto _st0;
		_ctr53:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 1062 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 1068 "gen/ragel/24__cat4_2.c"
		
		goto _st30;
		_st30:
		p+= 1;
		st_case_30:
		if ( p == pe )
			goto _out30;
		if ( ( (*( p))) == 97 ) {
			goto _ctr55;
		}
		goto _st0;
		_ctr55:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 1085 "gen/ragel/24__cat4_2.c"
		
		goto _st31;
		_st31:
		p+= 1;
		st_case_31:
		if ( p == pe )
			goto _out31;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr57;
			}
			case 98: {
				goto _st33;
			}
		}
		goto _st0;
		_ctr57:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 1107 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 1113 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 1119 "gen/ragel/24__cat4_2.c"
		
		goto _st32;
		_st32:
		p+= 1;
		st_case_32:
		if ( p == pe )
			goto _out32;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr31;
			}
			case 98: {
				goto _st33;
			}
		}
		goto _st0;
		_st33:
		p+= 1;
		st_case_33:
		if ( p == pe )
			goto _out33;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr33;
			}
			case 98: {
				goto _st33;
			}
		}
		goto _st0;
		_out34: cs = 34; goto _out; 
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
		_out: {}
	}
	
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
	
	
	in->p = p;
	in->pe = pe;
}
