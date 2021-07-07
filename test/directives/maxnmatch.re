// re2c $INPUT -o $OUTPUT -i --posix-captures
// Test `maxnmatch:re2c` directive (global or with block list).

// maxnmatch:re2c (expect 4)
/*!maxnmatch:re2c */

// maxnmatch:re2c:x1 (expect 1)
/*!maxnmatch:re2c:x1 */

// maxnmatch:re2c:x1:y2 (expect 2)
/*!maxnmatch:re2c:x1:y2 */

// maxnmatch:re2c:y2:z4 (expect 4)
/*!maxnmatch:re2c:y2:z4 */

// maxnmatch:re2c:z4:x1 (expect 4)
/*!maxnmatch:re2c:z4:x1 */

// maxnmatch:re2c:x1:y2:z4 (expect 4)
/*!maxnmatch:re2c:x1:y2:z4 */

/*!re2c:x1
    "a" { a }
    *   { x }
*/

/*!re2c:y2
    ("b") { b }
    *     { y }
*/

/*!re2c:z4
    ((("c"))) { c }
    *         { z }
*/

