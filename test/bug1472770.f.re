#define NULL ((char*) 0)
#define YYCTYPE char
#define YYCURSOR p
#define YYLIMIT p
#define YYMARKER q
#define YYFILL(n)

YYCTYPE yych;
int yySavedState;

#define YYGETSTATE()	yySavedState
#define YYSETSTATE(n)	yySavedState = n;

#include <stdio.h>

int scan(char *p)
{
	int n = 0;
	char *q;
	
	printf("[--------------\n");
	printf("%s\n", p);
	printf("]--------------\n");
start:
/*!re2c
[^\n\000]* '\n'
	{
		++n;
		goto start;
	}
[^\n\000]* '\000'
	{
		return n;
	}
*/
}

int main(int argc, char **argv)
{
	int n = 0;
	char *largv[4];

	if (argc < 2)
	{
		argc = 4;
		argv = largv;
		argv[1] = "";
		argv[2] = "1\n\n";
		argv[3] = "1\n2\n";
	}
	while(++n < argc)
	{
		printf("%d\n", scan(argv[n]));
	}
	return 0;
}
