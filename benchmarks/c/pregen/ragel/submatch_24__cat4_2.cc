#line 1 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
#include "ragel/base.h"

namespace ragel_submatch_24__cat4_2 {
	
	const char *delim = "\n";
	
	
#line 23 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"

	

#line 11 "gen/ragel/submatch_24__cat4_2.cc"
static const int abcd_start = 34;
	static const int abcd_first_final = 34;
	static const int abcd_error = 0;
	
	static const int abcd_en_main = 34;
	
	
#line 25 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"

	
	static int lex(Input *in, int count) {
		char *p = in->p;
		char *pe = in->pe;
		const char
		*a0, *a1, *a2, *a3,
		*b0, *b1, *b2, *b3;
		int cs;
		

#line 28 "gen/ragel/submatch_24__cat4_2.cc"
	{
			cs = (int)abcd_start;
		}
		
#line 35 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"


#line 33 "gen/ragel/submatch_24__cat4_2.cc"
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
#line 15 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				
				OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
				OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
				OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
				OUTS(a3, b3); OUTC('.'); OUTS(b3, p + 1);
			}
			
#line 116 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a0 = p; }
			
#line 135 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 11 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b0 = p; }
			
#line 140 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b0 = p; }
			
#line 156 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b0 = p; }
			
#line 177 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a1 = p; }
			
#line 182 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 187 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b0 = p; }
			
#line 208 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a1 = p; }
			
#line 213 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 218 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b0 = p; }
			
#line 239 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a1 = p; }
			
#line 244 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 249 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a2 = p; }
			
#line 254 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 259 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b0 = p; }
			
#line 280 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a1 = p; }
			
#line 285 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 290 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a2 = p; }
			
#line 295 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 300 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b0 = p; }
			
#line 321 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a1 = p; }
			
#line 326 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 331 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a2 = p; }
			
#line 336 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 341 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a3 = p; }
			
#line 346 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b3 = p; }
			
#line 351 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 11 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b0 = p; }
			
#line 372 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a1 = p; }
			
#line 377 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 382 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a2 = p; }
			
#line 387 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 392 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a3 = p; }
			
#line 397 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b3 = p; }
			
#line 402 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a1 = p; }
			
#line 443 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 448 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a2 = p; }
			
#line 453 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 458 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a3 = p; }
			
#line 463 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b3 = p; }
			
#line 468 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 484 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 489 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b3 = p; }
			
#line 494 "gen/ragel/submatch_24__cat4_2.cc"

			goto _st11;
			_ctr25:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 501 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a2 = p; }
			
#line 506 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 511 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a3 = p; }
			
#line 516 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b3 = p; }
			
#line 521 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a2 = p; }
			
#line 562 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 567 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a3 = p; }
			
#line 572 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b3 = p; }
			
#line 577 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 593 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b3 = p; }
			
#line 598 "gen/ragel/submatch_24__cat4_2.cc"

			goto _st14;
			_ctr31:
				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 605 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a3 = p; }
			
#line 610 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b3 = p; }
			
#line 615 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a3 = p; }
			
#line 656 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b3 = p; }
			
#line 661 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b3 = p; }
			
#line 677 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a1 = p; }
			
#line 743 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 748 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a2 = p; }
			
#line 753 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 758 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 774 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 779 "gen/ragel/submatch_24__cat4_2.cc"

			goto _st22;
			_ctr52:
				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 786 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a2 = p; }
			
#line 791 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 796 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 817 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a2 = p; }
			
#line 822 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 827 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a3 = p; }
			
#line 832 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b3 = p; }
			
#line 837 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a1 = p; }
			
#line 886 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 891 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 907 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 12 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b1 = p; }
			
#line 928 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a2 = p; }
			
#line 933 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 938 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a2 = p; }
			
#line 973 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 978 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 994 "gen/ragel/submatch_24__cat4_2.cc"

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
#line 13 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b2 = p; }
			
#line 1015 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				a3 = p; }
			
#line 1020 "gen/ragel/submatch_24__cat4_2.cc"

				{
#line 14 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"
				b3 = p; }
			
#line 1025 "gen/ragel/submatch_24__cat4_2.cc"

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
		
#line 36 "../../../benchmarks/c/src/ragel/submatch_24__cat4_2.rl"

		
		in->p = p;
		in->pe = pe;
		
		return count;
	}
	
	RAGEL_BENCH()
	RAGEL_TEST()
	
} // namespace ragel_submatch_24__cat4_2
