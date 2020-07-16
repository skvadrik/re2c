// re2c $INPUT -o $OUTPUT -w --encoding-policy fail
/*!re2c
	*	{ return DEFAULT; }
	[^]	{ return FULL; }
*/
