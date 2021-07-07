// re2c $INPUT -o $OUTPUT -if
// This test is for global `getstate:re2c` with `use:re2c` and non-use blocks.

// global `getstate:re2c` including y, z and unnamed blocks,
// with start label in the first unnamed block
/*!getstate:re2c */

// rules block
/*!rules:re2c:x
    * { x }
*/

// use block (expect a local state switch for this block only)
/*!use:re2c:x */

// unnamed global block that includes x (has start label)
/*!re2c
    !use:x;
*/

// local block y (no start label)
/*!local:re2c:y
    * { y }
*/

// global block z that includes x (no start label)
/*!re2c:z
    !use:x;
*/

// unnamed local block (no start label)
/*!local:re2c
    * { ? }
*/

// use block (expect a local state switch for this block only)
/*!use:re2c */
