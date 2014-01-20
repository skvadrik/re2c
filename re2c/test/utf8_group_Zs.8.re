#include <stdio.h>
bool scan(const char * start, const char * const limit)
{
#	define YYCTYPE unsigned char
#	define YYCURSOR start
Zs:
	/*!re2c
		re2c:yyfill:enable = 0;
				Zs = [\x20-\x20\xa0-\xa0\u1680-\u1680\u180e-\u180e\u2000-\u200a\u202f-\u202f\u205f-\u205f\u3000-\u3000];
		Zs { goto Zs; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Zs [] = "\x20\xC2\xA0\xE1\x9A\x80\xE1\xA0\x8E\xE2\x80\x80\xE2\x80\x81\xE2\x80\x82\xE2\x80\x83\xE2\x80\x84\xE2\x80\x85\xE2\x80\x86\xE2\x80\x87\xE2\x80\x88\xE2\x80\x89\xE2\x80\x8A\xE2\x80\xAF\xE2\x81\x9F\xE3\x80\x80\x00";
int main ()
{
	if (!scan (buffer_Zs, buffer_Zs + sizeof (buffer_Zs) - 1))
		printf("test 'Zs' failed\n");
}
