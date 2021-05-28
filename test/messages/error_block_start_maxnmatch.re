// re2c $INPUT -o $OUTPUT
/*!maxnmatch:re2c*/ // ok, end of block
/*!maxnmatch:re2c */ // ok, space
/*!maxnmatch:re2c	*/ // ok, space
/*!maxnmatch:re2c
*/ // ok, newline
/*!maxnmatch:re2cx */ // bad
