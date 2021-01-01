#line 1 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
#include "ragel/common.c"

const char *delim = "\n";


#line 35 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"



#line 12 "gen/ragel/datetime-T1.c"
static const signed char _datetime_key_offsets[] = {
	0, 0, 2, 4, 6, 7, 9, 11,
	12, 16, 18, 19, 22, 24, 25, 27,
	29, 30, 32, 34, 37, 40, 42, 43,
	45, 47, 48, 50, 52, 54, 56, 58,
	60, 62, 64, 67, 0
};

static const char _datetime_trans_keys[] = {
	48, 57, 48, 57, 48, 57, 45, 48,
	49, 49, 57, 45, 48, 51, 49, 50,
	49, 57, 84, 50, 48, 49, 48, 57,
	58, 48, 53, 48, 57, 58, 48, 53,
	48, 57, 43, 45, 90, 50, 48, 49,
	48, 57, 58, 48, 53, 48, 57, 10,
	48, 51, 48, 51, 48, 57, 48, 49,
	48, 50, 48, 57, 48, 57, 48, 57,
	45, 48, 57, 48, 49, 57, 0
};

static const signed char _datetime_single_lengths[] = {
	0, 0, 0, 0, 1, 2, 0, 1,
	2, 0, 1, 1, 0, 1, 0, 0,
	1, 0, 0, 3, 1, 0, 1, 0,
	0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 1, 0
};

static const signed char _datetime_range_lengths[] = {
	0, 1, 1, 1, 0, 0, 1, 0,
	1, 1, 0, 1, 1, 0, 1, 1,
	0, 1, 1, 0, 1, 1, 0, 1,
	1, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 0
};

static const signed char _datetime_index_offsets[] = {
	0, 0, 2, 4, 6, 8, 11, 13,
	15, 19, 21, 23, 26, 28, 30, 32,
	34, 36, 38, 40, 44, 47, 49, 51,
	53, 55, 57, 59, 61, 63, 65, 67,
	69, 71, 73, 76, 0
};

static const signed char _datetime_cond_targs[] = {
	2, 0, 3, 0, 4, 0, 5, 0,
	6, 30, 0, 7, 0, 8, 0, 9,
	29, 28, 0, 10, 0, 11, 0, 27,
	12, 0, 13, 0, 14, 0, 15, 0,
	16, 0, 17, 0, 18, 0, 19, 0,
	20, 20, 25, 0, 26, 21, 0, 22,
	0, 23, 0, 24, 0, 25, 0, 35,
	0, 22, 0, 13, 0, 10, 0, 10,
	0, 7, 0, 32, 0, 33, 0, 34,
	0, 5, 34, 0, 1, 31, 0, 0,
	1, 2, 3, 4, 5, 6, 7, 8,
	9, 10, 11, 12, 13, 14, 15, 16,
	17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30, 31, 32,
	33, 34, 35, 0
};

static const signed char _datetime_cond_actions[] = {
	0, 0, 0, 0, 0, 0, 1, 0,
	2, 2, 0, 0, 0, 3, 0, 4,
	4, 4, 0, 0, 0, 5, 0, 6,
	6, 0, 0, 0, 7, 0, 8, 0,
	0, 0, 9, 0, 10, 0, 0, 0,
	11, 11, 11, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 12,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 13, 13, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0
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
	
	
#line 113 "gen/ragel/datetime-T1.c"
	{
		cs = (int)datetime_start;
	}
	
#line 48 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
	
	
#line 121 "gen/ragel/datetime-T1.c"
	{
		int _klen;
		unsigned int _trans = 0;
		const char * _keys;
		_resume: {}
		if ( p == pe )
			goto _out;
		_keys = ( _datetime_trans_keys + (_datetime_key_offsets[cs]));
		_trans = (unsigned int)_datetime_index_offsets[cs];
		
		_klen = (int)_datetime_single_lengths[cs];
		if ( _klen > 0 ) {
			const char *_lower = _keys;
			const char *_upper = _keys + _klen - 1;
			const char *_mid;
			while ( 1 ) {
				if ( _upper < _lower ) {
					_keys += _klen;
					_trans += (unsigned int)_klen;
					break;
				}
				
				_mid = _lower + ((_upper-_lower) >> 1);
				if ( ( (*( p))) < (*( _mid)) )
					_upper = _mid - 1;
				else if ( ( (*( p))) > (*( _mid)) )
					_lower = _mid + 1;
				else {
					_trans += (unsigned int)(_mid - _keys);
					goto _match;
				}
			}
		}
		
		_klen = (int)_datetime_range_lengths[cs];
		if ( _klen > 0 ) {
			const char *_lower = _keys;
			const char *_upper = _keys + (_klen<<1) - 2;
			const char *_mid;
			while ( 1 ) {
				if ( _upper < _lower ) {
					_trans += (unsigned int)_klen;
					break;
				}
				
				_mid = _lower + (((_upper-_lower) >> 1) & ~1);
				if ( ( (*( p))) < (*( _mid)) )
					_upper = _mid - 2;
				else if ( ( (*( p))) > (*( _mid + 1)) )
					_lower = _mid + 2;
				else {
					_trans += (unsigned int)((_mid - _keys)>>1);
					break;
				}
			}
		}
		
		_match: {}
		cs = (int)_datetime_cond_targs[_trans];
		
		if ( _datetime_cond_actions[_trans] != 0 ) {
			
			switch ( _datetime_cond_actions[_trans] ) {
				case 13:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						y1 = p; }
					
#line 190 "gen/ragel/datetime-T1.c"
					
					
					break; 
				}
				case 1:  {
					{
#line 16 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						y2 = p; }
					
#line 200 "gen/ragel/datetime-T1.c"
					
					
					break; 
				}
				case 2:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						m1 = p; }
					
#line 210 "gen/ragel/datetime-T1.c"
					
					
					break; 
				}
				case 3:  {
					{
#line 17 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						m2 = p; }
					
#line 220 "gen/ragel/datetime-T1.c"
					
					
					break; 
				}
				case 4:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						d1 = p; }
					
#line 230 "gen/ragel/datetime-T1.c"
					
					
					break; 
				}
				case 5:  {
					{
#line 18 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						d2 = p; }
					
#line 240 "gen/ragel/datetime-T1.c"
					
					
					break; 
				}
				case 6:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						h1 = p; }
					
#line 250 "gen/ragel/datetime-T1.c"
					
					
					break; 
				}
				case 7:  {
					{
#line 19 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						h2 = p; }
					
#line 260 "gen/ragel/datetime-T1.c"
					
					
					break; 
				}
				case 8:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						M1 = p; }
					
#line 270 "gen/ragel/datetime-T1.c"
					
					
					break; 
				}
				case 9:  {
					{
#line 20 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						M2 = p; }
					
#line 280 "gen/ragel/datetime-T1.c"
					
					
					break; 
				}
				case 10:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						s1 = p; }
					
#line 290 "gen/ragel/datetime-T1.c"
					
					
					break; 
				}
				case 11:  {
					{
#line 21 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						s2 = p; }
					
#line 300 "gen/ragel/datetime-T1.c"
					
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						z1 = p; }
					
#line 306 "gen/ragel/datetime-T1.c"
					
					
					break; 
				}
				case 12:  {
					{
#line 22 "../../../benchmarks/submatch_dfa_aot/src/ragel/datetime.rl"
						z2 = p; }
					
#line 316 "gen/ragel/datetime-T1.c"
					
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
					
#line 331 "gen/ragel/datetime-T1.c"
					
					
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
