/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	YYMARKER = YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 4) YYFILL(4);
	yych = *YYCURSOR;
	if (yych >= 0x01) {
		yyt1 = YYCURSOR;
		yyt2 = NULL;
		goto yy2;
	}
	yyt1 = YYCURSOR;
	yyt2 = NULL;
	yyt3 = NULL;
yy1:
	yynmatch = 3;
	yypmatch[0] = yyt1;
	yypmatch[3] = yyt2;
	yypmatch[5] = yyt3;
	yypmatch[1] = YYCURSOR;
	yypmatch[2] = yyt2;
	yypmatch[4] = yyt3;
	if (yypmatch[2] != NULL) yypmatch[2] -= 2;
	if (yypmatch[4] != NULL) yypmatch[4] -= 3;
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
	yych = *++YYCURSOR;
	if (yych <= 0x00) {
		yyt2 = YYCURSOR;
		yyt3 = NULL;
		goto yy1;
	}
	yyt3 = YYCURSOR;
	yych = *++YYCURSOR;
	if (yych <= 0x00) {
		yyt3 = YYCURSOR;
		goto yy1;
	}
yy4:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= 0x00) {
		yyt2 = YYCURSOR;
		yyt3 = NULL;
		goto yy1;
	}
	yyt2 = YYCURSOR;
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= 0x00) {
		yyt2 = yyt3;
		yyt3 = YYCURSOR;
		goto yy1;
	}
	yyt3 = yyt2;
	goto yy4;
}

captures/posix/basic/01.re:6:4: warning: rule matches empty string [-Wmatch-empty-string]
captures/posix/basic/01.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
captures/posix/basic/01.re:7:7: warning: unreachable rule (shadowed by rule at line 6) [-Wunreachable-rules]
