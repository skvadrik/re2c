
#line 1 "repeater.re"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RET(n) printf("%d\n", n); return n

int scan(char *s, int l){
char *p = s;
char *q;
#define YYCTYPE         char
#define YYCURSOR        p
#define YYLIMIT         (s+l)
#define YYMARKER        q
#define YYFILL(n)

#line 6 "<stdout>"
{
	YYCTYPE yych;
	unsigned int yyaccept;
	goto yy0;
yy1:	++YYCURSOR;
yy0:
	if((YYLIMIT - YYCURSOR) < 7) YYFILL(7);
	yych = *YYCURSOR;
	switch(yych){
	case 0x0A:	case '^':	case 'q':	goto yy6;
	case 'A':	goto yy3;
	case 'a':	goto yy4;
	default:	goto yy2;
	}
yy2:	YYCURSOR = YYMARKER;
	switch(yyaccept){
	case 0:	goto yy5;
	}
yy3:	yych = *++YYCURSOR;
	switch(yych){
	case 0x0A:	goto yy8;
	case 'A':	case 'a':	goto yy7;
	default:	goto yy2;
	}
yy4:	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch(yych){
	case 0x0A:	goto yy8;
	case 'A':	case 'a':	goto yy7;
	default:	goto yy5;
	}
yy5:
#line 20 "repeater.re"
{RET(0);}
#line 41 "<stdout>"
yy6:	yych = *++YYCURSOR;
	goto yy5;
yy7:	yych = *++YYCURSOR;
	switch(yych){
	case 0x0A:	goto yy11;
	case 'A':	case 'a':	goto yy10;
	default:	goto yy2;
	}
yy8:	++YYCURSOR;
	goto yy9;
yy9:
#line 16 "repeater.re"
{RET(1);}
#line 55 "<stdout>"
yy10:	yych = *++YYCURSOR;
	switch(yych){
	case 0x0A:	goto yy11;
	case 'A':	case 'a':	goto yy13;
	default:	goto yy2;
	}
yy11:	++YYCURSOR;
	goto yy12;
yy12:
#line 17 "repeater.re"
{RET(2);}
#line 67 "<stdout>"
yy13:	yych = *++YYCURSOR;
	switch(yych){
	case 0x0A:	goto yy15;
	case 'A':	case 'a':	goto yy14;
	default:	goto yy2;
	}
yy14:	yych = *++YYCURSOR;
	switch(yych){
	case 0x0A:	goto yy15;
	case 'A':	case 'a':	goto yy17;
	default:	goto yy2;
	}
yy15:	++YYCURSOR;
	goto yy16;
yy16:
#line 19 "repeater.re"
{RET(3);}
#line 85 "<stdout>"
yy17:	yych = *++YYCURSOR;
	switch(yych){
	case 0x0A:	goto yy18;
	default:	goto yy21;
	}
yy18:	++YYCURSOR;
	goto yy19;
yy19:
#line 18 "repeater.re"
{RET(4);}
#line 96 "<stdout>"
yy20:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy21;
yy21:	switch(yych){
	case 0x0A:	goto yy15;
	case 'A':	case 'a':	goto yy20;
	default:	goto yy2;
	}
}
#line 21 "repeater.re"

}

#define do_scan(str) scan(str, strlen(str))

main()
{
	do_scan("a\n");
	do_scan("aa\n");
	do_scan("aaa\n");
	do_scan("aaaa\n");
	do_scan("q");
	do_scan("a");
	do_scan("A\n");
	do_scan("AA\n");
	do_scan("aAa\n");
	do_scan("AaaA\n");
	do_scan("Q");
	do_scan("AaaAa\n");
	do_scan("AaaAaA\n");
	do_scan("A");
	do_scan("\n");
	do_scan("0");
}
