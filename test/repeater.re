#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RET(n) return n

int scan(const char *s, int l){
const char *p = s;
const char *q;
#define YYCTYPE         char
#define YYCURSOR        p
#define YYLIMIT         (s+l)
#define YYMARKER        q
#define YYFILL(n)
/*!re2c
	any     = [\000-\377];

	'a'{1}"\n"      {RET(1);}
	'a'{2,3}"\n"    {RET(2);}
	'a'{6}"\n"      {RET(3);}
	'a'{4,}"\n"	    {RET(4);}
	[^aq\n]         {RET(5);}
	any             {RET(0);}
*/
}

void _do_scan(int exp, const char * str, int len)
{
	int ret = scan(str, len);
	
	printf("%d %s %d\n", exp, exp == ret ? "==" : "!=", ret);
}

#define do_scan(exp, str) _do_scan(exp, str, sizeof(str) - 1)

main()
{
	do_scan(1, "a\n");
	do_scan(2, "aa\n");
	do_scan(2, "aaa\n");
	do_scan(4, "aaaa\n");
	do_scan(0, "q");
	do_scan(0, "a");
	do_scan(1, "A\n");
	do_scan(2, "AA\n");
	do_scan(2, "aAa\n");
	do_scan(4, "AaaA\n");
	do_scan(5, "Q");
	do_scan(4, "AaaAa\n");
	do_scan(3, "AaaAaA\n");
	do_scan(5, "A");
	do_scan(0, "\n");
	do_scan(5, "0");
	do_scan(0, "a");
	do_scan(0, "q");
	do_scan(5, "x");
}
