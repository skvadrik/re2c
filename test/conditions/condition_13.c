/* Generated by re2c */
#line 1 "conditions/condition_13.re"
// re2c $INPUT -o $OUTPUT -cg

#line 6 "conditions/condition_13.c"
{
	YYCTYPE yych;
	static const void* yyctable[3] = {
		&&yyc_0,
		&&yyc_r1,
		&&yyc_r2
	};
	goto *yyctable[YYGETCONDITION()];
/* *********************************** */
yyc_0:
	YYSETCONDITION(yycr1);
	goto yyc_r1;
/* *********************************** */
yyc_r1:
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= '2') {
		if (yych <= '0') goto yy2;
		if (yych <= '1') goto yy3;
		goto yy4;
	} else {
		if (yych <= '`') goto yy2;
		if (yych <= 'a') goto yy5;
		if (yych <= 'b') goto yy6;
	}
yy2:
yy3:
	++YYCURSOR;
	goto yyc_r1;
yy4:
	++YYCURSOR;
	goto yyc_r1;
yy5:
	++YYCURSOR;
	YYSETCONDITION(yycr2);
	goto yyc_r2;
yy6:
	++YYCURSOR;
	YYSETCONDITION(yycr2);
	goto yyc_r2;
/* *********************************** */
yyc_r2:
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= '2') {
		if (yych <= '0') goto yy8;
		if (yych <= '1') goto yy9;
		goto yy10;
	} else {
		if (yych == 'b') goto yy11;
	}
yy8:
yy9:
	++YYCURSOR;
	YYSETCONDITION(yycr1);
	goto yyc_r1;
yy10:
	++YYCURSOR;
	YYSETCONDITION(yycr1);
	goto yyc_r1;
yy11:
	++YYCURSOR;
	goto yyc_r2;
}
#line 10 "conditions/condition_13.re"

conditions/condition_13.re:2:0: warning: control flow in condition 'r1' is undefined for strings that match '[\x0-\x30\x33-\x60\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]
conditions/condition_13.re:2:0: warning: control flow in condition 'r2' is undefined for strings that match '[\x0-\x30\x33-\x61\x63-\xFF]', use default rule '*' [-Wundefined-control-flow]
conditions/condition_13.re:2:0: warning: condition numbers may change, use `conditions` block to generate reliable condition identifiers [-Wcondition-order]
