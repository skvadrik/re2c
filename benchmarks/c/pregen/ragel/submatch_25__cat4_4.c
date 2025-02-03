#line 1 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 21 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"



#line 9 "gen/ragel/submatch_25__cat4_4.c"
static const int abcd_start = 60;
static const int abcd_first_final = 60;
static const int abcd_error = 0;

static const int abcd_en_main = 60;


#line 23 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*a0, *a1, *a2, *a3,
	*b0, *b1, *b2, *b3;
	int cs;
	

#line 27 "gen/ragel/submatch_25__cat4_4.c"
	{
		cs = (int)abcd_start;
	}
	
#line 34 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"


#line 32 "gen/ragel/submatch_25__cat4_4.c"
{
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
		_ctr35:
			{
#line 13 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 167 "gen/ragel/submatch_25__cat4_4.c"

		goto _st60;
		_st60:
		p+= 1;
		st_case_60:
		if ( p == pe )
			goto _out60;
		if ( ( (*( p))) == 97 ) {
			goto _ctr113;
		}
		goto _st0;
		_st0:
		st_case_0:
		goto _out0;
		_ctr113:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a0 = p; }
		
#line 186 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 191 "gen/ragel/submatch_25__cat4_4.c"

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
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 207 "gen/ragel/submatch_25__cat4_4.c"

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
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 223 "gen/ragel/submatch_25__cat4_4.c"

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
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 239 "gen/ragel/submatch_25__cat4_4.c"

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
				goto _st43;
			}
		}
		goto _st0;
		_ctr8:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 260 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 265 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 270 "gen/ragel/submatch_25__cat4_4.c"

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
				goto _st43;
			}
		}
		goto _st0;
		_ctr11:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 291 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 296 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 301 "gen/ragel/submatch_25__cat4_4.c"

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
				goto _st43;
			}
		}
		goto _st0;
		_ctr13:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 322 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 327 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 332 "gen/ragel/submatch_25__cat4_4.c"

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
				goto _st43;
			}
		}
		goto _st0;
		_ctr15:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 353 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 358 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 363 "gen/ragel/submatch_25__cat4_4.c"

		goto _st8;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr17;
			}
			case 98: {
				goto _st34;
			}
		}
		goto _st0;
		_ctr17:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 384 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 389 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 394 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 399 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 404 "gen/ragel/submatch_25__cat4_4.c"

		goto _st9;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr20;
			}
			case 98: {
				goto _st34;
			}
		}
		goto _st0;
		_ctr20:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 425 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 430 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 435 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 440 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 445 "gen/ragel/submatch_25__cat4_4.c"

		goto _st10;
		_st10:
		p+= 1;
		st_case_10:
		if ( p == pe )
			goto _out10;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr22;
			}
			case 98: {
				goto _st34;
			}
		}
		goto _st0;
		_ctr22:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 466 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 471 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 476 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 481 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 486 "gen/ragel/submatch_25__cat4_4.c"

		goto _st11;
		_st11:
		p+= 1;
		st_case_11:
		if ( p == pe )
			goto _out11;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr24;
			}
			case 98: {
				goto _st34;
			}
		}
		goto _st0;
		_ctr24:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 507 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 512 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 517 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 522 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 527 "gen/ragel/submatch_25__cat4_4.c"

		goto _st12;
		_st12:
		p+= 1;
		st_case_12:
		if ( p == pe )
			goto _out12;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr26;
			}
			case 98: {
				goto _st33;
			}
		}
		goto _st0;
		_ctr26:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 548 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 553 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 558 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 563 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 568 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 573 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 578 "gen/ragel/submatch_25__cat4_4.c"

		goto _st13;
		_st13:
		p+= 1;
		st_case_13:
		if ( p == pe )
			goto _out13;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr29;
			}
			case 98: {
				goto _st33;
			}
		}
		goto _st0;
		_ctr29:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 599 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 604 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 609 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 614 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 619 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 624 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 629 "gen/ragel/submatch_25__cat4_4.c"

		goto _st14;
		_st14:
		p+= 1;
		st_case_14:
		if ( p == pe )
			goto _out14;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr31;
			}
			case 98: {
				goto _st33;
			}
		}
		goto _st0;
		_ctr31:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 650 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 655 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 660 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 665 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 670 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 675 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 680 "gen/ragel/submatch_25__cat4_4.c"

		goto _st15;
		_st15:
		p+= 1;
		st_case_15:
		if ( p == pe )
			goto _out15;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr33;
			}
			case 98: {
				goto _st33;
			}
		}
		goto _st0;
		_ctr33:
			{
#line 9 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b0 = p; }
		
#line 701 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 706 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 711 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 716 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 721 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 726 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 731 "gen/ragel/submatch_25__cat4_4.c"

		goto _st16;
		_st16:
		p+= 1;
		st_case_16:
		if ( p == pe )
			goto _out16;
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
		goto _st0;
		_st17:
		p+= 1;
		st_case_17:
		if ( p == pe )
			goto _out17;
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
		goto _st0;
		_ctr37:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 772 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 777 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 782 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 787 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 792 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 797 "gen/ragel/submatch_25__cat4_4.c"

		goto _st18;
		_st18:
		p+= 1;
		st_case_18:
		if ( p == pe )
			goto _out18;
		if ( ( (*( p))) == 97 ) {
			goto _ctr39;
		}
		goto _st0;
		_ctr39:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 813 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 818 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 823 "gen/ragel/submatch_25__cat4_4.c"

		goto _st19;
		_st19:
		p+= 1;
		st_case_19:
		if ( p == pe )
			goto _out19;
		if ( ( (*( p))) == 97 ) {
			goto _ctr41;
		}
		goto _st0;
		_ctr41:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 839 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 844 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 849 "gen/ragel/submatch_25__cat4_4.c"

		goto _st20;
		_st20:
		p+= 1;
		st_case_20:
		if ( p == pe )
			goto _out20;
		if ( ( (*( p))) == 97 ) {
			goto _ctr43;
		}
		goto _st0;
		_ctr43:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 865 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 870 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 875 "gen/ragel/submatch_25__cat4_4.c"

		goto _st21;
		_ctr45:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 882 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 887 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 892 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 897 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 902 "gen/ragel/submatch_25__cat4_4.c"

		goto _st21;
		_st21:
		p+= 1;
		st_case_21:
		if ( p == pe )
			goto _out21;
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
		goto _st0;
		_st22:
		p+= 1;
		st_case_22:
		if ( p == pe )
			goto _out22;
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
		goto _st0;
		_ctr47:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 943 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 948 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 953 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 958 "gen/ragel/submatch_25__cat4_4.c"

		goto _st23;
		_st23:
		p+= 1;
		st_case_23:
		if ( p == pe )
			goto _out23;
		if ( ( (*( p))) == 97 ) {
			goto _ctr49;
		}
		goto _st0;
		_ctr49:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 974 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 979 "gen/ragel/submatch_25__cat4_4.c"

		goto _st24;
		_st24:
		p+= 1;
		st_case_24:
		if ( p == pe )
			goto _out24;
		if ( ( (*( p))) == 97 ) {
			goto _ctr51;
		}
		goto _st0;
		_ctr51:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 995 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 1000 "gen/ragel/submatch_25__cat4_4.c"

		goto _st25;
		_st25:
		p+= 1;
		st_case_25:
		if ( p == pe )
			goto _out25;
		if ( ( (*( p))) == 97 ) {
			goto _ctr53;
		}
		goto _st0;
		_ctr53:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1016 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 1021 "gen/ragel/submatch_25__cat4_4.c"

		goto _st26;
		_ctr55:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1028 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 1033 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 1038 "gen/ragel/submatch_25__cat4_4.c"

		goto _st26;
		_st26:
		p+= 1;
		st_case_26:
		if ( p == pe )
			goto _out26;
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
		goto _st0;
		_st27:
		p+= 1;
		st_case_27:
		if ( p == pe )
			goto _out27;
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
		goto _st0;
		_ctr57:
			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 1079 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 1084 "gen/ragel/submatch_25__cat4_4.c"

		goto _st28;
		_st28:
		p+= 1;
		st_case_28:
		if ( p == pe )
			goto _out28;
		if ( ( (*( p))) == 97 ) {
			goto _ctr59;
		}
		goto _st0;
		_ctr59:
			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 1100 "gen/ragel/submatch_25__cat4_4.c"

		goto _st29;
		_st29:
		p+= 1;
		st_case_29:
		if ( p == pe )
			goto _out29;
		if ( ( (*( p))) == 97 ) {
			goto _ctr61;
		}
		goto _st0;
		_ctr61:
			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 1116 "gen/ragel/submatch_25__cat4_4.c"

		goto _st30;
		_st30:
		p+= 1;
		st_case_30:
		if ( p == pe )
			goto _out30;
		if ( ( (*( p))) == 97 ) {
			goto _ctr63;
		}
		goto _st0;
		_ctr63:
			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 1132 "gen/ragel/submatch_25__cat4_4.c"

		goto _st31;
		_st31:
		p+= 1;
		st_case_31:
		if ( p == pe )
			goto _out31;
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
		goto _st0;
		_st32:
		p+= 1;
		st_case_32:
		if ( p == pe )
			goto _out32;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr35;
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
				goto _ctr37;
			}
			case 98: {
				goto _st33;
			}
		}
		goto _st0;
		_st34:
		p+= 1;
		st_case_34:
		if ( p == pe )
			goto _out34;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr66;
			}
			case 98: {
				goto _st34;
			}
		}
		goto _st0;
		_ctr66:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 1198 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1203 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 1208 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1213 "gen/ragel/submatch_25__cat4_4.c"

		goto _st35;
		_st35:
		p+= 1;
		st_case_35:
		if ( p == pe )
			goto _out35;
		if ( ( (*( p))) == 97 ) {
			goto _ctr68;
		}
		goto _st0;
		_ctr68:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1229 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1234 "gen/ragel/submatch_25__cat4_4.c"

		goto _st36;
		_st36:
		p+= 1;
		st_case_36:
		if ( p == pe )
			goto _out36;
		if ( ( (*( p))) == 97 ) {
			goto _ctr70;
		}
		goto _st0;
		_ctr70:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1250 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1255 "gen/ragel/submatch_25__cat4_4.c"

		goto _st37;
		_st37:
		p+= 1;
		st_case_37:
		if ( p == pe )
			goto _out37;
		if ( ( (*( p))) == 97 ) {
			goto _ctr72;
		}
		goto _st0;
		_ctr72:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1271 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1276 "gen/ragel/submatch_25__cat4_4.c"

		goto _st38;
		_ctr96:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1283 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 1288 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1293 "gen/ragel/submatch_25__cat4_4.c"

		goto _st38;
		_st38:
		p+= 1;
		st_case_38:
		if ( p == pe )
			goto _out38;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr74;
			}
			case 98: {
				goto _st42;
			}
		}
		goto _st0;
		_ctr74:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1314 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 1319 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1324 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 1329 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 1334 "gen/ragel/submatch_25__cat4_4.c"

		goto _st39;
		_st39:
		p+= 1;
		st_case_39:
		if ( p == pe )
			goto _out39;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr77;
			}
			case 98: {
				goto _st42;
			}
		}
		goto _st0;
		_ctr77:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1355 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 1360 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1365 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 1370 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 1375 "gen/ragel/submatch_25__cat4_4.c"

		goto _st40;
		_st40:
		p+= 1;
		st_case_40:
		if ( p == pe )
			goto _out40;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr79;
			}
			case 98: {
				goto _st42;
			}
		}
		goto _st0;
		_ctr79:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1396 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 1401 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1406 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 1411 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 1416 "gen/ragel/submatch_25__cat4_4.c"

		goto _st41;
		_st41:
		p+= 1;
		st_case_41:
		if ( p == pe )
			goto _out41;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr45;
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
				goto _ctr47;
			}
			case 98: {
				goto _st42;
			}
		}
		goto _st0;
		_st43:
		p+= 1;
		st_case_43:
		if ( p == pe )
			goto _out43;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr81;
			}
			case 98: {
				goto _st43;
			}
		}
		goto _st0;
		_ctr81:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a1 = p; }
		
