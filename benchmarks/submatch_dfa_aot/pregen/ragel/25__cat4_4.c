#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"



#line 12 "gen/ragel/25__cat4_4.c"
static const int abcd_start = 60;
static const int abcd_first_final = 60;
static const int abcd_error = 0;

static const int abcd_en_main = 60;


#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3,
	*b0, *b1, *b2, *b3;
	int cs;
	
	
#line 33 "gen/ragel/25__cat4_4.c"
	{
		cs = (int)abcd_start;
	}
	
#line 34 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
	
	
#line 41 "gen/ragel/25__cat4_4.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 60:
			goto st_case_60;
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
			case 47:
			goto st_case_47;
			case 48:
			goto st_case_48;
			case 49:
			goto st_case_49;
			case 50:
			goto st_case_50;
			case 51:
			goto st_case_51;
			case 52:
			goto st_case_52;
			case 53:
			goto st_case_53;
			case 54:
			goto st_case_54;
			case 55:
			goto st_case_55;
			case 56:
			goto st_case_56;
			case 57:
			goto st_case_57;
			case 58:
			goto st_case_58;
			case 59:
			goto st_case_59;
		}
		goto st_out;
		_ctr35:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 180 "gen/ragel/25__cat4_4.c"
		
		goto _st60;
		_st60:
		p+= 1;
		if ( p == pe )
			goto _test_eof60;
		st_case_60:
		if ( ( (*( p))) == 97 ) {
			goto _ctr113;
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr113:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a0 = p; }
		
#line 203 "gen/ragel/25__cat4_4.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 209 "gen/ragel/25__cat4_4.c"
		
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 228 "gen/ragel/25__cat4_4.c"
		
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 247 "gen/ragel/25__cat4_4.c"
		
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 266 "gen/ragel/25__cat4_4.c"
		
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
				goto _st43;
			}
		}
		{
			goto _st0;
		}
		_ctr8:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 290 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 296 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 302 "gen/ragel/25__cat4_4.c"
		
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
				goto _st43;
			}
		}
		{
			goto _st0;
		}
		_ctr11:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 326 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 332 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 338 "gen/ragel/25__cat4_4.c"
		
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
				goto _st43;
			}
		}
		{
			goto _st0;
		}
		_ctr13:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 362 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 368 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 374 "gen/ragel/25__cat4_4.c"
		
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
				goto _st43;
			}
		}
		{
			goto _st0;
		}
		_ctr15:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 398 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 404 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 410 "gen/ragel/25__cat4_4.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr17;
			}
			case 98: {
				goto _st34;
			}
		}
		{
			goto _st0;
		}
		_ctr17:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 434 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 440 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 446 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 452 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 458 "gen/ragel/25__cat4_4.c"
		
		goto _st9;
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr20;
			}
			case 98: {
				goto _st34;
			}
		}
		{
			goto _st0;
		}
		_ctr20:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 482 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 488 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 494 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 500 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 506 "gen/ragel/25__cat4_4.c"
		
		goto _st10;
		_st10:
		p+= 1;
		if ( p == pe )
			goto _test_eof10;
		st_case_10:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr22;
			}
			case 98: {
				goto _st34;
			}
		}
		{
			goto _st0;
		}
		_ctr22:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 530 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 536 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 542 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 548 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 554 "gen/ragel/25__cat4_4.c"
		
		goto _st11;
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr24;
			}
			case 98: {
				goto _st34;
			}
		}
		{
			goto _st0;
		}
		_ctr24:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 578 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 584 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 590 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 596 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 602 "gen/ragel/25__cat4_4.c"
		
		goto _st12;
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr26;
			}
			case 98: {
				goto _st33;
			}
		}
		{
			goto _st0;
		}
		_ctr26:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 626 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 632 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 638 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 644 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 650 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 656 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 662 "gen/ragel/25__cat4_4.c"
		
		goto _st13;
		_st13:
		p+= 1;
		if ( p == pe )
			goto _test_eof13;
		st_case_13:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr29;
			}
			case 98: {
				goto _st33;
			}
		}
		{
			goto _st0;
		}
		_ctr29:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 686 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 692 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 698 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 704 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 710 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 716 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 722 "gen/ragel/25__cat4_4.c"
		
		goto _st14;
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr31;
			}
			case 98: {
				goto _st33;
			}
		}
		{
			goto _st0;
		}
		_ctr31:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 746 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 752 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 758 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 764 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 770 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 776 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 782 "gen/ragel/25__cat4_4.c"
		
		goto _st15;
		_st15:
		p+= 1;
		if ( p == pe )
			goto _test_eof15;
		st_case_15:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr33;
			}
			case 98: {
				goto _st33;
			}
		}
		{
			goto _st0;
		}
		_ctr33:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b0 = p; }
		
