#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"



#line 12 "gen/ragel/cat8_2-G2.c"
static const int abcd_start = 130;
static const int abcd_first_final = 130;
static const int abcd_error = 0;

static const int abcd_en_main = 130;


#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
	*b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
	int cs;
	
	
#line 33 "gen/ragel/cat8_2-G2.c"
	{
		cs = (int)abcd_start;
	}
	
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
	
	
#line 41 "gen/ragel/cat8_2-G2.c"
	{
		if ( p == pe )
			goto _test_eof;
		switch ( cs ) {
			case 130:
			goto st_case_130;
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
			case 73:
			goto st_case_73;
			case 74:
			goto st_case_74;
			case 75:
			goto st_case_75;
			case 76:
			goto st_case_76;
			case 77:
			goto st_case_77;
			case 78:
			goto st_case_78;
			case 79:
			goto st_case_79;
			case 80:
			goto st_case_80;
			case 81:
			goto st_case_81;
			case 82:
			goto st_case_82;
			case 83:
			goto st_case_83;
			case 84:
			goto st_case_84;
			case 85:
			goto st_case_85;
			case 86:
			goto st_case_86;
			case 87:
			goto st_case_87;
			case 88:
			goto st_case_88;
			case 89:
			goto st_case_89;
			case 90:
			goto st_case_90;
			case 91:
			goto st_case_91;
			case 92:
			goto st_case_92;
			case 93:
			goto st_case_93;
			case 94:
			goto st_case_94;
			case 95:
			goto st_case_95;
			case 96:
			goto st_case_96;
			case 97:
			goto st_case_97;
			case 98:
			goto st_case_98;
			case 99:
			goto st_case_99;
			case 100:
			goto st_case_100;
			case 101:
			goto st_case_101;
			case 102:
			goto st_case_102;
			case 103:
			goto st_case_103;
			case 104:
			goto st_case_104;
			case 105:
			goto st_case_105;
			case 106:
			goto st_case_106;
			case 107:
			goto st_case_107;
			case 108:
			goto st_case_108;
			case 109:
			goto st_case_109;
			case 110:
			goto st_case_110;
			case 111:
			goto st_case_111;
			case 112:
			goto st_case_112;
			case 113:
			goto st_case_113;
			case 114:
			goto st_case_114;
			case 115:
			goto st_case_115;
			case 116:
			goto st_case_116;
			case 117:
			goto st_case_117;
			case 118:
			goto st_case_118;
			case 119:
			goto st_case_119;
			case 120:
			goto st_case_120;
			case 121:
			goto st_case_121;
			case 122:
			goto st_case_122;
			case 123:
			goto st_case_123;
			case 124:
			goto st_case_124;
			case 125:
			goto st_case_125;
			case 126:
			goto st_case_126;
			case 127:
			goto st_case_127;
			case 128:
			goto st_case_128;
			case 129:
			goto st_case_129;
		}
		goto st_out;
		_ctr39:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 324 "gen/ragel/cat8_2-G2.c"
		
		goto _st130;
		_st130:
		p+= 1;
		if ( p == pe )
			goto _test_eof130;
		st_case_130:
		if ( ( (*( p))) == 97 ) {
			goto _ctr245;
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr245:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a0 = p; }
		
#line 347 "gen/ragel/cat8_2-G2.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 353 "gen/ragel/cat8_2-G2.c"
		
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 372 "gen/ragel/cat8_2-G2.c"
		
		goto _st2;
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr4;
			}
			case 98: {
				goto _st105;
			}
		}
		{
			goto _st0;
		}
		_ctr4:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 396 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 402 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 408 "gen/ragel/cat8_2-G2.c"
		
		goto _st3;
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr7;
			}
			case 98: {
				goto _st105;
			}
		}
		{
			goto _st0;
		}
		_ctr7:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 432 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 438 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 444 "gen/ragel/cat8_2-G2.c"
		
		goto _st4;
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr9;
			}
			case 98: {
				goto _st84;
			}
		}
		{
			goto _st0;
		}
		_ctr9:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 468 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 474 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 480 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 486 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 492 "gen/ragel/cat8_2-G2.c"
		
		goto _st5;
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr12;
			}
			case 98: {
				goto _st84;
			}
		}
		{
			goto _st0;
		}
		_ctr12:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 516 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 522 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 528 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 534 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 540 "gen/ragel/cat8_2-G2.c"
		
		goto _st6;
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr14;
			}
			case 98: {
				goto _st67;
			}
		}
		{
			goto _st0;
		}
		_ctr14:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 564 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 570 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 576 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 582 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 588 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 594 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 600 "gen/ragel/cat8_2-G2.c"
		
		goto _st7;
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr17;
			}
			case 98: {
				goto _st67;
			}
		}
		{
			goto _st0;
		}
		_ctr17:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 624 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 630 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 636 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 642 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 648 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 654 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 660 "gen/ragel/cat8_2-G2.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr19;
			}
			case 98: {
				goto _st54;
			}
		}
		{
			goto _st0;
		}
		_ctr19:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 684 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 690 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 696 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 702 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 708 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 714 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 720 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 726 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 732 "gen/ragel/cat8_2-G2.c"
		
		goto _st9;
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr22;
			}
			case 98: {
				goto _st54;
			}
		}
		{
			goto _st0;
		}
		_ctr22:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 756 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 762 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 768 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 774 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 780 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 786 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 792 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 798 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 804 "gen/ragel/cat8_2-G2.c"
		
		goto _st10;
		_st10:
		p+= 1;
		if ( p == pe )
			goto _test_eof10;
		st_case_10:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr24;
			}
			case 98: {
				goto _st45;
			}
		}
		{
			goto _st0;
		}
		_ctr24:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 828 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 834 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 840 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 846 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 852 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 858 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 864 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 870 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 876 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 882 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 888 "gen/ragel/cat8_2-G2.c"
		
		goto _st11;
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr27;
			}
			case 98: {
				goto _st45;
			}
		}
		{
			goto _st0;
		}
		_ctr27:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 912 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 918 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 924 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 930 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 936 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 942 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 948 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 954 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 960 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 966 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 972 "gen/ragel/cat8_2-G2.c"
		
		goto _st12;
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr29;
			}
			case 98: {
				goto _st40;
			}
		}
		{
			goto _st0;
		}
		_ctr29:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 996 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 1002 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 1008 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 1014 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 1020 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 1026 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 1032 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 1038 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 1044 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 1050 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 1056 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 1062 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 1068 "gen/ragel/cat8_2-G2.c"
		
		goto _st13;
		_st13:
		p+= 1;
		if ( p == pe )
			goto _test_eof13;
		st_case_13:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr32;
			}
			case 98: {
				goto _st40;
			}
		}
		{
			goto _st0;
		}
		_ctr32:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 1092 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 1098 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 1104 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 1110 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 1116 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 1122 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 1128 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 1134 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 1140 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 1146 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 1152 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 1158 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 1164 "gen/ragel/cat8_2-G2.c"
		
		goto _st14;
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr34;
			}
			case 98: {
				goto _st39;
			}
		}
		{
			goto _st0;
		}
		_ctr34:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 1188 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 1194 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 1200 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 1206 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 1212 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 1218 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 1224 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 1230 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 1236 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 1242 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 1248 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 1254 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 1260 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 1266 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 1272 "gen/ragel/cat8_2-G2.c"
		
		goto _st15;
		_st15:
		p+= 1;
		if ( p == pe )
			goto _test_eof15;
		st_case_15:
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
		_ctr37:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b0 = p; }
		
