/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --tags

{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a':
			yyt1 = YYCURSOR;
			yyt2 = NULL;
			goto yy2;
		case 'b':
			yyt2 = YYCURSOR;
			goto yy4;
		default:
			yyt1 = YYCURSOR;
			yyt2 = NULL;
			goto yy1;
	}
yy1:
	p = yyt2;
	q = yyt1;
	{}
yy2:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy3:
	switch (yych) {
		case 'a': goto yy2;
		default: goto yy1;
	}
yy4:
	yych = *(YYMARKER = ++YYCURSOR);
	yyt1 = NULL;
	switch (yych) {
		case 'b': goto yy5;
		default: goto yy3;
	}
yy5:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy7;
		default: goto yy6;
	}
yy6:
	YYCURSOR = YYMARKER;
	yyt1 = NULL;
	goto yy1;
yy7:
	++YYCURSOR;
	goto yy1;
}

tags/topsort2.re:4:28: warning: rule matches empty string [-Wmatch-empty-string]
tags/topsort2.re:4:28: warning: tag 'p' has 2nd degree of nondeterminism [-Wnondeterministic-tags]
tags/topsort2.re:4:28: warning: tag 'q' has 2nd degree of nondeterminism [-Wnondeterministic-tags]
