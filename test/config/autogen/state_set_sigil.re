// re2c $INPUT -o $OUTPUT -rfi
/*!rules:re2c
  [a] { a }
  *   { x }
*/

// re2c:api:sigil = "ÿ";
// re2c:define:YYSETSTATE = "state = @@;";
/*!use:re2c
  re2c:api:sigil = "ÿ";
  re2c:define:YYSETSTATE = "state = @@;";
*/

// re2c:api:sigil = "ÿ";
// re2c:define:YYSETSTATE = "state = ÿ;";
/*!use:re2c
  re2c:api:sigil = "ÿ";
  re2c:define:YYSETSTATE = "state = ÿ;";
*/

// re2c:api:sigil = @@;
// re2c:define:YYSETSTATE = "state = @@;";
/*!use:re2c
  re2c:api:sigil = @@;
  re2c:define:YYSETSTATE = "state = @@;";
*/

// re2c:api:sigil = @@;
// re2c:define:YYSETSTATE = "state = ÿ;";
/*!use:re2c
  re2c:api:sigil = @@;
  re2c:define:YYSETSTATE = "state = ÿ;";
*/

// re2c:define:YYSETSTATE@state = @@;
// re2c:api:sigil = "ÿ";
// re2c:define:YYSETSTATE = "state = @@;";
/*!use:re2c
  re2c:define:YYSETSTATE@state = @@;
  re2c:api:sigil = "ÿ";
  re2c:define:YYSETSTATE = "state = @@;";
*/

// re2c:define:YYSETSTATE@state = @@;
// re2c:api:sigil = "ÿ";
// re2c:define:YYSETSTATE = "state = ÿ;";
/*!use:re2c
  re2c:define:YYSETSTATE@state = @@;
  re2c:api:sigil = "ÿ";
  re2c:define:YYSETSTATE = "state = ÿ;";
*/

// re2c:define:YYSETSTATE@state = @@;
// re2c:api:sigil = @@;
// re2c:define:YYSETSTATE = "state = @@;";
/*!use:re2c
  re2c:define:YYSETSTATE@state = @@;
  re2c:api:sigil = @@;
  re2c:define:YYSETSTATE = "state = @@;";
*/

// re2c:define:YYSETSTATE@state = @@;
// re2c:api:sigil = @@;
// re2c:define:YYSETSTATE = "state = ÿ;";
/*!use:re2c
  re2c:define:YYSETSTATE@state = @@;
  re2c:api:sigil = @@;
  re2c:define:YYSETSTATE = "state = ÿ;";
*/

// re2c:define:YYSETSTATE@state = "ÿ";
// re2c:api:sigil = "ÿ";
// re2c:define:YYSETSTATE = "state = @@;";
/*!use:re2c
  re2c:define:YYSETSTATE@state = "ÿ";
  re2c:api:sigil = "ÿ";
  re2c:define:YYSETSTATE = "state = @@;";
*/

// re2c:define:YYSETSTATE@state = "ÿ";
// re2c:api:sigil = "ÿ";
// re2c:define:YYSETSTATE = "state = ÿ;";
/*!use:re2c
  re2c:define:YYSETSTATE@state = "ÿ";
  re2c:api:sigil = "ÿ";
  re2c:define:YYSETSTATE = "state = ÿ;";
*/

// re2c:define:YYSETSTATE@state = "ÿ";
// re2c:api:sigil = @@;
// re2c:define:YYSETSTATE = "state = @@;";
/*!use:re2c
  re2c:define:YYSETSTATE@state = "ÿ";
  re2c:api:sigil = @@;
  re2c:define:YYSETSTATE = "state = @@;";
*/

// re2c:define:YYSETSTATE@state = "ÿ";
// re2c:api:sigil = @@;
// re2c:define:YYSETSTATE = "state = ÿ;";
/*!use:re2c
  re2c:define:YYSETSTATE@state = "ÿ";
  re2c:api:sigil = @@;
  re2c:define:YYSETSTATE = "state = ÿ;";
*/

