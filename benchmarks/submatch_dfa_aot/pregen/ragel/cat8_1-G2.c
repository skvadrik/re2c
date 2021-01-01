#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"



#line 12 "gen/ragel/cat8_1-G2.c"
static const int abcd_start = 73;
static const int abcd_first_final = 73;
static const int abcd_error = 0;

static const int abcd_en_main = 73;


#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
	*b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
	int cs;
	
	
#line 33 "gen/ragel/cat8_1-G2.c"
	{
		cs = (int)abcd_start;
	}
	
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
	
	
#line 41 "gen/ragel/cat8_1-G2.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 73:
			goto st_case_73;
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
			case 60:
			goto st_case_60;
			case 61:
			goto st_case_61;
			case 62:
			goto st_case_62;
			case 63:
			goto st_case_63;
			case 64:
			goto st_case_64;
			case 65:
			goto st_case_65;
			case 66:
			goto st_case_66;
			case 67:
			goto st_case_67;
			case 68:
			goto st_case_68;
			case 69:
			goto st_case_69;
			case 70:
			goto st_case_70;
			case 71:
			goto st_case_71;
			case 72:
			goto st_case_72;
		}
		goto st_out;
		_ctr23:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 210 "gen/ragel/cat8_1-G2.c"
		
		goto _st73;
		_st73:
		p+= 1;
		if ( p == pe )
			goto _test_eof73;
		st_case_73:
		if ( ( (*( p))) == 97 ) {
			goto _ctr132;
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr132:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a0 = p; }
		
#line 233 "gen/ragel/cat8_1-G2.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b0 = p; }
		
#line 239 "gen/ragel/cat8_1-G2.c"
		
		goto _st1;
		_st1:
		p+= 1;
		if ( p == pe )
			goto _test_eof1;
		st_case_1:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr2;
			}
			case 98: {
				goto _st60;
			}
		}
		{
			goto _st0;
		}
		_ctr2:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b0 = p; }
		
#line 263 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a1 = p; }
		
#line 269 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 275 "gen/ragel/cat8_1-G2.c"
		
		goto _st2;
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr5;
			}
			case 98: {
				goto _st49;
			}
		}
		{
			goto _st0;
		}
		_ctr5:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b0 = p; }
		
#line 299 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a1 = p; }
		
#line 305 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 311 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 317 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 323 "gen/ragel/cat8_1-G2.c"
		
		goto _st3;
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr8;
			}
			case 98: {
				goto _st40;
			}
		}
		{
			goto _st0;
		}
		_ctr8:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b0 = p; }
		
#line 347 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a1 = p; }
		
#line 353 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 359 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 365 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 371 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 377 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 383 "gen/ragel/cat8_1-G2.c"
		
		goto _st4;
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr11;
			}
			case 98: {
				goto _st33;
			}
		}
		{
			goto _st0;
		}
		_ctr11:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b0 = p; }
		
#line 407 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a1 = p; }
		
#line 413 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 419 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 425 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 431 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 437 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 443 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 449 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 455 "gen/ragel/cat8_1-G2.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr14;
			}
			case 98: {
				goto _st28;
			}
		}
		{
			goto _st0;
		}
		_ctr14:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b0 = p; }
		
#line 479 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a1 = p; }
		
#line 485 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 491 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 497 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 503 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 509 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 515 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 521 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 527 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 533 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 539 "gen/ragel/cat8_1-G2.c"
		
		goto _st6;
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr17;
			}
			case 98: {
				goto _st25;
			}
		}
		{
			goto _st0;
		}
		_ctr17:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b0 = p; }
		
#line 563 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a1 = p; }
		
#line 569 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 575 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 581 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 587 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 593 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 599 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 605 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 611 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 617 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 623 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 629 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 635 "gen/ragel/cat8_1-G2.c"
		
		goto _st7;
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr20;
			}
			case 98: {
				goto _st24;
			}
		}
		{
			goto _st0;
		}
		_ctr20:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b0 = p; }
		
#line 659 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a1 = p; }
		
#line 665 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 671 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 677 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 683 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 689 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 695 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 701 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 707 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 713 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 719 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 725 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 731 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a7 = p; }
		
#line 737 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 743 "gen/ragel/cat8_1-G2.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 97: {
				goto _ctr20;
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
				goto _ctr23;
			}
			case 97: {
				goto _ctr25;
			}
			case 98: {
				goto _st9;
			}
		}
		{
			goto _st0;
		}
		_ctr25:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a1 = p; }
		
