#include <stdio.h>

#define YYCTYPE unsigned int
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Lm:
	/*!re2c
		re2c:yyfill:enable = 0;
		Lm = [\u02b0-\u02c1\u02c6-\u02d1\u02e0-\u02e4\u02ec-\u02ec\u02ee-\u02ee\u0374-\u0374\u037a-\u037a\u0559-\u0559\u0640-\u0640\u06e5-\u06e6\u07f4-\u07f5\u07fa-\u07fa\u081a-\u081a\u0824-\u0824\u0828-\u0828\u0971-\u0971\u0e46-\u0e46\u0ec6-\u0ec6\u10fc-\u10fc\u17d7-\u17d7\u1843-\u1843\u1aa7-\u1aa7\u1c78-\u1c7d\u1d2c-\u1d61\u1d78-\u1d78\u1d9b-\u1dbf\u2071-\u2071\u207f-\u207f\u2090-\u209c\u2c7d-\u2c7d\u2d6f-\u2d6f\u2e2f-\u2e2f\u3005-\u3005\u3031-\u3035\u303b-\u303b\u309d-\u309e\u30fc-\u30fe\ua015-\ua015\ua4f8-\ua4fd\ua60c-\ua60c\ua67f-\ua67f\ua717-\ua71f\ua770-\ua770\ua788-\ua788\ua9cf-\ua9cf\uaa70-\uaa70\uaadd-\uaadd\uff70-\uff70\uff9e-\uff9f];
		Lm { goto Lm; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Lm [] = {0x2b0,0x2c1,  0x2c6,0x2d1,  0x2e0,0x2e4,  0x2ec,0x2ec,  0x2ee,0x2ee,  0x374,0x374,  0x37a,0x37a,  0x559,0x559,  0x640,0x640,  0x6e5,0x6e6,  0x7f4,0x7f5,  0x7fa,0x7fa,  0x81a,0x81a,  0x824,0x824,  0x828,0x828,  0x971,0x971,  0xe46,0xe46,  0xec6,0xec6,  0x10fc,0x10fc,  0x17d7,0x17d7,  0x1843,0x1843,  0x1aa7,0x1aa7,  0x1c78,0x1c7d,  0x1d2c,0x1d61,  0x1d78,0x1d78,  0x1d9b,0x1dbf,  0x2071,0x2071,  0x207f,0x207f,  0x2090,0x209c,  0x2c7d,0x2c7d,  0x2d6f,0x2d6f,  0x2e2f,0x2e2f,  0x3005,0x3005,  0x3031,0x3035,  0x303b,0x303b,  0x309d,0x309e,  0x30fc,0x30fe,  0xa015,0xa015,  0xa4f8,0xa4fd,  0xa60c,0xa60c,  0xa67f,0xa67f,  0xa717,0xa71f,  0xa770,0xa770,  0xa788,0xa788,  0xa9cf,0xa9cf,  0xaa70,0xaa70,  0xaadd,0xaadd,  0xff70,0xff70,  0xff9e,0xff9f,  0x0,0x0};
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
	YYCTYPE * buffer_Lm = new YYCTYPE [211];
	unsigned int buffer_len = encode_utf32 (chars_Lm, sizeof (chars_Lm) / sizeof (unsigned int), buffer_Lm);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Lm), reinterpret_cast<const YYCTYPE *> (buffer_Lm + buffer_len)))
		printf("test 'Lm' failed\n");
	delete [] buffer_Lm;
	return 0;
}
