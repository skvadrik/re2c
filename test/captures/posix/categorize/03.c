/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	YYMARKER = YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if (yych >= 0x01) {
		yyt1 = YYCURSOR;
		yyt3 = YYCURSOR;
		goto yy2;
	}
	yyt1 = YYCURSOR;
	yyt2 = NULL;
	yyt3 = NULL;
yy1:
	yynmatch = 2;
	yypmatch[0] = yyt1;
	yypmatch[2] = yyt3;
	yypmatch[3] = yyt2;
	yypmatch[1] = YYCURSOR;
	{}
yy2:
	yych = *++YYCURSOR;
	if (yych >= 0x01) goto yy3;
	YYCURSOR = YYMARKER;
	yyt1 = YYCURSOR;
	yyt2 = NULL;
	yyt3 = NULL;
	goto yy1;
yy3:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= 0x00) {
		yyt2 = YYCURSOR;
		goto yy1;
	}
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	yyt2 = YYCURSOR;
	if (yych <= 0x00) goto yy1;
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= 0x00) {
		yyt2 = YYCURSOR;
		goto yy1;
	}
	yyt3 = YYCURSOR;
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= 0x00) {
		yyt3 = yyt2;
		yyt2 = YYCURSOR;
		goto yy1;
	}
	goto yy3;
}

captures/posix/categorize/03.re:6:4: warning: rule matches empty string [-Wmatch-empty-string]
captures/posix/categorize/03.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
captures/posix/categorize/03.re:7:7: warning: unreachable rule (shadowed by rule at line 6) [-Wunreachable-rules]
