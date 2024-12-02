#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"



#line 12 "gen/ragel/27__cat8_1.c"
static const int abcd_start = 73;
static const int abcd_first_final = 73;
static const int abcd_error = 0;

static const int abcd_en_main = 73;


#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
	*b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
	int cs;
	
	
#line 33 "gen/ragel/27__cat8_1.c"
	{
		cs = (int)abcd_start;
	}
	
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
	
	
#line 41 "gen/ragel/27__cat8_1.c"
	{
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
		_ctr23:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 207 "gen/ragel/27__cat8_1.c"
		
		goto _st73;
		_st73:
		p+= 1;
		st_case_73:
		if ( p == pe )
			goto _out73;
		if ( ( (*( p))) == 97 ) {
			goto _ctr132;
		}
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr132:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a0 = p; }
		
#line 227 "gen/ragel/27__cat8_1.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b0 = p; }
		
#line 233 "gen/ragel/27__cat8_1.c"
		
		goto _st1;
		_st1:
		p+= 1;
		st_case_1:
		if ( p == pe )
			goto _out1;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr2;
			}
			case 98: {
				goto _st60;
			}
		}
		goto _st0;
		_ctr2:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b0 = p; }
		
#line 255 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a1 = p; }
		
#line 261 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 267 "gen/ragel/27__cat8_1.c"
		
		goto _st2;
		_st2:
		p+= 1;
		st_case_2:
		if ( p == pe )
			goto _out2;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr5;
			}
			case 98: {
				goto _st49;
			}
		}
		goto _st0;
		_ctr5:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b0 = p; }
		
#line 289 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a1 = p; }
		
#line 295 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 301 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 307 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 313 "gen/ragel/27__cat8_1.c"
		
		goto _st3;
		_st3:
		p+= 1;
		st_case_3:
		if ( p == pe )
			goto _out3;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr8;
			}
			case 98: {
				goto _st40;
			}
		}
		goto _st0;
		_ctr8:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b0 = p; }
		
#line 335 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a1 = p; }
		
#line 341 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 347 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 353 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 359 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 365 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 371 "gen/ragel/27__cat8_1.c"
		
		goto _st4;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr11;
			}
			case 98: {
				goto _st33;
			}
		}
		goto _st0;
		_ctr11:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b0 = p; }
		
#line 393 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a1 = p; }
		
#line 399 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 405 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 411 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 417 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 423 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 429 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 435 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 441 "gen/ragel/27__cat8_1.c"
		
		goto _st5;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr14;
			}
			case 98: {
				goto _st28;
			}
		}
		goto _st0;
		_ctr14:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b0 = p; }
		
#line 463 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a1 = p; }
		
#line 469 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 475 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 481 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 487 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 493 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 499 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 505 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 511 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 517 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 523 "gen/ragel/27__cat8_1.c"
		
		goto _st6;
		_st6:
		p+= 1;
		st_case_6:
		if ( p == pe )
			goto _out6;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr17;
			}
			case 98: {
				goto _st25;
			}
		}
		goto _st0;
		_ctr17:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b0 = p; }
		
#line 545 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a1 = p; }
		
#line 551 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 557 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 563 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 569 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 575 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 581 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 587 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 593 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 599 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 605 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 611 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 617 "gen/ragel/27__cat8_1.c"
		
		goto _st7;
		_st7:
		p+= 1;
		st_case_7:
		if ( p == pe )
			goto _out7;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr20;
			}
			case 98: {
				goto _st24;
			}
		}
		goto _st0;
		_ctr20:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b0 = p; }
		
#line 639 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a1 = p; }
		
#line 645 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 651 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 657 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 663 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 669 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 675 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 681 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 687 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 693 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 699 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 705 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 711 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a7 = p; }
		
#line 717 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 723 "gen/ragel/27__cat8_1.c"
		
		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
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
		goto _st0;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
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
		goto _st0;
		_ctr25:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a1 = p; }
		
#line 765 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 771 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 777 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 783 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 789 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 795 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 801 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 807 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 813 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 819 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 825 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 831 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a7 = p; }
		
#line 837 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 843 "gen/ragel/27__cat8_1.c"
		
		goto _st10;
		_ctr27:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 851 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 857 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 863 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 869 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 875 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 881 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 887 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 893 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 899 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 905 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 911 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a7 = p; }
		
