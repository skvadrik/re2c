#line 1 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 26 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"



#line 9 "gen/ragel/submatch_06__email.c"
static const int email_start = 9;
static const int email_first_final = 9;
static const int email_error = -1;

static const int email_en_main = 9;


#line 28 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	char *p1, *p2;
	int cs;
	

#line 25 "gen/ragel/submatch_06__email.c"
	{
		cs = (int)email_start;
	}
	
#line 37 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"


#line 30 "gen/ragel/submatch_06__email.c"
{
		switch ( cs ) {
			case 9:
			goto st_case_9;
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
		}
		_ctr10:
			{
#line 17 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"
			
			outc(out, ' ');
			outs(out, p1, p2 - 1);
			outc(out, ' ');
			outs(out, p2, p);
			outc(out, '\n');
		}
		
#line 64 "gen/ragel/submatch_06__email.c"

		goto _st9;
		_st9:
		p+= 1;
		st_case_9:
		if ( p == pe )
			goto _out9;
		switch( ( (*( p))) ) {
			case 10: {
				goto _st9;
			}
			case 33: {
				goto _ctr12;
			}
			case 45: {
				goto _ctr12;
			}
			case 61: {
				goto _ctr12;
			}
			case 63: {
				goto _ctr12;
			}
		}
		if ( ( (*( p))) < 42 ) {
			if ( 35 <= ( (*( p))) && ( (*( p))) <= 39 ) {
				goto _ctr12;
			}
		} else if ( ( (*( p))) > 43 ) {
			if ( ( (*( p))) > 57 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 126 ) {
					goto _ctr12;
				}
			} else if ( ( (*( p))) >= 47 ) {
				goto _ctr12;
			}
		} else {
			goto _ctr12;
		}
		goto _st0;
		_st0:
		p+= 1;
		st_case_0:
		if ( p == pe )
			goto _out0;
		if ( ( (*( p))) == 10 ) {
			goto _st9;
		}
		goto _st0;
		_ctr12:
			{
#line 15 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"
			p1 = p; }
		
#line 118 "gen/ragel/submatch_06__email.c"

		goto _st1;
		_st1:
		p+= 1;
		st_case_1:
		if ( p == pe )
			goto _out1;
		switch( ( (*( p))) ) {
			case 10: {
				goto _st9;
			}
			case 33: {
				goto _st1;
			}
			case 46: {
				goto _st2;
			}
			case 61: {
				goto _st1;
			}
			case 63: {
				goto _st1;
			}
			case 64: {
				goto _st3;
			}
		}
		if ( ( (*( p))) < 42 ) {
			if ( 35 <= ( (*( p))) && ( (*( p))) <= 39 ) {
				goto _st1;
			}
		} else if ( ( (*( p))) > 43 ) {
			if ( ( (*( p))) > 57 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 126 ) {
					goto _st1;
				}
			} else if ( ( (*( p))) >= 45 ) {
				goto _st1;
			}
		} else {
			goto _st1;
		}
		goto _st0;
		_st2:
		p+= 1;
		st_case_2:
		if ( p == pe )
			goto _out2;
		switch( ( (*( p))) ) {
			case 10: {
				goto _st9;
			}
			case 33: {
				goto _st1;
			}
			case 45: {
				goto _st1;
			}
			case 61: {
				goto _st1;
			}
			case 63: {
				goto _st1;
			}
		}
		if ( ( (*( p))) < 42 ) {
			if ( 35 <= ( (*( p))) && ( (*( p))) <= 39 ) {
				goto _st1;
			}
		} else if ( ( (*( p))) > 43 ) {
			if ( ( (*( p))) > 57 ) {
				if ( 94 <= ( (*( p))) && ( (*( p))) <= 126 ) {
					goto _st1;
				}
			} else if ( ( (*( p))) >= 47 ) {
				goto _st1;
			}
		} else {
			goto _st1;
		}
		goto _st0;
		_st3:
		p+= 1;
		st_case_3:
		if ( p == pe )
			goto _out3;
		if ( ( (*( p))) == 10 ) {
			goto _st9;
		}
		if ( ( (*( p))) > 57 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _ctr5;
			}
		} else if ( ( (*( p))) >= 48 ) {
			goto _ctr5;
		}
		goto _st0;
		_ctr5:
			{
#line 16 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"
			p2 = p; }
		
#line 220 "gen/ragel/submatch_06__email.c"

		goto _st4;
		_st4:
		p+= 1;
		st_case_4:
		if ( p == pe )
			goto _out4;
		switch( ( (*( p))) ) {
			case 10: {
				goto _st9;
			}
			case 45: {
				goto _st5;
			}
			case 46: {
				goto _st6;
			}
		}
		if ( ( (*( p))) > 57 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st4;
			}
		} else if ( ( (*( p))) >= 48 ) {
			goto _st4;
		}
		goto _st0;
		_st5:
		p+= 1;
		st_case_5:
		if ( p == pe )
			goto _out5;
		switch( ( (*( p))) ) {
			case 10: {
				goto _st9;
			}
			case 45: {
				goto _st5;
			}
		}
		if ( ( (*( p))) > 57 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st4;
			}
		} else if ( ( (*( p))) >= 48 ) {
			goto _st4;
		}
		goto _st0;
		_st6:
		p+= 1;
		st_case_6:
		if ( p == pe )
			goto _out6;
		if ( ( (*( p))) == 10 ) {
			goto _st9;
		}
		if ( ( (*( p))) > 57 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st7;
			}
		} else if ( ( (*( p))) >= 48 ) {
			goto _st7;
		}
		goto _st0;
		_st7:
		p+= 1;
		st_case_7:
		if ( p == pe )
			goto _out7;
		switch( ( (*( p))) ) {
			case 10: {
				goto _ctr10;
			}
			case 45: {
				goto _st8;
			}
			case 46: {
				goto _st6;
			}
		}
		if ( ( (*( p))) > 57 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st7;
			}
		} else if ( ( (*( p))) >= 48 ) {
			goto _st7;
		}
		goto _st0;
		_st8:
		p+= 1;
		st_case_8:
		if ( p == pe )
			goto _out8;
		switch( ( (*( p))) ) {
			case 10: {
				goto _st9;
			}
			case 45: {
				goto _st8;
			}
		}
		if ( ( (*( p))) > 57 ) {
			if ( 97 <= ( (*( p))) && ( (*( p))) <= 122 ) {
				goto _st7;
			}
		} else if ( ( (*( p))) >= 48 ) {
			goto _st7;
		}
		goto _st0;
		_out9: cs = 9; goto _out; 
		_out0: cs = 0; goto _out; 
		_out1: cs = 1; goto _out; 
		_out2: cs = 2; goto _out; 
		_out3: cs = 3; goto _out; 
		_out4: cs = 4; goto _out; 
		_out5: cs = 5; goto _out; 
		_out6: cs = 6; goto _out; 
		_out7: cs = 7; goto _out; 
		_out8: cs = 8; goto _out; 
		_out: {}
	}
	
#line 38 "../../../benchmarks/c/src/ragel/submatch_06__email.rl"

	
	in->p = p;
	in->pe = pe;
}
