// re2c $INPUT -o $OUTPUT -x --encoding-policy fail
/*!re2c
	*	{ return DEFAULT; }
	[^]	{ return FULL; }
*/
