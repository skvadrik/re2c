// re2c $INPUT -o $OUTPUT
/*!re2c*/ // ok, end of block
/*!re2c */ // ok, space
/*!re2c	*/ // ok, space
/*!re2c
*/ // ok, newline
/*!re2c"a"{} */ // bad