#line 917 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 923 "gen/ragel/27__cat8_1.c"
		
		goto _st10;
		_st10:
		p+= 1;
		st_case_10:
		if ( p == pe )
			goto _out10;
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
		goto _st0;
		_st11:
		p+= 1;
		st_case_11:
		if ( p == pe )
			goto _out11;
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
		goto _st0;
		_ctr29:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 965 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 971 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 977 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 983 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 989 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 995 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 1001 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 1007 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 1013 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 1019 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a7 = p; }
		
#line 1025 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 1031 "gen/ragel/27__cat8_1.c"
		
		goto _st12;
		_ctr31:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 1039 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 1045 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 1051 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 1057 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 1063 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 1069 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 1075 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 1081 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 1087 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a7 = p; }
		
#line 1093 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 1099 "gen/ragel/27__cat8_1.c"
		
		goto _st12;
		_st12:
		p+= 1;
		st_case_12:
		if ( p == pe )
			goto _out12;
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
		goto _st0;
		_st13:
		p+= 1;
		st_case_13:
		if ( p == pe )
			goto _out13;
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
		goto _st0;
		_ctr33:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 1141 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 1147 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 1153 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 1159 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 1165 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 1171 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 1177 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 1183 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a7 = p; }
		
#line 1189 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 1195 "gen/ragel/27__cat8_1.c"
		
		goto _st14;
		_ctr35:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 1203 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 1209 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 1215 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 1221 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 1227 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 1233 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 1239 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a7 = p; }
		
#line 1245 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 1251 "gen/ragel/27__cat8_1.c"
		
		goto _st14;
		_st14:
		p+= 1;
		st_case_14:
		if ( p == pe )
			goto _out14;
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
		goto _st0;
		_st15:
		p+= 1;
		st_case_15:
		if ( p == pe )
			goto _out15;
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
		goto _st0;
		_ctr37:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 1293 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 1299 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 1305 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 1311 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 1317 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 1323 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a7 = p; }
		
#line 1329 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 1335 "gen/ragel/27__cat8_1.c"
		
		goto _st16;
		_ctr39:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 1343 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 1349 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 1355 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 1361 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 1367 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a7 = p; }
		
#line 1373 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 1379 "gen/ragel/27__cat8_1.c"
		
		goto _st16;
		_st16:
		p+= 1;
		st_case_16:
		if ( p == pe )
			goto _out16;
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
		goto _st0;
		_st17:
		p+= 1;
		st_case_17:
		if ( p == pe )
			goto _out17;
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
		goto _st0;
		_ctr41:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 1421 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 1427 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 1433 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 1439 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a7 = p; }
		
#line 1445 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 1451 "gen/ragel/27__cat8_1.c"
		
		goto _st18;
		_ctr43:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 1459 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 1465 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 1471 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a7 = p; }
		
#line 1477 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 1483 "gen/ragel/27__cat8_1.c"
		
		goto _st18;
		_st18:
		p+= 1;
		st_case_18:
		if ( p == pe )
			goto _out18;
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
		goto _st0;
		_st19:
		p+= 1;
		st_case_19:
		if ( p == pe )
			goto _out19;
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
		goto _st0;
		_ctr45:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 1525 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 1531 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a7 = p; }
		
#line 1537 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 1543 "gen/ragel/27__cat8_1.c"
		
		goto _st20;
		_ctr47:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 1551 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a7 = p; }
		
#line 1557 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 1563 "gen/ragel/27__cat8_1.c"
		
		goto _st20;
		_st20:
		p+= 1;
		st_case_20:
		if ( p == pe )
			goto _out20;
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
		goto _st0;
		_st21:
		p+= 1;
		st_case_21:
		if ( p == pe )
			goto _out21;
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
		goto _st0;
		_ctr49:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a7 = p; }
		
#line 1605 "gen/ragel/27__cat8_1.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 1611 "gen/ragel/27__cat8_1.c"
		
		goto _st22;
		_ctr51:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b7 = p; }
		
