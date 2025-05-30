/* Generated by re2c */
#line 1 "c/submatch/03_captures.re"
// re2c $INPUT -o $OUTPUT
#include <assert.h>
#include <stddef.h>

typedef struct { int major, minor, patch; } SemVer;

static int s2n(const char *s, const char *e) { // pre-parsed string to number
    int n = 0;
    for (; s < e; ++s) n = n * 10 + (*s - '0');
    return n;
}

static int lex(const char *str, SemVer *ver) {
    const char *YYCURSOR = str, *YYMARKER;

    // Final tag variables available in semantic action.
    
#line 21 "c/submatch/03_captures.c"
const char *yytl0;
const char *yytl1;
const char *yytl2;
const char *yytl3;
const char *yytr0;
const char *yytr1;
const char *yytr2;
const char *yytr3;
#line 17 "c/submatch/03_captures.re"


    // Intermediate tag variables used by the lexer (must be autogenerated).
    
#line 35 "c/submatch/03_captures.c"
const char *yyt1;
const char *yyt2;
const char *yyt3;
const char *yyt4;
const char *yyt5;
#line 20 "c/submatch/03_captures.re"


    
#line 45 "c/submatch/03_captures.c"
{
	char yych;
	yych = *YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			yyt1 = YYCURSOR;
			goto yy3;
		default: goto yy1;
	}
yy1:
	++YYCURSOR;
yy2:
#line 36 "c/submatch/03_captures.re"
	{ return 1; }
#line 69 "c/submatch/03_captures.c"
yy3:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case '.': goto yy4;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy6;
		default: goto yy2;
	}
yy4:
	yych = *++YYCURSOR;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			yyt2 = YYCURSOR;
			goto yy7;
		default: goto yy5;
	}
yy5:
	YYCURSOR = YYMARKER;
	goto yy2;
yy6:
	yych = *++YYCURSOR;
	switch (yych) {
		case '.': goto yy4;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy6;
		default: goto yy5;
	}
yy7:
	yych = *++YYCURSOR;
	switch (yych) {
		case 0x00:
			yyt3 = YYCURSOR;
			yyt4 = NULL;
			yyt5 = NULL;
			goto yy8;
		case '.':
			yyt3 = YYCURSOR;
			yyt5 = YYCURSOR;
			goto yy9;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy7;
		default: goto yy5;
	}
yy8:
	++YYCURSOR;
	yytl1 = yyt1;
	yytl2 = yyt2;
	yytr2 = yyt3;
	yytl3 = yyt5;
	yytr3 = yyt4;
	yytl0 = yyt1;
	yytr0 = YYCURSOR;
	yytr1 = yyt2;
	yytr1 -= 1;
#line 29 "c/submatch/03_captures.re"
	{
            (void) yytl0; (void) yytr0; // some variables are unused
            ver->major = s2n(yytl1, yytr1);
            ver->minor = s2n(yytl2, yytr2);
            ver->patch = yytl3 ? s2n(yytl3 + 1, yytr3) : 0;
            return 0;
        }
#line 165 "c/submatch/03_captures.c"
yy9:
	yych = *++YYCURSOR;
	if (yych <= 0x00) goto yy5;
	goto yy11;
yy10:
	yych = *++YYCURSOR;
yy11:
	switch (yych) {
		case 0x00:
			yyt4 = YYCURSOR;
			goto yy8;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy10;
		default: goto yy5;
	}
}
#line 37 "c/submatch/03_captures.re"

}

int main() {
    SemVer v;
    assert(lex("23.34", &v) == 0 && v.major == 23 && v.minor == 34 && v.patch == 0);
    assert(lex("1.2.999", &v) == 0 && v.major == 1 && v.minor == 2 && v.patch == 999);
    assert(lex("1.a", &v) == 1);
    return 0;
}
