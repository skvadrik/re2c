#include <stdio.h>
bool scan(const char * start, const char * const limit)
{
#	define YYCTYPE unsigned char
#	define YYCURSOR start
Zp:
	/*!re2c
		re2c:yyfill:enable = 0;
				Zp = [\u2029-\u2029];
		Zp { goto Zp; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Zp [] = "\xE2\x80\xA9\x00";
int main ()
{
	if (!scan (buffer_Zp, buffer_Zp + sizeof (buffer_Zp) - 1))
		printf("test 'Zp' failed\n");
}
