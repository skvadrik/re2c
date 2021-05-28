// re2c $INPUT -o $OUTPUT
/*!ignore:re2c*/ // ok, end of block
/*!ignore:re2c */ // ok, space
/*!ignore:re2c	*/ // ok, space
/*!ignore:re2c
*/ // ok, newline
/*!ignore:re2cx */ // bad
