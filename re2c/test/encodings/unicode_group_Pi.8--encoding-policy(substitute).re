#include <stdio.h>
#include "utf8.h"
#define YYCTYPE unsigned char
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Pi:
	/*!re2c
		re2c:yyfill:enable = 0;
		Pi = [\xab-\xab\u2018-\u2018\u201b-\u201c\u201f-\u201f\u2039-\u2039\u2e02-\u2e02\u2e04-\u2e04\u2e09-\u2e09\u2e0c-\u2e0c\u2e1c-\u2e1c\u2e20-\u2e20];
		Pi { goto Pi; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Pi [] = {0xab,0xab,  0x2018,0x2018,  0x201b,0x201c,  0x201f,0x201f,  0x2039,0x2039,  0x2e02,0x2e02,  0x2e04,0x2e04,  0x2e09,0x2e09,  0x2e0c,0x2e0c,  0x2e1c,0x2e1c,  0x2e20,0x2e20,  0x0,0x0};
static unsigned int encode_utf8 (const unsigned int * ranges, unsigned int ranges_count, unsigned char * s)
{
	unsigned char * const s_start = s;
	for (unsigned int i = 0; i < ranges_count - 2; i += 2)
		for (unsigned int j = ranges[i]; j <= ranges[i + 1]; ++j)
			s += re2c::utf8::rune_to_bytes (s, j);
	re2c::utf8::rune_to_bytes (s, ranges[ranges_count - 1]);
	return s - s_start + 1;
}

int main ()
{
	YYCTYPE * buffer_Pi = new YYCTYPE [52];
	unsigned int buffer_len = encode_utf8 (chars_Pi, sizeof (chars_Pi) / sizeof (unsigned int), buffer_Pi);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Pi), reinterpret_cast<const YYCTYPE *> (buffer_Pi + buffer_len)))
		printf("test 'Pi' failed\n");
	delete [] buffer_Pi;
	return 0;
}
