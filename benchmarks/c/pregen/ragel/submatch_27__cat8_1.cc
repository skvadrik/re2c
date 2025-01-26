#line 1 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
#include "ragel/base.h"

namespace ragel_submatch_27__cat8_1 {
	
	const char *delim = "\n";
	
	
#line 31 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"

	

#line 11 "gen/ragel/submatch_27__cat8_1.cc"
static const int abcd_start = 73;
	static const int abcd_first_final = 73;
	static const int abcd_error = 0;
	
	static const int abcd_en_main = 73;
	
	
#line 33 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *pe = in->pe;
		const char
		*a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
		*b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
		int cs;
		

#line 28 "gen/ragel/submatch_27__cat8_1.cc"
	{
			cs = (int)abcd_start;
		}
		
#line 43 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"


#line 33 "gen/ragel/submatch_27__cat8_1.cc"
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
#line 19 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
				OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
				OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
				OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
				OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
			}
			
#line 198 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a0 = p; }
			
#line 217 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b0 = p; }
			
#line 222 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b0 = p; }
			
#line 243 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a1 = p; }
			
#line 248 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 253 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b0 = p; }
			
#line 274 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a1 = p; }
			
#line 279 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 284 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 289 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 294 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b0 = p; }
			
#line 315 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a1 = p; }
			
#line 320 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 325 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 330 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 335 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 340 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 345 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b0 = p; }
			
#line 366 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a1 = p; }
			
#line 371 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 376 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 381 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 386 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 391 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 396 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 401 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 406 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b0 = p; }
			
#line 427 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a1 = p; }
			
#line 432 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 437 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 442 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 447 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 452 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 457 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 462 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 467 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 472 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 477 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b0 = p; }
			
#line 498 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a1 = p; }
			
#line 503 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 508 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 513 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 518 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 523 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 528 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 533 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 538 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 543 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 548 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 553 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 558 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b0 = p; }
			
#line 579 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a1 = p; }
			
#line 584 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 589 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 594 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 599 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 604 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 609 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 614 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 619 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 624 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 629 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 634 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 639 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a7 = p; }
			
#line 644 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 649 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a1 = p; }
			
#line 690 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 695 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 700 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 705 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 710 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 715 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 720 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 725 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 730 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 735 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 740 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 745 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a7 = p; }
			
#line 750 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 755 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st10;
			_ctr27:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 762 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 767 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 772 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 777 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 782 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 787 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 792 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 797 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 802 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 807 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 812 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a7 = p; }
			
#line 817 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 822 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 863 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 868 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 873 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 878 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 883 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 888 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 893 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 898 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 903 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 908 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a7 = p; }
			
#line 913 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 918 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st12;
			_ctr31:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 925 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 930 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 935 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 940 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 945 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 950 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 955 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 960 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 965 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a7 = p; }
			
#line 970 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 975 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 1016 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 1021 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 1026 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 1031 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 1036 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 1041 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 1046 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 1051 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a7 = p; }
			
#line 1056 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 1061 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st14;
			_ctr35:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 1068 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 1073 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 1078 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 1083 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 1088 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 1093 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 1098 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a7 = p; }
			
#line 1103 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 1108 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 1149 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 1154 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 1159 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 1164 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 1169 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 1174 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a7 = p; }
			
#line 1179 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 1184 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st16;
			_ctr39:
				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 1191 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 1196 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 1201 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 1206 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 1211 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a7 = p; }
			
#line 1216 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 1221 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 1262 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 1267 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 1272 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 1277 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a7 = p; }
			
#line 1282 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 1287 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st18;
			_ctr43:
				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 1294 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 1299 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 1304 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a7 = p; }
			
#line 1309 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 1314 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 1355 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 1360 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a7 = p; }
			
#line 1365 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 1370 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st20;
			_ctr47:
				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 1377 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a7 = p; }
			
#line 1382 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 1387 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a7 = p; }
			