#line 1619 "gen/ragel/27__cat8_1.c"
		
		goto _st22;
		_st22:
		p+= 1;
		st_case_22:
		if ( p == pe )
			goto _out22;
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
		goto _st0;
		_st23:
		p+= 1;
		st_case_23:
		if ( p == pe )
			goto _out23;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr23;
			}
			case 98: {
				goto _st23;
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
				goto _ctr25;
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
				goto _ctr53;
			}
			case 98: {
				goto _st25;
			}
		}
		goto _st0;
		_ctr53:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a1 = p; }
		
#line 1686 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 1692 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 1698 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 1704 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 1710 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 1716 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 1722 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 1728 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 1734 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 1740 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 1746 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 1752 "gen/ragel/27__cat8_1.c"
		
		goto _st26;
		_ctr58:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 1760 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 1766 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 1772 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 1778 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 1784 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 1790 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 1796 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 1802 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 1808 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 1814 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 1820 "gen/ragel/27__cat8_1.c"
		
		goto _st26;
		_st26:
		p+= 1;
		st_case_26:
		if ( p == pe )
			goto _out26;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr27;
			}
			case 98: {
				goto _st27;
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
				goto _ctr29;
			}
			case 98: {
				goto _st27;
			}
		}
		goto _st0;
		_st28:
		p+= 1;
		st_case_28:
		if ( p == pe )
			goto _out28;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr56;
			}
			case 98: {
				goto _st28;
			}
		}
		goto _st0;
		_ctr56:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a1 = p; }
		
#line 1870 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 1876 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 1882 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 1888 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 1894 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 1900 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 1906 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 1912 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 1918 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 1924 "gen/ragel/27__cat8_1.c"
		
		goto _st29;
		_ctr65:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 1932 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 1938 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 1944 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 1950 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 1956 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 1962 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 1968 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 1974 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 1980 "gen/ragel/27__cat8_1.c"
		
		goto _st29;
		_st29:
		p+= 1;
		st_case_29:
		if ( p == pe )
			goto _out29;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr58;
			}
			case 98: {
				goto _st30;
			}
		}
		goto _st0;
		_st30:
		p+= 1;
		st_case_30:
		if ( p == pe )
			goto _out30;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr60;
			}
			case 98: {
				goto _st30;
			}
		}
		goto _st0;
		_ctr60:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 2016 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 2022 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 2028 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 2034 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 2040 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 2046 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 2052 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 2058 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 2064 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 2070 "gen/ragel/27__cat8_1.c"
		
		goto _st31;
		_ctr69:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 2078 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 2084 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 2090 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 2096 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 2102 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 2108 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 2114 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 2120 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 2126 "gen/ragel/27__cat8_1.c"
		
		goto _st31;
		_st31:
		p+= 1;
		st_case_31:
		if ( p == pe )
			goto _out31;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr31;
			}
			case 98: {
				goto _st32;
			}
		}
		goto _st0;
		_st32:
		p+= 1;
		st_case_32:
		if ( p == pe )
			goto _out32;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr33;
			}
			case 98: {
				goto _st32;
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
				goto _ctr63;
			}
			case 98: {
				goto _st33;
			}
		}
		goto _st0;
		_ctr63:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a1 = p; }
		
