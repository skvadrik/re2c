#include <stdio.h>
#include "utf16.h"
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Pe:
	/*!re2c
		re2c:yyfill:enable = 0;
		Pe = [\x29-\x29\x5d-\x5d\x7d-\x7d\u0f3b-\u0f3b\u0f3d-\u0f3d\u169c-\u169c\u2046-\u2046\u207e-\u207e\u208e-\u208e\u232a-\u232a\u2769-\u2769\u276b-\u276b\u276d-\u276d\u276f-\u276f\u2771-\u2771\u2773-\u2773\u2775-\u2775\u27c6-\u27c6\u27e7-\u27e7\u27e9-\u27e9\u27eb-\u27eb\u27ed-\u27ed\u27ef-\u27ef\u2984-\u2984\u2986-\u2986\u2988-\u2988\u298a-\u298a\u298c-\u298c\u298e-\u298e\u2990-\u2990\u2992-\u2992\u2994-\u2994\u2996-\u2996\u2998-\u2998\u29d9-\u29d9\u29db-\u29db\u29fd-\u29fd\u2e23-\u2e23\u2e25-\u2e25\u2e27-\u2e27\u2e29-\u2e29\u3009-\u3009\u300b-\u300b\u300d-\u300d\u300f-\u300f\u3011-\u3011\u3015-\u3015\u3017-\u3017\u3019-\u3019\u301b-\u301b\u301e-\u301f\ufd3f-\ufd3f\ufe18-\ufe18\ufe36-\ufe36\ufe38-\ufe38\ufe3a-\ufe3a\ufe3c-\ufe3c\ufe3e-\ufe3e\ufe40-\ufe40\ufe42-\ufe42\ufe44-\ufe44\ufe48-\ufe48\ufe5a-\ufe5a\ufe5c-\ufe5c\ufe5e-\ufe5e\uff09-\uff09\uff3d-\uff3d\uff5d-\uff5d\uff60-\uff60\uff63-\uff63];
		Pe { goto Pe; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Pe [] = {0x29,0x29,  0x5d,0x5d,  0x7d,0x7d,  0xf3b,0xf3b,  0xf3d,0xf3d,  0x169c,0x169c,  0x2046,0x2046,  0x207e,0x207e,  0x208e,0x208e,  0x232a,0x232a,  0x2769,0x2769,  0x276b,0x276b,  0x276d,0x276d,  0x276f,0x276f,  0x2771,0x2771,  0x2773,0x2773,  0x2775,0x2775,  0x27c6,0x27c6,  0x27e7,0x27e7,  0x27e9,0x27e9,  0x27eb,0x27eb,  0x27ed,0x27ed,  0x27ef,0x27ef,  0x2984,0x2984,  0x2986,0x2986,  0x2988,0x2988,  0x298a,0x298a,  0x298c,0x298c,  0x298e,0x298e,  0x2990,0x2990,  0x2992,0x2992,  0x2994,0x2994,  0x2996,0x2996,  0x2998,0x2998,  0x29d9,0x29d9,  0x29db,0x29db,  0x29fd,0x29fd,  0x2e23,0x2e23,  0x2e25,0x2e25,  0x2e27,0x2e27,  0x2e29,0x2e29,  0x3009,0x3009,  0x300b,0x300b,  0x300d,0x300d,  0x300f,0x300f,  0x3011,0x3011,  0x3015,0x3015,  0x3017,0x3017,  0x3019,0x3019,  0x301b,0x301b,  0x301e,0x301f,  0xfd3f,0xfd3f,  0xfe18,0xfe18,  0xfe36,0xfe36,  0xfe38,0xfe38,  0xfe3a,0xfe3a,  0xfe3c,0xfe3c,  0xfe3e,0xfe3e,  0xfe40,0xfe40,  0xfe42,0xfe42,  0xfe44,0xfe44,  0xfe48,0xfe48,  0xfe5a,0xfe5a,  0xfe5c,0xfe5c,  0xfe5e,0xfe5e,  0xff09,0xff09,  0xff3d,0xff3d,  0xff5d,0xff5d,  0xff60,0xff60,  0xff63,0xff63,  0x0,0x0};
static unsigned int encode_utf16 (const unsigned int * ranges, unsigned int ranges_count, unsigned short * s)
{
	unsigned short * const s_start = s;
	for (unsigned int i = 0; i < ranges_count; i += 2)
		for (unsigned int j = ranges[i]; j <= ranges[i + 1]; ++j)
		{
			if (j <= re2c::utf16::MAX_1WORD_RUNE)
				*s++ = j;
			else
			{
				*s++ = re2c::utf16::lead_surr(j);
				*s++ = re2c::utf16::trail_surr(j);
			}
		}
	return s - s_start;
}

int main ()
{
	YYCTYPE * buffer_Pe = new YYCTYPE [144];
	unsigned int buffer_len = encode_utf16 (chars_Pe, sizeof (chars_Pe) / sizeof (unsigned int), buffer_Pe);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Pe), reinterpret_cast<const YYCTYPE *> (buffer_Pe + buffer_len)))
		printf("test 'Pe' failed\n");
	delete [] buffer_Pe;
	return 0;
}