#line 1296 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 1302 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 1308 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 1314 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 1320 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 1326 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 1332 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 1338 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 1344 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 1350 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 1356 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 1362 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 1368 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 1374 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 1380 "gen/ragel/cat8_2-G2.c"
		
		goto _st16;
		_st16:
		p+= 1;
		if ( p == pe )
			goto _test_eof16;
		st_case_16:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
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
		_st17:
		p+= 1;
		if ( p == pe )
			goto _test_eof17;
		st_case_17:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
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
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 1426 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 1432 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 1438 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 1444 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 1450 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 1456 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 1462 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 1468 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 1474 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 1480 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 1486 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 1492 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 1498 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 1504 "gen/ragel/cat8_2-G2.c"
		
		goto _st18;
		_st18:
		p+= 1;
		if ( p == pe )
			goto _test_eof18;
		st_case_18:
		if ( ( (*( p))) == 97 ) {
			goto _ctr43;
		}
		{
			goto _st0;
		}
		_ctr43:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 1523 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 1529 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 1535 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 1541 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 1547 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 1553 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 1559 "gen/ragel/cat8_2-G2.c"
		
		goto _st19;
		_ctr45:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 1567 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 1573 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 1579 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 1585 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 1591 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 1597 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 1603 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 1609 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 1615 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 1621 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 1627 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 1633 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 1639 "gen/ragel/cat8_2-G2.c"
		
		goto _st19;
		_st19:
		p+= 1;
		if ( p == pe )
			goto _test_eof19;
		st_case_19:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
			}
			case 97: {
				goto _ctr45;
			}
			case 98: {
				goto _st20;
			}
		}
		{
			goto _st0;
		}
		_st20:
		p+= 1;
		if ( p == pe )
			goto _test_eof20;
		st_case_20:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
			}
			case 97: {
				goto _ctr47;
			}
			case 98: {
				goto _st20;
			}
		}
		{
			goto _st0;
		}
		_ctr47:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 1685 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 1691 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 1697 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 1703 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 1709 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 1715 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 1721 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 1727 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 1733 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 1739 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 1745 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 1751 "gen/ragel/cat8_2-G2.c"
		
		goto _st21;
		_st21:
		p+= 1;
		if ( p == pe )
			goto _test_eof21;
		st_case_21:
		if ( ( (*( p))) == 97 ) {
			goto _ctr49;
		}
		{
			goto _st0;
		}
		_ctr49:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 1770 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 1776 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 1782 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 1788 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 1794 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 1800 "gen/ragel/cat8_2-G2.c"
		
		goto _st22;
		_ctr51:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 1808 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 1814 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 1820 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 1826 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 1832 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 1838 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 1844 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 1850 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 1856 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 1862 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 1868 "gen/ragel/cat8_2-G2.c"
		
		goto _st22;
		_st22:
		p+= 1;
		if ( p == pe )
			goto _test_eof22;
		st_case_22:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
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
				goto _ctr39;
			}
			case 97: {
				goto _ctr53;
			}
			case 98: {
				goto _st23;
			}
		}
		{
			goto _st0;
		}
		_ctr53:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 1914 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 1920 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 1926 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 1932 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 1938 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 1944 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 1950 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 1956 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 1962 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 1968 "gen/ragel/cat8_2-G2.c"
		
		goto _st24;
		_st24:
		p+= 1;
		if ( p == pe )
			goto _test_eof24;
		st_case_24:
		if ( ( (*( p))) == 97 ) {
			goto _ctr55;
		}
		{
			goto _st0;
		}
		_ctr55:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 1987 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 1993 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 1999 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2005 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 2011 "gen/ragel/cat8_2-G2.c"
		
		goto _st25;
		_ctr57:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 2019 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 2025 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 2031 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 2037 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 2043 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 2049 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2055 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 2061 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 2067 "gen/ragel/cat8_2-G2.c"
		
		goto _st25;
		_st25:
		p+= 1;
		if ( p == pe )
			goto _test_eof25;
		st_case_25:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
			}
			case 97: {
				goto _ctr57;
			}
			case 98: {
				goto _st26;
			}
		}
		{
			goto _st0;
		}
		_st26:
		p+= 1;
		if ( p == pe )
			goto _test_eof26;
		st_case_26:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
			}
			case 97: {
				goto _ctr59;
			}
			case 98: {
				goto _st26;
			}
		}
		{
			goto _st0;
		}
		_ctr59:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 2113 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 2119 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 2125 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 2131 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 2137 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2143 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 2149 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 2155 "gen/ragel/cat8_2-G2.c"
		
		goto _st27;
		_st27:
		p+= 1;
		if ( p == pe )
			goto _test_eof27;
		st_case_27:
		if ( ( (*( p))) == 97 ) {
			goto _ctr61;
		}
		{
			goto _st0;
		}
		_ctr61:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 2174 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 2180 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2186 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 2192 "gen/ragel/cat8_2-G2.c"
		
		goto _st28;
		_ctr63:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 2200 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 2206 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 2212 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 2218 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2224 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 2230 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 2236 "gen/ragel/cat8_2-G2.c"
		
		goto _st28;
		_st28:
		p+= 1;
		if ( p == pe )
			goto _test_eof28;
		st_case_28:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
			}
			case 97: {
				goto _ctr63;
			}
			case 98: {
				goto _st29;
			}
		}
		{
			goto _st0;
		}
		_st29:
		p+= 1;
		if ( p == pe )
			goto _test_eof29;
		st_case_29:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
			}
			case 97: {
				goto _ctr65;
			}
			case 98: {
				goto _st29;
			}
		}
		{
			goto _st0;
		}
		_ctr65:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 2282 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 2288 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 2294 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2300 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 2306 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 2312 "gen/ragel/cat8_2-G2.c"
		
		goto _st30;
		_st30:
		p+= 1;
		if ( p == pe )
			goto _test_eof30;
		st_case_30:
		if ( ( (*( p))) == 97 ) {
			goto _ctr67;
		}
		{
			goto _st0;
		}
		_ctr67:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 2331 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2337 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 2343 "gen/ragel/cat8_2-G2.c"
		
		goto _st31;
		_ctr69:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 2351 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 2357 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2363 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 2369 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 2375 "gen/ragel/cat8_2-G2.c"
		
		goto _st31;
		_st31:
		p+= 1;
		if ( p == pe )
			goto _test_eof31;
		st_case_31:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
			}
			case 97: {
				goto _ctr69;
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
				goto _ctr39;
			}
			case 97: {
				goto _ctr71;
			}
			case 98: {
				goto _st32;
			}
		}
		{
			goto _st0;
		}
		_ctr71:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 2421 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2427 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 2433 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 2439 "gen/ragel/cat8_2-G2.c"
		
		goto _st33;
		_st33:
		p+= 1;
		if ( p == pe )
			goto _test_eof33;
		st_case_33:
		if ( ( (*( p))) == 97 ) {
			goto _ctr73;
		}
		{
			goto _st0;
		}
		_ctr73:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2458 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 2464 "gen/ragel/cat8_2-G2.c"
		
		goto _st34;
		_ctr75:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2472 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 2478 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 2484 "gen/ragel/cat8_2-G2.c"
		
		goto _st34;
		_st34:
		p+= 1;
		if ( p == pe )
			goto _test_eof34;
		st_case_34:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
			}
			case 97: {
				goto _ctr75;
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
			case 10: {
				goto _ctr39;
			}
			case 97: {
				goto _ctr77;
			}
			case 98: {
				goto _st35;
			}
		}
		{
			goto _st0;
		}
		_ctr77:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 2530 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 2536 "gen/ragel/cat8_2-G2.c"
		
		goto _st36;
		_st36:
		p+= 1;
		if ( p == pe )
			goto _test_eof36;
		st_case_36:
		if ( ( (*( p))) == 97 ) {
			goto _ctr79;
		}
		{
			goto _st0;
		}
		_ctr79:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 2555 "gen/ragel/cat8_2-G2.c"
		
		goto _st37;
		_st37:
		p+= 1;
		if ( p == pe )
			goto _test_eof37;
		st_case_37:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
			}
			case 97: {
				goto _ctr79;
			}
			case 98: {
				goto _st38;
			}
		}
		{
			goto _st0;
		}
		_st38:
		p+= 1;
		if ( p == pe )
			goto _test_eof38;
		st_case_38:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
			}
			case 98: {
				goto _st38;
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
				goto _ctr41;
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
				goto _ctr82;
			}
			case 98: {
				goto _st40;
			}
		}
		{
			goto _st0;
		}
		_ctr82:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 2630 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 2636 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 2642 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 2648 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 2654 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 2660 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 2666 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 2672 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 2678 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 2684 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 2690 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2696 "gen/ragel/cat8_2-G2.c"
		
		goto _st41;
		_st41:
		p+= 1;
		if ( p == pe )
			goto _test_eof41;
		st_case_41:
		if ( ( (*( p))) == 97 ) {
			goto _ctr84;
		}
		{
			goto _st0;
		}
		_ctr84:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 2715 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 2721 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 2727 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 2733 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 2739 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2745 "gen/ragel/cat8_2-G2.c"
		
		goto _st42;
		_ctr96:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 2753 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 2759 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 2765 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 2771 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 2777 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 2783 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 2789 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 2795 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 2801 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 2807 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2813 "gen/ragel/cat8_2-G2.c"
		
		goto _st42;
		_st42:
		p+= 1;
		if ( p == pe )
			goto _test_eof42;
		st_case_42:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr86;
			}
			case 98: {
				goto _st44;
			}
		}
		{
			goto _st0;
		}
		_ctr86:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 2837 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 2843 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 2849 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 2855 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 2861 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 2867 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 2873 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 2879 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 2885 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 2891 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 2897 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 2903 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 2909 "gen/ragel/cat8_2-G2.c"
		
		goto _st43;
		_st43:
		p+= 1;
		if ( p == pe )
			goto _test_eof43;
		st_case_43:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr45;
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
				goto _ctr47;
			}
			case 98: {
				goto _st44;
			}
		}
		{
			goto _st0;
		}
		_st45:
		p+= 1;
		if ( p == pe )
			goto _test_eof45;
		st_case_45:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr89;
			}
			case 98: {
				goto _st45;
			}
		}
		{
			goto _st0;
		}
		_ctr89:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 2965 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 2971 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 2977 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 2983 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 2989 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 2995 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 3001 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3007 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 3013 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 3019 "gen/ragel/cat8_2-G2.c"
		
		goto _st46;
		_st46:
		p+= 1;
		if ( p == pe )
			goto _test_eof46;
		st_case_46:
		if ( ( (*( p))) == 97 ) {
			goto _ctr91;
		}
		{
			goto _st0;
		}
		_ctr91:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 3038 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3044 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3050 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3056 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 3062 "gen/ragel/cat8_2-G2.c"
		
		goto _st47;
		_ctr111:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 3070 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 3076 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3082 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 3088 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3094 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 3100 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3106 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 3112 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 3118 "gen/ragel/cat8_2-G2.c"
		
		goto _st47;
		_st47:
		p+= 1;
		if ( p == pe )
			goto _test_eof47;
		st_case_47:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr93;
			}
			case 98: {
				goto _st49;
			}
		}
		{
			goto _st0;
		}
		_ctr93:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 3142 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 3148 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3154 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 3160 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3166 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 3172 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3178 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 3184 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 3190 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 3196 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 3202 "gen/ragel/cat8_2-G2.c"
		
		goto _st48;
		_st48:
		p+= 1;
		if ( p == pe )
			goto _test_eof48;
		st_case_48:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr96;
			}
			case 98: {
				goto _st49;
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
				goto _ctr97;
			}
			case 98: {
				goto _st49;
			}
		}
		{
			goto _st0;
		}
		_ctr97:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 3242 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3248 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 3254 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3260 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 3266 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3272 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 3278 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 3284 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 3290 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 3296 "gen/ragel/cat8_2-G2.c"
		
		goto _st50;
		_st50:
		p+= 1;
		if ( p == pe )
			goto _test_eof50;
		st_case_50:
		if ( ( (*( p))) == 97 ) {
			goto _ctr99;
		}
		{
			goto _st0;
		}
		_ctr99:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3315 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3321 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3327 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 3333 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 3339 "gen/ragel/cat8_2-G2.c"
		
		goto _st51;
		_ctr119:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3347 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 3353 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3359 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 3365 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3371 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 3377 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 3383 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 3389 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 3395 "gen/ragel/cat8_2-G2.c"
		
		goto _st51;
		_st51:
		p+= 1;
		if ( p == pe )
			goto _test_eof51;
		st_case_51:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr101;
			}
			case 98: {
				goto _st53;
			}
		}
		{
			goto _st0;
		}
		_ctr101:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3419 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 3425 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3431 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 3437 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3443 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 3449 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 3455 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 3461 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 3467 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 3473 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 3479 "gen/ragel/cat8_2-G2.c"
		
		goto _st52;
		_st52:
		p+= 1;
		if ( p == pe )
			goto _test_eof52;
		st_case_52:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr51;
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
				goto _ctr53;
			}
			case 98: {
				goto _st53;
			}
		}
		{
			goto _st0;
		}
		_st54:
		p+= 1;
		if ( p == pe )
			goto _test_eof54;
		st_case_54:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr104;
			}
			case 98: {
				goto _st54;
			}
		}
		{
			goto _st0;
		}
		_ctr104:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 3535 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 3541 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 3547 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3553 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 3559 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3565 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 3571 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3577 "gen/ragel/cat8_2-G2.c"
		
		goto _st55;
		_st55:
		p+= 1;
		if ( p == pe )
			goto _test_eof55;
		st_case_55:
		if ( ( (*( p))) == 97 ) {
			goto _ctr106;
		}
		{
			goto _st0;
		}
		_ctr106:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 3596 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3602 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3608 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3614 "gen/ragel/cat8_2-G2.c"
		
		goto _st56;
		_ctr134:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 3622 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 3628 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3634 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 3640 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3646 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 3652 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3658 "gen/ragel/cat8_2-G2.c"
		
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
				goto _st58;
			}
		}
		{
			goto _st0;
		}
		_ctr108:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 3682 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 3688 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3694 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 3700 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3706 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 3712 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3718 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 3724 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 3730 "gen/ragel/cat8_2-G2.c"
		
		goto _st57;
		_st57:
		p+= 1;
		if ( p == pe )
			goto _test_eof57;
		st_case_57:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr111;
			}
			case 98: {
				goto _st58;
			}
		}
		{
			goto _st0;
		}
		_st58:
		p+= 1;
		if ( p == pe )
			goto _test_eof58;
		st_case_58:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr112;
			}
			case 98: {
				goto _st58;
			}
		}
		{
			goto _st0;
		}
		_ctr112:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 3770 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3776 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 3782 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3788 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 3794 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3800 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 3806 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 3812 "gen/ragel/cat8_2-G2.c"
		
		goto _st59;
		_st59:
		p+= 1;
		if ( p == pe )
			goto _test_eof59;
		st_case_59:
		if ( ( (*( p))) == 97 ) {
			goto _ctr114;
		}
		{
			goto _st0;
		}
		_ctr114:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3831 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3837 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3843 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 3849 "gen/ragel/cat8_2-G2.c"
		
		goto _st60;
		_ctr142:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3857 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 3863 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3869 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 3875 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3881 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 3887 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 3893 "gen/ragel/cat8_2-G2.c"
		
		goto _st60;
		_st60:
		p+= 1;
		if ( p == pe )
			goto _test_eof60;
		st_case_60:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr116;
			}
			case 98: {
				goto _st62;
			}
		}
		{
			goto _st0;
		}
		_ctr116:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 3917 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 3923 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 3929 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 3935 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 3941 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 3947 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 3953 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 3959 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 3965 "gen/ragel/cat8_2-G2.c"
		
		goto _st61;
		_st61:
		p+= 1;
		if ( p == pe )
			goto _test_eof61;
		st_case_61:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr119;
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
				goto _ctr120;
			}
			case 98: {
				goto _st62;
			}
		}
		{
			goto _st0;
		}
		_ctr120:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 4005 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4011 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 4017 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4023 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 4029 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 4035 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 4041 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 4047 "gen/ragel/cat8_2-G2.c"
		
		goto _st63;
		_st63:
		p+= 1;
		if ( p == pe )
			goto _test_eof63;
		st_case_63:
		if ( ( (*( p))) == 97 ) {
			goto _ctr122;
		}
		{
			goto _st0;
		}
		_ctr122:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4066 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4072 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 4078 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 4084 "gen/ragel/cat8_2-G2.c"
		
		goto _st64;
		_ctr150:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4092 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 4098 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4104 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 4110 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 4116 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 4122 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 4128 "gen/ragel/cat8_2-G2.c"
		
		goto _st64;
		_st64:
		p+= 1;
		if ( p == pe )
			goto _test_eof64;
		st_case_64:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr124;
			}
			case 98: {
				goto _st66;
			}
		}
		{
			goto _st0;
		}
		_ctr124:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4152 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 4158 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4164 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 4170 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 4176 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 4182 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 4188 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 4194 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 4200 "gen/ragel/cat8_2-G2.c"
		
		goto _st65;
		_st65:
		p+= 1;
		if ( p == pe )
			goto _test_eof65;
		st_case_65:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr57;
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
				goto _ctr59;
			}
			case 98: {
				goto _st66;
			}
		}
		{
			goto _st0;
		}
		_st67:
		p+= 1;
		if ( p == pe )
			goto _test_eof67;
		st_case_67:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr127;
			}
			case 98: {
				goto _st67;
			}
		}
		{
			goto _st0;
		}
		_ctr127:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 4256 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 4262 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 4268 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 4274 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 4280 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4286 "gen/ragel/cat8_2-G2.c"
		
		goto _st68;
		_st68:
		p+= 1;
		if ( p == pe )
			goto _test_eof68;
		st_case_68:
		if ( ( (*( p))) == 97 ) {
			goto _ctr129;
		}
		{
			goto _st0;
		}
		_ctr129:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 4305 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 4311 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4317 "gen/ragel/cat8_2-G2.c"
		
		goto _st69;
		_ctr165:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 4325 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 4331 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 4337 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 4343 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4349 "gen/ragel/cat8_2-G2.c"
		
		goto _st69;
		_st69:
		p+= 1;
		if ( p == pe )
			goto _test_eof69;
		st_case_69:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr131;
			}
			case 98: {
				goto _st71;
			}
		}
		{
			goto _st0;
		}
		_ctr131:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 4373 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 4379 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 4385 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 4391 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4397 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 4403 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4409 "gen/ragel/cat8_2-G2.c"
		
		goto _st70;
		_st70:
		p+= 1;
		if ( p == pe )
			goto _test_eof70;
		st_case_70:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr134;
			}
			case 98: {
				goto _st71;
			}
		}
		{
			goto _st0;
		}
		_st71:
		p+= 1;
		if ( p == pe )
			goto _test_eof71;
		st_case_71:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr135;
			}
			case 98: {
				goto _st71;
			}
		}
		{
			goto _st0;
		}
		_ctr135:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 4449 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 4455 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 4461 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4467 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 4473 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4479 "gen/ragel/cat8_2-G2.c"
		
		goto _st72;
		_st72:
		p+= 1;
		if ( p == pe )
			goto _test_eof72;
		st_case_72:
		if ( ( (*( p))) == 97 ) {
			goto _ctr137;
		}
		{
			goto _st0;
		}
		_ctr137:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 4498 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4504 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4510 "gen/ragel/cat8_2-G2.c"
		
		goto _st73;
		_ctr173:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 4518 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 4524 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4530 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 4536 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4542 "gen/ragel/cat8_2-G2.c"
		
		goto _st73;
		_st73:
		p+= 1;
		if ( p == pe )
			goto _test_eof73;
		st_case_73:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr139;
			}
			case 98: {
				goto _st75;
			}
		}
		{
			goto _st0;
		}
		_ctr139:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 4566 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 4572 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4578 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 4584 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4590 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 4596 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 4602 "gen/ragel/cat8_2-G2.c"
		
		goto _st74;
		_st74:
		p+= 1;
		if ( p == pe )
			goto _test_eof74;
		st_case_74:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr142;
			}
			case 98: {
				goto _st75;
			}
		}
		{
			goto _st0;
		}
		_st75:
		p+= 1;
		if ( p == pe )
			goto _test_eof75;
		st_case_75:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr143;
			}
			case 98: {
				goto _st75;
			}
		}
		{
			goto _st0;
		}
		_ctr143:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 4642 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4648 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 4654 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4660 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 4666 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 4672 "gen/ragel/cat8_2-G2.c"
		
		goto _st76;
		_st76:
		p+= 1;
		if ( p == pe )
			goto _test_eof76;
		st_case_76:
		if ( ( (*( p))) == 97 ) {
			goto _ctr145;
		}
		{
			goto _st0;
		}
		_ctr145:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4691 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4697 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 4703 "gen/ragel/cat8_2-G2.c"
		
		goto _st77;
		_ctr181:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4711 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 4717 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4723 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 4729 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 4735 "gen/ragel/cat8_2-G2.c"
		
		goto _st77;
		_st77:
		p+= 1;
		if ( p == pe )
			goto _test_eof77;
		st_case_77:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr147;
			}
			case 98: {
				goto _st79;
			}
		}
		{
			goto _st0;
		}
		_ctr147:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 4759 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 4765 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4771 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 4777 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 4783 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 4789 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 4795 "gen/ragel/cat8_2-G2.c"
		
		goto _st78;
		_st78:
		p+= 1;
		if ( p == pe )
			goto _test_eof78;
		st_case_78:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr150;
			}
			case 98: {
				goto _st79;
			}
		}
		{
			goto _st0;
		}
		_st79:
		p+= 1;
		if ( p == pe )
			goto _test_eof79;
		st_case_79:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr151;
			}
			case 98: {
				goto _st79;
			}
		}
		{
			goto _st0;
		}
		_ctr151:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 4835 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4841 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 4847 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 4853 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 4859 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 4865 "gen/ragel/cat8_2-G2.c"
		
		goto _st80;
		_st80:
		p+= 1;
		if ( p == pe )
			goto _test_eof80;
		st_case_80:
		if ( ( (*( p))) == 97 ) {
			goto _ctr153;
		}
		{
			goto _st0;
		}
		_ctr153:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4884 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 4890 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 4896 "gen/ragel/cat8_2-G2.c"
		
		goto _st81;
		_ctr189:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4904 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 4910 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 4916 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 4922 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 4928 "gen/ragel/cat8_2-G2.c"
		
		goto _st81;
		_st81:
		p+= 1;
		if ( p == pe )
			goto _test_eof81;
		st_case_81:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr155;
			}
			case 98: {
				goto _st83;
			}
		}
		{
			goto _st0;
		}
		_ctr155:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 4952 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 4958 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 4964 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 4970 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 4976 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 4982 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 4988 "gen/ragel/cat8_2-G2.c"
		
		goto _st82;
		_st82:
		p+= 1;
		if ( p == pe )
			goto _test_eof82;
		st_case_82:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr63;
			}
			case 98: {
				goto _st83;
			}
		}
		{
			goto _st0;
		}
		_st83:
		p+= 1;
		if ( p == pe )
			goto _test_eof83;
		st_case_83:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr65;
			}
			case 98: {
				goto _st83;
			}
		}
		{
			goto _st0;
		}
		_st84:
		p+= 1;
		if ( p == pe )
			goto _test_eof84;
		st_case_84:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr158;
			}
			case 98: {
				goto _st84;
			}
		}
		{
			goto _st0;
		}
		_ctr158:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 5044 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 5050 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 5056 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 5062 "gen/ragel/cat8_2-G2.c"
		
		goto _st85;
		_st85:
		p+= 1;
		if ( p == pe )
			goto _test_eof85;
		st_case_85:
		if ( ( (*( p))) == 97 ) {
			goto _ctr160;
		}
		{
			goto _st0;
		}
		_ctr160:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 5081 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 5087 "gen/ragel/cat8_2-G2.c"
		
		goto _st86;
		_ctr204:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 5095 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 5101 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 5107 "gen/ragel/cat8_2-G2.c"
		
		goto _st86;
		_st86:
		p+= 1;
		if ( p == pe )
			goto _test_eof86;
		st_case_86:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr162;
			}
			case 98: {
				goto _st88;
			}
		}
		{
			goto _st0;
		}
		_ctr162:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 5131 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 5137 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 5143 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 5149 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 5155 "gen/ragel/cat8_2-G2.c"
		
		goto _st87;
		_st87:
		p+= 1;
		if ( p == pe )
			goto _test_eof87;
		st_case_87:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr165;
			}
			case 98: {
				goto _st88;
			}
		}
		{
			goto _st0;
		}
		_st88:
		p+= 1;
		if ( p == pe )
			goto _test_eof88;
		st_case_88:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr166;
			}
			case 98: {
				goto _st88;
			}
		}
		{
			goto _st0;
		}
		_ctr166:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 5195 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 5201 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 5207 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 5213 "gen/ragel/cat8_2-G2.c"
		
		goto _st89;
		_st89:
		p+= 1;
		if ( p == pe )
			goto _test_eof89;
		st_case_89:
		if ( ( (*( p))) == 97 ) {
			goto _ctr168;
		}
		{
			goto _st0;
		}
		_ctr168:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 5232 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 5238 "gen/ragel/cat8_2-G2.c"
		
		goto _st90;
		_ctr212:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 5246 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 5252 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 5258 "gen/ragel/cat8_2-G2.c"
		
		goto _st90;
		_st90:
		p+= 1;
		if ( p == pe )
			goto _test_eof90;
		st_case_90:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr170;
			}
			case 98: {
				goto _st92;
			}
		}
		{
			goto _st0;
		}
		_ctr170:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 5282 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 5288 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 5294 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 5300 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 5306 "gen/ragel/cat8_2-G2.c"
		
		goto _st91;
		_st91:
		p+= 1;
		if ( p == pe )
			goto _test_eof91;
		st_case_91:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr173;
			}
			case 98: {
				goto _st92;
			}
		}
		{
			goto _st0;
		}
		_st92:
		p+= 1;
		if ( p == pe )
			goto _test_eof92;
		st_case_92:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr174;
			}
			case 98: {
				goto _st92;
			}
		}
		{
			goto _st0;
		}
		_ctr174:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 5346 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 5352 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 5358 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 5364 "gen/ragel/cat8_2-G2.c"
		
		goto _st93;
		_st93:
		p+= 1;
		if ( p == pe )
			goto _test_eof93;
		st_case_93:
		if ( ( (*( p))) == 97 ) {
			goto _ctr176;
		}
		{
			goto _st0;
		}
		_ctr176:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 5383 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 5389 "gen/ragel/cat8_2-G2.c"
		
		goto _st94;
		_ctr220:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 5397 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 5403 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 5409 "gen/ragel/cat8_2-G2.c"
		
		goto _st94;
		_st94:
		p+= 1;
		if ( p == pe )
			goto _test_eof94;
		st_case_94:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr178;
			}
			case 98: {
				goto _st96;
			}
		}
		{
			goto _st0;
		}
		_ctr178:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 5433 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 5439 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 5445 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 5451 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 5457 "gen/ragel/cat8_2-G2.c"
		
		goto _st95;
		_st95:
		p+= 1;
		if ( p == pe )
			goto _test_eof95;
		st_case_95:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr181;
			}
			case 98: {
				goto _st96;
			}
		}
		{
			goto _st0;
		}
		_st96:
		p+= 1;
		if ( p == pe )
			goto _test_eof96;
		st_case_96:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr182;
			}
			case 98: {
				goto _st96;
			}
		}
		{
			goto _st0;
		}
		_ctr182:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 5497 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 5503 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 5509 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 5515 "gen/ragel/cat8_2-G2.c"
		
		goto _st97;
		_st97:
		p+= 1;
		if ( p == pe )
			goto _test_eof97;
		st_case_97:
		if ( ( (*( p))) == 97 ) {
			goto _ctr184;
		}
		{
			goto _st0;
		}
		_ctr184:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 5534 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 5540 "gen/ragel/cat8_2-G2.c"
		
		goto _st98;
		_ctr228:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 5548 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 5554 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 5560 "gen/ragel/cat8_2-G2.c"
		
		goto _st98;
		_st98:
		p+= 1;
		if ( p == pe )
			goto _test_eof98;
		st_case_98:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr186;
			}
			case 98: {
				goto _st100;
			}
		}
		{
			goto _st0;
		}
		_ctr186:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 5584 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 5590 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 5596 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 5602 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 5608 "gen/ragel/cat8_2-G2.c"
		
		goto _st99;
		_st99:
		p+= 1;
		if ( p == pe )
			goto _test_eof99;
		st_case_99:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr189;
			}
			case 98: {
				goto _st100;
			}
		}
		{
			goto _st0;
		}
		_st100:
		p+= 1;
		if ( p == pe )
			goto _test_eof100;
		st_case_100:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr190;
			}
			case 98: {
				goto _st100;
			}
		}
		{
			goto _st0;
		}
		_ctr190:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 5648 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 5654 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 5660 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 5666 "gen/ragel/cat8_2-G2.c"
		
		goto _st101;
		_st101:
		p+= 1;
		if ( p == pe )
			goto _test_eof101;
		st_case_101:
		if ( ( (*( p))) == 97 ) {
			goto _ctr192;
		}
		{
			goto _st0;
		}
		_ctr192:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 5685 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 5691 "gen/ragel/cat8_2-G2.c"
		
		goto _st102;
		_ctr236:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 5699 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 5705 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 5711 "gen/ragel/cat8_2-G2.c"
		
		goto _st102;
		_st102:
		p+= 1;
		if ( p == pe )
			goto _test_eof102;
		st_case_102:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr194;
			}
			case 98: {
				goto _st104;
			}
		}
		{
			goto _st0;
		}
		_ctr194:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 5735 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 5741 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 5747 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 5753 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 5759 "gen/ragel/cat8_2-G2.c"
		
		goto _st103;
		_st103:
		p+= 1;
		if ( p == pe )
			goto _test_eof103;
		st_case_103:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr69;
			}
			case 98: {
				goto _st104;
			}
		}
		{
			goto _st0;
		}
		_st104:
		p+= 1;
		if ( p == pe )
			goto _test_eof104;
		st_case_104:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr71;
			}
			case 98: {
				goto _st104;
			}
		}
		{
			goto _st0;
		}
		_st105:
		p+= 1;
		if ( p == pe )
			goto _test_eof105;
		st_case_105:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr197;
			}
			case 98: {
				goto _st105;
			}
		}
		{
			goto _st0;
		}
		_ctr197:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a1 = p; }
		
