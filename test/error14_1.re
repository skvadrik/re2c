// re2c $INPUT -o $OUTPUT -1
/*!re2c
	"ABC"		{ return 1; }
	"ABD"		{ return 2; }
	[^]			{ return 0; }
*/

/*!max:re2c */

/*!max:re2c */