#line 806 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 812 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 818 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 824 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 830 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 836 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 842 "gen/ragel/25__cat4_4.c"
		
		goto _st16;
		_st16:
		p+= 1;
		if ( p == pe )
			goto _test_eof16;
		st_case_16:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr35;
			}
			case 97: {
				goto _ctr33;
			}
			case 98: {
				goto _st17;
			}
		}
		{
			goto _st0;
		}
		_st17:
		p+= 1;
		if ( p == pe )
			goto _test_eof17;
		st_case_17:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr35;
			}
			case 97: {
				goto _ctr37;
			}
			case 98: {
				goto _st17;
			}
		}
		{
			goto _st0;
		}
		_ctr37:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 888 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 894 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 900 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 906 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 912 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 918 "gen/ragel/25__cat4_4.c"
		
		goto _st18;
		_st18:
		p+= 1;
		if ( p == pe )
			goto _test_eof18;
		st_case_18:
		if ( ( (*( p))) == 97 ) {
			goto _ctr39;
		}
		{
			goto _st0;
		}
		_ctr39:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 937 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 943 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 949 "gen/ragel/25__cat4_4.c"
		
		goto _st19;
		_st19:
		p+= 1;
		if ( p == pe )
			goto _test_eof19;
		st_case_19:
		if ( ( (*( p))) == 97 ) {
			goto _ctr41;
		}
		{
			goto _st0;
		}
		_ctr41:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 968 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 974 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 980 "gen/ragel/25__cat4_4.c"
		
		goto _st20;
		_st20:
		p+= 1;
		if ( p == pe )
			goto _test_eof20;
		st_case_20:
		if ( ( (*( p))) == 97 ) {
			goto _ctr43;
		}
		{
			goto _st0;
		}
		_ctr43:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 999 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1005 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 1011 "gen/ragel/25__cat4_4.c"
		
		goto _st21;
		_ctr45:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1019 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 1025 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1031 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 1037 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 1043 "gen/ragel/25__cat4_4.c"
		
		goto _st21;
		_st21:
		p+= 1;
		if ( p == pe )
			goto _test_eof21;
		st_case_21:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr35;
			}
			case 97: {
				goto _ctr45;
			}
			case 98: {
				goto _st22;
			}
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
			case 10: {
				goto _ctr35;
			}
			case 97: {
				goto _ctr47;
			}
			case 98: {
				goto _st22;
			}
		}
		{
			goto _st0;
		}
		_ctr47:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 1089 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1095 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 1101 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 1107 "gen/ragel/25__cat4_4.c"
		
		goto _st23;
		_st23:
		p+= 1;
		if ( p == pe )
			goto _test_eof23;
		st_case_23:
		if ( ( (*( p))) == 97 ) {
			goto _ctr49;
		}
		{
			goto _st0;
		}
		_ctr49:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1126 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 1132 "gen/ragel/25__cat4_4.c"
		
		goto _st24;
		_st24:
		p+= 1;
		if ( p == pe )
			goto _test_eof24;
		st_case_24:
		if ( ( (*( p))) == 97 ) {
			goto _ctr51;
		}
		{
			goto _st0;
		}
		_ctr51:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1151 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 1157 "gen/ragel/25__cat4_4.c"
		
		goto _st25;
		_st25:
		p+= 1;
		if ( p == pe )
			goto _test_eof25;
		st_case_25:
		if ( ( (*( p))) == 97 ) {
			goto _ctr53;
		}
		{
			goto _st0;
		}
		_ctr53:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1176 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 1182 "gen/ragel/25__cat4_4.c"
		
		goto _st26;
		_ctr55:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1190 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 1196 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 1202 "gen/ragel/25__cat4_4.c"
		
		goto _st26;
		_st26:
		p+= 1;
		if ( p == pe )
			goto _test_eof26;
		st_case_26:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr35;
			}
			case 97: {
				goto _ctr55;
			}
			case 98: {
				goto _st27;
			}
		}
		{
			goto _st0;
		}
		_st27:
		p+= 1;
		if ( p == pe )
			goto _test_eof27;
		st_case_27:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr35;
			}
			case 97: {
				goto _ctr57;
			}
			case 98: {
				goto _st27;
			}
		}
		{
			goto _st0;
		}
		_ctr57:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 1248 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 1254 "gen/ragel/25__cat4_4.c"
		
		goto _st28;
		_st28:
		p+= 1;
		if ( p == pe )
			goto _test_eof28;
		st_case_28:
		if ( ( (*( p))) == 97 ) {
			goto _ctr59;
		}
		{
			goto _st0;
		}
		_ctr59:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 1273 "gen/ragel/25__cat4_4.c"
		
		goto _st29;
		_st29:
		p+= 1;
		if ( p == pe )
			goto _test_eof29;
		st_case_29:
		if ( ( (*( p))) == 97 ) {
			goto _ctr61;
		}
		{
			goto _st0;
		}
		_ctr61:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 1292 "gen/ragel/25__cat4_4.c"
		
		goto _st30;
		_st30:
		p+= 1;
		if ( p == pe )
			goto _test_eof30;
		st_case_30:
		if ( ( (*( p))) == 97 ) {
			goto _ctr63;
		}
		{
			goto _st0;
		}
		_ctr63:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 1311 "gen/ragel/25__cat4_4.c"
		
		goto _st31;
		_st31:
		p+= 1;
		if ( p == pe )
			goto _test_eof31;
		st_case_31:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr35;
			}
			case 97: {
				goto _ctr63;
			}
			case 98: {
				goto _st32;
			}
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
			case 10: {
				goto _ctr35;
			}
			case 98: {
				goto _st32;
			}
		}
		{
			goto _st0;
		}
		_st33:
		p+= 1;
		if ( p == pe )
			goto _test_eof33;
		st_case_33:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr37;
			}
			case 98: {
				goto _st33;
			}
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
			case 97: {
				goto _ctr66;
			}
			case 98: {
				goto _st34;
			}
		}
		{
			goto _st0;
		}
		_ctr66:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 1386 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1392 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 1398 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1404 "gen/ragel/25__cat4_4.c"
		
		goto _st35;
		_st35:
		p+= 1;
		if ( p == pe )
			goto _test_eof35;
		st_case_35:
		if ( ( (*( p))) == 97 ) {
			goto _ctr68;
		}
		{
			goto _st0;
		}
		_ctr68:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1423 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1429 "gen/ragel/25__cat4_4.c"
		
		goto _st36;
		_st36:
		p+= 1;
		if ( p == pe )
			goto _test_eof36;
		st_case_36:
		if ( ( (*( p))) == 97 ) {
			goto _ctr70;
		}
		{
			goto _st0;
		}
		_ctr70:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1448 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1454 "gen/ragel/25__cat4_4.c"
		
		goto _st37;
		_st37:
		p+= 1;
		if ( p == pe )
			goto _test_eof37;
		st_case_37:
		if ( ( (*( p))) == 97 ) {
			goto _ctr72;
		}
		{
			goto _st0;
		}
		_ctr72:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1473 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1479 "gen/ragel/25__cat4_4.c"
		
		goto _st38;
		_ctr96:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1487 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 1493 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1499 "gen/ragel/25__cat4_4.c"
		
		goto _st38;
		_st38:
		p+= 1;
		if ( p == pe )
			goto _test_eof38;
		st_case_38:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr74;
			}
			case 98: {
				goto _st42;
			}
		}
		{
			goto _st0;
		}
		_ctr74:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1523 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 1529 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1535 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 1541 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 1547 "gen/ragel/25__cat4_4.c"
		
		goto _st39;
		_st39:
		p+= 1;
		if ( p == pe )
			goto _test_eof39;
		st_case_39:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr77;
			}
			case 98: {
				goto _st42;
			}
		}
		{
			goto _st0;
		}
		_ctr77:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1571 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 1577 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1583 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 1589 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 1595 "gen/ragel/25__cat4_4.c"
		
		goto _st40;
		_st40:
		p+= 1;
		if ( p == pe )
			goto _test_eof40;
		st_case_40:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr79;
			}
			case 98: {
				goto _st42;
			}
		}
		{
			goto _st0;
		}
		_ctr79:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1619 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 1625 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1631 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 1637 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 1643 "gen/ragel/25__cat4_4.c"
		
		goto _st41;
		_st41:
		p+= 1;
		if ( p == pe )
			goto _test_eof41;
		st_case_41:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr45;
			}
			case 98: {
				goto _st42;
			}
		}
		{
			goto _st0;
		}
		_st42:
		p+= 1;
		if ( p == pe )
			goto _test_eof42;
		st_case_42:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr47;
			}
			case 98: {
				goto _st42;
			}
		}
		{
			goto _st0;
		}
		_st43:
		p+= 1;
		if ( p == pe )
			goto _test_eof43;
		st_case_43:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr81;
			}
			case 98: {
				goto _st43;
			}
		}
		{
			goto _st0;
		}
		_ctr81:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a1 = p; }
		
