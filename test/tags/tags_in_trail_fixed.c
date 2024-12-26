/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --tags

// fixed trailing context, fixed tags p and q

{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 4) YYFILL(4);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy3;
		default: goto yy1;
	}
yy1:
	++YYCURSOR;
yy2:
	{}
yy3:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 'b': goto yy4;
		default: goto yy2;
	}
yy4:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'c': goto yy6;
		default: goto yy5;
	}
yy5:
	YYCURSOR = YYMARKER;
	goto yy2;
yy6:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'd': goto yy7;
		default: goto yy5;
	}
yy7:
	++YYCURSOR;
	p = YYCURSOR;
	p -= 4;
	q = YYCURSOR;
	q -= 2;
	YYCURSOR -= 3;
	{}
}


// variable trailing context, fixed tags p and q

{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 4) YYFILL(4);
	yych = *YYCURSOR;
	switch (yych) {
		case 'a': goto yy11;
		default: goto yy9;
	}
yy9:
	++YYCURSOR;
yy10:
	{}
yy11:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 'b':
			yyt1 = YYCURSOR;
			goto yy12;
		case 'c':
			yyt1 = YYCURSOR;
			goto yy14;
		default: goto yy10;
	}
yy12:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'c': goto yy14;
		default: goto yy13;
	}
yy13:
	YYCURSOR = YYMARKER;
	goto yy10;
yy14:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'd': goto yy15;
		default: goto yy13;
	}
yy15:
	++YYCURSOR;
	p = yyt1;
	p -= 1;
	q = YYCURSOR;
	q -= 2;
	YYCURSOR = yyt1;
	{}
}
