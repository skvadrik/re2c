#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"



#line 12 "gen/ragel/22__cat2_8.c"
static const int abcd_start = 28;
static const int abcd_first_final = 28;
static const int abcd_error = 0;

static const int abcd_en_main = 28;


#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1,
	*b0, *b1;
	int cs;
	
	
#line 33 "gen/ragel/22__cat2_8.c"
	{
		cs = (int)abcd_start;
	}
	
#line 30 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
	
	
#line 41 "gen/ragel/22__cat2_8.c"
	{
		switch ( cs ) {
			case 28:
			goto st_case_28;
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
		}
		_ctr33:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
		}
		
#line 111 "gen/ragel/22__cat2_8.c"
		
		goto _st28;
		_st28:
		p+= 1;
		st_case_28:
		if ( p == pe )
			goto _out28;
		if ( ( (*( p))) == 97 ) {
			goto _ctr53;
		}
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr53:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			a0 = p; }
		
#line 131 "gen/ragel/22__cat2_8.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 137 "gen/ragel/22__cat2_8.c"
		
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 154 "gen/ragel/22__cat2_8.c"
		
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 171 "gen/ragel/22__cat2_8.c"
		
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 188 "gen/ragel/22__cat2_8.c"
		
		goto _st4;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
		if ( ( (*( p))) == 97 ) {
			goto _ctr8;
		}
		goto _st0;
		_ctr8:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 205 "gen/ragel/22__cat2_8.c"
		
		goto _st5;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
		if ( ( (*( p))) == 97 ) {
			goto _ctr10;
		}
		goto _st0;
		_ctr10:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 222 "gen/ragel/22__cat2_8.c"
		
		goto _st6;
		_st6:
		p+= 1;
		st_case_6:
		if ( p == pe )
			goto _out6;
		if ( ( (*( p))) == 97 ) {
			goto _ctr12;
		}
		goto _st0;
		_ctr12:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 239 "gen/ragel/22__cat2_8.c"
		
		goto _st7;
		_st7:
		p+= 1;
		st_case_7:
		if ( p == pe )
			goto _out7;
		if ( ( (*( p))) == 97 ) {
			goto _ctr14;
		}
		goto _st0;
		_ctr14:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 256 "gen/ragel/22__cat2_8.c"
		
		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr16;
			}
			case 98: {
				goto _st27;
			}
		}
		goto _st0;
		_ctr16:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 278 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			a1 = p; }
		
#line 284 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 290 "gen/ragel/22__cat2_8.c"
		
		goto _st9;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr19;
			}
			case 98: {
				goto _st27;
			}
		}
		goto _st0;
		_ctr19:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 312 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			a1 = p; }
		
#line 318 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 324 "gen/ragel/22__cat2_8.c"
		
		goto _st10;
		_st10:
		p+= 1;
		st_case_10:
		if ( p == pe )
			goto _out10;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr21;
			}
			case 98: {
				goto _st27;
			}
		}
		goto _st0;
		_ctr21:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 346 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			a1 = p; }
		
#line 352 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 358 "gen/ragel/22__cat2_8.c"
		
		goto _st11;
		_st11:
		p+= 1;
		st_case_11:
		if ( p == pe )
			goto _out11;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr23;
			}
			case 98: {
				goto _st27;
			}
		}
		goto _st0;
		_ctr23:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 380 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			a1 = p; }
		
#line 386 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 392 "gen/ragel/22__cat2_8.c"
		
		goto _st12;
		_st12:
		p+= 1;
		st_case_12:
		if ( p == pe )
			goto _out12;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr25;
			}
			case 98: {
				goto _st27;
			}
		}
		goto _st0;
		_ctr25:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 414 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			a1 = p; }
		
#line 420 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 426 "gen/ragel/22__cat2_8.c"
		
		goto _st13;
		_st13:
		p+= 1;
		st_case_13:
		if ( p == pe )
			goto _out13;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr27;
			}
			case 98: {
				goto _st27;
			}
		}
		goto _st0;
		_ctr27:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 448 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			a1 = p; }
		
#line 454 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 460 "gen/ragel/22__cat2_8.c"
		
		goto _st14;
		_st14:
		p+= 1;
		st_case_14:
		if ( p == pe )
			goto _out14;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr29;
			}
			case 98: {
				goto _st27;
			}
		}
		goto _st0;
		_ctr29:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 482 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			a1 = p; }
		
