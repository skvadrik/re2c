/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *(YYMARKER = YYCURSOR);
	switch (yych) {
		case 'a':
			yyt1 = YYCURSOR;
			yyt3 = YYCURSOR;
			goto yy2;
		case 'b':
			yyt1 = YYCURSOR;
			yyt3 = YYCURSOR;
			goto yy3;
		default:
			yyt1 = YYCURSOR;
			yyt2 = NULL;
			yyt3 = NULL;
			goto yy1;
	}
yy1:
	yynmatch = 2;
	yypmatch[0] = yyt1;
	yypmatch[2] = yyt2;
	yypmatch[3] = yyt3;
	yypmatch[1] = YYCURSOR;
	{}
yy2:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			yyt3 = YYCURSOR;
			goto yy2;
		case 'b': goto yy5;
		default:
			yyt2 = yyt3;
			yyt3 = YYCURSOR;
			goto yy1;
	}
yy3:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy5;
		default: goto yy4;
	}
yy4:
	YYCURSOR = YYMARKER;
	if (yyaccept == 0) {
		yyt1 = YYCURSOR;
		yyt2 = NULL;
		yyt3 = NULL;
		goto yy1;
	} else {
		yyt3 = YYCURSOR;
		goto yy1;
	}
yy5:
	yyaccept = 1;
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			yyt3 = YYCURSOR;
			goto yy2;
		case 'b':
			yyt2 = yyt3;
			yyt3 = YYCURSOR;
			goto yy3;
		default:
			yyt2 = yyt3;
			yyt3 = YYCURSOR;
			goto yy1;
	}
}

captures/posix/glennfowler/25.re:6:4: warning: rule matches empty string [-Wmatch-empty-string]
captures/posix/glennfowler/25.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
captures/posix/glennfowler/25.re:7:7: warning: unreachable rule (shadowed by rule at line 6) [-Wunreachable-rules]
