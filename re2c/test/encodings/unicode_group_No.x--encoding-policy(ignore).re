#include <stdio.h>
#include "utf16.h"
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
No:
	/*!re2c
		re2c:yyfill:enable = 0;
		No = [\xb2-\xb3\xb9-\xb9\xbc-\xbe\u09f4-\u09f9\u0b72-\u0b77\u0bf0-\u0bf2\u0c78-\u0c7e\u0d70-\u0d75\u0f2a-\u0f33\u1369-\u137c\u17f0-\u17f9\u19da-\u19da\u2070-\u2070\u2074-\u2079\u2080-\u2089\u2150-\u215f\u2189-\u2189\u2460-\u249b\u24ea-\u24ff\u2776-\u2793\u2cfd-\u2cfd\u3192-\u3195\u3220-\u3229\u3251-\u325f\u3280-\u3289\u32b1-\u32bf\ua830-\ua835\U00010107-\U00010133\U00010175-\U00010178\U0001018a-\U0001018a\U00010320-\U00010323\U00010858-\U0001085f\U00010916-\U0001091b\U00010a40-\U00010a47\U00010a7d-\U00010a7e\U00010b58-\U00010b5f\U00010b78-\U00010b7f\U00010e60-\U00010e7e\U00011052-\U00011065\U0001d360-\U0001d371\U0001f100-\U0001f10a];
		No { goto No; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_No [] = {0xb2,0xb3,  0xb9,0xb9,  0xbc,0xbe,  0x9f4,0x9f9,  0xb72,0xb77,  0xbf0,0xbf2,  0xc78,0xc7e,  0xd70,0xd75,  0xf2a,0xf33,  0x1369,0x137c,  0x17f0,0x17f9,  0x19da,0x19da,  0x2070,0x2070,  0x2074,0x2079,  0x2080,0x2089,  0x2150,0x215f,  0x2189,0x2189,  0x2460,0x249b,  0x24ea,0x24ff,  0x2776,0x2793,  0x2cfd,0x2cfd,  0x3192,0x3195,  0x3220,0x3229,  0x3251,0x325f,  0x3280,0x3289,  0x32b1,0x32bf,  0xa830,0xa835,  0x10107,0x10133,  0x10175,0x10178,  0x1018a,0x1018a,  0x10320,0x10323,  0x10858,0x1085f,  0x10916,0x1091b,  0x10a40,0x10a47,  0x10a7d,0x10a7e,  0x10b58,0x10b5f,  0x10b78,0x10b7f,  0x10e60,0x10e7e,  0x11052,0x11065,  0x1d360,0x1d371,  0x1f100,0x1f10a,  0x0,0x0};
static unsigned int encode_utf16 (const unsigned int * ranges, unsigned int ranges_count, unsigned short * s)
{
	unsigned short * const s_start = s;
	for (unsigned int i = 0; i < ranges_count; i += 2)
		for (unsigned int j = ranges[i]; j <= ranges[i + 1]; ++j)
		{
			if (j <= re2c::utf16::MAX_1WORD_RUNE)
				*s++ = j;
			else
			{
				*s++ = re2c::utf16::lead_surr(j);
				*s++ = re2c::utf16::trail_surr(j);
			}
		}
	return s - s_start;
}

int main ()
{
	YYCTYPE * buffer_No = new YYCTYPE [914];
	unsigned int buffer_len = encode_utf16 (chars_No, sizeof (chars_No) / sizeof (unsigned int), buffer_No);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_No), reinterpret_cast<const YYCTYPE *> (buffer_No + buffer_len)))
		printf("test 'No' failed\n");
	delete [] buffer_No;
	return 0;
}
