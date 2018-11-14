#include <stdio.h>

#define YYCTYPE unsigned int
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Me:
	/*!re2c
		re2c:yyfill:enable = 0;
		Me = [\u0488-\u0489\u20dd-\u20e0\u20e2-\u20e4\ua670-\ua672];
		Me { goto Me; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Me [] = {0x488,0x489,  0x20dd,0x20e0,  0x20e2,0x20e4,  0xa670,0xa672,  0x0,0x0};
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
	YYCTYPE * buffer_Me = new YYCTYPE [13];
	unsigned int buffer_len = encode_utf32 (chars_Me, sizeof (chars_Me) / sizeof (unsigned int), buffer_Me);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Me), reinterpret_cast<const YYCTYPE *> (buffer_Me + buffer_len)))
		printf("test 'Me' failed\n");
	delete [] buffer_Me;
	return 0;
}
