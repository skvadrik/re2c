// re2c $INPUT -o $OUTPUT -1
/*!max:re2c */

/*!re2c
	"ABC"		{ return 1; }
	"ABD"		{ return 2; }
	[^]			{ return 0; }
*/
