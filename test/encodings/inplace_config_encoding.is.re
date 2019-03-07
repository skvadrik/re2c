EBCDIC:
/*!re2c
	re2c:flags:e = 1;
	"a"	{return 0;}
	*	{return DEFAULT;}
*/

UCS2:
/*!re2c
	re2c:flags:e = 0;
	re2c:flags:w = 1;
	"\uFFFF"	{return 0;}
	*		{return DEFAULT;}
*/

UTF16:
/*!re2c
	re2c:flags:w = 0;
	re2c:flags:x = 1;
	"\U0010FFFF"	{return 0;}
	*		{return DEFAULT;}
*/

UTF32:
/*!re2c
	re2c:flags:x = 0;
	re2c:flags:u = 1;
	"\U0010FFFF"	{return 0;}
	*		{return DEFAULT;}
*/

UTF8:
/*!re2c
	re2c:flags:u = 0;
	re2c:flags:8 = 1;
	"\U0010FFFF"	{return 0;}
	*		{return DEFAULT;}
*/

ASCII:
/*!re2c
	re2c:flags:8 = 0;
	"a"	{return 0;}
	*	{return DEFAULT;}
*/
