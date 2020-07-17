// re2c $INPUT -o $OUTPUT -ri
/*!rules:re2c
  [a] { a }
  *   { x }
*/

// re2c:api:sigil = need;
// re2c:define:YYFILL = "fill(@@)";
/*!use:re2c
  re2c:api:sigil = need;
  re2c:define:YYFILL = "fill(@@)";
*/

// re2c:api:sigil = need;
// re2c:define:YYFILL = "fill(need);";
/*!use:re2c
  re2c:api:sigil = need;
  re2c:define:YYFILL = "fill(need);";
*/

// re2c:api:sigil = @@;
// re2c:define:YYFILL = "fill(@@)";
/*!use:re2c
  re2c:api:sigil = @@;
  re2c:define:YYFILL = "fill(@@)";
*/

// re2c:api:sigil = @@;
// re2c:define:YYFILL = "fill(need);";
/*!use:re2c
  re2c:api:sigil = @@;
  re2c:define:YYFILL = "fill(need);";
*/

// re2c:define:YYFILL@len = @@;
// re2c:api:sigil = need;
// re2c:define:YYFILL = "fill(@@)";
/*!use:re2c
  re2c:define:YYFILL@len = @@;
  re2c:api:sigil = need;
  re2c:define:YYFILL = "fill(@@)";
*/

// re2c:define:YYFILL@len = @@;
// re2c:api:sigil = need;
// re2c:define:YYFILL = "fill(need);";
/*!use:re2c
  re2c:define:YYFILL@len = @@;
  re2c:api:sigil = need;
  re2c:define:YYFILL = "fill(need);";
*/

// re2c:define:YYFILL@len = @@;
// re2c:api:sigil = @@;
// re2c:define:YYFILL = "fill(@@)";
/*!use:re2c
  re2c:define:YYFILL@len = @@;
  re2c:api:sigil = @@;
  re2c:define:YYFILL = "fill(@@)";
*/

// re2c:define:YYFILL@len = @@;
// re2c:api:sigil = @@;
// re2c:define:YYFILL = "fill(need);";
/*!use:re2c
  re2c:define:YYFILL@len = @@;
  re2c:api:sigil = @@;
  re2c:define:YYFILL = "fill(need);";
*/

// re2c:define:YYFILL@len = need;
// re2c:api:sigil = need;
// re2c:define:YYFILL = "fill(@@)";
/*!use:re2c
  re2c:define:YYFILL@len = need;
  re2c:api:sigil = need;
  re2c:define:YYFILL = "fill(@@)";
*/

// re2c:define:YYFILL@len = need;
// re2c:api:sigil = need;
// re2c:define:YYFILL = "fill(need);";
/*!use:re2c
  re2c:define:YYFILL@len = need;
  re2c:api:sigil = need;
  re2c:define:YYFILL = "fill(need);";
*/

// re2c:define:YYFILL@len = need;
// re2c:api:sigil = @@;
// re2c:define:YYFILL = "fill(@@)";
/*!use:re2c
  re2c:define:YYFILL@len = need;
  re2c:api:sigil = @@;
  re2c:define:YYFILL = "fill(@@)";
*/

// re2c:define:YYFILL@len = need;
// re2c:api:sigil = @@;
// re2c:define:YYFILL = "fill(need);";
/*!use:re2c
  re2c:define:YYFILL@len = need;
  re2c:api:sigil = @@;
  re2c:define:YYFILL = "fill(need);";
*/

