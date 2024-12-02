#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 29 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"



#line 12 "gen/ragel/28__cat8_2.c"
static const int abcd_start = 130;
static const int abcd_first_final = 130;
static const int abcd_error = 0;

static const int abcd_en_main = 130;


#line 31 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
	*b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
	int cs;
	
	
#line 33 "gen/ragel/28__cat8_2.c"
	{
		cs = (int)abcd_start;
	}
	
#line 42 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
	
	
#line 41 "gen/ragel/28__cat8_2.c"
	{
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
		_ctr39:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
			outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
			outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
			outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
			outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
		}
		
#line 321 "gen/ragel/28__cat8_2.c"
		
		goto _st130;
		_st130:
		p+= 1;
		st_case_130:
		if ( p == pe )
			goto _out130;
		if ( ( (*( p))) == 97 ) {
			goto _ctr245;
		}
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr245:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a0 = p; }
		
#line 341 "gen/ragel/28__cat8_2.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 347 "gen/ragel/28__cat8_2.c"
		
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 364 "gen/ragel/28__cat8_2.c"
		
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
				goto _st105;
			}
		}
		goto _st0;
		_ctr4:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 386 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 392 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 398 "gen/ragel/28__cat8_2.c"
		
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
				goto _st105;
			}
		}
		goto _st0;
		_ctr7:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 420 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 426 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 432 "gen/ragel/28__cat8_2.c"
		
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
				goto _st84;
			}
		}
		goto _st0;
		_ctr9:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 454 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 460 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 466 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 472 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 478 "gen/ragel/28__cat8_2.c"
		
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
				goto _st84;
			}
		}
		goto _st0;
		_ctr12:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 500 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 506 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 512 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 518 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 524 "gen/ragel/28__cat8_2.c"
		
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
				goto _st67;
			}
		}
		goto _st0;
		_ctr14:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 546 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 552 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 558 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 564 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 570 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 576 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 582 "gen/ragel/28__cat8_2.c"
		
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
				goto _st67;
			}
		}
		goto _st0;
		_ctr17:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 604 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 610 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 616 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 622 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 628 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 634 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 640 "gen/ragel/28__cat8_2.c"
		
		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr19;
			}
			case 98: {
				goto _st54;
			}
		}
		goto _st0;
		_ctr19:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 662 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 668 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 674 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 680 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 686 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 692 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 698 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 704 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 710 "gen/ragel/28__cat8_2.c"
		
		goto _st9;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr22;
			}
			case 98: {
				goto _st54;
			}
		}
		goto _st0;
		_ctr22:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 732 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 738 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 744 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 750 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 756 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 762 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 768 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 774 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 780 "gen/ragel/28__cat8_2.c"
		
		goto _st10;
		_st10:
		p+= 1;
		st_case_10:
		if ( p == pe )
			goto _out10;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr24;
			}
			case 98: {
				goto _st45;
			}
		}
		goto _st0;
		_ctr24:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 802 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 808 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 814 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 820 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 826 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 832 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 838 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 844 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 850 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 856 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 862 "gen/ragel/28__cat8_2.c"
		
		goto _st11;
		_st11:
		p+= 1;
		st_case_11:
		if ( p == pe )
			goto _out11;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr27;
			}
			case 98: {
				goto _st45;
			}
		}
		goto _st0;
		_ctr27:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 884 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 890 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 896 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 902 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 908 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 914 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 920 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 926 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 932 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 938 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 944 "gen/ragel/28__cat8_2.c"
		
		goto _st12;
		_st12:
		p+= 1;
		st_case_12:
		if ( p == pe )
			goto _out12;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr29;
			}
			case 98: {
				goto _st40;
			}
		}
		goto _st0;
		_ctr29:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 966 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 972 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 978 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 984 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 990 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 996 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 1002 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 1008 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 1014 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 1020 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 1026 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 1032 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 1038 "gen/ragel/28__cat8_2.c"
		
		goto _st13;
		_st13:
		p+= 1;
		st_case_13:
		if ( p == pe )
			goto _out13;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr32;
			}
			case 98: {
				goto _st40;
			}
		}
		goto _st0;
		_ctr32:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 1060 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 1066 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 1072 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 1078 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 1084 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 1090 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 1096 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 1102 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 1108 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 1114 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 1120 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 1126 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 1132 "gen/ragel/28__cat8_2.c"
		
		goto _st14;
		_st14:
		p+= 1;
		st_case_14:
		if ( p == pe )
			goto _out14;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr34;
			}
			case 98: {
				goto _st39;
			}
		}
		goto _st0;
		_ctr34:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 1154 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 1160 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 1166 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 1172 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 1178 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 1184 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 1190 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 1196 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 1202 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 1208 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 1214 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 1220 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 1226 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 1232 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 1238 "gen/ragel/28__cat8_2.c"
		
		goto _st15;
		_st15:
		p+= 1;
		st_case_15:
		if ( p == pe )
			goto _out15;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr37;
			}
			case 98: {
				goto _st39;
			}
		}
		goto _st0;
		_ctr37:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b0 = p; }
		