#line 5815 "gen/ragel/cat8_2-G2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 5821 "gen/ragel/cat8_2-G2.c"
		
		goto _st106;
		_st106:
		p+= 1;
		if ( p == pe )
			goto _test_eof106;
		st_case_106:
		if ( ( (*( p))) == 97 ) {
			goto _ctr199;
		}
		{
			goto _st0;
		}
		_ctr199:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 5840 "gen/ragel/cat8_2-G2.c"
		
		goto _st107;
		_st107:
		p+= 1;
		if ( p == pe )
			goto _test_eof107;
		st_case_107:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr201;
			}
			case 98: {
				goto _st109;
			}
		}
		{
			goto _st0;
		}
		_ctr201:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b1 = p; }
		
#line 5864 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 5870 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 5876 "gen/ragel/cat8_2-G2.c"
		
		goto _st108;
		_st108:
		p+= 1;
		if ( p == pe )
			goto _test_eof108;
		st_case_108:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr204;
			}
			case 98: {
				goto _st109;
			}
		}
		{
			goto _st0;
		}
		_st109:
		p+= 1;
		if ( p == pe )
			goto _test_eof109;
		st_case_109:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr205;
			}
			case 98: {
				goto _st109;
			}
		}
		{
			goto _st0;
		}
		_ctr205:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a2 = p; }
		
