/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	YYMARKER = YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 5) YYFILL(5);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			yyt1 = YYCURSOR;
			goto yy2;
		default: goto yy1;
	}
yy1:
	yynmatch = 1;
	yypmatch[0] = YYCURSOR;
	yypmatch[1] = YYCURSOR;
	{}
yy2:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'b':
			yyt2 = YYCURSOR;
			goto yy4;
		case 'c':
			yyt2 = YYCURSOR;
			goto yy5;
		default: goto yy3;
	}
yy3:
	YYCURSOR = YYMARKER;
	goto yy1;
yy4:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'b':
			yyt3 = YYCURSOR;
			goto yy7;
		case 'c':
			yyt3 = YYCURSOR;
			goto yy8;
		default: goto yy3;
	}
yy5:
	++YYCURSOR;
yy6:
	yynmatch = 3;
	yypmatch[2] = yyt1;
	yypmatch[4] = yyt2;
	yypmatch[0] = yyt1;
	yypmatch[1] = YYCURSOR;
	yypmatch[3] = yyt2;
	yypmatch[5] = YYCURSOR;
	{}
yy7:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'c': goto yy9;
		default: goto yy3;
	}
yy8:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'd': goto yy5;
		default:
			yyt2 = yyt3;
			goto yy6;
	}
yy9:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'd':
			yyt2 = yyt3;
			goto yy5;
		default: goto yy3;
	}
}

captures/posix/forcedassoc/02.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
