#include <stdio.h>
#include "utf16.h"
#define YYCTYPE unsigned short
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
static unsigned int encode_utf16 (const unsigned int * ranges, unsigned int ranges_count, unsigned short * s)
{
	unsigned short * const s_start = s;
	for (unsigned int i = 0; i < ranges_count; i += 2)
		for (unsigned int j = ranges[i]; j <= ranges[i + 1]; ++j)
		{
			if (j <= re2c::utf16::MAX_1WORD_RUNE)
				*s++ = j;
			else
			{
				*s++ = re2c::utf16::lead_surr(j);
				*s++ = re2c::utf16::trail_surr(j);
			}
		}
	return s - s_start;
}

int main ()
{
	YYCTYPE * buffer_Pi = new YYCTYPE [26];
	unsigned int buffer_len = encode_utf16 (chars_Pi, sizeof (chars_Pi) / sizeof (unsigned int), buffer_Pi);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Pi), reinterpret_cast<const YYCTYPE *> (buffer_Pi + buffer_len)))
		printf("test 'Pi' failed\n");
	delete [] buffer_Pi;
	return 0;
}
