// re2c $INPUT -o $OUTPUT -fi
/*!rules:re2c
  [a] { a }
  *   { x }
*/

// normal block, 1 state
/*!re2c
  re2c:define:YYGETSTATE = "GETSTATE_1";
  re2c:define:YYSETSTATE = "SETSTATE_1";

  [e] { e }
  *   { x }
*/

// reuse block, 3 states
/*!use:re2c
  re2c:define:YYGETSTATE = "GETSTATE_REUSE_1";
  re2c:define:YYSETSTATE = "SETSTATE_REUSE_1";

  [b]+ | [c]+ { c }
*/

// normal block, 1 state
/*!re2c
  re2c:define:YYGETSTATE = "GETSTATE_2";
  re2c:define:YYSETSTATE = "SETSTATE_2";

  [f] { f }
  *   { x }
*/

// last normal block, no rules, only the YYGETSTATE configuration
/*!re2c
  re2c:define:YYGETSTATE = "GETSTATE_LAST";
*/

// reuse block, 1 state
/*!use:re2c
  re2c:define:YYGETSTATE = "GETSTATE_REUSE_2";
  re2c:define:YYSETSTATE = "SETSTATE_REUSE_2";
*/
