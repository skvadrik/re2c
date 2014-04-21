#include <stdio.h>
#include "utf8.h"
#define YYCTYPE unsigned char
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Pf:
	/*!re2c
		re2c:yyfill:enable = 0;
		Pf = [\xbb-\xbb\u2019-\u2019\u201d-\u201d\u203a-\u203a\u2e03-\u2e03\u2e05-\u2e05\u2e0a-\u2e0a\u2e0d-\u2e0d\u2e1d-\u2e1d\u2e21-\u2e21];
		Pf { goto Pf; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Pf [] = {0xbb,0xbb,  0x2019,0x2019,  0x201d,0x201d,  0x203a,0x203a,  0x2e03,0x2e03,  0x2e05,0x2e05,  0x2e0a,0x2e0a,  0x2e0d,0x2e0d,  0x2e1d,0x2e1d,  0x2e21,0x2e21,  0x0,0x0};
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
	YYCTYPE * buffer_Pf = new YYCTYPE [44];
	unsigned int buffer_len = encode_utf8 (chars_Pf, sizeof (chars_Pf) / sizeof (unsigned int), buffer_Pf);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Pf), reinterpret_cast<const YYCTYPE *> (buffer_Pf + buffer_len)))
		printf("test 'Pf' failed\n");
	delete [] buffer_Pf;
	return 0;
}