#line 1428 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 1433 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st22;
			_ctr51:
				{
#line 18 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b7 = p; }
			
#line 1440 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a1 = p; }
			
#line 1506 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 1511 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 1516 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 1521 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 1526 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 1531 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 1536 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 1541 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 1546 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 1551 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 1556 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 1561 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st26;
			_ctr58:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 1568 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 1573 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 1578 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 1583 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 1588 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 1593 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 1598 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 1603 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 1608 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 1613 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 1618 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a1 = p; }
			
#line 1667 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 1672 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 1677 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 1682 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 1687 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 1692 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 1697 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 1702 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 1707 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 1712 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st29;
			_ctr65:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 1719 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 1724 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 1729 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 1734 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 1739 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 1744 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 1749 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 1754 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 1759 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 1794 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 1799 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 1804 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 1809 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 1814 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 1819 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 1824 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 1829 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 1834 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 1839 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st31;
			_ctr69:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 1846 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 1851 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 1856 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 1861 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 1866 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 1871 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 1876 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 1881 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 1886 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a1 = p; }
			
#line 1935 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 1940 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 1945 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 1950 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 1955 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 1960 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 1965 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 1970 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st34;
			_ctr76:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 1977 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 1982 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 1987 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 1992 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 1997 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 2002 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2007 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 2042 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 2047 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 2052 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 2057 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 2062 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2067 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 2072 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 2077 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st36;
			_ctr80:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 2084 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 2089 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 2094 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 2099 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2104 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 2109 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 2114 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 2149 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 2154 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 2159 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2164 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 2169 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 2174 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 2179 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 2184 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st38;
			_ctr84:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 2191 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 2196 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2201 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 2206 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 2211 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 2216 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 2221 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a1 = p; }
			
#line 2270 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 2275 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 2280 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 2285 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 2290 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 2295 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st41;
			_ctr91:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 2302 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 2307 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 2312 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 2317 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 2322 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 2357 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 2362 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 2367 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 2372 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 2377 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2382 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st43;
			_ctr95:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 2389 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 2394 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 2399 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 2404 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2409 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 2444 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 2449 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 2454 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2459 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 2464 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 2469 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st45;
			_ctr99:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 2476 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 2481 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2486 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 2491 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 2496 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 2531 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2536 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 2541 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 2546 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 2551 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 2556 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st47;
			_ctr103:
				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2563 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 2568 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 2573 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 2578 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 2583 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a1 = p; }
			
#line 2632 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 2637 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 2642 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 2647 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st50;
			_ctr110:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 2654 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 2659 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 2664 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 2699 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 2704 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 2709 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 2714 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st52;
			_ctr114:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 2721 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 2726 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 2731 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 2766 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 2771 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 2776 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2781 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st54;
			_ctr118:
				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 2788 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 2793 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2798 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 2833 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2838 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 2843 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 2848 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st56;
			_ctr122:
				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 2855 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 2860 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 2865 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 2900 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 2905 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 2910 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 2915 "gen/ragel/submatch_27__cat8_1.cc"

			goto _st58;
			_ctr126:
				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 2922 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 2927 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 2932 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a1 = p; }
			
#line 2981 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b1 = p; }
			
#line 2986 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a2 = p; }
			
#line 3021 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b2 = p; }
			
#line 3026 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a3 = p; }
			
#line 3061 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b3 = p; }
			
#line 3066 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a4 = p; }
			
#line 3101 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 15 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b4 = p; }
			
#line 3106 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a5 = p; }
			
#line 3141 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 16 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b5 = p; }
			
#line 3146 "gen/ragel/submatch_27__cat8_1.cc"

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
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				a6 = p; }
			
#line 3181 "gen/ragel/submatch_27__cat8_1.cc"

				{
#line 17 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"
				b6 = p; }
			
#line 3186 "gen/ragel/submatch_27__cat8_1.cc"

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
		
#line 44 "../../../benchmarks/c/src/ragel/submatch_27__cat8_1.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH_AND_TEST()
	
} // namespace ragel_submatch_27__cat8_1
