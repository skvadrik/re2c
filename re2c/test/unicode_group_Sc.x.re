#include <stdio.h>
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Sc:
	/*!re2c
		re2c:yyfill:enable = 0;
				Sc = [\x24-\x24\xa2-\xa5\u060b-\u060b\u09f2-\u09f3\u09fb-\u09fb\u0af1-\u0af1\u0bf9-\u0bf9\u0e3f-\u0e3f\u17db-\u17db\u20a0-\u20b9\ua838-\ua838\ufdfc-\ufdfc\ufe69-\ufe69\uff04-\uff04\uffe0-\uffe1\uffe5-\uffe6];
		Sc { goto Sc; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Sc [] = "\x24\x00\xA2\x00\xA3\x00\xA4\x00\xA5\x00\x0B\x06\xF2\x09\xF3\x09\xFB\x09\xF1\x0A\xF9\x0B\x3F\x0E\xDB\x17\xA0\x20\xA1\x20\xA2\x20\xA3\x20\xA4\x20\xA5\x20\xA6\x20\xA7\x20\xA8\x20\xA9\x20\xAA\x20\xAB\x20\xAC\x20\xAD\x20\xAE\x20\xAF\x20\xB0\x20\xB1\x20\xB2\x20\xB3\x20\xB4\x20\xB5\x20\xB6\x20\xB7\x20\xB8\x20\xB9\x20\x38\xA8\xFC\xFD\x69\xFE\x04\xFF\xE0\xFF\xE1\xFF\xE5\xFF\xE6\xFF\x00\x00";
int main ()
{
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Sc), reinterpret_cast<const YYCTYPE *> (buffer_Sc + sizeof (buffer_Sc) - 1)))
		printf("test 'Sc' failed\n");
}
