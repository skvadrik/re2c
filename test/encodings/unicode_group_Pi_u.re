// re2c $INPUT -o $OUTPUT -u
#include <stdint.h>
#include <stdio.h>
#define YYCTYPE uint32_t

bool scan(const YYCTYPE* start, const YYCTYPE* const limit) {
	__attribute__((unused)) const YYCTYPE* YYMARKER;
#define YYCURSOR start
Pi:
/*!re2c
	re2c:yyfill:enable = 0;
	Pi = [\xab\u2018\u201b-\u201c\u201f\u2039\u2e02\u2e04\u2e09\u2e0c\u2e1c\u2e20];
		Pi { goto Pi; }
		* { return YYCURSOR - 1 == limit; }
	*/
}

static const uint32_t chars_Pi[] = {0xab,0xab,0x2018,0x2018,0x201b,0x201c,0x201f,0x201f,0x2039,0x2039,0x2e02,0x2e02,0x2e04,0x2e04,0x2e09,0x2e09,0x2e0c,0x2e0c,0x2e1c,0x2e1c,0x2e20,0x2e20,};

static uint32_t encode_utf32(const uint32_t* ranges, uint32_t ranges_count, uint32_t* s) {
	uint32_t* const s0 = s;
	for (uint32_t i = 0; i < ranges_count; i += 2)
		for (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j) *s++ = j;
	for (uint32_t i = 0; i < 1; ++i) s[i] = 0;
	return s - s0;
}

int main() {
	YYCTYPE* buffer_Pi = new YYCTYPE[13];
	uint32_t buffer_Pi_len = encode_utf32(chars_Pi, sizeof(chars_Pi) / sizeof(uint32_t), buffer_Pi);
	if (!scan(buffer_Pi, buffer_Pi + buffer_Pi_len)) printf("test 'Pi' failed\n");
	delete[] buffer_Pi;
	return 0;
}