#line 2176 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 2182 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 2188 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 2194 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 2200 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 2206 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 2212 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 2218 "gen/ragel/27__cat8_1.c"
		
		goto _st34;
		_ctr76:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 2226 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 2232 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 2238 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 2244 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 2250 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 2256 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 2262 "gen/ragel/27__cat8_1.c"
		
		goto _st34;
		_st34:
		p+= 1;
		st_case_34:
		if ( p == pe )
			goto _out34;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr65;
			}
			case 98: {
				goto _st35;
			}
		}
		goto _st0;
		_st35:
		p+= 1;
		st_case_35:
		if ( p == pe )
			goto _out35;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr67;
			}
			case 98: {
				goto _st35;
			}
		}
		goto _st0;
		_ctr67:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 2298 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 2304 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 2310 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 2316 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 2322 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 2328 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 2334 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 2340 "gen/ragel/27__cat8_1.c"
		
		goto _st36;
		_ctr80:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 2348 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 2354 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 2360 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 2366 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 2372 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 2378 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 2384 "gen/ragel/27__cat8_1.c"
		
		goto _st36;
		_st36:
		p+= 1;
		st_case_36:
		if ( p == pe )
			goto _out36;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr69;
			}
			case 98: {
				goto _st37;
			}
		}
		goto _st0;
		_st37:
		p+= 1;
		st_case_37:
		if ( p == pe )
			goto _out37;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr71;
			}
			case 98: {
				goto _st37;
			}
		}
		goto _st0;
		_ctr71:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 2420 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 2426 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 2432 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 2438 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 2444 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 2450 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 2456 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 2462 "gen/ragel/27__cat8_1.c"
		
		goto _st38;
		_ctr84:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 2470 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 2476 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 2482 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 2488 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 2494 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 2500 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 2506 "gen/ragel/27__cat8_1.c"
		
		goto _st38;
		_st38:
		p+= 1;
		st_case_38:
		if ( p == pe )
			goto _out38;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr35;
			}
			case 98: {
				goto _st39;
			}
		}
		goto _st0;
		_st39:
		p+= 1;
		st_case_39:
		if ( p == pe )
			goto _out39;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr37;
			}
			case 98: {
				goto _st39;
			}
		}
		goto _st0;
		_st40:
		p+= 1;
		st_case_40:
		if ( p == pe )
			goto _out40;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr74;
			}
			case 98: {
				goto _st40;
			}
		}
		goto _st0;
		_ctr74:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a1 = p; }
		
#line 2556 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 2562 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 2568 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 2574 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 2580 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 2586 "gen/ragel/27__cat8_1.c"
		
		goto _st41;
		_ctr91:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 2594 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 2600 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 2606 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 2612 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 2618 "gen/ragel/27__cat8_1.c"
		
		goto _st41;
		_st41:
		p+= 1;
		st_case_41:
		if ( p == pe )
			goto _out41;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr76;
			}
			case 98: {
				goto _st42;
			}
		}
		goto _st0;
		_st42:
		p+= 1;
		st_case_42:
		if ( p == pe )
			goto _out42;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr78;
			}
			case 98: {
				goto _st42;
			}
		}
		goto _st0;
		_ctr78:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 2654 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 2660 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 2666 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 2672 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 2678 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 2684 "gen/ragel/27__cat8_1.c"
		
		goto _st43;
		_ctr95:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 2692 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 2698 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 2704 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 2710 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 2716 "gen/ragel/27__cat8_1.c"
		
		goto _st43;
		_st43:
		p+= 1;
		st_case_43:
		if ( p == pe )
			goto _out43;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr80;
			}
			case 98: {
				goto _st44;
			}
		}
		goto _st0;
		_st44:
		p+= 1;
		st_case_44:
		if ( p == pe )
			goto _out44;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr82;
			}
			case 98: {
				goto _st44;
			}
		}
		goto _st0;
		_ctr82:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 2752 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 2758 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 2764 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 2770 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 2776 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 2782 "gen/ragel/27__cat8_1.c"
		
		goto _st45;
		_ctr99:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 2790 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 2796 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 2802 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 2808 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 2814 "gen/ragel/27__cat8_1.c"
		
		goto _st45;
		_st45:
		p+= 1;
		st_case_45:
		if ( p == pe )
			goto _out45;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr84;
			}
			case 98: {
				goto _st46;
			}
		}
		goto _st0;
		_st46:
		p+= 1;
		st_case_46:
		if ( p == pe )
			goto _out46;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr86;
			}
			case 98: {
				goto _st46;
			}
		}
		goto _st0;
		_ctr86:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 2850 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 2856 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 2862 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 2868 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 2874 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 2880 "gen/ragel/27__cat8_1.c"
		
		goto _st47;
		_ctr103:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 2888 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 2894 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 2900 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 2906 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 2912 "gen/ragel/27__cat8_1.c"
		
		goto _st47;
		_st47:
		p+= 1;
		st_case_47:
		if ( p == pe )
			goto _out47;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr39;
			}
			case 98: {
				goto _st48;
			}
		}
		goto _st0;
		_st48:
		p+= 1;
		st_case_48:
		if ( p == pe )
			goto _out48;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr41;
			}
			case 98: {
				goto _st48;
			}
		}
		goto _st0;
		_st49:
		p+= 1;
		st_case_49:
		if ( p == pe )
			goto _out49;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr89;
			}
			case 98: {
				goto _st49;
			}
		}
		goto _st0;
		_ctr89:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a1 = p; }
		
