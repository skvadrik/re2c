// re2c $INPUT -o $OUTPUT -ri
/*!rules:re2c
  [a] { a }
  *   { x }
*/

// re2c:eof = 0;
/*!use:re2c
  re2c:eof = 0;
  $ { eof }
*/

// re2c:eof = 0;
// re2c:yyfill:check = 0;
/*!use:re2c
  re2c:eof = 0;
  re2c:yyfill:check = 0;
  $ { eof }
*/

// re2c:eof = 0;
// re2c:yyfill:check = 1;
/*!use:re2c
  re2c:eof = 0;
  re2c:yyfill:check = 1;
  $ { eof }
*/

