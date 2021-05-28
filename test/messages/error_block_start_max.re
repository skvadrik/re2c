// re2c $INPUT -o $OUTPUT
/*!max:re2c*/ // ok, end of block
/*!max:re2c */ // ok, space
/*!max:re2c	*/ // ok, space
/*!max:re2c
*/ // ok, newline
/*!max:re2c1 */ // bad
