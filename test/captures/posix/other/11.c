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
			yyt2 = NULL;
			goto yy2;
		default:
			yyt1 = YYCURSOR;
			yyt2 = NULL;
			yyt3 = NULL;
			goto yy1;
	}
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
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy4;
		default: goto yy3;
	}
yy3:
	YYCURSOR = YYMARKER;
	if (yyaccept == 0) {
		yyt1 = YYCURSOR;
		yyt2 = NULL;
		yyt3 = NULL;
		goto yy1;
	} else {
		yyt2 = YYCURSOR;
		yyt3 = NULL;
		goto yy1;
	}
yy4:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy5;
		default:
			yyt2 = YYCURSOR;
			yyt3 = NULL;
			goto yy1;
	}
yy5:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy6;
		default:
			yyt3 = YYCURSOR;
			goto yy1;
	}
yy6:
	yyaccept = 1;
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy7;
		default:
			yyt2 = YYCURSOR;
			yyt3 = NULL;
			goto yy1;
	}
yy7:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy8;
		default: goto yy3;
	}
yy8:
	yyaccept = 1;
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy2;
		default:
			yyt2 = YYCURSOR;
			yyt3 = NULL;
			goto yy1;
	}
}

captures/posix/other/11.re:6:4: warning: rule matches empty string [-Wmatch-empty-string]
captures/posix/other/11.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
captures/posix/other/11.re:7:7: warning: unreachable rule (shadowed by rule at line 6) [-Wunreachable-rules]
