#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"



#line 12 "gen/ragel/datetime-F1.c"
static const char _datetime_trans_keys[] = {
	1, 0, 4, 9, 4, 9, 4, 9,
	3, 3, 4, 5, 5, 9, 3, 3,
	4, 7, 5, 9, 11, 11, 4, 6,
	4, 9, 10, 10, 4, 8, 4, 9,
	10, 10, 4, 8, 4, 9, 2, 12,
	4, 6, 4, 9, 10, 10, 4, 8,
	4, 9, 0, 0, 4, 7, 4, 7,
	4, 9, 4, 5, 4, 6, 4, 9,
	4, 9, 4, 9, 3, 9, 4, 9,
	0
};

static const signed char _datetime_char_class[] = {
	0, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 2, 1, 3, 1, 1, 4, 5,
	6, 7, 8, 8, 9, 9, 9, 9,
	10, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 11, 1, 1, 1, 1, 1,
	12, 0
};

static const short _datetime_index_offsets[] = {
	0, 0, 6, 12, 18, 19, 21, 26,
	27, 31, 36, 37, 40, 46, 47, 52,
	58, 59, 64, 70, 81, 84, 90, 91,
	96, 102, 103, 107, 111, 117, 119, 122,
	128, 134, 140, 147, 0
};

static const signed char _datetime_indicies[] = {
	2, 2, 2, 2, 2, 2, 3, 3,
	3, 3, 3, 3, 4, 4, 4, 4,
	4, 4, 5, 7, 8, 10, 10, 10,
	10, 10, 11, 13, 14, 14, 15, 17,
	17, 17, 17, 17, 18, 20, 20, 21,
	23, 23, 23, 23, 23, 23, 24, 26,
	26, 26, 26, 26, 28, 28, 28, 28,
	28, 28, 29, 31, 31, 31, 31, 31,
	33, 33, 33, 33, 33, 33, 34, 34,
	0, 0, 0, 0, 0, 0, 0, 0,
	35, 37, 37, 38, 39, 39, 39, 39,
	39, 39, 40, 41, 41, 41, 41, 41,
	42, 42, 42, 42, 42, 42, 43, 39,
	39, 39, 39, 23, 23, 23, 23, 17,
	17, 17, 17, 17, 17, 17, 17, 10,
	10, 10, 49, 49, 49, 49, 49, 49,
	50, 50, 50, 50, 50, 50, 51, 51,
	51, 51, 51, 51, 5, 51, 51, 51,
	51, 51, 51, 53, 54, 54, 54, 54,
	54, 0
};

static const signed char _datetime_index_defaults[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0
};

static const signed char _datetime_cond_targs[] = {
	0, 1, 2, 3, 4, 5, 5, 6,
	30, 6, 7, 8, 8, 9, 28, 29,
	9, 10, 11, 11, 12, 27, 12, 13,
	14, 14, 15, 15, 16, 17, 17, 18,
	18, 19, 20, 25, 20, 21, 26, 22,
	23, 24, 25, 35, 27, 28, 29, 30,
	31, 32, 33, 34, 35, 1, 31, 0
};

static const signed char _datetime_cond_actions[] = {
	0, 0, 0, 0, 0, 1, 0, 2,
	2, 0, 0, 3, 0, 4, 4, 4,
	0, 0, 5, 0, 6, 6, 0, 0,
	7, 0, 8, 0, 0, 9, 0, 10,
	0, 0, 11, 11, 0, 0, 0, 0,
	0, 0, 0, 12, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 13, 13, 0
};

static const int datetime_start = 35;
static const int datetime_first_final = 35;
static const int datetime_error = 0;

static const int datetime_en_main = 35;


#line 37 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"


static void lex(Input *in, Output *out)
{
	char *p = in->p;
	char *pe = in->pe;
	const char
	*s1, *y1, *h1, *m1, *d1, *M1, *z1,
	*s2, *y2, *h2, *m2, *d2, *M2, *z2;
	int cs;
	
	
#line 119 "gen/ragel/datetime-F1.c"
	{
		cs = (int)datetime_start;
	}
	
#line 48 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
	
	
#line 127 "gen/ragel/datetime-F1.c"
	{
		unsigned int _trans = 0;
		const char * _keys;
		const signed char * _inds;
		int _ic;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _datetime_trans_keys + ((cs<<1)));
		_inds = ( _datetime_indicies + (_datetime_index_offsets[cs]));
		
		if ( ( (*( p))) <= 90 && ( (*( p))) >= 10 ) {
			_ic = (int)_datetime_char_class[(int)( (*( p))) - 10];
			if ( _ic <= (int)(*( _keys+1)) && _ic >= (int)(*( _keys)) )
				_trans = (unsigned int)(*( _inds + (int)( _ic - (int)(*( _keys)) ) )); 
			else
				_trans = (unsigned int)_datetime_index_defaults[cs];
		}
		else {
			_trans = (unsigned int)_datetime_index_defaults[cs];
		}
		
		cs = (int)_datetime_cond_targs[_trans];
		
		if ( _datetime_cond_actions[_trans] != 0 ) {
			
			switch ( _datetime_cond_actions[_trans] ) {
				case 13:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						y1 = p; }
					
#line 160 "gen/ragel/datetime-F1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						y2 = p; }
					
#line 170 "gen/ragel/datetime-F1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						m1 = p; }
					
#line 180 "gen/ragel/datetime-F1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						m2 = p; }
					
#line 190 "gen/ragel/datetime-F1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						d1 = p; }
					
#line 200 "gen/ragel/datetime-F1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						d2 = p; }
					
#line 210 "gen/ragel/datetime-F1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						h1 = p; }
					
#line 220 "gen/ragel/datetime-F1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						h2 = p; }
					
#line 230 "gen/ragel/datetime-F1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						M1 = p; }
					
#line 240 "gen/ragel/datetime-F1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						M2 = p; }
					
#line 250 "gen/ragel/datetime-F1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						s1 = p; }
					
#line 260 "gen/ragel/datetime-F1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						s2 = p; }
					
#line 270 "gen/ragel/datetime-F1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						z1 = p; }
					
#line 276 "gen/ragel/datetime-F1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						z2 = p; }
					
#line 286 "gen/ragel/datetime-F1.c"
					
					{
#line 23 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						
						OUT("year: ",    y1, y2);
						OUT("month: ",   m1, m2);
						OUT("day: ",     d1, d2);
						OUT("hours: ",   h1, h2);
						OUT("minutes: ", M1, M2);
						OUT("seconds: ", s1, s2);
						OUT("tz: ",      z1, z2);
						outc(out, '\n');
					}
					
#line 301 "gen/ragel/datetime-F1.c"
					
					
					break; 
				}
			}
			
		}
		
		if ( cs != 0 ) {
			p += 1;
			goto _resume;
		}
		_out: {}
	}
	
#line 49 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
	
	
	in->p = p;
	in->pe = pe;
}
