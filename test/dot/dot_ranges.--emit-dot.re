// re2c $INPUT -o $OUTPUT  --emit-dot
/*!re2c

	[a-b\xFE-\xFF]	{ return 1; }
	[0-8] | "^"	{ return 2; }
	[^]		{ return 3; }

*/
