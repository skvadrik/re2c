/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	YYMARKER = YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			yyt1 = YYCURSOR;
			goto yy2;
		case 'b':
			yyt1 = YYCURSOR;
			yyt3 = YYCURSOR;
			goto yy4;
		default: goto yy1;
	}
yy1:
	yynmatch = 1;
	yypmatch[0] = YYCURSOR;
	yypmatch[1] = YYCURSOR;
	{}
yy2:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy2;
		case 'b':
			yyt3 = YYCURSOR;
			goto yy4;
		default: goto yy3;
	}
yy3:
	YYCURSOR = YYMARKER;
	goto yy1;
yy4:
	yych = *++YYCURSOR;
	yyt2 = YYCURSOR;
	goto yy7;
yy5:
	yynmatch = 4;
	yypmatch[2] = yyt1;
	yypmatch[4] = yyt3;
	yypmatch[6] = yyt2;
	yypmatch[0] = yyt1;
	yypmatch[1] = YYCURSOR;
	yypmatch[3] = yyt3;
	yypmatch[5] = yyt2;
	yypmatch[7] = YYCURSOR;
	{}
yy6:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy7:
	switch (yych) {
		case 'c': goto yy6;
		default: goto yy5;
	}
}

captures/posix/rightassoc/06.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
