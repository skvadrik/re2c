// re2c $INPUT -o $OUTPUT -cg
#include <stdio.h>

// changing this to '#if 1' changes program behaviour
#if 0
#    define yyca 1
#    define yycb 0
#else
#    define yyca 0
#    define yycb 1
#endif

int main ()
{
	int cond = yyca;
	char * YYCURSOR = "aaaaaaaabb";
#define YYSETCONDITION(c) cond = c
#define YYGETCONDITION() cond
	for (;;)
	{
/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE = "unsigned char";

	<b> [^] { printf ("b\n"); break; }

	<a> "a"       { printf ("a\n");      continue; }
	<a> [^a] => b { printf ("a => b\n"); continue; }
*/
	}
	return 0;
}
