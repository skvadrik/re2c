/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -i --tags
#include <stddef.h>
#include <stdio.h>

static void lex(const char *YYCURSOR)
{
    const char *YYMARKER, *p0, *p1, *p2, *p3, *p4;
    const char *yyt1;const char *yyt2;
    
{
	char yych;
	yych = *YYCURSOR;
	switch (yych) {
		case '0': goto yy3;
		default: goto yy1;
	}
yy1:
	++YYCURSOR;
yy2:
	{ printf("error\n"); return; }
yy3:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
		case '1':
			yyt1 = YYCURSOR;
			goto yy4;
		case '2':
			yyt1 = YYCURSOR;
			goto yy6;
		default: goto yy2;
	}
yy4:
	yych = *++YYCURSOR;
	switch (yych) {
		case '1': goto yy4;
		case '2': goto yy6;
		default: goto yy5;
	}
yy5:
	YYCURSOR = YYMARKER;
	goto yy2;
yy6:
	yych = *++YYCURSOR;
	switch (yych) {
		case '3':
			yyt2 = YYCURSOR;
			goto yy7;
		case '4':
			yyt2 = YYCURSOR;
			goto yy8;
		default: goto yy5;
	}
yy7:
	yych = *++YYCURSOR;
	switch (yych) {
		case '3': goto yy7;
		case '4': goto yy8;
		default: goto yy5;
	}
yy8:
	++YYCURSOR;
	p1 = yyt1;
	p3 = yyt2;
	p0 = yyt1;
	p0 -= 1;
	p2 = yyt2;
	p2 -= 1;
	p4 = YYCURSOR;
	p4 -= 1;
	{
            printf("'%.*s', '%.*s', '%.*s', '%.*s', '%.*s'\n",
                p1 - p0, p0,
                p2 - p1, p1,
                p3 - p2, p2,
                p4 - p3, p3,
                YYCURSOR - p4, p4);
                return;
        }
}

}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        lex(argv[i]);
    }
    return 0;
}
