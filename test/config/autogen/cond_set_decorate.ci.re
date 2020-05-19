/*!re2c
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
*/

// re2c:decorate = 0;
/*!re2c
  re2c:decorate = 0;
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
*/

// re2c:decorate = 1;
/*!re2c
  re2c:decorate = 1;
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
*/

// re2c:define:YYSETCONDITION:naked = 0;
/*!re2c
  re2c:define:YYSETCONDITION:naked = 0;
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
*/

// re2c:define:YYSETCONDITION:naked = 0;
// re2c:decorate = 0;
/*!re2c
  re2c:define:YYSETCONDITION:naked = 0;
  re2c:decorate = 0;
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
*/

// re2c:define:YYSETCONDITION:naked = 0;
// re2c:decorate = 1;
/*!re2c
  re2c:define:YYSETCONDITION:naked = 0;
  re2c:decorate = 1;
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
*/

// re2c:define:YYSETCONDITION:naked = 1;
/*!re2c
  re2c:define:YYSETCONDITION:naked = 1;
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
*/

// re2c:define:YYSETCONDITION:naked = 1;
// re2c:decorate = 0;
/*!re2c
  re2c:define:YYSETCONDITION:naked = 1;
  re2c:decorate = 0;
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
*/

// re2c:define:YYSETCONDITION:naked = 1;
// re2c:decorate = 1;
/*!re2c
  re2c:define:YYSETCONDITION:naked = 1;
  re2c:decorate = 1;
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
*/