#line 1699 "gen/ragel/25__cat4_4.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1705 "gen/ragel/25__cat4_4.c"
		
		goto _st44;
		_st44:
		p+= 1;
		if ( p == pe )
			goto _test_eof44;
		st_case_44:
		if ( ( (*( p))) == 97 ) {
			goto _ctr83;
		}
		{
			goto _st0;
		}
		_ctr83:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1724 "gen/ragel/25__cat4_4.c"
		
		goto _st45;
		_st45:
		p+= 1;
		if ( p == pe )
			goto _test_eof45;
		st_case_45:
		if ( ( (*( p))) == 97 ) {
			goto _ctr85;
		}
		{
			goto _st0;
		}
		_ctr85:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1743 "gen/ragel/25__cat4_4.c"
		
		goto _st46;
		_st46:
		p+= 1;
		if ( p == pe )
			goto _test_eof46;
		st_case_46:
		if ( ( (*( p))) == 97 ) {
			goto _ctr87;
		}
		{
			goto _st0;
		}
		_ctr87:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1762 "gen/ragel/25__cat4_4.c"
		
		goto _st47;
		_st47:
		p+= 1;
		if ( p == pe )
			goto _test_eof47;
		st_case_47:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr89;
			}
			case 98: {
				goto _st51;
			}
		}
		{
			goto _st0;
		}
		_ctr89:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1786 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 1792 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1798 "gen/ragel/25__cat4_4.c"
		
		goto _st48;
		_st48:
		p+= 1;
		if ( p == pe )
			goto _test_eof48;
		st_case_48:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr92;
			}
			case 98: {
				goto _st51;
			}
		}
		{
			goto _st0;
		}
		_ctr92:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1822 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 1828 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1834 "gen/ragel/25__cat4_4.c"
		
		goto _st49;
		_st49:
		p+= 1;
		if ( p == pe )
			goto _test_eof49;
		st_case_49:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr94;
			}
			case 98: {
				goto _st51;
			}
		}
		{
			goto _st0;
		}
		_ctr94:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b1 = p; }
		
