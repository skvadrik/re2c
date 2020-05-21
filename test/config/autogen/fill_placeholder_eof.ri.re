/*!rules:re2c
  [a] { a }
  *   { x }
*/

// re2c:eof = 0;
// re2c:placeholder = need;
// re2c:define:YYFILL = "fill(@@)";
/*!use:re2c
  re2c:eof = 0;
  re2c:placeholder = need;
  re2c:define:YYFILL = "fill(@@)";
  $ { eof }
*/

// re2c:eof = 0;
// re2c:placeholder = need;
// re2c:define:YYFILL = "fill(need);";
/*!use:re2c
  re2c:eof = 0;
  re2c:placeholder = need;
  re2c:define:YYFILL = "fill(need);";
  $ { eof }
*/

// re2c:eof = 0;
// re2c:placeholder = @@;
// re2c:define:YYFILL = "fill(@@)";
/*!use:re2c
  re2c:eof = 0;
  re2c:placeholder = @@;
  re2c:define:YYFILL = "fill(@@)";
  $ { eof }
*/

// re2c:eof = 0;
// re2c:placeholder = @@;
// re2c:define:YYFILL = "fill(need);";
/*!use:re2c
  re2c:eof = 0;
  re2c:placeholder = @@;
  re2c:define:YYFILL = "fill(need);";
  $ { eof }
*/

// re2c:eof = 0;
// re2c:define:YYFILL@len = @@;
// re2c:placeholder = need;
// re2c:define:YYFILL = "fill(@@)";
/*!use:re2c
  re2c:eof = 0;
  re2c:define:YYFILL@len = @@;
  re2c:placeholder = need;
  re2c:define:YYFILL = "fill(@@)";
  $ { eof }
*/

// re2c:eof = 0;
// re2c:define:YYFILL@len = @@;
// re2c:placeholder = need;
// re2c:define:YYFILL = "fill(need);";
/*!use:re2c
  re2c:eof = 0;
  re2c:define:YYFILL@len = @@;
  re2c:placeholder = need;
  re2c:define:YYFILL = "fill(need);";
  $ { eof }
*/

// re2c:eof = 0;
// re2c:define:YYFILL@len = @@;
// re2c:placeholder = @@;
// re2c:define:YYFILL = "fill(@@)";
/*!use:re2c
  re2c:eof = 0;
  re2c:define:YYFILL@len = @@;
  re2c:placeholder = @@;
  re2c:define:YYFILL = "fill(@@)";
  $ { eof }
*/

// re2c:eof = 0;
// re2c:define:YYFILL@len = @@;
// re2c:placeholder = @@;
// re2c:define:YYFILL = "fill(need);";
/*!use:re2c
  re2c:eof = 0;
  re2c:define:YYFILL@len = @@;
  re2c:placeholder = @@;
  re2c:define:YYFILL = "fill(need);";
  $ { eof }
*/

// re2c:eof = 0;
// re2c:define:YYFILL@len = need;
// re2c:placeholder = need;
// re2c:define:YYFILL = "fill(@@)";
/*!use:re2c
  re2c:eof = 0;
  re2c:define:YYFILL@len = need;
  re2c:placeholder = need;
  re2c:define:YYFILL = "fill(@@)";
  $ { eof }
*/

// re2c:eof = 0;
// re2c:define:YYFILL@len = need;
// re2c:placeholder = need;
// re2c:define:YYFILL = "fill(need);";
/*!use:re2c
  re2c:eof = 0;
  re2c:define:YYFILL@len = need;
  re2c:placeholder = need;
  re2c:define:YYFILL = "fill(need);";
  $ { eof }
*/

// re2c:eof = 0;
// re2c:define:YYFILL@len = need;
// re2c:placeholder = @@;
// re2c:define:YYFILL = "fill(@@)";
/*!use:re2c
  re2c:eof = 0;
  re2c:define:YYFILL@len = need;
  re2c:placeholder = @@;
  re2c:define:YYFILL = "fill(@@)";
  $ { eof }
*/

// re2c:eof = 0;
// re2c:define:YYFILL@len = need;
// re2c:placeholder = @@;
// re2c:define:YYFILL = "fill(need);";
/*!use:re2c
  re2c:eof = 0;
  re2c:define:YYFILL@len = need;
  re2c:placeholder = @@;
  re2c:define:YYFILL = "fill(need);";
  $ { eof }
*/