#line 488 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 494 "gen/ragel/22__cat2_8.c"
		
		goto _st15;
		_st15:
		p+= 1;
		st_case_15:
		if ( p == pe )
			goto _out15;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr31;
			}
			case 98: {
				goto _st27;
			}
		}
		goto _st0;
		_ctr31:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b0 = p; }
		
#line 516 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			a1 = p; }
		
#line 522 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 528 "gen/ragel/22__cat2_8.c"
		
		goto _st16;
		_st16:
		p+= 1;
		st_case_16:
		if ( p == pe )
			goto _out16;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr33;
			}
			case 97: {
				goto _ctr31;
			}
			case 98: {
				goto _st17;
			}
		}
		goto _st0;
		_st17:
		p+= 1;
		st_case_17:
		if ( p == pe )
			goto _out17;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr33;
			}
			case 97: {
				goto _ctr35;
			}
			case 98: {
				goto _st17;
			}
		}
		goto _st0;
		_ctr35:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			a1 = p; }
		
#line 570 "gen/ragel/22__cat2_8.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 576 "gen/ragel/22__cat2_8.c"
		
		goto _st18;
		_st18:
		p+= 1;
		st_case_18:
		if ( p == pe )
			goto _out18;
		if ( ( (*( p))) == 97 ) {
			goto _ctr37;
		}
		goto _st0;
		_ctr37:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 593 "gen/ragel/22__cat2_8.c"
		
		goto _st19;
		_st19:
		p+= 1;
		st_case_19:
		if ( p == pe )
			goto _out19;
		if ( ( (*( p))) == 97 ) {
			goto _ctr39;
		}
		goto _st0;
		_ctr39:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 610 "gen/ragel/22__cat2_8.c"
		
		goto _st20;
		_st20:
		p+= 1;
		st_case_20:
		if ( p == pe )
			goto _out20;
		if ( ( (*( p))) == 97 ) {
			goto _ctr41;
		}
		goto _st0;
		_ctr41:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 627 "gen/ragel/22__cat2_8.c"
		
		goto _st21;
		_st21:
		p+= 1;
		st_case_21:
		if ( p == pe )
			goto _out21;
		if ( ( (*( p))) == 97 ) {
			goto _ctr43;
		}
		goto _st0;
		_ctr43:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 644 "gen/ragel/22__cat2_8.c"
		
		goto _st22;
		_st22:
		p+= 1;
		st_case_22:
		if ( p == pe )
			goto _out22;
		if ( ( (*( p))) == 97 ) {
			goto _ctr45;
		}
		goto _st0;
		_ctr45:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 661 "gen/ragel/22__cat2_8.c"
		
		goto _st23;
		_st23:
		p+= 1;
		st_case_23:
		if ( p == pe )
			goto _out23;
		if ( ( (*( p))) == 97 ) {
			goto _ctr47;
		}
		goto _st0;
		_ctr47:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 678 "gen/ragel/22__cat2_8.c"
		
		goto _st24;
		_st24:
		p+= 1;
		st_case_24:
		if ( p == pe )
			goto _out24;
		if ( ( (*( p))) == 97 ) {
			goto _ctr49;
		}
		goto _st0;
		_ctr49:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
			b1 = p; }
		
#line 695 "gen/ragel/22__cat2_8.c"
		
		goto _st25;
		_st25:
		p+= 1;
		st_case_25:
		if ( p == pe )
			goto _out25;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr33;
			}
			case 97: {
				goto _ctr49;
			}
			case 98: {
				goto _st26;
			}
		}
		goto _st0;
		_st26:
		p+= 1;
		st_case_26:
		if ( p == pe )
			goto _out26;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr33;
			}
			case 98: {
				goto _st26;
			}
		}
		goto _st0;
		_st27:
		p+= 1;
		st_case_27:
		if ( p == pe )
			goto _out27;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr35;
			}
			case 98: {
				goto _st27;
			}
		}
		goto _st0;
		_out28: cs = 28; goto _out; 
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
		_out: {}
	}
	
#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/22__cat2_8.rl"
	
	
	in->p = p;
	in->pe = pe;
}
