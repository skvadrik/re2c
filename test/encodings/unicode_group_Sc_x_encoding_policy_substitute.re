// re2c $INPUT -o $OUTPUT -x --encoding-policy substitute
#include <stdint.h>
#include <stdio.h>
#include "utf16.h"
#define YYCTYPE uint16_t

bool scan(const YYCTYPE* start, const YYCTYPE* const limit) {
	__attribute__((unused)) const YYCTYPE* YYMARKER;
#define YYCURSOR start
Sc:
/*!re2c
	re2c:yyfill:enable = 0;
	Sc = [\x24\xa2-\xa5\u058f\u060b\u07fe-\u07ff\u09f2-\u09f3\u09fb\u0af1\u0bf9\u0e3f\u17db\u20a0-\u20c0\ua838\ufdfc\ufe69\uff04\uffe0-\uffe1\uffe5-\uffe6\U00011fdd-\U00011fe0\U0001e2ff\U0001ecb0];
		Sc { goto Sc; }
		* { return YYCURSOR - 1 == limit; }
	*/
}

static const uint32_t chars_Sc[] = {0x24,0x24,0xa2,0xa5,0x58f,0x58f,0x60b,0x60b,0x7fe,0x7ff,0x9f2,0x9f3,0x9fb,0x9fb,0xaf1,0xaf1,0xbf9,0xbf9,0xe3f,0xe3f,0x17db,0x17db,0x20a0,0x20c0,0xa838,0xa838,0xfdfc,0xfdfc,0xfe69,0xfe69,0xff04,0xff04,0xffe0,0xffe1,0xffe5,0xffe6,0x11fdd,0x11fe0,0x1e2ff,0x1e2ff,0x1ecb0,0x1ecb0,};

static uint32_t encode_utf16(const uint32_t* ranges, uint32_t ranges_count, uint16_t* s) {
	uint16_t* const s0 = s;
	for (uint32_t i = 0; i < ranges_count; i += 2)
		for (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j)
			if (j <= re2c::utf16::MAX_1WORD_RUNE) {
				*s++ = j;
			} else {
				*s++ = re2c::utf16::lead_surr(j);
				*s++ = re2c::utf16::trail_surr(j);
			}
	for (uint32_t i = 0; i < 2; ++i) s[i] = 0;
	return s - s0;
}

int main() {
	YYCTYPE* buffer_Sc = new YYCTYPE[128];
	uint32_t buffer_Sc_len = encode_utf16(chars_Sc, sizeof(chars_Sc) / sizeof(uint32_t), buffer_Sc);
	if (!scan(buffer_Sc, buffer_Sc + buffer_Sc_len)) printf("test 'Sc' failed\n");
	delete[] buffer_Sc;
	return 0;
}
