// re2c $INPUT -o $OUTPUT -8 --encoding-policy fail
#include <stdio.h>
#include "utf8.h"
#define YYCTYPE unsigned char
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Zs:
	/*!re2c
		re2c:yyfill:enable = 0;
		Zs = [\x20-\x20\xa0-\xa0\u1680-\u1680\u2000-\u200a\u202f-\u202f\u205f-\u205f\u3000-\u3000];
		Zs { goto Zs; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Zs [] = {0x20,0x20,  0xa0,0xa0,  0x1680,0x1680,  0x2000,0x200a,  0x202f,0x202f,  0x205f,0x205f,  0x3000,0x3000,  0x0,0x0};
static unsigned int encode_utf8 (const unsigned int * ranges, unsigned int ranges_count, unsigned int * s)
{
	unsigned int * const s_start = s;
	for (unsigned int i = 0; i < ranges_count - 2; i += 2)
		for (unsigned int j = ranges[i]; j <= ranges[i + 1]; ++j)
			s += re2c::utf8::rune_to_bytes (s, j);
	re2c::utf8::rune_to_bytes (s, ranges[ranges_count - 1]);
	return s - s_start + 1;
}

int main ()
{
	unsigned int * buffer_Zs = new unsigned int [72];
	YYCTYPE * s = (YYCTYPE *) buffer_Zs;
	unsigned int buffer_len = encode_utf8 (chars_Zs, sizeof (chars_Zs) / sizeof (unsigned int), buffer_Zs);
	/* convert 32-bit code units to YYCTYPE; reuse the same buffer */
	for (unsigned int i = 0; i < buffer_len; ++i) s[i] = buffer_Zs[i];
	if (!scan (s, s + buffer_len))
		printf("test 'Zs' failed\n");
	delete [] buffer_Zs;
	return 0;
}