#line 5916 "gen/ragel/cat8_2-G2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 5922 "gen/ragel/cat8_2-G2.c"
		
		goto _st110;
		_st110:
		p+= 1;
		if ( p == pe )
			goto _test_eof110;
		st_case_110:
		if ( ( (*( p))) == 97 ) {
			goto _ctr207;
		}
		{
			goto _st0;
		}
		_ctr207:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 5941 "gen/ragel/cat8_2-G2.c"
		
		goto _st111;
		_st111:
		p+= 1;
		if ( p == pe )
			goto _test_eof111;
		st_case_111:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr209;
			}
			case 98: {
				goto _st113;
			}
		}
		{
			goto _st0;
		}
		_ctr209:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b2 = p; }
		
#line 5965 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 5971 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 5977 "gen/ragel/cat8_2-G2.c"
		
		goto _st112;
		_st112:
		p+= 1;
		if ( p == pe )
			goto _test_eof112;
		st_case_112:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr212;
			}
			case 98: {
				goto _st113;
			}
		}
		{
			goto _st0;
		}
		_st113:
		p+= 1;
		if ( p == pe )
			goto _test_eof113;
		st_case_113:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr213;
			}
			case 98: {
				goto _st113;
			}
		}
		{
			goto _st0;
		}
		_ctr213:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a3 = p; }
		
