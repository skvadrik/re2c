#include <stdio.h>

#define YYCTYPE unsigned int
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Sk:
	/*!re2c
		re2c:yyfill:enable = 0;
		Sk = [\x5e-\x5e\x60-\x60\xa8-\xa8\xaf-\xaf\xb4-\xb4\xb8-\xb8\u02c2-\u02c5\u02d2-\u02df\u02e5-\u02eb\u02ed-\u02ed\u02ef-\u02ff\u0375-\u0375\u0384-\u0385\u1fbd-\u1fbd\u1fbf-\u1fc1\u1fcd-\u1fcf\u1fdd-\u1fdf\u1fed-\u1fef\u1ffd-\u1ffe\u309b-\u309c\ua700-\ua716\ua720-\ua721\ua789-\ua78a\ufbb2-\ufbc1\uff3e-\uff3e\uff40-\uff40\uffe3-\uffe3];
		Sk { goto Sk; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Sk [] = {0x5e,0x5e,  0x60,0x60,  0xa8,0xa8,  0xaf,0xaf,  0xb4,0xb4,  0xb8,0xb8,  0x2c2,0x2c5,  0x2d2,0x2df,  0x2e5,0x2eb,  0x2ed,0x2ed,  0x2ef,0x2ff,  0x375,0x375,  0x384,0x385,  0x1fbd,0x1fbd,  0x1fbf,0x1fc1,  0x1fcd,0x1fcf,  0x1fdd,0x1fdf,  0x1fed,0x1fef,  0x1ffd,0x1ffe,  0x309b,0x309c,  0xa700,0xa716,  0xa720,0xa721,  0xa789,0xa78a,  0xfbb2,0xfbc1,  0xff3e,0xff3e,  0xff40,0xff40,  0xffe3,0xffe3,  0x0,0x0};
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
	YYCTYPE * buffer_Sk = new YYCTYPE [116];
	unsigned int buffer_len = encode_utf32 (chars_Sk, sizeof (chars_Sk) / sizeof (unsigned int), buffer_Sk);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Sk), reinterpret_cast<const YYCTYPE *> (buffer_Sk + buffer_len)))
		printf("test 'Sk' failed\n");
	delete [] buffer_Sk;
	return 0;
}
