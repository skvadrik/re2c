// re2c $INPUT -o $OUTPUT
/*!types:re2c*/ // ok, end of block
/*!types:re2c */ // ok, space
/*!types:re2c	*/ // ok, space
/*!types:re2c
*/ // ok, newline
/*!types:re2cx */ // bad
