#include <stdio.h>

#define YYCTYPE unsigned int
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Zl:
	/*!re2c
		re2c:yyfill:enable = 0;
		Zl = [\u2028-\u2028];
		Zl { goto Zl; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Zl [] = {0x2028,0x2028,  0x0,0x0};
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
	YYCTYPE * buffer_Zl = new YYCTYPE [2];
	unsigned int buffer_len = encode_utf32 (chars_Zl, sizeof (chars_Zl) / sizeof (unsigned int), buffer_Zl);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Zl), reinterpret_cast<const YYCTYPE *> (buffer_Zl + buffer_len)))
		printf("test 'Zl' failed\n");
	delete [] buffer_Zl;
	return 0;
}
