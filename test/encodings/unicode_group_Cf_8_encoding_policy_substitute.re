// re2c $INPUT -o $OUTPUT -8 --encoding-policy substitute
#include <stdint.h>
#include <stdio.h>
#include "utf8.h"
#define YYCTYPE uint8_t

bool scan(const YYCTYPE* start, const YYCTYPE* const limit) {
	__attribute__((unused)) const YYCTYPE* YYMARKER;
#define YYCURSOR start
Cf:
/*!re2c
	re2c:yyfill:enable = 0;
	Cf = [\xad\u0600-\u0605\u061c\u06dd\u070f\u0890-\u0891\u08e2\u180e\u200b-\u200f\u202a-\u202e\u2060-\u2064\u2066-\u206f\ufeff\ufff9-\ufffb\U000110bd\U000110cd\U00013430-\U0001343f\U0001bca0-\U0001bca3\U0001d173-\U0001d17a\U000e0001\U000e0020-\U000e007f];
		Cf { goto Cf; }
		* { return YYCURSOR - 1 == limit; }
	*/
}

static const uint32_t chars_Cf[] = {0xad,0xad,0x600,0x605,0x61c,0x61c,0x6dd,0x6dd,0x70f,0x70f,0x890,0x891,0x8e2,0x8e2,0x180e,0x180e,0x200b,0x200f,0x202a,0x202e,0x2060,0x2064,0x2066,0x206f,0xfeff,0xfeff,0xfff9,0xfffb,0x110bd,0x110bd,0x110cd,0x110cd,0x13430,0x1343f,0x1bca0,0x1bca3,0x1d173,0x1d17a,0xe0001,0xe0001,0xe0020,0xe007f,};

static uint32_t encode_utf8(const uint32_t* ranges, uint32_t ranges_count, uint8_t* s) {
	uint8_t* const s0 = s;
	for (uint32_t i = 0; i < ranges_count; i += 2)
		for (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j) s += re2c::utf8::rune_to_bytes(s, j);
	for (uint32_t i = 0; i < 6; ++i) s[i] = 0;
	return s - s0;
}

int main() {
	YYCTYPE* buffer_Cf = new YYCTYPE[1026];
	uint32_t buffer_Cf_len = encode_utf8(chars_Cf, sizeof(chars_Cf) / sizeof(uint32_t), buffer_Cf);
	if (!scan(buffer_Cf, buffer_Cf + buffer_Cf_len)) printf("test 'Cf' failed\n");
	delete[] buffer_Cf;
	return 0;
}
