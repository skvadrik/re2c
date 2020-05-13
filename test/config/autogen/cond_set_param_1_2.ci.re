// re2c:define:YYSETCONDITION = "cond = @@;";
// re2c:define:YYSETCONDITION@cond = #;
/*!re2c
  re2c:define:YYSETCONDITION = "cond = @@;";
  re2c:define:YYSETCONDITION@cond = #;
  <c1> [a] => c2 { a }
  <c2> [b] => c1 { b }
  <*> *          { x }
*/
