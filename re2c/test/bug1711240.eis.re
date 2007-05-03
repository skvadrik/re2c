char scan(const unsigned char *s)
{
/*!re2c
	'"'
	{
		return '"';
	}
	'\x2F'
	{
		return '\x2F';
	}
	'\x7F'
	{
		return '\x7F';
	}
	[^]
	{
		return '\0';
	}
*/
}
