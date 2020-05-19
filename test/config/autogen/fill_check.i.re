/*!re2c
  [a] { a }
  *   { x }
*/

// re2c:yyfill:check = 0;
/*!re2c
  re2c:yyfill:check = 0;
  [a] { a }
  *   { x }
*/

// re2c:yyfill:check = 1;
/*!re2c
  re2c:yyfill:check = 1;
  [a] { a }
  *   { x }
*/

