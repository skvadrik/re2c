/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -cgir
// multiple scanners

enum YYCONDTYPE {
	yycr1,
	yycr2
};


void scan(unsigned char* in)
{

{
	unsigned char yych;
	static const void* yyctable[2] = {
		&&yyc_r1,
		&&yyc_r2
	};
	goto *yyctable[YYGETCONDITION()];
/* *********************************** */
yyc_r1:
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= '2') {
		if (yych <= '0') goto yy1;
		if (yych <= '1') goto yy2;
		goto yy3;
	} else {
		if (yych <= '`') goto yy1;
		if (yych <= 'a') goto yy4;
		if (yych <= 'b') goto yy5;
	}
yy1:
yy2:
	++YYCURSOR;
	{ return "1"; }
yy3:
	++YYCURSOR;
	{ return "2"; }
yy4:
	++YYCURSOR;
	{ return "a"; }
yy5:
	++YYCURSOR;
	{ return "b"; }
/* *********************************** */
yyc_r2:
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= '2') {
		if (yych <= '0') goto yy7;
		if (yych <= '1') goto yy8;
		goto yy9;
	} else {
		if (yych == 'b') goto yy10;
	}
yy7:
yy8:
	++YYCURSOR;
	{ return "1"; }
yy9:
	++YYCURSOR;
	{ return "2"; }
yy10:
	++YYCURSOR;
	{ return "b"; }
}

}

void scan(unsigned short* in)
{

{
	YYCTYPE yych;
	static const void* yyctable[2] = {
		&&yyc_r1,
		&&yyc_r2
	};
	goto *yyctable[YYGETCONDITION()];
/* *********************************** */
yyc_r1:
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= '2') {
		if (yych <= '0') goto yy12;
		if (yych <= '1') goto yy13;
		goto yy14;
	} else {
		if (yych <= '`') goto yy12;
		if (yych <= 'a') goto yy15;
		if (yych <= 'b') goto yy16;
	}
yy12:
yy13:
	++YYCURSOR;
	{ return "1"; }
yy14:
	++YYCURSOR;
	{ return "2"; }
yy15:
	++YYCURSOR;
	{ return "a"; }
yy16:
	++YYCURSOR;
	{ return "b"; }
/* *********************************** */
yyc_r2:
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= '2') {
		if (yych <= '0') goto yy18;
		if (yych <= '1') goto yy19;
		goto yy20;
	} else {
		if (yych == 'b') goto yy21;
	}
yy18:
yy19:
	++YYCURSOR;
	{ return "1"; }
yy20:
	++YYCURSOR;
	{ return "2"; }
yy21:
	++YYCURSOR;
	{ return "b"; }
}

}

void scan(unsigned int* in)
{

{
	YYCTYPE yych;
	static const void* yyctable[2] = {
		&&yyc_r1,
		&&yyc_r2
	};
	goto *yyctable[YYGETCONDITION()];
/* *********************************** */
yyc_r1:
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= '2') {
		if (yych <= '0') goto yy23;
		if (yych <= '1') goto yy24;
		goto yy25;
	} else {
		if (yych <= '`') goto yy23;
		if (yych <= 'a') goto yy26;
		if (yych <= 'b') goto yy27;
	}
yy23:
yy24:
	++YYCURSOR;
	{ return "1"; }
yy25:
	++YYCURSOR;
	{ return "2"; }
yy26:
	++YYCURSOR;
	{ return "a"; }
yy27:
	++YYCURSOR;
	{ return "b"; }
/* *********************************** */
yyc_r2:
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= '2') {
		if (yych <= '0') goto yy29;
		if (yych <= '1') goto yy30;
		goto yy31;
	} else {
		if (yych == 'b') goto yy32;
	}
yy29:
yy30:
	++YYCURSOR;
	{ return "1"; }
yy31:
	++YYCURSOR;
	{ return "2"; }
yy32:
	++YYCURSOR;
	{ return "b"; }
}

}

reuse/repeat-01.re:14:2: warning: control flow in condition 'r1' is undefined for strings that match '[\x0-\x30\x33-\x60\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]
reuse/repeat-01.re:14:2: warning: control flow in condition 'r2' is undefined for strings that match '[\x0-\x30\x33-\x61\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]
reuse/repeat-01.re:28:0: warning: control flow in condition 'r1' is undefined for strings that match '[\x0-\x30\x33-\x60\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]
reuse/repeat-01.re:28:0: warning: control flow in condition 'r2' is undefined for strings that match '[\x0-\x30\x33-\x61\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]
reuse/repeat-01.re:40:0: warning: control flow in condition 'r1' is undefined for strings that match '[\x0-\x30\x33-\x60\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]
reuse/repeat-01.re:40:0: warning: control flow in condition 'r2' is undefined for strings that match '[\x0-\x30\x33-\x61\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]
