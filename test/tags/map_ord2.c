/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --tags
// incorrect automaton if mapping of TDFA states ignores version order

{
	YYCTYPE yych;
	YYMARKER = YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 8) YYFILL(8);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			yyt1 = YYCURSOR;
			yyt2 = NULL;
			goto yy2;
		default:
			yyt1 = NULL;
			goto yy1;
	}
yy1:
	t = yyt1;
	{}
yy2:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy4;
		default: goto yy3;
	}
yy3:
	YYCURSOR = YYMARKER;
	yyt1 = NULL;
	goto yy1;
yy4:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy5;
		default: goto yy1;
	}
yy5:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy6;
		default:
			yyt1 = yyt2;
			goto yy1;
	}
yy6:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy7;
		default:
			yyt1 = yyt2;
			goto yy1;
	}
yy7:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy8;
		default: goto yy1;
	}
yy8:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy9;
		default: goto yy1;
	}
yy9:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy10;
		default:
			yyt1 = yyt2;
			goto yy1;
	}
yy10:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy10;
		default: goto yy1;
	}
}

tags/map_ord2.re:5:24: warning: rule matches empty string [-Wmatch-empty-string]
tags/map_ord2.re:5:24: warning: tag `t` has 2nd degree of nondeterminism [-Wnondeterministic-tags]
