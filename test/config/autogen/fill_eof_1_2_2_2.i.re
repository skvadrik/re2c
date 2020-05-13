// re2c:eof = 0;
// re2c:define:YYFILL = "fill(need);";
// re2c:define:YYFILL@len = need;
// re2c:yyfill:check = 1;
/*!re2c
  re2c:eof = 0;
  re2c:define:YYFILL = "fill(need);";
  re2c:define:YYFILL@len = need;
  re2c:yyfill:check = 1;
  $ { eof }
  [a] { a }
  *   { x }
*/
