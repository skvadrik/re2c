/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *(YYMARKER = YYCURSOR);
	switch (yych) {
		case 'a':
			yyt1 = YYCURSOR;
			yyt3 = NULL;
			goto yy2;
		case 'b':
			yyt1 = YYCURSOR;
			yyt2 = YYCURSOR;
			yyt3 = NULL;
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
		case 'b': goto yy6;
		default: goto yy3;
	}
yy3:
	YYCURSOR = YYMARKER;
	goto yy1;
yy4:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'b': goto yy6;
		default: goto yy5;
	}
yy5:
	yynmatch = 4;
	yypmatch[2] = yyt1;
	yypmatch[5] = yyt2;
	yypmatch[0] = yyt1;
	yypmatch[1] = YYCURSOR;
	yypmatch[3] = YYCURSOR;
	yypmatch[3] -= 1;
	yypmatch[4] = yyt2;
	yypmatch[6] = YYCURSOR;
	yypmatch[6] -= 1;
	yypmatch[7] = YYCURSOR;
	{}
yy6:
	++YYCURSOR;
	yyt2 = yyt3;
	goto yy5;
}

captures/posix/osxbsdcritical/02.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
