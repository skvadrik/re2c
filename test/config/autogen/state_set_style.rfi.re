// re2c $INPUT -o $OUTPUT -rfi
/*!rules:re2c
  [a] { a }
  *   { x }
*/

/*!use:re2c
*/

// re2c:api:style = free-form;
/*!use:re2c
  re2c:api:style = free-form;
*/

// re2c:api:style = functions;
/*!use:re2c
  re2c:api:style = functions;
*/

// re2c:define:YYSETSTATE:naked = 0;
/*!use:re2c
  re2c:define:YYSETSTATE:naked = 0;
*/

// re2c:define:YYSETSTATE:naked = 0;
// re2c:api:style = free-form;
/*!use:re2c
  re2c:define:YYSETSTATE:naked = 0;
  re2c:api:style = free-form;
*/

// re2c:define:YYSETSTATE:naked = 0;
// re2c:api:style = functions;
/*!use:re2c
  re2c:define:YYSETSTATE:naked = 0;
  re2c:api:style = functions;
*/

// re2c:define:YYSETSTATE:naked = 1;
/*!use:re2c
  re2c:define:YYSETSTATE:naked = 1;
*/

// re2c:define:YYSETSTATE:naked = 1;
// re2c:api:style = free-form;
/*!use:re2c
  re2c:define:YYSETSTATE:naked = 1;
  re2c:api:style = free-form;
*/

// re2c:define:YYSETSTATE:naked = 1;
// re2c:api:style = functions;
/*!use:re2c
  re2c:define:YYSETSTATE:naked = 1;
  re2c:api:style = functions;
*/

