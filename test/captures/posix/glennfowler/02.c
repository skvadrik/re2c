/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 4) YYFILL(4);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			yyt1 = YYCURSOR;
			yyt2 = YYCURSOR;
			goto yy2;
		case 'b':
			yyt1 = YYCURSOR;
			yyt2 = YYCURSOR;
			yyt3 = NULL;
			yyt4 = YYCURSOR;
			goto yy3;
		default:
			yyt1 = YYCURSOR;
			yyt2 = YYCURSOR;
			yyt3 = NULL;
			yyt4 = YYCURSOR;
			goto yy1;
	}
yy1:
	yynmatch = 5;
	yypmatch[2] = yyt1;
	yypmatch[4] = yyt2;
	yypmatch[7] = yyt3;
	yypmatch[8] = yyt4;
	yypmatch[0] = yyt1;
	yypmatch[1] = YYCURSOR;
	yypmatch[3] = yyt2;
	yypmatch[5] = yyt4;
	yypmatch[6] = yyt3;
	yypmatch[9] = YYCURSOR;
	if (yypmatch[6] != NULL) yypmatch[6] -= 2;
	{}
yy2:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 'a':
			yyt4 = YYCURSOR;
			goto yy4;
		case 'b':
			yyt3 = NULL;
			yyt4 = YYCURSOR;
			goto yy6;
		default:
			yyt2 = YYCURSOR;
			yyt3 = NULL;
			yyt4 = YYCURSOR;
			goto yy1;
	}
yy3:
	++YYCURSOR;
	goto yy1;
yy4:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'b': goto yy7;
		default: goto yy5;
	}
yy5:
	YYCURSOR = YYMARKER;
	yyt2 = YYCURSOR;
	yyt3 = NULL;
	yyt4 = YYCURSOR;
	goto yy1;
yy6:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'b':
			yyt3 = YYCURSOR;
			yyt4 = YYCURSOR;
			goto yy3;
		default:
			yyt2 = yyt4;
			goto yy1;
	}
yy7:
	yych = *++YYCURSOR;
	yyt2 = yyt4;
	yyt3 = YYCURSOR;
	yyt4 = YYCURSOR;
	switch (yych) {
		case 'b': goto yy3;
		default: goto yy1;
	}
}

captures/posix/glennfowler/02.re:6:4: warning: rule matches empty string [-Wmatch-empty-string]
captures/posix/glennfowler/02.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
captures/posix/glennfowler/02.re:7:7: warning: unreachable rule (shadowed by rule at line 6) [-Wunreachable-rules]
