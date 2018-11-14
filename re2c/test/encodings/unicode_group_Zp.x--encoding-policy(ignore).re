#include <stdio.h>
#include "utf16.h"
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Zp:
	/*!re2c
		re2c:yyfill:enable = 0;
		Zp = [\u2029-\u2029];
		Zp { goto Zp; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Zp [] = {0x2029,0x2029,  0x0,0x0};
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
	YYCTYPE * buffer_Zp = new YYCTYPE [4];
	unsigned int buffer_len = encode_utf16 (chars_Zp, sizeof (chars_Zp) / sizeof (unsigned int), buffer_Zp);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Zp), reinterpret_cast<const YYCTYPE *> (buffer_Zp + buffer_len)))
		printf("test 'Zp' failed\n");
	delete [] buffer_Zp;
	return 0;
}
