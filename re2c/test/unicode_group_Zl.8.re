#include <stdio.h>
#define YYCTYPE unsigned char
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Zl:
	/*!re2c
		re2c:yyfill:enable = 0;
				Zl = [\u2028-\u2028];
		Zl { goto Zl; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Zl [] = "\xE2\x80\xA8\x00";
int main ()
{
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Zl), reinterpret_cast<const YYCTYPE *> (buffer_Zl + sizeof (buffer_Zl) - 1)))
		printf("test 'Zl' failed\n");
}