#line 789 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 795 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 801 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 807 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 813 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 819 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 825 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 831 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 837 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 843 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 849 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 855 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a7 = p; }
		
#line 861 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 867 "gen/ragel/cat8_1-G2.c"
		
		goto _st10;
		_ctr27:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 875 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 881 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 887 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 893 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 899 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 905 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 911 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 917 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 923 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 929 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 935 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a7 = p; }
		
#line 941 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 947 "gen/ragel/cat8_1-G2.c"
		
		goto _st10;
		_st10:
		p+= 1;
		if ( p == pe )
			goto _test_eof10;
		st_case_10:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 97: {
				goto _ctr27;
			}
			case 98: {
				goto _st11;
			}
		}
		{
			goto _st0;
		}
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 97: {
				goto _ctr29;
			}
			case 98: {
				goto _st11;
			}
		}
		{
			goto _st0;
		}
		_ctr29:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 993 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 999 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 1005 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 1011 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 1017 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 1023 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 1029 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 1035 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 1041 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 1047 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a7 = p; }
		
#line 1053 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 1059 "gen/ragel/cat8_1-G2.c"
		
		goto _st12;
		_ctr31:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 1067 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 1073 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 1079 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 1085 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 1091 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 1097 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 1103 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 1109 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 1115 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a7 = p; }
		
#line 1121 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 1127 "gen/ragel/cat8_1-G2.c"
		
		goto _st12;
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 97: {
				goto _ctr31;
			}
			case 98: {
				goto _st13;
			}
		}
		{
			goto _st0;
		}
		_st13:
		p+= 1;
		if ( p == pe )
			goto _test_eof13;
		st_case_13:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 97: {
				goto _ctr33;
			}
			case 98: {
				goto _st13;
			}
		}
		{
			goto _st0;
		}
		_ctr33:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 1173 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 1179 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 1185 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 1191 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 1197 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 1203 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 1209 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 1215 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a7 = p; }
		
#line 1221 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 1227 "gen/ragel/cat8_1-G2.c"
		
		goto _st14;
		_ctr35:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 1235 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 1241 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 1247 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 1253 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 1259 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 1265 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 1271 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a7 = p; }
		
#line 1277 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 1283 "gen/ragel/cat8_1-G2.c"
		
		goto _st14;
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 97: {
				goto _ctr35;
			}
			case 98: {
				goto _st15;
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
			case 10: {
				goto _ctr23;
			}
			case 97: {
				goto _ctr37;
			}
			case 98: {
				goto _st15;
			}
		}
		{
			goto _st0;
		}
		_ctr37:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 1329 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 1335 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 1341 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 1347 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 1353 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 1359 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a7 = p; }
		
#line 1365 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 1371 "gen/ragel/cat8_1-G2.c"
		
		goto _st16;
		_ctr39:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 1379 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 1385 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 1391 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 1397 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 1403 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a7 = p; }
		
#line 1409 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 1415 "gen/ragel/cat8_1-G2.c"
		
		goto _st16;
		_st16:
		p+= 1;
		if ( p == pe )
			goto _test_eof16;
		st_case_16:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 97: {
				goto _ctr39;
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
				goto _ctr23;
			}
			case 97: {
				goto _ctr41;
			}
			case 98: {
				goto _st17;
			}
		}
		{
			goto _st0;
		}
		_ctr41:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 1461 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 1467 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 1473 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 1479 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a7 = p; }
		
#line 1485 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 1491 "gen/ragel/cat8_1-G2.c"
		
		goto _st18;
		_ctr43:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 1499 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 1505 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 1511 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a7 = p; }
		
#line 1517 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 1523 "gen/ragel/cat8_1-G2.c"
		
		goto _st18;
		_st18:
		p+= 1;
		if ( p == pe )
			goto _test_eof18;
		st_case_18:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 97: {
				goto _ctr43;
			}
			case 98: {
				goto _st19;
			}
		}
		{
			goto _st0;
		}
		_st19:
		p+= 1;
		if ( p == pe )
			goto _test_eof19;
		st_case_19:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 97: {
				goto _ctr45;
			}
			case 98: {
				goto _st19;
			}
		}
		{
			goto _st0;
		}
		_ctr45:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 1569 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 1575 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a7 = p; }
		
#line 1581 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 1587 "gen/ragel/cat8_1-G2.c"
		
		goto _st20;
		_ctr47:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 1595 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a7 = p; }
		
