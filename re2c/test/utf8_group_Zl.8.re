#include <stdio.h>
bool scan(const char * start, const char * const limit)
{
	__attribute__((unused)) const char * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCTYPE unsigned char
#	define YYCURSOR start
Zl:
	/*!re2c
		re2c:yyfill:enable = 0;
				Zl = [\u2028-\u2028];
		Zl { goto Zl; }
		* { return YYCURSOR == limit; }
	*/
}
static const char buffer_Zl [] = "\xE2\x80\xA8\xFF";
int main ()
{
	if (!scan (buffer_Zl, buffer_Zl + sizeof (buffer_Zl) - 1))
		printf("test 'Zl' failed\n");
}
