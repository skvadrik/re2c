#include <stdio.h>

#define YYCTYPE unsigned int
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Z:
	/*!re2c
		re2c:yyfill:enable = 0;
		Z = [\x20-\x20\xa0-\xa0\u1680-\u1680\u180e-\u180e\u2000-\u200a\u2028-\u2029\u202f-\u202f\u205f-\u205f\u3000-\u3000];
		Z { goto Z; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Z [] = {0x20,0x20,  0xa0,0xa0,  0x1680,0x1680,  0x180e,0x180e,  0x2000,0x200a,  0x2028,0x2029,  0x202f,0x202f,  0x205f,0x205f,  0x3000,0x3000,  0x0,0x0};
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
	YYCTYPE * buffer_Z = new YYCTYPE [21];
	unsigned int buffer_len = encode_utf32 (chars_Z, sizeof (chars_Z) / sizeof (unsigned int), buffer_Z);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Z), reinterpret_cast<const YYCTYPE *> (buffer_Z + buffer_len)))
		printf("test 'Z' failed\n");
	delete [] buffer_Z;
	return 0;
}
