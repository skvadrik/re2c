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
		if ( p == pe )
			goto _test_eof;
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
		goto st_out;
		_ctr19:
		{
#line 13 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			
			outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
			outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
			outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
			outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
		}
		
#line 128 "gen/ragel/24__cat4_2.c"
		
		goto _st34;
		_st34:
		p+= 1;
		if ( p == pe )
			goto _test_eof34;
		st_case_34:
		if ( ( (*( p))) == 97 ) {
			goto _ctr61;
		}
		{
			goto _st0;
		}
		st_case_0:
		_st0:
		cs = 0;
		goto _pop;
		_ctr61:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a0 = p; }
		
#line 151 "gen/ragel/24__cat4_2.c"
		
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 157 "gen/ragel/24__cat4_2.c"
		
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
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 176 "gen/ragel/24__cat4_2.c"
		
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
				goto _st25;
			}
		}
		{
			goto _st0;
		}
		_ctr4:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 200 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 206 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 212 "gen/ragel/24__cat4_2.c"
		
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
				goto _st25;
			}
		}
		{
			goto _st0;
		}
		_ctr7:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 236 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 242 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 248 "gen/ragel/24__cat4_2.c"
		
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
				goto _st20;
			}
		}
		{
			goto _st0;
		}
		_ctr9:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 272 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 278 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 284 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 290 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 296 "gen/ragel/24__cat4_2.c"
		
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
				goto _st20;
			}
		}
		{
			goto _st0;
		}
		_ctr12:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 320 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 326 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 332 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 338 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 344 "gen/ragel/24__cat4_2.c"
		
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
				goto _st19;
			}
		}
		{
			goto _st0;
		}
		_ctr14:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 368 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 374 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 380 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 386 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 392 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 398 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 404 "gen/ragel/24__cat4_2.c"
		
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
				goto _st19;
			}
		}
		{
			goto _st0;
		}
		_ctr17:
		{
#line 9 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b0 = p; }
		
#line 428 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 434 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 440 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 446 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 452 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 458 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 464 "gen/ragel/24__cat4_2.c"
		
		goto _st8;
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
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
				goto _ctr19;
			}
			case 97: {
				goto _ctr21;
			}
			case 98: {
				goto _st9;
			}
		}
		{
			goto _st0;
		}
		_ctr21:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 510 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 516 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 522 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 528 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 534 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 540 "gen/ragel/24__cat4_2.c"
		
		goto _st10;
		_st10:
		p+= 1;
		if ( p == pe )
			goto _test_eof10;
		st_case_10:
		if ( ( (*( p))) == 97 ) {
			goto _ctr23;
		}
		{
			goto _st0;
		}
		_ctr23:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 559 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 565 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 571 "gen/ragel/24__cat4_2.c"
		
		goto _st11;
		_ctr25:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 579 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 585 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 591 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 597 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 603 "gen/ragel/24__cat4_2.c"
		
		goto _st11;
		_st11:
		p+= 1;
		if ( p == pe )
			goto _test_eof11;
		st_case_11:
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
		{
			goto _st0;
		}
		_st12:
		p+= 1;
		if ( p == pe )
			goto _test_eof12;
		st_case_12:
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
		{
			goto _st0;
		}
		_ctr27:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 649 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 655 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 661 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 667 "gen/ragel/24__cat4_2.c"
		
		goto _st13;
		_st13:
		p+= 1;
		if ( p == pe )
			goto _test_eof13;
		st_case_13:
		if ( ( (*( p))) == 97 ) {
			goto _ctr29;
		}
		{
			goto _st0;
		}
		_ctr29:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 686 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 692 "gen/ragel/24__cat4_2.c"
		
		goto _st14;
		_ctr31:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 700 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 706 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 712 "gen/ragel/24__cat4_2.c"
		
		goto _st14;
		_st14:
		p+= 1;
		if ( p == pe )
			goto _test_eof14;
		st_case_14:
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
				goto _ctr19;
			}
			case 97: {
				goto _ctr33;
			}
			case 98: {
				goto _st15;
			}
		}
		{
			goto _st0;
		}
		_ctr33:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 758 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 764 "gen/ragel/24__cat4_2.c"
		
		goto _st16;
		_st16:
		p+= 1;
		if ( p == pe )
			goto _test_eof16;
		st_case_16:
		if ( ( (*( p))) == 97 ) {
			goto _ctr35;
		}
		{
			goto _st0;
		}
		_ctr35:
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 783 "gen/ragel/24__cat4_2.c"
		
		goto _st17;
		_st17:
		p+= 1;
		if ( p == pe )
			goto _test_eof17;
		st_case_17:
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
		{
			goto _st0;
		}
		_st18:
		p+= 1;
		if ( p == pe )
			goto _test_eof18;
		st_case_18:
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr19;
			}
			case 98: {
				goto _st18;
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
			case 97: {
				goto _ctr21;
			}
			case 98: {
				goto _st19;
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
			case 97: {
				goto _ctr38;
			}
			case 98: {
				goto _st20;
			}
		}
		{
			goto _st0;
		}
		_ctr38:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 858 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 864 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 870 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 876 "gen/ragel/24__cat4_2.c"
		
		goto _st21;
		_st21:
		p+= 1;
		if ( p == pe )
			goto _test_eof21;
		st_case_21:
		if ( ( (*( p))) == 97 ) {
			goto _ctr40;
		}
		{
			goto _st0;
		}
		_ctr40:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 895 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 901 "gen/ragel/24__cat4_2.c"
		
		goto _st22;
		_ctr52:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 909 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 915 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 921 "gen/ragel/24__cat4_2.c"
		
		goto _st22;
		_st22:
		p+= 1;
		if ( p == pe )
			goto _test_eof22;
		st_case_22:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr42;
			}
			case 98: {
				goto _st24;
			}
		}
		{
			goto _st0;
		}
		_ctr42:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 945 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 951 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 957 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 963 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 969 "gen/ragel/24__cat4_2.c"
		
		goto _st23;
		_st23:
		p+= 1;
		if ( p == pe )
			goto _test_eof23;
		st_case_23:
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
		_st24:
		p+= 1;
		if ( p == pe )
			goto _test_eof24;
		st_case_24:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr27;
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
				goto _ctr45;
			}
			case 98: {
				goto _st25;
			}
		}
		{
			goto _st0;
		}
		_ctr45:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a1 = p; }
		
