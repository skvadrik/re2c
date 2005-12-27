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

	'a'{,}"\n"      {RET(1);}
	any             {RET(0);}
*/
}
