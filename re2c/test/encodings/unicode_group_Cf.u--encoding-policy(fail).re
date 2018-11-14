#include <stdio.h>

#define YYCTYPE unsigned int
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Cf:
	/*!re2c
		re2c:yyfill:enable = 0;
		Cf = [\xad-\xad\u0600-\u0603\u06dd-\u06dd\u070f-\u070f\u17b4-\u17b5\u200b-\u200f\u202a-\u202e\u2060-\u2064\u206a-\u206f\ufeff-\ufeff\ufff9-\ufffb\U000110bd-\U000110bd\U0001d173-\U0001d17a\U000e0001-\U000e0001\U000e0020-\U000e007f];
		Cf { goto Cf; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Cf [] = {0xad,0xad,  0x600,0x603,  0x6dd,0x6dd,  0x70f,0x70f,  0x17b4,0x17b5,  0x200b,0x200f,  0x202a,0x202e,  0x2060,0x2064,  0x206a,0x206f,  0xfeff,0xfeff,  0xfff9,0xfffb,  0x110bd,0x110bd,  0x1d173,0x1d17a,  0xe0001,0xe0001,  0xe0020,0xe007f,  0x0,0x0};
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
	YYCTYPE * buffer_Cf = new YYCTYPE [141];
	unsigned int buffer_len = encode_utf32 (chars_Cf, sizeof (chars_Cf) / sizeof (unsigned int), buffer_Cf);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Cf), reinterpret_cast<const YYCTYPE *> (buffer_Cf + buffer_len)))
		printf("test 'Cf' failed\n");
	delete [] buffer_Cf;
	return 0;
}