#line 1601 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 1607 "gen/ragel/cat8_1-G2.c"
		
		goto _st20;
		_st20:
		p+= 1;
		if ( p == pe )
			goto _test_eof20;
		st_case_20:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 97: {
				goto _ctr47;
			}
			case 98: {
				goto _st21;
			}
		}
		{
			goto _st0;
		}
		_st21:
		p+= 1;
		if ( p == pe )
			goto _test_eof21;
		st_case_21:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 97: {
				goto _ctr49;
			}
			case 98: {
				goto _st21;
			}
		}
		{
			goto _st0;
		}
		_ctr49:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a7 = p; }
		
#line 1653 "gen/ragel/cat8_1-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 1659 "gen/ragel/cat8_1-G2.c"
		
		goto _st22;
		_ctr51:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b7 = p; }
		
#line 1667 "gen/ragel/cat8_1-G2.c"
		
		goto _st22;
		_st22:
		p+= 1;
		if ( p == pe )
			goto _test_eof22;
		st_case_22:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 97: {
				goto _ctr51;
			}
			case 98: {
				goto _st23;
			}
		}
		{
			goto _st0;
		}
		_st23:
		p+= 1;
		if ( p == pe )
			goto _test_eof23;
		st_case_23:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 98: {
				goto _st23;
			}
		}
		{
			goto _st0;
		}
		_st24:
		p+= 1;
		if ( p == pe )
			goto _test_eof24;
		st_case_24:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr25;
			}
			case 98: {
				goto _st24;
			}
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
			case 97: {
				goto _ctr53;
			}
			case 98: {
				goto _st25;
			}
		}
		{
			goto _st0;
		}
		_ctr53:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a1 = p; }
		
#line 1742 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 1748 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 1754 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 1760 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 1766 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 1772 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 1778 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 1784 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 1790 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 1796 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 1802 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 1808 "gen/ragel/cat8_1-G2.c"
		
		goto _st26;
		_ctr58:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 1816 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 1822 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 1828 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 1834 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 1840 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 1846 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 1852 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 1858 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 1864 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 1870 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 1876 "gen/ragel/cat8_1-G2.c"
		
		goto _st26;
		_st26:
		p+= 1;
		if ( p == pe )
			goto _test_eof26;
		st_case_26:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr27;
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
			case 97: {
				goto _ctr29;
			}
			case 98: {
				goto _st27;
			}
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
			case 97: {
				goto _ctr56;
			}
			case 98: {
				goto _st28;
			}
		}
		{
			goto _st0;
		}
		_ctr56:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a1 = p; }
		
#line 1932 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 1938 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 1944 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 1950 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 1956 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 1962 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 1968 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 1974 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 1980 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 1986 "gen/ragel/cat8_1-G2.c"
		
		goto _st29;
		_ctr65:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 1994 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 2000 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 2006 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 2012 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2018 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 2024 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2030 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 2036 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 2042 "gen/ragel/cat8_1-G2.c"
		
		goto _st29;
		_st29:
		p+= 1;
		if ( p == pe )
			goto _test_eof29;
		st_case_29:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr58;
			}
			case 98: {
				goto _st30;
			}
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
			case 97: {
				goto _ctr60;
			}
			case 98: {
				goto _st30;
			}
		}
		{
			goto _st0;
		}
		_ctr60:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 2082 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 2088 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 2094 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2100 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 2106 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2112 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 2118 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 2124 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 2130 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 2136 "gen/ragel/cat8_1-G2.c"
		
		goto _st31;
		_ctr69:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 2144 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 2150 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2156 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 2162 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2168 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 2174 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 2180 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 2186 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 2192 "gen/ragel/cat8_1-G2.c"
		
		goto _st31;
		_st31:
		p+= 1;
		if ( p == pe )
			goto _test_eof31;
		st_case_31:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr31;
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
			case 97: {
				goto _ctr33;
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
				goto _ctr63;
			}
			case 98: {
				goto _st33;
			}
		}
		{
			goto _st0;
		}
		_ctr63:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a1 = p; }
		
