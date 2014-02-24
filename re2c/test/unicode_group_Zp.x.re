#include <stdio.h>
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Zp:
	/*!re2c
		re2c:yyfill:enable = 0;
				Zp = [\u2029-\u2029];
		Zp { goto Zp; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Zp [] = "\x29\x20\x00\x00";
int main ()
{
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Zp), reinterpret_cast<const YYCTYPE *> (buffer_Zp + sizeof (buffer_Zp) - 1)))
		printf("test 'Zp' failed\n");
}