#line 1025 "gen/ragel/24__cat4_2.c"
		
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 1031 "gen/ragel/24__cat4_2.c"
		
		goto _st26;
		_st26:
		p+= 1;
		if ( p == pe )
			goto _test_eof26;
		st_case_26:
		if ( ( (*( p))) == 97 ) {
			goto _ctr47;
		}
		{
			goto _st0;
		}
		_ctr47:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 1050 "gen/ragel/24__cat4_2.c"
		
		goto _st27;
		_st27:
		p+= 1;
		if ( p == pe )
			goto _test_eof27;
		st_case_27:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr49;
			}
			case 98: {
				goto _st29;
			}
		}
		{
			goto _st0;
		}
		_ctr49:
		{
#line 10 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b1 = p; }
		
#line 1074 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 1080 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 1086 "gen/ragel/24__cat4_2.c"
		
		goto _st28;
		_st28:
		p+= 1;
		if ( p == pe )
			goto _test_eof28;
		st_case_28:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr52;
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
			case 97: {
				goto _ctr53;
			}
			case 98: {
				goto _st29;
			}
		}
		{
			goto _st0;
		}
		_ctr53:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a2 = p; }
		
#line 1126 "gen/ragel/24__cat4_2.c"
		
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 1132 "gen/ragel/24__cat4_2.c"
		
		goto _st30;
		_st30:
		p+= 1;
		if ( p == pe )
			goto _test_eof30;
		st_case_30:
		if ( ( (*( p))) == 97 ) {
			goto _ctr55;
		}
		{
			goto _st0;
		}
		_ctr55:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 1151 "gen/ragel/24__cat4_2.c"
		
		goto _st31;
		_st31:
		p+= 1;
		if ( p == pe )
			goto _test_eof31;
		st_case_31:
		switch( ( (*( p))) ) {
			case 97: {
				goto _ctr57;
			}
			case 98: {
				goto _st33;
			}
		}
		{
			goto _st0;
		}
		_ctr57:
		{
#line 11 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b2 = p; }
		
#line 1175 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			a3 = p; }
		
#line 1181 "gen/ragel/24__cat4_2.c"
		
		{
#line 12 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
			b3 = p; }
		
#line 1187 "gen/ragel/24__cat4_2.c"
		
		goto _st32;
		_st32:
		p+= 1;
		if ( p == pe )
			goto _test_eof32;
		st_case_32:
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
		_st33:
		p+= 1;
		if ( p == pe )
			goto _test_eof33;
		st_case_33:
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
		st_out:
		_test_eof34: cs = 34; goto _test_eof; 
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
		
		_test_eof: {}
		if ( cs >= 34 )
			goto _out; _pop: {}
		_out: {}
	}
	
#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/24__cat4_2.rl"
	
	
	in->p = p;
	in->pe = pe;
}
