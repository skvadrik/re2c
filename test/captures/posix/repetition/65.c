/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --flex-syntax

{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	YYMARKER = YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 10) YYFILL(10);
	yych = *YYCURSOR;
	switch (yych) {
		case 'X':
			yyt1 = YYCURSOR;
			goto yy2;
		default: goto yy1;
	}
yy1:
	yynmatch = 1;
	yypmatch[0] = YYCURSOR;
	yypmatch[1] = YYCURSOR;
	{}
yy2:
	yych = *++YYCURSOR;
	switch (yych) {
		case 0x00: goto yy3;
		case 'Y':
			yyt2 = YYCURSOR;
			yyt3 = YYCURSOR;
			goto yy5;
		default: goto yy4;
	}
yy3:
	YYCURSOR = YYMARKER;
	switch (yyaccept) {
		case 0: goto yy1;
		case 1: goto yy6;
		default:
			yyt2 = yyt4;
			goto yy6;
	}
yy4:
	yych = *++YYCURSOR;
	switch (yych) {
		case 0x00: goto yy3;
		case 'Y':
			yyt2 = YYCURSOR;
			yyt3 = YYCURSOR;
			goto yy8;
		default: goto yy7;
	}
yy5:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 0x00: goto yy6;
		case 'Y':
			yyt2 = YYCURSOR;
			yyt3 = YYCURSOR;
			goto yy8;
		default: goto yy7;
	}
yy6:
	yynmatch = 2;
	yypmatch[0] = yyt1;
	yypmatch[2] = yyt2;
	yypmatch[3] = yyt3;
	yypmatch[1] = YYCURSOR;
	{}
yy7:
	yych = *++YYCURSOR;
	switch (yych) {
		case 0x00: goto yy3;
		case 'Y':
			yyt2 = YYCURSOR;
			yyt3 = YYCURSOR;
			goto yy10;
		default: goto yy9;
	}
yy8:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 0x00: goto yy6;
		case 'Y':
			yyt2 = YYCURSOR;
			yyt3 = YYCURSOR;
			goto yy10;
		default: goto yy9;
	}
yy9:
	yych = *++YYCURSOR;
	switch (yych) {
		case 0x00: goto yy3;
		case 'Y':
			yyt2 = YYCURSOR;
			yyt3 = YYCURSOR;
			goto yy12;
		default: goto yy11;
	}
yy10:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 0x00: goto yy6;
		case 'Y':
			yyt2 = YYCURSOR;
			yyt3 = YYCURSOR;
			goto yy12;
		default: goto yy11;
	}
yy11:
	yych = *++YYCURSOR;
	switch (yych) {
		case 0x00: goto yy3;
		case 'Y':
			yyt2 = YYCURSOR;
			yyt3 = YYCURSOR;
			goto yy14;
		default: goto yy13;
	}
yy12:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 0x00: goto yy6;
		case 'Y':
			yyt2 = YYCURSOR;
			yyt3 = YYCURSOR;
			goto yy14;
		default: goto yy13;
	}
yy13:
	yych = *++YYCURSOR;
	switch (yych) {
		case 0x00: goto yy3;
		case 'Y':
			yyt3 = YYCURSOR;
			yyt4 = YYCURSOR;
			goto yy16;
		default:
			yyt4 = YYCURSOR;
			goto yy15;
	}
yy14:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 0x00: goto yy6;
		case 'Y':
			yyt3 = YYCURSOR;
			yyt4 = YYCURSOR;
			goto yy16;
		default:
			yyt4 = YYCURSOR;
			goto yy15;
	}
yy15:
	yych = *++YYCURSOR;
	switch (yych) {
		case 0x00: goto yy3;
		case 'Y':
			yyt3 = YYCURSOR;
			yyt5 = YYCURSOR;
			goto yy18;
		default:
			yyt5 = YYCURSOR;
			goto yy17;
	}
yy16:
	yyaccept = 2;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 0x00:
			yyt2 = yyt4;
			goto yy6;
		case 'Y':
			yyt3 = YYCURSOR;
			yyt5 = YYCURSOR;
			goto yy18;
		default:
			yyt5 = YYCURSOR;
			goto yy17;
	}
yy17:
	yych = *++YYCURSOR;
	switch (yych) {
		case 0x00: goto yy3;
		case 'Y':
			yyt3 = YYCURSOR;
			yyt6 = YYCURSOR;
			goto yy20;
		default:
			yyt6 = YYCURSOR;
			goto yy19;
	}
yy18:
	yyaccept = 2;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 0x00:
			yyt2 = yyt4;
			goto yy6;
		case 'Y':
			yyt3 = YYCURSOR;
			yyt6 = YYCURSOR;
			goto yy20;
		default:
			yyt6 = YYCURSOR;
			goto yy19;
	}
yy19:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'Y':
			yyt3 = YYCURSOR;
			goto yy21;
		default: goto yy3;
	}
yy20:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'Y':
			yyt3 = YYCURSOR;
			goto yy21;
		default:
			yyt2 = yyt5;
			goto yy6;
	}
yy21:
	++YYCURSOR;
	yyt2 = yyt6;
	goto yy6;
}

captures/posix/repetition/65.re:7:7: warning: rule matches empty string [-Wmatch-empty-string]
