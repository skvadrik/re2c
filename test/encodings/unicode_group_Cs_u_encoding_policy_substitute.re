// re2c $INPUT -o $OUTPUT -u --encoding-policy substitute
#include <stdint.h>
#include <stdio.h>
#define YYCTYPE uint32_t

bool scan(const YYCTYPE* start, const YYCTYPE* const limit) {
	__attribute__((unused)) const YYCTYPE* YYMARKER;
#define YYCURSOR start
Cs:
/*!re2c
	re2c:yyfill:enable = 0;
	Cs = [\ud800-\udfff];
		Cs { goto Cs; }
		* { return YYCURSOR - 1 == limit; }
	*/
}

static const uint32_t chars_Cs[] = {0xd800,0xdfff,};

static uint32_t encode_utf32(const uint32_t* ranges, uint32_t ranges_count, uint32_t* s) {
	uint32_t* const s0 = s;
	for (uint32_t i = 0; i < ranges_count; i += 2)
		for (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j) *s++ = j;
	for (uint32_t i = 0; i < 1; ++i) s[i] = 0;
	return s - s0;
}

int main() {
	YYCTYPE* buffer_Cs = new YYCTYPE[2049];
	uint32_t buffer_Cs_len = encode_utf32(chars_Cs, sizeof(chars_Cs) / sizeof(uint32_t), buffer_Cs);
	if (!scan(buffer_Cs, buffer_Cs + buffer_Cs_len)) printf("test 'Cs' failed\n");
	delete[] buffer_Cs;
	return 0;
}
