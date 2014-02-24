#include <stdio.h>
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Pe:
	/*!re2c
		re2c:yyfill:enable = 0;
				Pe = [\x29-\x29\x5d-\x5d\x7d-\x7d\u0f3b-\u0f3b\u0f3d-\u0f3d\u169c-\u169c\u2046-\u2046\u207e-\u207e\u208e-\u208e\u232a-\u232a\u2769-\u2769\u276b-\u276b\u276d-\u276d\u276f-\u276f\u2771-\u2771\u2773-\u2773\u2775-\u2775\u27c6-\u27c6\u27e7-\u27e7\u27e9-\u27e9\u27eb-\u27eb\u27ed-\u27ed\u27ef-\u27ef\u2984-\u2984\u2986-\u2986\u2988-\u2988\u298a-\u298a\u298c-\u298c\u298e-\u298e\u2990-\u2990\u2992-\u2992\u2994-\u2994\u2996-\u2996\u2998-\u2998\u29d9-\u29d9\u29db-\u29db\u29fd-\u29fd\u2e23-\u2e23\u2e25-\u2e25\u2e27-\u2e27\u2e29-\u2e29\u3009-\u3009\u300b-\u300b\u300d-\u300d\u300f-\u300f\u3011-\u3011\u3015-\u3015\u3017-\u3017\u3019-\u3019\u301b-\u301b\u301e-\u301f\ufd3f-\ufd3f\ufe18-\ufe18\ufe36-\ufe36\ufe38-\ufe38\ufe3a-\ufe3a\ufe3c-\ufe3c\ufe3e-\ufe3e\ufe40-\ufe40\ufe42-\ufe42\ufe44-\ufe44\ufe48-\ufe48\ufe5a-\ufe5a\ufe5c-\ufe5c\ufe5e-\ufe5e\uff09-\uff09\uff3d-\uff3d\uff5d-\uff5d\uff60-\uff60\uff63-\uff63];
		Pe { goto Pe; }
		[^] { return YYCURSOR == limit; }
	*/
}
static const char buffer_Pe [] = "\x29\x00\x5D\x00\x7D\x00\x3B\x0F\x3D\x0F\x9C\x16\x46\x20\x7E\x20\x8E\x20\x2A\x23\x69\x27\x6B\x27\x6D\x27\x6F\x27\x71\x27\x73\x27\x75\x27\xC6\x27\xE7\x27\xE9\x27\xEB\x27\xED\x27\xEF\x27\x84\x29\x86\x29\x88\x29\x8A\x29\x8C\x29\x8E\x29\x90\x29\x92\x29\x94\x29\x96\x29\x98\x29\xD9\x29\xDB\x29\xFD\x29\x23\x2E\x25\x2E\x27\x2E\x29\x2E\x09\x30\x0B\x30\x0D\x30\x0F\x30\x11\x30\x15\x30\x17\x30\x19\x30\x1B\x30\x1E\x30\x1F\x30\x3F\xFD\x18\xFE\x36\xFE\x38\xFE\x3A\xFE\x3C\xFE\x3E\xFE\x40\xFE\x42\xFE\x44\xFE\x48\xFE\x5A\xFE\x5C\xFE\x5E\xFE\x09\xFF\x3D\xFF\x5D\xFF\x60\xFF\x63\xFF\x00\x00";
int main ()
{
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Pe), reinterpret_cast<const YYCTYPE *> (buffer_Pe + sizeof (buffer_Pe) - 1)))
		printf("test 'Pe' failed\n");
}
