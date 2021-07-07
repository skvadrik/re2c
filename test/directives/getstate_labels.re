// re2c $INPUT -o $OUTPUT -if
// This test is for `getstate:re2c` and fill labels.

// global `getstate:re2c` (start in x)
/*!getstate:re2c */

// `getstate:re2c` for y, x, z (start in y)
/*!getstate:re2c:y:x:z */

// global block w (no rules)
/*!re2c:w
    // no rules
*/

// global block x (with start label)
/*!re2c:x
    * { x }
*/

// unnamed global block (no rules, but changes fill label to 'Ly')
/*!re2c
    re2c:label:yyFillLabel = "Ly";
*/

// global block y (with start label)
/*!re2c:y
    * { y }
*/

// unnamed global block (no rules, but changes fill label to 'L??')
/*!re2c
    re2c:label:yyFillLabel = "L??";
*/

// local block z (no start label)
/*!local:re2c:z
    * { z }
    re2c:label:yyFillLabel = "Lz";
*/

// the same directives at the end of file (in different order)
// should be no different from the ones at the beginning of the file

// `getstate:re2c` for y, x, z (start in y)
/*!getstate:re2c:y:x:z */

// global `getstate:re2c` (start in x)
/*!getstate:re2c */
