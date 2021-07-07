// re2c $INPUT -o $OUTPUT -i
// Test `max:re2c` directive (global or with block list).

// max:re2c (expect 4)
/*!max:re2c */

// max:re2c:x1 (expect 1)
/*!max:re2c:x1 */

// max:re2c:x1:y2 (expect 2)
/*!max:re2c:x1:y2 */

// max:re2c:y2:z4 (expect 4)
/*!max:re2c:y2:z4 */

// max:re2c:z4:x1 (expect 4)
/*!max:re2c:z4:x1 */

// max:re2c:x1:y2:z4 (expect 4)
/*!max:re2c:x1:y2:z4 */

/*!re2c:x1
    "a" { a }
    *   { x }
*/

/*!re2c:y2
    "bb" { b }
    *    { y }
*/

/*!re2c:z4
    "cccc" { c }
    *      { z }
*/

