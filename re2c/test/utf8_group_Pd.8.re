#include <stdio.h>
bool scan(const char * start, const char * const limit)
{
#	define YYCTYPE unsigned char
#	define YYCURSOR start
Pd:
	/*!re2c
		re2c:yyfill:enable = 0;
				Pd = [\x2d-\x2d\u058a-\u058a\u05be-\u05be\u1400-\u1400\u1806-\u1806\u2010-\u2015\u2e17-\u2e17\u2e1a-\u2e1a\u301c-\u301c\u3030-\u3030\u30a0-\u30a0\ufe31-\ufe32\ufe58-\ufe58\ufe63-\ufe63\uff0d-\uff0d];
		Pd { goto Pd; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Pd [] = "\x2D\xD6\x8A\xD6\xBE\xE1\x90\x80\xE1\xA0\x86\xE2\x80\x90\xE2\x80\x91\xE2\x80\x92\xE2\x80\x93\xE2\x80\x94\xE2\x80\x95\xE2\xB8\x97\xE2\xB8\x9A\xE3\x80\x9C\xE3\x80\xB0\xE3\x82\xA0\xEF\xB8\xB1\xEF\xB8\xB2\xEF\xB9\x98\xEF\xB9\xA3\xEF\xBC\x8D\x00";
int main ()
{
	if (!scan (buffer_Pd, buffer_Pd + sizeof (buffer_Pd) - 1))
		printf("test 'Pd' failed\n");
}
