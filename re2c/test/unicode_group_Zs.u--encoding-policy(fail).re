#include <stdio.h>
#define YYCTYPE unsigned int
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Zs:
	/*!re2c
		re2c:yyfill:enable = 0;
		Zs = [\x20-\x20\xa0-\xa0\u1680-\u1680\u180e-\u180e\u2000-\u200a\u202f-\u202f\u205f-\u205f\u3000-\u3000];
		Zs { goto Zs; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Zs [] = "\x20\x00\x00\x00\xA0\x00\x00\x00\x80\x16\x00\x00\x0E\x18\x00\x00\x00\x20\x00\x00\x01\x20\x00\x00\x02\x20\x00\x00\x03\x20\x00\x00\x04\x20\x00\x00\x05\x20\x00\x00\x06\x20\x00\x00\x07\x20\x00\x00\x08\x20\x00\x00\x09\x20\x00\x00\x0A\x20\x00\x00\x2F\x20\x00\x00\x5F\x20\x00\x00\x00\x30\x00\x00\x00\x00\x00\x00";
int main ()
{
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Zs), reinterpret_cast<const YYCTYPE *> (buffer_Zs + sizeof (buffer_Zs) - 1)))
		printf("test 'Zs' failed\n");
}
