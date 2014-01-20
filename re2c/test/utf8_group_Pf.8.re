#include <stdio.h>
bool scan(const char * start, const char * const limit)
{
#	define YYCTYPE unsigned char
#	define YYCURSOR start
Pf:
	/*!re2c
		re2c:yyfill:enable = 0;
				Pf = [\xbb-\xbb\u2019-\u2019\u201d-\u201d\u203a-\u203a\u2e03-\u2e03\u2e05-\u2e05\u2e0a-\u2e0a\u2e0d-\u2e0d\u2e1d-\u2e1d\u2e21-\u2e21];
		Pf { goto Pf; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Pf [] = "\xC2\xBB\xE2\x80\x99\xE2\x80\x9D\xE2\x80\xBA\xE2\xB8\x83\xE2\xB8\x85\xE2\xB8\x8A\xE2\xB8\x8D\xE2\xB8\x9D\xE2\xB8\xA1\x00";
int main ()
{
	if (!scan (buffer_Pf, buffer_Pf + sizeof (buffer_Pf) - 1))
		printf("test 'Pf' failed\n");
}