#line 6017 "gen/ragel/cat8_2-G2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 6023 "gen/ragel/cat8_2-G2.c"
		
		goto _st114;
		_st114:
		p+= 1;
		if ( p == pe )
			goto _test_eof114;
		st_case_114:
		if ( ( (*( p))) == 97 ) {
			goto _ctr215;
		}
		{
			goto _st0;
		}
		_ctr215:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 6042 "gen/ragel/cat8_2-G2.c"
		
		goto _st115;
		_st115:
		p+= 1;
		if ( p == pe )
			goto _test_eof115;
		st_case_115:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr217;
			}
			case 98: {
				goto _st117;
			}
		}
		{
			goto _st0;
		}
		_ctr217:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b3 = p; }
		
#line 6066 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 6072 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 6078 "gen/ragel/cat8_2-G2.c"
		
		goto _st116;
		_st116:
		p+= 1;
		if ( p == pe )
			goto _test_eof116;
		st_case_116:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr220;
			}
			case 98: {
				goto _st117;
			}
		}
		{
			goto _st0;
		}
		_st117:
		p+= 1;
		if ( p == pe )
			goto _test_eof117;
		st_case_117:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr221;
			}
			case 98: {
				goto _st117;
			}
		}
		{
			goto _st0;
		}
		_ctr221:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a4 = p; }
		
