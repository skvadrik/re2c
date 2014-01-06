#include <stdio.h>
bool scan(const char * start, const char * const limit)
{
#	define YYCTYPE unsigned char
#	define YYCURSOR start
Me:
	/*!re2c
		re2c:yyfill:enable = 0;
				Me = [\u0488-\u0489\u20dd-\u20e0\u20e2-\u20e4\ua670-\ua672];
		Me { goto Me; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Me [] = "\xD2\x88\xD2\x89\xE2\x83\x9D\xE2\x83\x9E\xE2\x83\x9F\xE2\x83\xA0\xE2\x83\xA2\xE2\x83\xA3\xE2\x83\xA4\xEA\x99\xB0\xEA\x99\xB1\xEA\x99\xB2\x00";
int main ()
{
	if (!scan (buffer_Me, buffer_Me + sizeof (buffer_Me) - 1))
		printf("test 'Me' failed\n");
}
