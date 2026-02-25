// re2c $INPUT -o $OUTPUT -8 --encoding-policy substitute
#include <stdint.h>
#include <stdio.h>
#include "utf8.h"
#define YYCTYPE uint8_t

bool scan(const YYCTYPE* start, const YYCTYPE* const limit) {
	__attribute__((unused)) const YYCTYPE* YYMARKER;
#define YYCURSOR start
Lt:
/*!re2c
	re2c:yyfill:enable = 0;
	Lt = [\u01c5\u01c8\u01cb\u01f2\u1f88-\u1f8f\u1f98-\u1f9f\u1fa8-\u1faf\u1fbc\u1fcc\u1ffc];
		Lt { goto Lt; }
		* { return YYCURSOR - 1 == limit; }
	*/
}

static const uint32_t chars_Lt[] = {0x1c5,0x1c5,0x1c8,0x1c8,0x1cb,0x1cb,0x1f2,0x1f2,0x1f88,0x1f8f,0x1f98,0x1f9f,0x1fa8,0x1faf,0x1fbc,0x1fbc,0x1fcc,0x1fcc,0x1ffc,0x1ffc,};

static uint32_t encode_utf8(const uint32_t* ranges, uint32_t ranges_count, uint8_t* s) {
	uint8_t* const s0 = s;
	for (uint32_t i = 0; i < ranges_count; i += 2)
		for (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j) s += re2c::utf8::rune_to_bytes(s, j);
	for (uint32_t i = 0; i < 6; ++i) s[i] = 0;
	return s - s0;
}

int main() {
	YYCTYPE* buffer_Lt = new YYCTYPE[192];
	uint32_t buffer_Lt_len = encode_utf8(chars_Lt, sizeof(chars_Lt) / sizeof(uint32_t), buffer_Lt);
	if (!scan(buffer_Lt, buffer_Lt + buffer_Lt_len)) printf("test 'Lt' failed\n");
	delete[] buffer_Lt;
	return 0;
}
