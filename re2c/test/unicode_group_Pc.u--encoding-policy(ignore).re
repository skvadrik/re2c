#include <stdio.h>
#define YYCTYPE unsigned int
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Pc:
	/*!re2c
		re2c:yyfill:enable = 0;
		Pc = [\x5f-\x5f\u203f-\u2040\u2054-\u2054\ufe33-\ufe34\ufe4d-\ufe4f\uff3f-\uff3f];
		Pc { goto Pc; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Pc [] = "\x5F\x00\x00\x00\x3F\x20\x00\x00\x40\x20\x00\x00\x54\x20\x00\x00\x33\xFE\x00\x00\x34\xFE\x00\x00\x4D\xFE\x00\x00\x4E\xFE\x00\x00\x4F\xFE\x00\x00\x3F\xFF\x00\x00\x00\x00\x00\x00";
int main ()
{
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Pc), reinterpret_cast<const YYCTYPE *> (buffer_Pc + sizeof (buffer_Pc) - 1)))
		printf("test 'Pc' failed\n");
}
