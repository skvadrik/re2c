// re2c $INPUT -o $OUTPUT -u --encoding-policy ignore
#include <stdint.h>
#include <stdio.h>
#define YYCTYPE uint32_t

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

static uint32_t encode_utf32(const uint32_t* ranges, uint32_t ranges_count, uint32_t* s) {
	uint32_t* const s0 = s;
	for (uint32_t i = 0; i < ranges_count; i += 2)
		for (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j) *s++ = j;
	for (uint32_t i = 0; i < 1; ++i) s[i] = 0;
	return s - s0;
}

int main() {
	YYCTYPE* buffer_Zp = new YYCTYPE[2];
	uint32_t buffer_Zp_len = encode_utf32(chars_Zp, sizeof(chars_Zp) / sizeof(uint32_t), buffer_Zp);
	if (!scan(buffer_Zp, buffer_Zp + buffer_Zp_len)) printf("test 'Zp' failed\n");
	delete[] buffer_Zp;
	return 0;
}
