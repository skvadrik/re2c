/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -if




	switch (YYGETSTATE()) {
	default:
		goto yy0;
	case 0:
		if (YYLIMIT <= YYCURSOR) goto yy7;
		goto yyFillLabel0;
	case 1:
		if (YYLIMIT <= YYCURSOR) goto yy15;
		goto yyFillLabel1;
	case 2:
		if (YYLIMIT <= YYCURSOR) goto yy23;
		goto yyFillLabel2;
	case 3:
		if (YYLIMIT <= YYCURSOR) goto yy31;
		goto yyFillLabel3;
	}
yy0:
yyFillLabel0:
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':	goto yy5;
	default:
		if (YYLIMIT <= YYCURSOR) {
			YYSETSTATE(0);
			fill();
		}
		goto yy3;
	}
yy3:
	++YYCURSOR;
	{ return FAIL; }
yy5:
	++YYCURSOR;
	{ return OK; }
yy7:
	{ return EOF; }




yyFillLabel1:
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':	goto yy13;
	default:
		if (YYLIMIT <= YYCURSOR) {
			YYSETSTATE(1);
			fill();
		}
		goto yy11;
	}
yy11:
	++YYCURSOR;
	{ return FAIL; }
yy13:
	++YYCURSOR;
	{ return OK; }
yy15:
	{ return EOF; }




yyFillLabel2:
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':	goto yy21;
	default:
		if (YYLIMIT <= YYCURSOR) {
			YYSETSTATE(2);
			fill();
		}
		goto yy19;
	}
yy19:
	++YYCURSOR;
	{ return FAIL; }
yy21:
	++YYCURSOR;
	{ return OK; }
yy23:
	{ return EOF; }




yyFillLabel3:
	yych = *YYCURSOR;
	switch (yych) {
	case 'a':	goto yy29;
	default:
		if (YYLIMIT <= YYCURSOR) {
			YYSETSTATE(3);
			fill();
		}
		goto yy27;
	}
yy27:
	++YYCURSOR;
	{ return FAIL; }
yy29:
	++YYCURSOR;
	{ return OK; }
yy31:
	{ return EOF; }

