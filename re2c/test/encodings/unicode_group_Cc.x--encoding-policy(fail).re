#include <stdio.h>
#include "utf16.h"
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Cc:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cc = [\x00-\x1f\x7f-\x9f];
		Cc { goto Cc; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Cc [] = {0x0,0x1f,  0x7f,0x9f,  0x20,0x20};
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
	YYCTYPE * buffer_Cc = new YYCTYPE [132];
	unsigned int buffer_len = encode_utf16 (chars_Cc, sizeof (chars_Cc) / sizeof (unsigned int), buffer_Cc);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Cc), reinterpret_cast<const YYCTYPE *> (buffer_Cc + buffer_len)))
		printf("test 'Cc' failed\n");
	delete [] buffer_Cc;
	return 0;
}