#line 1858 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 1864 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1870 "gen/ragel/25__cat4_4.c"
		
		goto _st50;
		_st50:
		p+= 1;
		if ( p == pe )
			goto _test_eof50;
		st_case_50:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr96;
			}
			case 98: {
				goto _st51;
			}
		}
		{
			goto _st0;
		}
		_st51:
		p+= 1;
		if ( p == pe )
			goto _test_eof51;
		st_case_51:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr97;
			}
			case 98: {
				goto _st51;
			}
		}
		{
			goto _st0;
		}
		_ctr97:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a2 = p; }
		
#line 1910 "gen/ragel/25__cat4_4.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1916 "gen/ragel/25__cat4_4.c"
		
		goto _st52;
		_st52:
		p+= 1;
		if ( p == pe )
			goto _test_eof52;
		st_case_52:
		if ( ( (*( p))) == 97 ) {
			goto _ctr99;
		}
		{
			goto _st0;
		}
		_ctr99:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1935 "gen/ragel/25__cat4_4.c"
		
		goto _st53;
		_st53:
		p+= 1;
		if ( p == pe )
			goto _test_eof53;
		st_case_53:
		if ( ( (*( p))) == 97 ) {
			goto _ctr101;
		}
		{
			goto _st0;
		}
		_ctr101:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1954 "gen/ragel/25__cat4_4.c"
		
		goto _st54;
		_st54:
		p+= 1;
		if ( p == pe )
			goto _test_eof54;
		st_case_54:
		if ( ( (*( p))) == 97 ) {
			goto _ctr103;
		}
		{
			goto _st0;
		}
		_ctr103:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1973 "gen/ragel/25__cat4_4.c"
		
		goto _st55;
		_st55:
		p+= 1;
		if ( p == pe )
			goto _test_eof55;
		st_case_55:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr105;
			}
			case 98: {
				goto _st59;
			}
		}
		{
			goto _st0;
		}
		_ctr105:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 1997 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 2003 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 2009 "gen/ragel/25__cat4_4.c"
		
		goto _st56;
		_st56:
		p+= 1;
		if ( p == pe )
			goto _test_eof56;
		st_case_56:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr108;
			}
			case 98: {
				goto _st59;
			}
		}
		{
			goto _st0;
		}
		_ctr108:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 2033 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 2039 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 2045 "gen/ragel/25__cat4_4.c"
		
		goto _st57;
		_st57:
		p+= 1;
		if ( p == pe )
			goto _test_eof57;
		st_case_57:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr110;
			}
			case 98: {
				goto _st59;
			}
		}
		{
			goto _st0;
		}
		_ctr110:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b2 = p; }
		
