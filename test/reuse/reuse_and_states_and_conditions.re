// re2c $INPUT -o $OUTPUT -cfi
/*!types:re2c*/

/*!rules:re2c
  <a> [a] :=> b
  <b> [b] :=> a
  <*> * { x }
*/

// normal block, 2 states (+1 from other normal blocks), 2 conditions
/*!re2c
  re2c:define:YYGETSTATE = "GETSTATE_1";
  re2c:define:YYSETSTATE = "SETSTATE_1";

  <u> [u] :=> v
  <v> [v] :=> u
  <*> *   { x }
*/

// reuse block, 4 states, 4 conditions
/*!use:re2c
  re2c:define:YYGETSTATE = "GETSTATE_REUSE_1";
  re2c:define:YYSETSTATE = "SETSTATE_REUSE_1";

  <c> [c] { c }
  <d> [d] { d }
*/

// reuse block, 4 states, 3 conditions
/*!use:re2c
  re2c:define:YYGETSTATE = "GETSTATE_REUSE_2";
  re2c:define:YYSETSTATE = "SETSTATE_REUSE_2";

  <e> [e]+ { e }
*/

// normal block, 1 state, 1 condition
/*!re2c
  re2c:define:YYGETSTATE = "GETSTATE_2";
  re2c:define:YYSETSTATE = "SETSTATE_2";

  <w> [w] { w }
  <*> *   { x }
*/

// last normal block, no rules, only the YYGETSTATE configuration
/*!re2c
  re2c:define:YYGETSTATE = "GETSTATE_LAST";
*/
