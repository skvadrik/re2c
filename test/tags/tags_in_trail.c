/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --tags

{
	YYCTYPE yych;
	goto yy0;
yy1:
	++YYCURSOR;
yy0:
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy1;
		case 'b':
			yyt1 = YYCURSOR;
			goto yy3;
		case 'c':
			yyt1 = YYCURSOR;
			yyt2 = YYCURSOR;
			goto yy4;
		default:
			yyt1 = YYCURSOR;
			yyt2 = YYCURSOR;
			goto yy2;
	}
yy2:
	p = yyt2;
	YYCURSOR = yyt1;
	{}
yy3:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'b': goto yy3;
		case 'c':
			yyt2 = YYCURSOR;
			goto yy4;
		default:
			yyt2 = YYCURSOR;
			goto yy2;
	}
yy4:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
		case 'c': goto yy4;
		default: goto yy2;
	}
}

tags/tags_in_trail.re:4:20: warning: rule matches empty string [-Wmatch-empty-string]
