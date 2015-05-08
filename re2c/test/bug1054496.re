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
any = [\001-\377];
'<a' 			{ RET(TAG_A); }
[<][A-Za-z]+	{ RET(TAG_TAG); }
[\000]			{ RET(TAG_EOI); }
any				{ goto cont; }
*/
}

#define do_scan(str) scan(str, strlen(str))

main()
{
	do_scan("0");
}