#line 1260 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 1266 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 1272 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 1278 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 1284 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 1290 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 1296 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 1302 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 1308 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 1314 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 1320 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 1326 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 1332 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 1338 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 1344 "gen/ragel/28__cat8_2.c"
		
		goto _st16;
		_st16:
		p+= 1;
		st_case_16:
		if ( p == pe )
			goto _out16;
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
		goto _st0;
		_st17:
		p+= 1;
		st_case_17:
		if ( p == pe )
			goto _out17;
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
		goto _st0;
		_ctr41:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 1386 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 1392 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 1398 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 1404 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 1410 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 1416 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 1422 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 1428 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 1434 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 1440 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 1446 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 1452 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 1458 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 1464 "gen/ragel/28__cat8_2.c"
		
		goto _st18;
		_st18:
		p+= 1;
		st_case_18:
		if ( p == pe )
			goto _out18;
		if ( ( (*( p))) == 97 ) {
			goto _ctr43;
		}
		goto _st0;
		_ctr43:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 1481 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 1487 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 1493 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 1499 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 1505 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 1511 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 1517 "gen/ragel/28__cat8_2.c"
		
		goto _st19;
		_ctr45:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 1525 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 1531 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 1537 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 1543 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 1549 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 1555 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 1561 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 1567 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 1573 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 1579 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 1585 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 1591 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 1597 "gen/ragel/28__cat8_2.c"
		
		goto _st19;
		_st19:
		p+= 1;
		st_case_19:
		if ( p == pe )
			goto _out19;
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
		goto _st0;
		_st20:
		p+= 1;
		st_case_20:
		if ( p == pe )
			goto _out20;
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
		goto _st0;
		_ctr47:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 1639 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 1645 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 1651 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 1657 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 1663 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 1669 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 1675 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 1681 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 1687 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 1693 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 1699 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 1705 "gen/ragel/28__cat8_2.c"
		
		goto _st21;
		_st21:
		p+= 1;
		st_case_21:
		if ( p == pe )
			goto _out21;
		if ( ( (*( p))) == 97 ) {
			goto _ctr49;
		}
		goto _st0;
		_ctr49:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 1722 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 1728 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 1734 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 1740 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 1746 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 1752 "gen/ragel/28__cat8_2.c"
		
		goto _st22;
		_ctr51:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 1760 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 1766 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 1772 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 1778 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 1784 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 1790 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 1796 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 1802 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 1808 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 1814 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 1820 "gen/ragel/28__cat8_2.c"
		
		goto _st22;
		_st22:
		p+= 1;
		st_case_22:
		if ( p == pe )
			goto _out22;
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
		goto _st0;
		_st23:
		p+= 1;
		st_case_23:
		if ( p == pe )
			goto _out23;
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
		goto _st0;
		_ctr53:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 1862 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 1868 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 1874 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 1880 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 1886 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 1892 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 1898 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 1904 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 1910 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 1916 "gen/ragel/28__cat8_2.c"
		
		goto _st24;
		_st24:
		p+= 1;
		st_case_24:
		if ( p == pe )
			goto _out24;
		if ( ( (*( p))) == 97 ) {
			goto _ctr55;
		}
		goto _st0;
		_ctr55:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 1933 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 1939 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 1945 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 1951 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 1957 "gen/ragel/28__cat8_2.c"
		
		goto _st25;
		_ctr57:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 1965 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 1971 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 1977 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 1983 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 1989 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 1995 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 2001 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 2007 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 2013 "gen/ragel/28__cat8_2.c"
		
		goto _st25;
		_st25:
		p+= 1;
		st_case_25:
		if ( p == pe )
			goto _out25;
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
		goto _st0;
		_st26:
		p+= 1;
		st_case_26:
		if ( p == pe )
			goto _out26;
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
		goto _st0;
		_ctr59:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 2055 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 2061 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 2067 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 2073 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 2079 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 2085 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 2091 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 2097 "gen/ragel/28__cat8_2.c"
		
		goto _st27;
		_st27:
		p+= 1;
		st_case_27:
		if ( p == pe )
			goto _out27;
		if ( ( (*( p))) == 97 ) {
			goto _ctr61;
		}
		goto _st0;
		_ctr61:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 2114 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 2120 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 2126 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 2132 "gen/ragel/28__cat8_2.c"
		
		goto _st28;
		_ctr63:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 2140 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 2146 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 2152 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 2158 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 2164 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 2170 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 2176 "gen/ragel/28__cat8_2.c"
		
		goto _st28;
		_st28:
		p+= 1;
		st_case_28:
		if ( p == pe )
			goto _out28;
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
		goto _st0;
		_st29:
		p+= 1;
		st_case_29:
		if ( p == pe )
			goto _out29;
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
		goto _st0;
		_ctr65:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 2218 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 2224 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 2230 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 2236 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 2242 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 2248 "gen/ragel/28__cat8_2.c"
		
		goto _st30;
		_st30:
		p+= 1;
		st_case_30:
		if ( p == pe )
			goto _out30;
		if ( ( (*( p))) == 97 ) {
			goto _ctr67;
		}
		goto _st0;
		_ctr67:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 2265 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 2271 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 2277 "gen/ragel/28__cat8_2.c"
		
		goto _st31;
		_ctr69:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 2285 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 2291 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 2297 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 2303 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 2309 "gen/ragel/28__cat8_2.c"
		
		goto _st31;
		_st31:
		p+= 1;
		st_case_31:
		if ( p == pe )
			goto _out31;
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
		goto _st0;
		_st32:
		p+= 1;
		st_case_32:
		if ( p == pe )
			goto _out32;
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
		goto _st0;
		_ctr71:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 2351 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 2357 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 2363 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 2369 "gen/ragel/28__cat8_2.c"
		
		goto _st33;
		_st33:
		p+= 1;
		st_case_33:
		if ( p == pe )
			goto _out33;
		if ( ( (*( p))) == 97 ) {
			goto _ctr73;
		}
		goto _st0;
		_ctr73:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 2386 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 2392 "gen/ragel/28__cat8_2.c"
		
		goto _st34;
		_ctr75:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 2400 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 2406 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 2412 "gen/ragel/28__cat8_2.c"
		
		goto _st34;
		_st34:
		p+= 1;
		st_case_34:
		if ( p == pe )
			goto _out34;
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
		goto _st0;
		_st35:
		p+= 1;
		st_case_35:
		if ( p == pe )
			goto _out35;
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
		goto _st0;
		_ctr77:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 2454 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 2460 "gen/ragel/28__cat8_2.c"
		
		goto _st36;
		_st36:
		p+= 1;
		st_case_36:
		if ( p == pe )
			goto _out36;
		if ( ( (*( p))) == 97 ) {
			goto _ctr79;
		}
		goto _st0;
		_ctr79:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 2477 "gen/ragel/28__cat8_2.c"
		
		goto _st37;
		_st37:
		p+= 1;
		st_case_37:
		if ( p == pe )
			goto _out37;
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
		goto _st0;
		_st38:
		p+= 1;
		st_case_38:
		if ( p == pe )
			goto _out38;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr39;
			}
			case 98: {
				goto _st38;
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
				goto _ctr41;
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
				goto _ctr82;
			}
			case 98: {
				goto _st40;
			}
		}
		goto _st0;
		_ctr82:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 2544 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 2550 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 2556 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 2562 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 2568 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 2574 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 2580 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 2586 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 2592 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 2598 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 2604 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 2610 "gen/ragel/28__cat8_2.c"
		
		goto _st41;
		_st41:
		p+= 1;
		st_case_41:
		if ( p == pe )
			goto _out41;
		if ( ( (*( p))) == 97 ) {
			goto _ctr84;
		}
		goto _st0;
		_ctr84:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 2627 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 2633 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 2639 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 2645 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 2651 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 2657 "gen/ragel/28__cat8_2.c"
		
		goto _st42;
		_ctr96:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 2665 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 2671 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 2677 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 2683 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 2689 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 2695 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 2701 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 2707 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 2713 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 2719 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 2725 "gen/ragel/28__cat8_2.c"
		
		goto _st42;
		_st42:
		p+= 1;
		st_case_42:
		if ( p == pe )
			goto _out42;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr86;
			}
			case 98: {
				goto _st44;
			}
		}
		goto _st0;
		_ctr86:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 2747 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 2753 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 2759 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 2765 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 2771 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 2777 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 2783 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 2789 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 2795 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 2801 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 2807 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 2813 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 2819 "gen/ragel/28__cat8_2.c"
		
		goto _st43;
		_st43:
		p+= 1;
		st_case_43:
		if ( p == pe )
			goto _out43;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr45;
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
				goto _ctr47;
			}
			case 98: {
				goto _st44;
			}
		}
		goto _st0;
		_st45:
		p+= 1;
		st_case_45:
		if ( p == pe )
			goto _out45;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr89;
			}
			case 98: {
				goto _st45;
			}
		}
		goto _st0;
		_ctr89:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 2869 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 2875 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 2881 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 2887 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 2893 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 2899 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 2905 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 2911 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 2917 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 2923 "gen/ragel/28__cat8_2.c"
		
		goto _st46;
		_st46:
		p+= 1;
		st_case_46:
		if ( p == pe )
			goto _out46;
		if ( ( (*( p))) == 97 ) {
			goto _ctr91;
		}
		goto _st0;
		_ctr91:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 2940 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 2946 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 2952 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 2958 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 2964 "gen/ragel/28__cat8_2.c"
		
		goto _st47;
		_ctr111:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 2972 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 2978 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 2984 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 2990 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 2996 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 3002 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3008 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 3014 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 3020 "gen/ragel/28__cat8_2.c"
		
		goto _st47;
		_st47:
		p+= 1;
		st_case_47:
		if ( p == pe )
			goto _out47;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr93;
			}
			case 98: {
				goto _st49;
			}
		}
		goto _st0;
		_ctr93:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 3042 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 3048 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 3054 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 3060 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3066 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 3072 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3078 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 3084 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 3090 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 3096 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 3102 "gen/ragel/28__cat8_2.c"
		
		goto _st48;
		_st48:
		p+= 1;
		st_case_48:
		if ( p == pe )
			goto _out48;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr96;
			}
			case 98: {
				goto _st49;
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
				goto _ctr97;
			}
			case 98: {
				goto _st49;
			}
		}
		goto _st0;
		_ctr97:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 3138 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 3144 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 3150 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3156 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 3162 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3168 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 3174 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 3180 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 3186 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 3192 "gen/ragel/28__cat8_2.c"
		
		goto _st50;
		_st50:
		p+= 1;
		st_case_50:
		if ( p == pe )
			goto _out50;
		if ( ( (*( p))) == 97 ) {
			goto _ctr99;
		}
		goto _st0;
		_ctr99:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 3209 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3215 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3221 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 3227 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 3233 "gen/ragel/28__cat8_2.c"
		
		goto _st51;
		_ctr119:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 3241 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 3247 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3253 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 3259 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3265 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 3271 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 3277 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 3283 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 3289 "gen/ragel/28__cat8_2.c"
		
		goto _st51;
		_st51:
		p+= 1;
		st_case_51:
		if ( p == pe )
			goto _out51;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr101;
			}
			case 98: {
				goto _st53;
			}
		}
		goto _st0;
		_ctr101:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 3311 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 3317 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3323 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 3329 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3335 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 3341 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 3347 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 3353 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 3359 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 3365 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 3371 "gen/ragel/28__cat8_2.c"
		
		goto _st52;
		_st52:
		p+= 1;
		st_case_52:
		if ( p == pe )
			goto _out52;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr51;
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
				goto _ctr53;
			}
			case 98: {
				goto _st53;
			}
		}
		goto _st0;
		_st54:
		p+= 1;
		st_case_54:
		if ( p == pe )
			goto _out54;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr104;
			}
			case 98: {
				goto _st54;
			}
		}
		goto _st0;
		_ctr104:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 3421 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 3427 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 3433 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 3439 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 3445 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3451 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 3457 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3463 "gen/ragel/28__cat8_2.c"
		
		goto _st55;
		_st55:
		p+= 1;
		st_case_55:
		if ( p == pe )
			goto _out55;
		if ( ( (*( p))) == 97 ) {
			goto _ctr106;
		}
		goto _st0;
		_ctr106:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 3480 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 3486 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3492 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3498 "gen/ragel/28__cat8_2.c"
		
		goto _st56;
		_ctr134:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 3506 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 3512 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 3518 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 3524 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3530 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 3536 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3542 "gen/ragel/28__cat8_2.c"
		
		goto _st56;
		_st56:
		p+= 1;
		st_case_56:
		if ( p == pe )
			goto _out56;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr108;
			}
			case 98: {
				goto _st58;
			}
		}
		goto _st0;
		_ctr108:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 3564 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 3570 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 3576 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 3582 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3588 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 3594 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3600 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 3606 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 3612 "gen/ragel/28__cat8_2.c"
		
		goto _st57;
		_st57:
		p+= 1;
		st_case_57:
		if ( p == pe )
			goto _out57;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr111;
			}
			case 98: {
				goto _st58;
			}
		}
		goto _st0;
		_st58:
		p+= 1;
		st_case_58:
		if ( p == pe )
			goto _out58;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr112;
			}
			case 98: {
				goto _st58;
			}
		}
		goto _st0;
		_ctr112:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 3648 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 3654 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 3660 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3666 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 3672 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3678 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 3684 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 3690 "gen/ragel/28__cat8_2.c"
		
		goto _st59;
		_st59:
		p+= 1;
		st_case_59:
		if ( p == pe )
			goto _out59;
		if ( ( (*( p))) == 97 ) {
			goto _ctr114;
		}
		goto _st0;
		_ctr114:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 3707 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3713 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3719 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 3725 "gen/ragel/28__cat8_2.c"
		
		goto _st60;
		_ctr142:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 3733 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 3739 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3745 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 3751 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3757 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 3763 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 3769 "gen/ragel/28__cat8_2.c"
		
		goto _st60;
		_st60:
		p+= 1;
		st_case_60:
		if ( p == pe )
			goto _out60;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr116;
			}
			case 98: {
				goto _st62;
			}
		}
		goto _st0;
		_ctr116:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 3791 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 3797 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3803 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 3809 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3815 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 3821 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 3827 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 3833 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 3839 "gen/ragel/28__cat8_2.c"
		
		goto _st61;
		_st61:
		p+= 1;
		st_case_61:
		if ( p == pe )
			goto _out61;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr119;
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
				goto _ctr120;
			}
			case 98: {
				goto _st62;
			}
		}
		goto _st0;
		_ctr120:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 3875 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3881 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 3887 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3893 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 3899 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 3905 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 3911 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 3917 "gen/ragel/28__cat8_2.c"
		
		goto _st63;
		_st63:
		p+= 1;
		st_case_63:
		if ( p == pe )
			goto _out63;
		if ( ( (*( p))) == 97 ) {
			goto _ctr122;
		}
		goto _st0;
		_ctr122:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3934 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3940 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 3946 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 3952 "gen/ragel/28__cat8_2.c"
		
		goto _st64;
		_ctr150:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 3960 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 3966 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 3972 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 3978 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 3984 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 3990 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 3996 "gen/ragel/28__cat8_2.c"
		
		goto _st64;
		_st64:
		p+= 1;
		st_case_64:
		if ( p == pe )
			goto _out64;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr124;
			}
			case 98: {
				goto _st66;
			}
		}
		goto _st0;
		_ctr124:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 4018 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 4024 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 4030 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 4036 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 4042 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 4048 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 4054 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 4060 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 4066 "gen/ragel/28__cat8_2.c"
		
		goto _st65;
		_st65:
		p+= 1;
		st_case_65:
		if ( p == pe )
			goto _out65;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr57;
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
				goto _ctr59;
			}
			case 98: {
				goto _st66;
			}
		}
		goto _st0;
		_st67:
		p+= 1;
		st_case_67:
		if ( p == pe )
			goto _out67;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr127;
			}
			case 98: {
				goto _st67;
			}
		}
		goto _st0;
		_ctr127:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 4116 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 4122 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 4128 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 4134 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 4140 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 4146 "gen/ragel/28__cat8_2.c"
		
		goto _st68;
		_st68:
		p+= 1;
		st_case_68:
		if ( p == pe )
			goto _out68;
		if ( ( (*( p))) == 97 ) {
			goto _ctr129;
		}
		goto _st0;
		_ctr129:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 4163 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 4169 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 4175 "gen/ragel/28__cat8_2.c"
		
		goto _st69;
		_ctr165:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 4183 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 4189 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 4195 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 4201 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 4207 "gen/ragel/28__cat8_2.c"
		
		goto _st69;
		_st69:
		p+= 1;
		st_case_69:
		if ( p == pe )
			goto _out69;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr131;
			}
			case 98: {
				goto _st71;
			}
		}
		goto _st0;
		_ctr131:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 4229 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 4235 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 4241 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 4247 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 4253 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 4259 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 4265 "gen/ragel/28__cat8_2.c"
		
		goto _st70;
		_st70:
		p+= 1;
		st_case_70:
		if ( p == pe )
			goto _out70;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr134;
			}
			case 98: {
				goto _st71;
			}
		}
		goto _st0;
		_st71:
		p+= 1;
		st_case_71:
		if ( p == pe )
			goto _out71;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr135;
			}
			case 98: {
				goto _st71;
			}
		}
		goto _st0;
		_ctr135:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 4301 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 4307 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 4313 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 4319 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 4325 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 4331 "gen/ragel/28__cat8_2.c"
		
		goto _st72;
		_st72:
		p+= 1;
		st_case_72:
		if ( p == pe )
			goto _out72;
		if ( ( (*( p))) == 97 ) {
			goto _ctr137;
		}
		goto _st0;
		_ctr137:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 4348 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 4354 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 4360 "gen/ragel/28__cat8_2.c"
		
		goto _st73;
		_ctr173:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 4368 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 4374 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 4380 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 4386 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 4392 "gen/ragel/28__cat8_2.c"
		
		goto _st73;
		_st73:
		p+= 1;
		st_case_73:
		if ( p == pe )
			goto _out73;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr139;
			}
			case 98: {
				goto _st75;
			}
		}
		goto _st0;
		_ctr139:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 4414 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 4420 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 4426 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 4432 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 4438 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 4444 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 4450 "gen/ragel/28__cat8_2.c"
		
		goto _st74;
		_st74:
		p+= 1;
		st_case_74:
		if ( p == pe )
			goto _out74;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr142;
			}
			case 98: {
				goto _st75;
			}
		}
		goto _st0;
		_st75:
		p+= 1;
		st_case_75:
		if ( p == pe )
			goto _out75;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr143;
			}
			case 98: {
				goto _st75;
			}
		}
		goto _st0;
		_ctr143:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 4486 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 4492 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 4498 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 4504 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 4510 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 4516 "gen/ragel/28__cat8_2.c"
		
		goto _st76;
		_st76:
		p+= 1;
		st_case_76:
		if ( p == pe )
			goto _out76;
		if ( ( (*( p))) == 97 ) {
			goto _ctr145;
		}
		goto _st0;
		_ctr145:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 4533 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 4539 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 4545 "gen/ragel/28__cat8_2.c"
		
		goto _st77;
		_ctr181:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 4553 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 4559 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 4565 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 4571 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 4577 "gen/ragel/28__cat8_2.c"
		
		goto _st77;
		_st77:
		p+= 1;
		st_case_77:
		if ( p == pe )
			goto _out77;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr147;
			}
			case 98: {
				goto _st79;
			}
		}
		goto _st0;
		_ctr147:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 4599 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 4605 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 4611 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 4617 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 4623 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 4629 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 4635 "gen/ragel/28__cat8_2.c"
		
		goto _st78;
		_st78:
		p+= 1;
		st_case_78:
		if ( p == pe )
			goto _out78;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr150;
			}
			case 98: {
				goto _st79;
			}
		}
		goto _st0;
		_st79:
		p+= 1;
		st_case_79:
		if ( p == pe )
			goto _out79;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr151;
			}
			case 98: {
				goto _st79;
			}
		}
		goto _st0;
		_ctr151:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 4671 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 4677 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 4683 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 4689 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 4695 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 4701 "gen/ragel/28__cat8_2.c"
		
		goto _st80;
		_st80:
		p+= 1;
		st_case_80:
		if ( p == pe )
			goto _out80;
		if ( ( (*( p))) == 97 ) {
			goto _ctr153;
		}
		goto _st0;
		_ctr153:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 4718 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 4724 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 4730 "gen/ragel/28__cat8_2.c"
		
		goto _st81;
		_ctr189:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 4738 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 4744 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 4750 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 4756 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 4762 "gen/ragel/28__cat8_2.c"
		
		goto _st81;
		_st81:
		p+= 1;
		st_case_81:
		if ( p == pe )
			goto _out81;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr155;
			}
			case 98: {
				goto _st83;
			}
		}
		goto _st0;
		_ctr155:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 4784 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 4790 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 4796 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 4802 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 4808 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 4814 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 4820 "gen/ragel/28__cat8_2.c"
		
		goto _st82;
		_st82:
		p+= 1;
		st_case_82:
		if ( p == pe )
			goto _out82;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr63;
			}
			case 98: {
				goto _st83;
			}
		}
		goto _st0;
		_st83:
		p+= 1;
		st_case_83:
		if ( p == pe )
			goto _out83;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr65;
			}
			case 98: {
				goto _st83;
			}
		}
		goto _st0;
		_st84:
		p+= 1;
		st_case_84:
		if ( p == pe )
			goto _out84;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr158;
			}
			case 98: {
				goto _st84;
			}
		}
		goto _st0;
		_ctr158:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 4870 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 4876 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 4882 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 4888 "gen/ragel/28__cat8_2.c"
		
		goto _st85;
		_st85:
		p+= 1;
		st_case_85:
		if ( p == pe )
			goto _out85;
		if ( ( (*( p))) == 97 ) {
			goto _ctr160;
		}
		goto _st0;
		_ctr160:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 4905 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 4911 "gen/ragel/28__cat8_2.c"
		
		goto _st86;
		_ctr204:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 4919 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 4925 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 4931 "gen/ragel/28__cat8_2.c"
		
		goto _st86;
		_st86:
		p+= 1;
		st_case_86:
		if ( p == pe )
			goto _out86;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr162;
			}
			case 98: {
				goto _st88;
			}
		}
		goto _st0;
		_ctr162:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 4953 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 4959 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 4965 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 4971 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 4977 "gen/ragel/28__cat8_2.c"
		
		goto _st87;
		_st87:
		p+= 1;
		st_case_87:
		if ( p == pe )
			goto _out87;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr165;
			}
			case 98: {
				goto _st88;
			}
		}
		goto _st0;
		_st88:
		p+= 1;
		st_case_88:
		if ( p == pe )
			goto _out88;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr166;
			}
			case 98: {
				goto _st88;
			}
		}
		goto _st0;
		_ctr166:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 5013 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 5019 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 5025 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 5031 "gen/ragel/28__cat8_2.c"
		
		goto _st89;
		_st89:
		p+= 1;
		st_case_89:
		if ( p == pe )
			goto _out89;
		if ( ( (*( p))) == 97 ) {
			goto _ctr168;
		}
		goto _st0;
		_ctr168:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 5048 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 5054 "gen/ragel/28__cat8_2.c"
		
		goto _st90;
		_ctr212:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 5062 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 5068 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 5074 "gen/ragel/28__cat8_2.c"
		
		goto _st90;
		_st90:
		p+= 1;
		st_case_90:
		if ( p == pe )
			goto _out90;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr170;
			}
			case 98: {
				goto _st92;
			}
		}
		goto _st0;
		_ctr170:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 5096 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 5102 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 5108 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 5114 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 5120 "gen/ragel/28__cat8_2.c"
		
		goto _st91;
		_st91:
		p+= 1;
		st_case_91:
		if ( p == pe )
			goto _out91;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr173;
			}
			case 98: {
				goto _st92;
			}
		}
		goto _st0;
		_st92:
		p+= 1;
		st_case_92:
		if ( p == pe )
			goto _out92;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr174;
			}
			case 98: {
				goto _st92;
			}
		}
		goto _st0;
		_ctr174:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 5156 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 5162 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 5168 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 5174 "gen/ragel/28__cat8_2.c"
		
		goto _st93;
		_st93:
		p+= 1;
		st_case_93:
		if ( p == pe )
			goto _out93;
		if ( ( (*( p))) == 97 ) {
			goto _ctr176;
		}
		goto _st0;
		_ctr176:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 5191 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 5197 "gen/ragel/28__cat8_2.c"
		
		goto _st94;
		_ctr220:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 5205 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 5211 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 5217 "gen/ragel/28__cat8_2.c"
		
		goto _st94;
		_st94:
		p+= 1;
		st_case_94:
		if ( p == pe )
			goto _out94;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr178;
			}
			case 98: {
				goto _st96;
			}
		}
		goto _st0;
		_ctr178:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 5239 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 5245 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 5251 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 5257 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 5263 "gen/ragel/28__cat8_2.c"
		
		goto _st95;
		_st95:
		p+= 1;
		st_case_95:
		if ( p == pe )
			goto _out95;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr181;
			}
			case 98: {
				goto _st96;
			}
		}
		goto _st0;
		_st96:
		p+= 1;
		st_case_96:
		if ( p == pe )
			goto _out96;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr182;
			}
			case 98: {
				goto _st96;
			}
		}
		goto _st0;
		_ctr182:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 5299 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 5305 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 5311 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 5317 "gen/ragel/28__cat8_2.c"
		
		goto _st97;
		_st97:
		p+= 1;
		st_case_97:
		if ( p == pe )
			goto _out97;
		if ( ( (*( p))) == 97 ) {
			goto _ctr184;
		}
		goto _st0;
		_ctr184:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 5334 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 5340 "gen/ragel/28__cat8_2.c"
		
		goto _st98;
		_ctr228:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 5348 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 5354 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 5360 "gen/ragel/28__cat8_2.c"
		
		goto _st98;
		_st98:
		p+= 1;
		st_case_98:
		if ( p == pe )
			goto _out98;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr186;
			}
			case 98: {
				goto _st100;
			}
		}
		goto _st0;
		_ctr186:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 5382 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 5388 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 5394 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 5400 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 5406 "gen/ragel/28__cat8_2.c"
		
		goto _st99;
		_st99:
		p+= 1;
		st_case_99:
		if ( p == pe )
			goto _out99;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr189;
			}
			case 98: {
				goto _st100;
			}
		}
		goto _st0;
		_st100:
		p+= 1;
		st_case_100:
		if ( p == pe )
			goto _out100;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr190;
			}
			case 98: {
				goto _st100;
			}
		}
		goto _st0;
		_ctr190:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 5442 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 5448 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 5454 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 5460 "gen/ragel/28__cat8_2.c"
		
		goto _st101;
		_st101:
		p+= 1;
		st_case_101:
		if ( p == pe )
			goto _out101;
		if ( ( (*( p))) == 97 ) {
			goto _ctr192;
		}
		goto _st0;
		_ctr192:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 5477 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 5483 "gen/ragel/28__cat8_2.c"
		
		goto _st102;
		_ctr236:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 5491 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 5497 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 5503 "gen/ragel/28__cat8_2.c"
		
		goto _st102;
		_st102:
		p+= 1;
		st_case_102:
		if ( p == pe )
			goto _out102;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr194;
			}
			case 98: {
				goto _st104;
			}
		}
		goto _st0;
		_ctr194:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 5525 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 5531 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 5537 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 5543 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 5549 "gen/ragel/28__cat8_2.c"
		
		goto _st103;
		_st103:
		p+= 1;
		st_case_103:
		if ( p == pe )
			goto _out103;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr69;
			}
			case 98: {
				goto _st104;
			}
		}
		goto _st0;
		_st104:
		p+= 1;
		st_case_104:
		if ( p == pe )
			goto _out104;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr71;
			}
			case 98: {
				goto _st104;
			}
		}
		goto _st0;
		_st105:
		p+= 1;
		st_case_105:
		if ( p == pe )
			goto _out105;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr197;
			}
			case 98: {
				goto _st105;
			}
		}
		goto _st0;
		_ctr197:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a1 = p; }
		
