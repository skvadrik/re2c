// re2c $INPUT -o $OUTPUT
/*!rules:re2c*/ // ok, end of block
/*!rules:re2c:_Yx1*/ // ok, end of block
/*!rules:re2c */ // ok, space
/*!rules:re2c:Yx1 */ // ok, space
/*!rules:re2c	*/ // ok, space
/*!rules:re2c:yX1_	*/ // ok, space
/*!rules:re2c
*/ // ok, newline
/*!rules:re2c:_
*/ // ok, newline
/*!rules:re2c:1Yx */ // bad, name starts with digit
