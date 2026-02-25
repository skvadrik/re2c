// re2c $INPUT -o $OUTPUT -x --encoding-policy fail
#include <stdint.h>
#include <stdio.h>
#include "utf16.h"
#define YYCTYPE uint16_t

bool scan(const YYCTYPE* start, const YYCTYPE* const limit) {
	__attribute__((unused)) const YYCTYPE* YYMARKER;
#define YYCURSOR start
Pd:
/*!re2c
	re2c:yyfill:enable = 0;
	Pd = [\x2d\u058a\u05be\u1400\u1806\u2010-\u2015\u2e17\u2e1a\u2e3a-\u2e3b\u2e40\u2e5d\u301c\u3030\u30a0\ufe31-\ufe32\ufe58\ufe63\uff0d\U00010ead];
		Pd { goto Pd; }
		* { return YYCURSOR - 1 == limit; }
	*/
}

static const uint32_t chars_Pd[] = {0x2d,0x2d,0x58a,0x58a,0x5be,0x5be,0x1400,0x1400,0x1806,0x1806,0x2010,0x2015,0x2e17,0x2e17,0x2e1a,0x2e1a,0x2e3a,0x2e3b,0x2e40,0x2e40,0x2e5d,0x2e5d,0x301c,0x301c,0x3030,0x3030,0x30a0,0x30a0,0xfe31,0xfe32,0xfe58,0xfe58,0xfe63,0xfe63,0xff0d,0xff0d,0x10ead,0x10ead,};

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
	YYCTYPE* buffer_Pd = new YYCTYPE[54];
	uint32_t buffer_Pd_len = encode_utf16(chars_Pd, sizeof(chars_Pd) / sizeof(uint32_t), buffer_Pd);
	if (!scan(buffer_Pd, buffer_Pd + buffer_Pd_len)) printf("test 'Pd' failed\n");
	delete[] buffer_Pd;
	return 0;
}