#line 5599 "gen/ragel/28__cat8_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 5605 "gen/ragel/28__cat8_2.c"
		
		goto _st106;
		_st106:
		p+= 1;
		st_case_106:
		if ( p == pe )
			goto _out106;
		if ( ( (*( p))) == 97 ) {
			goto _ctr199;
		}
		goto _st0;
		_ctr199:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 5622 "gen/ragel/28__cat8_2.c"
		
		goto _st107;
		_st107:
		p+= 1;
		st_case_107:
		if ( p == pe )
			goto _out107;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr201;
			}
			case 98: {
				goto _st109;
			}
		}
		goto _st0;
		_ctr201:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b1 = p; }
		
#line 5644 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 5650 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 5656 "gen/ragel/28__cat8_2.c"
		
		goto _st108;
		_st108:
		p+= 1;
		st_case_108:
		if ( p == pe )
			goto _out108;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr204;
			}
			case 98: {
				goto _st109;
			}
		}
		goto _st0;
		_st109:
		p+= 1;
		st_case_109:
		if ( p == pe )
			goto _out109;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr205;
			}
			case 98: {
				goto _st109;
			}
		}
		goto _st0;
		_ctr205:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a2 = p; }
		
#line 5692 "gen/ragel/28__cat8_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 5698 "gen/ragel/28__cat8_2.c"
		
		goto _st110;
		_st110:
		p+= 1;
		st_case_110:
		if ( p == pe )
			goto _out110;
		if ( ( (*( p))) == 97 ) {
			goto _ctr207;
		}
		goto _st0;
		_ctr207:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 5715 "gen/ragel/28__cat8_2.c"
		
		goto _st111;
		_st111:
		p+= 1;
		st_case_111:
		if ( p == pe )
			goto _out111;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr209;
			}
			case 98: {
				goto _st113;
			}
		}
		goto _st0;
		_ctr209:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b2 = p; }
		
