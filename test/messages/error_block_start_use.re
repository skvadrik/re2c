// re2c $INPUT -o $OUTPUT

/*!rules:re2c*/
/*!rules:re2c:_Yx1*/
/*!rules:re2c:Yx1*/
/*!rules:re2c:yX1*/
/*!rules:re2c:yX1_*/
/*!rules:re2c:_*/

/*!use:re2c*/ // ok, end of block
/*!use:re2c:_Yx1*/ // ok, end of block
/*!use:re2c */ // ok, space
/*!use:re2c:Yx1 */ // ok, space
/*!use:re2c	*/ // ok, space
/*!use:re2c:yX1_	*/ // ok, space
/*!use:re2c
*/ // ok, newline
/*!use:re2c:_
*/ // ok, newline
/*!use:re2c: */ // bad, empty name
