/*!re2c
  [a] { a }
  *   { x }
*/

// re2c:decorate = 0;
/*!re2c
  re2c:decorate = 0;
  [a] { a }
  *   { x }
*/

// re2c:decorate = 1;
/*!re2c
  re2c:decorate = 1;
  [a] { a }
  *   { x }
*/

// re2c:define:YYSETSTATE:naked = 0;
/*!re2c
  re2c:define:YYSETSTATE:naked = 0;
  [a] { a }
  *   { x }
*/

// re2c:define:YYSETSTATE:naked = 0;
// re2c:decorate = 0;
/*!re2c
  re2c:define:YYSETSTATE:naked = 0;
  re2c:decorate = 0;
  [a] { a }
  *   { x }
*/

// re2c:define:YYSETSTATE:naked = 0;
// re2c:decorate = 1;
/*!re2c
  re2c:define:YYSETSTATE:naked = 0;
  re2c:decorate = 1;
  [a] { a }
  *   { x }
*/

// re2c:define:YYSETSTATE:naked = 1;
/*!re2c
  re2c:define:YYSETSTATE:naked = 1;
  [a] { a }
  *   { x }
*/

// re2c:define:YYSETSTATE:naked = 1;
// re2c:decorate = 0;
/*!re2c
  re2c:define:YYSETSTATE:naked = 1;
  re2c:decorate = 0;
  [a] { a }
  *   { x }
*/

// re2c:define:YYSETSTATE:naked = 1;
// re2c:decorate = 1;
/*!re2c
  re2c:define:YYSETSTATE:naked = 1;
  re2c:decorate = 1;
  [a] { a }
  *   { x }
*/

