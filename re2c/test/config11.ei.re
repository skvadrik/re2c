unsigned char scan(const unsigned char *s)
{
	unsigned char* cr;
	unsigned char  ch;
/*!re2c

re2c:define:YYCTYPE     = "unsigned char";
re2c:define:YYCURSOR    = cr;
re2c:define:YYFILL      = fill;
re2c:variable:yych      = ch;
re2c:yyfill:enable      = 0;

"a" := return 'a';
"b" := return 'b';

*/
}
