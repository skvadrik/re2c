#include <stdio.h>

#define YYCTYPE unsigned int
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Sm:
	/*!re2c
		re2c:yyfill:enable = 0;
		Sm = [\x2b-\x2b\x3c-\x3e\x7c-\x7c\x7e-\x7e\xac-\xac\xb1-\xb1\xd7-\xd7\xf7-\xf7\u03f6-\u03f6\u0606-\u0608\u2044-\u2044\u2052-\u2052\u207a-\u207c\u208a-\u208c\u2118-\u2118\u2140-\u2144\u214b-\u214b\u2190-\u2194\u219a-\u219b\u21a0-\u21a0\u21a3-\u21a3\u21a6-\u21a6\u21ae-\u21ae\u21ce-\u21cf\u21d2-\u21d2\u21d4-\u21d4\u21f4-\u22ff\u2308-\u230b\u2320-\u2321\u237c-\u237c\u239b-\u23b3\u23dc-\u23e1\u25b7-\u25b7\u25c1-\u25c1\u25f8-\u25ff\u266f-\u266f\u27c0-\u27c4\u27c7-\u27ca\u27cc-\u27cc\u27ce-\u27e5\u27f0-\u27ff\u2900-\u2982\u2999-\u29d7\u29dc-\u29fb\u29fe-\u2aff\u2b30-\u2b44\u2b47-\u2b4c\ufb29-\ufb29\ufe62-\ufe62\ufe64-\ufe66\uff0b-\uff0b\uff1c-\uff1e\uff5c-\uff5c\uff5e-\uff5e\uffe2-\uffe2\uffe9-\uffec\U0001d6c1-\U0001d6c1\U0001d6db-\U0001d6db\U0001d6fb-\U0001d6fb\U0001d715-\U0001d715\U0001d735-\U0001d735\U0001d74f-\U0001d74f\U0001d76f-\U0001d76f\U0001d789-\U0001d789\U0001d7a9-\U0001d7a9\U0001d7c3-\U0001d7c3];
		Sm { goto Sm; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Sm [] = {0x2b,0x2b,  0x3c,0x3e,  0x7c,0x7c,  0x7e,0x7e,  0xac,0xac,  0xb1,0xb1,  0xd7,0xd7,  0xf7,0xf7,  0x3f6,0x3f6,  0x606,0x608,  0x2044,0x2044,  0x2052,0x2052,  0x207a,0x207c,  0x208a,0x208c,  0x2118,0x2118,  0x2140,0x2144,  0x214b,0x214b,  0x2190,0x2194,  0x219a,0x219b,  0x21a0,0x21a0,  0x21a3,0x21a3,  0x21a6,0x21a6,  0x21ae,0x21ae,  0x21ce,0x21cf,  0x21d2,0x21d2,  0x21d4,0x21d4,  0x21f4,0x22ff,  0x2308,0x230b,  0x2320,0x2321,  0x237c,0x237c,  0x239b,0x23b3,  0x23dc,0x23e1,  0x25b7,0x25b7,  0x25c1,0x25c1,  0x25f8,0x25ff,  0x266f,0x266f,  0x27c0,0x27c4,  0x27c7,0x27ca,  0x27cc,0x27cc,  0x27ce,0x27e5,  0x27f0,0x27ff,  0x2900,0x2982,  0x2999,0x29d7,  0x29dc,0x29fb,  0x29fe,0x2aff,  0x2b30,0x2b44,  0x2b47,0x2b4c,  0xfb29,0xfb29,  0xfe62,0xfe62,  0xfe64,0xfe66,  0xff0b,0xff0b,  0xff1c,0xff1e,  0xff5c,0xff5c,  0xff5e,0xff5e,  0xffe2,0xffe2,  0xffe9,0xffec,  0x1d6c1,0x1d6c1,  0x1d6db,0x1d6db,  0x1d6fb,0x1d6fb,  0x1d715,0x1d715,  0x1d735,0x1d735,  0x1d74f,0x1d74f,  0x1d76f,0x1d76f,  0x1d789,0x1d789,  0x1d7a9,0x1d7a9,  0x1d7c3,0x1d7c3,  0x0,0x0};
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
	YYCTYPE * buffer_Sm = new YYCTYPE [949];
	unsigned int buffer_len = encode_utf32 (chars_Sm, sizeof (chars_Sm) / sizeof (unsigned int), buffer_Sm);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Sm), reinterpret_cast<const YYCTYPE *> (buffer_Sm + buffer_len)))
		printf("test 'Sm' failed\n");
	delete [] buffer_Sm;
	return 0;
}
