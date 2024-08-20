/* Generated by re2c */
#line 1 "c/reuse/usedir.re"
// re2c $INPUT -o $OUTPUT
#include <assert.h>

// This example shows how to combine reusable re2c blocks: two blocks
// ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
// in both blocks; the 'fish' block takes priority because it is used
// earlier. Default rule * occurs in all three blocks; the local (not
// inherited) definition takes priority.

enum What { COLOR, FISH, DUNNO };

#line 15 "c/reuse/usedir.re"


#line 20 "c/reuse/usedir.re"


static What lex(const char *s) {
    const char *YYCURSOR = s, *YYMARKER;
    
#line 24 "c/reuse/usedir.c"
{
	char yych;
	yych = *YYCURSOR;
	switch (yych) {
		case 'e': goto yy3;
		case 'h': goto yy4;
		case 'm': goto yy5;
		case 'r': goto yy6;
		case 's': goto yy7;
		default: goto yy1;
	}
yy1:
	++YYCURSOR;
yy2:
#line 30 "c/reuse/usedir.re"
	{ return DUNNO; }
#line 41 "c/reuse/usedir.c"
yy3:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 'e': goto yy8;
		default: goto yy2;
	}
yy4:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 'a': goto yy10;
		default: goto yy2;
	}
yy5:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 'a': goto yy11;
		default: goto yy2;
	}
yy6:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 'e': goto yy12;
		default: goto yy2;
	}
yy7:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case 'a': goto yy13;
		default: goto yy2;
	}
yy8:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'l': goto yy14;
		default: goto yy9;
	}
yy9:
	YYCURSOR = YYMARKER;
	goto yy2;
yy10:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'd': goto yy15;
		default: goto yy9;
	}
yy11:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'g': goto yy16;
		default: goto yy9;
	}
yy12:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'd': goto yy17;
		default: goto yy9;
	}
yy13:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'l': goto yy18;
		default: goto yy9;
	}
yy14:
	++YYCURSOR;
#line 19 "c/reuse/usedir.re"
	{ return FISH; }
#line 109 "c/reuse/usedir.c"
yy15:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'd': goto yy19;
		default: goto yy9;
	}
yy16:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'e': goto yy20;
		default: goto yy9;
	}
yy17:
	++YYCURSOR;
#line 14 "c/reuse/usedir.re"
	{ return COLOR; }
#line 126 "c/reuse/usedir.c"
yy18:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'm': goto yy21;
		default: goto yy9;
	}
yy19:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'o': goto yy22;
		default: goto yy9;
	}
yy20:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'n': goto yy23;
		default: goto yy9;
	}
yy21:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'o': goto yy24;
		default: goto yy9;
	}
yy22:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'c': goto yy25;
		default: goto yy9;
	}
yy23:
	yych = *++YYCURSOR;
	switch (yych) {
		case 't': goto yy26;
		default: goto yy9;
	}
yy24:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'n': goto yy14;
		default: goto yy9;
	}
yy25:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'k': goto yy14;
		default: goto yy9;
	}
yy26:
	yych = *++YYCURSOR;
	switch (yych) {
		case 'a': goto yy17;
		default: goto yy9;
	}
}
#line 31 "c/reuse/usedir.re"

}

int main() {
    assert(lex("salmon") == FISH);
    assert(lex("what?") == DUNNO);
    return 0;
}