#line 2962 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 2968 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 2974 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 2980 "gen/ragel/27__cat8_1.c"
		
		goto _st50;
		_ctr110:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 2988 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 2994 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 3000 "gen/ragel/27__cat8_1.c"
		
		goto _st50;
		_st50:
		p+= 1;
		st_case_50:
		if ( p == pe )
			goto _out50;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr91;
			}
			case 98: {
				goto _st51;
			}
		}
		goto _st0;
		_st51:
		p+= 1;
		st_case_51:
		if ( p == pe )
			goto _out51;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr93;
			}
			case 98: {
				goto _st51;
			}
		}
		goto _st0;
		_ctr93:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 3036 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 3042 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 3048 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 3054 "gen/ragel/27__cat8_1.c"
		
		goto _st52;
		_ctr114:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 3062 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 3068 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 3074 "gen/ragel/27__cat8_1.c"
		
		goto _st52;
		_st52:
		p+= 1;
		st_case_52:
		if ( p == pe )
			goto _out52;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr95;
			}
			case 98: {
				goto _st53;
			}
		}
		goto _st0;
		_st53:
		p+= 1;
		st_case_53:
		if ( p == pe )
			goto _out53;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr97;
			}
			case 98: {
				goto _st53;
			}
		}
		goto _st0;
		_ctr97:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 3110 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 3116 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 3122 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 3128 "gen/ragel/27__cat8_1.c"
		
		goto _st54;
		_ctr118:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 3136 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 3142 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 3148 "gen/ragel/27__cat8_1.c"
		
		goto _st54;
		_st54:
		p+= 1;
		st_case_54:
		if ( p == pe )
			goto _out54;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr99;
			}
			case 98: {
				goto _st55;
			}
		}
		goto _st0;
		_st55:
		p+= 1;
		st_case_55:
		if ( p == pe )
			goto _out55;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr101;
			}
			case 98: {
				goto _st55;
			}
		}
		goto _st0;
		_ctr101:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 3184 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 3190 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 3196 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 3202 "gen/ragel/27__cat8_1.c"
		
		goto _st56;
		_ctr122:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 3210 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 3216 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 3222 "gen/ragel/27__cat8_1.c"
		
		goto _st56;
		_st56:
		p+= 1;
		st_case_56:
		if ( p == pe )
			goto _out56;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr103;
			}
			case 98: {
				goto _st57;
			}
		}
		goto _st0;
		_st57:
		p+= 1;
		st_case_57:
		if ( p == pe )
			goto _out57;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr105;
			}
			case 98: {
				goto _st57;
			}
		}
		goto _st0;
		_ctr105:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 3258 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 3264 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 3270 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 3276 "gen/ragel/27__cat8_1.c"
		
		goto _st58;
		_ctr126:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 3284 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 3290 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 3296 "gen/ragel/27__cat8_1.c"
		
		goto _st58;
		_st58:
		p+= 1;
		st_case_58:
		if ( p == pe )
			goto _out58;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr43;
			}
			case 98: {
				goto _st59;
			}
		}
		goto _st0;
		_st59:
		p+= 1;
		st_case_59:
		if ( p == pe )
			goto _out59;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr45;
			}
			case 98: {
				goto _st59;
			}
		}
		goto _st0;
		_st60:
		p+= 1;
		st_case_60:
		if ( p == pe )
			goto _out60;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr108;
			}
			case 98: {
				goto _st60;
			}
		}
		goto _st0;
		_ctr108:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a1 = p; }
		
#line 3346 "gen/ragel/27__cat8_1.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b1 = p; }
		
#line 3352 "gen/ragel/27__cat8_1.c"
		
		goto _st61;
		_st61:
		p+= 1;
		st_case_61:
		if ( p == pe )
			goto _out61;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr110;
			}
			case 98: {
				goto _st62;
			}
		}
		goto _st0;
		_st62:
		p+= 1;
		st_case_62:
		if ( p == pe )
			goto _out62;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr112;
			}
			case 98: {
				goto _st62;
			}
		}
		goto _st0;
		_ctr112:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a2 = p; }
		
#line 3388 "gen/ragel/27__cat8_1.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b2 = p; }
		
