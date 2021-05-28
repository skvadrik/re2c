// re2c $INPUT -o $OUTPUT
/*!header:re2c:on*/ // ok, end of block
/*!header:re2c:off*/ // ok, end of block
/*!header:re2c:on */ // ok, space
/*!header:re2c:off	*/ // ok, space
/*!header:re2c:on
*/ // ok, newline
/*!header:re2c */ // bad
