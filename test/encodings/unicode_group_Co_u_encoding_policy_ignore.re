// re2c $INPUT -o $OUTPUT -u --encoding-policy ignore
#include <stdint.h>
#include <stdio.h>
#define YYCTYPE uint32_t

bool scan(const YYCTYPE* start, const YYCTYPE* const limit) {
	__attribute__((unused)) const YYCTYPE* YYMARKER;
#define YYCURSOR start
Co:
/*!re2c
	re2c:yyfill:enable = 0;
	Co = [\ue000-\uf8ff\U000f0000-\U000ffffd\U00100000-\U0010fffd];
		Co { goto Co; }
		* { return YYCURSOR - 1 == limit; }
	*/
}

static const uint32_t chars_Co[] = {0xe000,0xf8ff,0xf0000,0xffffd,0x100000,0x10fffd,};

static uint32_t encode_utf32(const uint32_t* ranges, uint32_t ranges_count, uint32_t* s) {
	uint32_t* const s0 = s;
	for (uint32_t i = 0; i < ranges_count; i += 2)
		for (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j) *s++ = j;
	for (uint32_t i = 0; i < 1; ++i) s[i] = 0;
	return s - s0;
}

int main() {
	YYCTYPE* buffer_Co = new YYCTYPE[137469];
	uint32_t buffer_Co_len = encode_utf32(chars_Co, sizeof(chars_Co) / sizeof(uint32_t), buffer_Co);
	if (!scan(buffer_Co, buffer_Co + buffer_Co_len)) printf("test 'Co' failed\n");
	delete[] buffer_Co;
	return 0;
}