#line 5737 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 5743 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 5749 "gen/ragel/28__cat8_2.c"
		
		goto _st112;
		_st112:
		p+= 1;
		st_case_112:
		if ( p == pe )
			goto _out112;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr212;
			}
			case 98: {
				goto _st113;
			}
		}
		goto _st0;
		_st113:
		p+= 1;
		st_case_113:
		if ( p == pe )
			goto _out113;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr213;
			}
			case 98: {
				goto _st113;
			}
		}
		goto _st0;
		_ctr213:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a3 = p; }
		
#line 5785 "gen/ragel/28__cat8_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 5791 "gen/ragel/28__cat8_2.c"
		
		goto _st114;
		_st114:
		p+= 1;
		st_case_114:
		if ( p == pe )
			goto _out114;
		if ( ( (*( p))) == 97 ) {
			goto _ctr215;
		}
		goto _st0;
		_ctr215:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 5808 "gen/ragel/28__cat8_2.c"
		
		goto _st115;
		_st115:
		p+= 1;
		st_case_115:
		if ( p == pe )
			goto _out115;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr217;
			}
			case 98: {
				goto _st117;
			}
		}
		goto _st0;
		_ctr217:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b3 = p; }
		
#line 5830 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 5836 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 5842 "gen/ragel/28__cat8_2.c"
		
		goto _st116;
		_st116:
		p+= 1;
		st_case_116:
		if ( p == pe )
			goto _out116;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr220;
			}
			case 98: {
				goto _st117;
			}
		}
		goto _st0;
		_st117:
		p+= 1;
		st_case_117:
		if ( p == pe )
			goto _out117;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr221;
			}
			case 98: {
				goto _st117;
			}
		}
		goto _st0;
		_ctr221:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a4 = p; }
		
