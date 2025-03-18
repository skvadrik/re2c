// re2c $INPUT -o $OUTPUT -i

/*!re2c
  re2c:yyfill:enable = 0;
*/

/*!rules:re2c:b1
  [a] { a }
  * { * }
*/

/*!rules:re2c:b2
  "za" { a }
  "zabc" { abc }
  "zabcde" { abcde }
  * { * }
*/

/*!rules:re2c:b3
  [a]* { a }
  * { * }
*/

/*!rules:re2c:b4
  [a]* { a }
*/

// b1 (match-code-point)
/*!use:re2c:b1 */
// b1 (match-error)
/*!use:re2c:b1 re2c:on-default = match-error; */

// b2 (match-code-point)
/*!use:re2c:b2 */
// b2 (match-error)
/*!use:re2c:b2 re2c:on-default = match-error; */

// b2 -s (match-code-point)
/*!use:re2c:b2 re2c:nested-ifs = 1; */
// b2 -s (match-error)
/*!use:re2c:b2 re2c:nested-ifs = 1; re2c:on-default = match-error; */

// b3 (match-code-point)
/*!use:re2c:b3 */
// b3 (match-error) - default rule is shadowed, as they both match empty string
/*!use:re2c:b3 re2c:on-default = match-error; */

// b4 (match-code-point)
/*!use:re2c:b4 */
// b4 (match-error)
/*!use:re2c:b4 re2c:on-default = match-error; */
