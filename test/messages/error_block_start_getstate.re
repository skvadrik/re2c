// re2c $INPUT -o $OUTPUT -f
/*!getstate:re2c*/ // ok, end of block
/*!getstate:re2c */ // ok, space
/*!getstate:re2c	*/ // ok, space
/*!getstate:re2c
*/ // ok, newline
/*!getstate:re2cx */ // bad
