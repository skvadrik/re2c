/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
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
	++YYCURSOR;
	yyt1 = NULL;
	yynmatch = 2;
	yypmatch[3] = yyt1;
	yypmatch[0] = YYCURSOR;
	yypmatch[0] -= 1;
	yypmatch[1] = YYCURSOR;
	yypmatch[2] = yyt1;
	if (yypmatch[2] != NULL) yypmatch[2] -= 1;
	{}
}

captures/posix/other/03.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]