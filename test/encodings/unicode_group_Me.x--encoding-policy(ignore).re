// re2c $INPUT -o $OUTPUT -x --encoding-policy ignore
#include <stdio.h>
#include "utf16.h"
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Me:
	/*!re2c
		re2c:yyfill:enable = 0;
		Me = [\u0488-\u0489\u1abe-\u1abe\u20dd-\u20e0\u20e2-\u20e4\ua670-\ua672];
		Me { goto Me; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Me [] = {0x488,0x489,  0x1abe,0x1abe,  0x20dd,0x20e0,  0x20e2,0x20e4,  0xa670,0xa672,  0x0,0x0};
static unsigned int encode_utf16 (const unsigned int * ranges, unsigned int ranges_count, unsigned int * s)
{
	unsigned int * const s_start = s;
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
	unsigned int * buffer_Me = new unsigned int [28];
	YYCTYPE * s = (YYCTYPE *) buffer_Me;
	unsigned int buffer_len = encode_utf16 (chars_Me, sizeof (chars_Me) / sizeof (unsigned int), buffer_Me);
	/* convert 32-bit code units to YYCTYPE; reuse the same buffer */
	for (unsigned int i = 0; i < buffer_len; ++i) s[i] = buffer_Me[i];
	if (!scan (s, s + buffer_len))
		printf("test 'Me' failed\n");
	delete [] buffer_Me;
	return 0;
}
