/*!rules:re2c
  [a] { a }
  *   { x }
*/

// this block has 3 states
/*!use:re2c
  re2c:define:YYGETSTATE = "GETSTATE_1";
  re2c:define:YYSETSTATE = "SETSTATE_1";

  [b]+ | [c]+ { c }
*/

// this block has 1 state
/*!use:re2c
  re2c:define:YYGETSTATE = "GETSTATE_2";
  re2c:define:YYSETSTATE = "SETSTATE_2";
*/