#line 1465 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1470 "gen/ragel/submatch_25__cat4_4.c"

		goto _st44;
		_st44:
		p+= 1;
		st_case_44:
		if ( p == pe )
			goto _out44;
		if ( ( (*( p))) == 97 ) {
			goto _ctr83;
		}
		goto _st0;
		_ctr83:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1486 "gen/ragel/submatch_25__cat4_4.c"

		goto _st45;
		_st45:
		p+= 1;
		st_case_45:
		if ( p == pe )
			goto _out45;
		if ( ( (*( p))) == 97 ) {
			goto _ctr85;
		}
		goto _st0;
		_ctr85:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1502 "gen/ragel/submatch_25__cat4_4.c"

		goto _st46;
		_st46:
		p+= 1;
		st_case_46:
		if ( p == pe )
			goto _out46;
		if ( ( (*( p))) == 97 ) {
			goto _ctr87;
		}
		goto _st0;
		_ctr87:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1518 "gen/ragel/submatch_25__cat4_4.c"

		goto _st47;
		_st47:
		p+= 1;
		st_case_47:
		if ( p == pe )
			goto _out47;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr89;
			}
			case 98: {
				goto _st51;
			}
		}
		goto _st0;
		_ctr89:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1539 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 1544 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1549 "gen/ragel/submatch_25__cat4_4.c"

		goto _st48;
		_st48:
		p+= 1;
		st_case_48:
		if ( p == pe )
			goto _out48;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr92;
			}
			case 98: {
				goto _st51;
			}
		}
		goto _st0;
		_ctr92:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1570 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 1575 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1580 "gen/ragel/submatch_25__cat4_4.c"

		goto _st49;
		_st49:
		p+= 1;
		st_case_49:
		if ( p == pe )
			goto _out49;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr94;
			}
			case 98: {
				goto _st51;
			}
		}
		goto _st0;
		_ctr94:
			{
#line 10 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b1 = p; }
		
#line 1601 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 1606 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1611 "gen/ragel/submatch_25__cat4_4.c"

		goto _st50;
		_st50:
		p+= 1;
		st_case_50:
		if ( p == pe )
			goto _out50;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr96;
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
				goto _ctr97;
			}
			case 98: {
				goto _st51;
			}
		}
		goto _st0;
		_ctr97:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a2 = p; }
		
