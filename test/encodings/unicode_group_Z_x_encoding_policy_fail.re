// re2c $INPUT -o $OUTPUT -x --encoding-policy fail
#include <stdint.h>
#include <stdio.h>
#include "utf16.h"
#define YYCTYPE uint16_t

bool scan(const YYCTYPE* start, const YYCTYPE* const limit) {
	__attribute__((unused)) const YYCTYPE* YYMARKER;
#define YYCURSOR start
Z:
/*!re2c
	re2c:yyfill:enable = 0;
	Z = [\x20\xa0\u1680\u2000-\u200a\u2028-\u2029\u202f\u205f\u3000];
		Z { goto Z; }
		* { return YYCURSOR - 1 == limit; }
	*/
}

static const uint32_t chars_Z[] = {0x20,0x20,0xa0,0xa0,0x1680,0x1680,0x2000,0x200a,0x2028,0x2029,0x202f,0x202f,0x205f,0x205f,0x3000,0x3000,};

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
	YYCTYPE* buffer_Z = new YYCTYPE[40];
	uint32_t buffer_Z_len = encode_utf16(chars_Z, sizeof(chars_Z) / sizeof(uint32_t), buffer_Z);
	if (!scan(buffer_Z, buffer_Z + buffer_Z_len)) printf("test 'Z' failed\n");
	delete[] buffer_Z;
	return 0;
}
