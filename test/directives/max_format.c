/* Generated by re2c */
#line 1 "directives/max_format.re"
// re2c $INPUT -o $OUTPUT --posix-captures
// Test `max:re2c` and `maxnmatch:re2c` directives with optional format.

// default
#line 8 "directives/max_format.c"
#define YYMAXFILL 1
#line 5 "directives/max_format.re"

// #define YYMAXFILL @@
#line 13 "directives/max_format.c"
#define YYMAXFILL 1
#line 7 "directives/max_format.re"

// static const int MaxFill = @@{max};
#line 18 "directives/max_format.c"
static const int MaxFill = 1;
#line 11 "directives/max_format.re"

// line 12

// default
#line 25 "directives/max_format.c"
#define YYMAXNMATCH 1
#line 15 "directives/max_format.re"

// #define YYMAXFILL @@
#line 30 "directives/max_format.c"
#define YYMAXNMATCH 1
#line 17 "directives/max_format.re"

// static const int MaxNMatch = @@{max};
#line 35 "directives/max_format.c"
static const int MaxNMatch = 1;
#line 21 "directives/max_format.re"

// line 22


#line 42 "directives/max_format.c"
{
	YYCTYPE yych;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy2;
		default: goto yy1;
	}
yy1:
	++YYCURSOR;
#line 26 "directives/max_format.re"
	{ x }
#line 55 "directives/max_format.c"
yy2:
	++YYCURSOR;
	yynmatch = 1;
	yypmatch[0] = YYCURSOR;
	yypmatch[0] -= 1;
	yypmatch[1] = YYCURSOR;
#line 25 "directives/max_format.re"
	{ a }
#line 64 "directives/max_format.c"
}
#line 27 "directives/max_format.re"