#line 6118 "gen/ragel/cat8_2-G2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 6124 "gen/ragel/cat8_2-G2.c"
		
		goto _st118;
		_st118:
		p+= 1;
		if ( p == pe )
			goto _test_eof118;
		st_case_118:
		if ( ( (*( p))) == 97 ) {
			goto _ctr223;
		}
		{
			goto _st0;
		}
		_ctr223:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 6143 "gen/ragel/cat8_2-G2.c"
		
		goto _st119;
		_st119:
		p+= 1;
		if ( p == pe )
			goto _test_eof119;
		st_case_119:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr225;
			}
			case 98: {
				goto _st121;
			}
		}
		{
			goto _st0;
		}
		_ctr225:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b4 = p; }
		
#line 6167 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 6173 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 6179 "gen/ragel/cat8_2-G2.c"
		
		goto _st120;
		_st120:
		p+= 1;
		if ( p == pe )
			goto _test_eof120;
		st_case_120:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr228;
			}
			case 98: {
				goto _st121;
			}
		}
		{
			goto _st0;
		}
		_st121:
		p+= 1;
		if ( p == pe )
			goto _test_eof121;
		st_case_121:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr229;
			}
			case 98: {
				goto _st121;
			}
		}
		{
			goto _st0;
		}
		_ctr229:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a5 = p; }
		
