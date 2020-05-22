/*!rules:re2c
  [a] { a }
  *   { x }
*/

/*!use:re2c
*/

// re2c:decorate = 0;
/*!use:re2c
  re2c:decorate = 0;
*/

// re2c:decorate = 1;
/*!use:re2c
  re2c:decorate = 1;
*/

// re2c:define:YYGETSTATE:naked = 0;
/*!use:re2c
  re2c:define:YYGETSTATE:naked = 0;
*/

// re2c:define:YYGETSTATE:naked = 0;
// re2c:decorate = 0;
/*!use:re2c
  re2c:define:YYGETSTATE:naked = 0;
  re2c:decorate = 0;
*/

// re2c:define:YYGETSTATE:naked = 0;
// re2c:decorate = 1;
/*!use:re2c
  re2c:define:YYGETSTATE:naked = 0;
  re2c:decorate = 1;
*/

// re2c:define:YYGETSTATE:naked = 1;
/*!use:re2c
  re2c:define:YYGETSTATE:naked = 1;
*/

// re2c:define:YYGETSTATE:naked = 1;
// re2c:decorate = 0;
/*!use:re2c
  re2c:define:YYGETSTATE:naked = 1;
  re2c:decorate = 0;
*/

// re2c:define:YYGETSTATE:naked = 1;
// re2c:decorate = 1;
/*!use:re2c
  re2c:define:YYGETSTATE:naked = 1;
  re2c:decorate = 1;
*/

