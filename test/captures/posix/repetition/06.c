/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	YYMARKER = YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 6) YYFILL(6);
	yych = *YYCURSOR;
	if (yych >= 0x01) {
		yyt1 = YYCURSOR;
		goto yy2;
	}
yy1:
	yynmatch = 1;
	yypmatch[0] = YYCURSOR;
	yypmatch[1] = YYCURSOR;
	{}
yy2:
	yych = *++YYCURSOR;
	if (yych >= 0x01) goto yy4;
yy3:
	YYCURSOR = YYMARKER;
	goto yy1;
yy4:
	yych = *++YYCURSOR;
	if (yych <= 0x00) goto yy3;
	yyt2 = YYCURSOR;
	yyt4 = NULL;
	yych = *++YYCURSOR;
	if (yych >= 0x01) {
		yyt2 = YYCURSOR;
		yyt4 = NULL;
		goto yy6;
	}
	yyt3 = YYCURSOR;
	yyt5 = YYCURSOR;
yy5:
	yynmatch = 4;
	yypmatch[0] = yyt1;
	yypmatch[2] = yyt2;
	yypmatch[3] = yyt3;
	yypmatch[5] = yyt4;
	yypmatch[7] = yyt5;
	yypmatch[1] = YYCURSOR;
	yypmatch[4] = yyt4;
	yypmatch[6] = yyt5;
	if (yypmatch[4] != NULL) yypmatch[4] -= 2;
	if (yypmatch[6] != NULL) yypmatch[6] -= 1;
	{}
yy6:
	yych = *++YYCURSOR;
	if (yych <= 0x00) {
		yyt3 = YYCURSOR;
		yyt5 = YYCURSOR;
		goto yy5;
	}
	yyt2 = YYCURSOR;
	yyt4 = NULL;
	yych = *++YYCURSOR;
	if (yych <= 0x00) {
		yyt3 = YYCURSOR;
		yyt5 = YYCURSOR;
		goto yy5;
	}
	++YYCURSOR;
	yyt3 = YYCURSOR;
	yyt4 = YYCURSOR;
	yyt5 = NULL;
	goto yy5;
}

captures/posix/repetition/06.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
