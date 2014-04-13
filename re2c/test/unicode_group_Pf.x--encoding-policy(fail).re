#include <stdio.h>
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Pf:
	/*!re2c
		re2c:yyfill:enable = 0;
		Pf = [\xbb-\xbb\u2019-\u2019\u201d-\u201d\u203a-\u203a\u2e03-\u2e03\u2e05-\u2e05\u2e0a-\u2e0a\u2e0d-\u2e0d\u2e1d-\u2e1d\u2e21-\u2e21];
		Pf { goto Pf; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Pf [] = "\xBB\x00\x19\x20\x1D\x20\x3A\x20\x03\x2E\x05\x2E\x0A\x2E\x0D\x2E\x1D\x2E\x21\x2E\x00\x00";
int main ()
{
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Pf), reinterpret_cast<const YYCTYPE *> (buffer_Pf + sizeof (buffer_Pf) - 1)))
		printf("test 'Pf' failed\n");
}