#line 2248 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 2254 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 2260 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 2266 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 2272 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2278 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 2284 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2290 "gen/ragel/cat8_1-G2.c"
		
		goto _st34;
		_ctr76:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 2298 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 2304 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 2310 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 2316 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2322 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 2328 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2334 "gen/ragel/cat8_1-G2.c"
		
		goto _st34;
		_st34:
		p+= 1;
		if ( p == pe )
			goto _test_eof34;
		st_case_34:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr65;
			}
			case 98: {
				goto _st35;
			}
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
			case 97: {
				goto _ctr67;
			}
			case 98: {
				goto _st35;
			}
		}
		{
			goto _st0;
		}
		_ctr67:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 2374 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 2380 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 2386 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2392 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 2398 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2404 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 2410 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 2416 "gen/ragel/cat8_1-G2.c"
		
		goto _st36;
		_ctr80:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 2424 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 2430 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2436 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 2442 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2448 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 2454 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 2460 "gen/ragel/cat8_1-G2.c"
		
		goto _st36;
		_st36:
		p+= 1;
		if ( p == pe )
			goto _test_eof36;
		st_case_36:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr69;
			}
			case 98: {
				goto _st37;
			}
		}
		{
			goto _st0;
		}
		_st37:
		p+= 1;
		if ( p == pe )
			goto _test_eof37;
		st_case_37:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr71;
			}
			case 98: {
				goto _st37;
			}
		}
		{
			goto _st0;
		}
		_ctr71:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 2500 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2506 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 2512 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2518 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 2524 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 2530 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 2536 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 2542 "gen/ragel/cat8_1-G2.c"
		
		goto _st38;
		_ctr84:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2550 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 2556 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2562 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 2568 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 2574 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 2580 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 2586 "gen/ragel/cat8_1-G2.c"
		
		goto _st38;
		_st38:
		p+= 1;
		if ( p == pe )
			goto _test_eof38;
		st_case_38:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr35;
			}
			case 98: {
				goto _st39;
			}
		}
		{
			goto _st0;
		}
		_st39:
		p+= 1;
		if ( p == pe )
			goto _test_eof39;
		st_case_39:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr37;
			}
			case 98: {
				goto _st39;
			}
		}
		{
			goto _st0;
		}
		_st40:
		p+= 1;
		if ( p == pe )
			goto _test_eof40;
		st_case_40:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr74;
			}
			case 98: {
				goto _st40;
			}
		}
		{
			goto _st0;
		}
		_ctr74:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a1 = p; }
		
#line 2642 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 2648 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 2654 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 2660 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 2666 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2672 "gen/ragel/cat8_1-G2.c"
		
		goto _st41;
		_ctr91:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 2680 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 2686 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 2692 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 2698 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2704 "gen/ragel/cat8_1-G2.c"
		
		goto _st41;
		_st41:
		p+= 1;
		if ( p == pe )
			goto _test_eof41;
		st_case_41:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr76;
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
				goto _ctr78;
			}
			case 98: {
				goto _st42;
			}
		}
		{
			goto _st0;
		}
		_ctr78:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 2744 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 2750 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 2756 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2762 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 2768 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2774 "gen/ragel/cat8_1-G2.c"
		
		goto _st43;
		_ctr95:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 2782 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 2788 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2794 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 2800 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2806 "gen/ragel/cat8_1-G2.c"
		
		goto _st43;
		_st43:
		p+= 1;
		if ( p == pe )
			goto _test_eof43;
		st_case_43:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr80;
			}
			case 98: {
				goto _st44;
			}
		}
		{
			goto _st0;
		}
		_st44:
		p+= 1;
		if ( p == pe )
			goto _test_eof44;
		st_case_44:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr82;
			}
			case 98: {
				goto _st44;
			}
		}
		{
			goto _st0;
		}
		_ctr82:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 2846 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2852 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 2858 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2864 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 2870 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 2876 "gen/ragel/cat8_1-G2.c"
		
		goto _st45;
		_ctr99:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 2884 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 2890 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2896 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 2902 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 2908 "gen/ragel/cat8_1-G2.c"
		
		goto _st45;
		_st45:
		p+= 1;
		if ( p == pe )
			goto _test_eof45;
		st_case_45:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr84;
			}
			case 98: {
				goto _st46;
			}
		}
		{
			goto _st0;
		}
		_st46:
		p+= 1;
		if ( p == pe )
			goto _test_eof46;
		st_case_46:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr86;
			}
			case 98: {
				goto _st46;
			}
		}
		{
			goto _st0;
		}
		_ctr86:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 2948 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2954 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 2960 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 2966 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 2972 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 2978 "gen/ragel/cat8_1-G2.c"
		
		goto _st47;
		_ctr103:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 2986 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 2992 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 2998 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 3004 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 3010 "gen/ragel/cat8_1-G2.c"
		
		goto _st47;
		_st47:
		p+= 1;
		if ( p == pe )
			goto _test_eof47;
		st_case_47:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr39;
			}
			case 98: {
				goto _st48;
			}
		}
		{
			goto _st0;
		}
		_st48:
		p+= 1;
		if ( p == pe )
			goto _test_eof48;
		st_case_48:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr41;
			}
			case 98: {
				goto _st48;
			}
		}
		{
			goto _st0;
		}
		_st49:
		p+= 1;
		if ( p == pe )
			goto _test_eof49;
		st_case_49:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr89;
			}
			case 98: {
				goto _st49;
			}
		}
		{
			goto _st0;
		}
		_ctr89:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a1 = p; }
		
