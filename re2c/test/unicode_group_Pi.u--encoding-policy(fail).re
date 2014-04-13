#include <stdio.h>
#define YYCTYPE unsigned int
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Pi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Pi = [\xab-\xab\u2018-\u2018\u201b-\u201c\u201f-\u201f\u2039-\u2039\u2e02-\u2e02\u2e04-\u2e04\u2e09-\u2e09\u2e0c-\u2e0c\u2e1c-\u2e1c\u2e20-\u2e20];
		Pi { goto Pi; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Pi [] = "\xAB\x00\x00\x00\x18\x20\x00\x00\x1B\x20\x00\x00\x1C\x20\x00\x00\x1F\x20\x00\x00\x39\x20\x00\x00\x02\x2E\x00\x00\x04\x2E\x00\x00\x09\x2E\x00\x00\x0C\x2E\x00\x00\x1C\x2E\x00\x00\x20\x2E\x00\x00\x00\x00\x00\x00";
int main ()
{
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Pi), reinterpret_cast<const YYCTYPE *> (buffer_Pi + sizeof (buffer_Pi) - 1)))
		printf("test 'Pi' failed\n");
}
