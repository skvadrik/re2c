#include <stdio.h>
#include "utf8.h"
#define YYCTYPE unsigned char
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
L_:
	/*!re2c
		re2c:yyfill:enable = 0;
		L_ = [\x41-\x5a\x61-\x7a\xaa-\xaa\xb5-\xb5\xba-\xba\xc0-\xd6\xd8-\xf6\xf8-\u01ba\u01bc-\u01bf\u01c4-\u0293\u0295-\u02af\u0370-\u0373\u0376-\u0377\u037b-\u037d\u0386-\u0386\u0388-\u038a\u038c-\u038c\u038e-\u03a1\u03a3-\u03f5\u03f7-\u0481\u048a-\u0527\u0531-\u0556\u0561-\u0587\u10a0-\u10c5\u1d00-\u1d2b\u1d62-\u1d77\u1d79-\u1d9a\u1e00-\u1f15\u1f18-\u1f1d\u1f20-\u1f45\u1f48-\u1f4d\u1f50-\u1f57\u1f59-\u1f59\u1f5b-\u1f5b\u1f5d-\u1f5d\u1f5f-\u1f7d\u1f80-\u1fb4\u1fb6-\u1fbc\u1fbe-\u1fbe\u1fc2-\u1fc4\u1fc6-\u1fcc\u1fd0-\u1fd3\u1fd6-\u1fdb\u1fe0-\u1fec\u1ff2-\u1ff4\u1ff6-\u1ffc\u2102-\u2102\u2107-\u2107\u210a-\u2113\u2115-\u2115\u2119-\u211d\u2124-\u2124\u2126-\u2126\u2128-\u2128\u212a-\u212d\u212f-\u2134\u2139-\u2139\u213c-\u213f\u2145-\u2149\u214e-\u214e\u2183-\u2184\u2c00-\u2c2e\u2c30-\u2c5e\u2c60-\u2c7c\u2c7e-\u2ce4\u2ceb-\u2cee\u2d00-\u2d25\ua640-\ua66d\ua680-\ua697\ua722-\ua76f\ua771-\ua787\ua78b-\ua78e\ua790-\ua791\ua7a0-\ua7a9\ua7fa-\ua7fa\ufb00-\ufb06\ufb13-\ufb17\uff21-\uff3a\uff41-\uff5a\U00010400-\U0001044f\U0001d400-\U0001d454\U0001d456-\U0001d49c\U0001d49e-\U0001d49f\U0001d4a2-\U0001d4a2\U0001d4a5-\U0001d4a6\U0001d4a9-\U0001d4ac\U0001d4ae-\U0001d4b9\U0001d4bb-\U0001d4bb\U0001d4bd-\U0001d4c3\U0001d4c5-\U0001d505\U0001d507-\U0001d50a\U0001d50d-\U0001d514\U0001d516-\U0001d51c\U0001d51e-\U0001d539\U0001d53b-\U0001d53e\U0001d540-\U0001d544\U0001d546-\U0001d546\U0001d54a-\U0001d550\U0001d552-\U0001d6a5\U0001d6a8-\U0001d6c0\U0001d6c2-\U0001d6da\U0001d6dc-\U0001d6fa\U0001d6fc-\U0001d714\U0001d716-\U0001d734\U0001d736-\U0001d74e\U0001d750-\U0001d76e\U0001d770-\U0001d788\U0001d78a-\U0001d7a8\U0001d7aa-\U0001d7c2\U0001d7c4-\U0001d7cb];
		L_ { goto L_; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_L_ [] = {0x41,0x5a,  0x61,0x7a,  0xaa,0xaa,  0xb5,0xb5,  0xba,0xba,  0xc0,0xd6,  0xd8,0xf6,  0xf8,0x1ba,  0x1bc,0x1bf,  0x1c4,0x293,  0x295,0x2af,  0x370,0x373,  0x376,0x377,  0x37b,0x37d,  0x386,0x386,  0x388,0x38a,  0x38c,0x38c,  0x38e,0x3a1,  0x3a3,0x3f5,  0x3f7,0x481,  0x48a,0x527,  0x531,0x556,  0x561,0x587,  0x10a0,0x10c5,  0x1d00,0x1d2b,  0x1d62,0x1d77,  0x1d79,0x1d9a,  0x1e00,0x1f15,  0x1f18,0x1f1d,  0x1f20,0x1f45,  0x1f48,0x1f4d,  0x1f50,0x1f57,  0x1f59,0x1f59,  0x1f5b,0x1f5b,  0x1f5d,0x1f5d,  0x1f5f,0x1f7d,  0x1f80,0x1fb4,  0x1fb6,0x1fbc,  0x1fbe,0x1fbe,  0x1fc2,0x1fc4,  0x1fc6,0x1fcc,  0x1fd0,0x1fd3,  0x1fd6,0x1fdb,  0x1fe0,0x1fec,  0x1ff2,0x1ff4,  0x1ff6,0x1ffc,  0x2102,0x2102,  0x2107,0x2107,  0x210a,0x2113,  0x2115,0x2115,  0x2119,0x211d,  0x2124,0x2124,  0x2126,0x2126,  0x2128,0x2128,  0x212a,0x212d,  0x212f,0x2134,  0x2139,0x2139,  0x213c,0x213f,  0x2145,0x2149,  0x214e,0x214e,  0x2183,0x2184,  0x2c00,0x2c2e,  0x2c30,0x2c5e,  0x2c60,0x2c7c,  0x2c7e,0x2ce4,  0x2ceb,0x2cee,  0x2d00,0x2d25,  0xa640,0xa66d,  0xa680,0xa697,  0xa722,0xa76f,  0xa771,0xa787,  0xa78b,0xa78e,  0xa790,0xa791,  0xa7a0,0xa7a9,  0xa7fa,0xa7fa,  0xfb00,0xfb06,  0xfb13,0xfb17,  0xff21,0xff3a,  0xff41,0xff5a,  0x10400,0x1044f,  0x1d400,0x1d454,  0x1d456,0x1d49c,  0x1d49e,0x1d49f,  0x1d4a2,0x1d4a2,  0x1d4a5,0x1d4a6,  0x1d4a9,0x1d4ac,  0x1d4ae,0x1d4b9,  0x1d4bb,0x1d4bb,  0x1d4bd,0x1d4c3,  0x1d4c5,0x1d505,  0x1d507,0x1d50a,  0x1d50d,0x1d514,  0x1d516,0x1d51c,  0x1d51e,0x1d539,  0x1d53b,0x1d53e,  0x1d540,0x1d544,  0x1d546,0x1d546,  0x1d54a,0x1d550,  0x1d552,0x1d6a5,  0x1d6a8,0x1d6c0,  0x1d6c2,0x1d6da,  0x1d6dc,0x1d6fa,  0x1d6fc,0x1d714,  0x1d716,0x1d734,  0x1d736,0x1d74e,  0x1d750,0x1d76e,  0x1d770,0x1d788,  0x1d78a,0x1d7a8,  0x1d7aa,0x1d7c2,  0x1d7c4,0x1d7cb,  0x0,0x0};
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
	YYCTYPE * buffer_L_ = new YYCTYPE [12908];
	unsigned int buffer_len = encode_utf8 (chars_L_, sizeof (chars_L_) / sizeof (unsigned int), buffer_L_);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_L_), reinterpret_cast<const YYCTYPE *> (buffer_L_ + buffer_len)))
		printf("test 'L_' failed\n");
	delete [] buffer_L_;
	return 0;
}
