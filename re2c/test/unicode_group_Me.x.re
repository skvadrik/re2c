#include <stdio.h>
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Me:
	/*!re2c
		re2c:yyfill:enable = 0;
				Me = [\u0488-\u0489\u20dd-\u20e0\u20e2-\u20e4\ua670-\ua672];
		Me { goto Me; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Me [] = "\x88\x04\x89\x04\xDD\x20\xDE\x20\xDF\x20\xE0\x20\xE2\x20\xE3\x20\xE4\x20\x70\xA6\x71\xA6\x72\xA6\x00\x00";
int main ()
{
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Me), reinterpret_cast<const YYCTYPE *> (buffer_Me + sizeof (buffer_Me) - 1)))
		printf("test 'Me' failed\n");
}
