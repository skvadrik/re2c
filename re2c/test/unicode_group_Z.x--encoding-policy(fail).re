#include <stdio.h>
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Z:
	/*!re2c
		re2c:yyfill:enable = 0;
		Z = [\x20-\x20\xa0-\xa0\u1680-\u1680\u180e-\u180e\u2000-\u200a\u2028-\u2029\u202f-\u202f\u205f-\u205f\u3000-\u3000];
		Z { goto Z; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Z [] = "\x20\x00\xA0\x00\x80\x16\x0E\x18\x00\x20\x01\x20\x02\x20\x03\x20\x04\x20\x05\x20\x06\x20\x07\x20\x08\x20\x09\x20\x0A\x20\x28\x20\x29\x20\x2F\x20\x5F\x20\x00\x30\x00\x00";
int main ()
{
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Z), reinterpret_cast<const YYCTYPE *> (buffer_Z + sizeof (buffer_Z) - 1)))
		printf("test 'Z' failed\n");
}
