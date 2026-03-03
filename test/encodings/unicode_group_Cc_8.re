// re2c $INPUT -o $OUTPUT -8
#include <stdint.h>
#include <stdio.h>
#include "utf8.h"
#define YYCTYPE uint8_t

bool scan(const YYCTYPE* start, const YYCTYPE* const limit) {
	__attribute__((unused)) const YYCTYPE* YYMARKER;
#define YYCURSOR start
Cc:
/*!re2c
	re2c:yyfill:enable = 0;
	Cc = [\x00-\x1f\x7f-\x9f];
		Cc { goto Cc; }
		* { return YYCURSOR - 1 == limit; }
	*/
}

static const uint32_t chars_Cc[] = {0x0,0x1f,0x7f,0x9f,};

static uint32_t encode_utf8(const uint32_t* ranges, uint32_t ranges_count, uint8_t* s) {
	uint8_t* const s0 = s;
	for (uint32_t i = 0; i < ranges_count; i += 2)
		for (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j) s += re2c::utf8::rune_to_bytes(s, j);
	for (uint32_t i = 0; i < 6; ++i) s[i] = 32;
	return s - s0;
}

int main() {
	YYCTYPE* buffer_Cc = new YYCTYPE[396];
	uint32_t buffer_Cc_len = encode_utf8(chars_Cc, sizeof(chars_Cc) / sizeof(uint32_t), buffer_Cc);
	if (!scan(buffer_Cc, buffer_Cc + buffer_Cc_len)) printf("test 'Cc' failed\n");
	delete[] buffer_Cc;
	return 0;
}
