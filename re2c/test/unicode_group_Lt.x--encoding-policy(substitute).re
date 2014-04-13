#include <stdio.h>
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Lt:
	/*!re2c
		re2c:yyfill:enable = 0;
		Lt = [\u01c5-\u01c5\u01c8-\u01c8\u01cb-\u01cb\u01f2-\u01f2\u1f88-\u1f8f\u1f98-\u1f9f\u1fa8-\u1faf\u1fbc-\u1fbc\u1fcc-\u1fcc\u1ffc-\u1ffc];
		Lt { goto Lt; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Lt [] = "\xC5\x01\xC8\x01\xCB\x01\xF2\x01\x88\x1F\x89\x1F\x8A\x1F\x8B\x1F\x8C\x1F\x8D\x1F\x8E\x1F\x8F\x1F\x98\x1F\x99\x1F\x9A\x1F\x9B\x1F\x9C\x1F\x9D\x1F\x9E\x1F\x9F\x1F\xA8\x1F\xA9\x1F\xAA\x1F\xAB\x1F\xAC\x1F\xAD\x1F\xAE\x1F\xAF\x1F\xBC\x1F\xCC\x1F\xFC\x1F\x00\x00";
int main ()
{
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Lt), reinterpret_cast<const YYCTYPE *> (buffer_Lt + sizeof (buffer_Lt) - 1)))
		printf("test 'Lt' failed\n");
}
