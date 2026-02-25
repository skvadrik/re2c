// re2c $INPUT -o $OUTPUT -8 --encoding-policy fail
#include <stdint.h>
#include <stdio.h>
#include "utf8.h"
#define YYCTYPE uint8_t

bool scan(const YYCTYPE* start, const YYCTYPE* const limit) {
	__attribute__((unused)) const YYCTYPE* YYMARKER;
#define YYCURSOR start
Zp:
/*!re2c
	re2c:yyfill:enable = 0;
	Zp = [\u2029];
		Zp { goto Zp; }
		* { return YYCURSOR - 1 == limit; }
	*/
}

static const uint32_t chars_Zp[] = {0x2029,0x2029,};

static uint32_t encode_utf8(const uint32_t* ranges, uint32_t ranges_count, uint8_t* s) {
	uint8_t* const s0 = s;
	for (uint32_t i = 0; i < ranges_count; i += 2)
		for (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j) s += re2c::utf8::rune_to_bytes(s, j);
	for (uint32_t i = 0; i < 6; ++i) s[i] = 0;
	return s - s0;
}

int main() {
	YYCTYPE* buffer_Zp = new YYCTYPE[12];
	uint32_t buffer_Zp_len = encode_utf8(chars_Zp, sizeof(chars_Zp) / sizeof(uint32_t), buffer_Zp);
	if (!scan(buffer_Zp, buffer_Zp + buffer_Zp_len)) printf("test 'Zp' failed\n");
	delete[] buffer_Zp;
	return 0;
}
