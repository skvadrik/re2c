// re2c $INPUT -o $OUTPUT --tags -s
// Test `stags:re2c` and `mtags:re2c` directives (global or with block list).
/*!re2c re2c:yyfill:enable = 0; */

// stags:re2c
/*!stags:re2c format = "@@;";*/
// mtags:re2c
/*!mtags:re2c format = "@@;";*/


// tags have common 'yyt' prefix, so tag variables are shared between blocks

// stags:re2c:x1
/*!stags:re2c:x1 format = "@@;";*/
// mtags:re2c:x1
/*!mtags:re2c:x1 format = "@@;";*/

// stags:re2c:y1
/*!stags:re2c:y1 format = "@@;";*/
// mtags:re2c:y1
/*!mtags:re2c:y1 format = "@@;";*/

// stags:re2c:x1:y1
/*!stags:re2c:x1:y1 format = "@@;"; */
// mtags:re2c:x1:y1
/*!mtags:re2c:x1:y1 format = "@@;"; */


// tags have custom block-specific prefixes, so tag variables are separate

// stags:re2c:x2
/*!stags:re2c:x2 format = "@@;";*/
// mtags:re2c:x2
/*!mtags:re2c:x2 format = "@@;";*/

// stags:re2c:y2
/*!stags:re2c:y2 format = "@@;";*/
// mtags:re2c:y2
/*!mtags:re2c:y2 format = "@@;";*/

// stags:re2c:x2:y2
/*!stags:re2c:x2:y2 format = "@@;"; */
// mtags:re2c:x2:y2
/*!mtags:re2c:x2:y2 format = "@@;"; */


// rules:re2c:x
/*!rules:re2c:x
    @x1 (@x2 [a])? { a }
*/

// rules:re2c:y
/*!rules:re2c:y
    @y1 (@y2 #y3 [b])? { b }
*/


// re2c:x1
/*!re2c:x1
    !use:x;
*/

// re2c:y1
/*!re2c:y1
    !use:y;
*/


// re2c:x2
/*!re2c:x2
    !use:x;
    re2c:tags:prefix = "x2_";
*/

// re2c:y2
/*!re2c:y2
    !use:y;
    re2c:tags:prefix = "y2_";
*/
