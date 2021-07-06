// re2c $INPUT -o $OUTPUT -if
// This test is for `getstate:re2c` with a list of blocks.

// `getstate:re2c:y` (start in y)
/*!getstate:re2c:y */

// `getstate:re2c:z:x` (start in z)
/*!getstate:re2c:z:x */

// `getstate:re2c:y:x:z` (start in y)
/*!getstate:re2c:y:x:z */

// global block w (no rules)
/*!re2c:w
    // no rules
*/

// global block x (no start label)
/*!re2c:x
    * { x }
*/

// global block y (with start label)
/*!re2c:y
    * { y }
*/

// local block z (with start label)
/*!local:re2c:z
    * { z }
*/

// the same directives at the end of file (in different order)
// should be no different from the ones at the beginning of the file

// `getstate:re2c:y:x:z` (start in y)
/*!getstate:re2c:y:x:z */

// `getstate:re2c:z:x` (start in z)
/*!getstate:re2c:z:x */

// `getstate:re2c:y` (start in y)
/*!getstate:re2c:y */
