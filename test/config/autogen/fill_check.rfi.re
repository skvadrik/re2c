// re2c $INPUT -o $OUTPUT -rfi
/*!rules:re2c
  [a] { a }
  *   { x }
*/

/*!use:re2c
*/

// re2c:yyfill:check = 0;
/*!use:re2c
  re2c:yyfill:check = 0;
*/

// re2c:yyfill:check = 1;
/*!use:re2c
  re2c:yyfill:check = 1;
*/

