/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *(YYMARKER = YYCURSOR);
	switch (yych) {
		case 'a':
			yyt1 = YYCURSOR;
			yyt5 = YYCURSOR;
			yyt6 = NULL;
			goto yy2;
		case 'b':
			yyt1 = YYCURSOR;
			yyt3 = YYCURSOR;
			yyt4 = YYCURSOR;
			yyt5 = YYCURSOR;
			yyt6 = NULL;
			goto yy4;
		default: goto yy1;
	}
yy1:
	yynmatch = 1;
	yypmatch[0] = YYCURSOR;
	yypmatch[1] = YYCURSOR;
	{}
yy2:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			yyt5 = YYCURSOR;
			yyt6 = NULL;
			goto yy2;
		case 'b':
			yyt2 = YYCURSOR;
			yyt3 = YYCURSOR;
			yyt4 = NULL;
			goto yy6;
		default: goto yy3;
	}
yy3:
	YYCURSOR = YYMARKER;
	if (yyaccept == 0) goto yy1;
	else goto yy5;
yy4:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 'a':
			yyt2 = yyt5;
			yyt5 = YYCURSOR;
			yyt6 = NULL;
			goto yy2;
		case 'b':
			yyt2 = YYCURSOR;
			yyt3 = YYCURSOR;
			yyt4 = NULL;
			goto yy6;
		default:
			yyt2 = yyt5;
			goto yy5;
	}
yy5:
	yynmatch = 3;
	yypmatch[0] = yyt1;
	yypmatch[2] = yyt2;
	yypmatch[3] = yyt3;
	yypmatch[5] = yyt4;
	yypmatch[1] = YYCURSOR;
	yypmatch[4] = yyt4;
	{}
yy6:
	yyaccept = 1;
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			yyt2 = yyt5;
			yyt4 = yyt6;
			yyt5 = YYCURSOR;
			yyt6 = NULL;
			goto yy2;
		case 'b':
			yyt5 = yyt2;
			yyt6 = yyt4;
			yyt2 = YYCURSOR;
			yyt3 = YYCURSOR;
			yyt4 = NULL;
			goto yy6;
		default:
			yyt2 = yyt5;
			yyt4 = yyt6;
			goto yy5;
	}
}

captures/posix/osxbsdcritical/03.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
