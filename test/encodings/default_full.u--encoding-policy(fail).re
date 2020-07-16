// re2c $INPUT -o $OUTPUT -u --encoding-policy fail
/*!re2c
	*	{ return DEFAULT; }
	[^]	{ return FULL; }
*/
