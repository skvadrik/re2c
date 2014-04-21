#include <stdio.h>

#define YYCTYPE unsigned int
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Pd:
	/*!re2c
		re2c:yyfill:enable = 0;
		Pd = [\x2d-\x2d\u058a-\u058a\u05be-\u05be\u1400-\u1400\u1806-\u1806\u2010-\u2015\u2e17-\u2e17\u2e1a-\u2e1a\u301c-\u301c\u3030-\u3030\u30a0-\u30a0\ufe31-\ufe32\ufe58-\ufe58\ufe63-\ufe63\uff0d-\uff0d];
		Pd { goto Pd; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Pd [] = {0x2d,0x2d,  0x58a,0x58a,  0x5be,0x5be,  0x1400,0x1400,  0x1806,0x1806,  0x2010,0x2015,  0x2e17,0x2e17,  0x2e1a,0x2e1a,  0x301c,0x301c,  0x3030,0x3030,  0x30a0,0x30a0,  0xfe31,0xfe32,  0xfe58,0xfe58,  0xfe63,0xfe63,  0xff0d,0xff0d,  0x0,0x0};
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
	YYCTYPE * buffer_Pd = new YYCTYPE [22];
	unsigned int buffer_len = encode_utf32 (chars_Pd, sizeof (chars_Pd) / sizeof (unsigned int), buffer_Pd);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Pd), reinterpret_cast<const YYCTYPE *> (buffer_Pd + buffer_len)))
		printf("test 'Pd' failed\n");
	delete [] buffer_Pd;
	return 0;
}
