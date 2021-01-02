#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 26 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"



#line 12 "gen/ragel/email.c"
static const int email_start = 9;
static const int email_first_final = 9;
static const int email_error = -1;

static const int email_en_main = 9;


#line 28 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	char *p1, *p2;
	int cs;
	
	
#line 31 "gen/ragel/email.c"
	{
		cs = (int)email_start;
	}
	
#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
	
	
#line 39 "gen/ragel/email.c"
	{
		if ( p == pe )
			goto _test_eof;
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
		goto st_out;
		_ctr10:
		{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
			
			outc(out, ' ');
			outs(out, p1, p2 - 1);
			outc(out, ' ');
			outs(out, p2, p);
			outc(out, '\n');
		}
		
#line 77 "gen/ragel/email.c"
		
		goto _st9;
		_st9:
		p+= 1;
		if ( p == pe )
			goto _test_eof9;
		st_case_9:
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
		{
			goto _st0;
		}
		_st0:
		p+= 1;
		if ( p == pe )
			goto _test_eof0;
		st_case_0:
		if ( ( (*( p))) == 10 ) {
			goto _st9;
		}
		{
			goto _st0;
		}
		_ctr12:
		{
#line 15 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
			p1 = p; }
		
#line 136 "gen/ragel/email.c"
		
		goto _st1;
		_st1:
		p+= 1;
		if ( p == pe )
			goto _test_eof1;
		st_case_1:
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
		{
			goto _st0;
		}
		_st2:
		p+= 1;
		if ( p == pe )
			goto _test_eof2;
		st_case_2:
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
		{
			goto _st0;
		}
		_st3:
		p+= 1;
		if ( p == pe )
			goto _test_eof3;
		st_case_3:
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
		{
			goto _st0;
		}
		_ctr5:
		{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
			p2 = p; }
		
#line 245 "gen/ragel/email.c"
		
		goto _st4;
		_st4:
		p+= 1;
		if ( p == pe )
			goto _test_eof4;
		st_case_4:
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
		{
			goto _st0;
		}
		_st5:
		p+= 1;
		if ( p == pe )
			goto _test_eof5;
		st_case_5:
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
		{
			goto _st0;
		}
		_st6:
		p+= 1;
		if ( p == pe )
			goto _test_eof6;
		st_case_6:
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
		{
			goto _st0;
		}
		_st7:
		p+= 1;
		if ( p == pe )
			goto _test_eof7;
		st_case_7:
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
		{
			goto _st0;
		}
		_st8:
		p+= 1;
		if ( p == pe )
			goto _test_eof8;
		st_case_8:
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
		{
			goto _st0;
		}
		st_out:
		_test_eof9: cs = 9; goto _test_eof; 
		_test_eof0: cs = 0; goto _test_eof; 
		_test_eof1: cs = 1; goto _test_eof; 
		_test_eof2: cs = 2; goto _test_eof; 
		_test_eof3: cs = 3; goto _test_eof; 
		_test_eof4: cs = 4; goto _test_eof; 
		_test_eof5: cs = 5; goto _test_eof; 
		_test_eof6: cs = 6; goto _test_eof; 
		_test_eof7: cs = 7; goto _test_eof; 
		_test_eof8: cs = 8; goto _test_eof; 
		
		_test_eof: {}
		if ( cs >= 9 )
			goto _out; _out: {}
	}
	
#line 38 "../../../benchmarks/submatch_dfa_aot/src/ragel/email.rl"
	
	
	in->p = p;
	in->pe = pe;
}