#line 5878 "gen/ragel/28__cat8_2.c"
		
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 5884 "gen/ragel/28__cat8_2.c"
		
		goto _st118;
		_st118:
		p+= 1;
		st_case_118:
		if ( p == pe )
			goto _out118;
		if ( ( (*( p))) == 97 ) {
			goto _ctr223;
		}
		goto _st0;
		_ctr223:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 5901 "gen/ragel/28__cat8_2.c"
		
		goto _st119;
		_st119:
		p+= 1;
		st_case_119:
		if ( p == pe )
			goto _out119;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr225;
			}
			case 98: {
				goto _st121;
			}
		}
		goto _st0;
		_ctr225:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b4 = p; }
		
#line 5923 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 5929 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 5935 "gen/ragel/28__cat8_2.c"
		
		goto _st120;
		_st120:
		p+= 1;
		st_case_120:
		if ( p == pe )
			goto _out120;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr228;
			}
			case 98: {
				goto _st121;
			}
		}
		goto _st0;
		_st121:
		p+= 1;
		st_case_121:
		if ( p == pe )
			goto _out121;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr229;
			}
			case 98: {
				goto _st121;
			}
		}
		goto _st0;
		_ctr229:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a5 = p; }
		
#line 5971 "gen/ragel/28__cat8_2.c"
		
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 5977 "gen/ragel/28__cat8_2.c"
		
		goto _st122;
		_st122:
		p+= 1;
		st_case_122:
		if ( p == pe )
			goto _out122;
		if ( ( (*( p))) == 97 ) {
			goto _ctr231;
		}
		goto _st0;
		_ctr231:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 5994 "gen/ragel/28__cat8_2.c"
		
		goto _st123;
		_st123:
		p+= 1;
		st_case_123:
		if ( p == pe )
			goto _out123;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr233;
			}
			case 98: {
				goto _st125;
			}
		}
		goto _st0;
		_ctr233:
		{
#line 14 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b5 = p; }
		
#line 6016 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 6022 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 6028 "gen/ragel/28__cat8_2.c"
		
		goto _st124;
		_st124:
		p+= 1;
		st_case_124:
		if ( p == pe )
			goto _out124;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr236;
			}
			case 98: {
				goto _st125;
			}
		}
		goto _st0;
		_st125:
		p+= 1;
		st_case_125:
		if ( p == pe )
			goto _out125;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr237;
			}
			case 98: {
				goto _st125;
			}
		}
		goto _st0;
		_ctr237:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a6 = p; }
		
