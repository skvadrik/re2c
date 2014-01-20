#include <stdio.h>
bool scan(const char * start, const char * const limit)
{
#	define YYCTYPE unsigned char
#	define YYCURSOR start
Pc:
	/*!re2c
		re2c:yyfill:enable = 0;
				Pc = [\x5f-\x5f\u203f-\u2040\u2054-\u2054\ufe33-\ufe34\ufe4d-\ufe4f\uff3f-\uff3f];
		Pc { goto Pc; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Pc [] = "\x5F\xE2\x80\xBF\xE2\x81\x80\xE2\x81\x94\xEF\xB8\xB3\xEF\xB8\xB4\xEF\xB9\x8D\xEF\xB9\x8E\xEF\xB9\x8F\xEF\xBC\xBF\x00";
int main ()
{
	if (!scan (buffer_Pc, buffer_Pc + sizeof (buffer_Pc) - 1))
		printf("test 'Pc' failed\n");
}
