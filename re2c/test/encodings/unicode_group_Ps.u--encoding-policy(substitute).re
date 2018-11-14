#include <stdio.h>

#define YYCTYPE unsigned int
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Ps:
	/*!re2c
		re2c:yyfill:enable = 0;
		Ps = [\x28-\x28\x5b-\x5b\x7b-\x7b\u0f3a-\u0f3a\u0f3c-\u0f3c\u169b-\u169b\u201a-\u201a\u201e-\u201e\u2045-\u2045\u207d-\u207d\u208d-\u208d\u2329-\u2329\u2768-\u2768\u276a-\u276a\u276c-\u276c\u276e-\u276e\u2770-\u2770\u2772-\u2772\u2774-\u2774\u27c5-\u27c5\u27e6-\u27e6\u27e8-\u27e8\u27ea-\u27ea\u27ec-\u27ec\u27ee-\u27ee\u2983-\u2983\u2985-\u2985\u2987-\u2987\u2989-\u2989\u298b-\u298b\u298d-\u298d\u298f-\u298f\u2991-\u2991\u2993-\u2993\u2995-\u2995\u2997-\u2997\u29d8-\u29d8\u29da-\u29da\u29fc-\u29fc\u2e22-\u2e22\u2e24-\u2e24\u2e26-\u2e26\u2e28-\u2e28\u3008-\u3008\u300a-\u300a\u300c-\u300c\u300e-\u300e\u3010-\u3010\u3014-\u3014\u3016-\u3016\u3018-\u3018\u301a-\u301a\u301d-\u301d\ufd3e-\ufd3e\ufe17-\ufe17\ufe35-\ufe35\ufe37-\ufe37\ufe39-\ufe39\ufe3b-\ufe3b\ufe3d-\ufe3d\ufe3f-\ufe3f\ufe41-\ufe41\ufe43-\ufe43\ufe47-\ufe47\ufe59-\ufe59\ufe5b-\ufe5b\ufe5d-\ufe5d\uff08-\uff08\uff3b-\uff3b\uff5b-\uff5b\uff5f-\uff5f\uff62-\uff62];
		Ps { goto Ps; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Ps [] = {0x28,0x28,  0x5b,0x5b,  0x7b,0x7b,  0xf3a,0xf3a,  0xf3c,0xf3c,  0x169b,0x169b,  0x201a,0x201a,  0x201e,0x201e,  0x2045,0x2045,  0x207d,0x207d,  0x208d,0x208d,  0x2329,0x2329,  0x2768,0x2768,  0x276a,0x276a,  0x276c,0x276c,  0x276e,0x276e,  0x2770,0x2770,  0x2772,0x2772,  0x2774,0x2774,  0x27c5,0x27c5,  0x27e6,0x27e6,  0x27e8,0x27e8,  0x27ea,0x27ea,  0x27ec,0x27ec,  0x27ee,0x27ee,  0x2983,0x2983,  0x2985,0x2985,  0x2987,0x2987,  0x2989,0x2989,  0x298b,0x298b,  0x298d,0x298d,  0x298f,0x298f,  0x2991,0x2991,  0x2993,0x2993,  0x2995,0x2995,  0x2997,0x2997,  0x29d8,0x29d8,  0x29da,0x29da,  0x29fc,0x29fc,  0x2e22,0x2e22,  0x2e24,0x2e24,  0x2e26,0x2e26,  0x2e28,0x2e28,  0x3008,0x3008,  0x300a,0x300a,  0x300c,0x300c,  0x300e,0x300e,  0x3010,0x3010,  0x3014,0x3014,  0x3016,0x3016,  0x3018,0x3018,  0x301a,0x301a,  0x301d,0x301d,  0xfd3e,0xfd3e,  0xfe17,0xfe17,  0xfe35,0xfe35,  0xfe37,0xfe37,  0xfe39,0xfe39,  0xfe3b,0xfe3b,  0xfe3d,0xfe3d,  0xfe3f,0xfe3f,  0xfe41,0xfe41,  0xfe43,0xfe43,  0xfe47,0xfe47,  0xfe59,0xfe59,  0xfe5b,0xfe5b,  0xfe5d,0xfe5d,  0xff08,0xff08,  0xff3b,0xff3b,  0xff5b,0xff5b,  0xff5f,0xff5f,  0xff62,0xff62,  0x0,0x0};
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
	YYCTYPE * buffer_Ps = new YYCTYPE [73];
	unsigned int buffer_len = encode_utf32 (chars_Ps, sizeof (chars_Ps) / sizeof (unsigned int), buffer_Ps);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Ps), reinterpret_cast<const YYCTYPE *> (buffer_Ps + buffer_len)))
		printf("test 'Ps' failed\n");
	delete [] buffer_Ps;
	return 0;
}
