/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *(YYMARKER = YYCURSOR);
	switch (yych) {
		case 'a':
			yyt1 = YYCURSOR;
			yyt2 = YYCURSOR;
			goto yy2;
		case 'b':
			yyt1 = YYCURSOR;
			yyt2 = YYCURSOR;
			goto yy4;
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
			yyt3 = YYCURSOR;
			goto yy8;
		default: goto yy7;
	}
yy3:
	YYCURSOR = YYMARKER;
	goto yy1;
yy4:
	++YYCURSOR;
yy5:
	yynmatch = 3;
	yypmatch[2] = yyt1;
	yypmatch[4] = yyt2;
	yypmatch[0] = yyt1;
	yypmatch[1] = YYCURSOR;
	yypmatch[3] = yyt2;
	yypmatch[5] = YYCURSOR;
	{}
yy6:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
yy7:
	switch (yych) {
		case 'a':
			yyt3 = YYCURSOR;
			goto yy6;
		case 'b':
			yyt2 = yyt3;
			yyt3 = YYCURSOR;
			goto yy8;
		default: goto yy3;
	}
yy8:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'c': goto yy4;
		default:
			yyt2 = yyt3;
			goto yy5;
	}
}

captures/posix/forcedassoc/14.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