#line 3066 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 3072 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 3078 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 3084 "gen/ragel/cat8_1-G2.c"
		
		goto _st50;
		_ctr110:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 3092 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 3098 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 3104 "gen/ragel/cat8_1-G2.c"
		
		goto _st50;
		_st50:
		p+= 1;
		if ( p == pe )
			goto _test_eof50;
		st_case_50:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr91;
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
				goto _ctr93;
			}
			case 98: {
				goto _st51;
			}
		}
		{
			goto _st0;
		}
		_ctr93:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 3144 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 3150 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 3156 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 3162 "gen/ragel/cat8_1-G2.c"
		
		goto _st52;
		_ctr114:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 3170 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 3176 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 3182 "gen/ragel/cat8_1-G2.c"
		
		goto _st52;
		_st52:
		p+= 1;
		if ( p == pe )
			goto _test_eof52;
		st_case_52:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr95;
			}
			case 98: {
				goto _st53;
			}
		}
		{
			goto _st0;
		}
		_st53:
		p+= 1;
		if ( p == pe )
			goto _test_eof53;
		st_case_53:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr97;
			}
			case 98: {
				goto _st53;
			}
		}
		{
			goto _st0;
		}
		_ctr97:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 3222 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 3228 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 3234 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 3240 "gen/ragel/cat8_1-G2.c"
		
		goto _st54;
		_ctr118:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 3248 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 3254 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 3260 "gen/ragel/cat8_1-G2.c"
		
		goto _st54;
		_st54:
		p+= 1;
		if ( p == pe )
			goto _test_eof54;
		st_case_54:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr99;
			}
			case 98: {
				goto _st55;
			}
		}
		{
			goto _st0;
		}
		_st55:
		p+= 1;
		if ( p == pe )
			goto _test_eof55;
		st_case_55:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr101;
			}
			case 98: {
				goto _st55;
			}
		}
		{
			goto _st0;
		}
		_ctr101:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 3300 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 3306 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 3312 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 3318 "gen/ragel/cat8_1-G2.c"
		
		goto _st56;
		_ctr122:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 3326 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 3332 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 3338 "gen/ragel/cat8_1-G2.c"
		
		goto _st56;
		_st56:
		p+= 1;
		if ( p == pe )
			goto _test_eof56;
		st_case_56:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr103;
			}
			case 98: {
				goto _st57;
			}
		}
		{
			goto _st0;
		}
		_st57:
		p+= 1;
		if ( p == pe )
			goto _test_eof57;
		st_case_57:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr105;
			}
			case 98: {
				goto _st57;
			}
		}
		{
			goto _st0;
		}
		_ctr105:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 3378 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 3384 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 3390 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 3396 "gen/ragel/cat8_1-G2.c"
		
		goto _st58;
		_ctr126:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 3404 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 3410 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 3416 "gen/ragel/cat8_1-G2.c"
		
		goto _st58;
		_st58:
		p+= 1;
		if ( p == pe )
			goto _test_eof58;
		st_case_58:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr43;
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
				goto _ctr45;
			}
			case 98: {
				goto _st59;
			}
		}
		{
			goto _st0;
		}
		_st60:
		p+= 1;
		if ( p == pe )
			goto _test_eof60;
		st_case_60:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr108;
			}
			case 98: {
				goto _st60;
			}
		}
		{
			goto _st0;
		}
		_ctr108:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a1 = p; }
		
#line 3472 "gen/ragel/cat8_1-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b1 = p; }
		
