/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	YYMARKER = YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
		case 'b':
			yyt1 = YYCURSOR;
			goto yy2;
		case 'c':
			yyt1 = YYCURSOR;
			yyt2 = NULL;
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
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
		case 'b': goto yy2;
		case 'c':
			yyt2 = YYCURSOR;
			goto yy4;
		default: goto yy3;
	}
yy3:
	YYCURSOR = YYMARKER;
	goto yy1;
yy4:
	++YYCURSOR;
	yyt3 = NULL;
	yynmatch = 3;
	yypmatch[0] = yyt1;
	yypmatch[3] = yyt2;
	yypmatch[4] = yyt3;
	yypmatch[5] = yyt3;
	yypmatch[1] = YYCURSOR;
	yypmatch[2] = yyt2;
	if (yypmatch[2] != NULL) yypmatch[2] -= 1;
	{}
}

captures/posix/basic/14.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
