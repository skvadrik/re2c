#include <stdio.h>
#include "utf16.h"
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Pc:
	/*!re2c
		re2c:yyfill:enable = 0;
		Pc = [\x5f-\x5f\u203f-\u2040\u2054-\u2054\ufe33-\ufe34\ufe4d-\ufe4f\uff3f-\uff3f];
		Pc { goto Pc; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Pc [] = {0x5f,0x5f,  0x203f,0x2040,  0x2054,0x2054,  0xfe33,0xfe34,  0xfe4d,0xfe4f,  0xff3f,0xff3f,  0x0,0x0};
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
	YYCTYPE * buffer_Pc = new YYCTYPE [22];
	unsigned int buffer_len = encode_utf16 (chars_Pc, sizeof (chars_Pc) / sizeof (unsigned int), buffer_Pc);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Pc), reinterpret_cast<const YYCTYPE *> (buffer_Pc + buffer_len)))
		printf("test 'Pc' failed\n");
	delete [] buffer_Pc;
	return 0;
}