#line 6219 "gen/ragel/cat8_2-G2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 6225 "gen/ragel/cat8_2-G2.c"
		
		goto _st122;
		_st122:
		p+= 1;
		if ( p == pe )
			goto _test_eof122;
		st_case_122:
		if ( ( (*( p))) == 97 ) {
			goto _ctr231;
		}
		{
			goto _st0;
		}
		_ctr231:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 6244 "gen/ragel/cat8_2-G2.c"
		
		goto _st123;
		_st123:
		p+= 1;
		if ( p == pe )
			goto _test_eof123;
		st_case_123:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr233;
			}
			case 98: {
				goto _st125;
			}
		}
		{
			goto _st0;
		}
		_ctr233:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b5 = p; }
		
#line 6268 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 6274 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 6280 "gen/ragel/cat8_2-G2.c"
		
		goto _st124;
		_st124:
		p+= 1;
		if ( p == pe )
			goto _test_eof124;
		st_case_124:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr236;
			}
			case 98: {
				goto _st125;
			}
		}
		{
			goto _st0;
		}
		_st125:
		p+= 1;
		if ( p == pe )
			goto _test_eof125;
		st_case_125:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr237;
			}
			case 98: {
				goto _st125;
			}
		}
		{
			goto _st0;
		}
		_ctr237:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a6 = p; }
		
