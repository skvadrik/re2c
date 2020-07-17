// re2c $INPUT -o $OUTPUT  --emit-dot
/*!re2c

"\x00"	{ return 1; }
[^]	{ return 3; }

*/
