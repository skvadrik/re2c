// re2c $INPUT -o $OUTPUT -u --encoding-policy ignore
#include <stdint.h>
#include <stdio.h>
#define YYCTYPE uint32_t

bool scan(const YYCTYPE* start, const YYCTYPE* const limit) {
	__attribute__((unused)) const YYCTYPE* YYMARKER;
#define YYCURSOR start
Sk:
/*!re2c
	re2c:yyfill:enable = 0;
	Sk = [\x5e\x60\xa8\xaf\xb4\xb8\u02c2-\u02c5\u02d2-\u02df\u02e5-\u02eb\u02ed\u02ef-\u02ff\u0375\u0384-\u0385\u0888\u1fbd\u1fbf-\u1fc1\u1fcd-\u1fcf\u1fdd-\u1fdf\u1fed-\u1fef\u1ffd-\u1ffe\u309b-\u309c\ua700-\ua716\ua720-\ua721\ua789-\ua78a\uab5b\uab6a-\uab6b\ufbb2-\ufbc2\uff3e\uff40\uffe3\U0001f3fb-\U0001f3ff];
		Sk { goto Sk; }
		* { return YYCURSOR - 1 == limit; }
	*/
}

static const uint32_t chars_Sk[] = {0x5e,0x5e,0x60,0x60,0xa8,0xa8,0xaf,0xaf,0xb4,0xb4,0xb8,0xb8,0x2c2,0x2c5,0x2d2,0x2df,0x2e5,0x2eb,0x2ed,0x2ed,0x2ef,0x2ff,0x375,0x375,0x384,0x385,0x888,0x888,0x1fbd,0x1fbd,0x1fbf,0x1fc1,0x1fcd,0x1fcf,0x1fdd,0x1fdf,0x1fed,0x1fef,0x1ffd,0x1ffe,0x309b,0x309c,0xa700,0xa716,0xa720,0xa721,0xa789,0xa78a,0xab5b,0xab5b,0xab6a,0xab6b,0xfbb2,0xfbc2,0xff3e,0xff3e,0xff40,0xff40,0xffe3,0xffe3,0x1f3fb,0x1f3ff,};

static uint32_t encode_utf32(const uint32_t* ranges, uint32_t ranges_count, uint32_t* s) {
	uint32_t* const s0 = s;
	for (uint32_t i = 0; i < ranges_count; i += 2)
		for (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j) *s++ = j;
	for (uint32_t i = 0; i < 1; ++i) s[i] = 0;
	return s - s0;
}

int main() {
	YYCTYPE* buffer_Sk = new YYCTYPE[126];
	uint32_t buffer_Sk_len = encode_utf32(chars_Sk, sizeof(chars_Sk) / sizeof(uint32_t), buffer_Sk);
	if (!scan(buffer_Sk, buffer_Sk + buffer_Sk_len)) printf("test 'Sk' failed\n");
	delete[] buffer_Sk;
	return 0;
}
