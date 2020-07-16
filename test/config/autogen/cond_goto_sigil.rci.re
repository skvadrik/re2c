// re2c $INPUT -o $OUTPUT -rci
/*!rules:re2c
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
*/

// re2c:api:sigil = #;
/*!use:re2c
  re2c:api:sigil = #;
*/

// re2c:api:sigil = @@;
/*!use:re2c
  re2c:api:sigil = @@;
*/

// re2c:cond:goto@cond = #;
// re2c:api:sigil = #;
/*!use:re2c
  re2c:cond:goto@cond = #;
  re2c:api:sigil = #;
*/

// re2c:cond:goto@cond = #;
// re2c:api:sigil = @@;
/*!use:re2c
  re2c:cond:goto@cond = #;
  re2c:api:sigil = @@;
*/

// re2c:cond:goto@cond = @@;
// re2c:api:sigil = #;
/*!use:re2c
  re2c:cond:goto@cond = @@;
  re2c:api:sigil = #;
*/

// re2c:cond:goto@cond = @@;
// re2c:api:sigil = @@;
/*!use:re2c
  re2c:cond:goto@cond = @@;
  re2c:api:sigil = @@;
*/

// re2c:cond:goto = "goto #;";
// re2c:api:sigil = #;
/*!use:re2c
  re2c:cond:goto = "goto #;";
  re2c:api:sigil = #;
*/

// re2c:cond:goto = "goto #;";
// re2c:api:sigil = @@;
/*!use:re2c
  re2c:cond:goto = "goto #;";
  re2c:api:sigil = @@;
*/

// re2c:cond:goto = "goto #;";
// re2c:cond:goto@cond = #;
// re2c:api:sigil = #;
/*!use:re2c
  re2c:cond:goto = "goto #;";
  re2c:cond:goto@cond = #;
  re2c:api:sigil = #;
*/

// re2c:cond:goto = "goto #;";
// re2c:cond:goto@cond = #;
// re2c:api:sigil = @@;
/*!use:re2c
  re2c:cond:goto = "goto #;";
  re2c:cond:goto@cond = #;
  re2c:api:sigil = @@;
*/

// re2c:cond:goto = "goto #;";
// re2c:cond:goto@cond = @@;
// re2c:api:sigil = #;
/*!use:re2c
  re2c:cond:goto = "goto #;";
  re2c:cond:goto@cond = @@;
  re2c:api:sigil = #;
*/

// re2c:cond:goto = "goto #;";
// re2c:cond:goto@cond = @@;
// re2c:api:sigil = @@;
/*!use:re2c
  re2c:cond:goto = "goto #;";
  re2c:cond:goto@cond = @@;
  re2c:api:sigil = @@;
*/

// re2c:cond:goto = "goto @@;";
// re2c:api:sigil = #;
/*!use:re2c
  re2c:cond:goto = "goto @@;";
  re2c:api:sigil = #;
*/

// re2c:cond:goto = "goto @@;";
// re2c:api:sigil = @@;
/*!use:re2c
  re2c:cond:goto = "goto @@;";
  re2c:api:sigil = @@;
*/

// re2c:cond:goto = "goto @@;";
// re2c:cond:goto@cond = #;
// re2c:api:sigil = #;
/*!use:re2c
  re2c:cond:goto = "goto @@;";
  re2c:cond:goto@cond = #;
  re2c:api:sigil = #;
*/

// re2c:cond:goto = "goto @@;";
// re2c:cond:goto@cond = #;
// re2c:api:sigil = @@;
/*!use:re2c
  re2c:cond:goto = "goto @@;";
  re2c:cond:goto@cond = #;
  re2c:api:sigil = @@;
*/

// re2c:cond:goto = "goto @@;";
// re2c:cond:goto@cond = @@;
// re2c:api:sigil = #;
/*!use:re2c
  re2c:cond:goto = "goto @@;";
  re2c:cond:goto@cond = @@;
  re2c:api:sigil = #;
*/

// re2c:cond:goto = "goto @@;";
// re2c:cond:goto@cond = @@;
// re2c:api:sigil = @@;
/*!use:re2c
  re2c:cond:goto = "goto @@;";
  re2c:cond:goto@cond = @@;
  re2c:api:sigil = @@;
*/

