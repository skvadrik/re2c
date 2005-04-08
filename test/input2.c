
#line 1 "input2.re"

#line 6 "<stdout>"
{
	YYCTYPE yych;
	unsigned int yyaccept;
	goto yy0;
	++YYCURSOR;
yy0:
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch(yych){
	case 'a':	goto yy3;
	default:	goto yy2;
	}
yy2:yy3:	++YYCURSOR;
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	goto yy4;
yy4:	switch(yych){
	case 'a':	goto yy3;
	case 'b':	goto yy5;
	default:	goto yy2;
	}
yy5:	yych = *++YYCURSOR;
	switch(yych){
	case 'b':	goto yy6;
	default:	goto yy2;
	}
yy6:	++YYCURSOR;
	goto yy7;
yy7:
#line 3 "input2.re"
{ return 1; }
#line 39 "<stdout>"
}
#line 5 "input2.re"

