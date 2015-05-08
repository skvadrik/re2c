#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RET(n)	printf("%d\n", n); return n
#define TAG_EOI	0
#define TAG_A	1
#define TAG_TAG	2

int scan(char *s, int l)
{
	char *p = s;
	char *q;
#define YYCTYPE         char
#define YYCURSOR        p
#define YYLIMIT         (s+l)
#define YYMARKER        q
#define YYFILL(n)
cont:
/*!re2c
any = [\000-\377];
(["] ([\000-\376]\["])+ ["]) { RET(1); }
any				{ goto cont; }
*/
}

#define do_scan(str) scan(str, strlen(str))

main()
{
	do_scan("0");
}