#line 3394 "gen/ragel/27__cat8_1.c"
		
		goto _st63;
		_st63:
		p+= 1;
		st_case_63:
		if ( p == pe )
			goto _out63;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr114;
			}
			case 98: {
				goto _st64;
			}
		}
		goto _st0;
		_st64:
		p+= 1;
		st_case_64:
		if ( p == pe )
			goto _out64;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr116;
			}
			case 98: {
				goto _st64;
			}
		}
		goto _st0;
		_ctr116:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a3 = p; }
		
#line 3430 "gen/ragel/27__cat8_1.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b3 = p; }
		
#line 3436 "gen/ragel/27__cat8_1.c"
		
		goto _st65;
		_st65:
		p+= 1;
		st_case_65:
		if ( p == pe )
			goto _out65;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr118;
			}
			case 98: {
				goto _st66;
			}
		}
		goto _st0;
		_st66:
		p+= 1;
		st_case_66:
		if ( p == pe )
			goto _out66;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr120;
			}
			case 98: {
				goto _st66;
			}
		}
		goto _st0;
		_ctr120:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a4 = p; }
		
#line 3472 "gen/ragel/27__cat8_1.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b4 = p; }
		
#line 3478 "gen/ragel/27__cat8_1.c"
		
		goto _st67;
		_st67:
		p+= 1;
		st_case_67:
		if ( p == pe )
			goto _out67;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr122;
			}
			case 98: {
				goto _st68;
			}
		}
		goto _st0;
		_st68:
		p+= 1;
		st_case_68:
		if ( p == pe )
			goto _out68;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr124;
			}
			case 98: {
				goto _st68;
			}
		}
		goto _st0;
		_ctr124:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a5 = p; }
		
#line 3514 "gen/ragel/27__cat8_1.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b5 = p; }
		
#line 3520 "gen/ragel/27__cat8_1.c"
		
		goto _st69;
		_st69:
		p+= 1;
		st_case_69:
		if ( p == pe )
			goto _out69;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr126;
			}
			case 98: {
				goto _st70;
			}
		}
		goto _st0;
		_st70:
		p+= 1;
		st_case_70:
		if ( p == pe )
			goto _out70;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr128;
			}
			case 98: {
				goto _st70;
			}
		}
		goto _st0;
		_ctr128:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			a6 = p; }
		
#line 3556 "gen/ragel/27__cat8_1.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
			b6 = p; }
		
#line 3562 "gen/ragel/27__cat8_1.c"
		
		goto _st71;
		_st71:
		p+= 1;
		st_case_71:
		if ( p == pe )
			goto _out71;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr47;
			}
			case 98: {
				goto _st72;
			}
		}
		goto _st0;
		_st72:
		p+= 1;
		st_case_72:
		if ( p == pe )
			goto _out72;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr49;
			}
			case 98: {
				goto _st72;
			}
		}
		goto _st0;
		_out73: cs = 73; goto _out; 
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
		_out47: cs = 47; goto _out; 
		_out48: cs = 48; goto _out; 
		_out49: cs = 49; goto _out; 
		_out50: cs = 50; goto _out; 
		_out51: cs = 51; goto _out; 
		_out52: cs = 52; goto _out; 
		_out53: cs = 53; goto _out; 
		_out54: cs = 54; goto _out; 
		_out55: cs = 55; goto _out; 
		_out56: cs = 56; goto _out; 
		_out57: cs = 57; goto _out; 
		_out58: cs = 58; goto _out; 
		_out59: cs = 59; goto _out; 
		_out60: cs = 60; goto _out; 
		_out61: cs = 61; goto _out; 
		_out62: cs = 62; goto _out; 
		_out63: cs = 63; goto _out; 
		_out64: cs = 64; goto _out; 
		_out65: cs = 65; goto _out; 
		_out66: cs = 66; goto _out; 
		_out67: cs = 67; goto _out; 
		_out68: cs = 68; goto _out; 
		_out69: cs = 69; goto _out; 
		_out70: cs = 70; goto _out; 
		_out71: cs = 71; goto _out; 
		_out72: cs = 72; goto _out; 
		_out: {}
	}
	
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/27__cat8_1.rl"
	
	
	in->p = p;
	in->pe = pe;
}