#line 6064 "gen/ragel/28__cat8_2.c"
		
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 6070 "gen/ragel/28__cat8_2.c"
		
		goto _st126;
		_st126:
		p+= 1;
		st_case_126:
		if ( p == pe )
			goto _out126;
		if ( ( (*( p))) == 97 ) {
			goto _ctr239;
		}
		goto _st0;
		_ctr239:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 6087 "gen/ragel/28__cat8_2.c"
		
		goto _st127;
		_st127:
		p+= 1;
		st_case_127:
		if ( p == pe )
			goto _out127;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr241;
			}
			case 98: {
				goto _st129;
			}
		}
		goto _st0;
		_ctr241:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b6 = p; }
		
#line 6109 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			a7 = p; }
		
#line 6115 "gen/ragel/28__cat8_2.c"
		
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
			b7 = p; }
		
#line 6121 "gen/ragel/28__cat8_2.c"
		
		goto _st128;
		_st128:
		p+= 1;
		st_case_128:
		if ( p == pe )
			goto _out128;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr75;
			}
			case 98: {
				goto _st129;
			}
		}
		goto _st0;
		_st129:
		p+= 1;
		st_case_129:
		if ( p == pe )
			goto _out129;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr77;
			}
			case 98: {
				goto _st129;
			}
		}
		goto _st0;
		_out130: cs = 130; goto _out; 
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
		_out73: cs = 73; goto _out; 
		_out74: cs = 74; goto _out; 
		_out75: cs = 75; goto _out; 
		_out76: cs = 76; goto _out; 
		_out77: cs = 77; goto _out; 
		_out78: cs = 78; goto _out; 
		_out79: cs = 79; goto _out; 
		_out80: cs = 80; goto _out; 
		_out81: cs = 81; goto _out; 
		_out82: cs = 82; goto _out; 
		_out83: cs = 83; goto _out; 
		_out84: cs = 84; goto _out; 
		_out85: cs = 85; goto _out; 
		_out86: cs = 86; goto _out; 
		_out87: cs = 87; goto _out; 
		_out88: cs = 88; goto _out; 
		_out89: cs = 89; goto _out; 
		_out90: cs = 90; goto _out; 
		_out91: cs = 91; goto _out; 
		_out92: cs = 92; goto _out; 
		_out93: cs = 93; goto _out; 
		_out94: cs = 94; goto _out; 
		_out95: cs = 95; goto _out; 
		_out96: cs = 96; goto _out; 
		_out97: cs = 97; goto _out; 
		_out98: cs = 98; goto _out; 
		_out99: cs = 99; goto _out; 
		_out100: cs = 100; goto _out; 
		_out101: cs = 101; goto _out; 
		_out102: cs = 102; goto _out; 
		_out103: cs = 103; goto _out; 
		_out104: cs = 104; goto _out; 
		_out105: cs = 105; goto _out; 
		_out106: cs = 106; goto _out; 
		_out107: cs = 107; goto _out; 
		_out108: cs = 108; goto _out; 
		_out109: cs = 109; goto _out; 
		_out110: cs = 110; goto _out; 
		_out111: cs = 111; goto _out; 
		_out112: cs = 112; goto _out; 
		_out113: cs = 113; goto _out; 
		_out114: cs = 114; goto _out; 
		_out115: cs = 115; goto _out; 
		_out116: cs = 116; goto _out; 
		_out117: cs = 117; goto _out; 
		_out118: cs = 118; goto _out; 
		_out119: cs = 119; goto _out; 
		_out120: cs = 120; goto _out; 
		_out121: cs = 121; goto _out; 
		_out122: cs = 122; goto _out; 
		_out123: cs = 123; goto _out; 
		_out124: cs = 124; goto _out; 
		_out125: cs = 125; goto _out; 
		_out126: cs = 126; goto _out; 
		_out127: cs = 127; goto _out; 
		_out128: cs = 128; goto _out; 
		_out129: cs = 129; goto _out; 
		_out: {}
	}
	
#line 43 "../../../benchmarks/submatch_dfa_aot/src/ragel/28__cat8_2.rl"
	
	
	in->p = p;
	in->pe = pe;
}
