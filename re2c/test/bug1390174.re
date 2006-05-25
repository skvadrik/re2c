#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RET(n) return n

int scan(const char *s, int l) {
const char *p = s;
const char *q;
#define YYCTYPE         char
#define YYCURSOR        p
#define YYLIMIT         (s+l)
#define YYMARKER        q
#define YYFILL(n)
/*!re2c
	any     = [\000-\377];

	'a'{0,}"\n"     {RET(1);}
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
	do_scan(1, "aa\n");
	do_scan(1, "aaa\n");
	do_scan(1, "aaaa\n");
	do_scan(1, "\n");

	do_scan(0, "q");
	do_scan(0, "a");
}
