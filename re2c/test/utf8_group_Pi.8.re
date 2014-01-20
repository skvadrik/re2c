#include <stdio.h>
bool scan(const char * start, const char * const limit)
{
#	define YYCTYPE unsigned char
#	define YYCURSOR start
Pi:
	/*!re2c
		re2c:yyfill:enable = 0;
				Pi = [\xab-\xab\u2018-\u2018\u201b-\u201c\u201f-\u201f\u2039-\u2039\u2e02-\u2e02\u2e04-\u2e04\u2e09-\u2e09\u2e0c-\u2e0c\u2e1c-\u2e1c\u2e20-\u2e20];
		Pi { goto Pi; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Pi [] = "\xC2\xAB\xE2\x80\x98\xE2\x80\x9B\xE2\x80\x9C\xE2\x80\x9F\xE2\x80\xB9\xE2\xB8\x82\xE2\xB8\x84\xE2\xB8\x89\xE2\xB8\x8C\xE2\xB8\x9C\xE2\xB8\xA0\x00";
int main ()
{
	if (!scan (buffer_Pi, buffer_Pi + sizeof (buffer_Pi) - 1))
		printf("test 'Pi' failed\n");
}
