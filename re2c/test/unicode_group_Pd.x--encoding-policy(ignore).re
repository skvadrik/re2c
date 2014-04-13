#include <stdio.h>
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Pd:
	/*!re2c
		re2c:yyfill:enable = 0;
		Pd = [\x2d-\x2d\u058a-\u058a\u05be-\u05be\u1400-\u1400\u1806-\u1806\u2010-\u2015\u2e17-\u2e17\u2e1a-\u2e1a\u301c-\u301c\u3030-\u3030\u30a0-\u30a0\ufe31-\ufe32\ufe58-\ufe58\ufe63-\ufe63\uff0d-\uff0d];
		Pd { goto Pd; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Pd [] = "\x2D\x00\x8A\x05\xBE\x05\x00\x14\x06\x18\x10\x20\x11\x20\x12\x20\x13\x20\x14\x20\x15\x20\x17\x2E\x1A\x2E\x1C\x30\x30\x30\xA0\x30\x31\xFE\x32\xFE\x58\xFE\x63\xFE\x0D\xFF\x00\x00";
int main ()
{
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Pd), reinterpret_cast<const YYCTYPE *> (buffer_Pd + sizeof (buffer_Pd) - 1)))
		printf("test 'Pd' failed\n");
}
