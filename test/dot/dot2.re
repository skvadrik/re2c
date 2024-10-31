// re2c $INPUT -o $OUTPUT  --emit-dot --lang haskell

// Set a different language to ensure that the generated fingerprint
// still uses C-style comment syntax.

/*!re2c

"\x00"	{ return 1; }
[^]	{ return 3; }

*/