#line 2069 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			a3 = p; }
		
#line 2075 "gen/ragel/25__cat4_4.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
			b3 = p; }
		
#line 2081 "gen/ragel/25__cat4_4.c"
		
		goto _st58;
		_st58:
		p+= 1;
		if ( p == pe )
			goto _test_eof58;
		st_case_58:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr55;
			}
			case 98: {
				goto _st59;
			}
		}
		{
			goto _st0;
		}
		_st59:
		p+= 1;
		if ( p == pe )
			goto _test_eof59;
		st_case_59:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr57;
			}
			case 98: {
				goto _st59;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof60: cs = 60; goto _test_eof; 
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
		_test_eof47: cs = 47; goto _test_eof; 
		_test_eof48: cs = 48; goto _test_eof; 
		_test_eof49: cs = 49; goto _test_eof; 
		_test_eof50: cs = 50; goto _test_eof; 
		_test_eof51: cs = 51; goto _test_eof; 
		_test_eof52: cs = 52; goto _test_eof; 
		_test_eof53: cs = 53; goto _test_eof; 
		_test_eof54: cs = 54; goto _test_eof; 
		_test_eof55: cs = 55; goto _test_eof; 
		_test_eof56: cs = 56; goto _test_eof; 
		_test_eof57: cs = 57; goto _test_eof; 
		_test_eof58: cs = 58; goto _test_eof; 
		_test_eof59: cs = 59; goto _test_eof; 
		
		_test_eof: {}
		if ( cs >= 60 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/25__cat4_4.rl"
	
	
	in->p = p;
	in->pe = pe;
}