#line 1646 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1651 "gen/ragel/submatch_25__cat4_4.c"

		goto _st52;
		_st52:
		p+= 1;
		st_case_52:
		if ( p == pe )
			goto _out52;
		if ( ( (*( p))) == 97 ) {
			goto _ctr99;
		}
		goto _st0;
		_ctr99:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1667 "gen/ragel/submatch_25__cat4_4.c"

		goto _st53;
		_st53:
		p+= 1;
		st_case_53:
		if ( p == pe )
			goto _out53;
		if ( ( (*( p))) == 97 ) {
			goto _ctr101;
		}
		goto _st0;
		_ctr101:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1683 "gen/ragel/submatch_25__cat4_4.c"

		goto _st54;
		_st54:
		p+= 1;
		st_case_54:
		if ( p == pe )
			goto _out54;
		if ( ( (*( p))) == 97 ) {
			goto _ctr103;
		}
		goto _st0;
		_ctr103:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1699 "gen/ragel/submatch_25__cat4_4.c"

		goto _st55;
		_st55:
		p+= 1;
		st_case_55:
		if ( p == pe )
			goto _out55;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr105;
			}
			case 98: {
				goto _st59;
			}
		}
		goto _st0;
		_ctr105:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1720 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 1725 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 1730 "gen/ragel/submatch_25__cat4_4.c"

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
				goto _st59;
			}
		}
		goto _st0;
		_ctr108:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1751 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 1756 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 1761 "gen/ragel/submatch_25__cat4_4.c"

		goto _st57;
		_st57:
		p+= 1;
		st_case_57:
		if ( p == pe )
			goto _out57;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr110;
			}
			case 98: {
				goto _st59;
			}
		}
		goto _st0;
		_ctr110:
			{
#line 11 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b2 = p; }
		
#line 1782 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			a3 = p; }
		
#line 1787 "gen/ragel/submatch_25__cat4_4.c"

			{
#line 12 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"
			b3 = p; }
		
#line 1792 "gen/ragel/submatch_25__cat4_4.c"

		goto _st58;
		_st58:
		p+= 1;
		st_case_58:
		if ( p == pe )
			goto _out58;
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr55;
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
				goto _ctr57;
			}
			case 98: {
				goto _st59;
			}
		}
		goto _st0;
		_out60: cs = 60; goto _out; 
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
		_out: {}
	}
	
#line 35 "../../../benchmarks/c/src/ragel/submatch_25__cat4_4.rl"

	
	in->p = p;
	in->pe = pe;
}
