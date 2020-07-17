// re2c $INPUT -o $OUTPUT -rci
/*!rules:re2c
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
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

// re2c:define:YYSETCONDITION:naked = 0;
/*!use:re2c
  re2c:define:YYSETCONDITION:naked = 0;
*/

// re2c:define:YYSETCONDITION:naked = 0;
// re2c:api:style = free-form;
/*!use:re2c
  re2c:define:YYSETCONDITION:naked = 0;
  re2c:api:style = free-form;
*/

// re2c:define:YYSETCONDITION:naked = 0;
// re2c:api:style = functions;
/*!use:re2c
  re2c:define:YYSETCONDITION:naked = 0;
  re2c:api:style = functions;
*/

// re2c:define:YYSETCONDITION:naked = 1;
/*!use:re2c
  re2c:define:YYSETCONDITION:naked = 1;
*/

// re2c:define:YYSETCONDITION:naked = 1;
// re2c:api:style = free-form;
/*!use:re2c
  re2c:define:YYSETCONDITION:naked = 1;
  re2c:api:style = free-form;
*/

// re2c:define:YYSETCONDITION:naked = 1;
// re2c:api:style = functions;
/*!use:re2c
  re2c:define:YYSETCONDITION:naked = 1;
  re2c:api:style = functions;
*/