#line 6320 "gen/ragel/cat8_2-G2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 6326 "gen/ragel/cat8_2-G2.c"
		
		goto _st126;
		_st126:
		p+= 1;
		if ( p == pe )
			goto _test_eof126;
		st_case_126:
		if ( ( (*( p))) == 97 ) {
			goto _ctr239;
		}
		{
			goto _st0;
		}
		_ctr239:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 6345 "gen/ragel/cat8_2-G2.c"
		
		goto _st127;
		_st127:
		p+= 1;
		if ( p == pe )
			goto _test_eof127;
		st_case_127:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr241;
			}
			case 98: {
				goto _st129;
			}
		}
		{
			goto _st0;
		}
		_ctr241:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b6 = p; }
		
#line 6369 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			a7 = p; }
		
#line 6375 "gen/ragel/cat8_2-G2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
			b7 = p; }
		
#line 6381 "gen/ragel/cat8_2-G2.c"
		
		goto _st128;
		_st128:
		p+= 1;
		if ( p == pe )
			goto _test_eof128;
		st_case_128:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr75;
			}
			case 98: {
				goto _st129;
			}
		}
		{
			goto _st0;
		}
		_st129:
		p+= 1;
		if ( p == pe )
			goto _test_eof129;
		st_case_129:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr77;
			}
			case 98: {
				goto _st129;
			}
		}
		{
			goto _st0;
		}
		st_out:
		_test_eof130: cs = 130; goto _test_eof; 
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
		_test_eof73: cs = 73; goto _test_eof; 
		_test_eof74: cs = 74; goto _test_eof; 
		_test_eof75: cs = 75; goto _test_eof; 
		_test_eof76: cs = 76; goto _test_eof; 
		_test_eof77: cs = 77; goto _test_eof; 
		_test_eof78: cs = 78; goto _test_eof; 
		_test_eof79: cs = 79; goto _test_eof; 
		_test_eof80: cs = 80; goto _test_eof; 
		_test_eof81: cs = 81; goto _test_eof; 
		_test_eof82: cs = 82; goto _test_eof; 
		_test_eof83: cs = 83; goto _test_eof; 
		_test_eof84: cs = 84; goto _test_eof; 
		_test_eof85: cs = 85; goto _test_eof; 
		_test_eof86: cs = 86; goto _test_eof; 
		_test_eof87: cs = 87; goto _test_eof; 
		_test_eof88: cs = 88; goto _test_eof; 
		_test_eof89: cs = 89; goto _test_eof; 
		_test_eof90: cs = 90; goto _test_eof; 
		_test_eof91: cs = 91; goto _test_eof; 
		_test_eof92: cs = 92; goto _test_eof; 
		_test_eof93: cs = 93; goto _test_eof; 
		_test_eof94: cs = 94; goto _test_eof; 
		_test_eof95: cs = 95; goto _test_eof; 
		_test_eof96: cs = 96; goto _test_eof; 
		_test_eof97: cs = 97; goto _test_eof; 
		_test_eof98: cs = 98; goto _test_eof; 
		_test_eof99: cs = 99; goto _test_eof; 
		_test_eof100: cs = 100; goto _test_eof; 
		_test_eof101: cs = 101; goto _test_eof; 
		_test_eof102: cs = 102; goto _test_eof; 
		_test_eof103: cs = 103; goto _test_eof; 
		_test_eof104: cs = 104; goto _test_eof; 
		_test_eof105: cs = 105; goto _test_eof; 
		_test_eof106: cs = 106; goto _test_eof; 
		_test_eof107: cs = 107; goto _test_eof; 
		_test_eof108: cs = 108; goto _test_eof; 
		_test_eof109: cs = 109; goto _test_eof; 
		_test_eof110: cs = 110; goto _test_eof; 
		_test_eof111: cs = 111; goto _test_eof; 
		_test_eof112: cs = 112; goto _test_eof; 
		_test_eof113: cs = 113; goto _test_eof; 
		_test_eof114: cs = 114; goto _test_eof; 
		_test_eof115: cs = 115; goto _test_eof; 
		_test_eof116: cs = 116; goto _test_eof; 
		_test_eof117: cs = 117; goto _test_eof; 
		_test_eof118: cs = 118; goto _test_eof; 
		_test_eof119: cs = 119; goto _test_eof; 
		_test_eof120: cs = 120; goto _test_eof; 
		_test_eof121: cs = 121; goto _test_eof; 
		_test_eof122: cs = 122; goto _test_eof; 
		_test_eof123: cs = 123; goto _test_eof; 
		_test_eof124: cs = 124; goto _test_eof; 
		_test_eof125: cs = 125; goto _test_eof; 
		_test_eof126: cs = 126; goto _test_eof; 
		_test_eof127: cs = 127; goto _test_eof; 
		_test_eof128: cs = 128; goto _test_eof; 
		_test_eof129: cs = 129; goto _test_eof; 
		
		_test_eof: {}
		if ( cs >= 130 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/cat8_2.rl"
	
	
	in->p = p;
	in->pe = pe;
}
