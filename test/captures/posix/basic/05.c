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
		case 'b':
			yyt1 = YYCURSOR;
			yyt2 = YYCURSOR;
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
	if ((YYLIMIT - YYCURSOR) < 5) YYFILL(5);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy2;
		case 'b':
			yyt2 = YYCURSOR;
			yyt3 = YYCURSOR;
			goto yy4;
		default: goto yy3;
	}
yy3:
	YYCURSOR = YYMARKER;
	goto yy1;
yy4:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'b':
			yyt4 = YYCURSOR;
			goto yy5;
		default: goto yy3;
	}
yy5:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'b': goto yy6;
		default: goto yy3;
	}
yy6:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'b': goto yy7;
		default: goto yy3;
	}
yy7:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'b': goto yy9;
		default: goto yy8;
	}
yy8:
	yynmatch = 4;
	yypmatch[2] = yyt1;
	yypmatch[4] = yyt2;
	yypmatch[6] = yyt3;
	yypmatch[0] = yyt1;
	yypmatch[1] = YYCURSOR;
	yypmatch[3] = yyt2;
	yypmatch[5] = yyt3;
	yypmatch[7] = YYCURSOR;
	yypmatch[7] -= 3;
	{}
yy9:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'b': goto yy9;
		default:
			yyt3 = yyt4;
			goto yy8;
	}
}

captures/posix/basic/05.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
