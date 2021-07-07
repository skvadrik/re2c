// re2c $INPUT -o $OUTPUT -if
// This test is for `getstate:re2c` with a list of blocks
// with mixed `use:re2c` and non-use blocks.

// `getstate:re2c:y` (start in y)
/*!getstate:re2c:y */

// `getstate:re2c:z:x` (start in z)
/*!getstate:re2c:z:x */

// `getstate:re2c:y:x:z` (start in y)
/*!getstate:re2c:y:x:z */

// rules block w
/*!rules:re2c:w
    * { w }
*/

// use block (expect a local state switch for this block only)
/*!use:re2c:w */

// global block x (no start label)
/*!re2c:x
    * { x }
*/

// use block (expect a local state switch for this block only)
/*!use:re2c */

// global block y (with start label)
/*!re2c:y
    !use:w;
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
