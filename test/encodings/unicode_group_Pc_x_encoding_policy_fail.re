// re2c $INPUT -o $OUTPUT -x --encoding-policy fail
#include <stdint.h>
#include <stdio.h>
#include "utf16.h"
#define YYCTYPE uint16_t

bool scan(const YYCTYPE* start, const YYCTYPE* const limit) {
	__attribute__((unused)) const YYCTYPE* YYMARKER;
#define YYCURSOR start
Pc:
/*!re2c
	re2c:yyfill:enable = 0;
	Pc = [\x5f\u203f-\u2040\u2054\ufe33-\ufe34\ufe4d-\ufe4f\uff3f];
		Pc { goto Pc; }
		* { return YYCURSOR - 1 == limit; }
	*/
}

static const uint32_t chars_Pc[] = {0x5f,0x5f,0x203f,0x2040,0x2054,0x2054,0xfe33,0xfe34,0xfe4d,0xfe4f,0xff3f,0xff3f,};

static uint32_t encode_utf16(const uint32_t* ranges, uint32_t ranges_count, uint16_t* s) {
	uint16_t* const s0 = s;
	for (uint32_t i = 0; i < ranges_count; i += 2)
		for (uint32_t j = ranges[i]; j <= ranges[i + 1]; ++j)
			if (j <= re2c::utf16::MAX_1WORD_RUNE) {
				*s++ = j;
			} else {
				*s++ = re2c::utf16::lead_surr(j);
				*s++ = re2c::utf16::trail_surr(j);
			}
	for (uint32_t i = 0; i < 2; ++i) s[i] = 0;
	return s - s0;
}

int main() {
	YYCTYPE* buffer_Pc = new YYCTYPE[22];
	uint32_t buffer_Pc_len = encode_utf16(chars_Pc, sizeof(chars_Pc) / sizeof(uint32_t), buffer_Pc);
	if (!scan(buffer_Pc, buffer_Pc + buffer_Pc_len)) printf("test 'Pc' failed\n");
	delete[] buffer_Pc;
	return 0;
}
