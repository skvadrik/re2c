// re2c $INPUT -o $OUTPUT -8 --encoding-policy fail
/*!re2c
	*	{ return DEFAULT; }
	[^]	{ return FULL; }
*/
