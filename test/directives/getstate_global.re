// re2c $INPUT -o $OUTPUT -if
// This test is for `getstate:re2c` without a list of blocks.

// global `getstate:re2c` (should include x, y, z with start in x)
/*!getstate:re2c */

// global block w (no rules)
/*!re2c:w
    // no rules
*/

// global `getstate:re2c` (should include x, y, z with start in x)
/*!getstate:re2c */

// global block x (with start label)
/*!re2c:x
    * { x }
*/

// global `getstate:re2c` (should include x, y, z with start in x)
/*!getstate:re2c */

// global block y (no start label)
/*!re2c:y
    * { y }
*/

// global `getstate:re2c` (should include x, y, z with start in x)
/*!getstate:re2c */

// local block z (no start label)
/*!local:re2c:z
    * { z }
*/

// global `getstate:re2c` (should include x, y, z with start in x)
/*!getstate:re2c */
