#include <stdio.h>

#define YYCTYPE unsigned int
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
static unsigned int encode_utf32 (const unsigned int * ranges, unsigned int ranges_count, unsigned int * s)
{
	unsigned int * const s_start = s;
	for (unsigned int i = 0; i < ranges_count; i += 2)
		for (unsigned int j = ranges[i]; j <= ranges[i + 1]; ++j)
			*s++ = j;
	return s - s_start;
}

int main ()
{
	YYCTYPE * buffer_Zp = new YYCTYPE [2];
	unsigned int buffer_len = encode_utf32 (chars_Zp, sizeof (chars_Zp) / sizeof (unsigned int), buffer_Zp);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Zp), reinterpret_cast<const YYCTYPE *> (buffer_Zp + buffer_len)))
		printf("test 'Zp' failed\n");
	delete [] buffer_Zp;
	return 0;
}
