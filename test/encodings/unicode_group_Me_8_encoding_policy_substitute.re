// re2c $INPUT -o $OUTPUT -8 --encoding-policy substitute
#include <stdint.h>
#include <stdio.h>
#include "utf8.h"
#define YYCTYPE uint8_t

bool scan(const YYCTYPE* start, const YYCTYPE* const limit) {
	__attribute__((unused)) const YYCTYPE* YYMARKER;
#define YYCURSOR start
Me:
/*!re2c
	re2c:yyfill:enable = 0;
	Me = [\u0488-\u0489\u1abe\u20dd-\u20e0\u20e2-\u20e4\ua670-\ua672];
		Me { goto Me; }
		* { return YYCURSOR - 1 == limit; }
	*/
}

static const uint32_t chars_Me[] = {0x488,0x489,0x1abe,0x1abe,0x20dd,0x20e0,0x20e2,0x20e4,0xa670,0xa672,};

static uint32_t encode_utf8(const uint32_t* ranges, uint32_t ranges_count, uint8_t* s) {
	uint8_t* const s0 = s;
	for (uint32_t i = 0; i < ranges_count; i += 2)
		for (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j) s += re2c::utf8::rune_to_bytes(s, j);
	for (uint32_t i = 0; i < 6; ++i) s[i] = 0;
	return s - s0;
}

int main() {
	YYCTYPE* buffer_Me = new YYCTYPE[84];
	uint32_t buffer_Me_len = encode_utf8(chars_Me, sizeof(chars_Me) / sizeof(uint32_t), buffer_Me);
	if (!scan(buffer_Me, buffer_Me + buffer_Me_len)) printf("test 'Me' failed\n");
	delete[] buffer_Me;
	return 0;
}
