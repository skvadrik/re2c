/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	YYMARKER = YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy2;
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
		case 'b': goto yy4;
		default: goto yy3;
	}
yy3:
	YYCURSOR = YYMARKER;
	goto yy1;
yy4:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'c': goto yy5;
		default: goto yy3;
	}
yy5:
	++YYCURSOR;
	yynmatch = 4;
	yypmatch[0] = YYCURSOR;
	yypmatch[0] -= 3;
	yypmatch[1] = YYCURSOR;
	yypmatch[2] = YYCURSOR;
	yypmatch[2] -= 3;
	yypmatch[3] = YYCURSOR;
	yypmatch[3] -= 2;
	yypmatch[4] = YYCURSOR;
	yypmatch[4] -= 2;
	yypmatch[5] = YYCURSOR;
	yypmatch[5] -= 1;
	yypmatch[6] = YYCURSOR;
	yypmatch[6] -= 1;
	yypmatch[7] = YYCURSOR;
	{}
}

captures/posix/basic/21.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
