/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
		case 'b':
			yyt1 = YYCURSOR;
			goto yy2;
		default:
			yyt1 = YYCURSOR;
			yyt2 = YYCURSOR;
			goto yy1;
	}
yy1:
	yynmatch = 2;
	yypmatch[0] = yyt1;
	yypmatch[2] = yyt1;
	yypmatch[3] = yyt2;
	yypmatch[1] = YYCURSOR;
	{}
yy2:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
		case 'b': goto yy2;
		default:
			yyt2 = YYCURSOR;
			goto yy1;
	}
}

captures/posix/nullsubexpr/08.re:6:4: warning: rule matches empty string [-Wmatch-empty-string]
captures/posix/nullsubexpr/08.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
captures/posix/nullsubexpr/08.re:7:7: warning: unreachable rule (shadowed by rule at line 6) [-Wunreachable-rules]
