// re2c:define:YYGETCONDITION:naked = 1;
// re2c:decorate = 1;
/*!re2c
  re2c:define:YYGETCONDITION:naked = 1;
  re2c:decorate = 1;
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
*/
