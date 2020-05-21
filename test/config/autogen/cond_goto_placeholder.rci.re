/*!rules:re2c
  <c1> [a] :=> c2
  <c2> [b] :=> c1
  <*> * { x }
*/

// re2c:placeholder = #;
/*!use:re2c
  re2c:placeholder = #;
*/

// re2c:placeholder = @@;
/*!use:re2c
  re2c:placeholder = @@;
*/

// re2c:cond:goto@cond = #;
// re2c:placeholder = #;
/*!use:re2c
  re2c:cond:goto@cond = #;
  re2c:placeholder = #;
*/

// re2c:cond:goto@cond = #;
// re2c:placeholder = @@;
/*!use:re2c
  re2c:cond:goto@cond = #;
  re2c:placeholder = @@;
*/

// re2c:cond:goto@cond = @@;
// re2c:placeholder = #;
/*!use:re2c
  re2c:cond:goto@cond = @@;
  re2c:placeholder = #;
*/

// re2c:cond:goto@cond = @@;
// re2c:placeholder = @@;
/*!use:re2c
  re2c:cond:goto@cond = @@;
  re2c:placeholder = @@;
*/

// re2c:cond:goto = "goto #;";
// re2c:placeholder = #;
/*!use:re2c
  re2c:cond:goto = "goto #;";
  re2c:placeholder = #;
*/

// re2c:cond:goto = "goto #;";
// re2c:placeholder = @@;
/*!use:re2c
  re2c:cond:goto = "goto #;";
  re2c:placeholder = @@;
*/

// re2c:cond:goto = "goto #;";
// re2c:cond:goto@cond = #;
// re2c:placeholder = #;
/*!use:re2c
  re2c:cond:goto = "goto #;";
  re2c:cond:goto@cond = #;
  re2c:placeholder = #;
*/

// re2c:cond:goto = "goto #;";
// re2c:cond:goto@cond = #;
// re2c:placeholder = @@;
/*!use:re2c
  re2c:cond:goto = "goto #;";
  re2c:cond:goto@cond = #;
  re2c:placeholder = @@;
*/

// re2c:cond:goto = "goto #;";
// re2c:cond:goto@cond = @@;
// re2c:placeholder = #;
/*!use:re2c
  re2c:cond:goto = "goto #;";
  re2c:cond:goto@cond = @@;
  re2c:placeholder = #;
*/

// re2c:cond:goto = "goto #;";
// re2c:cond:goto@cond = @@;
// re2c:placeholder = @@;
/*!use:re2c
  re2c:cond:goto = "goto #;";
  re2c:cond:goto@cond = @@;
  re2c:placeholder = @@;
*/

// re2c:cond:goto = "goto @@;";
// re2c:placeholder = #;
/*!use:re2c
  re2c:cond:goto = "goto @@;";
  re2c:placeholder = #;
*/

// re2c:cond:goto = "goto @@;";
// re2c:placeholder = @@;
/*!use:re2c
  re2c:cond:goto = "goto @@;";
  re2c:placeholder = @@;
*/

// re2c:cond:goto = "goto @@;";
// re2c:cond:goto@cond = #;
// re2c:placeholder = #;
/*!use:re2c
  re2c:cond:goto = "goto @@;";
  re2c:cond:goto@cond = #;
  re2c:placeholder = #;
*/

// re2c:cond:goto = "goto @@;";
// re2c:cond:goto@cond = #;
// re2c:placeholder = @@;
/*!use:re2c
  re2c:cond:goto = "goto @@;";
  re2c:cond:goto@cond = #;
  re2c:placeholder = @@;
*/

// re2c:cond:goto = "goto @@;";
// re2c:cond:goto@cond = @@;
// re2c:placeholder = #;
/*!use:re2c
  re2c:cond:goto = "goto @@;";
  re2c:cond:goto@cond = @@;
  re2c:placeholder = #;
*/

// re2c:cond:goto = "goto @@;";
// re2c:cond:goto@cond = @@;
// re2c:placeholder = @@;
/*!use:re2c
  re2c:cond:goto = "goto @@;";
  re2c:cond:goto@cond = @@;
  re2c:placeholder = @@;
*/

