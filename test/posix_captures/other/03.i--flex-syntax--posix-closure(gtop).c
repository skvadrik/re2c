/* Generated by re2c */

{
	YYCTYPE yych;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':	goto yy3;
	default:	goto yy2;
	}
yy2:
	yynmatch = 1;
	yypmatch[0] = YYCURSOR;
	yypmatch[1] = YYCURSOR;
	{}
yy3:
	++YYCURSOR;
	yyt1 = NULL;
	yynmatch = 2;
	yypmatch[2] = yyt1;
	yypmatch[3] = yyt1;
	yypmatch[0] = YYCURSOR - 1;
	yypmatch[1] = YYCURSOR;
	{}
}

posix_captures/other/03.i--flex-syntax--posix-closure(gtop).re:6:7: warning: rule matches empty string [-Wmatch-empty-string]