#line 3478 "gen/ragel/cat8_1-G2.c"
		
		goto _st61;
		_st61:
		p+= 1;
		if ( p == pe )
			goto _test_eof61;
		st_case_61:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr110;
			}
			case 98: {
				goto _st62;
			}
		}
		{
			goto _st0;
		}
		_st62:
		p+= 1;
		if ( p == pe )
			goto _test_eof62;
		st_case_62:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr112;
			}
			case 98: {
				goto _st62;
			}
		}
		{
			goto _st0;
		}
		_ctr112:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a2 = p; }
		
#line 3518 "gen/ragel/cat8_1-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b2 = p; }
		
#line 3524 "gen/ragel/cat8_1-G2.c"
		
		goto _st63;
		_st63:
		p+= 1;
		if ( p == pe )
			goto _test_eof63;
		st_case_63:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr114;
			}
			case 98: {
				goto _st64;
			}
		}
		{
			goto _st0;
		}
		_st64:
		p+= 1;
		if ( p == pe )
			goto _test_eof64;
		st_case_64:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr116;
			}
			case 98: {
				goto _st64;
			}
		}
		{
			goto _st0;
		}
		_ctr116:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a3 = p; }
		
#line 3564 "gen/ragel/cat8_1-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b3 = p; }
		
#line 3570 "gen/ragel/cat8_1-G2.c"
		
		goto _st65;
		_st65:
		p+= 1;
		if ( p == pe )
			goto _test_eof65;
		st_case_65:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr118;
			}
			case 98: {
				goto _st66;
			}
		}
		{
			goto _st0;
		}
		_st66:
		p+= 1;
		if ( p == pe )
			goto _test_eof66;
		st_case_66:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr120;
			}
			case 98: {
				goto _st66;
			}
		}
		{
			goto _st0;
		}
		_ctr120:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a4 = p; }
		
#line 3610 "gen/ragel/cat8_1-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b4 = p; }
		
#line 3616 "gen/ragel/cat8_1-G2.c"
		
		goto _st67;
		_st67:
		p+= 1;
		if ( p == pe )
			goto _test_eof67;
		st_case_67:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr122;
			}
			case 98: {
				goto _st68;
			}
		}
		{
			goto _st0;
		}
		_st68:
		p+= 1;
		if ( p == pe )
			goto _test_eof68;
		st_case_68:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr124;
			}
			case 98: {
				goto _st68;
			}
		}
		{
			goto _st0;
		}
		_ctr124:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a5 = p; }
		
#line 3656 "gen/ragel/cat8_1-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b5 = p; }
		
#line 3662 "gen/ragel/cat8_1-G2.c"
		
		goto _st69;
		_st69:
		p+= 1;
		if ( p == pe )
			goto _test_eof69;
		st_case_69:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr126;
			}
			case 98: {
				goto _st70;
			}
		}
		{
			goto _st0;
		}
		_st70:
		p+= 1;
		if ( p == pe )
			goto _test_eof70;
		st_case_70:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr128;
			}
			case 98: {
				goto _st70;
			}
		}
		{
			goto _st0;
		}
		_ctr128:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			a6 = p; }
		
#line 3702 "gen/ragel/cat8_1-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
			b6 = p; }
		
#line 3708 "gen/ragel/cat8_1-G2.c"
		
		goto _st71;
		_st71:
		p+= 1;
		if ( p == pe )
			goto _test_eof71;
		st_case_71:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr47;
			}
			case 98: {
				goto _st72;
			}
		}
		{
			goto _st0;
		}
		_st72:
		p+= 1;
		if ( p == pe )
			goto _test_eof72;
		st_case_72:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr49;
			}
			case 98: {
				goto _st72;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof73: cs = 73; goto _test_eof; 
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
		_test_eof60: cs = 60; goto _test_eof; 
		_test_eof61: cs = 61; goto _test_eof; 
		_test_eof62: cs = 62; goto _test_eof; 
		_test_eof63: cs = 63; goto _test_eof; 
		_test_eof64: cs = 64; goto _test_eof; 
		_test_eof65: cs = 65; goto _test_eof; 
		_test_eof66: cs = 66; goto _test_eof; 
		_test_eof67: cs = 67; goto _test_eof; 
		_test_eof68: cs = 68; goto _test_eof; 
		_test_eof69: cs = 69; goto _test_eof; 
		_test_eof70: cs = 70; goto _test_eof; 
		_test_eof71: cs = 71; goto _test_eof; 
		_test_eof72: cs = 72; goto _test_eof; 
		
		_test_eof: {}
		if ( cs >= 73 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_1.rl"
	
	
	in->p = p;
	in->pe = pe;
}
