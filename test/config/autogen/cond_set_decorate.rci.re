/*!rules:re2c
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
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

// re2c:define:YYSETCONDITION:naked = 0;
/*!use:re2c
  re2c:define:YYSETCONDITION:naked = 0;
*/

// re2c:define:YYSETCONDITION:naked = 0;
// re2c:decorate = 0;
/*!use:re2c
  re2c:define:YYSETCONDITION:naked = 0;
  re2c:decorate = 0;
*/

// re2c:define:YYSETCONDITION:naked = 0;
// re2c:decorate = 1;
/*!use:re2c
  re2c:define:YYSETCONDITION:naked = 0;
  re2c:decorate = 1;
*/

// re2c:define:YYSETCONDITION:naked = 1;
/*!use:re2c
  re2c:define:YYSETCONDITION:naked = 1;
*/

// re2c:define:YYSETCONDITION:naked = 1;
// re2c:decorate = 0;
/*!use:re2c
  re2c:define:YYSETCONDITION:naked = 1;
  re2c:decorate = 0;
*/

// re2c:define:YYSETCONDITION:naked = 1;
// re2c:decorate = 1;
/*!use:re2c
  re2c:define:YYSETCONDITION:naked = 1;
  re2c:decorate = 1;
*/

