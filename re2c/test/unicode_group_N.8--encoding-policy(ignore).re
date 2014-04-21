#include <stdio.h>
#include "utf8.h"
#define YYCTYPE unsigned char
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
N:
	/*!re2c
		re2c:yyfill:enable = 0;
		N = [\x30-\x39\xb2-\xb3\xb9-\xb9\xbc-\xbe\u0660-\u0669\u06f0-\u06f9\u07c0-\u07c9\u0966-\u096f\u09e6-\u09ef\u09f4-\u09f9\u0a66-\u0a6f\u0ae6-\u0aef\u0b66-\u0b6f\u0b72-\u0b77\u0be6-\u0bf2\u0c66-\u0c6f\u0c78-\u0c7e\u0ce6-\u0cef\u0d66-\u0d75\u0e50-\u0e59\u0ed0-\u0ed9\u0f20-\u0f33\u1040-\u1049\u1090-\u1099\u1369-\u137c\u16ee-\u16f0\u17e0-\u17e9\u17f0-\u17f9\u1810-\u1819\u1946-\u194f\u19d0-\u19da\u1a80-\u1a89\u1a90-\u1a99\u1b50-\u1b59\u1bb0-\u1bb9\u1c40-\u1c49\u1c50-\u1c59\u2070-\u2070\u2074-\u2079\u2080-\u2089\u2150-\u2182\u2185-\u2189\u2460-\u249b\u24ea-\u24ff\u2776-\u2793\u2cfd-\u2cfd\u3007-\u3007\u3021-\u3029\u3038-\u303a\u3192-\u3195\u3220-\u3229\u3251-\u325f\u3280-\u3289\u32b1-\u32bf\ua620-\ua629\ua6e6-\ua6ef\ua830-\ua835\ua8d0-\ua8d9\ua900-\ua909\ua9d0-\ua9d9\uaa50-\uaa59\uabf0-\uabf9\uff10-\uff19\U00010107-\U00010133\U00010140-\U00010178\U0001018a-\U0001018a\U00010320-\U00010323\U00010341-\U00010341\U0001034a-\U0001034a\U000103d1-\U000103d5\U000104a0-\U000104a9\U00010858-\U0001085f\U00010916-\U0001091b\U00010a40-\U00010a47\U00010a7d-\U00010a7e\U00010b58-\U00010b5f\U00010b78-\U00010b7f\U00010e60-\U00010e7e\U00011052-\U0001106f\U00012400-\U00012462\U0001d360-\U0001d371\U0001d7ce-\U0001d7ff\U0001f100-\U0001f10a];
		N { goto N; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_N [] = {0x30,0x39,  0xb2,0xb3,  0xb9,0xb9,  0xbc,0xbe,  0x660,0x669,  0x6f0,0x6f9,  0x7c0,0x7c9,  0x966,0x96f,  0x9e6,0x9ef,  0x9f4,0x9f9,  0xa66,0xa6f,  0xae6,0xaef,  0xb66,0xb6f,  0xb72,0xb77,  0xbe6,0xbf2,  0xc66,0xc6f,  0xc78,0xc7e,  0xce6,0xcef,  0xd66,0xd75,  0xe50,0xe59,  0xed0,0xed9,  0xf20,0xf33,  0x1040,0x1049,  0x1090,0x1099,  0x1369,0x137c,  0x16ee,0x16f0,  0x17e0,0x17e9,  0x17f0,0x17f9,  0x1810,0x1819,  0x1946,0x194f,  0x19d0,0x19da,  0x1a80,0x1a89,  0x1a90,0x1a99,  0x1b50,0x1b59,  0x1bb0,0x1bb9,  0x1c40,0x1c49,  0x1c50,0x1c59,  0x2070,0x2070,  0x2074,0x2079,  0x2080,0x2089,  0x2150,0x2182,  0x2185,0x2189,  0x2460,0x249b,  0x24ea,0x24ff,  0x2776,0x2793,  0x2cfd,0x2cfd,  0x3007,0x3007,  0x3021,0x3029,  0x3038,0x303a,  0x3192,0x3195,  0x3220,0x3229,  0x3251,0x325f,  0x3280,0x3289,  0x32b1,0x32bf,  0xa620,0xa629,  0xa6e6,0xa6ef,  0xa830,0xa835,  0xa8d0,0xa8d9,  0xa900,0xa909,  0xa9d0,0xa9d9,  0xaa50,0xaa59,  0xabf0,0xabf9,  0xff10,0xff19,  0x10107,0x10133,  0x10140,0x10178,  0x1018a,0x1018a,  0x10320,0x10323,  0x10341,0x10341,  0x1034a,0x1034a,  0x103d1,0x103d5,  0x104a0,0x104a9,  0x10858,0x1085f,  0x10916,0x1091b,  0x10a40,0x10a47,  0x10a7d,0x10a7e,  0x10b58,0x10b5f,  0x10b78,0x10b7f,  0x10e60,0x10e7e,  0x11052,0x1106f,  0x12400,0x12462,  0x1d360,0x1d371,  0x1d7ce,0x1d7ff,  0x1f100,0x1f10a,  0x0,0x0};
static unsigned int encode_utf8 (const unsigned int * ranges, unsigned int ranges_count, unsigned char * s)
{
	unsigned char * const s_start = s;
	for (unsigned int i = 0; i < ranges_count - 2; i += 2)
		for (unsigned int j = ranges[i]; j <= ranges[i + 1]; ++j)
			s += re2c::utf8::rune_to_bytes (s, j);
	re2c::utf8::rune_to_bytes (s, ranges[ranges_count - 1]);
	return s - s_start + 1;
}

int main ()
{
	YYCTYPE * buffer_N = new YYCTYPE [4404];
	unsigned int buffer_len = encode_utf8 (chars_N, sizeof (chars_N) / sizeof (unsigned int), buffer_N);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_N), reinterpret_cast<const YYCTYPE *> (buffer_N + buffer_len)))
		printf("test 'N' failed\n");
	delete [] buffer_N;
	return 0;
}
