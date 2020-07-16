// re2c $INPUT -o $OUTPUT -fi
/*!re2c
  [a] { a }
  *   { x }
*/

// re2c:api:style = free-form;
/*!re2c
  re2c:api:style = free-form;
  [a] { a }
  *   { x }
*/

// re2c:api:style = functions;
/*!re2c
  re2c:api:style = functions;
  [a] { a }
  *   { x }
*/

// re2c:define:YYGETSTATE:naked = 0;
/*!re2c
  re2c:define:YYGETSTATE:naked = 0;
  [a] { a }
  *   { x }
*/

// re2c:define:YYGETSTATE:naked = 0;
// re2c:api:style = free-form;
/*!re2c
  re2c:define:YYGETSTATE:naked = 0;
  re2c:api:style = free-form;
  [a] { a }
  *   { x }
*/

// re2c:define:YYGETSTATE:naked = 0;
// re2c:api:style = functions;
/*!re2c
  re2c:define:YYGETSTATE:naked = 0;
  re2c:api:style = functions;
  [a] { a }
  *   { x }
*/

// re2c:define:YYGETSTATE:naked = 1;
/*!re2c
  re2c:define:YYGETSTATE:naked = 1;
  [a] { a }
  *   { x }
*/

// re2c:define:YYGETSTATE:naked = 1;
// re2c:api:style = free-form;
/*!re2c
  re2c:define:YYGETSTATE:naked = 1;
  re2c:api:style = free-form;
  [a] { a }
  *   { x }
*/

// re2c:define:YYGETSTATE:naked = 1;
// re2c:api:style = functions;
/*!re2c
  re2c:define:YYGETSTATE:naked = 1;
  re2c:api:style = functions;
  [a] { a }
  *   { x }
*/

