#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define YYGETCONDITION()  yy_state
#define YYSETCONDITION(s) yy_state = s
#define YYCTYPE         char
#define YYCURSOR        p
#define YYLIMIT         (s+l)
#define YYMARKER        q
#define YYFILL(n)

#define STATE(name)  yyc##name

static enum YYCONDTYPE yy_state;

/*!types:re2c */

int scan(char *s, int l)
{
	char *p = s;
	char *q = 0;
	char *t;

	for(;;)
	{
		t = p;
/*!re2c
	re2c:indent:top = 2;

	TABS_AND_SPACES = [ \t]*;
	LITERAL_DOLLAR = "$"[a-zA-Z];

	<INITIAL>LITERAL_DOLLAR {
		printf("FOUND %s\n", t);
		continue;
	}

	<ST_VALUE>LITERAL_DOLLAR+ {
		printf("Found $ or $\\<x>\n");
		continue;
	}

	<ST_VALUE>TABS_AND_SPACES {
		YYSETCONDITION(STATE(INITIAL));
		printf("Found spaces\n");
	}

	<INITIAL>"\000"		{ printf("EOF\n");	return 0; }
	<INITIAL>[^]			{ printf("ERR\n");	return 1; }

*/
	}
}

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		return scan(argv[1], strlen(argv[1]));
	}
	else
	{
		fprintf(stderr, "%s <expr>\n", argv[0]);
		return 1;
	}
}
